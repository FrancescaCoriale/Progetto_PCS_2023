#ifndef __RAFFINAMENTO_H
#define __RAFFINAMENTO_H

#include <iostream>
#include "Eigen/Eigen"
#include <fstream>
#include "Importazione.hpp"

using namespace Eigen;
using namespace std;
using namespace ImportLibrary;

namespace AlgorithmLibrary{

class Division{

    private:

    unsigned int LongestEdge;


    public:

    Vector2d Midpoint;
    int FindLongestEdge(Data Input, unsigned int& LongestEdge); //restituisce il lato più lungo
    void FindMidpoint(const unsigned int& LongestEdge, Data Input, Vector2d& Midpoint); //restituisce vettore 2Dim contenente le coordinate
    void CreateTriangles(const unsigned int& LongestEdge, Data Input, Vector2d& Midpoint);

};

class Raffinamento{
    private:

    Division division;
    const unsigned int theta;

    public:

    Raffinamento() = default;
    Raffinamento(Data Input, const unsigned int& theta, vector<SortArea::Pair> Aree, Adjacency GetList);





};


}
#endif // __RAFFINAMENTO_H
