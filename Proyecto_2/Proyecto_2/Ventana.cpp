#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include "Ventana.h"
#include "AppContext.h"
#include "Mapa.h"
#include "Prim.h"


using namespace std;
using namespace sf;

Ventana::Ventana(int largo, int ancho) {
    ventana = new RenderWindow(VideoMode(largo, ancho), "Grafos");
    seleccion = new Seleccion();
    mapa = new Mapa();
    bucleJuego();
}

//Este es el bucle principal del juego, aqui se ejecutaran todas las opciones graficas del juego, asi como los eventes del mouse y teclas
void Ventana::bucleJuego() {

    while (this->ventana->isOpen()) {

        AppContext::getInstance().setWindow(ventana);

        //sf::Image icon;
        //icon.loadFromFile("Resources/icono.PNG");
        //ventana->setIcon(29, 27, icon.getPixelsPtr());

        if (AppContext::getInstance().getPantalla() == 1) {
            Texture texture;
            if (!texture.loadFromFile("Resources/Principal.JPG"))
            {
                cout << "Error al cargar imagen" << endl;
            }

            Sprite sprite(texture);
            sprite.setPosition(0.f, 0.f);
            ventana->clear();
            ventana->draw(sprite);
            ventana->display();

        }
        else if (AppContext::getInstance().getPantalla() == 2) {
            seleccion->bucleJugar(ventana);
            
        }
        else if (AppContext::getInstance().getPantalla() == 3) {
            mapa->bucleJugar(ventana);
        }
        else if (AppContext::getInstance().getPantalla() == 4) {
    
        }
        else if (AppContext::getInstance().getPantalla() == 6) {

        }



        Event event;
        while (this->ventana->pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                ventana->close();
            }
            else if (event.type == sf::Event::MouseButtonPressed) {

                cout << Mouse::getPosition(*ventana).x << " , " << Mouse::getPosition(*ventana).y << endl;

                if (AppContext::getInstance().getPantalla() == 1) {
                    clickPantalla(Mouse::getPosition(*ventana).x, Mouse::getPosition(*ventana).y);
                }

                if (AppContext::getInstance().getPantalla() == 2) {
                    seleccion->clickPantalla(Mouse::getPosition(*ventana).x, Mouse::getPosition(*ventana).y);
                }

                if (AppContext::getInstance().getPantalla() == 3) {
                    mapa->clickPantalla(Mouse::getPosition(*ventana).x, Mouse::getPosition(*ventana).y);
                }

                if (AppContext::getInstance().getPantalla() == 6) {

                }

            }
            else if (event.type == sf::Event::KeyPressed) {

                if (AppContext::getInstance().getPantalla() == 6) {
                    //areaJuego->eventoTeclas(event, NULL);
                }

            }
            else if (event.type == sf::Event::MouseMoved) {
                mapa->moverLinea();
            }
             else if (event.key.code == sf::Keyboard::Enter) {

                mapa->enter();
            }
            else if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode < 128)
                {
                    char letra = static_cast<char>(event.text.unicode);
                    mapa->ingresarPeso(letra);
                }
            }
        }
    }
}

//Se detecta si se hizo click en algunos de los botones de la pantalla principal
void Ventana::clickPantalla(int x, int y) {

    if (x > 864 && x < 1128 && y > 353 && y < 425) {
        cout << "Jugar" << endl;
        AppContext::getInstance().setPantalla(2);
    }
    else {
        // create the graph given in above fugure
        int V = 9;
        Prim g(V);

        // making above shown graph
        g.anadirArista(0, 1, 4);
        g.anadirArista(0, 7, 8);
        g.anadirArista(1, 2, 8);
        g.anadirArista(1, 7, 11);
        g.anadirArista(2, 3, 7);
        g.anadirArista(2, 8, 2);
        g.anadirArista(2, 5, 4);
        g.anadirArista(3, 4, 9);
        g.anadirArista(3, 5, 14);
        g.anadirArista(4, 5, 10);
        g.anadirArista(5, 6, 2);
        g.anadirArista(6, 7, 1);
        g.anadirArista(6, 8, 6);
        g.anadirArista(7, 8, 7);

        g.prim();
    }
}
