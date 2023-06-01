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
    vector<double> SortedA;
    SortedArea() = default;
    SortedArea(vector<double>& Aree, unsigned int& theta);
};

class Division{
    //divisione del triangolo
    //creazione dei triangoli
    Point *origin;
    Point *end;
    array<double,2> CoordinatesMidpoint;
    unsigned int IdMidpoint;
    Point Midpoint;
    Triangle T;
    TriangularMesh Mesh;
    unsigned int IdLatoSx;
    unsigned int IdLatoDx;
    Point Opposite;
    //elementi nuovi triangoli
    unsigned int NewIdT1;
    unsigned int NewIdT2;
    array<unsigned int, 3> verticesT1;
    array<unsigned int, 3> verticesT2;
    array<unsigned int, 3> edgesT1;
    array<unsigned int, 3> edgesT2;

public:
    Division() = default;
    Division(Triangle& T);

};

class Raffinamento {
//prendo triangolo adiacente (ex T2)
//controllo: il longestedge di T2 è uguale a longestedge di T1?
        //se sì: fai solo division su T2
        //altrimenti: fai division + segment tra midpoint del longestedge di T2 e del longestedge di T1

    SortedArea SA;
    Division D;
    Triangle T;
    TriangularMesh Mesh;

public:
    Raffinamento()=default;
    Raffinamento(TriangularMesh& Mesh, Division& D, SortedArea& SA);


};


}
#endif // __RAFFINAMENTO_H
