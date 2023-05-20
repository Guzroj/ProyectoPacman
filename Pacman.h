#ifndef PACMAN_H
#define PACMAN_H
#include <QObject>
#include <QGraphicsTextItem>
#include <QKeyEvent>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <unistd.h>


class   PacMan : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
private:
    int i_pos;
    int j_pos;
    int direction;
    int**map_int;
    QGraphicsPixmapItem**map_pix;
    QGraphicsScene*scene;
    QGraphicsTextItem*text;
    QGraphicsTextItem*message;
    int vidas;
    int verimove(int i_pos, int j_pos);
    int scared;
    int counter;
    int score;
    //int points;
public:
    PacMan(int **map_int, QGraphicsPixmapItem **map_pix, QGraphicsScene *scene);
    void    keyPressEvent(QKeyEvent *event);
    int     get_pacman_i(void);
    void    set_defaut();
    int     get_score();
    int     scared_state();
    void    set_scared();
    int     get_direction();
    int     get_pacman_j(void);
    void    incr_score();
    void    print_score();
    void    set_lives();
    int     get_point();
    //prueba para que funcione back
    void refrescar();
    int points;
    int nivel();
    int contador=1;

public slots:
    void    move();
};

#endif // PACMAN_H
