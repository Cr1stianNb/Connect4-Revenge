#ifndef CONTROLADOR_ARCHIVO_H
#define CONTROLADOR_ARCHIVO_H


#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "GameController.hpp"
using namespace std;

// Foward Declaration
// La definición del método esta en main
int parseInt(string);

/**
 * @class ControladorArchivo
 * Clase que controla los metodos requeridos para la gestión de archivos
 * Implementa constantes de clase para los archivos .csv
 * 
*/
class ControladorArchivo
{
    private:
        /**
         * @param juegosIncompletos Guarda toda la información de los juegos incompletos que existen en ControladorArchivo::ARCHIVO_CARGADO
        */
        vector<GameController> juegosIncompletos;
    
    public:
        /**
         * Se guarda el nombre de archivo de las partidas completadas
         * 
        */
        static const string ARCHIVO_GUARDADO;
        /**
         * Se gurada el nombre del archivo de las partidas Incompletas
        */
        static const string ARCHIVO_CARGADO;

        /**
         * Constructor de la clase
        */
        ControladorArchivo();
        /**
         * Destructor de la clase
        */
        ~ControladorArchivo();

        /**
         * Método que retorna en formato string todos los resultado del archivo de partidas completas 
         * @return retorna un string con todas las partidas completas, definiendo el tablero, dificultad, nombre del archivo, resultado
        */
        string mostrarResultados();

        /**
         * Método retorna un GameController de una partida incompleta en especifica que el usuario decidirá
         * 
         * Si no hay partidas guardada.
         * 
         * PRE-CONDICIÓN: Se debe verificar si existe partidas guardadas
         * @return la Instancia de GameController que representa el juego
         * 
        */
        GameController& escogerPartida();

        /**
         * Método que retorna las partidas incompletas en formato string 
         * @return las partidas incompletas del jugador
         * 
        */
        string mostrarPartidasIncompletas();

        /**
         * Método que guarda en el archivo de guardado una partida Completa
         * @param GameController el juego completado a guardar
         * PRE-CONDICIÓN El juego deberá ser terminado. 
        */
        void guardarPartidaCompleta(GameController&);

        /**
         * Método que guarda en el archivo una partida incompleta
         * 
         * @param GameController el juego incompleto a guardar
        */
        void guardarPartidaIncompleta(GameController&);

        /**
         * Método que carga las partidas completas del archivo y las guarda en un vector de GameController
        */
        void cargarPartidasIncompleta();
        /**
         * @return el tamaño del vector<GameController> 
        */
        int getSizePartidasIncompleta();




};




#endif