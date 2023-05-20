#include "Pacman.h"
#include <iostream>

#define WIDTH 608
#define HEIGHT 702
#define size_x 21
#define size_y 19

#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>

/**
 * @brief PacMan::refrescar
 * Se encarga de refrescar los datos que recibe el pacman, es decir si se come el cherry, se come los fantasmas o come puntos
 */
//Matriz matriz;
//int nivel = matriz.nivel();

void    PacMan::refrescar()
{
    static int flag;

    if (points == 20)
    {
        map_int[15][10] = 6;
        if (!flag)
        {
            map_pix[15][10].setPixmap(QPixmap(":/Imagenes/Power.png"));
            scene->addItem(&(map_pix[15][10]));
            flag = 1;

        }
    }
    if (map_int[i_pos][j_pos] == 6)
    {
        scared = 1;
        map_int[i_pos][j_pos] = 0;
        scene->removeItem(&(map_pix[i_pos][j_pos]));
        flag = 0;

    }
    if (map_int[i_pos][j_pos] == 3)
    {
        map_int[i_pos][j_pos] = 0;
        score += 10;
        points++;
        if (score==400)
            nivel();
        if (score==600)
            nivel();
        if (score==700)
            nivel();
        scene->removeItem(&(map_pix[i_pos][j_pos]));
    }
}
/**
 * @brief PacMan::nivel
 * Aumenta el nivel del juego
 * @return la variable contador aumentada
 */
int PacMan::nivel(){
    contador++;
    return contador;
}
/**
 * @brief PacMan::scared_state
 * Se encarga de mandar el estado de asustado de los fantasmas
 * @return
 */
int     PacMan::scared_state()
{
    return (scared);
}
/**
 * @brief PacMan::set_scared
 * Define el estado de asustado en los fantasmas
 */
void    PacMan::set_scared()
{
    scared = !scared;
}
/**
 * @brief PacMan::get_score
 * Consigue la puntuacion actual de los fantasmas
 * @return
 */
int     PacMan::get_score()
{
    return (score);
}
/**
 * @brief PacMan::print_score
 * Printea la puntuacion actual
 */
void    PacMan::print_score()
{

    text->setDefaultTextColor(0x00ffffff);
    text->setFont(QFont("times", 15));
    text->setPlainText("Puntuacion " + QString::number(score) + "\t\tVidas: " + QString::number(vidas)+ "\t\tNivel: " + QString::number(contador));
    text->setPos(10 , HEIGHT - 30);
}
/**
 * @brief PacMan::incr_score
 * Aumenta la puntuacion
 */
void    PacMan::incr_score()
{
    score += 50;
}
/**
 * @brief PacMan::set_lives
 * Se encarga de restar vidas, se llama en donde se definio para disminuir las vidas
 */
void    PacMan::set_lives()
{
    vidas--;
}
/**
 * @brief PacMan::PacMan
 * Define los parametros que necesita el pacman, como la matriz y la matriz visual
 * @param map_i
 * Es la matriz
 * @param map_p
 * Es la matriz que visual
 * @param sc
 */
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
/**
 * @brief PacMan::get_direction
 * Obtiene la direccion del pacman
 * @return
 */

int     PacMan::get_direction()
{
    return (direction);
}
/**
 * @brief PacMan::keyPressEvent
 * Hace los movimientos del pacman con los estimulos que uno manda
 * @param event
 */

void    PacMan::keyPressEvent(QKeyEvent *event){

    if (event->key() == Qt::Key_Left){
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
/**
 * @brief PacMan::get_point
 * Obtiene la cantidad de puntos
 * @return
 */
int     PacMan::get_point()
{
    return (points);
}

/**
 * @brief SocketServer
 * Comunica la aplicacion con el qt creator
 */
void PacMan::SocketServer() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    // Crear socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        std::cerr << "Error al crear socket" << std::endl;
        return;
    }

    // Opción de socket para reutilizar la dirección
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        std::cerr << "Error en setsockopt" << std::endl;
        return;
    }

    // Configurar dirección del socket
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(5001);

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt))) {
        std::cerr << "Error en setsockopt" << std::endl;
        return;
    }


    // Enlazar socket a la dirección y puerto especificados
    if (bind(server_fd, (struct sockaddr *) &address, sizeof(address)) < 0) {
        std::cerr << "Error en bind" << std::endl;
        return;
    }

    // Escuchar conexiones entrantes
    if (listen(server_fd, 3) < 0) {
        std::cerr << "Error en listen" << std::endl;
        return;
    }

    std::cout << "Servidor en espera de conexiones..." << std::endl;


    // Aceptar nueva conexión
    if ((new_socket = accept(server_fd, (struct sockaddr *) &address, (socklen_t *) &addrlen)) < 0) {
        std::cerr << "Error en accept" << std::endl;
        return;
    }

    std::cout << "Nueva conexión aceptada" << std::endl;

        // Procesar mensajes entrantes
        char buffer[1024] = {0};
    int valread = read(new_socket, buffer, 1024);
    std::string mensajeRecibido(buffer); // Almacena el contenido del búfer en una variable de tipo string

    if (valread <= 0) {
        std::cout << "Cliente desconectado" << std::endl;
        close(new_socket);


        // Hacer algo con el mensaje recibido

        return;
    }

    //std::cout << "Mensaje recibido: " << buffer << std::endl;
    std::cout << "Mensaje recibido: " << mensajeRecibido << std::endl;
    numero = std::stoi(mensajeRecibido); ;

    char respuesta[] = "Mensaje recibido.\n";
    send(new_socket, respuesta, sizeof(respuesta), 0);
    std::cout << "Respuesta: " << respuesta << std::endl;
    //int numero = std::atoi(respuesta); ;
    qDebug()<<numero;
    if (close(server_fd) == -1) {
        std::cerr << "Error al cerrar el socket: " << std::strerror(errno) << std::endl;
        return;
    }
    if (close(new_socket) == -1) {
        std::cerr << "Error al cerrar el socket: " << std::strerror(errno) << std::endl;
        return;
    }
}
/**
 * @brief PacMan::move
 * Es un slot que permite el movmiento del pacman
 */
void    PacMan::move()
{
    static int flag;
    SocketServer();

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
    if (numero==1){
        qDebug()<<"Se mueve para izquierda";
    }
    if (numero==-1){
        qDebug()<<"Se mueve para la derecha";
    }
    if (numero==0){
        qDebug()<<"Se mueve para la arriba";
    }
    if (numero==2){
        qDebug()<<"Se mueve para abajo";
    }
    this->setPos(j_pos * 32, i_pos * 32);
}
/**
 * @brief PacMan::get_pacman_i
 * Localiza la fila donde esta el pacman
 * @return
 */
int     PacMan::get_pacman_i(void)
{
    return (i_pos);
}
/**
 * @brief PacMan::get_pacman_j
 * Localiza la columna donde esta pacman
 * @return
 */
int     PacMan::get_pacman_j(void)
{
    return (j_pos);
}
/**
 * @brief PacMan::verimove
 * Confrma el movmiento que va a realizar el pacman
 * @param i_pos
 * @param j_pos
 * @return
 */
int     PacMan::verimove(int i_pos, int j_pos)
{
    if (map_int[i_pos][j_pos] == 1)
        return (0);
    return (1);
}
/**
 * @brief PacMan::set_defaut
 * Define la posicion donde aparece el pacman
 */
void    PacMan::set_defaut()
{
    i_pos = 15;
    j_pos = 9;

    direction = 0;
    this->setPos(j_pos * 32, i_pos * 32);
}
