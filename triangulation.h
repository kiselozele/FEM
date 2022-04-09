#ifndef TRIANGULATION
#define TRIANGULATION

#include <math.h>
#include <iostream>
#include <vector>
#include <string>
#include "polygon.h"
#include "utils.h"

using namespace std;

void plot_delaunay(vector<triangle> triangles, string image_name);

void plot_polygon(vector<v2f> points, string image_name);

class triangulation : polygon{

public:
    triangulation(){};
    triangulation(vector<v2f> Points, vector<v2f> Region);
    void create();
    
    void refine(double tol);
    triangle StartingTriangle;
    vector<v2f> Points;
    vector<v2f> AdvancingFront;
    vector<v2f> Region;//Starting area
    vector<triangle> VecTriangles;
    int iteration;
};



#endif
