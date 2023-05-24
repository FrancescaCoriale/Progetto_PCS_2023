//estremi
//lunghezza
//punto medio
//adiacenza
#ifndef __SEGMENT_H
#define __SEGMENT_H

#include <iostream>
#include "Eigen/Eigen"
#include <fstream>

using namespace Eigen;
using namespace std;

namespace SegmentLibrary
class Point:
class Segment{
public:
    unsigned int IdOrigin;
    unsigned int IdEnd;

    //{
    //    Vector2d origin = {Coordinates[originEnd[0]][0], Coordinates[originEnd[0]][1]};
    //    Vector2d end = {Coordinates[originEnd[1]][0], Coordinates[originEnd[1]][1]};
    //    LengthEdge = (end-origin).norm();//calcolo la norma e la salvo nel vettore
    //    //elemento i-esimo di LengthEdge è la lunghezza dell'iesimo lato dentro OriginEnd
    //}
    midPoint()=default;
    LenghtEdge()=default;
    double LenghtEdge(){
        Vector2d diff={end.X()-origin.X(), end.Y()-origin.Y()};
        return (diff).norm();}
    double midPoint() {return {(end.Y()-origin.Y())/2,(end.X()-origin.X())/2};}
    unsigned int Adjacency (){}///////////!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!











}
