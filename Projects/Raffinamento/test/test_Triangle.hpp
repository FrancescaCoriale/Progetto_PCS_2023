//importa triangolo e fai un altro file
#ifndef __TEST_TRIANGLE_H
#define __TEST_TRIANGLE_H

#include <cmath>
#include <gtest/gtest.h>
#include "Point.hpp"
#include "Segment.hpp"
#include "Triangle.hpp"
#include "Raffinamento.hpp"
#include "Point.hpp"
#include "Eigen/Eigen"
#include <algorithm>

using namespace std;
using namespace Eigen;
using namespace RaffinamentoLibrary;
using namespace testing;



//Triangle(const unsigned int& Idvalue, const array<Point,3>& vertices,
         //const array<Segment,3>& edges);



TEST(TestRaffinamento,TestAreaCalculator)
{
    Triangle T;
    unsigned int IdTriangle=9;
    const array<Point,3> vertices={13, 18, 32};
    const array<Segment,3> edges={17, 20, 21};
    Triangle triangle(const unsigned int& Idvalue, const array<Point,3>& vertices,
             const array<Segment,3>& edges);
    EXPECT_EQ(triangle.Id, IdTriangle);
    EXPECT_EQ(triangle.pointsTriangle, vertices);
    EXPECT_EQ(triangle.segmentsTriangle, edges);

}




TEST(TestRaffinamento,TestAreaCalculator)
{
    Triangle T;
    unsigned int IdTriangle=9;
    unsigned int id1 = 13; double x1 = 0.5; double y1 = 0.5;
    unsigned int id2 = 18; double x2 = 0; double y2 = 0.5;
    unsigned int id3 = 32; double x3 = 0.25; double y3 = 0.25;
    Point p1(id1,x1,y1);
    Point p2(id2,x2,y2);
    Point p3(id3,x3,y3);

    double Area = T.AreaCalculator(p1,p2,p3);
    double AreaExpected = (0.125)/2;

    EXPECT_EQ(Area, AreaExpected);
}

TEST(TestRaffinamento, TestFindLongestEdge)
{
    Triangle T;
    unsigned int IdTriangle=9;
    unsigned int idE1 = 17;
    unsigned int idE2 = 20;
    unsigned int idE3 = 21;

    unsigned int id1 = 18; double x1 = 0; double y1 = 0.5;
    unsigned int id2 = 13; double x2 = 0.5; double y2 = 0.5;
    unsigned int id3 = 32; double x3 = 0.25; double y3 = 0.25;
    Point o1(id1,x1,y1); Point e1(id2,x2,y2);
    Point o2(id2,x2,y2); Point e2(id3,x3,y3);
    Point o3(id3,x3,y3); Point e3(id1,x1,y1);

    Segment edge1(id1,o1,e1);
    Segment edge2(id2,o2,e2);
    Segment edge3(id3,o3,e3);

    Segment longestEdge = T.FindLongestEdge(edge1,edge2,edge3);
    //lunghezze segmenti:
    //edge1 = 0.5
    //edge2 = 0.353
    //edge3 = 0.353
    Segment LongestExpected = edge1;
    EXPECT_EQ(longestEdge.Id, LongestExpected.Id);
}
#endif // __TEST_TRIANGLE_H
