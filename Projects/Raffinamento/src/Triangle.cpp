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
{//   Triangle::Triangle()
   //{
     //  Id = 0;
      // Idvertices = {};
     //  Idedges = {};
      // Area = 0.0;
      // longestEdge = FindLongestEdge() ;
  // }

    Triangle::Triangle(vector<Point>* points, vector<Segment>* segments,
                       const unsigned int& Idvalue, const array<unsigned int,3>& Idvertices,
                       const array<unsigned int,3>& Idedges):
    longestEdge(longestEdge)
    {
        Id = Idvalue;
        p1 = &((*points)[Idvertices[0]]);
        p2 = &((*points)[Idvertices[1]]);
        p3 = &((*points)[Idvertices[2]]);
        edge1 = &((*segments)[Idedges[0]]);
        edge2 = &((*segments)[Idedges[1]]);
        edge3 = &((*segments)[Idedges[2]]);


        longestEdge = FindLongestEdge(edge1, edge2, edge3);
        Area = AreaCalculator(p1,p2,p3);
    }

    double AreaCalculator(Point* p1, Point* p2, Point* p3)
    {
        double x1 = p1->x;
        double y1 = p1->y;
        double x2 = p2->x;
        double y2 = p2->y;
        double x3 = p3->x;
        double y3 = p3->y;
        double doubleArea = 0;

        //Formula dell'area di Gauss
        doubleArea += (x1*y2) - (y1*x2);
        doubleArea += (x2*y3) - (y2*x3);
        doubleArea += (x3*y1) - (y3*x1);
        return abs(doubleArea/2);
    }

    //void Triangle::setId(unsigned int IdVertice) {Id = IdVertice;}

    Segment FindLongestEdge(Segment* edge1,Segment* edge2, Segment* edge3)
    {
        //array delle lunghezze
        array<double,3> lunghezze = {edge1->length, edge2->length, edge3->length};
        //array degli id
        array<Segment, 3> lati = {*edge1, *edge2, *edge3};

        //restituisce l'iteratore che punta all'elemento massimo dell'array
        auto maxIterator = max_element(lunghezze.begin(), lunghezze.end());

        //calcola la posizione dell'elemento massimo
        int maxPosition = distance(lunghezze.begin(), maxIterator);
        return lati[maxPosition];
    }


}
