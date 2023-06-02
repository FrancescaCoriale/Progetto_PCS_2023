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


        Point *p1; //restituisce id, x e y
        Point *p2;
        Point *p3;

        Segment *edge1; //restituisce origin, end, lunghezza e midpoint
        Segment *edge2;
        Segment *edge3;

    public:

        Segment longestEdge;
        double Area;

        unsigned int Id;
        //const array<unsigned int,3>& Idvertices;
        //const array<unsigned int,3>& Idedges;

        //Triangle();
        Triangle(vector<Point>* points, vector<Segment>* segments,
                 const unsigned int& Idvalue, const array<unsigned int,3>& Idvertices,
                 const array<unsigned int,3>& Idedges);

        array<Point,3> PointsTriangle = {*p1,*p2,*p3};
        array<Segment,3> SegmentsTriangle = {*edge1,*edge2,*edge3};


        double AreaCalculator(Point* p1, Point* p2, Point* p3);

        //Segment FindLongestEdge();
        Segment FindLongestEdge(Segment* edge1,Segment* edge2, Segment* edge3);


    };
}

#endif // __TRIANGLE_H
