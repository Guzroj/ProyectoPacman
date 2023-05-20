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

    /*std::thread serverThread(SocketServer);  // Crear un hilo para ejecutar el servidor de sockets
    serverThread.detach();  // Desconectar el hilo principal del hilo del servidor*/


    return a.exec();
}

