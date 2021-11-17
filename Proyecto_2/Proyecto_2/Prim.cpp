#include <SFML/Graphics.hpp>
#include <iostream>
#include <functional>  
#include <algorithm>  
#include <queue>
#include <list>
# define INF 0x3f3f3f3f
#include "Prim.h"

//Constructor de la clase
Prim::Prim(int V) {
	this->V = V;
	adj = new list<iPair>[V];
}

void Prim::anadirArista(int u, int v, int w) {
	adj[u].push_back(make_pair(v, w));
	adj[v].push_back(make_pair(u, w));
}

void Prim::prim() {
	//	Crear una cola de prioridad para almacenar los vértices que
	// están siendo evaluados.
	priority_queue< iPair, vector <iPair>, greater<iPair> > pq;

	int src = 0; // inicia desde el vertice 0

//	crea un vector de claves, para almacenar los datos datos.
//	Se inicializan como infinitas INF
	vector<int> key(V, INF);

	//	Para almacenar la matriz que a su vez almacena el el arbol de expansión minima
	vector<int> parent(V, -1);

	//	Para tener el orden de los vertices incluidos
	vector<bool> inMST(V, false);

	//	Inserta el vertice inicial en la cola de prioridad 
	//	y la inicializa como 0 
	pq.push(make_pair(0, src));
	key[src] = 0;

	/* Bucle hasta que la cola de prioridad esté vacía */
	while (!pq.empty())
	{
		// El primer vértice del par es la clave inical del 
		// vértice, para extraerlo de la cola de prioridad.
		// La etiqueta del vértice se almacena en el segundo del par (se
		// tiene que hacerse así para mantener los vértices
		// de la clave ordenados (la clave debe ser el primer elemento
		// en el par)
		int u = pq.top().second;
		pq.pop();

		//Diferentes valores de clave para un mismo vértice pueden existir en la cola de prioridad.
		//El que tiene el menor valor de clave siempre se procesa primero.
		//Por lo tanto, ignora el resto.
		if (inMST[u] == true) {
			continue;
		}

		inMST[u] = true; //incluye el vertice de prioridad en el arbol abarcador minimo

		// 'i' se utiliza para obtener todos los vértices adyacentes de un vértice
		list< pair<int, int> >::iterator i;
		for (i = adj[u].begin(); i != adj[u].end(); ++i)
		{
			// Obtiene la etiqueta del vértice y el peso del adyacente actual
			// de u.
			int v = (*i).first;
			int weight = (*i).second;

			// Si v no está en el arbol abarcador minimo y el peso de (u,v) es menor
			// que la clave actual de v
			if (inMST[v] == false && key[v] > weight)
			{
				//  Actualización de la clave de v
				key[v] = weight;
				pq.push(make_pair(key[v], v));
				parent[v] = u;
			}
		}
	}

	// Imprime los bordes del arbol abarcador minimo utilizando la matriz de los padres
	for (int i = 1; i < V; ++i) {
		printf("%d - %d\n", parent[i], i);
		datos.push_back({ parent[i], i });
	}
}

vector<iPair> Prim::getDatos() {
	return datos;
}
