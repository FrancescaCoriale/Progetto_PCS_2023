#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
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

int main(int argc, char *argv[])
{
    TriangularMesh Mesh;

    string Theta = argv[1];
    unsigned int theta = stoi(Theta);
    //unsigned int theta = 10;

    string directory = argv[2];




    //importazione, lettura, creazione degli oggetti e adiacenza

    ImportMesh ImportMesh(Mesh, directory);


    //sorting
    vector<Triangle> SortedA = MergeSort(Mesh.Triangles, 0, Mesh.Triangles.size()-1);
//        for (unsigned int i = 0; i<Mesh.NumberCell2D; i++)
//            cout<<"sortedA alla posizione " << i << "___" <<SortedA[i]<<endl;

    vector<Triangle> ThetaVector;

    if (theta >= SortedA.size()) {
        cout << "Errore: theta troppo grande. Inserire un valore di theta più piccolo di "<< SortedA.size() << endl;
    }
   else {
        for (unsigned int i = SortedA.size() - 1; i >= SortedA.size() - theta; i--)
        {
//            cout << "SORTEDA TAGLIATO ALLA POSIZIONE " << i << "___" << SortedA[i] << endl;
            ThetaVector.insert(ThetaVector.begin(), SortedA[i]);
            cout << "thetaVector" << ThetaVector[0].Id << endl;

        }

    }


//    //SortedA.resize(theta);
//    for (unsigned int i = SortedA.size()-1; i>SortedA.size()-theta; i--)
//        cout<<"SORTEDA TAGLIATO ALLA POSIZIONE " << i << "___" <<SortedA[i]<<endl;
    unsigned int maxIterator = ThetaVector.size();

    //raffinamento

    Raffinamento Raffinamento(Mesh, maxIterator, ThetaVector);



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
            outputFile<<newTriangle;

//            string Id = to_string(newTriangle.Id);
//            string p1 = to_string(newTriangle.pointsTriangle[0].Id);
//            string p2 = to_string(newTriangle.pointsTriangle[1].Id);
//            string p3 = to_string(newTriangle.pointsTriangle[2].Id);
//            string edge1 = to_string(newTriangle.segmentsTriangle[0].Id);
//            string edge2 = to_string(newTriangle.segmentsTriangle[1].Id);
//            string edge3 = to_string(newTriangle.segmentsTriangle[2].Id);
//            outputFile << newTriangle.Id << " " << p1 << " " << p2 << " " << p3 << " " << edge1 << " " << edge2 << " " << edge3 ;
        }
    };


    outputFile.close();

//    int id = 1;
//    array
//    Triangle T = Triangle()


  return 0;
}








