#ifndef __SORTING_H
#define __SORTING_H
#include <iostream>
#include "Eigen/Eigen"
#include <fstream>
#include <vector>
#include "Triangle.hpp"

using namespace std;
using namespace Eigen;
using namespace RaffinamentoLibrary;


namespace SortingLibrary{

    inline bool operator > (const Triangle & object1, const Triangle & object2)
    {return object1.Area > object2.Area;}

    inline bool operator < (const Triangle & object1, const Triangle & object2)
    {return object1.Area < object2.Area;}

    void Merge(vector<Triangle>& v, const unsigned int& sx,
               const unsigned int& cx, const unsigned int& dx){
        unsigned int k = 0;
        vector<Triangle> w;
        unsigned int i = sx;
        unsigned int j = cx+1;

        while ((i <= cx) && (j <= dx))
        {
            if (v[i] < v[j]) //se sto a sinistra della divisione, ordino la sinistra
            {
                //v.insert(v.begin() + k, valore);
                w.insert(w.begin() + k, v[i]);
                i = i+1;  //incremento sx = sx+1
            }
            else  //se sto a destra del vettore, ordino la destra
            {
                w.insert(w.begin() + k, v[j]);
                j = j+1; //incremento cx+1 = cx+1 +1 = cx+2
            }
            k=k+1;
        }

        for ( ; i <= cx; i = i+1, k = k+1)
            w.insert(w.begin() + k, v[i]);
        for ( ; j <= dx; j = j+1, k = k+1)
            w.insert(w.begin()+k, v[j]);
        //for (i = sx; i <= dx; i = i+1)
            //v[i] = w[i-sx];  !!!! Id è di tipo const, non posso modificarlo, devo usare un puntatore
        //Se l'assegnazione dell'oggetto Triangle è necessaria, potresti valutare l'utilizzo di
        //un'operazione di copia personalizzata o una soluzione alternativa come un riferimento o
        //un puntatore al Triangle originale invece di copiarlo direttamente.
    };

    vector<Triangle> MergeSort(vector<Triangle>& v, const unsigned int& sx, const unsigned int& dx)
    {
        unsigned int cx = 0;

        if(sx < dx)
        {
            cx = (sx+dx)/2;
            MergeSort(v, sx, cx);
            MergeSort(v, cx+1, dx);
            Merge(v, sx, cx, dx);
        }
        return v;
    }

}
#endif

