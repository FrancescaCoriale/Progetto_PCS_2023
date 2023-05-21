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
        friend class Cell1D;
        friend class Cell2D;
        int ciao;

    };

    class Cell1D{

    public:

        unsigned int NumberCell1D;
        vector<vector<unsigned int>> OriginEnd1D;
        VectorXd LengthEdge;

        Cell1D(unsigned int& NumberCell1D, vector<vector<unsigned int>>& OriginEnd1D);

        //calcolo lunghezza dei lati
        void LengthEdges(const vector<vector<unsigned int>>& OriginEnd1D, const vector<Vector2d>& Coordinates0D, VectorXd& LengthEdge);

    };

    class Cell2D{

    public:
        unsigned int NumberCell2D;
        vector<vector<unsigned int>> Vertices2D;
        vector<vector<unsigned int>> Edges2D;
        vector<unsigned int> LongestEdge; //i-esimo elemento è id del lato più lungo dell'iesimo triangolo
        list<list<unsigned int>> AdjacencyList;
        vector<double> Aree;
        Cell2D(unsigned int& NumberCell2D, vector<vector<unsigned int>>& Vertices2D, vector<vector<unsigned int>>& Edges2D);

//calcolo lato più lungo di ogni triangolo. Prendendo da cell2D prendiamo i lati, da cell1d prendiamo origin end e infine da cell0d prendiamo le coordinate
//calcolo la norma di ogni lato e ne prendo il massimo. Restituisce un vettore dove alla posizione corrispondente all'id del triangolo troviamo l'id del lato più grande
        void FindLongestEdge(const vector<vector<unsigned int>>& OriginEnd1D, VectorXd& LengthEdge, const vector<vector<unsigned int>>& Edges2D, vector<unsigned int>& LongestEdge);

//calcolo area
        void AreaCalculator(const vector<Vector2d>& Coordinates0D, const vector<vector<unsigned int>>& Vertices2D, vector<double>& Aree );

//adiacenza: lista di liste: id triangolo è la posizione nel vettore esterno, id triangoli adiacenti sono i valori e id del lato confinante nel vettore interno
        void Adjacency(list<list<unsigned int>>& AdjacencyList, const vector<vector<unsigned int>>& Edges2D);

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
