#include <iostream>
#include <winsock2.h>
#include <ctime>

#pragma comment(lib, "ws2_32.lib")

#define PORT 8080
#define SERVER "127.0.0.1"

using namespace std;

void jugar(SOCKET sock);

int main() {
    WSADATA wsaData;
    SOCKET sock;
    struct sockaddr_in server;

    // Inicializar Winsock
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    // Crear socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(SERVER);
    server.sin_port = htons(PORT);

    if (connect(sock, (struct sockaddr*)&server, sizeof(server)) == -1) {
        cerr << "Conexión fallida!" << endl;
        return -1;
    }

    cout << "Conectado al servidor!" << endl;

    jugar(sock);

    closesocket(sock);
    WSACleanup();

    return 0;
}

void jugar(SOCKET sock) {
    char buffer[1024];
    int jugada;

    while (true) {
        // Mostrar la mano del jugador y pedir la jugada
        cout << "Elige una carta para jugar: ";
        cin >> jugada;

        // Enviar jugada al servidor
        snprintf(buffer, sizeof(buffer), "%d", jugada); // Convertir jugada a cadena
        send(sock, buffer, strlen(buffer), 0);

        // Recibir estado actualizado del juego
        int recibidos = recv(sock, buffer, sizeof(buffer), 0);
        buffer[recibidos] = '\0';
        cout << "Estado del juego: " << buffer << endl;

        // Aquí se puede agregar lógica para terminar el juego si el jugador gana o termina
    }
}
