#pragma once
#include <iostream>
#include <SFML\Graphics\RenderWindow.hpp>


using namespace sf;
using namespace std;

typedef pair<int, int> par;

class AppContext {
private:
	AppContext();
	int pantalla;
	bool partidaCargada;
	string datosPartida;
	RenderWindow* ventana;
	Event* ev;
	int tipo;
	vector<par> datosKrukal;
	//Partida* partida;
public:
	static AppContext& getInstance();
	int getPantalla();
	int getTipo();
	vector<par> getResultadoKruskal();
	void setPantalla(int p);
	void setPartidaCargada(bool partida);
	bool getPartidaCargada();
	void setDatosPartida(string datos);
	void setTipo(int t);
	string getDatosPartida();
	RenderWindow* getWindow();
	void setWindow(RenderWindow* v);
	Event* getEvent();
	void setEvent(Event* e);
	void setDatosKruskal(int u, int v);
};
