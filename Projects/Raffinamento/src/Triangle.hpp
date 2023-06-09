#ifndef __TRIANGLE_H
#define __TRIANGLE_H

#include <iostream>
#include "Eigen/Eigen"
#include <fstream>
#include "Point.hpp"
#include "Segment.hpp"

using namespace std;
using namespace Eigen;

//Coordinate x e y
namespace RaffinamentoLibrary

{
    class Triangle{

        public:
        Point p1; //restituisce id, x e y
        Point p2;
        Point p3;

        Segment edge1; //restituisce origin, end, lunghezza e midpoint
        Segment edge2;
        Segment edge3;



        array<Point,3> pointsTriangle;
        array<Segment,3> segmentsTriangle;

        Segment longestEdge;
        double Area;

        unsigned int Id;
        //const array<unsigned int,3>& Idvertices;
        //const array<unsigned int,3>& Idedges;

        Triangle() = default;
        Triangle(const unsigned int& Idvalue, const array<Point,3>& vertices,
                 const array<Segment,3>& edges);



        double AreaCalculator(const Point &p1,const Point &p2, const Point &p3);

        //Segment FindLongestEdge();
        Segment FindLongestEdge( Segment &edge1,  Segment &edge2,  Segment &edge3);

        void adjacency(Triangle & t, Segment & edge);


        void setSegment(Segment &s);
        void setPoints(array<Segment,3> &segmentsTriangle);

    };

    inline ostream& operator<<(ostream& os, const Triangle& T){
       return os << T.Id << " " << to_string(T.p1.Id) << " " << to_string(T.p2.Id) << " " << to_string(T.p3.Id) << " " << to_string(T.edge1.Id) << " " << to_string(T.edge2.Id) << " " << to_string(T.edge3.Id);}

    inline bool operator == (const Triangle & obj1, const Triangle & obj2)
    {return obj1.Id == obj2.Id;}

    //connette ad un segmento un triangolo e aggiorna il contatore di adiacenze c
    //void setS1(Segment s) {segmentsTriangle[0]=s;}
    //void setS2(Segment s) {segmentsTriangle[1]=s;}
    //void setS3(Segment s) {segmentsTriangle[2]=s;}



}

#endif // __TRIANGLE_H
