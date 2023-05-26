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

    double Segment::LenghtEdge(Point origin, Point end){
        double originX = origin.getX(); double originY = origin.getY();
        double endX = end.getX(); double endY = end.getY();
        Vector2d diff={endX-originX, endY-originY};
        return (diff).norm();
    }

    array<double,2> Segment::MidPoint(Point origin, Point end) {
        double originX = origin.getX(); double originY = origin.getY();
        double endX = end.getX(); double endY = end.getY();
        return {(endY-originY)/2,(endX-originX)/2};
    }

    Triangle* Segment::getT1() {return t1;}
    Triangle* Segment::getT2() {return t2;}

    unsigned int Segment::getId() const {return Id;}

    double Segment::getLengthEdge() const {return length;}

}
