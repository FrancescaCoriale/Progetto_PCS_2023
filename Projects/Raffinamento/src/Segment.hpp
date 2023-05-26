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

namespace RaffinamentoLibrary {
//FORWARD DECLARETION
class Triangle;

class Segment {
    public:
    Point origin;
    Point end;
    Triangle *t1;
    Triangle *t2;
    double length;
    array<double,2> midPoint;

    //{
    //    Vector2d origin = {Coordinates[originEnd[0]][0], Coordinates[originEnd[0]][1]};
    //    Vector2d end = {Coordinates[originEnd[1]][0], Coordinates[originEnd[1]][1]};
    //    LengthEdge = (end-origin).norm();//calcolo la norma e la salvo nel vettore
    //    //elemento i-esimo di LengthEdge è la lunghezza dell'iesimo lato dentro OriginEnd
    //}
    //midPoint()=default;
    //LenghtEdge()=default;
    Segment() = default;
    Segment(Point oValue, Point eValue);
    double LenghtEdge();
    double MidPoint();
    Triangle *getT1(); //cosi restituisco i due triangoli che contengono il segmento (ADIACENZA)
    Triangle *getT2();

    Segment getOriginEnd ();

};
}
#endif // __SEGMENT_H
