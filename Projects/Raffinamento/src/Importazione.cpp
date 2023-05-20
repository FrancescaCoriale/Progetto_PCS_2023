#include <Eigen/StdVector>
#include <iostream>
#include <fstream>
#include "Eigen/Eigen"
#include "Importazione.hpp"
#include "map"

namespace ImportLibrary
{

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


}

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
    }
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

    }
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
        }

        for (unsigned int i=0; i<3; i++) //contatore degli elementi del vettore interno
        {
            getline(rigaStream,row); //salva il 16 dentro row
            istringstream(row) >> edges[i];
        }

        Vertices2D.push_back(vertices);

    }
    //for(unsigned int i=0; i<80; i++){
    //    this->onOff.push_back(true);
    //}

}

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
    vector<unsigned int> vertices;
    //per ogni riga in Vertices2D prendo il vettore con i tre ID dei vertici
    for(int i = 0; i < n; i++) {
        vertices.push_back(Vertices2D[i]);
        x_1 = Coordinates0D[vertices(0)][0]; y_1 = Coordinates0D[vertices(0)][1];
        x_2 = Coordinates0D[vertices(1)][0]; y_2 = Coordinates0D[vertices(1)][1];
        x_3 = Coordinates0D[vertices(2)][0]; y_3 = Coordinates0D[vertices(2)][1];
        //Formula dell'area di Gauss
        A_12 = (x_1*y_2) - (y_1*x_2);
        A_23 = (x_2*y_3) - (y_2*x_3);
        A_31 = (x_3*y_1) - (y_3*x_1);
        Area = (A_12+A_23+A_31)/2;
        Aree[i] = Area;
    }
    cout<<Aree<< endl;
}



}














