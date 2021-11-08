#include <SFML/Graphics.hpp>
#include <iostream>
#include "Ventana.h"
#include "AppContext.h"
#include "Mapa.h"



Mapa::Mapa() {

}

void Mapa::bucleJugar(RenderWindow*& ventana) {

    Texture texture;
    //tab = new Tablero();
    evento1 = new Event;
    if (!texture.loadFromFile("Resources/Mapa4.PNG"))
    {
        cout << "Error al cargar imagen" << endl;
    }
    Sprite sprite(texture);
    sprite.setPosition(0.f, 0.f);

    sf::Text text1;
    sf::Font font;
    if (!font.loadFromFile("Resources/arial.ttf"))
    {
        // error...
    }
    text1.setFont(font); 
    text1.setString(accion);
    text1.setFillColor(sf::Color::Red);
    text1.setStyle(sf::Text::Bold);
    text1.setCharacterSize(13);
    text1.setPosition(26, 80);

    ventana->clear();
    ventana->draw(sprite);
    ventana->draw(text1);

    if (arista.size() > 0) {
        for (int i = 0; i < arista.size(); i++) {
            arista[i]->dibujarLinea(AppContext::getInstance().getWindow());
        }
    }

    if (vertice.size() > 0) {
        for (int i = 0; i < vertice.size(); i++) {
            vertice[i]->dibujarVertice(AppContext::getInstance().getWindow());
        }
    }

    if (vent) {
        Texture peso;
        peso.loadFromFile("Resources/pesos.PNG");
        Sprite p1(peso);
        p1.setPosition(750.f, 400.f);
        sf::Text text3;
        sf::Font font;
        if (!font.loadFromFile("Resources/arial.ttf"))
        {
            // error...
        }

        text3.setFont(font);
        text3.setString(p);
        text3.setCharacterSize(24);
        text3.setFillColor(sf::Color::Red);
        text3.setStyle(sf::Text::Bold);
        text3.setPosition(970, 490);

        ventana->draw(p1);
        ventana->draw(text3);
    }

    ventana->display();
}

void Mapa::clickPantalla(int x, int y) {

    if (x > 16 && x < 73 && y > 922 && y < 980) {
        cout << "Retroceso" << endl;
        AppContext::getInstance().setPantalla(1);
    }
    else if (x > 21 && x < 128 && y > 75 && y < 103) {
        cout << "Arista" << endl;
        if (accion == "Crear aristas") {
            accion = "Crear vertices";
        }
        else if(accion == "Crear vertices"){
            accion = "Crear aristas";
        }
        
    }
    else {

        if (AppContext::getInstance().getTipo() == 1) {


            if (accion == "Crear vertices") {
                if (init) {
                    x1 = x;
                    y1 = y;
                    VerticeGrafico* newVertice = new VerticeGrafico();
                    newVertice->setX1(x);
                    newVertice->setY1(y);
                    newVertice->setLetra1(letras.back());
                    letras.pop_back();
                    vertice.push_back(newVertice);
                }
                else {
                    init = true;
                }
            }
            else {

                if (vertice.size() > 2) {

                    cout << vertice.size() << endl;

                    if (cant == 0) {

                        AristaGrafico* na = new AristaGrafico();
                        x1 = Mouse::getPosition(*AppContext::getInstance().getWindow()).x;
                        y1 = Mouse::getPosition(*AppContext::getInstance().getWindow()).y;
                        x2 = Mouse::getPosition(*AppContext::getInstance().getWindow()).x;
                        y2 = Mouse::getPosition(*AppContext::getInstance().getWindow()).y;

                        cout << arista.size() << endl;

                        for (int i = 0; i < vertice.size(); i++) {
                            if (vertice[i]->getX1() + 10 >= x1 && vertice[i]->getX1() - 10 <= x1 && vertice[i]->getY1() + 10 >= y1 && vertice[i]->getY1() - 10 <= y1) {
                                arista.push_back(na);
                                cout << "Entroo" << endl;
                                x1 = vertice[i]->getX1();
                                y1 = vertice[i]->getY1();
                                x2 = vertice[i]->getX1();
                                y2 = vertice[i]->getY1();
                                arista[arista.size() - 1]->setX1(x1);
                                arista[arista.size() - 1]->setY1(y1);
                                arista[arista.size() - 1]->setX2(x1);
                                arista[arista.size() - 1]->setY2(y1);
                                cant++;
                            }
                        }
                    }
                    else if (cant == 1) {

                        x1 = Mouse::getPosition(*AppContext::getInstance().getWindow()).x;
                        y1 = Mouse::getPosition(*AppContext::getInstance().getWindow()).y;

                        for (int i = 0; i < vertice.size(); i++) {
                            if (vertice[i]->getX1() + 10 >= x1 && vertice[i]->getX1() - 10 <= x1 && vertice[i]->getY1() + 10 >= y1 && vertice[i]->getY1() - 10 <= y1) {
                                cout << "Entroo" << endl;
                                x2 = vertice[i]->getX1();
                                y2 = vertice[i]->getY1();
                                arista[arista.size() - 1]->setX2(x2);
                                arista[arista.size() - 1]->setY2(y2);
                                cant = 0;
                                vent = true;
                            }
                        }

                    }
                }

            }
        }
        else {

        }
    }
}

void Mapa::moverLinea() {
    if (cant == 1) {
        x2 = Mouse::getPosition(*AppContext::getInstance().getWindow()).x;
        y2 = Mouse::getPosition(*AppContext::getInstance().getWindow()).y;
        arista[arista.size() - 1]->setX2(x2);
        arista[arista.size() - 1]->setY2(y2);
    }
}

void Mapa::ingresarPeso(char peso) {
    p += peso;
}

void Mapa::enter() {
    arista[arista.size() - 1]->setPeso(stoi(p));
    p = "";
    vent = false;
}