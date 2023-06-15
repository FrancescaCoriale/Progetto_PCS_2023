#ifndef __TEST_RAFFINAMENTO_H
#define __TEST_RAFFINAMENTO_H

#include <gtest/gtest.h>
#include "Raffinamento.hpp"
#include "Point.hpp"
#include "Segment.hpp"
#include "Triangle.hpp"
using namespace std;
using namespace testing;
using namespace RaffinamentoLibrary;

TEST(TestRaffinamento, TestDivision)
{
    TriangularMesh mesh;
    unsigned int NumberCell0D = 109;
    unsigned int NumberCell1D = 294;
    unsigned int NumberCell2D = 186;
    // array<Triangle,2> Division(Triangle& T);
    unsigned int IdTriangle = 0;
    unsigned int id0 = 0; double x0 = -1; double y0 = 0;
    unsigned int id1 = 1; double x1 = -1; double y1 = -1;
    unsigned int id2 = 2; double x2 = 0; double y2 = 1;
    Point p0(id0,x0,y0);
    Point p1(id1,x1,y1);
    Point p2(id2,x2,y2);
    array<Point,3> vertices = {p0,p1,p2};

    unsigned int idE0 = 0;
    unsigned int idE1 = 1;
    unsigned int idE2 = 2;
    Segment edge0(idE0,p0,p1);
    Segment edge1(idE1,p1,p2);
    Segment edge2(idE2,p2,p0);
    array<Segment,3> edges = {edge0,edge1,edge2};

    Triangle T(IdTriangle, vertices, edges);

    unsigned int midPointId = 109;
    unsigned int newedge = 294;
    unsigned int newsx = 295;
    unsigned int newdx = 296;

    unsigned int T1ExpectedId = 186;
    array<unsigned int,3> T1ExpectedVertices = {p1.Id,midPointId,p0.Id};
    array<unsigned int, 3> T1ExpectedEdges = {newsx,newedge,edge0.Id};

    unsigned int T2ExpectedId = 187;
    array<unsigned int,3> T2ExpectedVertices = {midPointId,p2.Id,p0.Id};
    array<unsigned int, 3> T2ExpectedEdges = {newdx,edge2.Id,newedge};

    array<Triangle,2> NewTriangles = mesh.Division(NumberCell0D, NumberCell1D,
                                                   NumberCell2D, T, T.FindLongestEdge(T.segmentsTriangle));

    Triangle newT1 = NewTriangles[0];
    Triangle newT2 = NewTriangles[1];

    array<unsigned int,3> T1Vertices;
    array<unsigned int, 3> T1Edges;
    array<unsigned int,3> T2Vertices;
    array<unsigned int, 3> T2Edges;
    //voglio estrarre solo gli id degli elementi dei due triangoli nuovi
    for (unsigned int i=0; i<3; i++)
    {
        T1Vertices[i] = newT1.pointsTriangle[i].Id;
        T1Edges[i] =  newT1.segmentsTriangle[i].Id;
        T2Vertices[i] = newT2.pointsTriangle[i].Id;
        T2Edges[i] =  newT2.segmentsTriangle[i].Id;

    }

//test:
    EXPECT_EQ(newT1.Id, T1ExpectedId);
    EXPECT_EQ(T1Vertices, T1ExpectedVertices);
    EXPECT_EQ(T1Edges, T1ExpectedEdges);

    EXPECT_EQ(newT2.Id, T2ExpectedId);
    EXPECT_EQ(T2Vertices, T2ExpectedVertices);
    EXPECT_EQ(T2Edges, T2ExpectedEdges);
}

TEST(Testraffinamento, TestRaffinamento)
{

}

#endif // __TEST_RAFFINAMENTO_H
