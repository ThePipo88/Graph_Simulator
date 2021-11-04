#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

class Mapa {

private:
	RenderWindow* vnt;
	Event* evento1;

public:
	Mapa();
	void bucleJugar(RenderWindow*& ventana);
	void clickPantalla(int x, int y);
};