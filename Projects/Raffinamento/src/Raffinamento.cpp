#include <Eigen/StdVector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "Eigen/Eigen"
#include "Raffinamento.hpp"
#include "Point.hpp"
#include "Segment.hpp"

namespace RaffinamentoLibrary
{


void ImportMesh::Cell0D(TriangularMesh& Mesh)
{
    ifstream file;
    file.open("./Dataset/Test2/Cell0Ds.csv");
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
    file.open("./Dataset/Test2/Cell1Ds.csv");

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

        Point origin = Mesh.Points[IdOrigin];
        Point end = Mesh.Points[IdEnd];
        Segment* s = new Segment(id,origin,end);
        Mesh.Segments.push_back(*s);
    }
}

void ImportMesh::Cell2D(TriangularMesh& Mesh)
{
    ifstream file;
    file.open("./Dataset/Cell2Ds.csv");
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

        unsigned int IdVertix;
        unsigned int IdEdge;
        array<Point,3> vertices;
        array<Segment,3> edges;
        for (unsigned int i=0; i<3; i++) //contatore degli elementi del vettore interno
        {
            getline(rigaStream,row); //salva il 16 dentro row
            istringstream(row) >> IdVertix;
            vertices[i] = Mesh.Points[IdVertix];
        };

        for (unsigned int i=0; i<3; i++) //contatore degli elementi del vettore interno
        {
            getline(rigaStream,row); //salva il 16 dentro row
            istringstream(row) >> IdEdge;
            edges[i] = Mesh.Segments[IdEdge];
        };

        Triangle* t = new Triangle(Id,vertices,edges);
        Mesh.Triangles.push_back(*t);
        Mesh.OnOff.push_back(true);
    };
    //for(unsigned int i=0; i<80; i++){
    //    this->onOff.push_back(true);
    //}
}


array<Triangle,2> Division(Triangle& T, Segment & segment)
{
    TriangularMesh Mesh;
    Point origin = segment.origin;
    Point end = segment.end;
    array<double, 2> CoordinatesMidpoint = segment.midPoint; //contiene le sue coordinate, dobbiamo creare l'id
    unsigned int IdMidpoint = Mesh.Points.size() + 1;
    Point Opposite;
    unsigned int IdLatoSx;
    unsigned int IdLatoDx;

    Point Midpoint = Point(IdMidpoint, CoordinatesMidpoint[0], CoordinatesMidpoint[1]); //ho creato il nuovo punto medio
    Mesh.Points.push_back(Midpoint);

    //cerco id del vertice opposto
    for (unsigned int i = 0; i<3; i++)
    {
        if (origin.Id != T.pointsTriangle[i].Id || end.Id != T.pointsTriangle[i].Id)
        {
            Opposite.Id = T.pointsTriangle[i].Id;
        }
        if (segment.Id != T.segmentsTriangle[i].Id) //se non è il lato che ho diviso in 2
        {
            if (origin.Id ==  T.segmentsTriangle[i].end.Id)
            {
                IdLatoSx = T.segmentsTriangle[i].Id;
                for(unsigned int k=0; k<3; k++)
                {
                    if (k != segment.Id && k != i)
                    {
                        IdLatoDx = T.segmentsTriangle[k].Id;
                    }
                }
            }
            else if (end.Id ==  T.segmentsTriangle[i].origin.Id)
            {
                IdLatoDx = T.segmentsTriangle[i].Id;
                for(unsigned int k=0; k<3; k++)
                {
                    if (k != i && segment.Id != T.segmentsTriangle[k].Id)
                    {
                        IdLatoSx = T.segmentsTriangle[k].Id;

                    }
                }
            }
        }

    };

    //Spengo vecchio triangolo
    //Mesh.OnOff[T.Id] = false;


    //creo nuovi segmenti ???faccio metodo "CreationSegment"
    unsigned int NewIdS = Mesh.Segments.size()+1; //segmento che collega Midpoint e Opposte
    Segment NewS = Segment(NewIdS, Opposite, Midpoint);
    Mesh.Segments.push_back(NewS);

    unsigned int NewIdSO = Mesh.Segments.size()+1; //segmento che collega Midpoint e origin del longestEdge
    Segment NewSO = Segment(NewIdSO, origin, Midpoint);
    Mesh.Segments.push_back(NewSO);

    unsigned int NewIdSE = Mesh.Segments.size()+1; //segmento che collega Midpoint ed end del longestEdge
    Segment NewSE = Segment(NewIdSE,Midpoint, end);
    Mesh.Segments.push_back(NewSE);


    //definisco nuovo triangolo T1
    //Mesh.OnOff.push_back(true);
    //unsigned int NewIdT1 = Mesh.OnOff.size();

    //creo nuovi triangoli ???faccio metodo "CreationTriangle"
    unsigned int NewIdT1 = Mesh.Triangles.size()+1;
    Segment latoSx = Mesh.Segments[IdLatoSx];
    array<Point,3> verticesT1 = {origin, Midpoint, Opposite};
    array<Segment, 3> edgesT1 = {NewS, NewSO, latoSx};
    Triangle newT1 = Triangle(NewIdT1, verticesT1, edgesT1);
    Mesh.Triangles.push_back(newT1);

    //definisco nuovo triangolo T2
    //Mesh.OnOff.push_back(true);
    //unsigned int NewIdT2 = Mesh.OnOff.size();

    unsigned int NewIdT2 = Mesh.Triangles.size()+1;
    Segment latoDx = Mesh.Segments[IdLatoDx];
    array<Point,3> verticesT2 = {Midpoint, end, Opposite};
    array<Segment, 3> edgesT2 = {NewS, NewSE, latoDx};
    Triangle newT2 = Triangle(NewIdT2, verticesT2, edgesT2);
    Mesh.Triangles.push_back(newT2);

    return {newT1, newT2};
}

Raffinamento::Raffinamento(const unsigned int maxIterator, vector<Triangle> SortedA){

    for (unsigned int i=0; i<maxIterator; i++){
        Triangle T = SortedA[i];
        array<Triangle, 2> newTriangles = Division(T, T.longestEdge);
        Triangle newT1 = newTriangles[0];
        Triangle newT2 = newTriangles[1];
        Mesh.OnOff[T.Id] = "false";

        Mesh.OnOff.push_back(true);
        Mesh.OnOff.push_back(true);


        //se T è il getT1 di LongestEdge:
        if (*T.longestEdge.getT1() == T && Mesh.OnOff[(*T.longestEdge.getT2()).Id] == true)
            //fai division su getT2 (triangolo adiacente a T)
        {
            Triangle Ta = *T.longestEdge.getT2();
            array<Triangle, 2> newTrianglesA =Division(Ta, T.longestEdge);
            Triangle newT1A = newTrianglesA[0];
            Triangle newT2A = newTrianglesA[1];
            Mesh.OnOff[Ta.Id] = "false";
            Mesh.OnOff.push_back(true);
            Mesh.OnOff.push_back(true);

        }

        else if (*T.longestEdge.getT2() == T)
        {
            Triangle Ta = *T.longestEdge.getT1();
            array<Triangle, 2> newTrianglesA =Division(Ta, T.longestEdge);
            Triangle newT1A = newTrianglesA[0];
            Triangle newT2A = newTrianglesA[1];
            Mesh.OnOff[Ta.Id] = "false";
            Mesh.OnOff.push_back(true);
            Mesh.OnOff.push_back(true);

        }

    }
}



} //fine namespace



