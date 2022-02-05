#ifndef FEMFILE
#define FEMFILE
#include <vector>
#include <string>
#include "point.h"
#include "matrix.h"
using namespace std;


struct matrix {
public:
    // .--m---> n x m matrix
    // | . . .
    // n . . .
    // | . . .
    // v
    matrix();
    matrix(int n, int m);// with zeroes
    matrix(vector<vector<double>> data);
    void add_data(vector<vector<double>> data);

    vector<vector<double>> data;
    int n;
    int m;

    vector<double> & operator [] (int index);
    matrix operator + (matrix& M);
    matrix operator * (matrix& M);
    matrix operator * (double d);
    void print();
    void subMatrix(matrix temp, int p, int q, int n);
    double det();

    void transpose();
    //matrix transpose();
};

class FEM {
public:
    FEM();
    vector<point> points;//points[id] = {id.x, id.y}
    vector<int> boundary_point_id_0;
    vector<int> boundary_point_id_1;
    vector<point> quadrature_points;
    vector<double> quadrature_weights;

    vector<vector<int>> elements;//elements[id] = {id_point_0, id_point_1, id_point_2}
    vector<point> unit_element; // Unit triangle: { { 0,0 },{ 1,0 },{ 0,1 } }
    vector<double> time_nodes;

    matrix global_matrix_mass;
    matrix global_maxtrix_stiffness;

    matrix psi(point p);
    double jacobian(int element_id);

    matrix create_local_matrix_mass(int element_id);
    //matrix create_local_matrix_stiffness(int element_id);

    void read_points();
    void read_elements();
    void read_boundary(int array_id, string file_text);

    void print_element(int id_element);
    void create_time_nodes(double start_time, double end_time, int number_of_nodes);
    void create_global_matricies();
};


#endif