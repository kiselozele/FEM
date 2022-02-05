#include "FEM.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;



FEM::FEM() {

    this->unit_elt.data = { { 0,0 },{ 1,0 },{ 0,1 } };

    this->quadrature_weights = { 1. / 6., 1. / 6., 1. / 6. };
    this->quadrature_points = { {0,1. / 2.}, {1. / 2., 0}, {1. / 2., 1. / 2.} };
    read_points();
    read_elements();

    this->global_matrix_mass = matrix(points.size(), points.size());
}

void FEM::read_points() {
    fstream file;
    file.open("text/nodes.txt");
    vector<vector<double>> numbers;
    string line = "";
    while (getline(file, line)) {
        numbers.push_back(vector<double>{});
        string number = "";
        for (int i = 0; i < line.size(); i++) {
            if (line[i] == ',') {
                numbers[numbers.size() - 1].push_back(stod(number));
                number = "";
            }
            else {
                number += line[i];
            }
        }
        numbers[numbers.size() - 1].push_back(stod(number));
    }
    for (int i = 0; i < numbers.size(); i++) {
        points.push_back(point{ numbers[i][0], numbers[i][1] });
    }
}
void FEM::read_elements() {
    fstream file;
    file.open("text/elements.txt");
    vector<vector<int>> numbers;
    string line = "";
    while (getline(file, line)) {
        numbers.push_back(vector<int>{});
        string number = "";
        for (int i = 0; i < line.size(); i++) {
            if (line[i] == ',') {
                numbers[numbers.size() - 1].push_back(stoi(number));
                number = "";
            }
            else {
                number += line[i];
            }
        }
        numbers[numbers.size() - 1].push_back(stoi(number));
    }
    for (int i = 0; i < numbers.size(); i++) {
        //elements.push_back(vector<int>{ numbers[i][0] - 1, numbers[i][1] - 1, numbers[i][2] - 1});
        vector<point> v = { points[numbers[i][0] - 1],
            points[numbers[i][1] - 1], points[numbers[i][2] - 1] };
        elts.push_back(elt(v));
        vector<int> v_p = { numbers[i][0] - 1,
            numbers[i][1] - 1, numbers[i][2] - 1 };
        elts[i].id_points = v_p;
        //cout << numbers[i][0] - 1 << " " << numbers[i][1] - 1 << " " << numbers[i][2] - 1 << "\n";
    }
}

void FEM::read_boundary(int array_id, string text_file) {
    fstream file;
    file.open(text_file);
    vector<vector<double>> numbers;
    string line = "";
    while (getline(file, line)) {
        numbers.push_back(vector<double>{});
        string number = "";
        for (int i = 0; i < line.size(); i++) {
            if (line[i] == ',') {
                numbers[numbers.size() - 1].push_back(stoi(number));
                number = "";
            }
            else {
                number += line[i];
            }
        }
        numbers[numbers.size() - 1].push_back(stoi(number));
    }
    if (array_id == 0) {
        for (int i = 0; i < numbers.size(); i++) {
            boundary_point_id_0.push_back(numbers[i][0]);
        }
    }
    if (array_id == 1) {
        for (int i = 0; i < numbers.size(); i++) {
            boundary_point_id_1.push_back(numbers[i][0]);
        }
    }
}


void FEM::create_time_nodes(double start_time, double end_time, int number_of_nodes) {
    //work on vector<double> time_nodes
    double h = (end_time - start_time) / double(number_of_nodes - 1);
    for (int i = 0; i < number_of_nodes; i++) {
        time_nodes.push_back(start_time + i * h);
    }
}

matrix FEM::psi(point p) {
    matrix res(1, unit_elt.size());
    double X = p.x;
    double Y = p.y;

    res[0][0] = 1 - X - Y;
    res[0][1] = X;
    res[0][2] = Y;
    return res;
}

double FEM::jacobian(elt &e) {
    //returns matrix 2x2 for 2d
    double x_k = e[0].x;
    double y_k = e[0].y;
    
    double x_l = e[1].x;
    double y_l = e[1].y;

    double x_m = e[2].x;
    double y_m = e[2].y;

    matrix res(2, 2);
    res[0][0] = x_l - x_k; res[0][1] = y_l - y_k;
    res[1][0] = x_m - x_k; res[1][1] = y_m - y_k;
    return abs(res.det());
}


matrix FEM::create_local_matrix_mass(elt &e) {
    matrix local_matrix(e.size(), e.size());
    for (int i = 0; i < quadrature_weights.size(); i++) {
        matrix A = (psi(quadrature_points[i]));
        //cout << "A:" << "\n";
        //A.print();
        //cout << "B:" << "\n";
        //B.print();

        local_matrix = (transpose(A) * A)* (quadrature_weights[i] * jacobian(e)) + local_matrix;
    }
    return local_matrix;
}

void FEM::create_global_matricies() {
    for (int i = 0; i < elts.size(); i++) {
        matrix A = create_local_matrix_mass(elts[i]);
        for (int j = 0; j < A.n; j++){
            for (int k = 0; k < A.m; k++){
                global_matrix_mass[elts[i].id_points[j]][elts[i].id_points[k]] += A[j][k];
            }
        }
    }
    //global_matrix_mass[elements[i][j]][elements[i][k]] += A[j][k];
}

