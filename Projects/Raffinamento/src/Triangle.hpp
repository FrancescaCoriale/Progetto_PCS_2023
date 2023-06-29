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
        unsigned int Id;
        array<Point,3> pointsTriangle;
        array<Segment,3> segmentsTriangle;
        unsigned int longestEdge = 0;
        double Area = 0.0;

        //const array<unsigned int,3>& Idvertices;
        //const array<unsigned int,3>& Idedges;

        Triangle() = default;
        Triangle(const unsigned int& Idvalue, const array<Point,3>& vertices,
                 const array<Segment,3>& edges);


        void setSegment(const Segment &s);
        void setPoints(array<Segment,3> &segmentsTriangle);

        double AreaCalculator(const Point &p1,const Point &p2, const Point &p3);

        //Segment FindLongestEdge();

        unsigned int FindLongestEdge(const array<Segment, 3> &segmentsTriangle);

//        Segment FindLongestEdge(const vector<Segment *> & segmentsTriangle);
//        void adjacency(Triangle &t, Segment &edge);
//        void setSegment(const Segment &s);
//        void setPoints(vector<Segment*> &segmentsTriangle);

        void adjacency(Segment &edge); //Triangle &t,
    };


    inline ostream& operator << (ostream& os, const Point& P){
       return os << P.Id << ";" << to_string(P.x) << ";" << to_string(P.y) << endl;}

    inline ostream& operator << (ostream& os, const Segment& S){
       return os << S.Id << ";" << S.origin.x << ";" << S.origin.y << ";" << S.end.x << ";" << S.end.y <<endl;}

    inline ostream& operator << (ostream& os, const Triangle& T){
       return os << T.Id << ";" << to_string(T.pointsTriangle[0].Id) << ";" << to_string(T.pointsTriangle[1].Id) << ";" << to_string(T.pointsTriangle[2].Id) << ";" << to_string(T.segmentsTriangle[0].Id) << ";" << to_string(T.segmentsTriangle[1].Id) << ";" << to_string(T.segmentsTriangle[2].Id) <<endl;}




    inline bool operator == (const Triangle & obj1, const Triangle & obj2)
    {return obj1.Id == obj2.Id;}

    //connette ad un segmento un triangolo e aggiorna il contatore di adiacenze c
    //void setS1(Segment s) {segmentsTriangle[0]=s;}
    //void setS2(Segment s) {segmentsTriangle[1]=s;}
    //void setS3(Segment s) {segmentsTriangle[2]=s;}
}


#endif // __TRIANGLE_H
