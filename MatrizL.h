#ifndef MATRIZL_H
#define MATRIZL_H
#include <fstream>
#include <string>
#include <ctime>
#include <random>
#include <vector>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <QTimer>
#include <QObject>
#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include "Pacman.h"
#include "fantasma.h"
#include "FantasmaN.h"
#include "FantasmaA.h"
#include "FantasmaR.h"
#include "FantasmaRS.h"

class Matriz : public QGraphicsView{
private:
    QGraphicsScene          *scene;
    QGraphicsView           *view;
    QGraphicsPixmapItem     **map_pix;
    int                     **map_int;
    PacMan                  *pacman;
    Naranja                 *naranja;
    Rojo                    *rojo;
    Azul                    *azul;
    Rosa                    *rosa;
    QTimer                  *timer_pacman;
    QTimer                  *timer_naranja;
    QTimer                  *timer_rojo;
    QTimer                  *timer_azul;
    QTimer                  *timer_rosa;
public:
    Matriz(char *file_name);
    ~Matriz();
    void lectorLineas(int *map, std::string le );
    void corredor();
    void creaMapa();
    int veri(std::string le);
    int contador = 0;
    int nivel();

};

#endif // MATRIZL_H
