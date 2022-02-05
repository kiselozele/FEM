
#include "point.h"

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;
/*
point::point() {
	x = 0.0;
	y = 0.0;
}

point::point(double x, double y) {
	this->x = x;
	this->y = y;
}

point::point(int id, double x, double y, vector<int>& triangle_index, 
	vector<int>& triangle_seq, vector<int>& edges) {
	this->id = id;
	this->x = x;
	this->y = y;
	this->triangle_index = triangle_index;
	this->triangle_seq = triangle_seq;
	this->edges = edges;
}

point point::operator + (point const &p){
	point res;
	res.x = this->x + p.x;
	res.y = this->y + p.y;
	return res;
}

point point::operator - (point const &p){
	point res;
	res.x = this->x - p.x;
	res.y = this->y - p.y;
	return res;
}

double point::operator ^ (point const &p){
	return this->x*p.y - this->y*p.x;
}

double point::operator * (point const &p){
	return this->x*p.x + this->y*p.y;
}

double point::len(){
	return pow(pow(this->x,2) + pow(this->y,2), 0.5);
}

void point::remove_triangle(int position) {
	triangle_index.erase(triangle_index.begin() + position);
	triangle_seq.erase(triangle_seq.begin() + position);
}

void point::push_triangle(int index, int seq) {
	triangle_index.push_back(index);
	triangle_seq.push_back(seq);
}

void point::add_edge(int id) {
	edges.push_back(id);
}

void point::remove_edge(int id) {
	for (int i=0;i<edges.size();i++) {
		if (edges[i] == id) {
			edges.erase(edges.begin() + i);
			return;
		}
	}
}

double cos(point v1, point v2) {
	return (v1 * v2) / (v1.len()*v2.len());
}

double sin(point v1, point v2) {
	return (v1 ^ v2) / (v1.len()*v2.len());
}
*/