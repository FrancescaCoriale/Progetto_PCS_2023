#ifndef __EMPTY_H
#define __EMPTY_H

#include <iostream>
#include "Eigen/Eigen"
#include <fstream>
#include "map"

using namespace Eigen;
using namespace std;
namespace ProjectLibrary
{

  class Data {
    private:

    public:
        void Show() const { std::cout<< "Hello world;"<< std::endl; }
  };

  class SortArea {
    private:
      //????
        struct Pair {
            int first; //id
            double second; //Area
        //ordino vettore di (id,Area) per area maggiore:
            //modo possibile
            //bool compareSecondComponent(const vector<int>& a, const vector<int>& b) {
            //return a[1] > b[1];
            //}
            //sort(Aree.begin(), Aree.end(), compareSecondComponent);
        void SortedArea(vector<Pair> Aree);
    public:
        //calcolo aree dei triangoli e salvo (id,Area)
        void AreaCalculator(vector<Pair> Aree, Data Input);
    };
  };

  class Adjacency {
    public:
        Adjacency(vector<unsigned int> SortedA, Data Edges, list<list<unsigned int>> AdjacencyList);
    };

  class ImportData{
  private:
      unsigned int NumberCell0D;
      unsigned int NumberCell1D;
      unsigned int NumberCell2D;

  protected:
      map<unsigned int, Vector2d> Coordinates0D;
      map<unsigned int, Vector2d> OriginEnd1D;
      map<unsigned int, vector<int>> Vertices2D;
      map<unsigned int, vector<int>> Edges2D;

  public:
      ImportData() = default;
      ImportData(int& NumberCell, map<unsigned int, Vector2d>& Map){}; //unico costruttore per le due mappe
      ImportData(int& NumberCell0D, map<unsigned int, vector<int>>& Vertices2D, map<unsigned int, vector<int>>& Edges2D){};
      map<unsigned int, Vector2d> GetCoordinates0D();
      map<unsigned int, Vector2d> GetOriginEdn1D();
      map<unsigned int, vector<int>> GetVertices2D();
      const map<unsigned int, vector<int>>& GetEdges2D();
  };
}

#endif // __EMPTY_H
