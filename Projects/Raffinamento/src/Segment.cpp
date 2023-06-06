#include <Eigen/StdVector>
#include <iostream>
#include <fstream>
#include "Eigen/Eigen"
#include "Point.hpp"
#include "Segment.hpp"
//#include "map"
using namespace std;

namespace RaffinamentoLibrary
{
Segment::Segment(const unsigned int& IdValue, const Point& origin, const Point& end):
    Id(IdValue), origin(origin), end(end)

    {
        length = LenghtEdge(origin, end);

        midPoint = MidPoint(origin, end);
    }


    double Segment::LenghtEdge(const Point &origin, const Point &end) {
        Vector2d diff={end.x-origin.x, end.y-origin.y};

        return (diff).norm();
    }

    array<double,2> Segment::MidPoint(const Point &origin, const Point &end) {
        return {(end.y - origin.y)/2,(end.x - origin.x)/2};
    }

    Triangle* Segment::getT1() {return T1;}
    Triangle* Segment::getT2() {return T2;}


    void Segment::connectTriangle(){
        if (T1 = nullptr){
             T1 = ;
        };
        else:
            T2 =;

    }

    void Segment::disconnectTriangle(){

    }
    //double Segment::getLengthEdge() const {return length;}

}
