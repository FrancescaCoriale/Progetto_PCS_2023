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
    private:
        Point p1; //restituisce id, x e y
        Point p2;
        Point p3;
        Segment edge1; //restituisce origin, end, lunghezza e midpoint
        Segment edge2;
        Segment edge3;
        double Area;

        const unsigned int Id;
        const array<unsigned int,3>& vertices;
        const array<unsigned int,3>& edges;

    public:
        Triangle(const unsigned int& Id, array<unsigned int,3>& vertices, array<unsigned int,3>& edges);
        double AreaCalculator(Point& p1, Point& p2, Point& p3);
<<<<<<< Updated upstream

        void setId(unsigned int IdVerice);

=======
        unsigned int FindLongestEdge(Segment& edge1,Segment& edge2, Segment& edge3);
>>>>>>> Stashed changes
    };
}

#endif // __TRIANGLE_H
