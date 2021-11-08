#pragma once
#include <iostream>
#include <SFML\Graphics\RenderWindow.hpp>


using namespace sf;
using namespace std;

class AppContext {
private:
	AppContext();
	int pantalla;
	bool partidaCargada;
	string datosPartida;
	RenderWindow* ventana;
	Event* ev;
	int tipo;
	//Partida* partida;
public:
	static AppContext& getInstance();
	int getPantalla();
	int getTipo();
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
};