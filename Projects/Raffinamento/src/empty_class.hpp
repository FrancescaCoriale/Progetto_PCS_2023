#ifndef __EMPTY_H
#define __EMPTY_H

#include <iostream>

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
        SortedArea(vector<Pair> Aree);
    public:
        //calcolo aree dei triangoli e salvo (id,Area)
        AreaCalculator(vector<Pair> Aree, Data Input);
    };
  };

  class Adjacency {
    public:
        Adjacency(vector<unsigned int> SortedA, Data Edges, list<list<unsigned int>> AdjacencyList);

  };
}

#endif // __EMPTY_H
