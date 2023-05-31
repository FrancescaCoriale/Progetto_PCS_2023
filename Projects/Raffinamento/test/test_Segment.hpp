#ifndef __TEST_SEGMENT_H
#define __TEST_SEGMENT_H

#include <cmath>
#include <gtest/gtest.h>
#include "Segment.hpp"
#include "Raffinamento.hpp"
#include "Point.hpp"
#include "Eigen/Eigen"
#include <algorithm>

using namespace Eigen;
using namespace RaffinamentoLibrary;
using namespace testing;
TEST(TestRaffinamento, TestLenghtEdge)
{
    unsigned int IdEdge=5;
    Point origin= Point(13,0.5,0.5);
    Point end= Point(3,1,1);
    double lenght=Segment::LenghtEdge(origin,end);
    EXPECT_EQ=(lenght,1/sqrt(2));

}
TEST(TestRaffinamento,TestMidPoint)
{
    Point origin= Point(13,0.5,0.5);
    Point end= Point(3,1,1);
    array<double,2> midpoint=Segment::MidPoint(origin,end);
    EXPECT_EQ=(midpoint,{0.25,0.25});


}


#endif // __TEST_SEGMENT_H
