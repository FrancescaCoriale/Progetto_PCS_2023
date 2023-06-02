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
        double Area;
        Segment longestEdge;

        const unsigned int Id;
        const array<unsigned int,3>& Idvertices;
        const array<unsigned int,3>& Idedges;

        Triangle();
        Triangle(std::vector<Point>* points,std::vector<Segment>* segments,const unsigned int& Id, array<unsigned int,3>& Idvertices, array<unsigned int,3>& Idedges);

<<<<<<< Updated upstream
        array<Point,3> PointsTriangle = {*p1,*p2,*p3};
        array<Segment,3> SegmentsTriangle = {*edge1,*edge2,*edge3};
=======
        array<Point,3> PointsTriangle = {*p1, *p2, *p3};
        array<Segment,3> SegmentsTriangle = {*edge1, *edge2, *edge3};
>>>>>>> Stashed changes

        double AreaCalculator(Point* p1, Point* p2, Point* p3);

        Segment FindLongestEdge(Segment* edge1,Segment* edge2, Segment* edge3);


    };
}

#endif // __TRIANGLE_H
