#ifndef FANTASMA_H
#define FANTASMA_H

#define size_x 21
#define size_y 19

#include "Pacman.h"

class Fantasma :public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
protected:
    int             d;
    int             i_pos;
    int             j_pos;
    int             i_x;
    int             i_y;
    int             flag;
    int             i_exit;
    int             j_exit;
    int             direction;

    int             map_path[size_x][size_y];
    int             x_dir[4] = { 1, -1, 0, 0 };
    int             y_dir[4] = { 0, 0, 1, -1 };
    PacMan          *pacman;
    QGraphicsScene  *scene;
public:
    void            clear_map();
    void            restore_path();
    void            set_direction();
    virtual void    find_pacman() = 0;
    virtual void    find_path() = 0;
    int             check_intersect();
    int             set_direction_near();
    int             get_i_pos();
    int             get_j_pos();
    int             check_move(int i_pos, int j_pos);
    virtual void    set_default() = 0;
    virtual void    calculate_point() = 0;
                    Fantasma();
public slots:
    virtual void    move_ghost() = 0;
};

#endif // FANTASMA_H
