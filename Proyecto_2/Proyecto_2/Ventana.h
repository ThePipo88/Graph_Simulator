#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "AppContext.h"
#include "Seleccion.h"
#include "Mapa.h"

using namespace std;
using namespace sf;

class Ventana {

private:
	RenderWindow* ventana;
	Seleccion *seleccion;
	Mapa* mapa;
	ifstream f;

public:
	Ventana(int x, int y);
	void bucleJuego();
	void clickPantalla(int x, int y);
};