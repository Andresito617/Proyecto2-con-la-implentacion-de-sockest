#ifndef CARTA_H
#define CARTA_H

#include <string>
#include <iostream>
using namespace std;

class Carta {
public:
    string color;
    int numero;
    Carta(string c, int n) : color(c), numero(n) {}
    void mostrar() const {
        cout << "Carta: " << color << " " << numero << endl;
    }
    bool operator==(const Carta& otra) const {
        return color == otra.color && numero == otra.numero;
    }
};

#endif // CARTA_H
