#ifndef __MESHUTILITIES_H
#define __MESHUTILITIES_H

#include <iostream>
#include "Eigen/Eigen"
#include <fstream>

using namespace Eigen;
using namespace std;
namespace MeshUtilitiesLibrary
{
    class Cell0D{
    public:
        void FindCoordinates(const Vector2d& Coordinates, unsigned int& punto, Vector2d pointCoordinates);
        //unsigned int NumberCell0D;
        //vector<Vector2d> Coordinates0D;

        //Cell0D(unsigned int& NumberCell0D, vector<Vector2d>& Coordinates0D);
        //void CoordinateLato(Vector2d& Coordinates0D, );

    };

    class Cell1D{
    public:
        void LengthEdge(const array<unsigned int, 2>& originEnd, const vector<Vector2d>& Coordinates, unsigned int &LengthEdge);

        //Cell1D(unsigned int& NumberCell1D, vector<vector<unsigned int>>& OriginEnd1D);

        //calcolo lunghezza dei lati
        //void LengthEdges(const vector<vector<unsigned int>>& OriginEnd1D, const vector<Vector2d>& Coordinates0D, VectorXd& LengthEdge);
    };

    class Cell2D{

    public:
        unsigned int LongestEdge;
        double Area;
//calcolo lato più lungo di ogni triangolo. Prendendo da cell2D prendiamo i lati, da cell1d prendiamo origin end e infine da cell0d prendiamo le coordinate
//calcolo la norma di ogni lato e ne prendo il massimo. Restituisce un vettore dove alla posizione corrispondente all'id del triangolo troviamo l'id del lato più grande
        //void FindLongestEdge(const vector<vector<unsigned int>>& OriginEnd1D, VectorXd& LengthEdge, const vector<vector<unsigned int>>& Edges2D, vector<unsigned int>& LongestEdge);
        void FindLongestEdge(VectorXd& LengthEdges, const array<unsigned int, 3>& edges, unsigned int& LongestEdge);

//calcolo area
        //void AreaCalculator(const vector<Vector2d>& Coordinates0D, const vector<vector<unsigned int>>& Vertices2D, vector<double>& Aree );
        void AreaCalculator(const Vector2d& Coordinates0D, const vector<unsigned int>& vertices, double Area);


//imposto tutti i triangoli come true
        array<bool, 186> onOff= {true};

    };

    class SortArea {

    public:

        const unsigned int theta;

        struct Pair {
        int first; //id
        double second; //Area
        //ordino vettore di (id,Area) per area maggiore:
        //modo possibile
        //bool compareSecondComponent(const vector<int>& a, const vector<int>& b) {
        //return a[1] > b[1];
        };

        //sort(Aree.begin(), Aree.end(), compareSecondComponent);
        //dentro SortedA c'è l'algoritmo di sorting
        SortArea(vector<double>& Aree, vector<Pair>& SortedA, const unsigned int& theta);

    };

}

#endif // __IMPORTAZIONE_H
