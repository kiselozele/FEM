#include "FEM.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;



FEM::FEM() {
    this->unit_element = { { 0,0 },{ 1,0 },{ 0,1 } };
    this->quadrature_weights = { 1. / 6., 1. / 6., 1. / 6. };
    this->quadrature_points = { {0,1. / 2.}, {1. / 2., 0}, {1. / 2., 1. / 2.} };
    read_points();
    read_elements();

    this->global_matrix_mass = matrix(points.size(), points.size());
}

void FEM::read_points() {
    fstream file;
    file.open("nodes.txt");
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
    file.open("elements.txt");
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
        elements.push_back(vector<int>{ numbers[i][0] - 1, numbers[i][1] - 1, numbers[i][2] - 1});
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
void FEM::print_element(int id_element) {
    cout << "1st: # ";
    cout << elements[id_element][0] << " ";
    cout << "{"<< points[elements[id_element][0]].x << ", " << points[elements[id_element][0]].y << "}\n";
    cout << "2nd: # ";
    cout << elements[id_element][1] << " ";
    cout << "{" << points[elements[id_element][1]].x << ", " << points[elements[id_element][1]].y << "}\n";
    cout << "3rd: # ";
    cout << elements[id_element][2] << " ";
    cout << "{" << points[elements[id_element][2]].x << ", " << points[elements[id_element][2]].y << "}\n";
}

void FEM::create_time_nodes(double start_time, double end_time, int number_of_nodes) {
    //work on vector<double> time_nodes
    double h = (end_time - start_time) / double(number_of_nodes - 1);
    for (int i = 0; i < number_of_nodes; i++) {
        time_nodes.push_back(start_time + i * h);
    }
}
matrix::matrix() {
}
matrix::matrix(int n, int m) {
    for (int i = 0; i < n; i++) {
        data.push_back(vector<double>{});
        for (int j = 0; j < m; j++) {
            data[i].push_back(0.0);
        }
    }
    this->n = n;
    this->m = m;
}
matrix::matrix(vector<vector<double>> data) {
    this->data = data;
    n = data.size();
    m = data[0].size();
}
void matrix::add_data(vector<vector<double>> data) {
    this->data = data;
    n = data.size();
    m = data[0].size();
}
vector<double>& matrix::operator [] (int index) {
    return data[index];
}

matrix matrix::operator * (matrix& M) {
    if (this->m != M.n)
        throw "Not compatible matricies for operator *";
    matrix NEW(this->n, M.m);//sizes = this->n x M.m
    for (int i = 0; i < this->n; i++)
        for (int j = 0; j < M.m; j++)
            for (int k = 0; k < this->m; k++)
                NEW[i][j] += this->data[i][k] * M[k][j];
    return NEW;
}

matrix matrix::operator + (matrix& M) {
    if (this->m != M.m || this->n != M.n)
        throw "Not compatible matricies for operator +";
    matrix NEW(this->n, M.m);//sizes = this->n x M.m
    for (int i = 0; i < this->n; i++)
        for (int j = 0; j < M.m; j++)
            NEW[i][j] += this->data[i][j] + M[i][j];
    return NEW;
}

matrix matrix::operator *(double d) {
    matrix NEW(this->n, this->m);//sizes = this->n x M.m
    for (int i = 0; i < this->n; i++)
        for (int j = 0; j < this->m; j++)
            NEW[i][j] += this->data[i][j] * d;
    return NEW;
}

void matrix::print() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << data[i][j] << "\t";
        }
        cout << "\n";
    }
    cout << "\n";
}

void matrix::subMatrix(matrix temp, int p, int q, int n) {
    int i = 0, j = 0;
    // filling the sub matrix
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            // skipping if the current row or column is not equal to the current
            // element row and column
            if (row != p && col != q) {
                temp[i][j++] = data[row][col];
                if (j == n - 1) {
                    j = 0;
                    i++;
                }
            }
        }
    }
}

double matrix::det() {
    if (this->n != this->m)
        throw "Determinant of an nonsquare matrix";
    int determinant = 0;
    if (n == 1) {
        return data[0][0];
    }
    if (n == 2) {
        return (data[0][0] * data[1][1]) - (data[0][1] * data[1][0]);
    }
    matrix temp(n - 1, n - 1);
    int sign = 1;

    for (int i = 0; i < n; i++) {
        subMatrix(temp, 0, i, n - 1);
        determinant += sign * data[0][i] * temp.det();
        sign = -sign;
    }
    return determinant;
}

void matrix::transpose() {
    vector<vector<double>> data_copy = data;
    data.clear();
    for (int i = 0; i < m; i++) {
        data.push_back(vector<double>{});
        for (int j = 0; j < n; j++) {
            data[i].push_back(data_copy[j][i]);
        }
    }
    swap(this->m, this->n);
}

matrix Trans(matrix &M) {
    matrix NEW(M.data);
    NEW.transpose();
    return NEW;
}

matrix FEM::psi(point p) {
    matrix res(1, elements[0].size());
    double X = p.x;
    double Y = p.y;

    res[0][0] = 1 - X - Y;
    res[0][1] = X;
    res[0][2] = Y;
    return res;
}

double FEM::jacobian(int element_id) {
    //returns matrix 2x2 for 2d
    double x_k = points[elements[element_id][0]].x;
    double y_k = points[elements[element_id][0]].y;

    double x_l = points[elements[element_id][1]].x;
    double y_l = points[elements[element_id][1]].y;
    
    double x_m = points[elements[element_id][2]].x;
    double y_m = points[elements[element_id][2]].y;
    
    matrix res(2, 2);
    res[0][0] = x_l - x_k; res[0][1] = y_l - y_k;
    res[1][0] = x_m - x_k; res[1][1] = y_m - y_k;
    return abs(res.det());
}


matrix FEM::create_local_matrix_mass(int element_id) {
    matrix local_matrix(elements[0].size(), elements[0].size());
    for (int i = 0; i < quadrature_weights.size(); i++) {
        matrix A = (psi(quadrature_points[i]));
        matrix B = A;
        A.transpose();
        matrix C = A * B;
        //cout << "A:" << "\n";
        //A.print();
        //cout << "B:" << "\n";
        //B.print();
        C = C * (quadrature_weights[i] * jacobian(element_id));

        local_matrix = C + local_matrix;
    }
    return local_matrix;
}
void FEM::create_global_matricies() {
    for (int i = 0; i < elements.size(); i++) {
        matrix A = create_local_matrix_mass(i);
        for (int j = 0; j < A.n; j++)
            for (int k = 0; k < A.m; k++)
                global_matrix_mass[elements[i][j]][elements[i][k]] += A[j][k];
    }
}

