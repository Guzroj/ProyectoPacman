#include "FantasmaRS.h"
/**
 * @brief Rosa::find_path
 * encuentra la ruta mas cercana
 */
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

/**
 * @brief Rosa::Rosa
 * crea el objeto Rosa
 * @param sc
 * @param map
 * se obtiene el mapa
 * @param pc
 * referencia a pacman
 */
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

/*void        Rosa::find_pacman()
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
}*/

/**
 * @brief Rosa::find_pacman
 * encuentra a pacman y la ruta hacia el
 */
void Rosa::find_pacman()
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

    // Verificar si el backtracking está activo
    if (backtracking_active) {
        if (backtrack()) {
            // Se encontró una solución, actualizar la posición de Rosa
            this->setPos(j_pos * 32, i_pos * 32);
        }
    } else {
        find_path();
        if (set_direction_near())
        {
            clear_map();
            return ;
        }
        restore_path();
        set_direction();
    }

    clear_map();
}

/**
 * @brief Rosa::set_default
 * define la posicion inicial del fantasma
 */
void        Rosa::set_default()
{
    i_pos = 9;
    j_pos = 9;

    i_exit = i_pos;
    j_exit = j_pos;
    direction = 0;
    this->setPos(j_pos * 32, i_pos * 32);
}

/**
 * @brief Rosa::calculate_point
 * calcula la distancia y el punto de pacman
 */
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

/**
 * @brief Rosa::set_friends
 * reconoce los demas fantasmas para ubicarse bien
 * @param bl
 * referencia al fantasma rojo
 * @param cl
 * referencia al fantasma naranja
 * @param ink
 * referencia al fantasma azul
 */
void        Rosa::set_friends(Rojo *bl, Naranja *cl, Azul *ink)
{
    rojo = bl;
    naranja = cl;
    azul = ink;
}

/**
 * @brief Rosa::check_solution
 * verifica la solucion encontrada
 * @return
 * retorna la ubicacion de la solucion
 */

bool Rosa::check_solution()
{
    return (i_pos == i_exit && j_pos == j_exit);
}


/**
 * @brief Rosa::backtrack
 * realiza la busqueda utilizando backtracking
 * @return
 * regresa el resultado de utilizar el backtracking
 */
bool Rosa::backtrack()
{
    if (check_solution()) {
        return true;  // Se encontró la solución
    }

    // Intentar mover hacia arriba
    if (check_move(i_pos - 1, j_pos)) {
        // Guardar la posición actual
        int prev_i = i_pos;
        int prev_j = j_pos;

        // Mover hacia arriba
        i_pos--;
        if (backtrack()) {
            return true;  // Se encontró la solución
        }

        // No se encontró la solución, retroceder
        i_pos = prev_i;
        j_pos = prev_j;
    }

    // Intentar mover hacia abajo
    if (check_move(i_pos + 1, j_pos)) {
        // Guardar la posición actual
        int prev_i = i_pos;
        int prev_j = j_pos;

        // Mover hacia abajo
        i_pos++;
        if (backtrack()) {
            return true;  // Se encontró la solución
        }

        // No se encontró la solución, retroceder
        i_pos = prev_i;
        j_pos = prev_j;
    }

    // Intentar mover hacia la izquierda
    if (check_move(i_pos, j_pos - 1)) {
        // Guardar la posición actual
        int prev_i = i_pos;
        int prev_j = j_pos;

        // Mover hacia la izquierda
        j_pos--;
        if (backtrack()) {
            return true;  // Se encontró la solución
        }

        // No se encontró la solución, retroceder
        i_pos = prev_i;
        j_pos = prev_j;
    }

    // Intentar mover hacia la derecha
    if (check_move(i_pos, j_pos + 1)) {
        // Guardar la posición actual
        int prev_i = i_pos;
        int prev_j = j_pos;

        // Mover hacia la derecha
        j_pos++;
        if (backtrack()) {
            return true;  // Se encontró la solución
        }

        // No se encontró la solución, retroceder
        i_pos = prev_i;
        j_pos = prev_j;
    }

    return false;  // No se encontró ninguna solución desde esta posición
}

/**
 * @brief Rosa::activate_backtracking
 * verifica si hay que activar backtracking
 */
void Rosa::activate_backtracking()
{
    backtracking_active = true;
}

/*void    Rosa::move_f()
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
}*/


/**
 * @brief Rosa::move_f
 * Se encarga de mover al fantasma, determina si se debe utilizar el algoritmo de busqueda por amplitud o backtracking
 */
void Rosa::move_f()
{
    if (pacman->get_point() >= 40)
    {
        // Verificar la condición para activar el backtracking
        if (pacman->points == 200) {
            activate_backtracking();
    }

    if (backtracking_active) {
        if (backtrack()) {
            // Se encontró una solución, actualizar la posición de Rosa
            this->setPos(j_pos * 32, i_pos * 32);
        }
    } else {
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
}

