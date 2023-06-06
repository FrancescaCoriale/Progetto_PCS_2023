#ifndef __TEST_SEGMENT_H
#define __TEST_SEGMENT_H
#include "Point.hpp"
#include "Segment.hpp"
#include "Eigen/Eigen"
#include <cmath>
#include <iostream>
#include <fstream>
#include <gtest/gtest.h>
#include <algorithm>

using namespace Eigen;
using namespace RaffinamentoLibrary;
using namespace testing;
using namespace std;
TEST(TestRaffinamento, TestLenghtEdge)
{
    Segment S;
<<<<<<< Updated upstream
    unsigned int idO = 13;
    double xO = 0.5;
    double yO = 0.5;
    Point origin(idO, xO, yO);
    unsigned int idE = 3;
    double xE= 1;
    double yE = 1;
    Point end(idE, xE, yE);
=======
    unsigned int IdEdge=5;
    unsigned int idO = 13; double xO = 0.5; double y = 0.5;
    Point origin= Point(idO,xO,xO);
    Point end= Point(3,1,1);
>>>>>>> Stashed changes
    double lenght=S.LenghtEdge(origin,end);
    EXPECT_EQ(lenght,1/sqrt(2));

}
TEST(TestRaffinamento,TestMidPoint)
{
    Segment S;
    unsigned int idO = 13;
    double xO = 0.5;
    double yO = 0.5;
    Point origin(idO, xO, yO);
    unsigned int idE = 3;
    double xE= 1;
    double yE = 1;
    Point end(idE, xE, yE);
    array<double,2> midpoint=S.MidPoint(origin,end);
    array<double,2> expected = {0.25,0.25};
    EXPECT_EQ(midpoint, expected);




}


#endif // __TEST_SEGMENT_H
