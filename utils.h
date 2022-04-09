#ifndef FEM_UTILS
#define FEM_UTILS

#include <math.h>
#include <vector>

using namespace std;

typedef struct v2f{
	v2f();
	v2f(double x, double y);
	double len();
	void normalize();
	v2f getnormalized();
	v2f getortogonal();
	void orthogonalize();
	double x, y;

bool operator ==(const v2f& v);
v2f operator +(const v2f& v);
v2f operator -(const v2f& v);
double operator *(const v2f& v);
double operator ^(const v2f& v);
} v2f_st;


double cos(v2f v1, v2f v2);
double sin(v2f v1, v2f v2);

struct edge {
    edge();
    edge(v2f a, v2f b);
    v2f a, b;
    double len;
    void edit(v2f a, v2f b);
    bool operator ==(const edge& e);
};

struct triangle {
    triangle();
    triangle(v2f A, v2f B, v2f C);
    bool IsPointInCircumCircle(v2f P);
    double GetArea();
    v2f CircumCenter;
    vector<v2f> points;
    edge a, b, c;
    vector<edge> edges;
    double CircumRadius, alpha, beta, gamma;
    bool IsBad;
	bool operator== (const triangle& rt);

};

#endif
