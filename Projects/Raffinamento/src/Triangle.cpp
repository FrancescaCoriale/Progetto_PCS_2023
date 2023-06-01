#include <Eigen/StdVector>
#include <iostream>
#include <fstream>
#include "Eigen/Eigen"
#include <algorithm>

#include "Point.hpp"
#include "Segment.hpp"
#include "Triangle.hpp"
//#include "map"


using namespace std;
using namespace Eigen;

namespace RaffinamentoLibrary
{
    Triangle::Triangle(const unsigned int& Id, const array<unsigned int,3>& Idvertices, const array<unsigned int,3>& Idedges):
        Id(Id),
        Idvertices(Idvertices),
        Idedges(Idedges)
    {
        p1 = &Points[vertices[1]];
        p2 = &Points[vertices[2]];
        p3 = &Points[vertices[3]];
        edge1 = &Segments[edges[1]];
        edge2 = &Segments[edges[2]];
        edge3 = &Segments[edges[3]];

        Area = AreaCalculator(&p1,&p2,&p3);
        longestEdge = FindLongestEdge(&edge1, &edge2, &edge3);
    }

    double AreaCalculator(&p1, &p2,&p3)
    {
        double x1 = p1->x;
        double y1 = p1->y;
        double x2 = p2->x;
        double y2 = p2->y;
        double x3 = p3->x;
        double y3 = p3->y;
        double doubleArea = 0;

        //Formula dell'area di Gauss
        doubleArea += (x1*y2) - (y1*x2);
        doubleArea += (x2*y3) - (y2*x3);
        doubleArea += (x3*y1) - (y3*x1);
        return abs(doubleArea/2);
    }

    //void Triangle::setId(unsigned int IdVertice) {Id = IdVertice;}

    Segment FindLongestEdge(& edge1,&edge2, &edge3)
    {
        //array delle lunghezze
        array<double,3> lunghezze = {edge1->length, edge2->length, edge3->length};
        //array degli id
        array<Segment, 3> lati = {*edge1, *edge2, *edge3};

        //restituisce l'iteratore che punta all'elemento massimo dell'array
        auto maxIterator = max_element(lunghezze.begin(), lunghezze.end());

        //calcola la posizione dell'elemento massimo
        int maxPosition = distance(lunghezze.begin(), maxIterator);

        return lati[maxPosition];
    }


}
