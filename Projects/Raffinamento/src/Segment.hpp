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
    unsigned int Id;
    Point origin;
    Point end;

    Triangle * t1;
    Triangle * t2;

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
    Segment(unsigned int IdValue, Point oValue, Point eValue);

    double LenghtEdge(Point origin, Point end);
    array<double,2> MidPoint(Point origin, Point end);

    Triangle *getT1(); //cosi restituisco i due triangoli che contengono il segmento (ADIACENZA)
    Triangle *getT2();
    ///mi basta usare "." non serve get
    //double getLengthEdge() const;

};
}
#endif // __SEGMENT_H
