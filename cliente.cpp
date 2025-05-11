#include <iostream>
#include <string>
#include <winsock2.h>
#include <sstream>
#include "jugador.h"

#define PUERTO 8080

void jugar(SOCKET cliente_socket) {
    char buffer[1024];

    bool seguirJugando = true;
    int ronda = 1;

    while (seguirJugando) {
        // Recibir señal para que el cliente juegue
        int bytesRecibidos = recv(cliente_socket, buffer, 1024, 0);
        std::string mensaje(buffer);
        if (bytesRecibidos > 0 && mensaje == "JUEGA") {
            // Mostrar la mano del cliente
            Jugador clienteJugador;
            clienteJugador.mostrarMano();

            // Elección de carta del cliente
            int eleccionCliente;
            std::cout << "Selecciona tu carta (1-" << clienteJugador.mano.size() << "): ";
            std::cin >> eleccionCliente;

            // Verificar que la elección del cliente sea válida
            if (eleccionCliente < 1 || eleccionCliente > clienteJugador.mano.size()) {
                std::cout << "Selección inválida, intenta de nuevo.\n";
                continue;
            }

            // Seleccionar carta
            Carta cartaCliente = clienteJugador.mano[eleccionCliente - 1];
            clienteJugador.mano.erase(clienteJugador.mano.begin() + eleccionCliente - 1);

            // Enviar carta al servidor
            std::ostringstream oss;
            oss << cartaCliente.color << " " << cartaCliente.numero;
            std::string mensajeCarta = oss.str();
            send(cliente_socket, mensajeCarta.c_str(), mensajeCarta.size(), 0);

            // Recibir mensaje de continuación o fin del juego
            bytesRecibidos = recv(cliente_socket, buffer, 1024, 0);
            std::string respuesta(buffer);

            if (respuesta == "VICTORIA_SERVIDOR") {
                std::cout << "El servidor ha ganado la partida.\n";
                seguirJugando = false;
            } else if (respuesta == "VICTORIA_CLIENTE") {
                std::cout << "¡Has ganado la partida!\n";
                seguirJugando = false;
            } else if (respuesta == "CONTINUAR") {
                std::cout << "La partida continúa...\n";
            }
        }

        memset(buffer, 0, sizeof(buffer));
    }
}

int main() {
    WSADATA wsaData;
    SOCKET cliente_socket;
    sockaddr_in servidor;

    WSAStartup(MAKEWORD(2, 2), &wsaData);
    cliente_socket = socket(AF_INET, SOCK_STREAM, 0);

    servidor.sin_family = AF_INET;
    servidor.sin_port = htons(PUERTO);
    servidor.sin_addr.s_addr = inet_addr("192.168.20.116"); // Cambia por la IP del servidor

    connect(cliente_socket, (struct sockaddr*)&servidor, sizeof(servidor));

    std::cout << "Conectado al servidor.\n";
    jugar(cliente_socket);

    closesocket(cliente_socket);
    WSACleanup();

    return 0;
}