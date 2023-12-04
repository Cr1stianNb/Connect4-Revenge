#include "ControladorArchivo.h"
#include "Solver.hpp"


// Los nombres de los archivos utilizados
const string ControladorArchivo::ARCHIVO_GUARDADO = "partidas_guardadas.csv";
const string ControladorArchivo::ARCHIVO_CARGADO = "partidas_incompletas.csv";



/***
 * Constructor de la clase
*/
ControladorArchivo::ControladorArchivo() : juegosIncompletos{0}
{
    cargarPartidasIncompleta();
};
ControladorArchivo::~ControladorArchivo()
{};



int ControladorArchivo::getSizePartidasIncompleta()
{
    return juegosIncompletos.size();
}


void ControladorArchivo::cargarPartidasIncompleta()
{
    juegosIncompletos.clear(); // Para evitar partidas clones
    cout << "Empezando Lectura de archivos..." << endl;
    ifstream archivo(ARCHIVO_CARGADO);
    if(!archivo.fail()) // assert???
    {
        string linea;
        char delimitador = ',';
        bool primerJugador;
        int dificultad;
        int firstPlayer;
        int depthIn;
        while(getline(archivo, linea))
        {

            stringstream stream(linea);
            string tablero, dificultadS,  currentP, nombreJuego, depth;
            getline(stream, tablero, delimitador);
            getline(stream,dificultadS, delimitador);
            getline(stream,currentP, delimitador);
            getline(stream, nombreJuego, delimitador);
            getline(stream,depth, delimitador);
            firstPlayer = stoi(currentP);
            dificultad = stoi(dificultadS);
            depthIn = stoi(depth);              // Siempre va ser el  jugador actual player
            GameController game = GameController(Solver::PLAYER, depthIn, dificultad, nombreJuego, firstPlayer);
        
            if(!game.copyBoard(tablero)) // Copia el tablero, si no existe fallas al copiar entonces lo guarda en el vector
            {
                cout << "El juego con nombre: " << nombreJuego << "Ha sido descartado..." << endl;
            }
            else 
            {
                this->juegosIncompletos.push_back(game);
            }
        }

        cout << "Completado" << endl;

    }
    else
    {   
        cout << "Error al cargar las partidas " << endl; 
    } 
}


string ControladorArchivo::mostrarResultados()
{
    ifstream archivo(ARCHIVO_GUARDADO);
    if(archivo.fail())
    {
        return "No se pudo encontrar el archivo"; 
    }
    string linea;
    char delimitador = ',';
    int contador = 1;
    string str = "";
    while(getline(archivo, linea))
    {
        stringstream stream (linea);
        string tablero, dificultad, nombreJuego, resultado, first;
        getline(stream,tablero,delimitador);
        getline(stream, dificultad, delimitador);
        getline(stream, nombreJuego, delimitador);
        getline(stream,first,delimitador);
        getline(stream,resultado,delimitador);
        GameController g = GameController();
        g.setFirst(stoi(first));
        cout << "empezo" << g.getFirst();
        g.copyBoard(tablero);
        str += "\n-Partida numero: " +  to_string(contador) + "\n";
        str += g.printBoard() +  "\n";
        str += "Dificultad: " + dificultad + "\n";
        str += "Nombre del juego: " + nombreJuego + "\n";
        str += "Resultado: "  +  resultado + "\n";
        str += "------------------------------ \n";
        contador++;
    }
    archivo.close();
    return str;
}


/**
 * Se pregunta al usuario por el tablero a jugar
 * PRE-CONDICION: Se debe verificar si existen partidas guardadas
*/
GameController& ControladorArchivo::escogerPartida()
{
    int indicePartida;
    cout << mostrarPartidasIncompletas() << endl;
    while(true)
    {
        cout << "Escoge una de las partidas incompletas: (Por Numero): " << endl;
        indicePartida = parseInt("Ingrese una partida (enumeracion)");
        indicePartida--;
        if(!(indicePartida < 0 || indicePartida > juegosIncompletos.size()))
        {
            GameController& game =  juegosIncompletos[indicePartida];
            return game;

        }
    }
    
    return juegosIncompletos[0];
}
string ControladorArchivo::mostrarPartidasIncompletas()
{
    string text  = "\nListado de los nombres de las partidas incompletas: \n";
    for(int i=0; i<juegosIncompletos.size();i++)
    {
        text += "- " + to_string(i+1) + " Nombre de la partida: " +  juegosIncompletos[i].getGameName() + "\n";
    }
    return text;
}

void ControladorArchivo::guardarPartidaCompleta(GameController& juego)
{
    ofstream fich{ControladorArchivo::ARCHIVO_GUARDADO, ios::app};
    if (!fich)
    {
        cout << "Error al abrir " << ARCHIVO_GUARDADO << endl;
        exit(EXIT_FAILURE);
    }
    fich << juego.getSeq() << "," << juego.getDifficult() <<  "," << juego.getGameName() 
    << "," << juego.getFirst()  << ","<<(juego.getCurrentPlayer()==Solver::PLAYER ? "IA~Wins" : "Human~Wins") <<  endl;
    fich.close();
};


void ControladorArchivo::guardarPartidaIncompleta(GameController& juego)
{
    ofstream fich{ControladorArchivo::ARCHIVO_CARGADO, ios::app}; // Solo se agrega una linea mas
        if (!fich)
        {
            cout << "Error al abrir " << ARCHIVO_CARGADO << endl;
            exit(EXIT_FAILURE);
        }
   
    fich << juego.getSeq() << "," << juego.getDifficult() << "," << juego.getFirst() << "," << juego.getGameName() << "," << juego.getDepth() << endl;
    fich.close();
    
};
