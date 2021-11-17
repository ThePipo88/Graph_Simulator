#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <functional>  
#include <algorithm>  
#include <queue>
#include <list>
#include "Dijkstra.h"



Dijkstra::Dijkstra() {
	this->v = v;
}

void Dijkstra::insertarNodo(char letra) {
	Nodo* aux;
	Nodo* nuevo = (Nodo*)malloc(sizeof(Nodo));
	fflush(stdin);
	nuevo->dato = letra;
	nuevo->siguiente = NULL;
	nuevo->adyacencia = NULL;
	nuevo->visitado = nuevo->terminado = 0; //Cero en codigo asci es igual a nulo
	nuevo->monto = -1; //-1 significa que a este nodo no se le asignado ningun valor
	nuevo->anterior = 0;//Cero en codigo asci es igual a nulo
	if (inicio == NULL) {
		inicio = nuevo;
	}
	else {
		aux = inicio;
		while (aux->siguiente != NULL) {
			aux = aux->siguiente;
		}
		aux->siguiente = nuevo;
	}
}

void Dijkstra::insertarArista(char ini, char fin, int peso) {

	Arista* nuevo = (Arista*)malloc(sizeof(Arista));
	nuevo->siguiente = NULL;
	Nodo* aux;
	Nodo* aux2;
	if (inicio == NULL) {
		printf("Error: El grafo está vacio\n");
		return;
	}
	fflush(stdin);
	nuevo->peso = peso;
	aux = inicio;
	aux2 = inicio;
	while (aux2 != NULL) {
		if (aux2->dato == fin) {
			break;
		}
		aux2 = aux2->siguiente;
	}
	if (aux2 == NULL) {
		printf("Error:Vertice no encontrado\n");
		return;
	}
	while (aux != NULL) {
		if (aux->dato == ini) {
			agregarArista(aux, aux2, nuevo);
			return;
		}
		aux = aux->siguiente;
	}
	if (aux == NULL)
		printf("Error:Vertice no encontrado\n");
}


void Dijkstra::agregarArista(Nodo* aux, Nodo* aux2, Arista* nuevo) {
	Arista* a;
	if (aux->adyacencia == NULL) {
		aux->adyacencia = nuevo;
		nuevo->vrt = aux2;
	}
	else {
		a = aux->adyacencia;
		while (a->siguiente != NULL)
			a = a->siguiente;
		nuevo->vrt = aux2;
		a->siguiente = nuevo;
	}
}

void Dijkstra::visualizarGrafo() {
	Nodo* aux = inicio;
	Arista* ar;
	printf("Nodos\n");
	while (aux != NULL) {
		printf("%c:    ", aux->dato);
		if (aux->adyacencia != NULL) {
			ar = aux->adyacencia;
			while (ar != NULL) {
				printf(" %c", ar->vrt->dato);
				ar = ar->siguiente;
			}
		}
		printf("\n");
		aux = aux->siguiente;
	}
	printf("\n");
}


void Dijkstra::recorridoAnchura() {
	Nodo* aux = desencolar();
	if (aux == NULL)
		return;
	printf("%c ", aux->dato);
	if (aux->adyacencia != NULL) {
		Arista* a = aux->adyacencia;
		while (a != NULL) {
			if (a->vrt->visitado == 0) {
				insertarCola(a->vrt);
				a->vrt->visitado = 1;
			}
			a = a->siguiente;
		}
	}
	recorridoAnchura();

}

void Dijkstra::recorridoProfundidad(Nodo* aux) {
	Arista* a;
	aux->visitado = 1;
	if (aux->adyacencia != NULL) {
		a = aux->adyacencia;
		while (a != NULL) {
			if (a->vrt->visitado == 0) {
				recorridoProfundidad(a->vrt);
			}
			a = a->siguiente;
		}
	}
	aux->terminado = 1;
	insertarPila(aux);
}

void Dijkstra::insertarPila(Nodo* aux) {
	Lista* nuevo = (Lista*)malloc(sizeof(Lista));
	nuevo->dato = aux;
	nuevo->siguiente = NULL;
	if (ini == NULL) {
		ini = nuevo;
		final = nuevo;
	}
	else {
		nuevo->siguiente = ini;
		ini = nuevo;
	}
}

void Dijkstra::insertarCola(Nodo* aux) {
	Lista* nuevo = (Lista*)malloc(sizeof(Lista));
	nuevo->dato = aux;
	nuevo->siguiente = NULL;
	if (ini == NULL) {
		ini = nuevo;
		final = nuevo;
	}
	else {
		final->siguiente = nuevo;
		final = nuevo;
	}
}

Nodo* Dijkstra::desencolar() {
	Lista* aux;
	if (ini == NULL) {
		return NULL;
	}
	else {
		aux = ini;
		ini = ini->siguiente;
		aux->siguiente = NULL;
		if (ini == NULL)
			final = NULL;
	}
	Nodo* resultado = aux->dato;
	free(aux);
	return resultado;
}

void Dijkstra::reiniciar() {
	if (inicio != NULL) {
		Nodo* aux = inicio;
		while (aux != NULL) {
			aux->visitado = aux->terminado = 0;
			aux = aux->siguiente;
		}
	}
}
//Lorem Ipsum 
void Dijkstra::dijkstra(char a, char b) { //Recibe dos vertices a nodo inicial y b nodo destino
	Nodo* aux = inicio;
	fflush(stdin);
	while (aux != NULL) {
		if (aux->dato == a) { // auxiliar va a estar apuntando a nodo inicial
			aux->terminado = 1; // va a ser igual a 1 ya que se va a utilizar como nodo de inicio 
			aux->monto = 0;
			break;
		}
		aux = aux->siguiente; // El while se va a seguir recorriendo 
	}
	if (aux == NULL) { // si auxiliar es igual a nulo lo que quiere decir es que no se encontro el nodo inicial
		printf("Vertice no encontrado\n"); // Se le envia un mensaje al usuario de que el vertice no se encontro
		return;
	}
	while (aux != NULL) { // mientras sea distinto de null
		Arista* a = aux->adyacencia; // se declara una arista va a ser igual a auxiliar en su parte de adyacencia, es decir al iniciode la lista de adyacencia de ese nodo
		while (a != NULL) { //Mientras esta lista de adyacencia sea diferente de nulo
			if (a->vrt->monto == -1 || (aux->monto + a->peso) < a->vrt->monto) { //si el vertice no se a visitado todavia o cuando se visita un nodo por segunda vez su monto es menos Si es menor cambia si no no
				a->vrt->monto = aux->monto + a->peso; //sumar cantidad del nodo que viene mas el peso de la arista
				a->vrt->anterior = aux->dato; // aqui se guarda el dato que venia
			}
			a = a->siguiente; // se pasa a la arista siguiente
		}
		aux = inicio; // auxiliar va a se igual al inicio
		Nodo* min = inicio; // nodo min va a ayudar a buscar el nodo que tiene un menor monto

		while (min->anterior == 0 || min->terminado == 1) // mientras vertice no tenga un nulo en el vertice anterior
			min = min->siguiente;
		while (aux != NULL) { //mientras auxiliar sea diferente de nulo 
			if (aux->monto < min->monto && aux->terminado == 0 && aux->anterior != 0) // se va a indentificar el minimo vertice que tiene el monto mas pequeno && el vertice no tiene que estar terminado && tiene que tener algo en el nodo anterior
				min = aux; // se recorre la lista de vertices para encontrar el minimo 
			aux = aux->siguiente; // se sigue recorriendo
		}
		aux = min;
		aux->terminado = 1; // el vertice se marca como terminado, y se van a recorrer de nuevo sus vertices adyacentes
		if (aux->dato == b) // se encontro el vertice al que se quiere llegar
			break;

	}
	while (aux->anterior != 0) { // se va a imprimir en pantalla para esto se va a utilizar una pila
		insertarPila(aux); // se inserta el aux en una pila 
		char temp = aux->anterior;
		aux = inicio;
		while (aux->dato != temp) { // aqui se va a buscar el nodo que esta anterior a aux en la lista
			aux = aux->siguiente; // se avanza 
		}
	}
	insertarPila(aux);
	while (ini != NULL) { // se va desencolando para imprimir los vertices en orden 
		string letra = "";
		letra += desencolar()->dato;
		cout << letra << " ";
		datos.push_back(letra);
	}
	printf("\n");
	reiniciar();
}

vector<string> Dijkstra::getDatos() {
	return datos;
}