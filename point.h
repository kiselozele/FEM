#ifndef POINTS
#define POINTS

#include <vector>
using namespace std;

struct point {
public:
	point();
	point(double x, double y);

	double x;
	double y;
};


/*

public:
	point();
	point(double x, double y);
	point(int id, double x, double y, vector<int>& triangle_index, 
		vector<int>& triangle_seq, vector<int>& edges);

	point operator + (point const &p);
	point operator - (point const &p);
	double operator ^ (point const &p);
	double operator * (point const &p);
	double len();
	
	int id;
	double x;
	double y;
	vector<int> triangle_index;
	vector<int> triangle_seq;
	void remove_triangle(int position); //removes triangle_index & triangle_seq at index
	void push_triangle(int index, int seq);// adds new triangle
	
	vector<int> edges;
	void add_edge(int id);
	void remove_edge(int id);// removes given edge based on point id
};

double cos(point v1, point v2);
double sin(point v1, point v2);
*/
#endif