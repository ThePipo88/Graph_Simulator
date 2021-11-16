#include <SFML/Graphics.hpp>
#include <iostream>
#include <functional>  
#include <algorithm>  
#include <queue>
#include <list>

using namespace std;

struct Arista;

struct Nodo{
	char dato;
	Nodo* siguiente;
	Arista* adyacencia;
	int visitado,terminado;
	int monto;
	char anterior;
};

struct Arista{
	Nodo * vrt;
	Arista* siguiente;
	int peso;
};

struct Lista{
	Nodo * dato;
	Lista* siguiente;
};

class Dijkstra {

private:
	int v;
	Nodo* inicio = NULL;
	Lista* ini = NULL;
	Lista* final = NULL;

public:
	Dijkstra();
	void insertarNodo(char letra);
	void agregarArista(Nodo* aux, Nodo* aux2, Arista* nuevo);
	void insertarArista(char ini, char fin, int peso);
	void visualizarGrafo();
	void recorridoAnchura();
	void recorridoProfundidad(Nodo* aux);
	void insertarPila(Nodo* aux);
	void insertarCola(Nodo* aux);
	Nodo* desencolar();
	void reiniciar();
	void dijkstra(char a, char b);
};
