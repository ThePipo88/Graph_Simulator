#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

class Seleccion {

private:
	RenderWindow* vnt;
	Event* evento1;
	//Tablero* tab;

public:
	Seleccion();
	void bucleJugar(RenderWindow*& ventana);
	void clickPantalla(int x, int y);
	//void procesarEventos(RenderWindow*& ventana);


};
