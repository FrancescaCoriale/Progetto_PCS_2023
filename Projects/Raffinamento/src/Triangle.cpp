#include <Eigen/StdVector>
#include <iostream>
#include <fstream>
#include "Eigen/Eigen"
#include "MeshUtilities.hpp"
#include "Point.hpp"
#include "Segment.hpp"
#include "Triangle.hpp"
//#include "map"


using namespace std;
using namespace Eigen;

namespace RaffinamentoLibrary
{
    Triangle::Triangle(const unsigned int& Id, const array<unsigned int,3>& vertices, const array<unsigned int,3>& edges):
        Id(Id),
        vertices(vertices),
        edges(edges)
    {
          edges[1] = edge1.getId();
          edges[2] = edge2.getId();
          edges[3] = edge3.getId();
          vertices[1] = p1.getId();
          vertices[2] = p2.getId();
          vertices[3] = p3.getId();
          Area = AreaCalculator(p1,p2,p3);
    };

    double AreaCalculator(Point& p1, Point& p2, Point& p3)
    {
        double x1 = p1.getX();
        double y1 = p1.getX();
        double x2 = p2.getX();
        double y2 = p2.getX();
        double x3 = p3.getX();
        double y3 = p3.getX();
        double doubleArea = 0;

        //Formula dell'area di Gauss
        doubleArea += (x1*y2) - (y1*x2);
        doubleArea += (x2*y3) - (y2*x3);
        doubleArea += (x3*y1) - (y3*x1);
        return abs(doubleArea/2);
    };


}
