#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "VerticeGrafico.h"
#include "AristaGrafico.h"

using namespace std;
using namespace sf;

struct datos {
	int n1;
	int n2;
	int p;
};

class Mapa {

private:
	RenderWindow* vnt;
	Event* evento1;
	vector<String> letras = { "A","B","c","D","E","F","G","H","I","J","K","L","M","N","Ñ","O","P","Q","R","S","T","U","V","W","X","Y","Z" };
	vector<VerticeGrafico*> vertice;
	vector<AristaGrafico*> arista;
	vector<datos> datos;
	bool vent = false;
	int cant = 0;
	int V = 0;
	int E = 0;
	int nI = 0;
	int nF = 0;
	int pS = 0;
	bool init = false;
	float x1, y1;
	float x2, y2;
	string accion = "Crear vertices";
	string p = "";
	string tipo = "normal";

public:
	Mapa();
	void bucleJugar(RenderWindow*& ventana);
	void clickPantalla(int x, int y);
	void moverLinea();
	void ingresarPeso(char peso);
	void enter();
	string getLetra(int letra, string algoritmo);
};
