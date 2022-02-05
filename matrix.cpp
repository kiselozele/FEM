#include <iostream>
#include <vector>
#include <fstream>
#include "matrix.h"

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

void matrix::write(string name) {
    ofstream file;
    string dir = "text/" + name + ".txt";
    file.open(dir);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            file << data[i][j] << ",";
        }
        file << "\n";
    }
    file.close();
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

matrix transpose(matrix M) {
    M.transpose();
    return M;
}
