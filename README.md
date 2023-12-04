# Connect4-Revenge La IA Contraataca
Programa compila con el siguiente comando: <br>
g++ -o main.exe main.cpp <br>
Dentro del README del repositorio se debe incluir información sobre la
implementación, decisiones de diseño, resultados
# Un Programa para jugar contra una ia con dificultades <br>
## Para las decisiones de la IA se utilizo minimax con alpha, beta prunning <br>
Se decidio utilizar  alpha,beta prunning como una mejor en optimización del algoritmo minimax, para evitar propagar tableros que no tenian relevancia en el algoritmo
siendo muy efectiva para la optimizacion del juego, llegando a profundidades máximas de 8, sin esta implementación el programa corría solo con 4 de profundidad, la mitad de profundidad, lo cual tiene sentido debido
a la complejidad algoritmica de ambos 
### Para minimax: O(b^m)
### con alpha beta prunning: O(b^(m/2))
# Función Heuristica como reemplazo de estados terminales 
### Para que MiniMax funcionen correctamente en un juego de tablas, el algoritmo debe de llegar a un estado terminal (empate,ganada,perdida) para poder realizar un puntaje correcto
Sin embargo por problemas de optimización o rendimiento del programa minimax incluso con alpha beta prunning no llegaba a tal profundidad, debido a la gran cantidad de combinaciones existentes en el tablero 
4.531.985.219.092 posibles tableros existen en total (John Tromp). <br>
Por ello se utilizo una función heuristica como apoyo, para poder calcular Tableros sin la necesidad de ser terminales (estado final de juego), calculando por combinación de fichas, para todo el tablero y definiendo 
una valor a potencial a cada jugada, cada jugada tendra ponderado dependiendo de la importancia de la jugada (por ejemplo un movimiento ganador).




