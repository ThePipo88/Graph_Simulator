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
	vector<String> letras = { "Z","Y","X","W","V","U","T","S","R","Q","P","O","�","N","M","L","K","J","I","H","G","F","E","D","C","B","A"};
	vector<char> letrasResp = { 'Z','Y','X','W','V','U','T','S','R','Q','P','O','�','N','M','L','K','J','I','H','G','F','E','D','C','B','A' };
	vector<VerticeGrafico*> vertice;
	vector<AristaGrafico*> arista;
	vector<char> iniFin;
	vector<datos> datos;
	bool vent = false;
	bool selct = false;
	bool selct1 = false;
	bool selct2 = false;
	bool guardado = false;
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
	string resultado = "";
	char ltr1;
	char ltr2;
	int Gd;

public:
	Mapa();
	void bucleJugar(RenderWindow*& ventana);
	void clickPantalla(int x, int y);
	void moverLinea();
	void ingresarPeso(char peso);
	void enter();
	string getLetra(int letra, string algoritmo);
	char getLetraOrigin(string letra);
	void tokenize(std::string const& str, const char delim, std::vector<std::string>& out);
	int getNum(char letra);
};
