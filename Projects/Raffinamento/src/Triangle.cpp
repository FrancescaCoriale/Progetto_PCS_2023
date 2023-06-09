#include <Eigen/StdVector>
#include <iostream>
#include <fstream>
#include "Eigen/Eigen"
#include <algorithm>
#include "Point.hpp"
#include "Segment.hpp"
#include "Triangle.hpp"
//#include "map"


using namespace std;
using namespace Eigen;

namespace RaffinamentoLibrary

{
    Triangle::Triangle(const unsigned int& Idvalue, const array<Point,3>& vertices,
                       const array<Segment,3>& edges):
    Id(Idvalue)
    {

        pointsTriangle = {vertices[0],vertices[1],vertices[2]};
        //segmentsTriangle = {edge1,edge2,edge3};
        setSegment(edges[0]);
        setSegment(edges[1]);
        setSegment(edges[2]);

        setPoints(segmentsTriangle);

        Area = Triangle::AreaCalculator(vertices[0],vertices[1],vertices[2]);
        longestEdge = Triangle::FindLongestEdge(edges[0], edges[1], edges[2]);

    }


    double Triangle::AreaCalculator(const Point &p1, const Point &p2, const Point &p3)

    {
        double x1 = p1.x;
        double y1 = p1.y;
        double x2 = p2.x;
        double y2 = p2.y;
        double x3 = p3.x;
        double y3 = p3.y;
        double doubleArea = 0;

        //Formula dell'area di Gauss

        doubleArea += (x1*y2) - (y1*x2);
        doubleArea += (x2*y3) - (y2*x3);
        doubleArea += (x3*y1) - (y3*x1);

        //cout <<"area triangolo  "<<Id<< "___ "<<abs(doubleArea/2) <<endl;

        double area = abs(doubleArea/2);
        return area;




    }

    //void Triangle::setId(unsigned int IdVertice) {Id = IdVertice;}


    Segment Triangle::FindLongestEdge(const Segment &edge1,const Segment &edge2,const Segment &edge3)
    {
        //array delle lunghezze
        array<double,3> lunghezze = {edge1.length, edge2.length, edge3.length};
        //array degli id
        array<Segment, 3> lati = {edge1, edge2, edge3};

        //restituisce l'iteratore che punta all'elemento massimo dell'array
        auto maxIterator = max_element(lunghezze.begin(), lunghezze.end());

        //calcola la posizione dell'elemento massimo
        int maxPosition = distance(lunghezze.begin(), maxIterator);
        return lati[maxPosition];
    }


//ordino i segmenti in senso antiorario:
    void Triangle::setSegment(const Segment &s){
        if ((pointsTriangle[0] == s.origin || pointsTriangle[0] == s.end) &&
            (pointsTriangle[1] == s.end || pointsTriangle[1] == s.origin))
        {
            segmentsTriangle[0] = s;
        }
        if ((pointsTriangle[1] == s.origin || pointsTriangle[1] == s.end) && (pointsTriangle[2] == s.end || pointsTriangle[2] == s.origin))
        {
            segmentsTriangle[1] = s;
        }
        if ((pointsTriangle[2]  == s.origin || pointsTriangle[2]  == s.end) && (pointsTriangle[0]  == s.end || pointsTriangle[0]  == s.origin))
        {
            segmentsTriangle[2] = s;
        }
    }


    void Triangle::setPoints(array<Segment,3> &segmentsTriangle){
        if (segmentsTriangle[0].end.Id != segmentsTriangle[1].origin.Id)
        {
            Point tmp = segmentsTriangle[0].origin;
            segmentsTriangle[0].origin = segmentsTriangle[0].end;
            segmentsTriangle[0].end = tmp;
        }
        if (segmentsTriangle[1].end.Id != segmentsTriangle[2].origin.Id)
        {
            Point tmp = segmentsTriangle[1].origin;
            segmentsTriangle[1].origin = segmentsTriangle[1].end;
            segmentsTriangle[1].end = tmp;
        }
        if (segmentsTriangle[2].end.Id != segmentsTriangle[0].origin.Id)
        {
            Point tmp = segmentsTriangle[2].origin;
            segmentsTriangle[2].origin = segmentsTriangle[2].end;
            segmentsTriangle[2].end = tmp;
        }
    }

    void Triangle::adjacency(Triangle &t, Segment &edge)
    {
        Triangle *T = nullptr;
        T = &t;
        edge.connectTriangle(T);
    }


}
