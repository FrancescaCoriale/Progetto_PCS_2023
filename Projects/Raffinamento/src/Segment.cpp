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
        double originX = origin.getX(); double originY = origin.getY();
        double endX = end.getX(); double endY = end.getY();
        Vector2d diff={endX-originX, endY-originY};
        return (diff).norm();
    }

    array<double,2> MidPoint(Point origin, Point end) {
        double originX = origin.getX(); double originY = origin.getY();
        double endX = end.getX(); double endY = end.getY();
        return {(endY-originY)/2,(endX-originX)/2};
    }

<<<<<<< Updated upstream
    Segment(unsigned int IdValue, Point oValue, Point eValue) {
        Id = IdValue;
=======
    Segment(Point oValue, Point eValue):
    {
>>>>>>> Stashed changes
        origin = oValue;
        end = eValue;
        length = LenghtEdge(origin, end);
        midPoint = MidPoint(origin, end);
    }

    Triangle *getT1() {return t1;}
    Triangle *getT2() {return t2;}

    Point getOriginEnd() const{
        return origin, end;}

    unsigned int getId() const {return Id;}



}
