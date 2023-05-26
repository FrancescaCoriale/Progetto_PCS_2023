#ifndef __SORTING_H
#define __SORTING_H
#include <iostream>
#include "Eigen/Eigen"
#include <fstream>

using namespace std;
using namespace Eigen;

namespace RaffinamentoLibrary{


    template<typename T>
    //nel merge faccio la fusione
    void Merge(vector<T>& v,
               const unsigned int& sx,
               const unsigned int& cx,
               const unsigned int& dx)
    {
        unsigned int k = 0;
        vector<T> w;
        unsigned int i = sx;
        unsigned int j = cx+1;

        while ((i <= j-1) && (j <= dx))
        {
            if (v[i] <= v[j]) //se sto a sinistra della divisione, ordino la sinistra
            {
                w[k] = v[i];
                i = i+1;  //incremento sx = sx+1
            }
            else  //se sto a destra del vettore, ordino la destra
            {
                w[k] = v[j];
                j = j+1; //incremento cx+1 = cx+1 +1 = cx+2
            }
            k=k+1;
        }

        for ( ; i <= cx; i = i+1, k = k+1)
            w[k] = v[i];
        for ( ; j <= dx; j = j+1, k = k+1)
            w[k] = v[j];
        for (i = sx; i <= dx; i = i+1)
            v[i] = w[i-sx];

    }

    template<typename T>
    //nel mergeSort divido per 2 il vettore
    void MergeSort(vector<T>& v,
                   const unsigned int& sx,
                   const unsigned int& dx)
    {
        unsigned int cx = 0;

        if(sx < dx)
        {
            cx = (sx+dx)/2;
            MergeSort(v, sx, cx);
            MergeSort(v, cx+1, dx);
            Merge(v, sx, cx, dx);
        }
    }

}
#endif
