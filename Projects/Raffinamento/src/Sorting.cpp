<<<<<<< Updated upstream
#ifndef __SORTING_H
#define __SORTING_H
#include <iostream>
#include "Eigen/Eigen"
#include <fstream>
#include <vector>
#include "Raffinamento.hpp"
#include "Triangle.hpp"
#include "Sorting.hpp"

using namespace std;
using namespace Eigen;
using namespace RaffinamentoLibrary;

namespace SortLibrary{

    //nel merge faccio la fusione
    void MergeSort::Merge(vector<Triangle>& v, const unsigned int& sx,
               const unsigned int& cx, const unsigned int& dx)
    {
        unsigned int k = 0;
        vector<Triangle> w;
        unsigned int i = sx;
        unsigned int j = cx+1;

        while ((i <= cx) && (j <= dx))
        {
            if (v[i].Area <= v[j].Area) //se sto a sinistra della divisione, ordino la sinistra
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
    }

    //nel mergeSort divido per 2 il vettore
    MergeSort::MergeSort(vector<Triangle>& v,
                   const unsigned int& sx,
                   const unsigned int& dx):
    v(v), sx(sx), dx(dx)
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



} //fine namespace
#endif
=======
>>>>>>> Stashed changes
