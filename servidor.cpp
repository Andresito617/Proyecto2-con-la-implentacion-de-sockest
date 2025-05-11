#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <sstream>
#include <winsock2.h>
#include "jugador.h"

#define PUERTO 8080

void jugar(SOCKET nuevo_socket) {
    // Crear mazo
    std::vector<Carta> mazo;
    std::vector<std::string> colores = {"rojo", "azul", "verde", "naranja"};

    // Llenar el mazo con las cartas
    for (const auto& color : colores) {
        for (int i = 1; i <= 6; ++i) {
            mazo.emplace_back(color, i);
        }
    }

    // Barajar mazo
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(mazo.begin(), mazo.end(), g);

    // Repartir cartas
for (int i = 0; i < 5; ++i) {
    servidorJugador.agregarCarta(mazo[i * 2]);
    clienteJugador.agregarCarta(mazo[i * 2 + 1]);
}

bool seguirJugando = true;

while (seguirJugando && servidorJugador.tieneCartas() && clienteJugador.tieneCartas()) {
    std::cout << "Tu mano:\n";
    servidorJugador.mostrarMano();

    int eleccionServidor;
    std::cout << "Selecciona tu carta (1-" << servidorJugador.cantidadCartas() << "): ";
    std::cin >> eleccionServidor;

    if (eleccionServidor < 1 || eleccionServidor > servidorJugador.cantidadCartas()) {
        std::cout << "Selección inválida.\n";
        continue;
    }

    Carta cartaServidor = servidorJugador.obtenerCarta(eleccionServidor - 1);
    servidorJugador.eliminarCarta(eleccionServidor - 1);

    // Lógica para procesar cartaCliente que recibirías del socket
    Carta cartaCliente = /* recibir carta desde cliente */;
    
    // Eliminar carta cliente
    for (int i = 0; i < clienteJugador.cantidadCartas(); ++i) {
        if (clienteJugador.obtenerCarta(i) == cartaCliente) {
            clienteJugador.eliminarCarta(i);
            break;
        }
    }

    // Lógica del juego
    while (seguirJugando && !servidorJugador.mano.empty() && !clienteJugador.mano.empty()) {
        std::cout << "\n--- RONDA " << ronda << " ---\n";
        servidorJugador.mostrarMano();

        // Elección de carta del servidor
        int eleccionServidor;
        std::cout << "Selecciona tu carta (1-" << servidorJugador.mano.size() << "): ";
        std::cin >> eleccionServidor;

        // Verificar que la elección del servidor sea válida
        if (eleccionServidor < 1 || eleccionServidor > servidorJugador.mano.size()) {
            std::cout << "Selección inválida, intenta de nuevo.\n";
            continue;  // Continuar sin avanzar si la elección es inválida
        }

        // Seleccionar la carta del servidor
        Carta cartaServidor = servidorJugador.mano[eleccionServidor - 1];
        servidorJugador.mano.erase(servidorJugador.mano.begin() + eleccionServidor - 1);

        // Enviar señal para que el cliente juegue
        std::string mensaje = "JUEGA";
        send(nuevo_socket, mensaje.c_str(), mensaje.size(), 0);

        // Recibir carta del cliente
        int bytesRecibidos = recv(nuevo_socket, buffer, 1024, 0);
        if (bytesRecibidos > 0) {
            std::istringstream iss(buffer);
            std::string colorCliente;
            int numeroCliente;
            iss >> colorCliente >> numeroCliente;
            Carta cartaCliente(colorCliente, numeroCliente);

            // Eliminar carta del cliente de su mano
            for (auto it = clienteJugador.mano.begin(); it != clienteJugador.mano.end(); ++it) {
                if (*it == cartaCliente) {
                    clienteJugador.mano.erase(it);
                    break;
                }
            }

            std::cout << "\nCarta del cliente: ";
            cartaCliente.mostrar();
            std::cout << "\nTu carta: ";
            cartaServidor.mostrar();
            std::cout << std::endl;

            // Comparar cartas
            if (cartaServidor.numero > cartaCliente.numero) {
                servidorJugador.puntaje++;
                std::cout << "¡Ganaste esta ronda!\n";
            } else if (cartaServidor.numero < cartaCliente.numero) {
                clienteJugador.puntaje++;
                std::cout << "El cliente gana esta ronda.\n";
            } else {
                std::cout << "Empate en esta ronda.\n";
            }

            std::cout << "Puntaje -> Servidor: " << servidorJugador.puntaje << " | Cliente: " << clienteJugador.puntaje << "\n";

            // Validar fin del juego
            if (servidorJugador.puntaje >= 5) {
                std::string fin = "VICTORIA_SERVIDOR";
                send(nuevo_socket, fin.c_str(), fin.size(), 0);
                std::cout << "¡Ganaste la partida!\n";
                seguirJugando = false;
            } else if (clienteJugador.puntaje >= 5) {
                std::string fin = "VICTORIA_CLIENTE";
                send(nuevo_socket, fin.c_str(), fin.size(), 0);
                std::cout << "El cliente ha ganado la partida.\n";
                seguirJugando = false;
            } else {
                std::string continuar = "CONTINUAR";
                send(nuevo_socket, continuar.c_str(), continuar.size(), 0);
            }
        }

        ronda++;
        memset(buffer, 0, sizeof(buffer));
    }
}

int main() {
    WSADATA wsaData;
    SOCKET servidor_socket, nuevo_socket;
    sockaddr_in servidor, cliente;

    WSAStartup(MAKEWORD(2, 2), &wsaData);
    servidor_socket = socket(AF_INET, SOCK_STREAM, 0);

    servidor.sin_family = AF_INET;
    servidor.sin_port = htons(PUERTO);
    servidor.sin_addr.s_addr = INADDR_ANY;

    bind(servidor_socket, (struct sockaddr*)&servidor, sizeof(servidor));
    listen(servidor_socket, 1);

    std::cout << "Esperando conexión del cliente...\n";
    int cliente_len = sizeof(cliente);
    nuevo_socket = accept(servidor_socket, (struct sockaddr*)&cliente, &cliente_len);
    std::cout << "Cliente conectado.\n";

    jugar(nuevo_socket);

    closesocket(nuevo_socket);
    closesocket(servidor_socket);
    WSACleanup();

    return 0;
}