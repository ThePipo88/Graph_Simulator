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

    ventana->clear();
    ventana->draw(sprite);
    ventana->display();
}

void Mapa::clickPantalla(int x, int y) {

    if (x > 16 && x < 73 && y > 922 && y < 980) {
        cout << "Retroceso" << endl;
        AppContext::getInstance().setPantalla(1);
    }
}