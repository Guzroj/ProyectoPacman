#include "FantasmaRS.h"

void        Rosa::find_path()
{
    int i;
    int j;
    int k;

    map_path[rojo->get_i_pos()][rojo->get_j_pos()] = -5;
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
    map_path[rojo->get_i_pos()][rojo->get_j_pos()] = 0;
    map_path[naranja->get_i_pos()][naranja->get_j_pos()] = 0;
    map_path[azul->get_i_pos()][azul->get_j_pos()] = 0;
}

Rosa::Rosa(QGraphicsScene *sc, int **map, PacMan *pc) : Fantasma()
{
    scene = sc;
    pacman = pc;

    i_pos = 9;
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
    this->setPixmap(QPixmap(":/Imagenes/rosa.png"));
    this->setPos(j_pos * 32, i_pos * 32);
    scene->addItem(this);
}

void        Rosa::find_pacman()
{
    d = 0;
    flag = 0;
    if (!pacman->scared_state())
    {
        this->setPixmap(QPixmap(":/Imagenes/rosa.png"));
        calculate_point();
    }
    else
    {
        if (i_pos == 1 && j_pos == size_y - 2)
            pacman->set_scared();
        else
        {
            this->setPixmap(QPixmap(":/Imagenes/Comer.png"));
            i_exit = 1;
            j_exit = size_y - 2;
        }
    }
    map_path[i_pos][j_pos] = d;
    if (check_intersect())
        return ;
    find_path();
    if (set_direction_near())
    {
        clear_map();
        return ;
    }
    restore_path();
    set_direction();
    clear_map();
}

void        Rosa::set_default()
{
    i_pos = 9;
    j_pos = 9;

    i_exit = i_pos;
    j_exit = j_pos;
    direction = 0;
    this->setPos(j_pos * 32, i_pos * 32);
}

void        Rosa::calculate_point()
{
    int direction;

    direction = pacman->get_direction();
    if (direction == 1)
    {
        i_exit = pacman->get_pacman_i() - 4;
        j_exit = pacman->get_pacman_j();
        if (i_exit < 0)
        {
            i_exit = pacman->get_pacman_i();
            j_exit = pacman->get_pacman_j();
        }
    }
    if (direction == 2)
    {
        i_exit = pacman->get_pacman_i() + 4;
        j_exit = pacman->get_pacman_j();
        if (i_exit >= size_x)
        {
            i_exit = pacman->get_pacman_i();
            j_exit = pacman->get_pacman_j();
        }
    }
    if (direction == 3)
    {
        i_exit = pacman->get_pacman_i();
        j_exit = pacman->get_pacman_j() - 4;
        if (j_exit < 0)
        {
            i_exit = pacman->get_pacman_i();
            j_exit = pacman->get_pacman_j();
        }
    }
    if (direction == 4)
    {
        i_exit = pacman->get_pacman_i();
        j_exit = pacman->get_pacman_j() + 4;
        if (j_exit > size_y)
        {
            i_exit = pacman->get_pacman_i();
            j_exit = pacman->get_pacman_j();
        }
    }
    if (map_path[i_exit][j_exit] != -3)
    {
        i_exit = pacman->get_pacman_i();
        j_exit = pacman->get_pacman_j();
    }
}

void        Rosa::set_friends(Rojo *bl, Naranja *cl, Azul *ink)
{
    rojo = bl;
    naranja = cl;
    azul = ink;
}

void    Rosa::move_f()
{
    if (pacman->get_point() >= 50)
    {
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
}
