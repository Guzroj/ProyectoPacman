#ifndef FANTASMARS_H
#define FANTASMARS_H

#include "fantasma.h"
#include "FantasmaR.h"
#include "FantasmaN.h"
#include "FantasmaA.h"

class Naranja;
class Azul;
class Rojo;

/**
 * @brief The Rosa class
 * clase para el fantasma rosa
 */
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

   //para hacer el back del fantasma rosado
   bool     backtracking_active = false;
   void     activate_backtracking();
   bool     check_solution();
   bool     backtrack();


public slots:
    void    move_f();
};

#endif // FANTASMARS_H
