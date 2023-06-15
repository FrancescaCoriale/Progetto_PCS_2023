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
    if (argc == 1)
        cerr << "Errore: non ci sono argomenti nella linea di comando" << endl;
    TriangularMesh Mesh;

    string Theta = argv[1];
    unsigned int theta = stoi(Theta);
    cout << "raffineremo solo i primi " << theta << " triangoli" << endl;

    string directory = argv[2];

    //importazione, lettura, creazione degli oggetti e adiacenza

    ImportMesh ImportMesh(Mesh, directory);

    //sorting
    vector<unsigned int> v;
    for (unsigned int i = 0; i < Mesh.NumberCell2D; i++)
    {
        v.push_back(Mesh.Triangles[i].Id);
        cout << "id triangoli da ordinare" << v[i] << endl;
    }

    vector<unsigned int> SortedA = MergeSort(Mesh, v, 0, v.size()-1);

    vector<unsigned int> ThetaVector;
    ThetaVector.reserve(theta);

    if (theta >= SortedA.size()) {
        cout << "Errore: theta troppo grande. Inserire un valore di theta più piccolo di "<< SortedA.size() << endl;
    }
   else {


        for (unsigned int i = SortedA.size() - 1; i >= SortedA.size() - theta; i--)
        {
//            cout << "SORTEDA TAGLIATO ALLA POSIZIONE " << i << "___" << SortedA[i] << endl;
            ThetaVector.insert(ThetaVector.end(),SortedA[i]);
        }
        for (unsigned int i = 0; i < theta; i++)
        {
            cout << "ThetaVector alla posizione -- " << i << " -- " << ThetaVector[i] << endl;
        }

    }
    unsigned int maxIterator = ThetaVector.size();

    //raffinamento

    Raffinamento Raffinamento(Mesh, maxIterator, ThetaVector);



    //esportazione
    ofstream outputFile;
    string outputFilePath = directory + "/outputCell2Ds.csv";

    outputFile.open(outputFilePath);
    if (outputFile.fail())
        cerr<< "Errore nell'apertura del file di output" << endl;



    outputFile << "IdTriangle" << ";" << "Vertices" << ";" << ";" << ";" << "Edges"<< endl;
    for (unsigned int i = 0; i < Mesh.Triangles.size(); i++)
    {
        if (Mesh.OnOff[i] != true)
            continue;

        Triangle& newTriangle = Mesh.Triangles[i];
        outputFile<<newTriangle;

        //            string Id = to_string(newTriangle.Id);
        //            string p1 = to_string(newTriangle.pointsTriangle[0].Id);
        //            string p2 = to_string(newTriangle.pointsTriangle[1].Id);
        //            string p3 = to_string(newTriangle.pointsTriangle[2].Id);
        //            string edge1 = to_string(newTriangle.segmentsTriangle[0].Id);
        //            string edge2 = to_string(newTriangle.segmentsTriangle[1].Id);
        //            string edge3 = to_string(newTriangle.segmentsTriangle[2].Id);
        //            outputFile << newTriangle.Id << " " << p1 << " " << p2 << " " << p3 << " " << edge1 << " " << edge2 << " " << edge3 ;

    };

    outputFile.close();

  return 0;
}




