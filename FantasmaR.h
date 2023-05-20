#ifndef FANTASMAR_H
#define FANTASMAR_H

#include "fantasma.h"
#include "FantasmaRS.h"
#include "FantasmaN.h"
#include "FantasmaA.h"

class Rosa;
class Naranja;
class Azul;

/**
 * @brief The Rojo class
 * clase del fantasma rojo
 */
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

    //parte de prueba back
    bool            backtracking_active =false;
    bool            check_solution();
    void            activate_backtracking();
    bool            backtrack();
public slots:
    void            move_f();
};

#endif // FANTASMAR_H
