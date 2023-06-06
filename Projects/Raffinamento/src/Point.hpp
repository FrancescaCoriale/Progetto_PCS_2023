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
        Point() = default;
        Point(unsigned int & IdValue, double & xValue, double & yValue);
        ///mi basta "." non serve get
        //double getX() const; //const dice che il metodo non deve cambiare il parametro
        //double getY() const;
        //unsigned int getId() const;
    };
    //bool operator == (Point & obj1, Point& obj2)
   // {return obj1.Id = obj2.Id;}


}
#endif // __POINT_H
