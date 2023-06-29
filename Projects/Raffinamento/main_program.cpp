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
        //cout << "id triangoli da ordinare" << v[i] << endl;
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
//        for (unsigned int i = 0; i < theta; i++)
        {
//            cout << "ThetaVector alla posizione -- " << i << " -- " << ThetaVector[i] << endl;
            //cout << "thetaVector " << ThetaVector[0] << endl;
//            ThetaVector.push_back(SortedA[i]);
//        for (unsigned int k = 0; k<ThetaVector.size(); k++)
//        { cout << "thetaVector " << ThetaVector[k] << endl; }
        }
    }

    unsigned int maxIterator = ThetaVector.size();

    //raffinamento

    Raffinamento Raffinamento(Mesh, maxIterator, ThetaVector);



    //esportazione


/// RISCRIVO IL FILE DI IMPUT CELL 1D
//        ofstream inputFile;
//        string inputFilePath = directory + "/Prova1D.csv";

//        inputFile.open(inputFilePath);
//        if (inputFile.fail())
//            cerr<< "Errore nell'apertura del file di output 1D" << endl;

//        inputFile << "IdLato;" << "x1;" << "y1;"<< "x2;"<< "y2" << endl; //1=origin e 2=end
//        for (unsigned int i = 0; i < Mesh.Segments.size(); i++)
//        {
//            inputFile << Mesh.Segments[i];

//        }
//        inputFile.close();


/// OUTPUT CELL 0D VERTICI
    ofstream outputFile0D;
    string outputFilePath0D = directory + "/outputCell0Ds.csv";

    outputFile0D.open(outputFilePath0D);
    if (outputFile0D.fail())
        cerr<< "Errore nell'apertura del file di output OD" << endl;

    outputFile0D << "IdVertice;" << "X;" << "Y"<< endl;

    for (unsigned int i = 0; i < Mesh.Points.size(); i++)
    {
        outputFile0D << Mesh.Points[i];
//        if (Mesh.OnOff[i] != true)
//            continue;
//        for (unsigned int k = 0; k<3; k++)
//        {
//            outputFile0D << Mesh.Triangles[i].pointsTriangle[k];
////            unsigned int outputId = Mesh.Triangles[i].pointsTriangle[k].Id;
////            unsigned int outputX = Mesh.Triangles[i].pointsTriangle[k].x;
////            unsigned int outputY = Mesh.Triangles[i].pointsTriangle[k].y;
////            outputFile0D << outputId << outputX << outputY << endl;
//        }
    }
    outputFile0D.close();


/// OUTPUT CELL 1D LATI
    ofstream outputFile1D;
    string outputFilePath1D = directory + "/outputCell1Ds.csv";

    outputFile1D.open(outputFilePath1D);
    if (outputFile1D.fail())
        cerr<< "Errore nell'apertura del file di output 1D" << endl;

    outputFile1D << "IdLato;" << "x1;" << "y1;"<< "x2;"<< "y2" << endl; //1=origin e 2=end
    for (unsigned int i = 0; i < Mesh.Segments.size(); i++)
    {
        outputFile1D << Mesh.Segments[i];
//        if (Mesh.OnOff[i] != true)
//            continue;
//        for (unsigned int k = 0; k<3; k++)
//        {
//            outputFile1D << Mesh.Triangles[i].segmentsTriangle[k];
////            unsigned int outputId = Mesh.Triangles[i].segmentsTriangle[k].Id;
////            Point& outputO = Mesh.Triangles[i].segmentsTriangle[k].origin;
////            Point& outputE = Mesh.Triangles[i].segmentsTriangle[k].end;
////            outputFile1D << outputId << outputO.x << outputO.y <<outputE.x << outputE.y << endl;
//        }
    }
    outputFile1D.close();



/// OUTPUT CELL 2D TRIANGOLI
    ofstream outputFile2D;
    string outputFilePath2D = directory + "/outputCell2Ds.csv";

    outputFile2D.open(outputFilePath2D);
    if (outputFile2D.fail())
        cerr<< "Errore nell'apertura del file di output 2D" << endl;

    outputFile2D << "IdTriangle;" << "Vertices;" << ";"<< ";" << "Edges"<< endl;
    for (unsigned int i = 0; i < Mesh.Triangles.size(); i++)
    {
        if (Mesh.OnOff[i] != true)
            continue;
        outputFile2D<<Mesh.Triangles[i];
    };

    outputFile2D.close();


///// OUTPUT NEL CASO DI TEST 1
//    ofstream outputFile1D;
//    string outputFilePath1D = directory + "/output1Dtest1.csv";

//    outputFile1D.open(outputFilePath1D);
//    if (outputFile1D.fail())
//        cerr<< "Errore nell'apertura del file di output 1D" << endl;

//    outputFile1D << "IdLato;" << "x1;" << "y1;"<< "x2;"<< "y2" << endl; //1=origin e 2=end
//    for (unsigned int i = 0; i < Mesh.Triangles.size(); i++)
//    {
//        if (Mesh.OnOff[i] != true)
//            continue;
//        for (unsigned int k = 0; k<3; k++)
//        {
//            outputFile1D << Mesh.Triangles[i].segmentsTriangle[k];
////            unsigned int outputId = Mesh.Triangles[i].segmentsTriangle[k].Id;
////            Point& outputO = Mesh.Triangles[i].segmentsTriangle[k].origin;
////            Point& outputE = Mesh.Triangles[i].segmentsTriangle[k].end;
////            outputFile1D << outputId << outputO.x << outputO.y <<outputE.x << outputE.y << endl;
//        }
//    }
//    outputFile1D.close();


  return 0;
}

