#ifndef __POINT_H
#define __POINT_H

#include <iostream>
#include "Eigen/Eigen"
#include <fstream>

using namespace std;

//Coordinate x e y
namespace RaffinamentoLibrary
{
    class Point {
        unsigned int Id;
        double x;
        double y;
    public:
        Point();
        Point(unsigned int IdValue, double xValue, double yValue);
        double getX() const; //const dice che il metodo non deve cambiare il parametro
        double getY() const;
        unsigned int getId() const;
    };

}
#endif // __POINT_H
