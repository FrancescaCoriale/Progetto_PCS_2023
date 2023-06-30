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


TEST(TestRaffinamento, TestSegment)
{
//Valori che voglio:
    unsigned int idS=13;
    unsigned int idO = 13; double xO = 0.5; double yO = 0.5;
    unsigned int idE = 3; double xE= 1; double yE = 1;


    array<double,2> expectedX = {0.5,1};
    array<double,2> expectedY {0.5,1};

//Valori che creo:
    Point origin(idO,xO,yO);
    Point end(idE, xE, yE);
    Segment segment(idS, origin, end);

    array<double,2> pointsX = {origin.x, end.x};
    array<double,2> pointsY = {origin.y, end.y};

    unsigned int segmentO = origin.Id;
    unsigned int segmentE = end.Id;

//test:
    EXPECT_EQ(segment.Id, idS);
    EXPECT_EQ(segmentO, idO);
    EXPECT_EQ(segmentE, idE);

    EXPECT_EQ(pointsX, expectedX);
    EXPECT_EQ(pointsY, expectedY);



}
TEST(TestRaffinamento, TestLenghtEdge)
{
    Segment S;
    unsigned int idO = 13; double xO = 0.5; double yO = 0.5;
    Point origin(idO, xO, yO);
    unsigned int idE = 3; double xE= 1; double yE = 1;
    Point end(idE, xE, yE);
    double lenght=S.LenghtEdge(origin,end);
    double expected = 1/sqrt(2);
    EXPECT_EQ(lenght,expected);

}
TEST(TestRaffinamento,TestMidPoint)
{
    Segment S;
    unsigned int idO = 13; double xO = 0.5; double yO = 0.5;
    Point origin(idO, xO, yO);
    unsigned int idE = 3; double xE= 1; double yE = 1;
    Point end(idE, xE, yE);
    array<double,2> midpoint=S.MidPoint(origin,end);
    array<double,2> expected = {0.75,0.75};
    EXPECT_EQ(midpoint, expected);
}


#endif // __TEST_SEGMENT_H
