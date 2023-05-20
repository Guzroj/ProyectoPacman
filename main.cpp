#include <QApplication>
#include "MatrizL.h"
#define WIDTH 608
#define HEIGHT 702
#define size_x 21
#define size_y 19

#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>

/**
 * @brief SocketServer
 * Comunica la aplicacion con el qt creator
 */
void SocketServer() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    // Crear socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        std::cerr << "Error al crear socket" << std::endl;
        return;
    }

    // Opción de socket para reutilizar la dirección
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        std::cerr << "Error en setsockopt" << std::endl;
        return;
    }

    // Configurar dirección del socket
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(5001);

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt))) {
        std::cerr << "Error en setsockopt" << std::endl;
        return;
    }


    // Enlazar socket a la dirección y puerto especificados
    if (bind(server_fd, (struct sockaddr *) &address, sizeof(address)) < 0) {
        std::cerr << "Error en bind" << std::endl;
        return;
    }

    // Escuchar conexiones entrantes
    if (listen(server_fd, 3) < 0) {
        std::cerr << "Error en listen" << std::endl;
        return;
    }

    std::cout << "Servidor en espera de conexiones..." << std::endl;


    // Aceptar nueva conexión
    if ((new_socket = accept(server_fd, (struct sockaddr *) &address, (socklen_t *) &addrlen)) < 0) {
        std::cerr << "Error en accept" << std::endl;
        return;
    }

    std::cout << "Nueva conexión aceptada" << std::endl;

        // Procesar mensajes entrantes
        char buffer[1024] = {0};
        int valread = read(new_socket, buffer, 1024);

        if (valread <= 0) {
            std::cout << "Cliente desconectado" << std::endl;
            close(new_socket);
            return;
        }

    std::cout << "Mensaje recibido: " << buffer << std::endl;

    char respuesta[] = "Mensaje recibido.\n";
    send(new_socket, respuesta, sizeof(respuesta), 0);
    std::cout << "Respuesta: " << respuesta << std::endl;

    if (close(server_fd) == -1) {
        std::cerr << "Error al cerrar el socket: " << std::strerror(errno) << std::endl;
        return;
    }
    if (close(new_socket) == -1) {
        std::cerr << "Error al cerrar el socket: " << std::strerror(errno) << std::endl;
        return;
    }
}
//Comentario hecho para probar repositorio
//Otro comentario solo para probar
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Matriz *loop;
    if (argc == 1 || argc > 2)
    {
        std::cout << "Invalid number of parameters.\n";
        std::cout << "Usage: ./pacman maps/map.txt\n";
        exit(0);
    }

    loop = new Matriz(argv[1]);

    loop->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    loop->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    loop->setFixedSize(WIDTH, HEIGHT);
    loop->setSceneRect(0, 0, WIDTH, HEIGHT);
    loop->show();
    loop->corredor();

    /*while(true){std::thread serverThread(SocketServer);  // Crear un hilo para ejecutar el servidor de sockets
    serverThread.detach();  // Desconectar el hilo principal del hilo del servidor
    }*/
    return a.exec();
}

