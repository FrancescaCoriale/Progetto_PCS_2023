#include <Eigen/StdVector>
#include <iostream>
#include <fstream>
#include "Eigen/Eigen"
#include "MeshUtilities.hpp"
#include "Point.hpp"
//#include "map"


namespace RaffinamentoLibrary
{
    Point() {
        Id = 0;
        x = 0.0;
        y = 0.0;
    }

    Point(unsigned int IdValue, double xValue, double yValue) {
        Id = IdValue;
        x = xValue;
        y = yValue;
    }

    double X() const {return x;}
    double Y() const {return y;}
}
