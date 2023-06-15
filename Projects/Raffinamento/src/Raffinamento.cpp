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

    /// FILE 2D

    file1D.close();

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


      cout << "il triangolo " << Id2D<< "ha vertici "<< vertices[0]<<"--"<<vertices[1] <<"--"<< vertices[2]<<endl;
//      array <Point,3> PointsT = {Mesh.Points[vertices[0]], Mesh.Points[vertices[1]], Mesh.Points[vertices[2]]};
//      array<Segment, 3> SegmentsT = {Mesh.Segments[edges[0]], Mesh.Segments[edges[1]], Mesh.Segments[edges[2]]};


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

      Mesh.Triangles.back().longestEdge = Mesh.Triangles.back().FindLongestEdge({Mesh.Segments[edges[0]],
                                                                                 Mesh.Segments[edges[1]],
                                                                                 Mesh.Segments[edges[2]]});

      Mesh.Triangles.back().adjacency(Mesh.Triangles.back(), Mesh.Segments[edges[0]]);
      Mesh.Triangles.back().adjacency(Mesh.Triangles.back(), Mesh.Segments[edges[1]]);
      Mesh.Triangles.back().adjacency(Mesh.Triangles.back(), Mesh.Segments[edges[2]]);
      //cout << "fatta adiacenza" << endl;

    }


    for (unsigned int i = 0; i< Mesh.NumberCell2D; i++){
        //cout << "triangolo: " <<Mesh.Triangles[i].Id << endl;
        Mesh.OnOff.push_back(true);
    }

    unsigned int t = Mesh.Segments[Mesh.Triangles.back().longestEdge].getAdj2();
    cout << "Id Adiacente T2 di longestEdge: " << t << endl;

    file2D.close();

    cout << "lettura celle 2D fatta"<<endl;

}




array<Triangle,2>TriangularMesh::Division(unsigned int &NumberCell0D,
                                          unsigned int &NumberCell1D,
                                          unsigned int &NumberCell2D,
                                          Triangle &T, unsigned int idSegment)


{
    array<double, 2> CoordinatesMidpoint = Segments[idSegment].midPoint; //contiene le sue coordinate, dobbiamo creare l'id
    unsigned int IdMidpoint = NumberCell0D;
    unsigned int IdOpposite = 0;
    unsigned int IdLatoSx = 0;
    unsigned int IdLatoDx = 0;

    Point Midpoint(IdMidpoint, CoordinatesMidpoint[0], CoordinatesMidpoint[1]); //ho creato il nuovo punto medio
    Points.push_back(Midpoint);


    //cerco id del vertice opposto
    for (unsigned int i = 0; i<3; i++)
    {
        if ((Segments[idSegment].origin.Id != T.pointsTriangle[i].Id) &&
            (Segments[idSegment].end.Id != T.pointsTriangle[i].Id))
        {
            IdOpposite = T.pointsTriangle[i].Id;
        }

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
            }
        }

    };


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
    NumberCell1D +=1;


    unsigned int NewIdT1 = NumberCell2D;
    array<Point,3> verticesT1 = {Segments[idSegment].origin, Midpoint, Points[IdOpposite]};
    array<Segment, 3> edgesT1 = {NewS, NewSO, Segments[IdLatoSx]};
    Triangle newT1(NewIdT1, verticesT1, edgesT1);

    NumberCell2D +=1;

    unsigned int NewIdT2 = NumberCell2D;
    array<Point,3> verticesT2 = {Midpoint, Segments[idSegment].end, Points[IdOpposite]};
    array<Segment, 3> edgesT2 = {NewS, NewSE, Segments[IdLatoDx]};
    Triangle newT2(NewIdT2, verticesT2, edgesT2);

//    cout<<"Abbiamo diviso il triangolo numero  " << T.Id<<endl;
    return {newT1, newT2};
}

Raffinamento::Raffinamento(TriangularMesh& Mesh, const unsigned int &maxIterator, vector<unsigned int> &ThetaVector)
{
    for (unsigned int i=0; i < maxIterator; i++)
    {
        //ThetaVector[i];
        cout << "thetaV alla posizione i " << ThetaVector[i] <<endl;


        array<Triangle, 2> newTriangles =Mesh.Division(Mesh.NumberCell0D,
                                                       Mesh.NumberCell1D,
                                                       Mesh.NumberCell2D,
                                                       Mesh.Triangles[ThetaVector[i]],
                                                       Mesh.Triangles[ThetaVector[i]].longestEdge);

        cout << "new T1 "<< newTriangles[0] << endl;
        cout << "new T2 " << newTriangles[1] << endl;

        Mesh.Triangles.push_back(newTriangles[0]);
        Mesh.Triangles.push_back(newTriangles[1]);

        Mesh.OnOff[ThetaVector[i]] = false;
        Mesh.OnOff.push_back(true);
        Mesh.OnOff.push_back(true);

        unsigned int l = Mesh.Triangles[ThetaVector[i]].longestEdge;
//        cout << "finito di dividere T "<< Mesh.Triangles[ThetaVector[i]] << endl;

        unsigned int adj1 = Mesh.Segments[l].getAdj1();
        unsigned int adj2 = Mesh.Segments[l].getAdj2();

        cout << "primo adiacente: " << adj1 << endl;
        cout << "secondo adiacente: " << adj2 << endl;


        //se T è il getT1 di LongestEdge:
        if (adj1 == ThetaVector[i] && Mesh.OnOff[adj2] == true)
        {
            //fai division su getT2 (triangolo adiacente a T)
            cout << "sono nel primo if"<< endl;
            unsigned int Ta = adj2;
            cout<<"adiacente di "<< ThetaVector[i] << "è " << Ta << endl;

            array<Triangle,2> NewTrianglesA = Mesh.Division(Mesh.NumberCell0D, Mesh.NumberCell1D,
                                                            Mesh.NumberCell2D, Mesh.Triangles[Ta],
                                                            Mesh.Triangles[Ta].longestEdge);

            Mesh.Triangles.push_back(NewTrianglesA[0]);
            Mesh.Triangles.push_back(NewTrianglesA[1]);
            Mesh.OnOff[Ta] = false;
            Mesh.OnOff.push_back(true);
            Mesh.OnOff.push_back(true);

            cout << "abbiamo diviso Ta"<< Ta << endl;

        }

        else if (adj2 == ThetaVector[i] && Mesh.OnOff[adj1] == true)
        {
            cout << "sono nell'altro else if"<< endl;
            unsigned int Ta = adj1;
            cout<<"adiacente di "<< ThetaVector[i] << "è " << Ta<<endl;
            array<Triangle,2> NewTrianglesA = Mesh.Division(Mesh.NumberCell0D,
                                                            Mesh.NumberCell1D,
                                                            Mesh.NumberCell2D, Mesh.Triangles[Ta],
                                                            Mesh.Triangles[Ta].longestEdge);

            Mesh.Triangles.push_back(NewTrianglesA[0]);
            Mesh.Triangles.push_back(NewTrianglesA[1]);
            Mesh.OnOff[Ta] = false;
            Mesh.OnOff.push_back(true);
            Mesh.OnOff.push_back(true);
        }
    }
}



} //fine namespace



