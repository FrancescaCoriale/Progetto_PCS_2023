#ifndef __RAFFINAMENTO_H
#define __RAFFINAMENTO_H

#include <iostream>
#include "Eigen/Eigen"
#include <fstream>
#include "MeshUtilities.hpp"

using namespace Eigen;
using namespace std;
using namespace MeshUtilitiesLibrary;

namespace AlgorithmLibrary{

class TriangularMesh
{
public:
    unsigned int NumberCell0D = 0; ///< number of Cell0D
    std::vector<Point> Points;

    unsigned int NumberCell1D = 0; ///< number of Cell1D
    Eigen::VectorXd LengthEdges = {};
    std::vector<Segment> Segments;

    unsigned int NumberCell2D = 0; ///< number of Cell2D
    std::vector<double> Aree = {};
    std::vector<vector<unsigned int>> LongestEdges = {};
    std::vector<Triangle> Triangles;

    list<list<unsigned int>> AdjacencyLists = {};
    //adiacenza: lista di liste: id triangolo è la posizione nel vettore esterno, id triangoli adiacenti sono i valori e id del lato confinante nel vettore interno
    //void Adjacency(list<list<unsigned int>>& AdjacencyList, const vector<vector<unsigned int>>& Edges2D);
    void Adjacency(list<unsigned int>& AdjacencyList, const vector<array<unsigned int, 3>> Edges);
};


class ImportMesh
{
public:
    TriangularMesh Mesh;
    void Cell0D(TriangularMesh& Mesh);

    void Cell1D(TriangularMesh& Mesh);

    void Cell2D(TriangularMesh& Mesh);
};








class Division{
    public: 
    vector<bool> Triangles; //nel main creiamo vettore lungo NumberCell2D di tutti "true"

    unsigned int Midpoint = TriangularMesh::Vertices.size() +1; //uguale alla lunghezza di Vertices+1
    //creo id nuovi vertici originEnd del lato da creare per dividere il triangolo:
    //1. trovo il vertice che non è in originEnd del longestEdge
    //2. creo array di originEnd con il vertice del punto 1 e Midpoint
    //3. salvo vertice del punto 1 in un variabile Opposite (così divido meglio i triangoli)
    void CreateOriginEnd(const array<unsigned int,2>& originEnd, const array<unsigned int, 3>& vertices,
                         const unsigned int& Midpoint,
                         array<unsigned int,2>& NewOriginEnd, unsigned int Opposite);
    //dopo metodo CreateOriginEnd faccio un push.back in OriginEnds del nuovo array creato

    unsigned int DivisionEdge = TriangularMesh::Edges.size() +1; //uguale alla lunghezza di Edges+1
    //devo fare un push.back in Edges del nuovo id creato

    //per creare triangoli:
    //trovo i due vertici diversi da Opposite -> vertici A e B
    //come faccio? If esterno: IF Opposite è origin -> prendo end + posizione nel vettore come id del lato
                            //ELSE prendo origin + posizione nel vettore come id del lato
    //prendo end:
        //1. creo array di vertices del triangolo A
        //2. creo array di edges del triangolo A
    //prendo origin:
        //1. creo array di vertices del triangolo B
        //2. creo array di edges del triangolo B
    void CreateTriangle(const unsigned int& point, const array<unsigned int, 3>& edge,
                        const unsigned int& Opposite, const unsigned int& Midpoint,
                        array<unsigned int, 3> vertices, array<unsigned int, 3> edges);
    //push.back in Vertices ed Edges dei due array creati

    //aggiorno lista triangoli da considerare:
    //aggiungo nuovo triangolo creato in CreateTriangle con "true"
    //modifico triangolo iniziale come "false" ???? QUESTO MANCA ????
    unsigned int Triangle = Triangles.size() +1;
    void ChangeTriangles(vector<bool>& Triagles, const unsigned int& Triangle);

};

class Raffinamento{

    public:

    Division division;
    Raffinamento(vector<SortArea::Pair>& SortedA, list<list<unsigned int>>& AdjacencyList);


};


}
#endif // __RAFFINAMENTO_H
