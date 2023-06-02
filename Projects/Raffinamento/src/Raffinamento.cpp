#include <Eigen/StdVector>
#include <iostream>
#include <fstream>
#include "Eigen/Eigen"
#include "Raffinamento.hpp"
#include "Point.hpp"
#include "Segment.hpp"

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
    vector<Point> *points = &Mesh.Points;
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
    Mesh.Segments.reserve(Mesh.NumberCell1D);
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

        Segment* s = new Segment(points,id,IdOrigin,IdEnd);
        Mesh.Segments.push_back(*s);
    }
}

void ImportMesh::Cell2D(TriangularMesh& Mesh)
{
    vector<Point> *points = &Mesh.Points;
    vector<Segment> *segments = &Mesh.Segments;

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

        array<unsigned int,3> Idvertices;
        array<unsigned int,3> Idedges;
        for (unsigned int i=0; i<3; i++) //contatore degli elementi del vettore interno
        {
            getline(rigaStream,row); //salva il 16 dentro row
            istringstream(row) >> Idvertices[i];
        };

        for (unsigned int i=0; i<3; i++) //contatore degli elementi del vettore interno
        {
            getline(rigaStream,row); //salva il 16 dentro row
            istringstream(row) >> Idedges[i];
        };

        Triangle* t = new Triangle(points, segments, Id,Idvertices,Idedges);
        Mesh.Triangles.push_back(*t);
        Mesh.OnOff.push_back(true);
    };
    //for(unsigned int i=0; i<80; i++){
    //    this->onOff.push_back(true);
    //}
}



Division::Division(Triangle& T):
    T(T)
{
    points = &Mesh.Points;
    segments = &Mesh.Segments;
    origin = T.longestEdge.origin;
    end = T.longestEdge.end;
    CoordinatesMidpoint = T.longestEdge.midPoint; //contiene le sue coordinate, dobbiamo creare l'id
    IdMidpoint = Mesh.Points.size() + 1;
    Midpoint = Point(IdMidpoint, CoordinatesMidpoint[0], CoordinatesMidpoint[1]); //ho creato il nuovo punto medio
    Mesh.Points.push_back(Midpoint);


    //cerco id del vertice opposto
    for (unsigned int i = 0; i<3; i++)
    {
        if (origin->Id != T.PointsTriangle[i].Id || end->Id != T.PointsTriangle[i].Id)
        {
            Opposite->Id = T.PointsTriangle[i].Id;
        }
        if (T.longestEdge.Id != T.SegmentsTriangle[i].Id) //se non è il lato che ho diviso in 2
        {
            if (origin->Id ==  T.SegmentsTriangle[i].end->Id)
            {
                IdLatoSx = T.SegmentsTriangle[i].Id;
                for(unsigned int k=0; k<3; k++)
                {
                    if (k != T.longestEdge.Id && k != i)
                    {
                        IdLatoDx = T.SegmentsTriangle[k].Id;
                    }
                }
            }
            else if (end->Id ==  T.SegmentsTriangle[i].origin->Id)
            {
                IdLatoDx = T.SegmentsTriangle[i].Id;
                for(unsigned int k=0; k<3; k++)
                {
                    if (k != i && T.longestEdge.Id != T.SegmentsTriangle[k].Id)
                    {
                        IdLatoSx = T.SegmentsTriangle[k].Id;

                    }
                }
            }
        }

    };

    //Spengo vecchio triangolo
    //Mesh.OnOff[T.Id] = false;


    //creo nuovi segmenti
    unsigned int NewIdS = Mesh.Segments.size()+1; //segmento che collega Midpoint e Opposte
    Segment* NewS = new Segment(points, NewIdS, Opposite->Id, Midpoint.Id);
    Mesh.Segments.push_back(*NewS);

    unsigned int NewIdSO = Mesh.Segments.size()+1; //segmento che collega Midpoint e origin del longestEdge
    Segment* NewSO = new Segment(points,NewIdSO,origin->Id, Midpoint.Id);
    Mesh.Segments.push_back(*NewSO);

    unsigned int NewIdSE = Mesh.Segments.size()+1; //segmento che collega Midpoint ed end del longestEdge
    Segment* NewSE = new Segment(points,NewIdSE,Midpoint.Id, end->Id);
    Mesh.Segments.push_back(*NewSE);


    //definisco nuovo triangolo T1
    //Mesh.OnOff.push_back(true);
    //unsigned int NewIdT1 = Mesh.OnOff.size();

    unsigned int NewIdT1 = Mesh.Triangles.size()+1;
    array<unsigned int, 3> verticesT1 = {origin->Id, Midpoint.Id, Opposite->Id};
    array<unsigned int, 3> edgesT1 = {NewS->Id, NewSO->Id, IdLatoSx};
    Triangle* T1 = new Triangle(points, segments, NewIdT1, verticesT1, edgesT1);
    Mesh.Triangles.push_back(*T1);

    //definisco nuovo triangolo T2
    //Mesh.OnOff.push_back(true);
    //unsigned int NewIdT2 = Mesh.OnOff.size();

    unsigned int NewIdT2 = Mesh.Triangles.size()+1;
    array<unsigned int, 3> verticesT2 = {Midpoint.Id, end->Id, Opposite->Id};
    array<unsigned int, 3> edgesT2 = {NewS->Id, NewSE->Id, IdLatoDx};
    Triangle* T2 = new Triangle(points, segments, NewIdT2, verticesT2, edgesT2);
    Mesh.Triangles.push_back(*T2);
}




} //fine namespace



