#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include"Eigen/Eigen"
#include "Raffinamento.hpp"
#include "Point.hpp"
#include "Segment.hpp"
#include "Triangle.hpp"
#include "Sorting.hpp"

using namespace std;
using namespace Eigen;
using namespace RaffinamentoLibrary;
using namespace SortingLibrary;

int main(/*int argc, char *argv[]*/)
{
    TriangularMesh Mesh;

    //string Theta = argv[1];
    //unsigned int theta = stoi(Theta);
    unsigned int theta = 10;
    vector<Triangle> SortedA = MergeSort(Mesh.Triangles, 0, Mesh.Triangles.size()-1);
    SortedA.resize(theta);
    unsigned int maxIterator = SortedA.size();


    for (unsigned int i=0; i<maxIterator; i++)
    {
        Triangle t = SortedA[i];
        Division(&t);
        Mesh.OnOff[t.Id] = "false";
        Mesh.OnOff.push_back(true);
        Mesh.OnOff.push_back(true);

    }
    cout << OnOff << endl;

  return 0;
}
