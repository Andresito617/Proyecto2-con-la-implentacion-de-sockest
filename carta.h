#pragma #ifndef CARTA_H
#define CARTA_H

#include <string>

class Carta {
public:
    std::string color;
    int numero;

    Carta(std::string color, int numero);
    void mostrar() const;
    bool operator==(const Carta& otraCarta) const;
};

#endif // CARTA_Honce
