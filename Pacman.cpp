#include "Pacman.h"
#include <iostream>

#define WIDTH 608
#define HEIGHT 702
#define size_x 21
#define size_y 19
void    PacMan::refrescar()
{
    static int flag;

    if (points == 20)
    {
        map_int[15][9] = 6;
        if (!flag)
        {
            map_pix[15][9].setPixmap(QPixmap(":/Imagenes/Power.png"));
            scene->addItem(&(map_pix[15][9]));
            flag = 1;
        }
    }
    if (map_int[i_pos][j_pos] == 6)
    {
        score += 200;
        map_int[i_pos][j_pos] = 0;
        scene->removeItem(&(map_pix[15][9]));
        flag = 0;
    }
    if (map_int[i_pos][j_pos] == 3)
    {
        map_int[i_pos][j_pos] = 0;
        score += 10;
        points++;
        scene->removeItem(&(map_pix[i_pos][j_pos]));
    }
    if (map_int[i_pos][j_pos] == 4)
    {
        scared = 1;
        map_int[i_pos][j_pos] = 0;
        scene->removeItem(&(map_pix[i_pos][j_pos]));
    }
}

int     PacMan::scared_state()
{
    return (scared);
}

void    PacMan::set_scared()
{
    scared = !scared;
}

int     PacMan::get_score()
{
    return (score);
}

void    PacMan::print_score()
{
    text->setDefaultTextColor(0x00ffffff);
    text->setFont(QFont("times", 15));
    text->setPlainText("Puntuacion " + QString::number(score) + "\t\tVidas: " + QString::number(vidas));
    text->setPos(10 , HEIGHT - 30);
}

void    PacMan::incr_score()
{
    score += 100;
}

void    PacMan::set_lives()
{
    vidas--;
}

PacMan::PacMan(int **map_i, QGraphicsPixmapItem **map_p, QGraphicsScene *sc)
{
    i_pos = 15;
    score = 0;
    points = 0;
    j_pos = 9;
    counter = 0;
    direction = 0;
    map_int = map_i;
    map_pix = map_p;
    scene = sc;
    scared = 0;
    vidas = 3;
    text = new QGraphicsTextItem();
    message = new QGraphicsTextItem();
    this->setPixmap(QPixmap(":/Imagenes/Derecha.png"));
    this->setPos(j_pos * 32, i_pos * 32);
    scene->addItem(this);
    scene->addItem(text);
    print_score();
}

int     PacMan::get_direction()
{
    return (direction);
}

void    PacMan::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Left)
    {
        this->direction = 3;
        this->setPixmap(QPixmap(":/Imagenes/Izquierda.png"));
    }
    if (event->key() == Qt::Key_Right)
    {
        this->direction = 4;
        this->setPixmap(QPixmap(":/Imagenes/Derecha.png"));
    }
    if (event->key() == Qt::Key_Down)
    {
        this->direction = 2;
        this->setPixmap(QPixmap(":/Imagenes/Abajo.png"));
    }
    if (event->key() == Qt::Key_Up)
    {
        this->direction = 1;
        this->setPixmap(QPixmap(":/Imagenes/Arriba.png"));
    }
}

int     PacMan::get_point()
{
    return (points);
}

void    PacMan::move()
{
    static int flag;

    print_score();
    if (points == 149 && !flag)
    {
        message->setDefaultTextColor(0x00ff00ff);
        message->setFont(QFont("times", 40));
        message->setPlainText("YOU WIN");
        message->setPos(60, HEIGHT / 2 - 30);
        scene->addItem(message);
        scene->removeItem(this);
        scene->removeItem(text);
        flag = 1;
    }
    if (vidas <= 0 && !flag)
    {
        message->setDefaultTextColor(0x00ff00ff);
        message->setFont(QFont("times", 60));
        message->setPlainText("YOU LOST");
        message->setPos(80, HEIGHT / 2);
        scene->addItem(message);
        scene->removeItem(this);
        scene->removeItem(text);
        flag = 1;
    }
    refrescar();
    if (direction == 1)
    {
        if (i_pos == 0)
        {
            if (verimove(size_x - 1, j_pos))
                i_pos = size_x - 1;
        }
        else
            if (verimove(i_pos - 1, j_pos))
                i_pos--;
    }
    if (direction == 2)
    {
        if (i_pos == size_x - 1)
        {
            if (verimove(0, j_pos))
                i_pos = 0;
        }
        else
            if (verimove(i_pos + 1, j_pos))
                i_pos++;
    }
    if (direction == 3)
    {
        if (j_pos == 0)
        {
            if (verimove(i_pos, size_y - 1))
                j_pos = size_y - 1;
        }
        else
            if (verimove(i_pos, j_pos - 1))
                j_pos--;
    }
    if (direction == 4)
    {
        if (j_pos == size_y - 1)
        {
            if (verimove(i_pos, 0))
                j_pos = 0;
        }
        else
            if (verimove(i_pos, j_pos + 1))
                j_pos++;
    }
    this->setPos(j_pos * 32, i_pos * 32);
}

int     PacMan::get_pacman_i(void)
{
    return (i_pos);
}

int     PacMan::get_pacman_j(void)
{
    return (j_pos);
}

int     PacMan::verimove(int i_pos, int j_pos)
{
    if (map_int[i_pos][j_pos] == 1)
        return (0);
    return (1);
}

void    PacMan::set_defaut()
{
    i_pos = 15;
    j_pos = 9;

    direction = 0;
    this->setPos(j_pos * 32, i_pos * 32);
}
