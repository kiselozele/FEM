#ifndef UTILS
#define UTILS
#include <math.h>
#include <vector>
using namespace std;
struct v2f{
    v2f() {
        x = 0.;
        y = 0.;
    }
    v2f(double x, double y) {
        this->x = x;
        this->y = y;
    }
    
    bool operator ==(v2f v) {
        if(this->x == v.x && this->y == v.y) return true;
        else return false;
    }
    v2f operator + (v2f v) {
        v2f res(this->x +v.x, this->y+v.y);
        return res;
    }
    v2f operator - (v2f v) {
        v2f res(this->x -v.x, this->y-v.y);
        return res;
    }
    double operator *(v2f v) {
        return this->x*v.x + this->y*v.y;
    }
    double operator ^(v2f v) {
        return this->x*v.y - this->y*v.x;
    }
    double len() {
        return pow(x*x + y*y, 0.5);
    }
    
    double x, y;
};

struct edge {
    edge(){};
    edge(v2f a, v2f b) {
        this->a = a;
        this->b = b;
        len = pow(pow((a-b).x,2.)+pow((a-b).y, 2.), 0.5);
    }
    v2f a, b;
    double len;
    bool operator == (edge e) {
        if(this->a == e.a && this->b == e.b) return true;
        if(this->a == e.b && this->b == e.a) return true;
        else return false;
    }
    void edit(v2f a, v2f b) {
        this->a = a;
        this->b = b;
        len = pow(pow((a-b).x,2.)+pow((a-b).y, 2.), 0.5);
    }
};

double cos(v2f v1, v2f v2) {
	return (v1 * v2) / (v1.len()*v2.len());
}

double sin(v2f v1, v2f v2) {
	return (v1 ^ v2) / (v1.len()*v2.len());
}

struct triangle {
    triangle(){};
    triangle(v2f A, v2f B, v2f C) {
        this->points.push_back(A);
        this->points.push_back(B);
        this->points.push_back(C);
        a = edge(A, B);
        this->edges.push_back(a);
        b = edge(B, C);
        this->edges.push_back(b);
        c = edge(C, A);
        this->edges.push_back(c);
        alpha = acos(cos(B-A,C-A));
        beta = acos(cos(A-B,C-B));
        gamma = acos(cos(B-C,A-C));
        CircumCenter = v2f((A.x*sin(2.*alpha)+B.x*sin(2.*beta)+C.x*sin(2.*gamma))/(sin(2.*alpha)+sin(2.*beta)+sin(2.*gamma)), 
            (A.y*sin(2.*alpha)+B.y*sin(2.*beta)+C.y*sin(2.*gamma))/(sin(2.*alpha)+sin(2.*beta)+sin(2.*gamma)));
        CircumRadius = b.len/(2.*sin(alpha));
        //float p = (a.len +b.len + c.len)/2.;
        //CircumRadius = a.len*b.len*c.len/(4.f*sqrtf((p-a.len)*(p-b.len)*(p-c.len)*p));
        IsBad = false;
    }
    bool IsPointInCircumCircle(v2f P) {
        //cout<<"distance to center: " << (CircumCenter - P).len() << " & radius: " << CircumRadius << endl;
        if((CircumCenter-P).len() < CircumRadius) return true;
        else return false;
    }
    bool operator == (triangle t) {
        if(this->points[0] == t.points[0] && this->points[1] == t.points[1] && this->points[2] == t.points[2]) return true;
        else return false;
    }
    double GetArea() {
        return b.len*sin(alpha)/2.;
    }
    v2f CircumCenter;
    vector<v2f> points;
    edge a, b, c;
    vector<edge> edges;
    double CircumRadius, alpha, beta, gamma;
    bool IsBad;
};
#endif