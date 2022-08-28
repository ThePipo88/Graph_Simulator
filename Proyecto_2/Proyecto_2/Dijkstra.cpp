#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <functional>
#include <algorithm>
#include <queue>
#include <list>
#include "Dijkstra.h"

Dijkstra::Dijkstra()
{
	this->v = v;
}

void Dijkstra::insertarNodo(char letra)
{
	Nodo *aux;
	Nodo *nuevo = (Nodo *)malloc(sizeof(Nodo));
	fflush(stdin);
	nuevo->dato = letra;
	nuevo->siguiente = NULL;
	nuevo->adyacencia = NULL;
	nuevo->visitado = nuevo->terminado = 0; // Zero in asci code is equal to null
	nuevo->monto = -1;						//-1 means this node has not been assigned a value
	nuevo->anterior = 0;					// Zero in asci code is equal to null
	if (inicio == NULL)
	{
		inicio = nuevo;
	}
	else
	{
		aux = inicio;
		while (aux->siguiente != NULL)
		{
			aux = aux->siguiente;
		}
		aux->siguiente = nuevo;
	}
}

void Dijkstra::insertarArista(char ini, char fin, int peso)
{

	Arista *nuevo = (Arista *)malloc(sizeof(Arista));
	nuevo->siguiente = NULL;
	Nodo *aux;
	Nodo *aux2;
	if (inicio == NULL)
	{
		printf("Error: El grafo est� vacio\n");
		return;
	}
	fflush(stdin);
	nuevo->peso = peso;
	aux = inicio;
	aux2 = inicio;
	while (aux2 != NULL)
	{
		if (aux2->dato == fin)
		{
			break;
		}
		aux2 = aux2->siguiente;
	}
	if (aux2 == NULL)
	{
		printf("Error:Vertice no encontrado\n");
		return;
	}
	while (aux != NULL)
	{
		if (aux->dato == ini)
		{
			agregarArista(aux, aux2, nuevo);
			return;
		}
		aux = aux->siguiente;
	}
	if (aux == NULL)
		printf("Error:Vertice no encontrado\n");
}

void Dijkstra::agregarArista(Nodo *aux, Nodo *aux2, Arista *nuevo)
{
	Arista *a;
	if (aux->adyacencia == NULL)
	{
		aux->adyacencia = nuevo;
		nuevo->vrt = aux2;
	}
	else
	{
		a = aux->adyacencia;
		while (a->siguiente != NULL)
			a = a->siguiente;
		nuevo->vrt = aux2;
		a->siguiente = nuevo;
	}
}

void Dijkstra::visualizarGrafo()
{
	Nodo *aux = inicio;
	Arista *ar;
	printf("Nodos\n");
	while (aux != NULL)
	{
		printf("%c:    ", aux->dato);
		if (aux->adyacencia != NULL)
		{
			ar = aux->adyacencia;
			while (ar != NULL)
			{
				printf(" %c", ar->vrt->dato);
				ar = ar->siguiente;
			}
		}
		printf("\n");
		aux = aux->siguiente;
	}
	printf("\n");
}

void Dijkstra::recorridoAnchura()
{
	Nodo *aux = desencolar();
	if (aux == NULL)
		return;
	printf("%c ", aux->dato);
	if (aux->adyacencia != NULL)
	{
		Arista *a = aux->adyacencia;
		while (a != NULL)
		{
			if (a->vrt->visitado == 0)
			{
				insertarCola(a->vrt);
				a->vrt->visitado = 1;
			}
			a = a->siguiente;
		}
	}
	recorridoAnchura();
}

void Dijkstra::recorridoProfundidad(Nodo *aux)
{
	Arista *a;
	aux->visitado = 1;
	if (aux->adyacencia != NULL)
	{
		a = aux->adyacencia;
		while (a != NULL)
		{
			if (a->vrt->visitado == 0)
			{
				recorridoProfundidad(a->vrt);
			}
			a = a->siguiente;
		}
	}
	aux->terminado = 1;
	insertarPila(aux);
}

void Dijkstra::insertarPila(Nodo *aux)
{
	Lista *nuevo = (Lista *)malloc(sizeof(Lista));
	nuevo->dato = aux;
	nuevo->siguiente = NULL;
	if (ini == NULL)
	{
		ini = nuevo;
		final = nuevo;
	}
	else
	{
		nuevo->siguiente = ini;
		ini = nuevo;
	}
}

void Dijkstra::insertarCola(Nodo *aux)
{
	Lista *nuevo = (Lista *)malloc(sizeof(Lista));
	nuevo->dato = aux;
	nuevo->siguiente = NULL;
	if (ini == NULL)
	{
		ini = nuevo;
		final = nuevo;
	}
	else
	{
		final->siguiente = nuevo;
		final = nuevo;
	}
}

Nodo *Dijkstra::desencolar()
{
	Lista *aux;
	if (ini == NULL)
	{
		return NULL;
	}
	else
	{
		aux = ini;
		ini = ini->siguiente;
		aux->siguiente = NULL;
		if (ini == NULL)
			final = NULL;
	}
	Nodo *resultado = aux->dato;
	free(aux);
	return resultado;
}

void Dijkstra::reiniciar()
{
	if (inicio != NULL)
	{
		Nodo *aux = inicio;
		while (aux != NULL)
		{
			aux->visitado = aux->terminado = 0;
			aux = aux->siguiente;
		}
	}
}

void Dijkstra::dijkstra(char a, char b)
{ // Receive two vertices a initial node and destination node b
	Nodo *aux = inicio;
	fflush(stdin);
	while (aux != NULL)
	{
		if (aux->dato == a)
		{						// helper will be pointing to initial node
			aux->terminado = 1; // it will be equal to 1 since it will be used as the start node
			aux->monto = 0;
			break;
		}
		aux = aux->siguiente; // The while will continue looping
	}
	if (aux == NULL)
	{									   // if auxiliary is equal to null what it means is that the initial node was not found
		printf("Vertice no encontrado\n"); // Send a message to the user that the vertex was not found
		return;
	}
	while (aux != NULL)
	{								 // as long as it is not null
		Arista *a = aux->adyacencia; // an edge is declared to be equal to auxiliary in its adjacency part, that is, at the beginning of the adjacency list of that node
		while (a != NULL)
		{ // As long as this adjacency list is different from null
			if (a->vrt->monto == -1 || (aux->monto + a->peso) < a->vrt->monto)
			{										  // if the vertex has not been visited yet or when a node is visited for the second time its amount is less If it is less it changes yes no no
				a->vrt->monto = aux->monto + a->peso; // add amount of the node that comes plus the weight of the edge
				a->vrt->anterior = aux->dato;		  // here the data that came is saved
			}
			a = a->siguiente; // go to the next edge
		}
		aux = inicio;		// helper will be equal to start
		Nodo *min = inicio; // node min will help find the node that has a smaller amount

		while (min->anterior == 0 || min->terminado == 1) // as long as vertex does not have a null in the previous vertex
			min = min->siguiente;
		while (aux != NULL)
		{																			  // as long as auxiliary is different from null
			if (aux->monto < min->monto && aux->terminado == 0 && aux->anterior != 0) // will identify the minimum vertex that has the smallest amount && the vertex does not have to be terminated && has to have something in the previous node
				min = aux;															  // traverse the list of vertices to find the minimum
			aux = aux->siguiente;													  // keep looping
		}
		aux = min;
		aux->terminado = 1; // the vertex is marked as finished, and its adjacent vertices will be traversed again
		if (aux->dato == b) // found the vertex to reach
			break;
	}
	while (aux->anterior != 0)
	{					   // it will be printed on the screen for this a stack will be used
		insertarPila(aux); // push the aux onto a stack
		char temp = aux->anterior;
		aux = inicio;
		while (aux->dato != temp)
		{						  // here we will look for the node that is before aux in the list
			aux = aux->siguiente; // advance
		}
	}
	insertarPila(aux);
	while (ini != NULL)
	{ // dequeue to print the vertices in order
		string letra = "";
		letra += desencolar()->dato;
		cout << letra << " ";
		datos.push_back(letra);
	}
	printf("\n");
	reiniciar();
}

vector<string> Dijkstra::getDatos()
{
	return datos;
}