#ifndef __TEST_MESHUTILITIES_H
#define __TEST_MESHUTILITIES_H

#include <gtest/gtest.h>
#include "MeshUtilities.hpp"
#include "Eigen/Eigen"
#include <algorithm>

using namespace Eigen;
using namespace MeshUtilitiesLibrary;
using namespace testing;

TEST(TestMeshUtilities, TestAdjacency)
{
    unsigned int idToFind=3;
    EXPECTED_TRUE(find(Adjacency[0].begin(), Adjacency[0].end(), idToFind)!=Adjacency[0].end());

}
TEST(TestMeshUtilities,TestFindCoordinates)
{
    unsigned int id=0;
    Vector2d coordinate={-1,0};
    EXPECTED_EQ(FindCoordinates(TriangularMesh.Coordinates,id),coordinate);
}
TEST(TestMeshUtilities,TestLenghtEdge)
{
    unsigned int idEdge=5; //origin=13,end=3
    double expectedLenght=sqrt(2)/2;
    array<unsigned int,2> originEnd=FindOriginEnd(idEdge, vector<array<unsigned int, 2>> OriginEnds);
    EXPECT_EQ(LenghtEdge(originEnd, TriangularMesh.Coordinates),expectedLenght);


}
#endif // __TEST_MESHUTILITIES_H
