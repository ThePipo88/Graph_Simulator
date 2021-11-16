#include <SFML/Graphics.hpp>
#include <iostream>
#include "Ventana.h"
#include "AppContext.h"
#include "Mapa.h"
#include "kruskal.h"
#include "Prim.h"
#include "Dijkstra.h"


kruskal* g;
Prim* pr;
Dijkstra* d;


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

    sf::Text text2;
    text2.setFont(font);
    if (AppContext::getInstance().getTipo() == 1) {
        text2.setString("Kruskal");
    }
    text2.setFillColor(sf::Color::Red);
    text2.setStyle(sf::Text::Bold);
    text2.setCharacterSize(13);
    text2.setPosition(26, 137);

    sf::Text text3;
    text3.setFont(font);
    if (AppContext::getInstance().getTipo() == 1) {
        text3.setString("Prim");
    }
    text3.setFillColor(sf::Color::Red);
    text3.setStyle(sf::Text::Bold);
    text3.setCharacterSize(13);
    text3.setPosition(26, 192);

    ventana->clear();
    ventana->draw(sprite);
    ventana->draw(text1);
    ventana->draw(text2);
    ventana->draw(text3);

    if (arista.size() > 0) {
        for (int i = 0; i < arista.size(); i++) {
            if (tipo == "normal") {
                arista[i]->dibujarLinea(AppContext::getInstance().getWindow());
            }
            else if (tipo == "kruskal") {
                for (int j = 0; j < g->getDatos().size(); j++) {
                    if (arista[i]->getLetra1() == getLetra(g->getDatos()[j].first,"1") && arista[i]->getLetra2() == getLetra(g->getDatos()[j].second, "1") ||
                        arista[i]->getLetra1() == getLetra(g->getDatos()[j].second, "1") && arista[i]->getLetra2() == getLetra(g->getDatos()[j].first,"1")) {
                        arista[i]->dibujarLinea(AppContext::getInstance().getWindow());
                    }
                }
            }
            else if (tipo == "Prim") {
                for (int j = 0; j < pr->getDatos().size(); j++) {
                    if (arista[i]->getLetra1() == getLetra(pr->getDatos()[j].first, "1") && arista[i]->getLetra2() == getLetra(pr->getDatos()[j].second, "1") ||
                        arista[i]->getLetra1() == getLetra(pr->getDatos()[j].second, "1") && arista[i]->getLetra2() == getLetra(pr->getDatos()[j].first, "1")) {
                        arista[i]->dibujarLinea(AppContext::getInstance().getWindow());
                    }
                }
            }
        }
    }

    if (vertice.size() > 0) {
        for (int i = 0; i < vertice.size(); i++) {
            if (tipo == "normal") {
                vertice[i]->dibujarVertice(AppContext::getInstance().getWindow());
            }
            else if (tipo == "kruskal") {
                for (int j = 0; j < g->getDatos().size(); j++) {
                    if (vertice[i]->getLetra1() == getLetra(g->getDatos()[j].first, "1") || vertice[i]->getLetra1() == getLetra(g->getDatos()[j].second, "1")) {
                        vertice[i]->dibujarVertice(AppContext::getInstance().getWindow());
                    }
                }
            }
            else if (tipo == "Prim") {
                for (int j = 0; j < pr->getDatos().size(); j++) {
                    if (vertice[i]->getLetra1() == getLetra(pr->getDatos()[j].first, "1") || vertice[i]->getLetra1() == getLetra(pr->getDatos()[j].second, "1")) {
                        vertice[i]->dibujarVertice(AppContext::getInstance().getWindow());
                    }
                }
            }
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
    else if (x > 21 && x < 128 && y > 130 && y < 159) {

        cout << "Kruskal" << endl;
        if (AppContext::getInstance().getTipo() == 1) {

            if (tipo == "normal") {
                g = new kruskal(V, E);

                for (int i = 0; i < datos.size(); i++) {
                    cout << datos[i].n1 << endl;
                    g->agregarArista(datos[i].n1, datos[i].n2, datos[i].p);
                }
                int rs = g->kruskalAlg();
                cout << "Kruskal" << endl;
                for (int i = 0; i < g->getDatos().size(); i++) {
                    int n1 = g->getDatos()[i].first;
                    int n2 = g->getDatos()[i].second;

                    cout << getLetra(n1, "1") + "-" + getLetra(n2, "1") << endl;
                }
                tipo = "kruskal";
                cout << "\nWeight of MST is " << rs;
            }
            else {
                tipo = "normal";
            }
        }
        else {

            if (tipo == "normal") {

                d = new Dijkstra();

                for (int i = 0; i < vertice.size(); i++) {
                    string letra =  vertice[i]->getLetra1();
                    char arry[1];
                    copy(letra.begin(), letra.end(), arry);
                    d->insertarNodo(arry[0]);
                }

                for (int i = 0; i < datos.size(); i++) {
                    string letra1 = getLetra(datos[i].n1,"1");
                    char arry1[1];

                    string letra2 = getLetra(datos[i].n2, "1");
                    char arry2[1];

                    copy(letra1.begin(), letra1.end(), arry1);
                    copy(letra2.begin(), letra2.end(), arry2);

                    d->insertarArista(arry1[0],arry2[0],datos[i].p);
                }

                d->dijkstra('Z', 'W');
            }
        }
    }
    else if (x > 21 && x < 128 && y > 185 && y < 214) {

        if (AppContext::getInstance().getTipo() == 1) {

            if (tipo == "normal") {
                pr = new Prim(V);

                for (int i = 0; i < datos.size(); i++) {
                    pr->anadirArista(datos[i].n1, datos[i]
                        .n2, datos[i].p);
                }
                pr->prim();
                cout << "Prim" << endl;
                for (int i = 0; i < pr->getDatos().size(); i++) {
                    int n1 = pr->getDatos()[i].first;
                    int n2 = pr->getDatos()[i].second;

                    cout << getLetra(n1, "1") + "-" + getLetra(n2, "1") << endl;
                }
                tipo = "Prim";
            }
            else {
                tipo = "normal";
            }
        }
        else {

        }
    }
    else {

            tipo = "normal";

            if (accion == "Crear vertices") {
                if (init) {
                    x1 = x;
                    y1 = y;
                    cout <<V<< endl;
                    VerticeGrafico* newVertice = new VerticeGrafico();
                    newVertice->setX1(x);
                    newVertice->setY1(y);
                    newVertice->setNumero(V);
                    newVertice->setLetra1(letras.back());
                    letras.pop_back();
                    vertice.push_back(newVertice);
                    V++;
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
                        if (AppContext::getInstance().getTipo() == 1) {
                            na->setDirigido(false);
                        }
                        else {
                            na->setDirigido(true);
                        }
                        
                        x1 = Mouse::getPosition(*AppContext::getInstance().getWindow()).x;
                        y1 = Mouse::getPosition(*AppContext::getInstance().getWindow()).y;
                        x2 = Mouse::getPosition(*AppContext::getInstance().getWindow()).x;
                        y2 = Mouse::getPosition(*AppContext::getInstance().getWindow()).y;

                        cout << arista.size() << endl;

                        for (int i = 0; i < vertice.size(); i++) {
                            if (vertice[i]->getX1() + 10 >= x1 && vertice[i]->getX1() - 10 <= x1 && vertice[i]->getY1() + 10 >= y1 && vertice[i]->getY1() - 10 <= y1) {
                                na->setLetra1(vertice[i]->getLetra1());
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
                                E++;
                                nI = vertice[i]->getNumero();

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
                                arista[arista.size() - 1]->setLetra2(vertice[i]->getLetra1());
                                arista[arista.size() - 1]->setX2(x2);
                                arista[arista.size() - 1]->setY2(y2);

                                
                                int cx1 = arista[arista.size() - 1]->getX1();
                                int cx2 = arista[arista.size() - 1]->getX2();
                                int cy1 = arista[arista.size() - 1]->getY1();
                                int cy2 = arista[arista.size() - 1]->getY2();

                                cant = 0;
                                vent = true;
                                nF = vertice[i]->getNumero();
                            }
                        }

                    }
                }

            }
    }
}

void Mapa::moverLinea() {
    if (cant == 1) {
        x2 = Mouse::getPosition(*AppContext::getInstance().getWindow()).x;
        y2 = Mouse::getPosition(*AppContext::getInstance().getWindow()).y;
        arista[arista.size() - 1]->setX2(x2);
        arista[arista.size() - 1]->setY2(y2);

        arista[arista.size() - 1]->setX3(x2);
        arista[arista.size() - 1]->setY3(y2);
    }
}

void Mapa::ingresarPeso(char peso) {
    p += peso;
}

void Mapa::enter() {
    arista[arista.size() - 1]->setPeso(stoi(p));
    pS = stoi(p);
    vent = false;
    datos.push_back({ nI, nF,pS});
    p = "";
}

string Mapa::getLetra(int letra, string algoritmo) {

    if (algoritmo == "1") {
        for (int i = 0; i < vertice.size(); i++) {
            if (vertice[i]->getNumero() == letra) {
                return vertice[i]->getLetra1();
            }
        }
    }

    return "";
}