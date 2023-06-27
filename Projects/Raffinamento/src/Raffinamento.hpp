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

    Point CreateMidPoint(unsigned int &idSegment);

    array<unsigned int, 3> GetUtilities(Triangle &T, unsigned int &idSegment);

    array<Triangle,2> Division(unsigned int &NumberCell0D, unsigned int &NumberCell1D, unsigned int &NumberCell2D,
                               Triangle& T, unsigned int &idSegment, Point &Midpoint);

    array<Triangle,2> DivisionAdjacent(Triangle& adjT, unsigned int &idlongestEdge, Point &Midpoint,
                                       Segment &NewSO, Segment &NewSE);

//    inline bool operator > (const unsigned int & object1, const unsigned int & object2)
//    {return Triangles[object1].Area > Triangles[object2].Area;}



//    inline bool operator <= (const unsigned int & object1, const unsigned int & object2)
//    {return Triangles[object1].Area <= Triangles[object2].Area;}

};


class ImportMesh {
public:
    ImportMesh(TriangularMesh& Mesh, string & path);
};


//class Division{
//public:
    //Point Midpoint;
    //Segment NewS;
    //Segment NewSO;
    //Segment NewSE;
    //Triangle newT1;
    //Triangle newT2;

    //Division(unsigned int &NumberCell0D, unsigned int &NumberCell1D, unsigned int &NumberCell2D,
             //Triangle& T, Segment & segment);


//};


//metodo di divisione che a partire da un triangolo grande restituisce due triangoli piccoli
//non soddisfo ancora la condizione

class Raffinamento {
//prendo triangolo adiacente (ex T2)
//controllo: il longestedge di T2 è uguale a longestedge di T1?
        //se sì: fai solo division su T2
        //altrimenti: fai division + segment tra midpoint del longestedge di T2 e del longestedge di T1
public:
    Raffinamento(TriangularMesh &Mesh, const unsigned int &maxIterator, vector<unsigned int> &ThetaVector);


};



}
#endif // __RAFFINAMENTO_H
