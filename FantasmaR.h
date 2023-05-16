#ifndef FANTASMAR_H
#define FANTASMAR_H

#include "fantasma.h"
#include "FantasmaRS.h"
#include "FantasmaN.h"
#include "FantasmaA.h"

class Rosa;
class Naranja;
class Azul;

class Rojo: public Fantasma
{
private:
    Rosa        *rosa;
    Naranja    *naranja;
    Azul        *azul;

public:
    Rojo(QGraphicsScene *sc, int **map, PacMan *pc);
    void            set_default();
    void            calculate_point();
    void            find_pacman();
    void            set_friends(Rosa *pin, Naranja *cl, Azul *ink);
    void            find_path();
public slots:
    void            move_f();
};

#endif // FANTASMAR_H
