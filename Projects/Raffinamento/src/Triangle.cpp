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
    Triangle::Triangle(const unsigned int& Id, const array<unsigned int,3>& vertices, const array<unsigned int,3>& edges):
        Id(Id),
        vertices(vertices),
        edges(edges)
    {
          edge1.setId(edges[1]);
          edge2.setId(edges[2]);
          edge3.setId(edges[3]);
          p1.setId(vertices[1]);
          p2.setId(vertices[2]);
          p3.setId(vertices[3]);
          Area = AreaCalculator(p1,p2,p3);
    }

    double AreaCalculator(Point& p1, Point& p2, Point& p3)
    {
        double x1 = p1.getX();
        double y1 = p1.getX();
        double x2 = p2.getX();
        double y2 = p2.getX();
        double x3 = p3.getX();
        double y3 = p3.getX();
        double doubleArea = 0;

        //Formula dell'area di Gauss
        doubleArea += (x1*y2) - (y1*x2);
        doubleArea += (x2*y3) - (y2*x3);
        doubleArea += (x3*y1) - (y3*x1);
        return abs(doubleArea/2);
    }

    void Triangle::setId(unsigned int IdVertice) {Id = IdVertice;}

    unsigned int FindLongestEdge(Segment& edge1,Segment& edge2, Segment& edge3)
    {
        //array delle lunghezze
        array<double,3> lunghezze = {edge1.getLengthEdge(), edge2.getLengthEdge(), edge3.getLengthEdge()};
        //array degli id
        array<unsigned int, 3> IdLunghezze = {edge1.getId(), edge2.getId(), edge3.getId()};

        //restituisce l'iteratore che punta all'elemento massimo dell'array
        auto maxIterator = max_element(lunghezze.begin(), lunghezze.end());

        //calcola la posizione dell'elemento massimo
        int maxPosition = distance(lunghezze.begin(), maxIterator);

        return IdLunghezze[maxPosition];
    }


}
