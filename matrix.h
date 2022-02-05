#ifndef MATRIX
#define MATRIX

#include <vector>
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

    vector<double>& operator [] (int index);
    matrix operator + (matrix& M);
    matrix operator * (matrix& M);
    matrix operator * (double d);
    void print();
    void write(string name);
    void subMatrix(matrix temp, int p, int q, int n);
    double det();

    void transpose();
    //matrix transpose();
};

matrix transpose(matrix M);

#endif