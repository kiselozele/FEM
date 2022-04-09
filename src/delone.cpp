#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

#include "point.h"
#include "delone.h"


//       C.
//      /  \ 
//   b /     \ a
//    /        \ 
// A./__ ___ ___.\ B
//        c
// Vertices[0] = A, [1] = B, [2] = C
// Sides[0] = a, [1] = b, [2] = c

bool Delone::IsPointInTriangle(point& P, int Triangle_id) {
	point A = points[Triangles[Triangle_id][0]];
	point B = points[Triangles[Triangle_id][1]];
	point C = points[Triangles[Triangle_id][2]];
	return ((B-A)^(P-A)) >= 0 && ((B-C)^(P-C)) >= 0 && ((A-C)^(P-C)) >= 0;
}

bool Delone::IsPointOnEdgeOfTriangle(point& P, int Triangle_id) {
	point A = points[Triangles[Triangle_id][0]];
	point B = points[Triangles[Triangle_id][1]];
	point C = points[Triangles[Triangle_id][2]];
	return (((B - A) ^ (P - A)) == 0 && ((B - C) ^ (P - C)) >= 0 && ((A - C) ^ (P - C)) >= 0)||
		(((B - A) ^ (P - A)) >= 0 && ((B - C) ^ (P - C)) == 0 && ((A - C) ^ (P - C)) >= 0) ||
		(((B - A) ^ (P - A)) >= 0 && ((B - C) ^ (P - C)) >= 0 && ((A - C) ^ (P - C)) == 0);
}

void Delone::add_point(point &P) {
	points.push_back(P);
	int P_ind = points.size()-1;

}
