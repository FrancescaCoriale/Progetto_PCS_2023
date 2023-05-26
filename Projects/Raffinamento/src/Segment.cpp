#include <Eigen/StdVector>
#include <iostream>
#include <fstream>
#include "Eigen/Eigen"
#include "MeshUtilities.hpp"
#include "Point.hpp"
#include "Segment.hpp"
//#include "map"

namespace RaffinamentoLibrary
{
    double LenghtEdge(Point origin, Point end){
        double originX = origin.X(); double originY = origin.Y();
        double endX = end.X(); double endY = end.Y();
        Vector2d diff={endX-originX, endY-originY};
        return (diff).norm();
    }

    array<double,2> MidPoint(Point origin, Point end) {
        double originX = origin.X(); double originY = origin.Y();
        double endX = end.X(); double endY = end.Y();
        return {(endY-originY)/2,(endX-originX)/2};
    }

    Segment(Point oValue, Point eValue) {
        origin = oValue;
        end = eValue;
        length = LenghtEdge(origin, end);
        midPoint = MidPoint(origin, end);
    }

    Triangle *getT1() {return t1;}
    Triangle *getT2() {return t2;}

    Point getOriginEnd() {
        return origin, end;}



}
