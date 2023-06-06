#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Eigen/Eigen"
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

    //importazione, lettura e creazione degli oggetti
    ImportMesh imp;
    imp.Cell0D(Mesh);
    imp.Cell1D(Mesh);
    imp.Cell2D(Mesh);


    //sorting
    vector<Triangle> SortedA = MergeSort(Mesh.Triangles, 0, Mesh.Triangles.size()-1);
    SortedA.resize(theta);
    unsigned int maxIterator = SortedA.size();


    //raffinamento
    Raffinamento Raffinamento(maxIterator, SortedA);


    //esportazione
    ofstream outputFile;
    outputFile.open("outputFiles.csv");
    if (outputFile.fail())
        cerr<< "Errore nell'apertura del file di output" << endl;


    for (unsigned int i = 0; i < Mesh.Triangles.size(); i++)
    {
        if (Mesh.OnOff[i] == true)
        {
            Triangle newTriangle = Mesh.Triangles[i];
            string Id = to_string(newTriangle.Id);
            string p1 = to_string(newTriangle.pointsTriangle[0].Id);
            string p2 = to_string(newTriangle.pointsTriangle[1].Id);
            string p3 = to_string(newTriangle.pointsTriangle[2].Id);
            string edge1 = to_string(newTriangle.segmentsTriangle[0].Id);
            string edge2 = to_string(newTriangle.segmentsTriangle[1].Id);
            string edge3 = to_string(newTriangle.segmentsTriangle[2].Id);
            outputFile << newTriangle.Id << " " << p1 << " " << p2 << " " << p3 << " " << edge1 << " " << edge2 << " " << edge3 ;
        }
    };


    outputFile.close();
  return 0;
}








