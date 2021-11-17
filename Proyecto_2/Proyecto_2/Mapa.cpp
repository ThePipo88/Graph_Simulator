#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "Ventana.h"
#include "AppContext.h"
#include "Mapa.h"
#include "kruskal.h"
#include "Prim.h"
#include "Dijkstra.h"
#include "Warshall.h"

using namespace std;

kruskal *g;
Prim *pr;
Dijkstra *d;
Warshall *w;


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
    else {
        text2.setString("Dijkstra");
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
    else {
        text3.setString("Warshall");
    }
    text3.setFillColor(sf::Color::Red);
    text3.setStyle(sf::Text::Bold);
    text3.setCharacterSize(13);
    text3.setPosition(26, 192);

    sf::Text result;
    result.setFont(font);
    result.setString(resultado);
    result.setFillColor(sf::Color::White);
    result.setStyle(sf::Text::Bold);
    result.setCharacterSize(13);
    result.setPosition(26, 250);


    ventana->clear();
    ventana->draw(sprite);
    ventana->draw(text1);
    ventana->draw(text2);
    ventana->draw(text3);
    ventana->draw(result);

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
            else if (tipo == "Dijkstra") {

                arista[i]->dibujarLinea(AppContext::getInstance().getWindow());

                for (int j = 0; j < d->getDatos().size(); j++) {
                    if (j+1 < d->getDatos().size()) {
                        if (arista[i]->getLetra1() == d->getDatos()[j] && arista[i]->getLetra2() == d->getDatos()[j+1] ||
                            arista[i]->getLetra1() == d->getDatos()[j + 1] && arista[i]->getLetra2() == d->getDatos()[j]) {
                            arista[i]->dibujarLineaDijkstra(AppContext::getInstance().getWindow());
                        }
                    }
                }
            }
            else if (tipo == "Warshall") {

                arista[i]->dibujarLinea(AppContext::getInstance().getWindow());

                for (int j = 0; j < w->getDatos().size(); j++) {
                    if (j + 1 < w->getDatos().size()) {
                        if (arista[i]->getLetra1() == w->getDatos()[j] && arista[i]->getLetra2() == w->getDatos()[j + 1] ||
                            arista[i]->getLetra1() == w->getDatos()[j + 1] && arista[i]->getLetra2() == w->getDatos()[j]) {
                            arista[i]->dibujarLineaDijkstra(AppContext::getInstance().getWindow());
                        }
                    }
                }
            }
        }
    }

    if (vertice.size() > 0) {
        for (int i = 0; i < vertice.size(); i++) {
            if (tipo == "normal" || tipo == "Dijkstra" || tipo == "Warshall") {
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

    if (selct) {

        sf::Text text3;
        sf::Font font;
        if (!font.loadFromFile("Resources/arial.ttf"))
        {
            // error...
        }

        text3.setFont(font);
        text3.setCharacterSize(24);
        text3.setFillColor(sf::Color::White);
        text3.setStyle(sf::Text::Bold);
        text3.setPosition(800, 2);

        sf::Text let;
        if (!font.loadFromFile("Resources/arial.ttf"))
        {
            // error...
        }

        let.setFont(font);
        let.setCharacterSize(24);
        let.setFillColor(sf::Color::Red);
        let.setStyle(sf::Text::Bold);
        let.setPosition(1130, 2);
        let.setString(p);

        if (!selct1) {
            text3.setString("Seleccione el nodo inicial");
            ventana->draw(text3);
            ventana->draw(let);
        }
        else if (!selct2) {
            text3.setString("Seleccione el nodo final");
            ventana->draw(text3);
            ventana->draw(let);
        }
        else {

            if(Gd == 1){

                d = new Dijkstra();

                for (int i = 0; i < vertice.size(); i++) {
                    string letra = vertice[i]->getLetra1();
                    char arry[1];
                    copy(letra.begin(), letra.end(), arry);
                    d->insertarNodo(arry[0]);
                }

                resultado = "Dijkstra \n";
                for (int i = 0; i < datos.size(); i++) {
                    string letra1 = getLetra(datos[i].n1, "1");
                    char arry1[1];

                    string letra2 = getLetra(datos[i].n2, "1");
                    char arry2[1];

                    copy(letra1.begin(), letra1.end(), arry1);
                    copy(letra2.begin(), letra2.end(), arry2);

                    d->insertarArista(arry1[0], arry2[0], datos[i].p);
                }

                cout << iniFin.size();

                d->dijkstra(iniFin[0], iniFin[1]);

                for (int i = 0; i < d->getDatos().size(); i++) {
                    resultado += d->getDatos()[i] + "\n";
                }

                tipo = "Dijkstra";
                selct = false;

            }
            else {

                resultado = "Warshall \n";

                w = new Warshall(V+1, E);

                for (int i = 0; i < datos.size(); i++) {
                    w->createGraph(datos[i].n1+1,datos[i].n2+1,datos[i].p);
                }

                w->Floyd();
                w->print_path(iniFin[0], iniFin[1]);

                for (int i = 0; i < w->getDatos().size(); i++) {
                    resultado += w->getDatos()[i] + "\n";
                }
                tipo = "Warshall";
                selct = false;
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
        arista.clear();
        vertice.clear();
        V = 0;
        E = 0;
        datos.clear();
        letras.clear();
        resultado = "";
        letras = { "Z","Y","X","W","V","U","T","S","R","Q","P","O","Ñ","N","M","L","K","J","I","H","G","F","E","D","C","B","A" };
        tipo = "normal";
        selct1 = false;
        selct2 = false;
        accion = "Crear vertices";
        init = false;
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
    else if (x > 1833 && x < 1879 && y > 36 && y < 96) {
        cout << "Eliminar" << endl;
        arista.clear();
        vertice.clear();
        V = 0; 
        E = 0;
        datos.clear();
        letras.clear();
        resultado = "";
        letras = { "Z","Y","X","W","V","U","T","S","R","Q","P","O","Ñ","N","M","L","K","J","I","H","G","F","E","D","C","B","A" };
        tipo = "normal";
        selct1 = false;
        selct2 = false;
        accion = "Crear vertices";
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
                resultado += "Kruskal \n";

                for (int i = 0; i < g->getDatos().size(); i++) {
                    int n1 = g->getDatos()[i].first;
                    int n2 = g->getDatos()[i].second;

                    cout << getLetra(n1, "1") + "-" + getLetra(n2, "1") << endl;
                    resultado += getLetra(n1, "1") + "-" + getLetra(n2, "1") +"\n";
                }
                tipo = "kruskal";
                cout << "\nWeight of MST is " << rs;
            }
            else {
                tipo = "normal";
                resultado = "";
            }
        }
        else {

            if (tipo == "normal") {
                iniFin.clear();
                Gd = 1;
                selct = true;    
               
            }
            else {
                tipo = "normal";
                resultado = "";
                selct = false;
                selct1 = false;
                selct2 = false;
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
                resultado += "Prim \n";
                for (int i = 0; i < pr->getDatos().size(); i++) {
                    int n1 = pr->getDatos()[i].first;
                    int n2 = pr->getDatos()[i].second;

                    cout << getLetra(n1, "1") + "-" + getLetra(n2, "1") << endl;
                    resultado += getLetra(n1, "1") + "-" + getLetra(n2, "1") + "\n";
                }
                tipo = "Prim";
            }
            else {
                tipo = "normal";
                resultado = "";
            }
        }
        else {

            if (tipo == "normal") {
                iniFin.clear();
                Gd = 2;
                selct = true;
            }
            else {
                tipo = "normal";
                resultado = "";
                selct = false;
                selct1 = false;
                selct2 = false;
            }

        }
    }
    else {

            tipo = "normal";

            if (accion == "Crear vertices") {
                if (init) {
                    x1 = x;
                    y1 = y;
                    VerticeGrafico* newVertice = new VerticeGrafico();
                    newVertice->setX1(x);
                    newVertice->setY1(y);
                    newVertice->setNumero(V);
                    newVertice->setLetra1(letras.back());
                    letras.pop_back();
                    vertice.push_back(newVertice);
                    V++;
                    cout << V << endl;
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

                        

                        for (int i = 0; i < vertice.size(); i++) {
                            if (vertice[i]->getX1() + 10 >= x1 && vertice[i]->getX1() - 10 <= x1 && vertice[i]->getY1() + 10 >= y1 && vertice[i]->getY1() - 10 <= y1) {
                                na->setLetra1(vertice[i]->getLetra1());
                                arista.push_back(na);
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

    if (selct) {
        for (int i = 0; i < letrasResp.size(); i++) {
            if (peso == letrasResp[i]) {
                cout << "Letra encontrada" << endl;
                iniFin.push_back(peso);
            }
        }
    }  

    if (!selct) {
        if (peso == 'G' || peso == 'g') {
            cout << "Guardar" << endl;
                ofstream fichero("Datos.txt");
                fichero << "-";
                for (int i = 0; i < vertice.size(); i++) {
                    fichero << vertice[i]->getLetra1() << "/" << vertice[i]->getX1() << "/" << vertice[i]->getY1() << "/" << vertice[i]->getNumero() << endl;
                }
                fichero << "#" << endl;
                for (int i = 0; i < arista.size(); i++) {
                    fichero << arista[i]->getLetra1() << "/" << arista[i]->getLetra2() << "/" << arista[i]->getPeso() << "/" << arista[i]->getX1()<< "/" << arista[i]->getY1() << "/" << arista[i]->getX2() << "/" << arista[i]->getY2() << endl;
                }
                fichero << "&" << endl;
                fichero.close();
                p = "";
            
        }
        else if (peso == 'C' || peso == 'c') {
            cout << "Cargar" << endl;
            arista.clear();
            vertice.clear();
            V = 0;
            E = 0;
            datos.clear();
            letras.clear();
            resultado = "";
            letras = { "Z","Y","X","W","V","U","T","S","R","Q","P","O","Ñ","N","M","L","K","J","I","H","G","F","E","D","C","B","A" };
            tipo = "normal";
            selct1 = false;
            selct2 = false;
            accion = "Crear vertices";
            init = false;
            string dato = "";

            ifstream f;

            f.open("Datos.txt");
            if (!f) {
                cout << "Error abriendo el fichero" << endl;
            }

            dato = f.get();

            string cadena = "";
            char caracter;
            bool term1 = false;
            bool term2 = false;
            int cont = 0;

            caracter = f.get();

            while (!f.eof()) {

                while (caracter != '#' && !term1) {

                    while (caracter != '\n') {
                        cadena += caracter;
                        caracter = f.get();
                    }  

                    vector<string> v;

                    tokenize(cadena, '/', v);

                    VerticeGrafico* newVertice = new VerticeGrafico();
                    newVertice->setX1(stoi(v[1]));
                    newVertice->setY1(stoi(v[2]));
                    newVertice->setNumero(stoi(v[3]));
                    newVertice->setLetra1(v[0]);
                    letras.pop_back();
                    vertice.push_back(newVertice);
                    V++;
                    v.clear();
                    cadena = "";

                    caracter = f.get();

                    if (caracter == '#') {
                        term1 = true;
                    }
                }    
                caracter = f.get();
                caracter = f.get();

                while (caracter != '&' && !term2) {

                    while (caracter != '\n') {
                        cadena += caracter;
                        caracter = f.get();
                    }

                    vector<string> v;
                    tokenize(cadena, '/', v);

                    AristaGrafico* na = new AristaGrafico();
                    na->setLetra1(v[0]);
                    na->setLetra2(v[1]);
                    na->setPeso(stoi(v[2]));
                    na->setX1(stoi(v[3]));
                    na->setY1(stoi(v[4]));
                    na->setX2(stoi(v[5]));
                    na->setY2(stoi(v[6]));

                    if (AppContext::getInstance().getTipo() == 1) {
                        na->setDirigido(false);
                    }
                    else {
                        na->setDirigido(true);
                    }
                    char arry1[1];
                    copy(v[0].begin(), v[0].end(), arry1);

                    char arry2[1];
                    copy(v[1].begin(), v[1].end(), arry2);

                    for (int i = 0; i < vertice.size(); i++) {
                        if (vertice[i]->getLetra1() == v[0]) {
                            nI = vertice[i]->getNumero();
                        }
                    }
                    
                    for (int i = 0; i < vertice.size(); i++) {
                        if (vertice[i]->getLetra1() == v[1]) {
                            nF = vertice[i]->getNumero();
                        }
                    }

                    datos.push_back({ nI, nF,stoi(v[2])});

                    arista.push_back(na);

                    E++;
                    v.clear();
                    cadena = "";

                    caracter = f.get();

                    if (caracter == '&') {
                        term2 = true;
                    }
                }
            }
            f.close();
            p = "";
           
        }
    }
}

void Mapa::tokenize(std::string const& str, const char delim,std::vector<std::string>& out)
{
    size_t start;
    size_t end = 0;

    while ((start = str.find_first_not_of(delim, end)) != std::string::npos)
    {
        end = str.find(delim, start);
        out.push_back(str.substr(start, end - start));
    }
}

void Mapa::enter() {

    if (!selct1 && selct) {   
        if (iniFin.size() >= 1) {
            selct1 = true;
        }
        p = "";
    }
    else if (!selct2 && selct) {
        if (iniFin.size() >= 2) {
            selct2 = true;
        }
        p = "";
    }
    else {
        arista[arista.size() - 1]->setPeso(stoi(p));
        pS = stoi(p);
        vent = false;
        datos.push_back({ nI, nF,pS });
        p = "";
    }  
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

int Mapa::getNum(char letra) {

    for (int i = 0; i < letrasResp.size(); i++) {
        if (letrasResp[i] == letra) {
            return i;
        }
    }


    return 0;
}