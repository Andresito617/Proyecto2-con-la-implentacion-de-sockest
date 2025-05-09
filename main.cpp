#include <iostream>
#include "Juego.h"

using namespace std;

int main() {
    int numJugadores;

    cout << "Bienvenido al juego de cartas!" << endl;
    cout << "Ingrese el n�mero de jugadores: ";
    cin >> numJugadores;

    // Verifica que el n�mero de jugadores sea v�lido
    if (numJugadores < 2) {
        cout << "Se necesita al menos 2 jugadores para jugar." << endl;
        return 1; // Finaliza si el n�mero de jugadores no es v�lido
    }

    Juego juego(numJugadores); // Crear la instancia del juego

    juego.iniciarJuego(); // Iniciar el juego

    // Jugar rondas hasta que se haya completado el n�mero de rondas
    for (int ronda = 0; ronda < juego.obtenerNumeroDeRondas(); ronda++) {
        juego.jugarRonda(); // Jugar una ronda
    }

    juego.determinarGanador(); // Mostrar qui�n es el ganador final

    return 0; // Fin del juego
}