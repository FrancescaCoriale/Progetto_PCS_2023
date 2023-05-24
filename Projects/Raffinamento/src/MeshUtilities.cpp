#include <Eigen/StdVector>
#include <iostream>
#include <fstream>
#include "Eigen/Eigen"
#include "Importazione.hpp"
//#include "map"

namespace ImportLibrary
{
    ImportMesh::Cell0D(TriangularMesh& Mesh):
        NumberCell0D(NumberCell0D),
        Coordinates0D(Coordinates0D) {
        ifstream file;
        file.open("./Cell0Ds.csv");
        if(file.fail())
            return false;

        list<string> listLines;
        string line;
        while (getline(file, line))
            listLines.push_back(line);

        file.close();
        listLines.pop_front();
        NumberCell0D = listLines.size();

        if (mesh.NumberCell0D == 0)
        {
        cerr << "There is no cell 0D" << endl;
        return false;
        }
        Cell0DId.reserve(mesh.NumberCell0D);
        Cell0DCoordinates.reserve(mesh.NumberCell0D);

        Coordinates0D.resize(NumberCell0D);
        string row;
        for (string& riga : listLines) //for (tipo del contatore uguale a line : lista da cui prendo line)
        {
            istringstream rigaStream (riga); //prendo stringa da listLines, lo converto in stream

            getline(rigaStream,row);

            getline(rigaStream,row);

            Vector2d coordinates;
            getline(rigaStream,row);
            istringstream(row) >> coordinates[0];
            getline(rigaStream,row);
            istringstream(row) >> coordinates[1];

            Coordinates0D.push_back(coordinates); //STESSA CAZZO DI COSA DI PUSH_BACK
        }
        file.close();
        return true;
    }

    ImportMesh::Cell1D(TriangularMesh& Mesh):
            NumberCell1D(NumberCell1D),
            OriginEnds(OriginEnds) {
        ifstream file;
        file.open("./Cell1Ds.csv");

        if(file.fail())
          return false;

        list<string> listLines;
        string line;
        while (getline(file, line))
          listLines.push_back(line);

        listLines.pop_front();

        NumberCell1D = listLines.size();
        if (mesh.NumberCell1D == 0)
        {
          cerr << "There is no cell 1D" << endl;
          return false;
        }
        OriginEnds.resize(NumberCell1D);
        string row;
        for (string& riga : listLines) //for (tipo del contatore uguale a line : lista da cui prendo line)
        {
            istringstream rigaStream (riga); //prendo stringa da listLines, lo converto in stream
            getline(rigaStream,row) ; //prendo porzione di rigaStream fino a ;
            unsigned int id;
            istringstream (row) >> id; //dentro id ho il valore in intero

            getline(rigaStream,row) ; //prendo porzione di rigaStream fino a ;
            vector<unsigned int> originEnd;
            getline(rigaStream,row) ;
            istringstream(row) >> originEnd[0];
            getline(rigaStream,row) ;
            istringstream(row) >> originEnd[1];
            OriginEnds.push_back(originEnd); //STESSA CAZZO DI COSA DI <<
        }
    }

    ImportMesh::Cell2D(TriangularMesh& Mesh):
        NumberCell2D(NumberCell2D),
        Vertices(Vertices),
        Edges(Edges) {
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
        NumberCell2D = listLines.size();
        if (NumberCell2D == 0)
        {
            cout<<"nessuna cella 2D disponibile"<<endl;
        };
        Vertices.resize(NumberCell2D); //diamo una dimensione al vettore più esterno per poter inserire i vettori più interni
        Edges.resize(NumberCell2D);
        string row;
        for (string& riga : listLines) //for (tipo del contatore uguale a line : lista da cui prendo line)
        {
            istringstream rigaStream (riga); //prendo stringa da listLines, lo converto in stream

            getline(rigaStream,row) ; //MEMORIZZO GLI ID
            unsigned int id;
            istringstream (row) >> id;
            vector<unsigned int> vertices;
            vertices.resize(3);
            vector<unsigned int> edges;
            edges.resize(3);
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
            Vertices.push_back(vertices);
            Edges.push_back(edges);
        };
    }
    // NON SAPPIAMO COME USARLO:
    Cell0D::FindCoordinates(const Vectord2d& Coordinates, unsigned int& point, Vector2d pointCoordinates):
    {
        pointsCoordinates = {Coordinates0D[point][0], Coordinates0D[point][1]};
    }
    //

    Cell1D::LengthEdge(const Vector2D& originEnd,
                        const Vector2d& Coordinates0D, double LengthEdge):
    {
        Vector2d origin = {Coordinates0D[originEnd[0]][0], Coordinates0D[originEnd[0]][1]};
        Vector2d end = {Coordinates0D[originEnd[1]][0], Coordinates0D[originEnd[1]][1]};
        LengthEdge = (end-origin).norm();//calcolo la norma e la salvo nel vettore
        //elemento i-esimo di LengthEdge è la lunghezza dell'iesimo lato dentro OriginEnd
    }



    Cell2D::AreaCalculator(const Vector3d &x, const Vector3d &y, double Area):
    {
        double A_12; double A_23; double A_31;
        x_1 = x[0]; y_1 = y[0];
        x_2 = x[1]; y_2 = y[1];
        x_3 = x[2]; y_3 = y[2];
        //Formula dell'area di Gauss
        A_12 = (x_1*y_2) - (y_1*x_2);
        A_23 = (x_2*y_3) - (y_2*x_3);
        A_31 = (x_3*y_1) - (y_3*x_1);
        Area = (A_12+A_23+A_31)/2;

    }


    Cell2D::FindLongestEdge(VectorXd& LengthEdges, const array<unsigned int, 3>& edges, unsigned int& LongestEdge):
    {
        //unsigned int n = NumberCell2D; //quanti triangoli ho
        //for (unsigned int i=0; i<n; i++) //passo in rassegna ogni triangolo
        //{
        double max = 0;
        unsigned int id_longestEdge = 0;
            //vector<unsigned int> edges = Edges2D[i]; //i-esimo triangolo, salvo dentro edges i 3 lati
            for (unsigned int k=0; k<3; k++)
            {
                if (LengthEdges[edges[k]] > max)
                {
                    max = LengthEdges[edges[k]];
                    id_longestEdge = edges[k];
                };
            };
            LongestEdge[i] = id_longestEdge;
            max = 0;
        };
    }

    Cell2D::Adjacency(list<unsigned int>& AdjacencyList, const vector<unsigned int>& Edges2D):
    {
        unsigned int n = 187; //NumberCell2D; stesso problema di prima!!
        for (unsigned int i=0; i<n; i++) //id triangolo
        {
            list<unsigned int> list; //lista contenente i triangoli adiacenti all'i-esimo triangolo
            vector<unsigned int> edges = Edges2D[i]; //i-esimo triangolo, salvo dentro edges i 3 lati
            for(unsigned int k=0; k<n; k++) //id triangolo da confrontare con l'i-esimo trianglo
            {
                if (i!=k) //controllo di non prendere lo stesso triangolo
                {
                    for (unsigned int j=0; j<3; j++) //j-esimo elemento di edges
                    {
                        for (unsigned int w=0; w<3; w++) //w-esimo elemento di Edges2D[k]
                        {
                            if (edges[j]==Edges2D[k][w])
                                list.push_back(k);
                        }
                    }
                }
                AdjacencyList.push_back(list);
                list.clear(); //azzero la lista
            };

        };
    }








/////////////////////////////////////////
Cell0D::Cell0D(unsigned int& NumberCell0D, vector<Vector2d>& Coordinates0D):
    NumberCell0D(NumberCell0D),
    Coordinates0D(Coordinates0D)

{
    ifstream file;
    file.open("Cell0Ds.csv");
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
    NumberCell0D = listLines.size();
    if (NumberCell0D == 0)
    {   cout<<"nessuna cella disponibile"<<endl;
    }

    Coordinates0D.resize(NumberCell0D);
    string row;
    for (string& riga : listLines) //for (tipo del contatore uguale a line : lista da cui prendo line)
    {
        istringstream rigaStream (riga); //prendo stringa da listLines, lo converto in stream

        getline(rigaStream,row) ;

        getline(rigaStream,row) ;

        Vector2d coordinates;
        getline(rigaStream,row) ;
        istringstream(row) >> coordinates[0];
        getline(rigaStream,row) ;
        istringstream(row) >> coordinates[1];


        Coordinates0D.push_back(coordinates); //STESSA CAZZO DI COSA DI PUSH_BACK
    }


}

Cell1D::Cell1D(unsigned int& NumberCell1D, vector<vector<unsigned int>>& OriginEnd1D):
    NumberCell1D(NumberCell1D),
    OriginEnd1D(OriginEnd1D)

{
    ifstream file;
    file.open("Cell1Ds.csv");
    if (file.fail())
    {
        cerr<<"errore nell'apertura del file Cell1D"<<endl;
    }

    string line;
    list<string> listLines;
    while (getline(file,line))
        listLines.push_back(line);

    file.close();

    listLines.pop_front(); //elimino dalla lista la prima riga
    NumberCell1D = listLines.size();
    if (NumberCell1D == 0)
    {   cout<<"nessuna cella disponibile"<<endl;
    }

    OriginEnd1D.resize(NumberCell1D);
    string row;
    for (string& riga : listLines) //for (tipo del contatore uguale a line : lista da cui prendo line)
    {
        istringstream rigaStream (riga); //prendo stringa da listLines, lo converto in stream

        getline(rigaStream,row) ; //prendo porzione di rigaStream fino a ;
        unsigned int id;
        istringstream (row) >> id; //dentro id ho il valore in intero

        getline(rigaStream,row) ; //prendo porzione di rigaStream fino a ;

        vector<unsigned int> originEnd;
        getline(rigaStream,row) ;
        istringstream(row) >> originEnd[0];
        getline(rigaStream,row) ;
        istringstream(row) >> originEnd[1];

        OriginEnd1D.push_back(originEnd); //STESSA CAZZO DI COSA DI <<
    }
};


void LengthEdges(const vector<vector<unsigned int>>& OriginEnd1D, const vector<Vector2d>& Coordinates0D, VectorXd& LengthEdge)
{
    unsigned int n = NumberCell1D; //NumberCell1D; CHIEDERE dobbiamo chiamare il costruttore cell1d e dare il valore di Numbercell1d
    Vector2d origin;
    Vector2d end;
    for (unsigned int i =0; i < n; i++)
    {
        origin = {Coordinates0D[OriginEnd1D[i][0]][0], Coordinates0D[OriginEnd1D[i][0]][1]};
        end = {Coordinates0D[OriginEnd1D[i][1]][0], Coordinates0D[OriginEnd1D[i][1]][1]};
        LengthEdge[i] = (end-origin).norm(); //calcolo la norma e la salvo nel vettore
        //elemento i-esimo di LengthEdge è la lunghezza dell'iesimo lato dentro OriginEnd
    };
};



Cell2D::Cell2D(unsigned int& NumberCell2D, vector<vector<unsigned int>>& Vertices2D, vector<vector<unsigned int>>& Edges2D):
    NumberCell2D(NumberCell2D),
    Vertices2D(Vertices2D),
    Edges2D(Edges2D)
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
    NumberCell2D = listLines.size();
    if (NumberCell2D == 0)
    {
        cout<<"nessuna cella 2D disponibile"<<endl;

    };
    Vertices2D.resize(NumberCell2D); //diamo una dimensione al vettore più esterno per poter inserire i vettori più interni
    Edges2D.resize(NumberCell2D);


    string row;
    for (string& riga : listLines) //for (tipo del contatore uguale a line : lista da cui prendo line)
    {
        istringstream rigaStream (riga); //prendo stringa da listLines, lo converto in stream

        getline(rigaStream,row) ; //MEMORIZZO GLI ID
        unsigned int id;
        istringstream (row) >> id;

        vector<unsigned int> vertices;
        vertices.resize(3);
        vector<unsigned int> edges;
        edges.resize(3);
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

        Vertices2D.push_back(vertices);

    };
    //for(unsigned int i=0; i<80; i++){
    //    this->onOff.push_back(true);
    //}

};


void Cell2D::FindLongestEdge(const vector<vector<unsigned int>>& OriginEnd1D, VectorXd& LengthEdge, const vector<vector<unsigned int>>& Edges2D, vector<unsigned int>& LongestEdge)
{

    unsigned int n = NumberCell2D; //quanti triangoli ho


    for (unsigned int i=0; i<n; i++) //passo in rassegna ogni triangolo
    {
        double max = 0;
        unsigned int id_longestEdge = 0;
        vector<unsigned int> edges = Edges2D[i]; //i-esimo triangolo, salvo dentro edges i 3 lati
        for (unsigned int k=0; k<3; k++)
        {
            if (LengthEdge[edges[k]] > max)
            {
                max = LengthEdge[edges[k]];
                id_longestEdge = edges[k];
            };
        };
        LongestEdge[i] = id_longestEdge;
        max = 0;
    };
};

void Cell2D::AreaCalculator(const vector<Vector2d>& Coordinates0D, const vector<vector<unsigned int>>& Vertices2D, vector<double>& Aree)
{
    int n = NumberCell2D;
    double x_1; double y_1;
    double x_2; double y_2;
    double x_3; double y_3;
    double A_12 = 0;
    double A_23 = 0;
    double A_31 = 0;
    double Area = 0;

    //per ogni riga in Vertices2D prendo il vettore con i tre ID dei vertici
    for(int i = 0; i < n; i++) {
        x_1 = Coordinates0D[Vertices2D[i][0]][0]; y_1 = Coordinates0D[Vertices2D[i][0]][1];
        x_2 = Coordinates0D[Vertices2D[i][1]][0]; y_2 = Coordinates0D[Vertices2D[i][1]][1];
        x_3 = Coordinates0D[Vertices2D[i][2]][0]; y_3 = Coordinates0D[Vertices2D[i][2]][1];

        //Formula dell'area di Gauss
        A_12 = (x_1*y_2) - (y_1*x_2);
        A_23 = (x_2*y_3) - (y_2*x_3);
        A_31 = (x_3*y_1) - (y_3*x_1);
        Area = (A_12+A_23+A_31)/2;
        Aree[i] = Area;
    }
}


void Adjacency(list<list<unsigned int>>& AdjacencyList, const vector<vector<unsigned int>>& Edges2D)
{
    unsigned int n = 187; //NumberCell2D; stesso problema di prima!!

    for (unsigned int i=0; i<n; i++) //id triangolo
    {
        list<unsigned int> list; //lista contenente i triangoli adiacenti all'i-esimo triangolo
        vector<unsigned int> edges = Edges2D[i]; //i-esimo triangolo, salvo dentro edges i 3 lati

        for(unsigned int k=0; k<n; k++) //id triangolo da confrontare con l'i-esimo trianglo
        {
            if (i!=k) //controllo di non prendere lo stesso triangolo
            {
                for (unsigned int j=0; j<3; j++) //j-esimo elemento di edges
                {
                    for (unsigned int w=0; w<3; w++) //w-esimo elemento di Edges2D[k]
                    {
                        if (edges[j]==Edges2D[k][w])
                            list.push_back(k);
                    }
                }
            }
            AdjacencyList.push_back(list);
            list.clear(); //azzero la lista
        };

    };
};



}//parentesi del namespace














