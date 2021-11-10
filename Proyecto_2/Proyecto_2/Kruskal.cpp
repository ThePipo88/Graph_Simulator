#include <SFML/Graphics.hpp>
#include <iostream>
#include "Kruskal.h"

using namespace std;

kruskal::kruskal(int V, int E) {
	this->V = V;
	this->E = E;
}

void kruskal::agregarArista(int u, int v, int w) {
	edges.push_back({ w, {u, v} });
}

int kruskal::kruskalAlg() {
	int mst_wt = 0; // Initialize result

	// Sort edges in increasing order on basis of cost
	sort(edges.begin(), edges.end());

	// Create disjoint sets
	Conjuntos ds(V);

	// Iterate through all sorted edges
	vector< pair<int, iPair> >::iterator it;
	for (it = edges.begin(); it != edges.end(); it++)
	{
		int u = it->second.first;
		int v = it->second.second;

		int set_u = ds.encontrar(u);
		int set_v = ds.encontrar(v);


		if (set_u != set_v)
		{
			// Current edge will be in the MST
			// so print it
		    //cout << u << " - " << v << endl;

			datos.push_back({u,v});

			// Update MST weight
			mst_wt += it->first;

			// Merge two sets
			ds.unir(set_u, set_v);
		}
	}

	return mst_wt;
}

vector<iPair> kruskal::getDatos() {
	return datos;
}

Conjuntos::Conjuntos(int n) {

	// Allocate memory
	this->n = n;
	parent = new int[n + 1];
	rnk = new int[n + 1];

	// Initially, all vertices are in
	// different sets and have rank 0.
	for (int i = 0; i <= n; i++)
	{
		rnk[i] = 0;

		//every element is parent of itself
		parent[i] = i;
	}
}

int Conjuntos::encontrar(int u) {

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
