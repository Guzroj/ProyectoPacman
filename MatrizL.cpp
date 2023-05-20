#include "MatrizL.h"
//#include "FantasmaN.h"
#define size_x 21
#define size_y 19

/**
 * @brief Matriz::veri
 * Se encarga de verificar que exista la matriz
 * @param le
 * @return
 */
int Matriz::veri(std::string le){
    int i;

    i = 0;
    while (le[i])
    {
        if (le[i] < '0' || le[i] > '4')
            return (1);
        i++;
    }
    return (0);
}


/**
 * @brief Matriz::~Matriz
 * Borra todo
 */
Matriz::~Matriz(){
    delete scene;
    delete view;
    delete naranja;
    delete rosa;
    delete azul;
    delete rojo;
    delete timer_pacman;
    delete timer_naranja;
    delete timer_rosa;
    delete timer_azul;
    delete timer_rojo;

    for (int i = 0; i < size_x; i++)
    {
        for (int j = 0; j < size_y; j++)
        {
            delete map_pix[i];
            delete map_int[i];
        }
    }
    delete []map_pix;
    delete []map_int;
}

/**
 * @brief Matriz::creaMapa
 * Crea mapa de la matriz
 */
void Matriz::creaMapa(){
    for (int i = 0; i < size_x; i++)
    {
        for (int j = 0; j < size_y; j++)
        {
            if (map_int[i][j] == 1)
            {
                map_pix[i][j].setPixmap(QPixmap(":/Imagenes/Pared.png"));
                map_pix[i][j].setPos(j * 32, i * 32);
                scene->addItem(&(map_pix[i][j]));
            }
            if (map_int[i][j] == 3)
            {
                map_pix[i][j].setPixmap(QPixmap(":/Imagenes/Pelota.png"));
                map_pix[i][j].setPos(j * 32, i * 32);
                scene->addItem(&(map_pix[i][j]));
            }
            if (map_int[i][j] == 4)
            {
                map_pix[i][j].setPixmap(QPixmap(":/Imagenes/energizer.png"));
                map_pix[i][j].setPos(j * 32, i * 32);
                scene->addItem(&(map_pix[i][j]));
            }
        }
    }

}
/**
 * @brief Matriz::lectorLineas
 * Lee las lineas de la matriz
 * @param map
 * Es la matriz dinamica
 * @param le
 * Es un string de la fila
 */
void Matriz::lectorLineas(int *map, std::string le){
    for (int i = 0; i < size_y; i++)
        map[i] = le[i] - '0';
}
/**
 * @brief Matriz::corredor
 * Estan todos los qtimers
 */
void Matriz::corredor(){

    timer_pacman = new QTimer();
    timer_naranja = new QTimer();
    timer_rosa = new QTimer();
    timer_azul = new QTimer();
    timer_rojo = new QTimer();
    QObject::connect(timer_pacman, SIGNAL(timeout()), pacman, SLOT(move()));
    QObject::connect(timer_naranja, SIGNAL(timeout()), naranja, SLOT(move_f()));
    QObject::connect(timer_rosa, SIGNAL(timeout()), rosa, SLOT(move_f()));
    QObject::connect(timer_azul, SIGNAL(timeout()), azul, SLOT(move_f()));
    QObject::connect(timer_rojo, SIGNAL(timeout()), rojo, SLOT(move_f()));

    timer_pacman->start(300);
    timer_naranja->start(300);
    timer_rosa->start(300);
    timer_azul->start(300);
    timer_rojo->start(300);

}

/**
 * @brief Matriz::Matriz
 * Se usa para abrir la matriz desde el txt
 * @param file_name
 * Es nuestro map.txt
 */
Matriz::Matriz(char *file_name){
    std::ifstream   input;
    std::string     temp;
    int             nb;

    map_int = new int *[size_x];
    map_pix = new QGraphicsPixmapItem *[size_x];
    for (int i = 0; i < size_x; i++)
    {
        map_int[i] = new int[size_y];
        map_pix[i] = new QGraphicsPixmapItem[size_y];
    }

    input.open(file_name);
    if (input.is_open())
    {
        nb = 0;
        while (std::getline(input, temp))
        {
            if (temp.length() != size_y)
            {
                std::cout << "File error.\n";
                exit(0);
            }
            if (veri(temp))
            {
                std::cout << "File error.\n";
                exit(0);
            }
            lectorLineas(map_int[nb], temp);
            nb++;
        }
        if (nb != size_x)
        {
            std::cout << "File error.\n";
            exit(0);
        }
        input.close();
    }
    else
    {
        std::cout << "File missing: " << file_name << ".\n";
        exit(0);
    }
    scene = new QGraphicsScene();
    view = new QGraphicsView();
    this->setScene(scene);
    creaMapa();
    this->setStyleSheet("background-color:black;");
    pacman = new PacMan(map_int, map_pix, scene);
    pacman->setFlag(QGraphicsPixmapItem::ItemIsFocusable);
    pacman->setFocus();
    naranja = new Naranja(scene, map_int, pacman);
    rojo = new Rojo(scene, map_int, pacman);
    rosa = new Rosa(scene, map_int, pacman);
    azul = new Azul(scene, map_int, pacman);
    rojo->set_friends(rosa, naranja, azul);
    rosa->set_friends(rojo, naranja, azul);
    naranja->set_friends(rojo, rosa, azul);
    azul->set_friends(rojo, rosa, naranja);

}
