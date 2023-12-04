#include <iostream>
#include <vector>
#include <limits.h>
#include <array>
#include <sstream>
#include "Solver.hpp"
#include "GameController.hpp"
#include "ControladorArchivo.cpp"


/**
 * 	Definición la función global min
 * Determina entre dos numeros cual es el menor de los dos
 * @param a , numero a comparar
 * @param b , numero a comparar
 * @return true si a es menor que b, false lo contrario
 * 
*/
#define min(a,b) (((a) < (b)) ? (a) : (b))
/**
 * 	Definición la función global max
 * Determina entre dos numeros cual es el mayor de los dos
 * @param a , numero a comparar
 * @param b , numero a comparar
 * @return true si a es mayor que b, false lo contrario
 * 
*/
#define max(a,b) (((a) > (b)) ? (a) : (b))


using namespace std;

/**
 * Constantes Enteras, sirven como control de flujo en el menú.
*/
const int EMPEZAR_NUEVA = 1, CARGAR_INCOMPLETA = 2, VER_COMPLETA = 3, SALIR = 4;


/**
 * ParseInt(): mientras que el usuario no ponga por teclado un entero, continuara
 * @param string el contexto del número que se pide
 * @return un double
 * 
*/
int parseInt(string contexto)
{
    bool flag = true;
    int numero;
    string entrada = "";
    do
    {
        cout << contexto << endl;
        getline(cin, entrada);
        try
        {
            numero = stoi(entrada);
            flag = false;
        }
        catch(const invalid_argument& e)
        {
            cout << "Opcion no valida" << endl;
        }
        catch(const out_of_range& e1)
        {
            std::cerr << e1.what() << "\n";
        }
    } while (flag);
    return numero;
};

/**
 * procedimiento que muestra el menú empezar nueva partida 
 * todos los requerimientos para empezar una nueva partida
 * @param controladorArchivo clase que contiene todos los métodos para ingresar a los archivos
 *   
*/
void menuEmpezarNueva(ControladorArchivo& controladorArchivo);
/**
 * procedimiento que muestra el menú empezar cargar partidas completas
 * todos los requerimientos para mostrar partidas ya terminadas
 * @param controladorArchivo clase que contiene todos los métodos para ingresar a los archivos
 *   
*/
void menuCargarCompleta(ControladorArchivo& controladorArchivo);
/**
 * procedimiento que muestra el menú Cargar una partida incompleta
 * todos los requerimientos para empezar una nueva partida
 * @param controladorArchivo clase que contiene todos los métodos para ingresar a los archivos
 *   
*/
void menuCargarIncompleta(ControladorArchivo& controladorArchivo);
/**
 * Función que pregunta al usuario si quiere  guardar una partida incompleta
 * @return true, si el usuario quiere guardar la partida, false lo contrario
 *   
*/
bool guardarPartida();


/**
 * función main
 */
int main() 
{

	ControladorArchivo controladorArchivos = ControladorArchivo();
	int difficult = 0;
	int firstPlayer = 0;
	int depth = 0;
	string gameName = ""; 
	
	bool flag = true;
	int opc = 0;
	while(flag)
	{
		controladorArchivos.cargarPartidasIncompleta();
		cout << "Bienvenido a: Connect-4 AI-Human" << endl
		<< "		Menu Connect 4" << endl
		<< EMPEZAR_NUEVA << ") Empezar nueva partida " << endl
		<< CARGAR_INCOMPLETA << ") Cargar partida incompleta " << endl
		<< VER_COMPLETA << ") Ver Partidas Completas " << endl
		<< SALIR << ") Salir del programa" << endl;
		opc = parseInt("\nIngrese una opcion: ");

		switch(opc)
		{
			case EMPEZAR_NUEVA:

				menuEmpezarNueva(controladorArchivos);
				break;

			case CARGAR_INCOMPLETA:
				menuCargarIncompleta(controladorArchivos);
				break;
			
			case VER_COMPLETA:
				menuCargarCompleta(controladorArchivos);
				break;
			
			case SALIR:
				flag = false;
				cout << "Ha salido del programa Que tenga un buen dia :>" << endl;
				break;
			
			default:
				cout << "Error al escoger una opcion, intente nuevamente..." << endl;
				break;
		}

	}
};



void menuCargarIncompleta(ControladorArchivo& cArch)
{
	if(cArch.getSizePartidasIncompleta() == 0)
	{
		cout << "No tienes partidas guardadas para jugar..." << endl;
		int pausa = parseInt("Apreta un numero para continuar");
		return;
	}
	GameController &game = cArch.escogerPartida();
	int guardar = game.playGame();
	bool guardarIn = true;
	switch (guardar)
	{
	case GameController::COMP:
		/* code */
		cArch.guardarPartidaCompleta(game);
		cout << "Se guardo la partida completa" << endl;
		break;

	case GameController::INCOMP:

		guardarIn = guardarPartida();
		if(guardarIn) 
		{
			cArch.guardarPartidaIncompleta(game);
			cout << "Se guardo la partida" << endl;
		}
		else 
		{
			cout << "No se guardo la partida" << endl;
		}
		break;
	default:
		cout << "Como entraste aca?" << endl;
		break;
	}
}



void menuCargarCompleta(ControladorArchivo& cArch)
{
	cout << "El historial completo de partidas completadas" << endl;
	cout << cArch.mostrarResultados() << endl;
};


bool guardarPartida()
{
    while(true)
    {
        int opc = 0;
        cout << "Desea guardar la partida?" << endl
        << "1) si" << endl 
        << "2) no" << endl;
        opc = parseInt("Ingrese una opcion");
        switch ((opc))
        {
            case 1:
            	cout << "Se guardara la partida" << endl;
                return true;
                
            case 2:
                cout << "No se guardara la partida " << endl;
                return false;
                
            default:
                cout << "Opcion no valida " << endl;
                break;
        }
    }
    return false;
}

void menuEmpezarNueva(ControladorArchivo& cArch)
{
	int difficult = 0;
	int firstPlayer = 0;
	int depth = 0;
	string gameName = "";
	cout << "Ha ingresado: Empezar partida nueva  " << endl << "Porfavor ingrese las caracteristicas de la partida" << endl;
	cout << "Ingrese el nombre de la partida" << endl;
	getline(cin,gameName);
	difficult = parseInt("Ingrese la dificultad del bot (1-Facil) (2-Intermedio) (3-Dificil)");
	if(difficult > 3 || difficult < 0)
	{
		cout << "Opcion incorrecta, dificultad por defecto (Intermedio)" << endl;
		difficult = GameController::MIDDLE;
	}
	firstPlayer = parseInt("Ingrese quien empezara la partida: (2-Usted) (1-BOT)");
	if(firstPlayer > 2 || firstPlayer < 1)
	{
		cout << "Opcion incorrecta,  por defecto empezara usted " << endl;
		firstPlayer = Solver::PLAYER;
	}
	depth = parseInt("Ingrese la profundidad del bot (1-8)");
	if(depth < 0 || depth > 8)
	{
		cout << "No le gustaria jugar con esa profundidad (la ia piensa mucho sus movimientos ^.^), profundidad por defecto (5)" << endl; 
		depth = 5;
	}
	cout << "Terminado, preparando la partida..." << endl;
	cout << "Recuerde que puede cancelar/guardar la partida escribiendo FIN/fin " << endl;
	cout << "ADVERTENCIA (Las partidas con final se guardan automaticamente)" << endl;

	GameController game = GameController(firstPlayer, depth, difficult, gameName, firstPlayer);
	int guardar = game.playGame();
	bool guardarIn = true;
	switch (guardar)
	{
	case GameController::COMP:
		/* code */
		cArch.guardarPartidaCompleta(game);
		cout << "Se guardo la partida completa" << endl;
		break;

	case GameController::INCOMP:

		guardarIn = guardarPartida();
		if(guardarIn) 
		{
			cArch.guardarPartidaIncompleta(game);
			cout << "Se guardo la partida" << endl;
		}
		else 
		{
			cout << "No se guardo la partida" << endl;
		}
		break;
	default:
		cout << "Como entraste aca?" << endl;
		break;
	}

};

