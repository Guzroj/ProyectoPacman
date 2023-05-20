#ifndef FANTASMAN_H
#define FANTASMAN_H

#include "fantasma.h"
#include "FantasmaA.h"
#include "FantasmaRS.h"
#include "FantasmaR.h"

class Rojo;
class Rosa;
class Azul;

/**
 * @brief The Naranja class
 * clase del fantasma naranja
 */

class       Naranja: public Fantasma
{
private:
    Rojo  *rojo;
    Rosa   *rosa;
    Azul    *azul;
    Q_OBJECT

public:
    void    set_default();
    void    calculate_point();
    void    find_pacman();
    void    set_friends(Rojo *bl, Rosa *pnc, Azul *ink);
    void    find_path();
    Naranja(QGraphicsScene *sc, int **map, PacMan *pc);

    void find_path_A();


public slots:
    void    move_f();
};
#endif // FANTASMAN_H
