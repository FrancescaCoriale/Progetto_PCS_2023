#ifndef __IMPORTAZIONE_H
#define __IMPORTAZIONE_H

#include <iostream>
#include "Eigen/Eigen"
#include <fstream>

using namespace Eigen;
using namespace std;
namespace ImportLibrary
{

    class Cell0D{

    public:
        unsigned int NumberCell0D;
        vector<Vector2d> Coordinates0D;

        Cell0D(unsigned int& NumberCell0D, vector<Vector2d>& Coordinates0D);

    };

    class Cell1D{
    public:

        unsigned int NumberCell1D;
        vector<vector<unsigned int>> OriginEnd1D;
        Cell1D(unsigned int& NumberCell1D, vector<vector<unsigned int>>& OriginEnd1D);

    };

    class Cell2D{
    public:
        unsigned int NumberCell2D;
        vector<vector<unsigned int>> Vertices2D;
        vector<vector<unsigned int>> Edges2D;
        Cell2D(unsigned int& NumberCell2D, vector<vector<unsigned int>>& Vertices2D, vector<vector<unsigned int>>& Edges2D);

    };

    class SortArea {
    public:
        //????
        struct Pair {
        int first; //id
        double second; //Area
        //ordino vettore di (id,Area) per area maggiore:
        //modo possibile
        //bool compareSecondComponent(const vector<int>& a, const vector<int>& b) {
        //return a[1] > b[1];
        };
        //sort(Aree.begin(), Aree.end(), compareSecondComponent);
        void SortedA(vector<Pair> Aree);
        //calcolo aree dei triangoli e salvo (id,Area)
        void AreaCalculator(vector<Pair> Aree, Data Input);
};

    class Adjacency {
    public:
        Adjacency(vector<SortArea::Pair> Aree, Data Edges, list<list<unsigned int>> AdjacencyList);
        list<list<unsigned int>>& GetAdjacencyList();
    };

}

#endif // __IMPORTAZIONE_H
