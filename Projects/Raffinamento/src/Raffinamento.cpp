#include <Eigen/StdVector>
#include <iostream>
#include <fstream>
#include "Eigen/Eigen"
#include "MeshUtilities.hpp"
#include "Raffinamento.hpp"
#include "Point.hpp"
#include "Segment.hpp"
//#include "map"



namespace RaffinamentoLibrary
{

void Cell0D(TriangularMesh& Mesh)
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
    unsigned int Id;
    double x;
    double y;
    for (string& riga : listLines) //for (tipo del contatore uguale a line : lista da cui prendo line)
    {
        istringstream rigaStream (riga); //prendo stringa da listLines, lo converto in stream
        getline(rigaStream,row);
        istringstream(row) >> Id;
        getline(rigaStream,row);

        getline(rigaStream,row) ;
        istringstream(row) >> x;
        getline(rigaStream,row) ;
        istringstream(row) >> y;

        Point* p = new Point(Id,x,y);
        Mesh.Points.push_back(*p);
    }
}

void Cell1D(TriangularMesh& Mesh)
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
    unsigned int IdOrigin;
    unsigned int IdEnd;
    for (string& riga : listLines) //for (tipo del contatore uguale a line : lista da cui prendo line)
    {
        istringstream rigaStream (riga); //prendo stringa da listLines, lo converto in stream
        getline(rigaStream,row) ; //prendo porzione di rigaStream fino a ;
        unsigned int id;
        istringstream (row) >> id; //dentro id ho il valore in intero

        getline(rigaStream,row) ; //prendo porzione di rigaStream fino a ;
        getline(rigaStream,row) ;
        istringstream(row) >> IdOrigin;
        getline(rigaStream,row) ;
        istringstream(row) >> IdEnd;

        Segment* s = new Segment(IdOrigin,IdEnd);
        Mesh.Segments.push_back(*s);
    }
}




}
