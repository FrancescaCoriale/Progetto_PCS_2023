<<<<<<< Updated upstream
#ifndef __POINT_H
#define __POINT_H

#include <iostream>
#include "Eigen/Eigen"
#include <fstream>

using namespace Eigen;
using namespace std;

//Coordinate x e y
namespace PointLibrary
{
    class Point {
        double x;
        double y;
    public:
        Point(double xValue, double yValue) : x(xValue), y(yValue) {}
        double X() const {return x;} //const dice che il metodo non deve cambiare il parametro
        double Y() const {return y;}
    };

}
#endif // __POINT_H
