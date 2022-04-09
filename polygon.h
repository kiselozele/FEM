#ifndef FEM_POLYGON
#define FEM_POLYGON
#include<vector>


#include"utils.h"
#include "triangulation.h"

using namespace std;

class polygon {
public:
    polygon();
    polygon(vector<v2f> data);

    //returns 0 if the point p is on the border or is outside the poligon. Else it returns >= 1
    double IsPointInPolygon(v2f &p); 
    void GenerateAdvancingFront(double h_boundary);
    vector<v2f> data;
    vector<v2f> AdvancingFront;
};


#endif // !FEM_POLYGON
