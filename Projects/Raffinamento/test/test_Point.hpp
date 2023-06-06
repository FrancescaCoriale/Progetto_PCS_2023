#ifndef __TEST_POINT_H
#define __TEST_POINT_H

#include <cmath>
#include <gtest/gtest.h>
#include "iostream"
#include "Raffinamento.hpp"
#include "Point.hpp"
#include "Eigen/Eigen"
#include <algorithm>

using namespace Eigen;
using namespace RaffinamentoLibrary;
using namespace testing;

TEST(TestRaffinamento, TestPoint)
{
    unsigned int idO = 13; double xO = 0.5; double yO = 0.5;
    Point point(idO,xO,xO);
    EXPECT_EQ(point.id0, id0);
    EXPECT_EQ(point.x, x0);
    EXPECT_EQ(point.y, y0);

}
















#endif // __TEST_POINT_H
