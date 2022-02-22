#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <random>
//#include "point.h"
//#include "elt.h"
//#include "matrix.h"
//#include "FEM.h"
//#include "delone.h"
#include "triangulation.h"
#include "polygon.h"
using namespace std;


//TODO:
//DONE   matrix.write_to_txt_file()
//DONE   assemble global_matrix_stiffness & local_matrix_stiffness
//       tinyexpr++ into code
//DONE   struct definition of an element
//NOT DOING   gnuplot_functions in header?
//DONE   fix matrix.transpose() to "return" a matrix

/*
void plot_2d_NEW(vector<double>& v1, vector<double>& v2, vector<vector<double>>& v3, string image_name){

    FILE * gnuplotPipe = _popen ("gnuplot -persistant", "w"); // отваряме виртуална конзола с команда gnuplot и можем да си пишем в нея

    vector<string> commands;
   
    commands.push_back("set terminal gif animate delay 50 size 300, 300");// default размер на изображението (1024, 768)
    commands.push_back("set output '" + image_name + ".gif'"); // може да се промени на .jpeg и други, но трябва преди това set terminal jpeg

    commands.push_back("set xrange [-0.25:1]");
    commands.push_back("set yrange [0:1]");
    commands.push_back("set zrange [-0.05:0.05]");
    commands.push_back("set xyplane at 0");

    //commands.push_back("unset ztics");   
    commands.push_back("set margins 0, 0, 0, 0");
    //commands.push_back("unset border");
    commands.push_back("unset key");

    commands.push_back("set cbrange [-0.01:0.01]");

    commands.push_back("set style data lines");
    commands.push_back("set dgrid3d 10, 10");
    commands.push_back("set pm3d");

    for(int k=0;k<v3.size();k+=1){
        commands.push_back("$grid << EOD");
        for(int i=0;i<v3[k].size();i++){
                commands.push_back(to_string(v1[i]) + "\t"+ to_string(v2[i]) + "\t" + to_string(v3[k][i]));
        }
        commands.push_back("EOD");
        commands.push_back("splot '$grid' pal");
    }
    for(int i =0;i<commands.size();i++){
        fprintf(gnuplotPipe, "%s \n", commands[i].c_str());// много важно конвертиране от c++ string към c string - string.c_str()
    }
}
*/

int main() {
    /*
    FEM F;
    F.create_time_nodes(0,0.5,100);
    F.create_global_matricies();

    F.start();
    F.time_layers_Q.back().write("Q");
    F.time_layers_S.back().write("S");

    vector<double> v1;
    vector<double> v2;

    for (int i = 0;i < F.points.size();i++) {
        v1.push_back(F.points[i].x);
        v2.push_back(F.points[i].y);
    }
    vector<vector<double>> z;
    for (int i = 0;i < F.time_nodes.size();i++) {
        z.push_back(vector<double> {});
        for (int j = 0;j < F.time_layers_Q.size();j++) {
            z[i].push_back(F.time_layers_Q[i][j][0]);
        }
    }
    plot_2d_NEW(v1, v2, z, "anim");
    

    vector<v2f> points;
    cout<<"enter seed:\n";
    int seed;
    cin>> seed;
    mt19937 mt(seed);
    uniform_real_distribution<double> distx(0, 10);
    uniform_real_distribution<double> disty(0, 2);
    for(int i=0;i<2000;i++)
        points.push_back({distx(mt), disty(mt)});
    triangulation triang(points);
    triang.create();
    plot_delaunay(triang.VecTriangles, "delaunay");
    
    */

    vector<v2f> data ={
        {-1.,-1.},
        {1.,-1.},
        {1.,-0.05},
        {0.5,-0.05},
        {0.5,-0.95},
        {-0.5,-0.95},
        {-0.5,0.95},
        {0.5,0.95},
        {0.5,0.05},
        {1.,0.05},
        {1.,1.},
        {-1.,1.},
        {-1.,-1.}
    };
    plot_polygon(data, "polygon_0");
    
    polygon poly(data);
    double in;
    cout<< "enter h (double): ";
    cin>>in;
    poly.GenerateAdvancingFront(in);
    plot_polygon(poly.AdvancingFront, "polygon_1");

    system("pause");
}
