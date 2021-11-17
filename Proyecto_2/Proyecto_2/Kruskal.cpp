#include <SFML/Graphics.hpp>
#include <iostream>
#include "Kruskal.h"

using namespace std;

kruskal::kruskal(int V, int E) {
	this->V = V;
	this->E = E;
}

void kruskal::agregarArista(int u, int v, int w) { //Se asignan dos ariatas mas el peso
	edges.push_back({ w, {u, v} }); //Aqui se insertan a las aristas
}

int kruskal::kruskalAlg() {
	int mst_wt = 0; // inicializa el resultado

	// Clasifica los bordes en orden creciente según el costo
	sort(edges.begin(), edges.end());

	// Crear conjuntos disjuntos
	Conjuntos ds(V);

	// Iterar a través de todos los bordes ordenados
	vector< pair<int, iPair> >::iterator it;
	for (it = edges.begin(); it != edges.end(); it++)
	{
		int u = it->second.first;
		int v = it->second.second;

		int set_u = ds.encontrar(u);
		int set_v = ds.encontrar(v);


		if (set_u != set_v)
		{
			// El borde actual estará en el MST
			// así que imprímelo
			// cout << u << "-" << v << endl;

			datos.push_back({ u,v });

			// Actualizar el peso de MST
			mst_wt += it->first;

			// Fusionar dos conjuntos
			ds.unir(set_u, set_v);
		}
	}

	return mst_wt;
}

vector<iPair> kruskal::getDatos() {
	return datos;
}

Conjuntos::Conjuntos(int n) {

	// Asignar memoria
	this->n = n;
	parent = new int[n + 1];
	rnk = new int[n + 1];

	// Inicialmente, todos los vértices están en
	// conjuntos diferentes y tienen rango 0.
	for (int i = 0; i <= n; i++)
	{
		rnk[i] = 0;

		// cada elemento es padre de sí mismo
		parent[i] = i;
	}
}

int Conjuntos::encontrar(int u) { // Aqui se encutra el vertice padre

	if (u != parent[u]) {
		parent[u] = encontrar(parent[u]);
	}
	return parent[u];
}


void Conjuntos::unir(int x, int y) {
	x = encontrar(x), y = encontrar(y);


	if (rnk[x] > rnk[y]) {
		parent[y] = x;
	}
	else { // If rnk[x] <= rnk[y]
		parent[x] = y;
	}
	if (rnk[x] == rnk[y]) {
		rnk[y]++;
	}
}
