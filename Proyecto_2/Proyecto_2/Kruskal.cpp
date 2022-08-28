#include <SFML/Graphics.hpp>
#include <iostream>
#include "Kruskal.h"

using namespace std;

kruskal::kruskal(int V, int E)
{
	this->V = V;
	this->E = E;
}

void kruskal::agregarArista(int u, int v, int w)
{								  // Two ariatas are assigned plus the weight
	edges.push_back({w, {u, v}}); // Here the edges are inserted
}

int kruskal::kruskalAlg()
{
	int mst_wt = 0; // initialize the result

	// Sort the edges in increasing order of cost
	sort(edges.begin(), edges.end());

	// Create disjoint sets
	Conjuntos ds(V);

	// Iterate through all sorted edges//
	vector<pair<int, iPair>>::iterator it;
	for (it = edges.begin(); it != edges.end(); it++)
	{
		int u = it->second.first;
		int v = it->second.second;

		int set_u = ds.encontrar(u);
		int set_v = ds.encontrar(v);

		if (set_u != set_v)
		{
			// The current border will be on the MST
			// so print it

			datos.push_back({u, v});

			// Update MST weight
			mst_wt += it->first;

			// Merge two sets
			ds.unir(set_u, set_v);
		}
	}

	return mst_wt;
}

vector<iPair> kruskal::getDatos()
{
	return datos;
}

Conjuntos::Conjuntos(int n)
{

	// allocate memory
	this->n = n;
	parent = new int[n + 1];
	rnk = new int[n + 1];

	// Initially, all vertices are at
	// different sets and have rank 0.
	for (int i = 0; i <= n; i++)
	{
		rnk[i] = 0;

		// each element is parent of itself
		parent[i] = i;
	}
}

int Conjuntos::encontrar(int u)
{ // Here is the parent vertex

	if (u != parent[u])
	{
		parent[u] = encontrar(parent[u]);
	}
	return parent[u];
}

void Conjuntos::unir(int x, int y)
{
	x = encontrar(x), y = encontrar(y);

	if (rnk[x] > rnk[y])
	{
		parent[y] = x;
	}
	else
	{ // If rnk[x] <= rnk[y]
		parent[x] = y;
	}
	if (rnk[x] == rnk[y])
	{
		rnk[y]++;
	}
}
