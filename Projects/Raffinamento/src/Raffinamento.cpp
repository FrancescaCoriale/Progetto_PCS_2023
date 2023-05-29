#include <Eigen/StdVector>
#include <iostream>
#include <fstream>
#include "Eigen/Eigen"
#include "Raffinamento.hpp"
#include "Point.hpp"
#include "Segment.hpp"
#include "Sorting.hpp"
//#include "map"

using namespace SortLibrary;

namespace RaffinamentoLibrary
{


void ImportMesh::Cell0D(TriangularMesh& Mesh)
{
    ifstream file;
    file.open("C:/Users/annam/Desktop/Progetto_PCS_2023/Projects/Raffinamento/Dataset/Test2/Cell0Ds.csv");
    if (file.fail())
    {
        cerr<<"errore nell'apertura del file Cell0D"<<endl;
    }

    string line;
    list<string> listLines;
    while (getline(file,line))
        listLines.push_back(line);

    file.close();

    listLines.pop_front(); //elimino dalla lista la prima riga
    Mesh.NumberCell0D = listLines.size();
    if (Mesh.NumberCell0D == 0)
    {   cout<<"nessuna cella disponibile"<<endl;
    }

    Mesh.Points.resize(Mesh.NumberCell0D);
    string row;

    for (string& riga : listLines) //for (tipo del contatore uguale a line : lista da cui prendo line)
    {
        istringstream rigaStream (riga); //prendo stringa da listLines, lo converto in stream
        unsigned int Id;
        getline(rigaStream,row);
        istringstream(row) >> Id;
        getline(rigaStream,row);

        double x;
        getline(rigaStream,row) ;
        istringstream(row) >> x;

        double y;
        getline(rigaStream,row) ;
        istringstream(row) >> y;

        Point* p = new Point(Id,x,y);
        Mesh.Points.push_back(*p);
    }
}

void ImportMesh::Cell1D(TriangularMesh& Mesh)
{
    ifstream file;
    file.open("C:/Users/annam/Desktop/Progetto_PCS_2023/Projects/Raffinamento/Dataset/Test2/Cell1Ds.csv");

    if(file.fail())
    {
        cerr<<"errore nell'apertura del file Cell0D"<<endl;
    }

    list<string> listLines;
    string line;
    while (getline(file, line))
        listLines.push_back(line);

    listLines.pop_front();

    Mesh.NumberCell1D = listLines.size();
    if (Mesh.NumberCell1D == 0)
    {
        cerr << "There is no cell 1D" << endl;
    }
    Mesh.Segments.resize(Mesh.NumberCell1D);
    string row;
    for (string& riga : listLines) //for (tipo del contatore uguale a line : lista da cui prendo line)
    {
        istringstream rigaStream (riga); //prendo stringa da listLines, lo converto in stream
        getline(rigaStream,row) ; //prendo porzione di rigaStream fino a ;
        unsigned int id;
        istringstream (row) >> id; //dentro id ho il valore in intero

        getline(rigaStream,row) ; //prendo porzione di rigaStream fino a ;

        unsigned int IdOrigin;
        getline(rigaStream,row) ;
        istringstream(row) >> IdOrigin;

        unsigned int IdEnd;
        getline(rigaStream,row) ;
        istringstream(row) >> IdEnd;

        Segment* s = new Segment(id,IdOrigin,IdEnd);
        Mesh.Segments.push_back(*s);
    }
}

void ImportMesh::Cell2D(TriangularMesh& Mesh)
{
    ifstream file;
    file.open("./Cell2Ds.csv");
    if (file.fail())
    {
        cout<<"errore nell'apertura del file Cell2D"<<endl;
    };
    string line;
    list<string> listLines;
    while (getline(file,line))
        listLines.push_back(line);

    file.close();

    listLines.pop_front(); //elimino dalla lista la prima riga
    Mesh.NumberCell2D = listLines.size();
    if (Mesh.NumberCell2D == 0)
    {
        cout<<"nessuna cella 2D disponibile"<<endl;

    };

    string row;
    for (string& riga : listLines) //for (tipo del contatore uguale a line : lista da cui prendo line)
    {
        istringstream rigaStream (riga); //prendo stringa da listLines, lo converto in stream

        getline(rigaStream,row) ; //MEMORIZZO GLI ID
        unsigned int Id;
        istringstream (row) >> Id;

        array<unsigned int,3> vertices;
        array<unsigned int,3> edges;
        for (unsigned int i=0; i<3; i++) //contatore degli elementi del vettore interno
        {
            getline(rigaStream,row); //salva il 16 dentro row
            istringstream(row) >> vertices[i];
        };

        for (unsigned int i=0; i<3; i++) //contatore degli elementi del vettore interno
        {
            getline(rigaStream,row); //salva il 16 dentro row
            istringstream(row) >> edges[i];
        };

        Triangle* t = new Triangle(Id,vertices,edges);
        Mesh.Triangles.push_back(*t);
    };
    //for(unsigned int i=0; i<80; i++){
    //    this->onOff.push_back(true);
    //}
}

SortedArea::SortedArea(vector<double>& Aree, unsigned int& theta) {
    vector<double> SortedA = MergeSort(Aree, 0, Aree.size()-1);
    SortedA.resize(theta);
}

Division::Division(Triangle& T){
     //origin = T.longestEdge.origin;
     //end = T.longestEdge.end;
    Point origin = T.longestEdge.origin;
    Point end = T.longestEdge.end;
    array<double,2> CoordinatesMidpoint = T.longestEdge.midPoint; //contiene le sue coordinate, dobbiamo creare l'id
    unsigned int IdMidpoint = Mesh.NumberCell0D;
    Point Midpoint = Point(IdMidpoint, CoordinatesMidpoint[0], CoordinatesMidpoint[1]); //ho creato il nuovo punto medio
    Point Opposite;

    //cerco id del vertice opposto
    for (unsigned int i = 0; i<3; i++)
    {
        if (origin.Id != T.vertices[i] || end.Id != T.vertices[i])
           {
            Opposite.Id = T.vertices[i];
            }
        if (T.longestEdge.Id != T.edges[i]) //se non è il lato che ho diviso in 2
        {
           // if (origin.Id =  )
            {
                for(unsigned int k=0; k<3; k++)
                {
                    if (k != i && T.longestEdge.Id != T.edges[k])
                    {
                        unsigned int IdLatoSx = T.edges[i];
                        unsigned int IdLatoDx = T.edges[k];
                    }
                }

            }
            //else
            {
                for(unsigned int k=0; k<3; k++)
                {
                    if (k != i && T.longestEdge.Id != T.edges[k])
                    {
                        unsigned int IdLatoSx = T.edges[k];
                        unsigned int IdLatoDx = T.edges[i];
                    }
                }
            }
        }

    };

    unsigned int NewId;
    Segment* NewS = new Segment(NewId,Opposite, Midpoint);
    Segment* NewSO = new Segment(NewId,origin, Midpoint);
    Segment* NewSE = new Segment(NewId,Midpoint, end);
    unsigned int NewT1Id;
    unsigned int NewT2Id;
    array<unsigned int, 3> vertices1 = {origin.Id, Midpoint.Id, Opposite.Id};
    array<unsigned int, 3> vertices2 = {Midpoint.Id, end.Id, Opposite.Id};
    array<unsigned int, 3> edges1 = {NewS->Id, NewSO->Id,  };
    array<unsigned int, 3> edges2 = {NewS->Id, NewSE->Id, };
}






}



