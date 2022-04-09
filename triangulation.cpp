#ifndef TRIANGULATION
#define TRIANGULATION
#include <math.h>
#include <iostream>
#include <vector>
#include <string>

#include "polygon.h"
#include "utils.h"
#include "triangulation.h"

using namespace std;

void plot_delaunay(vector<triangle> triangles, string image_name){

    FILE * gnuplotPipe = _popen ("gnuplot", "w"); // отваряме виртуална конзола с команда gnuplot и можем да си пишем в нея

    vector<string> commands;

    commands.push_back("set terminal pngcairo size 1920, 1920");// default размер на изображението (1024, 768)
    commands.push_back("set output '" + image_name + ".png'"); // може да се промени на .jpeg и други, но трябва преди това set terminal jpeg

    commands.push_back("set xrange [-2:2]");
    commands.push_back("set yrange [-2:2]");
    commands.push_back("set grid");

    //commands.push_back("unset ztics");
    //commands.push_back("set margins 0, 0, 0, 0");
    //commands.push_back("unset border");
    commands.push_back("unset key");

    commands.push_back("$grid << EOD");

    for (auto& triangle : triangles) {
        commands.push_back(to_string(triangle.edges[0].a.x) + " " + to_string(triangle.edges[0].a.y));
        commands.push_back(to_string(triangle.edges[1].a.x) + " " + to_string(triangle.edges[1].a.y));
        commands.push_back(to_string(triangle.edges[2].a.x) + " " + to_string(triangle.edges[2].a.y));
        commands.push_back(to_string(triangle.edges[0].a.x) + " " + to_string(triangle.edges[0].a.y));

        commands.push_back("\n");
    }
    commands.push_back("EOD");

    commands.push_back("set style line 1 linecolor rgb '#0060ad' linetype 1 linewidth 2 pointtype 7 pointsize 1.5");
    commands.push_back("plot '$grid' with linespoints linestyle 1");
    for(int i =0;i<commands.size();i++){
        fprintf(gnuplotPipe, "%s \n", commands[i].c_str());// много важно конвертиране от c++ string към c string - string.c_str()
    }
    for (int i = 0;i < commands.size();i++) {
        //cout<<commands[i] << endl;
    }
    //system("pause");
}

void plot_polygon(vector<v2f> points, string image_name){

    FILE * gnuplotPipe = _popen ("gnuplot", "w"); // отваряме виртуална конзола с команда gnuplot и можем да си пишем в нея

    vector<string> commands;

    commands.push_back("set terminal pngcairo size 1920, 1920");// default размер на изображението (1024, 768)
    commands.push_back("set output '" + image_name + ".png'"); // може да се промени на .jpeg и други, но трябва преди това set terminal jpeg

    commands.push_back("set xrange [-2:2]");
    commands.push_back("set yrange [-2:2]");
    commands.push_back("set grid");

    //commands.push_back("unset ztics");
    //commands.push_back("set margins 0, 0, 0, 0");
    //commands.push_back("unset border");
    commands.push_back("unset key");

    commands.push_back("$grid << EOD");

    for (auto& point : points) {
        commands.push_back(to_string(point.x) + " " + to_string(point.y));
    }
    commands.push_back("EOD");

    commands.push_back("set style line 1 linecolor rgb '#0060ad' linetype 1 linewidth 2 pointtype 7 pointsize 1.5");
    commands.push_back("plot '$grid' with linespoints linestyle 1");
    for(int i =0;i<commands.size();i++){
        fprintf(gnuplotPipe, "%s \n", commands[i].c_str());// много важно конвертиране от c++ string към c string - string.c_str()
    }
    for (int i = 0;i < commands.size();i++) {
        //cout<<commands[i] << endl;
    }
    //system("pause");
}


class triangulation : polygon{
public:
    triangulation(){};
    triangulation(vector<v2f> Points, vector<v2f> Region) {
        this->Points = Points;
        this->AdvancingFront = Points;
        this->Region = Region;
        //float L, R, U, D;
        //TODO Find points for startingtriangle
        double L, R = Points[0].x;
        double U, D = Points[0].y;
        iteration = 0;

        for (int i = 1;i < Points.size();i++) {
            if(Points[i].x < L) L = Points[i].x;
            if(Points[i].x > R) R = Points[i].x;
            if(Points[i].y < D) D = Points[i].y;
            if(Points[i].y > U) U = Points[i].y;
        }
        v2f S_0(L-1.,D -1.); v2f S_1 (L-1., 2.*U-D + 1.); v2f S_2(2.*R - L + 1., D - 1.);
        StartingTriangle = triangle(S_0, S_1, S_2);
    }
    void create() {
        int counter = 0;
        VecTriangles.clear();
        VecTriangles.push_back(StartingTriangle);
        for (auto& point : Points) {
            vector<triangle> BadTriangles;

            for (auto& triangle : VecTriangles) {
                triangle.IsBad = triangle.IsPointInCircumCircle(point);
                if(triangle.IsBad)
                    BadTriangles.push_back(triangle);
            }
            vector<edge> Polygon;

            for (auto& triangle : BadTriangles) {
                for (int i = 0;i < 3;i++) {
                    bool IsShared = false;
                    for (auto& triangle2 : BadTriangles) {
                        if(triangle == triangle2)
                            continue;
                        for (int j = 0;j < 3;j++) {
                            if(triangle.edges[i] == triangle2.edges[j])
                                IsShared = true;
                        }
                    }
                    if(!IsShared)
                        Polygon.push_back(triangle.edges[i]);

                }
            }

            for (int i = 0;i < VecTriangles.size();) {
                if(VecTriangles[i].IsBad == true){
                    VecTriangles.erase(VecTriangles.begin() + i);
                }
                else {
                    i++;
                }
            }
            for (auto& edge : Polygon) {
                triangle NewTriangle(edge.a, edge.b, point);
                VecTriangles.push_back(NewTriangle);
            }
            counter++;
        }

        for (auto iter = VecTriangles.begin();iter != VecTriangles.end();) {
            bool ContrainsVertex = false;
            for (int i = 0;i < 3;i++) {
                for (int j = 0;j < 3;j++) {
                    if(iter->points[i] == StartingTriangle.points[j])
                        ContrainsVertex = true;
                }
            }
            if (ContrainsVertex) {
                iter = VecTriangles.erase(iter);
            }else iter ++;
        }

        cout<< "Created a triangulation with "<< VecTriangles.size() <<
            " triangles!\n";
        plot_delaunay(this->VecTriangles, "triangulation_iteration_" + to_string(iteration));

        if(iteration == 5)
            exit(0);

        iteration++;
    }

    void refine(double tol) {
        this->create();
        while(true){
            bool AnythingToDo = false;
            for (auto& triangle : VecTriangles) {
                double Dist = (Points[0] - triangle.CircumCenter).len();
                for (auto& P : Points) {
                    if(Dist > (P-triangle.CircumCenter).len())
                        Dist = (P-triangle.CircumCenter).len();
                }

                if (triangle.CircumRadius > tol && Dist > 0.1) {
                    Points.push_back(triangle.CircumCenter);
                    AnythingToDo = true;
                }
            }
            if (!AnythingToDo) {
                break;
            }
            this->create();
        }
        plot_delaunay(VecTriangles,"img_last_triangulation_before_cut");

        vector<v2f> ReverseRegion;
        for (int i = Region.size() - 1;i >= 0;i--) {
            ReverseRegion.push_back(Region[i]);
        }
        polygon poly(ReverseRegion);

        for (int i = 0;i < Points.size();) {
            double Dist = (Points[i] - AdvancingFront[0]).len();
            for (int j = 0;j < AdvancingFront.size();j++) {
                if (Dist > (Points[i] - AdvancingFront[j]).len()) {
                    Dist = (Points[i] - AdvancingFront[j]).len();
                }
            }

            if (poly.IsPointInPolygon(Points[i]) == 0.0 && Dist > 0.001) {
                Points.erase(Points.begin() + i);
            }
            else {
                i++;
            }
        }
        this->create();
        plot_delaunay(VecTriangles,"img_after_removed_pts");

    }
    triangle StartingTriangle;
    vector<v2f> Points;
    vector<v2f> AdvancingFront;
    vector<v2f> Region;//Starting area
    vector<triangle> VecTriangles;
    int iteration;


};



#endif
