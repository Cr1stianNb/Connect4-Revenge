
#ifndef GAME_CONTROLLER_HPP
#define GAME_CONTROLLER_HPP

#include <iostream>
#include "Solver.hpp"
#include <cstdlib>

//Foward DEclaration
int parseInt(string);


/**
 * @class GameController
 * Clase que contiene todas las funcionalidas para recrear un tablero de connect 4
*/
class GameController
{
    private:
        /**
         * Nombre del tablero
        */
        string gameName;
        /**
         * Formato en string del tablero
        */
        string seq;

        int difficult; // Dificultad
        int depth; // profundidad del bot
        bool isGameOver; // si termino la partida
        int moves; // movimientos de la partida
        int currentPlayer; // jugador actual en la partida
        int first; // Primero en jugar la partida
        Solver solver; // Sinstancia de solver para minimax y otras funcionalidades
        vector<vector<int>> board; // tablero de la partida

    public:

        static const int EASY = 1, MIDDLE = 2, HARD = 3;
        static const int INCOMP = 0, COMP = 1;


        

        /**
         * Constructor de la clase GameController
        */
        GameController(int currentPlayer = Solver::PLAYER, int depth = 5, int difficult = 1, string gameName = "Nombre_Por_Defecto", int firstPlayer = Solver::PLAYER) 
        :solver(), 
        board(Solver::ALTO, vector<int>(Solver::ANCHO)), 
        isGameOver(false), 
        currentPlayer(currentPlayer), 
        first(firstPlayer),
        moves(0), 
        depth(depth), 
        difficult(difficult), 
        gameName(gameName), seq("")
        {
            Solver::fillWith0(board);
        };

        
        void setFirst(int first)
        {
            this->first = first;
        }

        /**
         *  metodo para que el jugador (Usuario) realize una jugada
         * @return la cl¿olumna a jugar, si es -1 entonces es porque quiere finalizar la partida
         */
        int moverJugador() {

            string move = "";
            int moveInt = 0;
            bool flag = true;
            while(flag)
            {
                cout << "Escoge una columna (FIN/fin para salir de la partida)" << endl;
                getline(cin,move);
                if(move == "FIN" || move == "fin")
                {
                    return -1;
                }
                else 
                {
                   try 
                    {
                        moveInt = stoi(move);
                        if(moveInt < 0)
                        {
                            cout << "Opcion no valida, debe ser entre 0 y 6" << endl;
                        }
                        else if(moveInt > 6)
                        {
                            cout << "Opcion no valida, debe ser menor que 6" << endl;
                        }
                        else if(!solver.canPlay(board,moveInt))
                        {
                            cout << "Opcion no valida, no debe estar llena" << endl;
                        }
                        else 
                        {
                            flag = false;
                        }
                
                    }
                    catch(const invalid_argument& e)
                    {
                        cout << "Opcion no valida" << endl;
                    }
                    catch(const out_of_range& e1)
                    {
                        std::cerr << e1.what() << "\n";
                    }
                }

            }
            return moveInt;
        }


        string getGameName()
        {
            return gameName;
        }

        int getDifficult()
        {
            return difficult;
        }

        string getSeq()
        {
            return seq;
        }

        int getCurrentPlayer()
        {
            return currentPlayer;
        }

        int getDepth()
        {
            return depth;
        }

        int getFirst()
        {
            return first;
        }
        
        /**
         * Copia el tablero a partir de una secuencia de string
        */
        bool copyBoard(string seq)
        {
            if(solver.fill(board, seq, first) == seq.size())
            {
                this->seq = seq;
                return true;
            }
            return false;
        }

        /**
         * 
         * Movimiento de la IA, utiliza minimax
         * Y dependera de cual es la dificultad de la ia
         * @return la columna a jugar la ia
         */
        int aiMove() 
        {
            cout << "Calculando mov.." << endl;
            int random;
            int colR = rand() % 7;
            switch (difficult)
            {
            case EASY: // depth = 1, escoge un col random 
                random = (std::rand()) % 3 + 1;

                if(random != 1 && solver.canPlay(board, colR))
                {
                    return colR;
                } 
                else 
                {
                    return solver.miniMax(board, 1, 0 - INT_MAX, INT_MAX, Solver::AI)[1];

                }
            case MIDDLE:
                random = std::rand() % 4 + 1;
                if(random == 1 && solver.canPlay(board, colR))
                {
                    return (colR);
                }
                else 
                {
                    return solver.miniMax(board, depth, 0 - INT_MAX, INT_MAX, Solver::AI)[1];
                }
            
            case HARD:
                return solver.miniMax(board, depth, 0 - INT_MAX, INT_MAX, Solver::AI)[1];

            default:

                 return solver.miniMax(board, depth, 0 - INT_MAX, INT_MAX, Solver::AI)[1];
            }
        }

       

        /**
         * Metodo que inicia el juego
         * @return un entero que significa si el jugador quiere guardar la partido o si termino la partida
         */
        int playGame() {
            int col = 0;
            cout << printBoard();
            while (!isGameOver) 
            {
                if (currentPlayer == Solver::AI) 
                { 
                    col = aiMove();
                    solver.playCol(board, col, Solver::AI);
                }
                else if (currentPlayer == Solver::PLAYER) 
                { 
                    col = moverJugador();
                    if(col == -1) return INCOMP; // Si es -1 entonces se termina el juego
                    solver.playCol(board, col, Solver::PLAYER);
                }
                else if (moves == Solver::ALTO * Solver::ANCHO) // Empate
                { 
                    isGameOver = true;
                }
                seq += to_string((col+1)); // la secuencia en string del tablero
                isGameOver = solver.winningMove(board, currentPlayer); // si es true , entonces gano el jugador actual
                currentPlayer = (currentPlayer == 1) ? 2 : 1;
                moves++; 
                cout << endl;
                cout << printBoard();
            }
            if (moves == Solver::ALTO * Solver::ANCHO) 
            {
                cout << "Empate~~~!" << endl;
            }
            else 
            { 
                cout << ((currentPlayer == Solver::PLAYER) ? "IA GANA!" : "Jugador Gana!") << endl;
            }
            return COMP;
        }

        /**
         * 
         * @return retorna un string con el tablero
         * 
         */
        string printBoard() 
        {
            string text = "";
            for ( int i = 0; i < Solver::ANCHO; i++) 
            {
                text +=  " " + to_string(i);
            }
            text += "\n-----------------\n"; 
            for ( int r = 0; r < Solver::ALTO; r++) 
            {
                for ( int c = 0; c < Solver::ANCHO; c++) 
                {
                    text += "|";

                    switch (board[Solver::ALTO - r - 1][c]) 
                    {
                        case 0: text += " "; break; 
                        case 1: text += "O"; break;
                        case 2: text += "X"; break; 
                    }
                    if (c + 1 == Solver::ANCHO) text += "|";
                }
                text += "\n";
            }
            text +="-----------------\n\n";
            return text;
        }

        ~GameController()
        {

        };
};
#endif