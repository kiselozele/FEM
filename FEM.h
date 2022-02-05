#ifndef FEMFILE
#define FEMFILE
#include <vector>
#include <string>
#include "point.h"
#include "elt.h"
#include "matrix.h"

using namespace std;

class FEM {
public:
    FEM();
    vector<point> points;//points[id] = {id.x, id.y}
    vector<int> boundary_point_id_0;
    vector<int> boundary_point_id_1;
    vector<point> quadrature_points;
    vector<double> quadrature_weights;

    //vector<vector<int>> elements;//elements[id] = {id_point_0, id_point_1, id_point_2}
    vector<elt> elts;

    //vector<point> unit_element; // Unit triangle: { { 0,0 },{ 1,0 },{ 0,1 } }
    elt unit_elt; // Unit triangle: { { 0,0 },{ 1,0 },{ 0,1 } }
    vector<double> time_nodes;

    matrix global_matrix_mass;
    matrix global_maxtrix_stiffness;

    matrix psi(point p);
    double jacobian(elt &e);

    matrix create_local_matrix_mass(elt &e);
    //matrix create_local_matrix_stiffness(int element_id);

    void read_points();
    void read_elements();
    void read_boundary(int array_id, string file_text);

    void create_time_nodes(double start_time, double end_time, int number_of_nodes);
    void create_global_matricies();
};


#endif