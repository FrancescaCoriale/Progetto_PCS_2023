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
        return {(end.x + origin.x)/2,(end.y + origin.y)/2};
    }

    void Segment::connectTriangle(unsigned int &IdAdj){
        if (c == 0){
            IdAdj1 = IdAdj;
            c++;
        }
        else{
            IdAdj2 = IdAdj;
            //c++;
        }
    }

    void Segment::disconnectTriangle(unsigned int &IdAdj){
        if(IdAdj == IdAdj1){
            IdAdj1 = 0;
            c--;
        }
        else{
            IdAdj2 = 0;
            //c--;
        }
    }

    unsigned int Segment::getAdj1() {return IdAdj1;}
    unsigned int Segment::getAdj2() {return IdAdj2;}


//    void change(Segment &obj)
//    {
//        id_origin = obj.origin.Id;
//        obj.origin.Id = obj.end.Id;
//        obj.end.Id = id_origin;

//        x_origin = obj.origin.x;
//        obj.origin.x = obj.end.x;
//        obj.end.x = x_origin;

//        y_origin = obj.origin.y;
//        obj.origin.y = obj.end.y;
//        obj.end.y = y_origin;
//    }


}
