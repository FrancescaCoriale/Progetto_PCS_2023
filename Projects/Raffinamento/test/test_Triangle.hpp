//importa triangolo e fai un altro file
#ifndef __TEST_TRIANGLE_H
#define __TEST_TRIANGLE_H

#include <cmath>
#include <gtest/gtest.h>
#include "Segment.hpp"
#include "Triangle.hpp"
#include "Raffinamento.hpp"
#include "Point.hpp"
#include "Eigen/Eigen"
#include <algorithm>

using namespace Eigen;
using namespace RaffinamentoLibrary;
using namespace testing;
TEST(TestRaffinamento,TestAreaCalculator)
{
    unsigned int IdTriangle=9;
    Point p1= Point(13,0.5,0.5);
    Point p2= Point(18,0,0.5);
    Point p3= Point(32,0.25,0.25);


}
#endif // __TEST_TRIANGLE_H
