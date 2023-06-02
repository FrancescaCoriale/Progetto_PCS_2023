#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Eigen/Eigen"
#include "Raffinamento.hpp"
#include "Point.hpp"
#include "Segment.hpp"
#include "Triangle.hpp"
#include "Sorting.hpp"

using namespace std;
using namespace Eigen;
using namespace RaffinamentoLibrary;
using namespace SortingLibrary;

int main(/*int argc, char *argv[]*/)
{
    TriangularMesh Mesh;

    //string Theta = argv[1];
    //unsigned int theta = stoi(Theta);
    unsigned int theta = 10;
    vector<Triangle> SortedA = MergeSort(Mesh.Triangles, 0, Mesh.Triangles.size()-1);
    SortedA.resize(theta);
    unsigned int maxIterator = SortedA.size();


    for (unsigned int i=0; i<maxIterator; i++)
    {
        Triangle T = SortedA[i];
        Division(&T);
        Mesh.OnOff[T.Id] = "false";
        Mesh.OnOff.push_back(true);
        Mesh.OnOff.push_back(true);
        //se T è il getT1 di LongestEdge:
        if (*T.longestEdge.getT1 == T)
            //fai division su getT2 (triangolo adiacente a T)
        {
            Triangle T2 = *getT2;
            Division(&T2);
            Mesh.OnOff[T2.Id] = "false";
            Mesh.OnOff.push_back(true);
            Mesh.OnOff.push_back(true);
            //se i due mega triangoli condividono lo stesso longestEdge
            if(T.longestEdge == T2.longestEdge)
                //fai stop: perchè ho già diviso T2 e la condizione di raffinamento è soddisfatta
            {
                break;
            }
            else
            {
                //division sul triangolino nuovo di T2 che condivide longestedge di T
                if(T.longestEdge == Division.newT1->longestEdge)
                {
                    Division(newT1);
                }
                else
                {
                    Division(newT2);
                }

            }

        }
        else
        {
            Triangle T1 = *getT1;
            Division(&T1);
            Mesh.OnOff[T1.Id] = "false";
            Mesh.OnOff.push_back(true);
            Mesh.OnOff.push_back(true);
            //se i due mega triangoli condividono lo stesso longestEdge
            if(T.longestEdge == T1.longestEdge)
                //fai stop: perchè ho già diviso T2 e la condizione di raffinamento è soddisfatta
            {
                break;
            }
            else
            {
                //division sul triangolino nuovo di T2 che condivide longestedge di T
                if(T.longestEdge == Division.newT1->longestEdge)
                {
                    Division(newT1);
                }
                else
                {
                    Division(newT2);
                }

            }

        }

    }
    cout << OnOff << endl;

  return 0;
}
