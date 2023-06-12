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



TEST(TestRaffinamento,TestTriangle)
{
//Valori che mi aspetto:
    unsigned int IdTriangleExpected =9;
    unsigned int idE1 = 17;
    unsigned int idE2 = 20;
    unsigned int idE3 = 21;

    unsigned int id1 = 18; double x1 = 0; double y1 = 0.5;
    unsigned int id2 = 13; double x2 = 0.5; double y2 = 0.5;
    unsigned int id3 = 32; double x3 = 0.25; double y3 = 0.25;

    array<unsigned int,3> verticesId = {18,13,32};
    array<double,3> verticesX = {0,0.5,0.25};
    array<double,3> verticesY = {0.5,0.5,0.25};

    array<unsigned int,3> edgesId = {17,20,21};
    array<unsigned int,3> edgesO = {18,13,32};
    array<unsigned int,3> edgesE = {13,32,18};

//Valori che creo:
    Point o1(id1,x1,y1); Point e1(id2,x2,y2);
    Point o2(id2,x2,y2); Point e2(id3,x3,y3);
    Point o3(id3,x3,y3); Point e3(id1,x1,y1);

    Segment edge1(idE1,o1,e1);
    Segment edge2(idE2,o2,e2);
    Segment edge3(idE3,o3,e3);

    const array<Point,3> vertices = {o1,o2,o3};
    const array<Segment,3> edges = {edge1, edge2, edge3};


    Triangle triangle(9, vertices, edges);
    unsigned int IdTriangle = triangle.Id;

    array<unsigned int,3> pointsId;
    array<double,3> pointsX;
    array<double,3> pointsY;

    array<unsigned int, 3> segmentsId;
    array<unsigned int, 3> segmentsO;
    array<unsigned int, 3> segmentsE;
    //voglio estrarre solo gli id degli elementi dei due triangoli nuovi
    for (unsigned int i=0; i<3; i++)
    {
        pointsId[i] = triangle.pointsTriangle[i].Id;
        pointsX[i] = triangle.pointsTriangle[i].x;
        pointsY[i] =  triangle.pointsTriangle[i].y;

        segmentsId[i] = triangle.segmentsTriangle[i].Id;
        segmentsO[i] = triangle.segmentsTriangle[i].origin.Id;
        segmentsE[i] = triangle.segmentsTriangle[i].end.Id;
    }

//test:
    EXPECT_EQ(IdTriangle, IdTriangleExpected);

    EXPECT_EQ(verticesId, pointsId);
    EXPECT_EQ(verticesX, pointsX);
    EXPECT_EQ(verticesY, pointsY);

    EXPECT_EQ(edgesId, segmentsId);
    EXPECT_EQ(edgesO, segmentsO);
    EXPECT_EQ(edgesE, segmentsE);
}




TEST(TestRaffinamento,TestAreaCalculator)
{
    Triangle T;
    //unsigned int IdTriangle=9;
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
    //unsigned int IdTriangle=9;
    unsigned int idE1 = 17;
    unsigned int idE2 = 20;
    unsigned int idE3 = 21;

    unsigned int id1 = 18; double x1 = 0; double y1 = 0.5;
    unsigned int id2 = 13; double x2 = 0.5; double y2 = 0.5;
    unsigned int id3 = 32; double x3 = 0.25; double y3 = 0.25;
    Point o1(id1,x1,y1); Point e1(id2,x2,y2);
    Point o2(id2,x2,y2); Point e2(id3,x3,y3);
    Point o3(id3,x3,y3); Point e3(id1,x1,y1);

    Segment edge1(idE1,o1,e1);
    Segment edge2(idE2,o2,e2);
    Segment edge3(idE3,o3,e3);

    unsigned int longestEdge = T.FindLongestEdge({edge1,edge2,edge3});
    //lunghezze segmenti:
    //edge1 = 0.5
    //edge2 = 0.353
    //edge3 = 0.353
    unsigned int LongestExpected = edge1.Id;
    EXPECT_EQ(longestEdge, LongestExpected);
}
#endif // __TEST_TRIANGLE_H
