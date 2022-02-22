#ifndef DELONE
#define DELONE

class Delone {
	Delone();
	vector<int> point_ids;
	vector<vector<int>> Triangles;//Triangles[triangle_id][triangle_seq] = point_id
	vector<point> points;
	bool IsPointInTriangle(point& P, int Triangle_id);
	bool IsPointOnEdgeOfTriangle(point& P, int Triangle_id);

	void add_point(point &P);

};


#endif