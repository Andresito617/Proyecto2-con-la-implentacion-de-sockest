#include "jugador.h"
#include <iostream>

void Jugador::mostrarMano() const {
    std::cout << "Tus cartas son: ";
    for (size_t i = 0; i < mano.size(); ++i) {
        std::cout << (i + 1) << ": ";
        mano[i].mostrar();
        std::cout << " "; // A�adimos un espacio entre cartas
    }
    std::cout << std::endl << std::endl; // Salto de l�nea al final de la mano
}