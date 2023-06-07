#ifndef __RAFFINAMENTO_H
#define __RAFFINAMENTO_H

#include <iostream>
#include "Eigen/Eigen"
#include <fstream>
#include <vector>

#include "Segment.hpp"
#include "Triangle.hpp"
#include "Point.hpp"
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
    vector<bool> OnOff ;

    list<list<unsigned int>> AdjacencyLists = {};
    //adiacenza: lista di liste: id triangolo è la posizione nel vettore esterno, id triangoli adiacenti sono i valori e id del lato confinante nel vettore interno
    //void Adjacency(list<list<unsigned int>>& AdjacencyList, const vector<vector<unsigned int>>& Edges2D);
    void Adjacency(list<unsigned int>& AdjacencyList, const vector<array<unsigned int, 3>> Edges);
};


class ImportMesh {
public:
    TriangularMesh Mesh;
    void Cell0D(TriangularMesh& Mesh, string & path);

    void Cell1D(TriangularMesh& Mesh, string & path);

    void Cell2D(TriangularMesh& Mesh, string & path);
};



array<Triangle,2> Division(Triangle& T, Segment & segment);

//metodo di divisione che a partire da un triangolo grande restituisce due triangoli piccoli
//non soddisfo ancora la condizione

class Raffinamento {
//prendo triangolo adiacente (ex T2)
//controllo: il longestedge di T2 è uguale a longestedge di T1?
        //se sì: fai solo division su T2
        //altrimenti: fai division + segment tra midpoint del longestedge di T2 e del longestedge di T1

    Triangle T;
    TriangularMesh Mesh;

public:
    Raffinamento(const unsigned int maxIterator, vector<Triangle> SortedA);


};



}
#endif // __RAFFINAMENTO_H
