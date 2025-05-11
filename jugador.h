#ifndef JUGADOR_H
#define JUGADOR_H

#include "Carta.h"
#include <vector>
using namespace std;

class Jugador {
public:
    void mostrarMano() const;
    vector<Carta> mano;
    void agregarCarta(const Carta& carta);
    Carta obtenerCarta(int indice) const;
    void eliminarCarta(int indice);
    int cantidadCartas() const;
    bool tieneCartas() const;
    int puntaje = 0;
};

#endif