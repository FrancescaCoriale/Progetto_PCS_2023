#include <Eigen/StdVector>
#include <iostream>
#include <fstream>
#include "Eigen/Eigen"
#include "Point.hpp"
#include "Segment.hpp"
//#include "map"

namespace RaffinamentoLibrary
{
    Segment::Segment(unsigned int IdValue, Point oValue, Point eValue)
    {
        Id = IdValue;
        origin = oValue;
        end = eValue;
        length = LenghtEdge(origin, end);
        midPoint = MidPoint(origin, end);
    }

    double Segment::LenghtEdge(Point origin, Point end) {
        Vector2d diff={end.x-origin.x, end.y-origin.y};
        return (diff).norm();
    }

    array<double,2> Segment::MidPoint(Point origin, Point end) {
        return {(end.y-origin.y)/2,(end.x-origin.x)/2};
    }

    Triangle* Segment::getT1() {return t1;}
    Triangle* Segment::getT2() {return t2;}

    array<Point,2> Segment::getVertices() const {return {origin,end};}

    //double Segment::getLengthEdge() const {return length;}

}
