#include <iostream>
#include <vector>
#include <cmath>

#include "point.h"
#include "elt.h"
#include "matrix.h"
#include "FEM.h"

//#include "delone.h"
using namespace std;


//TODO:
//DONE   matrix.write_to_txt_file()
//       assemble global_matrix_stiffness & local_matrix_stiffness
//       tinyexpr++ into code
//DONE   struct definition of an element
//       gnuplot_functions in header?
//       fix matrix.transpose() to "return" a matrix

int main() {
    FEM F;
    F.create_global_matricies();
    F.global_matrix_mass.write("matrix");
    system("pause");
}
