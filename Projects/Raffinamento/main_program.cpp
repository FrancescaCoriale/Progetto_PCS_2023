#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include"Eigen/Eigen"
#include "Raffinamento.hpp"
#include "Sorting.hpp"

using namespace std;
using namespace Eigen;
using namespace RaffinamentoLibrary;
using namespace SortingLibrary;

int main(int argc, char *argv[])
{
    TriangularMesh Mesh;
    Triangle T;

    string Theta = argv[1];
    unsigned int theta = stoi(Theta);
    vector<Triangle> SortedA = MergeSort(Mesh.Triangles, 0, Mesh.Triangles.size()-1);
    SortedA.resize(theta);








  return 0;
}
