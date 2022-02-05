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

	for (int i = 0;i < Triangles.size();i++) {
		if (IsPointInTriangle(P, i) == true) {
			Triangles.push_back({Triangles[i][0], Triangles[i][1], P_ind});
			points[Triangles[i][0]].push_triangle(, 0);
			points[Triangles[i][1]].push_triangle(P_ind, 1);
			points[P_ind].push_triangle(P_ind, 2);

			points[Triangles[i][0]].push_triangle(P_ind, 0);

			points[Triangles[i][0]].add_edge(P_ind);
			points[Triangles[i][1]].add_edge(P_ind);
			points[Triangles[i][2]].add_edge(P_ind);
			
			points[P_ind].add_edge(Triangles[i][0]);
			points[P_ind].add_edge(Triangles[i][1]);
			points[P_ind].add_edge(Triangles[i][2]);

			Triangles.erase(Triangles.begin() + i);
		}
	}
}
