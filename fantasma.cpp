#include <QGraphicsPixmapItem>
#include "fantasma.h"

Fantasma::Fantasma()
{

}
void Fantasma::set_default()
{

}

void    Fantasma::move_f()
{

}

void    Fantasma::calculate_point()
{

}

void        Fantasma::set_direction()
{
    if (i_pos + 1 < size_x)
    {
        if (map_path[i_pos + 1][j_pos] == -4)
            direction = 2;
    }
    if (i_pos - 1 >= 0)
    {
        if (map_path[i_pos - 1][j_pos] == -4)
            direction = 1;
    }
    if (j_pos + 1 < size_x)
    {
        if (map_path[i_pos][j_pos + 1] == -4)
            direction = 4;
    }
    if (j_pos - 1 < size_x)
    {
        if (map_path[i_pos][j_pos - 1] == -4)
            direction = 3;
    }
}


void        Fantasma::find_pacman()
{

}

int     Fantasma::get_i_pos()
{
    return (i_pos);
}

int     Fantasma::get_j_pos()
{
    return (j_pos);
}

int     Fantasma::check_move(int i_pos, int j_pos)
{
    if (map_path[i_pos][j_pos] == -5)
        return (0);
    return (1);
}

int        Fantasma::check_intersect()
{
    if (i_pos == pacman->get_pacman_i() && j_pos == pacman->get_pacman_j()
        && !pacman->scared_state())
    {
        clear_map();
        pacman->set_defaut();
        pacman->set_lives();
        return (1);
    }
    if (i_pos == pacman->get_pacman_i() && j_pos == pacman->get_pacman_j()
        && pacman->scared_state())
    {
        clear_map();
        i_pos = 8;
        j_pos = 9;
        this->setPos(j_pos * 32, i_pos * 32);
        pacman->incr_score();
        return (1);
    }
    return (0);
}

void        Fantasma::clear_map()
{
    for (int i = 0; i < size_x; i++)
    {
        for (int j = 0; j < size_y; j++)
        {
            if (map_path[i][j] != -5)
                map_path[i][j] = -3;
        }
    }
}

void        Fantasma::restore_path()
{
    int i;
    int j;
    int k;

    i = i_exit;
    j = j_exit;
    while (d > 0)
    {
        d--;
        k = 0;
        while (k < 4)
        {
            i_x = i + x_dir[k];
            i_y = j + y_dir[k];
            if (i_x >= 0 && i_x < size_x
                && i_y >= 0 && i_y < size_y && map_path[i_x][i_y] == d)
            {
                map_path[i_x][i_y] = -4;
                i = i + x_dir[k];
                j = j + y_dir[k];
                break ;
            }
            k++;
        }
    }
}

int         Fantasma::set_direction_near()
{
    int flag;

    flag = 0;
    if (i_pos + 1 < size_x)
    {
        if (i_pos + 1 == i_exit && j_pos == j_exit)
        {
            direction = 2;
            flag = 1;
        }
    }
    if (i_pos - 1 >= 0)
    {
        if (i_pos -1 == i_exit && j_pos == j_exit)
        {
            direction = 1;
            flag = 1;
        }
    }
    if (j_pos + 1 < size_x)
    {
        if (i_pos == i_exit && j_pos + 1 == j_exit)
        {
            direction = 4;
            flag = 1;
        }
    }
    if (j_pos - 1 < size_x)
    {
        if (i_pos == i_exit && j_pos - 1 == j_exit)
        {
            direction = 3;
            flag = 1;
        }
    }
    if (flag)
        return (1);
    return (0);
}

void        Fantasma::find_path()
{

}

