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


void ImportMesh::Cell0D(TriangularMesh& Mesh, string & directory)
{
    ifstream file;
    string filePath = directory + "/Cell0Ds.csv";
    file.open(filePath);
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

    cout << "lettura celle 0D fatta"<<endl;
}

void ImportMesh::Cell1D(TriangularMesh& Mesh, string & directory)
{
    ifstream file;
    string filePath = directory + "/Cell1Ds.csv";
    file.open(filePath);


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
    cout << "lettura celle 1D fatta"<<endl;



}

void ImportMesh::Cell2D(TriangularMesh& Mesh, string & directory)
{
    ifstream file;
    string filePath = directory + "/Cell2Ds.csv";
    file.open(filePath);

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

    cout << "lettura celle 2D fatta"<<endl;
    for (unsigned int i = 0; i < 186; i++)
    {
        cout<< Mesh.OnOff[i];
    }
}


array<Triangle,2>TriangularMesh::Division(unsigned int &NumberCell0D, unsigned int &NumberCell1D, unsigned int &NumberCell2D,
              Triangle &T, Segment &segment)

{
    Point origin = segment.origin;
    Point end = segment.end;
    array<double, 2> CoordinatesMidpoint = segment.midPoint; //contiene le sue coordinate, dobbiamo creare l'id
    unsigned int IdMidpoint = NumberCell0D;
    Point Opposite;
    Segment LatoSx;
    Segment LatoDx;

    Point Midpoint(IdMidpoint, CoordinatesMidpoint[0], CoordinatesMidpoint[1]); //ho creato il nuovo punto medio
    Points.push_back(Midpoint);


    //cerco id del vertice opposto
    for (unsigned int i = 0; i<3; i++)
    {
        if ((origin.Id != T.pointsTriangle[i].Id) && (end.Id != T.pointsTriangle[i].Id))
        {
            Opposite = T.pointsTriangle[i];
        }
        if (segment.Id != T.segmentsTriangle[i].Id) //se non è il lato che ho diviso in 2
        {
            if (origin.Id ==  T.segmentsTriangle[i].end.Id)
            {
                LatoSx = T.segmentsTriangle[i];
                for(unsigned int k=0; k<3; k++)
                {
                    if (k != segment.Id && k != i)
                    {
                        LatoDx = T.segmentsTriangle[k];
                    }
                }
            }
            else if (end.Id ==  T.segmentsTriangle[i].origin.Id)
            {
                LatoDx = T.segmentsTriangle[i];
                for(unsigned int k=0; k<3; k++)
                {
                    if (k != i && segment.Id != k)
                    {
                        LatoSx = T.segmentsTriangle[k];

                    }
                }
            }
        }

    };

    //Spengo vecchio triangolo
    //Mesh.OnOff[T.Id] = false;


    //creo nuovi segmenti ???faccio metodo "CreationSegment"

    unsigned int NewIdS = NumberCell1D; //segmento che collega Midpoint e Opposte
    Segment NewS(NewIdS, Opposite, Midpoint);
    Segments.push_back(NewS);
    NumberCell1D +=1;
    unsigned int NewIdSO = NumberCell1D; //segmento che collega Midpoint e origin del longestEdge
    Segment NewSO(NewIdSO, origin, Midpoint);
    Segments.push_back(NewSO);
    NumberCell1D +=1;
    unsigned int NewIdSE = NumberCell1D; //segmento che collega Midpoint ed end del longestEdge
    Segment NewSE(NewIdSE,Midpoint, end);
    Segments.push_back(NewSE);
    NumberCell1D +=1;





    //definisco nuovo triangolo T1
    //Mesh.OnOff.push_back(true);
    //unsigned int NewIdT1 = Mesh.OnOff.size();

    //creo nuovi triangoli ???faccio metodo "CreationTriangle"

    unsigned int NewIdT1 = NumberCell2D;
    array<Point,3> verticesT1 = {origin, Midpoint, Opposite};
    array<Segment, 3> edgesT1 = {NewS, NewSO, LatoSx};
    Triangle newT1(NewIdT1, verticesT1, edgesT1);


    //definisco nuovo triangolo T2
    //Mesh.OnOff.push_back(true);
    //unsigned int NewIdT2 = Mesh.OnOff.size();
    NumberCell2D +=1;
    unsigned int NewIdT2 = NumberCell2D;
    array<Point,3> verticesT2 = {Midpoint, end, Opposite};
    array<Segment, 3> edgesT2 = {NewS, NewSE, LatoDx};
    Triangle newT2(NewIdT2, verticesT2, edgesT2);

    cout<<"Abbiamo diviso il triangolo numero " << T.Id<<endl;
    return {newT1, newT2};
}

Raffinamento::Raffinamento(TriangularMesh &Mesh, const unsigned int maxIterator, vector<Triangle> SortedA){

    for (unsigned int i=0; i<maxIterator; i++){
        Triangle T = SortedA[i];
        array<Triangle,2> NewTriangles = Mesh.Division(Mesh.NumberCell0D, Mesh.NumberCell1D,
                                  Mesh.NumberCell2D, T, T.longestEdge);
        //Point Midpoint = divisionElements.Midpoint;

        //Segment NewS = divisionElements.NewS;
        //Segment NewSO = divisionElements.NewSO;
        //Segment NewSE = divisionElements.NewSE;


        Triangle newT1 = NewTriangles[0];
        Triangle newT2 = NewTriangles[1];
        Mesh.Triangles.push_back(newT1);
        Mesh.Triangles.push_back(newT2);

        Mesh.OnOff.assign(T.Id, false);
        Mesh.OnOff.push_back(true);
        Mesh.OnOff.push_back(true);

        cout << "abbiamo diviso il triangolo T"<<endl;


        //se T è il getT1 di LongestEdge:
        if (*(T.longestEdge.getT1()) == T && Mesh.OnOff[(*(T.longestEdge.getT2())).Id] == true)
            //fai division su getT2 (triangolo adiacente a T)
        {
            Triangle Ta = *(T.longestEdge.getT2());
            cout<<"adiacente di "<< T.Id << "è " << Ta.Id<<endl;

            array<Triangle,2> NewTriangles = Mesh.Division(Mesh.NumberCell0D, Mesh.NumberCell1D,
                                              Mesh.NumberCell2D, T, T.longestEdge);

            Triangle newT1A = NewTriangles[0];
            Triangle newT2A = NewTriangles[1];

            Mesh.Triangles.push_back(newT1A);
            Mesh.Triangles.push_back(newT2A);
            Mesh.OnOff.assign(Ta.Id, false);
            Mesh.OnOff.push_back(true);
            Mesh.OnOff.push_back(true);

            cout << "abbiamo diviso Ta"<<endl;

        }

        else if (*(T.longestEdge.getT2()) == T && Mesh.OnOff[(*(T.longestEdge.getT1())).Id] == true)
        {
            Triangle Ta = *(T.longestEdge.getT1());
            cout<<"adiacente di "<< T.Id << "è " << Ta.Id<<endl;
            array<Triangle,2> NewTriangles = Mesh.Division(Mesh.NumberCell0D, Mesh.NumberCell1D,
                                              Mesh.NumberCell2D, T, T.longestEdge);

            Triangle newT1A = NewTriangles[0];
            Triangle newT2A = NewTriangles[1];

            Mesh.Triangles.push_back(newT1A);
            Mesh.Triangles.push_back(newT2A);
            Mesh.OnOff.assign(Ta.Id, false);
            Mesh.OnOff.push_back(true);
            Mesh.OnOff.push_back(true);

        }

    }
}



} //fine namespace



