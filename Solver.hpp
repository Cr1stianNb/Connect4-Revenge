

#ifndef SOLVER_HPP
#define SOLVER_HPP

#include <stdio.h>
#include <vector>
#include <limits.h>
#include <array>
#include <sstream>
using namespace std;




/**
 * @class Solver
 * Clase que se utiliza como un auxiliar para realizar todos los calculos en el tablero 
 * Implementa Atributos de clases publicos
 * 
*/
class Solver
{  
      public:
        /** Parametros de clase definen el Alto del tablero y el ancho del tablero*/
        static const int ALTO = 6, ANCHO = 7;
        static const int AI = 1, PLAYER = 2;
        Solver()
        {
        }
        /**
         * Método de clase que Rellena de 0 un vector de vector de int por parametro
         * @param board el tablero a llenar de 0
        */
        static void fillWith0(vector<vector<int>> &board)
        {
            for(int i=0; i<ALTO;i++)
            {
                for(int j=0; j<ANCHO;j++)
                {
                    board[i][j] = 0;
                }
            }
        }

        /**
         * Método que rellena un vector de vector de int a partir de una secuencia de string 
         * @param board tablero a rellenar 
         * @param seq secuencia a rellenar , por ejemplo: 111234 
         * (los 1 serían en la columna 1 y así sucesivamente, los primeros numeros en la secuencia significa que son las primeras jugadas)
         * @param firstIsHuman Parametro para identificar quien empezo la partida, si firstHuman es igual a Solver::Player entonces player empezo la partida
        */
        int fill(vector<vector<int>>& board, string seq, int firstIsHuman) 
        {

            int currentP = firstIsHuman;
         
            for( int i = 0; i < seq.size(); i++) 
            {
                int col = seq[i] - '1'; 
                if(col < 0 || col >= Solver::ANCHO || !canPlay(board, col)) return i; // Movimiento invalido, retornar en que indice fallo
                playCol(board, col, (currentP)); // Jugar 
                currentP = (currentP == 1 ? 2 : 1);
            } 
            return seq.size();
        }
        /**
         * Método que verifica si en el tablero existe una posición de victoria 
         * @param board vector de vector de int, simula el tablero 
         * @param playerToCheck jugador a realizar la revisión
         * @return true si existe 4 piezas conectadas seguidas
        */
        bool winningMove(vector<vector<int>>& board,  int playerToCheck)
        {
            int secuenciaPiezas = 0; 

            // Revisa Horizontalmente para cada fila 
            for (int col = 0; col < ANCHO - 3; col++) 
            { 
                for (int fila = 0; fila < ALTO; fila++) 
                { 
                    for (int i = 0; i < 4; i++) 
                    { 
                        if ((int)board[fila][col + i] == playerToCheck) 
                        { 
                            secuenciaPiezas++; 
                        }
                        if (secuenciaPiezas == 4)  return true; 
                    }
                    secuenciaPiezas = 0; 
                }
            }
            // Revisa Verticalmente
            for (int col = 0; col < ANCHO; col++) 
            {
                for (int fila = 0; fila < ALTO - 3; fila++) 
                {
                    for (int i = 0; i < 4; i++) 
                    {
                        if ((int)board[fila + i][col] == playerToCheck) 
                        {
                            secuenciaPiezas++;
                        }
                        if (secuenciaPiezas == 4) return true; 
                    }
                    secuenciaPiezas = 0;
                }
            }
            // Diegonal para abajo
            for (int col = 0; col < ANCHO - 3; col++) 
            {
                for (int fila = 3; fila < ALTO; fila++) 
                {
                    for (int i = 0; i < 4; i++) 
                    {
                        if ((int)board[fila - i][col + i] == playerToCheck) 
                        {
                            secuenciaPiezas++;
                        }
                        if (secuenciaPiezas == 4) return true;
                    }
                    secuenciaPiezas = 0;
                }
            }

            // Diagonal para arriba
            for ( int col = 0; col < ANCHO - 3; col++)
             {
                for ( int fila = 0; fila < ALTO - 3; fila++) 
                {
                    for (int i = 0; i < 4; i++) 
                    {
                        if (( int)board[fila + i][col + i] ==  playerToCheck) 
                        {
                            secuenciaPiezas++;
                        }
                        if (secuenciaPiezas == 4) return true;
                    }
                    secuenciaPiezas = 0;
                }
            }
            return false; // Entonces aún no gana
        }

        /**
         * Método que revisa si se puede jugar en una columna en especifica 
         * @param board vector de vectores de int representa el tablero del juego
         * @param col  entero que representa la columna a jugar, se verifica si es un movimiento factible
         * @return true si hay espacio y es un movimiento factible, false lo contrario
         * 
        */
        bool canPlay(vector<vector<int>>& board, int col)
        {
            if(col < 0 || col > ANCHO) return false;
            return board[ALTO-1][col] == 0; // 0 significa vacio
        }


        /**
         * Método de clase que duplica un vector por parametro 
         * 
         * @param board - el tablero a copiar
         * @return un tablero copia con las mismas dimensiones
         */
        static vector<vector<int>> copyBoard(vector<vector<int>> board) 
        {
            vector<vector<int>> newBoard(ALTO, vector<int>(ANCHO));
            for ( int fila = 0; fila < ALTO; fila++) 
            {
                for ( int col = 0; col < ANCHO; col++) 
                {
                    newBoard[fila][col] = board[fila][col]; // just straight copy
                }
            }
            return newBoard;
        }


        /**
         * Método que hace el movimiento en una tablero, en una columna y por un jugador
         * Pre-Requisito, se debe verificar si la columna es valida
         * @param board - El tablero a realizar el mov
         * @param col - columna a realizar el movimiento
         * @param currentPlayer - el jugador que hace el movimiento
         */
        void playCol(vector<vector<int>>& board, int col,  int currentPlayer) 
        {
            for (int fila = 0; fila < ALTO; fila++) 
            {
                if (board[fila][col] == 0) 
                {
                    board[fila][col] = currentPlayer; 
                    break;
                }
            }
        }


        /**
         * Implementación de MiniMax utilizando poda (beta y alfa) para optimización de la busca al mejor tablero
         * Por motivos de optimización la puntuación de cada posicion del tablero no se hizo llegando a un estado terminal del tablero
         * Se utilizo para una profundidad especifica por el parametro depth, siendo los tableros terminales los tableros que llegan a esa  profundidad
         * Para esos tableros "Terminales" se utilizo una función heuristica que calcula la bondad del tablero actual para la ia, 
         * la ia busca maximizar el tablero y el jugador minimizar este score, 
         * La función heuristica revisa para cada fila y columna la cantidad de fichas unidas para IA, PLAYER, y analiza los espacios vacios
         * Con esto determina que tan buena es el score para la ia, por ejemplo si en un tablero la funcion heuristica reviso que existe 3 fichas de ia juntas entonces
         * asignara un puntaje mayor que a un tablero que no tiene esta opcion 
         * @param board tablero inicial
         * @param depth  profundidad maxima del arbol
         * @param alfa prunning
         * @param beta prunning
         * @param currentPlayer jugador actual a realizar el movimiento en el tablero
         *
         * 
        */
         array<int, 2> miniMax(vector<vector<int> > &board, int depth, int alfa, int beta, int currentPlayer) 
         {
         
            if(depth == 0 || depth >= (ANCHO * ALTO)) 
            {
                return array<int, 2>{getScore(board, AI), -1}; // Get el score del tablero para la ia, solo de la IA porque minimax se utilizara para la IA, entonces 
                                                            // max buscara maximizar este score mientras que min (el jugador contrario) buscara minimizar el score de la ia
            }
            if (currentPlayer == AI) 
            { 
                array<int, 2> bestMov = {INT_MIN, -1};
                if (winningMove(board, PLAYER)) return bestMov;

                for (int col = 0; col < ANCHO; col++)  // Para cada hijo del tablero (En este caso para cada columna)
                {    
                    if (canPlay(board,col)) // Si no esta completa contarla como hijo
                    { 
                        vector<vector<int> > newBoard = Solver::copyBoard(board); 
                        playCol(newBoard, col, currentPlayer); // Hcer el movimiento 
                        int score = miniMax(newBoard, depth - 1, alfa, beta, PLAYER)[0]; // Revisar el score de ese movimiento
                        if (score > bestMov[0]) // Revisa si el movimiento que hizo es mejor al que teniamos
                        { 
                            bestMov = {score, col};
                        }
                        alfa = max(alfa, bestMov[0]); // alfa 
                        if (alfa >= beta) break; 
                        // Podar si alfa es mayor que beta, esto es debido a que 
                        // Ya se encontro un valor por el cual min se va ir (beta), entonces no vale la pena para max buscar un valor mayor si será rechazado
                        // De todas maneras reduciendo la busqueda en el "arbol"
                    }
                }
                return bestMov; 
            }
            else 
            {
                array<int, 2> bestMov = {INT_MAX, -1}; 

                if (winningMove(board, AI)) 
                {
                    return bestMov; 
                }
                for (int col = 0; col < ANCHO; col++) 
                {
                    if (board[ALTO - 1][col] == 0) 
                    {
                        vector<vector<int> > newBoard = Solver::copyBoard(board);
                        playCol(newBoard, col, currentPlayer);
                        int score = miniMax(newBoard, depth - 1, alfa, beta, AI)[0];
                        if (score < bestMov[0]) 
                        {
                            bestMov = {score, (int)col};
                        }
                        beta = min(beta, bestMov[0]);
                        if (alfa >= beta) break;
                        // Lo mismo para min, si ya se encontro un valor alpha para max entonces será en vano seguir buscando movimientos mas pequeños que alpha
                        // porque max ya encontro un buen score

                    }
                }
                return bestMov;
            }
        }

        /**
         *  Método que obtiene un valor "heuristico" del tablero, un método que busca la bondad del actual tablero
         *  Revisando la cantidad de fichas de jugador actual que se entrega por parametro 
         *  Busca el score para cadad combinacion de 4 posiciones del tablero y va acumulando el score para conseguir el valor del tablero actual 
         *  @param board , el tablero a revisar el puntaje
         *  @param currentPlayer , el jugador a sacar el puntaje del tablero
         */
         int getScore(vector<vector<int>> board, int currentPlayer) 
         {
            int score = 0;
            vector<int> filas(ANCHO);
            vector<int> columnas(ALTO);
            vector<int> set(4); // set de 4 posiciones, se ira por todas las posiciones de 4 pos seguidas, se caluclara el heur y se retorna al final

            // Secuencia de 4 posiciones horizontalmente
            for (int fila = 0; fila < ALTO; fila++) 
            {
                for (int col = 0; col < ANCHO; col++) 
                {
                    filas[col] = board[fila][col]; // this is a distinct row alone
                }
                for (int col = 0; col < ANCHO - 3; col++) 
                {
                    for (int i = 0; i < 4; i++) 
                    {
                        set[i] = filas[col + i]; // for each possible "set" of 4 spots from that row
                    }
                    score += scoreSet(set, currentPlayer); // find score
                }
            }
            // vertical
            for (int col = 0; col < ANCHO; col++) 
            {
                for (int fila = 0; fila < ALTO; fila++) 
                {
                    columnas[fila] = board[fila][col];
                }
                for (int fila = 0; fila < ALTO - 3; fila++) 
                {
                    for (int i = 0; i < 4; i++) 
                    {
                        set[i] = columnas[fila + i];
                    }
                    score += scoreSet(set, currentPlayer);
                }
            }
            // diagonal
            for (int fila = 0; fila < ALTO - 3; fila++) 
            {
                for (int col = 0; col < ANCHO; col++) 
                {
                    filas[col] = board[fila][col];
                }
                for (int col = 0; col < ANCHO - 3; col++)
                {
                    for (int i = 0; i < 4; i++) 
                    {
                        set[i] = board[fila + i][col + i];
                    }
                    score += scoreSet(set, currentPlayer);
                }
            }
            // diagonal
            for (int fila = 0; fila < ALTO - 3; fila++) 
            {
                for (int col = 0; col < ANCHO; col++) 
                {
                    filas[col] = board[fila][col];
                }
                for (int col = 0; col < ANCHO - 3; col++) 
                {
                    for (int i = 0; i < 4; i++) 
                    {
                        set[i] = board[fila + 3 - i][col + i];
                    }
                    score += scoreSet(set, currentPlayer);
                }
            }
            return score;
        }

        /**
         * 
         * @param vector - vector de 4 pos, representando una parte del tablero
         * @param currentPlayer - jugador actual
         * @return el score del vector de 4 posiciones que representa una parte del tablero
         */
         int scoreSet(vector<int> vector,  int currentPlayer) 
         {
            int buenas = 0; 
            int malas = 0; 
            int empty = 0; 
            for (int i = 0; i < vector.size(); i++) 
            { 
                buenas += (vector[i] == currentPlayer) ? 1 : 0;
                malas += (vector[i] == PLAYER || vector[i] == AI) ? 1 : 0;
                empty += (vector[i] == 0) ? 1 : 0;
            }

            malas -= buenas;
            return heuristica(buenas, malas, empty);
        }

        /**
         * Funcion heristica que determina por posiciones cuantas buenas,malas existen y les da un valor
         * Los parametros se calculan previamente y determina la cantidad de fichas para un set de 4 posiciones, 
         * Por ejemplo si en la primera columna del tablero es:
         * 1°Col
         * -
         * -
         * 0
         * X
         * X
         * X 
         * Si la ia es el O entonces la funcion calcularar como: 
         *      - buenas: 0
         *      - malas:3
         *      -vacia: 1 
         * El rival puede ganar al siguiente jugada, entonces le asignara un valor negativo para que con minimax no pueda llegar a esa posicion o bloquear
         * 
         * @param buenas - fichas del jugador a calcular
         * @param malas - fichas del rival
         * @param vacias - vacio
         * @return - the score as tabulated
         */
         int heuristica( int buenas,  int malas,  int vacias) 
         {
            int score = 0;
            if (buenas == 4) score += 500001;// Primero revisar si es mov ganador

            else if (buenas == 3 && vacias == 1)    score += 5000;

            else if (buenas == 2 && vacias == 2)    score += 500;

            else if (malas == 2 && vacias == 2)     score -= 501;

            else if (malas == 3 && vacias == 1)     score -= 5001;

            else if (malas == 4) { score -= 500000; } // Rival puede ganar con este set 
            return score;
        }
        ~Solver()
        {

        }
};


#endif