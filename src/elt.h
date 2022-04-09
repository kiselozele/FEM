#ifndef ELT
#define ELT
#include<iostream>
#include<vector>
#include "point.h"
using namespace std;

struct elt{
public:
    elt();
    elt(vector<point> &data);

    vector<point> data;
    vector<int> id_points;

    point& operator [] (int index);
    void add(point &p);
    int size();
    void print();

};

#endif