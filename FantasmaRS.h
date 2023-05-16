#ifndef FANTASMARS_H
#define FANTASMARS_H

#include "fantasma.h"
#include "FantasmaR.h"
#include "FantasmaN.h"
#include "FantasmaA.h"

class Naranja;
class Azul;
class Rojo;

class Rosa : public Fantasma
{
private:
    Naranja *naranja;
    Azul    *azul;
    Rojo    *rojo;
    Q_OBJECT
public:
    void    set_default();
    void    calculate_point();
    void    find_pacman();
    void    set_friends(Rojo *bl, Naranja *cl, Azul *ink);
    void    find_path();
    Rosa(QGraphicsScene *sc, int **map, PacMan *pc);
public slots:
    void    move_f();
};

#endif // FANTASMARS_H
