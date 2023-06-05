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

        array<Point,3> pointsTriangle;
        array<Segment,3> segmentsTriangle;

        Segment longestEdge;
        double Area;

        unsigned int Id;
        //const array<unsigned int,3>& Idvertices;
        //const array<unsigned int,3>& Idedges;

        Triangle() = default;
        Triangle(const unsigned int& Idvalue, const array<Point,3>& vertices,
                 const array<Segment,3>& edges);


        double AreaCalculator(const Point &p1,const Point &p2, const Point &p3);

        //Segment FindLongestEdge();
        Segment FindLongestEdge(const Segment &edge1, const Segment &edge2, const Segment &edge3);


    };
}

#endif // __TRIANGLE_H
