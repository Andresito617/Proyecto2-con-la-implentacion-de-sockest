#ifndef JUEGO_H
#define JUEGO_H

#include <vector>
#include <string>
#include <mutex>

class Jugador {
public:
    int id;
    std::string nombre;
    std::vector<int> mano; // Cartas del jugador

    Jugador(int id, const std::string& nombre);
    int jugarCarta(int cartaIndex); // Función para jugar una carta
};

class Juego {
private:
    std::vector<Jugador> jugadores;
    int turno;
    std::mutex mtx; // Mutex para sincronizar el acceso al juego

public:
    Juego(int numJugadores);
    void mostrarEstado(); // Mostrar el estado del juego
    void jugar(int jugadorID, int cartaIndex); // El jugador juega su carta
    void siguienteTurno(); // Cambiar el turno
    int getTurno(); // Obtener el turno actual
    Jugador& getJugador(int jugadorID); // Obtener un jugador por su ID
};

#endif // JUEGO_H#pragma once
