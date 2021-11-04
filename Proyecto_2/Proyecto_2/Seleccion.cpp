#include <SFML/Graphics.hpp>
#include <iostream>
#include "Ventana.h"
#include "AppContext.h"
#include "Seleccion.h"



Seleccion::Seleccion() {

}

void Seleccion::bucleJugar(RenderWindow*& ventana) {

    Texture texture;
    //tab = new Tablero();
    evento1 = new Event;
    if (!texture.loadFromFile("Resources/Crear.JPG"))
    {
        cout << "Error al cargar imagen" << endl;
    }
    Sprite sprite(texture);
    sprite.setPosition(0.f, 0.f);

    ventana->clear();
    ventana->draw(sprite);
    ventana->display();
}

void Seleccion::clickPantalla(int x, int y) {

    if (x > 116 && x < 379 && y > 875 && y < 944) {
        cout << "Retroceso" << endl;
        AppContext::getInstance().setPantalla(1);
    }
    else if (x > 848 && x < 1112 && y > 272 && y < 345) {
        cout << "Dirigido" << endl;
        AppContext::getInstance().setPantalla(3);
    }
    else if (x > 847 && x < 1112 && y > 429 && y < 501) {
        cout << "No dirigido" << endl;
        AppContext::getInstance().setPantalla(3);
    }

}
