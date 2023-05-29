#ifndef __TRIANGLE_H
#define __TRIANGLE_H

#include <iostream>
#include "Eigen/Eigen"
#include <fstream>
#include "Point.hpp"
#include "Segment.hpp"

using namespace std;
using namespace Eigen;

//Coordinate x e y
namespace RaffinamentoLibrary
{
    class Triangle{

        Point p1; //restituisce id, x e y
        Point p2;
        Point p3;
        Segment edge1; //restituisce origin, end, lunghezza e midpoint
        Segment edge2;
        Segment edge3;
        public:
        double Area;
        Segment longestEdge;

        const unsigned int Id;
        const array<unsigned int,3>& vertices;
        const array<unsigned int,3>& edges;

    public:
        Triangle();
        Triangle(const unsigned int& Id, array<unsigned int,3>& vertices, array<unsigned int,3>& edges);
        double AreaCalculator(Point& p1, Point& p2, Point& p3);
        //void setId(unsigned int IdVerice);
        Segment FindLongestEdge(Segment& edge1,Segment& edge2, Segment& edge3);
    };
}

#endif // __TRIANGLE_H
