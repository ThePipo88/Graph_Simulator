#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include "Ventana.h"
#include "AppContext.h"
#include "Mapa.h"
#include "Warshall.h"

using namespace std;
using namespace sf;

Ventana::Ventana(int largo, int ancho)
{
    ventana = new RenderWindow(VideoMode(largo, ancho), "Grafos");
    seleccion = new Seleccion();
    mapa = new Mapa();
    bucleJuego();
}

// This is the main loop of the game, here all the graphic options of the game will be executed, as well as the events of the mouse and keys
void Ventana::bucleJuego()
{

    while (this->ventana->isOpen())
    {

        AppContext::getInstance().setWindow(ventana);

        if (AppContext::getInstance().getPantalla() == 1)
        {
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
        else if (AppContext::getInstance().getPantalla() == 2)
        {
            seleccion->bucleJugar(ventana);
        }
        else if (AppContext::getInstance().getPantalla() == 3)
        {
            mapa->bucleJugar(ventana);
        }
        else if (AppContext::getInstance().getPantalla() == 4)
        {
        }
        else if (AppContext::getInstance().getPantalla() == 6)
        {
        }

        Event event;
        while (this->ventana->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                ventana->close();
            }
            else if (event.type == sf::Event::MouseButtonPressed)
            {

                cout << Mouse::getPosition(*ventana).x << " , " << Mouse::getPosition(*ventana).y << endl;

                if (AppContext::getInstance().getPantalla() == 1)
                {
                    clickPantalla(Mouse::getPosition(*ventana).x, Mouse::getPosition(*ventana).y);
                }

                if (AppContext::getInstance().getPantalla() == 2)
                {
                    seleccion->clickPantalla(Mouse::getPosition(*ventana).x, Mouse::getPosition(*ventana).y);
                }

                if (AppContext::getInstance().getPantalla() == 3)
                {
                    mapa->clickPantalla(Mouse::getPosition(*ventana).x, Mouse::getPosition(*ventana).y);
                }

                if (AppContext::getInstance().getPantalla() == 6)
                {
                }
            }
            else if (event.type == sf::Event::KeyPressed)
            {

                if (AppContext::getInstance().getPantalla() == 6)
                {
                    // areaJuego->eventoTeclas(event, NULL);
                }
            }
            else if (event.type == sf::Event::MouseMoved)
            {
                mapa->moverLinea();
            }
            else if (event.key.code == sf::Keyboard::Enter)
            {

                mapa->enter();
            }
            else if (event.type == sf::Event::TextEntered)
            {
                if (event.text.unicode < 128)
                {
                    char letra = static_cast<char>(event.text.unicode);
                    mapa->ingresarPeso(letra);
                }
            }
        }
    }
}

// It is detected if some of the buttons on the main screen were clicked
void Ventana::clickPantalla(int x, int y)
{

    if (x > 864 && x < 1128 && y > 353 && y < 425)
    {
        cout << "Jugar" << endl;
        AppContext::getInstance().setPantalla(2);
    }
}
