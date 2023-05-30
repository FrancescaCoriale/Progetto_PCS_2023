#ifndef __RAFFINAMENTO_H
#define __RAFFINAMENTO_H

#include <iostream>
#include "Eigen/Eigen"
#include <fstream>
#include <vector>
#include "Point.hpp"
#include "Segment.hpp"
#include "Triangle.hpp"
#include "Sorting.hpp"

using namespace Eigen;
using namespace std;
using namespace SortLibrary;


namespace RaffinamentoLibrary{

class TriangularMesh {
public:
    unsigned int NumberCell0D = 0; ///< number of Cell0D
    vector<Point> Points;

    unsigned int NumberCell1D = 0; ///< number of Cell1D
    VectorXd LengthEdges = {};
    vector<Segment> Segments;

    unsigned int NumberCell2D = 0; ///< number of Cell2D
    vector<vector<unsigned int>> LongestEdges = {};
    vector<Triangle> Triangles;
    vector<bool> OnOff;

    list<list<unsigned int>> AdjacencyLists = {};
    //adiacenza: lista di liste: id triangolo è la posizione nel vettore esterno, id triangoli adiacenti sono i valori e id del lato confinante nel vettore interno
    //void Adjacency(list<list<unsigned int>>& AdjacencyList, const vector<vector<unsigned int>>& Edges2D);
    void Adjacency(list<unsigned int>& AdjacencyList, const vector<array<unsigned int, 3>> Edges);
};


class ImportMesh {
public:
    TriangularMesh Mesh;
    void Cell0D(TriangularMesh& Mesh);

    void Cell1D(TriangularMesh& Mesh);

    void Cell2D(TriangularMesh& Mesh);
};





class SortedArea {

    vector<double> Aree = {};
    unsigned int theta = 10;
    public:
    SortedArea(vector<double>& Aree, unsigned int& theta);
};

class Division{
    //divisione del triangolo
    //creazione dei triangoli
    Triangle T;
    TriangularMesh Mesh;
    //elementi nuovi triangoli
    unsigned int NewId1;
    unsigned int NewId2;
    array<unsigned int, 3> vertices1;
    array<unsigned int, 3> vertices2;
    array<unsigned int, 3> edges1;
    array<unsigned int, 3> edges2;

public:
    Division(Triangle& T);
    Triangle T2 = Triangle(NewId1, vertices1, edges1);
    Triangle T1 = Triangle(NewId2, vertices2, edges2);

};

class Raffinamento {
//prendo triangolo adiacente (ex T2)
//controllo: il longestedge di T2 è uguale a longestedge di T1?
        //se sì: fai solo division su T2
        //altrimenti: fai division + segment tra midpoint del longestedge di T2 e del longestedge di T1
};


}
#endif // __RAFFINAMENTO_H
