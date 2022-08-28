#include <iostream>
#include "AppContext.h"

using namespace std;

// This class is of type Singlenton, and is responsible for saving important game data
AppContext::AppContext()
{

	pantalla = 1;
	ventana = nullptr;
}

AppContext &AppContext::getInstance()
{
	static AppContext INSTANCE;
	return INSTANCE;
}

int AppContext::getPantalla()
{
	return this->pantalla;
}

int AppContext::getTipo()
{
	return this->tipo;
}

void AppContext::setPantalla(int p)
{
	this->pantalla = p;
}

void AppContext::setTipo(int t)
{
	this->tipo = t;
}

RenderWindow *AppContext::getWindow()
{
	return ventana;
}

void AppContext::setWindow(RenderWindow *v)
{
	this->ventana = v;
}

Event *AppContext::getEvent()
{
	return ev;
}

void AppContext::setEvent(Event *e)
{
	ev = e;
}

void AppContext::setPartidaCargada(bool partida)
{
	this->partidaCargada = partida;
}

bool AppContext::getPartidaCargada()
{
	return this->partidaCargada;
}

void AppContext::setDatosPartida(string datos)
{
	this->datosPartida = datos;
}

string AppContext::getDatosPartida()
{
	return this->datosPartida;
}

vector<par> AppContext::getResultadoKruskal()
{
	return datosKrukal;
}

void AppContext::setDatosKruskal(int u, int v)
{
	datosKrukal.push_back({u, v});
}