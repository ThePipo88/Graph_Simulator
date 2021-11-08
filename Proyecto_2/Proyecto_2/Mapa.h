#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "VerticeGrafico.h"
#include "AristaGrafico.h"

using namespace std;
using namespace sf;

class Mapa {

private:
	RenderWindow* vnt;
	Event* evento1;
	vector<String> letras = { "A","B","c","D","E","F","G","H","I","J","K","L","M","N","Ñ","O","P","Q","R","S","T","U","V","W","X","Y","Z" };
	vector<VerticeGrafico*> vertice;
	vector<AristaGrafico*> arista;
	bool vent = false;
	int cant = 0;
	bool init = false;
	float x1, y1;
	float x2, y2;
	string accion = "Crear vertices";
	string p = "";

public:
	Mapa();
	void bucleJugar(RenderWindow*& ventana);
	void clickPantalla(int x, int y);
	void moverLinea();
	void ingresarPeso(char peso);
	void enter();
};