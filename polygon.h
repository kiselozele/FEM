#ifndef POLYGON
#define POLYGON
#include"utils.h"
#include<vector>
using namespace std;

class polygon {
public:
    polygon(){};
    polygon(vector<v2f> data) {
        this->data = data;
        //this->AdvancingFront = data;
    }
    double IsPointInPolygon(v2f &p) {
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

    void GenerateAdvancingFront(double h_boundary) {
        AdvancingFront = {};
        for (int i = 0;i < data.size() - 1;i++) {
            double n = floor((data[i+1]-data[i]).len()/h_boundary);
            for (int j = 0;j < n;j++) {
                AdvancingFront.push_back({(n-j)/n*data[i].x + j/n*data[i+1].x, 
                                          (n-j)/n*data[i].y + j/n*data[i+1].y});
            }
        }
        //???
    }

    vector<v2f> data;
    vector<v2f> AdvancingFront;
};



#endif // !POLYGON
