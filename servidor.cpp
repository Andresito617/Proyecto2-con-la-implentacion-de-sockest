#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <winsock2.h>
#include <ctime>
#include "juego.h"  // Incluir tu clase Juego
#include "jugador.h" // Incluir la clase Jugador, si la tienes

#pragma comment(lib, "ws2_32.lib")

#define PORT 8080
#define MAX_PLAYERS 4

using namespace std;

void gestionarJugador(SOCKET clienteSock, int jugadorID, vector<Jugador>& jugadores, mutex& mtx, Juego& juego);

int main() {
    WSADATA wsaData;
    SOCKET serverSock, clientSock;
    struct sockaddr_in server, client;
    int addrLen = sizeof(client);

    // Inicializar Winsock
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    // Crear socket
    serverSock = socket(AF_INET, SOCK_STREAM, 0);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    // Enlazar y escuchar
    bind(serverSock, (struct sockaddr*)&server, sizeof(server));
    listen(serverSock, 3);

    vector<thread> hilos;
    vector<Jugador> jugadores(MAX_PLAYERS);  // Jugadores del juego
    mutex mtx;

    Juego juego(MAX_PLAYERS);  // Crear el juego

    cout << "Servidor esperando conexiones..." << endl;

    // Esperar conexiones de jugadores
    for (int i = 0; i < MAX_PLAYERS; i++) {
        clientSock = accept(serverSock, (struct sockaddr*)&client, &addrLen);
        cout << "Jugador " << i + 1 << " conectado." << endl;

        // Asignar un hilo para gestionar a cada jugador
        hilos.push_back(thread(gestionarJugador, clientSock, i, ref(jugadores), ref(mtx), ref(juego)));
    }

    // Esperar que todos los hilos terminen
    for (auto& t : hilos) {
        t.join();
    }

    closesocket(serverSock);
    WSACleanup();

    return 0;
}

void gestionarJugador(SOCKET clienteSock, int jugadorID, vector<Jugador>& jugadores, mutex& mtx, Juego& juego) {
    // Aquí gestionas la interacción con el jugador en el servidor
    // Enviar el estado del juego, cartas y recibir las jugadas
    char buffer[1024];
    while (true) {
        // Recibir mensaje del cliente (la jugada)
        int recibidos = recv(clienteSock, buffer, sizeof(buffer), 0);
        if (recibidos == SOCKET_ERROR) {
            cout << "Error al recibir mensaje del jugador." << endl;
            break;
        }

        buffer[recibidos] = '\0'; // Asegurarse que el buffer sea una cadena válida
        cout << "Jugador " << jugadorID + 1 << " jugó: " << buffer << endl;

        // Procesar la jugada y actualizar el estado del juego
        mtx.lock();
        // Actualizar el juego (ejemplo: agregar la jugada al juego)
        // juego.jugarRonda(); // Aquí iría la lógica para continuar la ronda
        mtx.unlock();

        // Enviar el estado actualizado del juego al cliente
        send(clienteSock, "Estado del juego actualizado", 26, 0);  // Simulando un estado
    }
}