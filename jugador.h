#pragma once#ifndef JUGADOR_H
#define JUGADOR_H

#include <vector>
#include "carta.h"

class Jugador {
public:
    std::vector<Carta> mano;
    int puntaje;

    void mostrarMano() const;
};

#endif // JUGADOR_H
