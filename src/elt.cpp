#include "elt.h"

elt::elt(){}

elt::elt(vector<point> &data) {
    this->data = data;
}

point& elt::operator [] (int index) {
    return data[index];
}

void elt::add(point& p) {
    data.push_back(p);
}

int elt::size() {
    return data.size();
}
void elt::print() {
    for (int i = 0;i < data.size();i++){
        cout << "Point #"<<i<<": ";
        cout << "{" << data[i].x << "," << data[i].y << "}" << "\n";
    }
}
