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

    unsigned int c = 0;
    Triangle *T1;
    Triangle *T2;

    double length;
    array<double,2> midPoint;

    Segment() = default;
    Segment(const unsigned int &IdValue, const Point& origin, const Point& end);


    double LenghtEdge(const Point &origin, const Point &end);
    array<double,2> MidPoint(const Point &origin, const Point &end);

    Triangle *getT1(); //cosi restituisco i due triangoli che contengono il segmento (ADIACENZA)
    Triangle *getT2();

    void connectTriangle(Triangle *t);
    void disconnectTriangle(Triangle *t);
    ///mi basta usare "." non serve get
    //double getLengthEdge() const;


};


    inline bool operator == (const Segment & obj1, const Segment & obj2)
    {
        return obj1.Id == obj2.Id;
    }

}
#endif // __SEGMENT_H
