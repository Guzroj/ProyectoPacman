#include "FantasmaN.h"
#include <cmath>

Naranja::Naranja(QGraphicsScene *sc, int **map, PacMan *pc) : Fantasma()
{
    scene = sc;
    pacman = pc;

    i_pos = 9;
    j_pos = 8;
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
    this->setPixmap(QPixmap(":/Imagenes/FantasmaN.png"));
    this->setPos(j_pos * 32, i_pos * 32);
    scene->addItem(this);
}
/**
 * @brief Naranja::find_pacman
 * Busca el pacman
 */
void        Naranja::find_pacman()
{

    d = 0;
    flag = 0;
    if (!pacman->scared_state())
    {
        this->setPixmap(QPixmap(":/Imagenes/FantasmaN.png"));
        calculate_point();
    }
    else
    {
        if (i_pos == size_x - 2 && j_pos == size_y - 2)
            pacman->set_scared();
        else
        {
            this->setPixmap(QPixmap(":/Imagenes/Comer.png"));
            i_exit = size_x - 2;
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
/**
 * @brief Naranja::find_path
 * Busca el camino hacia pacman
 */
void        Naranja::find_path()
{
    int i;
    int j;
    int k;

    map_path[rojo->get_i_pos()][rojo->get_j_pos()] = -5;
    map_path[rosa->get_i_pos()][rosa->get_j_pos()] = -5;
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
    map_path[rosa->get_i_pos()][rosa->get_j_pos()] = 0;
    map_path[azul->get_i_pos()][azul->get_j_pos()] = 0;
}
/**
 * @brief Naranja::set_default
 * Define la posicion del fantasma naranja
 */
void        Naranja::set_default()
{
    i_pos = 9;
    j_pos = 8;

    i_exit = i_pos;
    j_exit = j_pos;
    direction = 0;
    this->setPos(j_pos * 32, i_pos * 32);
}

void        Naranja::calculate_point()
{
    int distance;

    distance = pow(i_pos - pacman->get_pacman_i(), 2);
    distance += pow(j_pos - pacman->get_pacman_j(), 2);
    distance = sqrt(distance);
    if (distance <= 8)
    {
        i_exit = pacman->get_pacman_i();
        j_exit = pacman->get_pacman_j();
    }
    else
    {
        i_exit = size_x - 2;
        j_exit = 1;
    }
    this->setPixmap(QPixmap(":/Imagenes/FantasmaN.png"));
}
/**
 * @brief Naranja::set_friends
 * Define la posicion en donde estan los otros fantasmas para evitar choques entre ellos
 * @param bl
 * Es el fantasma rojo
 * @param pnc
 * Es el fantasma rosa
 * @param ink
 * Es el fantasma Azul
 */
void        Naranja::set_friends(Rojo *bl, Rosa *pnc, Azul *ink)
{
    rojo = bl;
    rosa = pnc;
    azul = ink;
}

struct Nodo {
    int x;
    int y;
    Nodo* padre;
    int g;
    int h;
    int f;
};

int calcular_heuristica(Nodo* nodo, int destino_x, int destino_y) {
    int dx = abs(nodo->x - destino_x);
    int dy = abs(nodo->y - destino_y);
    return dx + dy;
}


void Naranja::find_path_A()
{
    // Creamos los nodos inicial y objetivo
    Nodo* inicio = new Nodo();
    inicio->x = i_pos;
    inicio->y = j_pos;
    inicio->padre = nullptr;
    inicio->g = 0;
    inicio->h = calcular_heuristica(inicio, i_exit, j_exit);
    inicio->f = inicio->g + inicio->h;

    Nodo* objetivo = new Nodo();
    objetivo->x = i_exit;
    objetivo->y = j_exit;
    objetivo->padre = nullptr;
    objetivo->g = 0;
    objetivo->h = 0;
    objetivo->f = 0;

    // Creamos listas abierta y cerrada
    std::vector<Nodo*> lista_abierta;
    std::vector<Nodo*> lista_cerrada;

    // Agregamos el nodo inicial a la lista abierta
    lista_abierta.push_back(inicio);

    while (!lista_abierta.empty()) {
        // Buscamos el nodo con el menor valor de f en la lista abierta
        Nodo* nodo_actual = lista_abierta[0];
        int indice_actual = 0;
        for (int i = 1; i < lista_abierta.size(); i++) {
            if (lista_abierta[i]->f < nodo_actual->f) {
                nodo_actual = lista_abierta[i];
                indice_actual = i;
            }
        }

        // Movemos el nodo actual de la lista abierta a la lista cerrada
        lista_abierta.erase(lista_abierta.begin() + indice_actual);
        lista_cerrada.push_back(nodo_actual);

        // Verificamos si hemos alcanzado el objetivo
        if (nodo_actual->x == objetivo->x && nodo_actual->y == objetivo->y) {
            // Reconstruimos el camino óptimo
            Nodo* nodo_camino = nodo_actual;
            while (nodo_camino != nullptr) {
                // Haz algo con el nodo_camino, como marcar el camino en el tablero
                nodo_camino = nodo_camino->padre;
            }
            break;
        }

        // Generamos los sucesores del nodo actual
        for (int i = 0; i < 4; i++) {
            int sucesor_x = x_dir[i] + nodo_actual->x;
            int sucesor_y = y_dir[i] + nodo_actual->y;

            // Verificamos si el sucesor está dentro de los límites del tablero
            if (sucesor_x >= 0 && sucesor_x < size_x && sucesor_y >= 0 && sucesor_y < size_y) {
                // Verificamos si el sucesor es un obstáculo
                if (map_path[sucesor_x][sucesor_y] != -5) {
                    // Creamos el nodo sucesor
                    Nodo* sucesor = new Nodo();
                    sucesor->x = sucesor_x;
                    sucesor->y = sucesor_y;
                    sucesor->padre = nodo_actual;
                    sucesor->g = nodo_actual->g + 1;
                    sucesor->h = calcular_heuristica(sucesor, objetivo->x, objetivo->y);
                    sucesor->f = sucesor->g + sucesor->h;

                    // Verificamos si el sucesor ya está en la lista cerrada
                    bool en_lista_cerrada = false;
                    for (Nodo* nodo : lista_cerrada) {
                        if (nodo->x == sucesor->x && nodo->y == sucesor->y) {
                            en_lista_cerrada = true;
                            break;
                        }
                    }

                    if (!en_lista_cerrada) {
                        // Verificamos si el sucesor ya está en la lista abierta
                        bool en_lista_abierta = false;
                        int indice_existente = -1;
                        for (int j = 0; j < lista_abierta.size(); j++) {
                            if (lista_abierta[j]->x == sucesor->x && lista_abierta[j]->y == sucesor->y) {
                                en_lista_abierta = true;
                                indice_existente = j;
                                break;
                            }
                        }

                        if (en_lista_abierta) {
                            // Si el sucesor ya está en la lista abierta pero tiene un costo g mayor,
                            // actualizamos su costo y su nodo padre
                            if (sucesor->g < lista_abierta[indice_existente]->g) {
                                lista_abierta[indice_existente]->g = sucesor->g;
                                lista_abierta[indice_existente]->padre = nodo_actual;
                            }
                        } else {
                            // Agregamos el sucesor a la lista abierta
                            lista_abierta.push_back(sucesor);
                        }
                    }
                }
            }
        }
    }

    // Liberamos la memoria de los nodos
    for (Nodo* nodo : lista_abierta) {
        delete nodo;
    }
    for (Nodo* nodo : lista_cerrada) {
        delete nodo;
    }
}



/**
 * @brief Naranja::move_f
 * Es un slot que permite el movimiento de los fantasmas
 */
void    Naranja::move_f()
{
    if (pacman->get_point() >= 90)

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
