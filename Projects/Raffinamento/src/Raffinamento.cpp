#include <Eigen/StdVector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "Eigen/Eigen"
#include "Raffinamento.hpp"
#include "Point.hpp"
#include "Segment.hpp"

using namespace std;

namespace RaffinamentoLibrary
{


ImportMesh::ImportMesh(TriangularMesh& Mesh, string & directory)
{
    /// file 0D

    ifstream file0D;

    string filePath0D = directory + "/Cell0Ds.csv";
    file0D.open(filePath0D);

    if (file0D.fail())

    {
        cerr<<"errore nell'apertura del file Cell0D"<<endl;
    }

    string line0D;
    list<string> listLines0D;
    while (getline(file0D,line0D))
        listLines0D.push_back(line0D);

    file0D.close();

    listLines0D.pop_front(); //elimino dalla lista la prima riga
    Mesh.NumberCell0D = listLines0D.size();
    if (Mesh.NumberCell0D == 0)
    {   cout<<"nessuna cella disponibile"<<endl;
    }

    Mesh.Points.reserve(Mesh.NumberCell0D);
    string row;

    for (string& line0D : listLines0D) //for (tipo del contatore uguale a line : lista da cui prendo line)
    {
        istringstream rigaStream (line0D); //prendo stringa da listLines, lo converto in stream
        unsigned int Id0D;
        unsigned int marker0D;
        double x;
        double y;

        rigaStream >> Id0D >> marker0D >> x >> y;
//        getline(rigaStream,row);
//        istringstream(row) >> Id;
//        getline(rigaStream,row);

//        getline(rigaStream,row) ;
//        istringstream(row) >> x;

//        getline(rigaStream,row) ;
//        istringstream(row) >> y;
//        cout << "il vertice " << Id0D << " ha coordinate" << x <<"--"<< y <<endl;


        Point p = Point(Id0D,x,y);
        Mesh.Points.push_back(p);
    }

    cout << "lettura celle 0D fatta"<<endl;



/// FILE 1D

    ifstream file1D;

    string filePath1D = directory + "/Cell1Ds.csv";
    file1D.open(filePath1D);

    if(file1D.fail())
    {
        cerr<<"errore nell'apertura del file Cell1D"<<endl;
    }

    list<string> listLines1D;
    string line1D;
    while (getline(file1D, line1D))
        listLines1D.push_back(line1D);

    listLines1D.pop_front();

    Mesh.NumberCell1D = listLines1D.size();

    if (Mesh.NumberCell1D == 0)
    {
        cerr << "There is no cell 1D" << endl;
    }

    Mesh.Segments.reserve(Mesh.NumberCell1D);

    for (string& line1D : listLines1D) //for (tipo del contatore uguale a line : lista da cui prendo line)
    {
        istringstream rigaStream1D (line1D); //prendo stringa da listLines, lo converto in stream
       // getline(rigaStream,row) ; //prendo porzione di rigaStream fino a ;
        unsigned int Id1D;
        unsigned int marker1D;
        unsigned int IdOrigin;
        unsigned int IdEnd;

//        istringstream (row) >> Id; //dentro id ho il valore in intero
//        getline(rigaStream,row) ; //prendo porzione di rigaStream fino a ;

//        getline(rigaStream,row) ;
//        istringstream(row) >> IdOrigin;

//        getline(rigaStream,row) ;
//        istringstream(row) >> IdEnd;

        rigaStream1D >> Id1D >> marker1D >> IdOrigin >> IdEnd ;
        //cout << "questo e l'id del vertice origin  " << Mesh.Points[IdOrigin].Id << endl;

        //cout << "il segmento "<< Id1D << "ha ogigin " << IdOrigin << " end " << IdEnd << endl;
        Point origin;
        origin.Id = Mesh.Points[IdOrigin].Id;
        origin.x = Mesh.Points[IdOrigin].x;
        origin.y = Mesh.Points[IdOrigin].y;
        Point end ;
        end.Id = Mesh.Points[IdEnd].Id;
        end.x = Mesh.Points[IdEnd].x;
        end.y = Mesh.Points[IdEnd].y;
        Segment* s = new Segment(Id1D,origin,end);
        //cout << "origin  " << origin.x << "__" << origin.y <<endl;
        //cout << "origin  " << end.x << "__" << end.y <<endl;
        Mesh.Segments.push_back(*s);
    }
    cout << "lettura celle 1D fatta"<<endl;

    file1D.close();

/// FILE 2D

    ifstream file2D;
    string filePath2D = directory + "/Cell2Ds.csv";
    file2D.open(filePath2D);

    if (file2D.fail())
        cout<<"errore nell'apertura del file cell2D";

    list<string> listLines2D;
    string line2D;
    while (getline(file2D, line2D))
      listLines2D.push_back(line2D);

    listLines2D.pop_front();

    Mesh.NumberCell2D = listLines2D.size();

    if (Mesh.NumberCell2D == 0)
    {
      cerr << "There is no cell 2D" << endl;
    }

    Mesh.Triangles.reserve(Mesh.NumberCell2D);

    for (const string& line : listLines2D)
    {
      istringstream converter(line);

      unsigned int Id2D;
      array<unsigned int, 3> vertices;
      array<unsigned int, 3> edges;

      converter >>  Id2D;
      for(unsigned int i = 0; i < 3; i++)
        converter >> vertices[i];
      for(unsigned int i = 0; i < 3; i++)
        converter >> edges[i];


      //Triangle T = Triangle(Id2D, PointsT, SegmentsT);
      //Mesh.Triangles.push_back(T);

      Mesh.Triangles.push_back(Triangle(Id2D,
                                        {Mesh.Points[vertices[0]], Mesh.Points[vertices[1]], Mesh.Points[vertices[2]]},
                                        {Mesh.Segments[edges[0]], Mesh.Segments[edges[1]], Mesh.Segments[edges[2]]}));
      //funzione back(&referenza) per prendere l'ultimo elemento inserito in Triangles
      //Triangle &T = Mesh.Triangles.back();
      Mesh.Triangles.back().Area = Mesh.Triangles.back().AreaCalculator(Mesh.Points[vertices[0]],
                                                                        Mesh.Points[vertices[1]],
                                                                        Mesh.Points[vertices[2]]);

      //Mesh.Triangles.back().longestEdge = Mesh.Triangles.back().FindLongestEdge({Mesh.Segments[edges[0]],
                                                                                 //Mesh.Segments[edges[1]],
                                                                                 //Mesh.Segments[edges[2]]});
      Mesh.Triangles.back().longestEdge = Mesh.Triangles.back().FindLongestEdge(Mesh.Triangles.back().segmentsTriangle);

      for (unsigned int i = 0; i<3; i++)
      {
        if (Mesh.Triangles.back().longestEdge == Mesh.Triangles.back().segmentsTriangle[i].Id)
        {
            if (Mesh.Segments[Mesh.Triangles.back().longestEdge].origin.Id != Mesh.Triangles.back().segmentsTriangle[i].origin.Id)
            {
                Point tmp = Mesh.Segments[Mesh.Triangles.back().longestEdge].origin;
                Mesh.Segments[Mesh.Triangles.back().longestEdge].origin = Mesh.Triangles.back().segmentsTriangle[i].origin;
                Mesh.Segments[Mesh.Triangles.back().longestEdge].end = tmp;
            }
        }
      }

      Mesh.Triangles.back().adjacency(Mesh.Segments[edges[0]]);
      Mesh.Triangles.back().adjacency(Mesh.Segments[edges[1]]);
      Mesh.Triangles.back().adjacency(Mesh.Segments[edges[2]]);
      //cout << "fatta adiacenza" << endl;
    }


    for (unsigned int i = 0; i< Mesh.NumberCell2D; i++){
        //cout << "triangolo: " <<Mesh.Triangles[i].Id << endl;
        Mesh.OnOff.push_back(true);
    }

    //unsigned int t = Mesh.Segments[Mesh.Triangles.back().longestEdge].getAdj2();
    //cout << "Id Adiacente T2 di longestEdge: " << t << endl;

    file2D.close();

    cout << "lettura celle 2D fatta"<<endl;

}

Point TriangularMesh::CreateMidPoint(unsigned int &idSegment)
{
    array<double, 2> CoordinatesMidpoint = Segments[idSegment].midPoint; //contiene le sue coordinate,
    //dobbiamo creare l'id:
    unsigned int IdMidpoint = NumberCell0D;
    //mi serve per non avere lo stesso id di punti diversi:
    NumberCell0D += 1;

    Point Midpoint(IdMidpoint, CoordinatesMidpoint[0], CoordinatesMidpoint[1]); //ho creato il nuovo punto medio
    Points.push_back(Midpoint);
    return Midpoint;
}

array<unsigned int, 3> TriangularMesh::GetUtilities(Triangle &T, unsigned int &idSegment)
{
    unsigned int IdOpposite;
    unsigned int IdLatoDx;
    unsigned int IdLatoSx;
    //cerco id del vertice opposto e dei due lati da mantenere:
    for (unsigned int i = 0; i<3; i++)
    {
        if ((Segments[idSegment].origin.Id != T.pointsTriangle[i].Id) &&
            (Segments[idSegment].end.Id != T.pointsTriangle[i].Id))
        {
            IdOpposite = T.pointsTriangle[i].Id;
        }
    }
    for (unsigned int i = 0; i<3; i++)
    {
        if (idSegment != T.segmentsTriangle[i].Id) //se non è il lato che ho diviso in 2
        {
            if (Segments[idSegment].origin.Id ==  T.segmentsTriangle[i].end.Id)
            {
                IdLatoSx = T.segmentsTriangle[i].Id;

                for(unsigned int k=0; k<3; k++)
                {
                    if (k != idSegment && k != i)
                    {
                        IdLatoDx = T.segmentsTriangle[k].Id;
                    }
                }
                break;
            }
            else if (Segments[idSegment].end.Id ==  T.segmentsTriangle[i].origin.Id)
            {
                IdLatoDx = T.segmentsTriangle[i].Id;

                for(unsigned int k=0; k<3; k++)
                {
                    if (k != i && idSegment != k)
                    {
                        IdLatoSx = T.segmentsTriangle[k].Id;
                    }
                }
                break;
            }
        }
    }
    return {IdOpposite, IdLatoDx, IdLatoSx};
}


array<Triangle,2>TriangularMesh::Division(unsigned int &NumberCell0D,
                                          unsigned int &NumberCell1D,
                                          unsigned int &NumberCell2D,
                                          Triangle &T, unsigned int &idSegment, Point &Midpoint)
{

/// TROVO OPPOSITE E DUE LATI DA TENERE:

    array<unsigned int,3> utilites= GetUtilities(T, idSegment);
    unsigned int IdOpposite = utilites[0];
    unsigned int IdLatoDx = utilites[1];
    unsigned int IdLatoSx = utilites[2];
    cout << "Opposite: " << IdOpposite << endl;

    cout << "Id lato sx: " << IdLatoSx << " ___ Id lato dx: "<< IdLatoDx << endl;

    unsigned int NewIdS = NumberCell1D; //segmento che collega Midpoint e Opposte


    Segment NewS(NewIdS, Points[IdOpposite], Midpoint);
    Segments.push_back(NewS);

    NumberCell1D +=1;
    unsigned int NewIdSO = NumberCell1D; //segmento che collega Midpoint e origin del longestEdge
    Segment NewSO(NewIdSO, Segments[idSegment].origin, Midpoint);
    Segments.push_back(NewSO);

    NumberCell1D +=1;
    unsigned int NewIdSE = NumberCell1D; //segmento che collega Midpoint ed end del longestEdge
    Segment NewSE(NewIdSE,Midpoint, Segments[idSegment].end);
    Segments.push_back(NewSE);

    //mi serve per non avere lo stesso id di lati diversi
    NumberCell1D +=1;


    unsigned int NewIdT1 = NumberCell2D;
    array<Point,3> verticesT1 = {Segments[idSegment].origin, Midpoint, Points[IdOpposite]};
    array<Segment, 3> edgesT1 = {NewSO, NewS, Segments[IdLatoSx]};
    Triangle newT1(NewIdT1, verticesT1, edgesT1);

    //aggiorno adiacenza:
    Segments[IdLatoSx].disconnectTriangle(T.Id);
    newT1.adjacency(Segments[IdLatoSx]);

    NumberCell2D +=1;
    unsigned int NewIdT2 = NumberCell2D;
    array<Point,3> verticesT2 = {Midpoint, Segments[idSegment].end, Points[IdOpposite]};
    array<Segment, 3> edgesT2 = {NewSE, Segments[IdLatoDx], NewS};
    Triangle newT2(NewIdT2, verticesT2, edgesT2);

    //aggiorno adiacenza:
    Segments[IdLatoDx].disconnectTriangle(T.Id);
    newT2.adjacency(Segments[IdLatoDx]);

    //mi serve per non ripetere lo stesso id per triangoli diversi:
    NumberCell2D +=1;

    return {newT1, newT2};
}


array<Triangle,2> TriangularMesh::DivisionAdjacent(Triangle& adjT, unsigned int &idlongestEdge, Point &Midpoint,
                                       Segment &NewSO, Segment &NewSE)
{
///TROVO OPPOSITE E DUE LATI DA TENERE
    array<unsigned int,3> utilites= GetUtilities(adjT, idlongestEdge);
    unsigned int IdOpposite = utilites[0];
    unsigned int IdLatoDx = utilites[1];
    unsigned int IdLatoSx = utilites[2];

    cout << "Opposite: " << IdOpposite << endl;
    cout << "Id lato sx: " << IdLatoSx << " ___ Id lato dx: "<< IdLatoDx << endl;

    unsigned int NewIdS = NumberCell1D; //segmento che collega Midpoint e Opposite
    Segment NewS(NewIdS, Points[IdOpposite], Midpoint);
    Segments.push_back(NewS);
    NumberCell1D +=1;
    cout << "Id lato nuovo: " << NewS.Id << endl;

    unsigned int NewIdT1 = NumberCell2D;
    array<Point,3> verticesT1 = {Midpoint, Segments[idlongestEdge].origin, Points[IdOpposite]};
    array<Segment, 3> edgesT1 = {NewSO, Segments[IdLatoSx], NewS};
    Triangle newT1(NewIdT1, verticesT1, edgesT1);

    //aggiorno adiacenza:
    newT1.adjacency(NewSO);
    Segments[IdLatoSx].disconnectTriangle(adjT.Id);
    newT1.adjacency(Segments[IdLatoSx]);

    NumberCell2D +=1;
    unsigned int NewIdT2 = NumberCell2D;
    array<Point,3> verticesT2 = {Segments[idlongestEdge].end, Midpoint, Points[IdOpposite]};
    array<Segment, 3> edgesT2 = {NewSE, NewS, Segments[IdLatoDx]};
    Triangle newT2(NewIdT2, verticesT2, edgesT2);

    //aggiorno adiacenza:
    newT2.adjacency(NewSE);
    Segments[IdLatoDx].disconnectTriangle(adjT.Id);
    newT2.adjacency(Segments[IdLatoDx]);

    //mi serve per non ripetere lo stesso id per triangoli diversi:
    NumberCell2D +=1;

    //cout<<"Abbiamo diviso il triangolo numero  " << T.Id<<endl;
    return {newT1, newT2};
}





Raffinamento::Raffinamento(TriangularMesh& Mesh, const unsigned int &maxIterator, vector<unsigned int> &ThetaVector)
{
    for (unsigned int i=0; i < maxIterator; i++)
    {
        ThetaVector[i];
        cout << "Divido triangolo di thetaV: " << Mesh.Triangles[ThetaVector[i]] <<endl;
        cout << "origin longest edge: " << Mesh.Segments[Mesh.Triangles[ThetaVector[i]].longestEdge].origin.Id << "__";
        cout << "end longest edge: " << Mesh.Segments[Mesh.Triangles[ThetaVector[i]].longestEdge].end.Id << endl;

        Point MidPoint = Mesh.CreateMidPoint(Mesh.Triangles[ThetaVector[i]].longestEdge);

        array<Triangle, 2> newTriangles = Mesh.Division(Mesh.NumberCell0D,
                                                       Mesh.NumberCell1D,
                                                       Mesh.NumberCell2D,
                                                       Mesh.Triangles[ThetaVector[i]],
                                                       Mesh.Triangles[ThetaVector[i]].longestEdge,
                                                       MidPoint);

//        cout << " origin primo lato: " << Mesh.Triangles[ThetaVector[i]].segmentsTriangle[0].origin.Id<< "__";
//        cout << " end primo lato: " << Mesh.Triangles[ThetaVector[i]].segmentsTriangle[0].end.Id <<endl;

//        cout << " origin secondo lato: " << Mesh.Triangles[ThetaVector[i]].segmentsTriangle[1].origin.Id << "__";
//        cout << " end secondo lato: " << Mesh.Triangles[ThetaVector[i]].segmentsTriangle[1].end.Id <<endl;

//        cout << " origin terzo lato: " << Mesh.Triangles[ThetaVector[i]].segmentsTriangle[2].origin.Id << "__";
//        cout << " end terzo lato: " << Mesh.Triangles[ThetaVector[i]].segmentsTriangle[2].end.Id <<endl;

        cout << "new T1 "<< newTriangles[0] << endl;
        cout << "new T2 " << newTriangles[1] << endl;

        Mesh.Triangles.push_back(newTriangles[0]);
        Mesh.Triangles.push_back(newTriangles[1]);

        Mesh.OnOff[ThetaVector[i]] = false;
//        cout << Mesh.OnOff[ThetaVector[i]] << " Ho spento il triangolo " << ThetaVector[i]<< endl;
        Mesh.OnOff.push_back(true);
//        cout << Mesh.OnOff[Mesh.OnOff.size()-1] << " Ho acceso il triangolo " << Mesh.OnOff.size()-1<< endl;
        Mesh.OnOff.push_back(true);
//        cout << Mesh.OnOff[Mesh.OnOff.size()-1] << " Ho acceso il triangolo " << Mesh.OnOff.size()-1<< endl;

        unsigned int l = Mesh.Triangles[ThetaVector[i]].longestEdge;

        unsigned int adj1 = Mesh.Segments[l].getAdj1();
        unsigned int adj2 = Mesh.Segments[l].getAdj2();

        cout << "primo adiacente: " << adj1 << endl;
        cout << "secondo adiacente: " << adj2 << endl;

        cout << "finito di dividere T "<< Mesh.Triangles[ThetaVector[i]] << endl;

        if (adj1 == 3567587327 || adj2 == 3567587327)
        {
            cout << "Lato di bordo" << endl;
        }

        //se T è il getT1 di LongestEdge:
        else if (adj1 == ThetaVector[i] && Mesh.OnOff[adj2] == true)
        {
            //fai division su getT2 (triangolo adiacente a T)
            cout << "sono nel primo if, caso T = GetT1"<< endl;
            unsigned int Ta = adj2;
            cout<<"adiacente di "<< ThetaVector[i] << " è " << Ta << endl;

            unsigned int idSO = Mesh.Segments.size()-2;
            unsigned int idSE = Mesh.Segments.size()-1;
            cout << "SO: " << idSO << "__" << " SE: " << idSE << endl;

            array<Triangle,2> NewTrianglesA = Mesh.DivisionAdjacent(Mesh.Triangles[Ta], Mesh.Triangles[ThetaVector[i]].longestEdge,
                                                               MidPoint, Mesh.Segments[idSO], Mesh.Segments[idSE]);

            cout << "new TA 1 "<< NewTrianglesA[0] << endl;
            cout << "new TA 2 " << NewTrianglesA[1] << endl;

            Mesh.Triangles.push_back(NewTrianglesA[0]);
            Mesh.Triangles.push_back(NewTrianglesA[1]);
            Mesh.OnOff[Ta] = false;
            Mesh.OnOff.push_back(true);
            Mesh.OnOff.push_back(true);

            cout << "abbiamo diviso Ta "<< Ta << endl;

        }

        else if (adj2 == ThetaVector[i] && Mesh.OnOff[adj1] == true)
        {
            cout << "sono nell'altro else if, caso T = GetT2"<< endl;
            unsigned int Ta = adj1;
            cout<<"adiacente di "<< ThetaVector[i] << " è " << Mesh.Triangles[Ta] <<endl;

            unsigned int idSO = Mesh.Segments.size()-2;
            unsigned int idSE = Mesh.Segments.size()-1;
            cout << "SO: " << idSO << "__" << " SE: " << idSE << endl;

            cout << "longestEdge vecchio: "<< Mesh.Triangles[ThetaVector[i]].longestEdge << endl;
            array<Triangle,2> NewTrianglesA = Mesh.DivisionAdjacent(Mesh.Triangles[Ta], Mesh.Triangles[ThetaVector[i]].longestEdge,
                                                               MidPoint, Mesh.Segments[idSO], Mesh.Segments[idSE]);

            cout << "new TA 1 " << NewTrianglesA[0] << endl;
            cout << "new TA 2 " << NewTrianglesA[1] << endl;

            Mesh.Triangles.push_back(NewTrianglesA[0]);
            Mesh.Triangles.push_back(NewTrianglesA[1]);
            Mesh.OnOff[Ta] = false;
            Mesh.OnOff.push_back(true);
            Mesh.OnOff.push_back(true);
        }
    }
}

} //fine namespace



