#include <iostream>
#include "Juego.h"

using namespace std;

int main() {
    int numJugadores;

    cout << "Bienvenido al juego de cartas!" << endl;
    cout << "Ingrese el número de jugadores: ";
    cin >> numJugadores;

    // Verifica que el número de jugadores sea válido
    if (numJugadores < 2) {
        cout << "Se necesita al menos 2 jugadores para jugar." << endl;
        return 1; // Finaliza si el número de jugadores no es válido
    }

    Juego juego(numJugadores); // Crear la instancia del juego

    juego.iniciarJuego(); // Iniciar el juego

    // Jugar rondas hasta que se haya completado el número de rondas
    for (int ronda = 0; ronda < juego.obtenerNumeroDeRondas(); ronda++) {
        juego.jugarRonda(); // Jugar una ronda
    }

    juego.determinarGanador(); // Mostrar quién es el ganador final

    return 0; // Fin del juego
}
