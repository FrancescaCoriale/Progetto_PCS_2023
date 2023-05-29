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

    public:
        unsigned int Id;
        double x;
        double y;
        Point();
        Point(unsigned int IdValue, double xValue, double yValue);
        ///mi basta "." non serve get
        //double getX() const; //const dice che il metodo non deve cambiare il parametro
        //double getY() const;
        //unsigned int getId() const;
    };

}
#endif // __POINT_H
