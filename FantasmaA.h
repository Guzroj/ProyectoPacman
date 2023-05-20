#ifndef FANTASMAA_H
#define FANTASMAA_H

#include "fantasma.h"
#include "FantasmaR.h"
#include "FantasmaN.h"
#include "FantasmaRS.h"

class       Rojo;
class       Rosa;
class       Naranja;

class       Azul : public Fantasma
{
private:
    Rojo      *rojo;
    Naranja   *naranja;
    Rosa      *rosa;
    Q_OBJECT
public:
    void    set_default();
    void    calculate_point();
    void    find_pacman();
    void    set_friends(Rojo *bl, Rosa *pnc, Naranja *cld);
    void    find_path();

            Azul(QGraphicsScene *sc, int **map, PacMan *pc);

public slots:
    void    move_f();
};

#endif // FANTASMAA_H
