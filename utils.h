#ifndef FEM_UTILS
#define FEM_UTILS

#include <math.h>
#include <vector>

using namespace std;

typedef struct v2f{
    v2f();
    v2f(double x, double y);   
    bool operator ==(v2f v);
    v2f operator + (v2f v);
    v2f operator - (v2f v);
    double operator *(v2f v);
    double operator ^(v2f v);
    double len();
    v2f getnormalized();
    void normalize();
    v2f getortogonal();
    void orthogonalize();
    double x, y;
} v2f;

double cos(v2f v1, v2f v2);
double sin(v2f v1, v2f v2);

struct edge {
    edge();
    edge(v2f a, v2f b);
    v2f a, b;
    double len;
    bool operator == (edge e);
    void edit(v2f a, v2f b);
};

struct triangle {
    triangle();
    triangle(v2f A, v2f B, v2f C);
    bool IsPointInCircumCircle(v2f P);
    bool operator == (triangle t);
    double GetArea();
    v2f CircumCenter;
    vector<v2f> points;
    edge a, b, c;
    vector<edge> edges;
    double CircumRadius, alpha, beta, gamma;
    bool IsBad;
};

#endif
