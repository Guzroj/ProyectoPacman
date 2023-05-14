#ifndef FANTASMAN_H
#define FANTASMAN_H

#include "fantasma.h"

class       Naranja: public Fantasma
{
private:
    //Blinky  *blinky;
    //Pinky   *pinky;
    //Inky    *inky;
    Q_OBJECT
public:
    void    set_default();
    void    calculate_point();
    void    find_pacman();
   // void    ft_set_friends(Blinky *bl, Pinky *pnc, Inky *ink);
    void    find_path();
    Naranja(QGraphicsScene *sc, int **map, PacMan *pc);
public slots:
    void    move_f();
};
#endif // FANTASMAN_H
