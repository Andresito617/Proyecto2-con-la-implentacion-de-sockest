#include "Jugador.h"
#include <iostream>

void Jugador::mostrarMano() const {
    for (size_t i = 0; i < mano.size(); ++i) {
        std::cout << i + 1 << ". ";
        mano[i].mostrar();
    }
}

void Jugador::agregarCarta(const Carta& carta) {
    mano.push_back(carta);
}

Carta Jugador::obtenerCarta(int indice) const {
    return mano[indice];
}

void Jugador::eliminarCarta(int indice) {
    mano.erase(mano.begin() + indice);
}

int Jugador::cantidadCartas() const {
    return mano.size();
}

bool Jugador::tieneCartas() const {
    return !mano.empty();
}
