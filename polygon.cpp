#include<vector>
#include"utils.h"
#include "triangulation.h"
#include "polygon.h"

using namespace std;

/* Implement class stuff of polygon */
polygon::polygon(){};
polygon::polygon(vector<v2f> data) {
    this->data = data;
    //this->AdvancingFront = data;
}

//returns 0 if the point p is on the border or is outside the poligon. Else it returns >= 1
double polygon::IsPointInPolygon(v2f &p) {
    vector<v2f> pol = data;
    for (auto& pt : pol) {
        pt = pt - p;
    }
    double w=0;
    for (int i = 0;i < pol.size() - 1;i++) {
        //cout<< "i= "<< i << endl;
        //cout<< "w= "<< w<< endl;
        if (pol[i].y * pol[i + 1].y < 0.) {
            double r = pol[i].x+pol[i].y*(pol[i+1].x-pol[i].x)/
                (pol[i].y-pol[i+1].y);
            if (r > 0.) {
                if(pol[i].y<0.) w++; else w--;
            }
        }
        else if(pol[i].y == 0. && pol[i].x >0.) {
            if(pol[i+1].y >0.){
                w = w + 0.5;
            }else{
                w = w - 0.5;
            }
        }else if(pol[i+1].y == 0. && pol[i+1].x >0.) {
            if(pol[i].y < 0.){
                w= w + 0.5;
            }else{
                w= w - 0.5;
            }
        }
    }
    return w;
}

void polygon::GenerateAdvancingFront(double h_boundary) {
    AdvancingFront = {};
    for (int i = 0;i < data.size() - 1;i++) {
        double n = floor((data[i+1]-data[i]).len()/h_boundary);
        for (int j = 0;j < n;j++) {
            AdvancingFront.push_back({(n-j)/n*data[i].x + j/n*data[i+1].x,
                                      (n-j)/n*data[i].y + j/n*data[i+1].y});
        }
    }
    for(int i=0;i<AdvancingFront.size() - 1;i++){
        //Calculate the normal to the boundary
        v2f A = AdvancingFront[i];
        v2f B = AdvancingFront[i+1];
        v2f n = (B-A).getortogonal().getnormalized();
        v2f N = (A+B); N.x /= 2.; N.y /= 2.;
        N.x += n.x*sqrt(3.)/2.*(B-A).len();
        N.y += n.y*sqrt(3.)/2.*(B-A).len();
        if(IsPointInPolygon(N) > 0){
            AdvancingFront.insert(AdvancingFront.begin() + i + 1, N);
            i++;
        }
    }
}
