//estremi
//lunghezza
//punto medio
//adiacenza
#ifndef __SEGMENT_H
#define __SEGMENT_H

#include <iostream>
#include "Eigen/Eigen"
#include <fstream>
#include "Point.hpp"

using namespace Eigen;
using namespace std;

namespace SegmentLibrary{
class Triangle;
class Segment{
public:
    unsigned int IdOrigin;
    unsigned int IdEnd;
    Triangle *t1;
    Triangle * t2;

    //{
    //    Vector2d origin = {Coordinates[originEnd[0]][0], Coordinates[originEnd[0]][1]};
    //    Vector2d end = {Coordinates[originEnd[1]][0], Coordinates[originEnd[1]][1]};
    //    LengthEdge = (end-origin).norm();//calcolo la norma e la salvo nel vettore
    //    //elemento i-esimo di LengthEdge è la lunghezza dell'iesimo lato dentro OriginEnd
    //}
    midPoint()=default;
    LenghtEdge()=default;
    double LenghtEdge(){
        Vector2d diff={end.X()-origin.X(), end.Y()-origin.Y()};
        return (diff).norm();}
    double midPoint() {return {(end.Y()-origin.Y())/2,(end.X()-origin.X())/2};}
    Triangle*gett1(){return t1;} //cosi prendo i due triangoli che contengono il segmento
    Triangle*gett2(){return t2;}










}
}
