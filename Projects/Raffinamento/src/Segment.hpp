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
class TriangularMesh;

class Segment {
    public:
    unsigned int Id;
    Point *origin;
    Point *end;

    Triangle *t1;
    Triangle *t2;

    double length;
    array<double,2> midPoint;

    Segment(unsigned int& IdValue, unsigned int& oValue, unsigned int& eValue);

    double LenghtEdge(Point& origin, Point& end);
    array<double,2> MidPoint(Point& origin, Point& end);

    Triangle *getT1(); //cosi restituisco i due triangoli che contengono il segmento (ADIACENZA)
    Triangle *getT2();
    ///mi basta usare "." non serve get
    //double getLengthEdge() const;

};
}
#endif // __SEGMENT_H
