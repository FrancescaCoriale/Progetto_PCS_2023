#ifndef __SORTING_H
#define __SORTING_H
#include <iostream>
#include "Eigen/Eigen"
#include <fstream>
#include <vector>
#include "Raffinamento.hpp"
#include "Triangle.hpp"

using namespace std;
using namespace Eigen;
using namespace RaffinamentoLibrary;

namespace SortLibrary{

class MergeSort{ //non fare classe,prendere il file di sorting e cambiare il tipo in triangle

    Triangle T;
    RaffinamentoLibrary::TriangularMesh Mesh;
    vector<Triangle> v = Mesh.Triangles;

public:
    void Merge(vector<Triangle>& v, const unsigned int& sx,
               const unsigned int& cx, const unsigned int& dx);

    MergeSort(vector<Triangle>& v, const unsigned int& sx, const unsigned int& dx);

};

}
#endif

