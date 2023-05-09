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

class Matriz : public QGraphicsView{
private:
    QGraphicsScene                          *scene;
    QGraphicsView                           *view;
    QGraphicsPixmapItem                     **map_pix;
    int                                     **map_int;
public:
    Matriz(char *file_name);
    ~Matriz();
    void lectorLineas(int *map, std::string le );
    void corredor();
    void creaMapa();
    int veri(std::string le);

};

#endif // MATRIZL_H
