
#include <math.h>
#include <vector>

#include "utils.h"

using namespace std;

bool 
v2f::operator ==(const v2f& v) {
    if (this->x == v.x && this->y == v.y)
	    return true;
    else
	    return false;

}
v2f 
v2f::operator +(const v2f& v) {
    v2f res(this->x + v.x, this->y + v.y);
    return res;
}
v2f 
v2f::operator -(const v2f& v) {
    v2f res(this->x - v.x, this->y - v.y);
    return res;
}
double 
v2f::operator *(const v2f& v) {
    return (this->x * v.x) + (this->y * v.y);
}
double 
v2f::operator ^(const v2f& v){
    return this->x * v.y - this->y * v.x;
}

v2f::v2f() {
        x = 0.;
        y = 0.;
    }
v2f::v2f(double x, double y) {
        this->x = x;
        this->y = y;
    }

double
v2f::len() {
        return pow(x*x + y*y, 0.5);
}

v2f
v2f::getnormalized() {
        v2f out(this->x, this->y);
        double len = out.len();
        out.x = out.x/len;
        out.y = out.y/len;
        return out;
    }

void
v2f::normalize() {
        double len = this->len();
        x = x/len;
        y = y/len;
}

v2f
v2f::getortogonal() {
        v2f out(-this->y, this->x);
        return out;
}

void
v2f::orthogonalize() {
        swap(this->x, this->y);
        this->y = -this->y;
}

double cos(v2f v1, v2f v2) {
	return (v1 * v2) / (v1.len()*v2.len());
}

double sin(v2f v1, v2f v2) {
	return (v1 ^ v2) / (v1.len()*v2.len());
}


edge::edge(){};
edge::edge(v2f a, v2f b) {
        this->a = a;
	this->b = b;
        len = pow(pow((a-b).x,2.)+pow((a-b).y, 2.), 0.5);
}
bool 
edge::operator ==(const edge& e) {
    if (this->a == e.a && this->b == e.b)
	    return true;
    if (this->a == e.b && this->b == e.a)
	    return true;
    return false;
}

void
edge::edit(v2f a, v2f b) {
    this->a = a;
    this->b = b;
    this->len = pow(pow((a-b).x,2.)+pow((a-b).y, 2.), 0.5);
}

triangle::triangle(){};
triangle::triangle(v2f A, v2f B, v2f C) {
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

        CircumCenter = v2f((A.x*sin(2.*alpha) + B.x * sin(2.*beta) + C.x * sin(2.*gamma))/(sin(2.*alpha)+sin(2.*beta)+sin(2.*gamma)),
            (A.y*sin(2.*alpha)+B.y*sin(2.*beta)+C.y*sin(2.*gamma))/(sin(2.*alpha)+sin(2.*beta)+sin(2.*gamma)));
        CircumRadius = b.len/(2.*sin(alpha));

        //float p = (a.len +b.len + c.len)/2.;
        //CircumRadius = a.len*b.len*c.len/(4.f*sqrtf((p-a.len)*(p-b.len)*(p-c.len)*p)); IsBad = false;

    }

bool
triangle::IsPointInCircumCircle(v2f P) {
    //cout<<"distance to center: " << (CircumCenter - P).len() << " & radius: " << CircumRadius << endl;
	if((CircumCenter - P).len() < CircumRadius)
		return true;
	else
		return false;
}
double
triangle::GetArea() {
    return b.len*sin(alpha)/2.;
}

bool triangle::operator== (const triangle& rt) {
	if (this->points[0] == rt.points[0] && this->points[1] == rt.points[1] && this->points[2] == rt.points[2])
		return true;
	else
		return false;
}
