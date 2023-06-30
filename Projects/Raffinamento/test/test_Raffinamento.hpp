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

TEST(TestRaffinamento, TestCreateMidPoint)
{
    unsigned int NumberCell0D = 109;
    unsigned int IdExpected = 109;
    array<double,2> CoordinatesExpected = {0.5, 1};

    unsigned int idO = 3; double xO = 1; double yO = 1;
    unsigned int idE = 2; double xE = 0; double yE = 1;
    Point origin(idO,xO,yO);
    Point end(idE,xE,yE);
    Segment longestEdge(3,origin,end);

    unsigned int IdMidpoint = NumberCell0D;
    array<double, 2> CoordinatesMidpoint = longestEdge.midPoint;
    Point Midpoint(IdMidpoint, CoordinatesMidpoint[0], CoordinatesMidpoint[1]);

    EXPECT_EQ(Midpoint.Id, IdExpected);
    EXPECT_EQ(Midpoint.x, CoordinatesExpected[0]);
    EXPECT_EQ(Midpoint.y, CoordinatesExpected[1]);



}

TEST(TestRaffinamento, TestGetUtilities)
{
    string directory = "/Users/francesca/Desktop/Progetto_PCS/Projects/Raffinamento/Dataset/Test2";
    TriangularMesh mesh;
    ImportMesh(mesh,directory);
    unsigned int IdTriangle = 1;
    unsigned int id0 = 3; double x0 = 1; double y0 = 1;
    unsigned int id1 = 2; double x1 = 0; double y1 = 1;
    unsigned int id2 = 13; double x2 = 0.5; double y2 = 0.5;
    Point p0(id0,x0,y0);
    Point p1(id1,x1,y1);
    Point p2(id2,x2,y2);
    array<Point,3> vertices = {p0,p1,p2};

    unsigned int idE0 = 3;
    unsigned int idE1 = 4;
    unsigned int idE2 = 5;
    Segment edge0(idE0,p0,p1);
    Segment edge1(idE1,p1,p2);
    Segment edge2(idE2,p2,p0);
    array<Segment,3> edges = {edge0,edge1,edge2};

    Triangle T(IdTriangle, vertices, edges);

    unsigned int longestEdge = idE0;


    unsigned int IdOppositeExpected = 13;
    unsigned int IdLatoDxExpected = 4;
    unsigned int IdLatoSxExpected = 5;
    array<unsigned int,3> utilities= mesh.GetUtilities(T,longestEdge);

    EXPECT_EQ(utilities[0], IdOppositeExpected);
    EXPECT_EQ(utilities[1], IdLatoDxExpected);
    EXPECT_EQ(utilities[2], IdLatoSxExpected);

}


TEST(TestRaffinamento, TestDivision)
{
    string directory = "/Users/francesca/Desktop/Progetto_PCS/Projects/Raffinamento/Dataset/Test2";
    TriangularMesh mesh;
    ImportMesh(mesh,directory);
    unsigned int NumberCell1D = 294;
    unsigned int NumberCell2D = 186;
    // array<Triangle,2> Division(Triangle& T);
    unsigned int IdTriangle = 1;
    unsigned int id0 = 3; double x0 = 1; double y0 = 1;
    unsigned int id1 = 2; double x1 = 0; double y1 = 1;
    unsigned int id2 = 13; double x2 = 0.5; double y2 = 0.5;
    Point p0(id0,x0,y0);
    Point p1(id1,x1,y1);
    Point p2(id2,x2,y2);
    array<Point,3> vertices = {p0,p1,p2};

    unsigned int idE0 = 3;
    unsigned int idE1 = 4;
    unsigned int idE2 = 5;
    Segment edge0(idE0,p0,p1);
    Segment edge1(idE1,p1,p2);
    Segment edge2(idE2,p2,p0);
    array<Segment,3> edges = {edge0,edge1,edge2};

    Triangle T(IdTriangle, vertices, edges);

    //Creo il nuovo punto medio
    unsigned int IdMidPoint = 109;
    array<double,2> CoordinatesMidpoint = {0.5, 1};
    Point Midpoint(IdMidPoint, CoordinatesMidpoint[0], CoordinatesMidpoint[1]);

    unsigned int longestEdge = idE0;

    unsigned int newedge = 294;
    unsigned int newso = 295;
    unsigned int newse = 296;

    unsigned int T1ExpectedId = 186;
    array<unsigned int,3> T1ExpectedVertices = {id0,IdMidPoint,id2};
    array<unsigned int, 3> T1ExpectedEdges = {newso,newedge,idE2};

    unsigned int T2ExpectedId = 187;
    array<unsigned int,3> T2ExpectedVertices = {IdMidPoint,id1,id2};
    array<unsigned int, 3> T2ExpectedEdges = {newse,idE1,newedge};

    //array<double, 2> CoordinatesMidpoint = T.segmentsTriangle[T.FindLongestEdge(T.segmentsTriangle)].midPoint; //contiene le sue coordinate,
    //unsigned int longestEdge = T.FindLongestEdge(T.segmentsTriangle);
    array<Triangle,2> NewTriangles = mesh.Division(NumberCell1D,
                                                   NumberCell2D, mesh.Triangles[IdTriangle],
                                                   longestEdge, Midpoint);

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

TEST(Testraffinamento, TestDivisionAdjacent)
{
    string directory = "/Users/francesca/Desktop/Progetto_PCS/Projects/Raffinamento/Dataset/Test2";
    TriangularMesh mesh;
    ImportMesh(mesh,directory);

    unsigned int NumberCell1D = 302;
    unsigned int NumberCell2D = 191;

    unsigned int IdTriangle = 187;
    unsigned int id0 = 109; double x0 = 0.5; double y0 = 1;
    unsigned int id1 = 2; double x1 = 0; double y1 = 1;
    unsigned int id2 = 13; double x2 = 0.5; double y2 = 0.5;
    Point p0(id0,x0,y0);
    Point p1(id1,x1,y1);
    Point p2(id2,x2,y2);
    array<Point,3> vertices = {p0,p1,p2};

    unsigned int idE0 = 296;
    unsigned int idE1 = 4;
    unsigned int idE2 = 294;
    Segment edge0(idE0,p0,p1);
    Segment edge1(idE1,p1,p2);
    Segment edge2(idE2,p2,p0);
    array<Segment,3> edges = {edge0,edge1,edge2};

    Triangle T(IdTriangle, vertices, edges);

//    unsigned int NumberCell1D = 294;
//    unsigned int NumberCell2D = 186;
//    // array<Triangle,2> Division(Triangle& T);
//    unsigned int IdTriangle = 1;
//    unsigned int id0 = 3; double x0 = 1; double y0 = 1;
//    unsigned int id1 = 2; double x1 = 0; double y1 = 1;
//    unsigned int id2 = 13; double x2 = 0.5; double y2 = 0.5;
//    Point p0(id0,x0,y0);
//    Point p1(id1,x1,y1);
//    Point p2(id2,x2,y2);
//    array<Point,3> vertices = {p0,p1,p2};

//    unsigned int idE0 = 3;
//    unsigned int idE1 = 4;
//    unsigned int idE2 = 5;
//    Segment edge0(idE0,p0,p1);
//    Segment edge1(idE1,p1,p2);
//    Segment edge2(idE2,p2,p0);
//    array<Segment,3> edges = {edge0,edge1,edge2};
//    unsigned int IdMidPoint = 109;
//    array<double,2> CoordinatesMidpoint = {0.5, 1};
//    Point Midpoint(IdMidPoint, CoordinatesMidpoint[0], CoordinatesMidpoint[1]);

//    unsigned int longestEdge = idE0;

//    array<Triangle,2> NewTriangles = mesh.Division(NumberCell1D,
//                                                   NumberCell2D, mesh.Triangles[IdTriangle],
//                                                   longestEdge, Midpoint);
//    Triangle newT = NewTriangles[1];

    //Creo il nuovo punto medio
    unsigned int IdMidPointAdj = 111;
    array<double,2> CoordinatesMidpointAdj = {0.25, 0.75};
    Point MidpointAdj(IdMidPointAdj, CoordinatesMidpointAdj[0], CoordinatesMidpointAdj[1]);

    unsigned int longestEdgeAdj = 4;


    unsigned int idso = 301;
    unsigned int idse = 302;

    unsigned int newedge = 303;

    unsigned int T1ExpectedId = 192;
    array<unsigned int,3> T1ExpectedVertices = {IdMidPoint,id2,id0};
    array<unsigned int, 3> T1ExpectedEdges = {idso,idE2,newedge};

    unsigned int T2ExpectedId = 193;
    array<unsigned int,3> T2ExpectedVertices = {id1,IdMidPoint,id0};
    array<unsigned int, 3> T2ExpectedEdges = {idse,newedge,idE0};

    array<Triangle,2> NewTrianglesAdj = mesh.DivisionAdjacent(newT, longestEdgeAdj,
             MidpointAdj, mesh.Segments[idso], mesh.Segments[idse]);

    Triangle newT1 = NewTrianglesAdj[0];
    Triangle newT2 = NewTrianglesAdj[1];

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


#endif // __TEST_RAFFINAMENTO_H
