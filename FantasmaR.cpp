#include "FantasmaR.h"

void        Rojo::calculate_point()
{
    if (!pacman->scared_state())
    {
        i_exit = pacman->get_pacman_i();
        j_exit = pacman->get_pacman_j();
        this->setPixmap(QPixmap(":/Imagenes/rojo.png"));
    }
    else
    {
        if (i_pos == 1 && j_pos == 1)
            pacman->set_scared();
        else
        {
            this->setPixmap(QPixmap(":/Imagenes/Comer.png"));
            i_exit = 1;
            j_exit = 1;
        }
    }
}

Rojo::Rojo(QGraphicsScene *sc, int **map, PacMan *pc) : Fantasma()
{
    scene = sc;
    pacman = pc;

    i_pos = 8;
    j_pos = 9;
    for (int i = 0; i < size_x; i++)
    {
        for (int j = 0; j < size_y; j++)
        {
            if (map[i][j] == 1)
                map_path[i][j] = -5;
            else
                map_path[i][j] = -3;
        }
    }
    this->setPixmap(QPixmap(":/Imagenes/rojo.png"));
    this->setPos(j_pos * 32, i_pos * 32);
    scene->addItem(this);
}

void        Rojo::set_default()
{
    i_exit = i_pos;
    j_exit = j_pos;
    i_pos = 9;
    j_pos = 9;
    direction = 0;
    this->setPos(j_pos * 32, i_pos * 32);
}

void        Rojo::set_friends(Rosa *pin, Naranja *cl, Azul *ink)
{
    rosa = pin;
    naranja = cl;
    azul = ink;
}

void        Rojo::find_path()
{
    int i;
    int j;
    int k;

    map_path[rosa->get_i_pos()][rosa->get_j_pos()] = -5;
    map_path[naranja->get_i_pos()][naranja->get_j_pos()] = -5;
    map_path[azul->get_i_pos()][azul->get_j_pos()] = -5;
    while (!flag && map_path[i_exit][j_exit] == -3)
    {
        i = 0;
        flag = 1;
        while (i < size_x)
        {
            j = 0;
            while (j < size_y)
            {
                if (map_path[i][j] == d)
                {
                    k = 0;
                    while (k < 4)
                    {
                        i_x = x_dir[k] + i;
                        i_y = y_dir[k] + j;
                        if ((i_x >= 0 && i_x < size_x)
                            && (i_y >= 0 && i_y < size_y) && (map_path[i_x][i_y] == -3))
                        {
                            map_path[i_x][i_y] = d + 1;
                            flag = 0;
                        }
                        k++;
                    }
                }
                j++;
            }
            i++;
        }
        d++;
    }
    map_path[rosa->get_i_pos()][rosa->get_j_pos()] = 0;
    map_path[naranja->get_i_pos()][naranja->get_j_pos()] = 0;
    map_path[azul->get_i_pos()][azul->get_j_pos()] = 0;
}

void        Rojo::find_pacman()
{
    d = 0;
    flag = 0;
    map_path[i_pos][j_pos] = d;
    if (check_intersect())
    {
        clear_map();
        return ;
    }
    find_path();
    if (set_direction_near())
    {
        if (check_intersect())
        {
            clear_map();
            return ;
        }
    }
    restore_path();
    set_direction();
    clear_map();
}

void    Rojo::move_f()
{
    calculate_point();
    find_pacman();
    if (direction == 1)
    {
        if (check_move(i_pos - 1, j_pos))
            i_pos--;
    }
    if (direction == 2)
    {
        if (check_move(i_pos + 1, j_pos))
            i_pos++;
    }
    if (direction == 3)
    {
        if (check_move(i_pos, j_pos - 1))
            j_pos--;
    }
    if (direction == 4)
    {
        if (check_move(i_pos, j_pos + 1))
            j_pos++;
    }
    this->setPos(j_pos * 32, i_pos * 32);
    if (check_intersect())
        return ;
}
