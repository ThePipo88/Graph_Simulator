#include <SFML/Graphics.hpp>
#include <iostream>
#include <functional>
#include <algorithm>
#include <queue>
#include <list>
#define INF 0x3f3f3f3f
#include "Prim.h"

// class constructor
Prim::Prim(int V)
{
	this->V = V;
	adj = new list<iPair>[V];
}

void Prim::anadirArista(int u, int v, int w)
{
	adj[u].push_back(make_pair(v, w));
	adj[v].push_back(make_pair(u, w));
}

void Prim::prim()
{
	// Create a priority queue to store the vertices that
	// are being evaluated.//
	priority_queue<iPair, vector<iPair>, greater<iPair>> pq;

	int src = 0; // start from vertex 0

	// create a vector of keys, to store the data data.
	// Initialize as infinite INF
	vector<int> key(V, INF);

	// To store the array which in turn stores the minimum spanning tree
	vector<int> parent(V, -1);

	// To have the order of the vertices included
	vector<bool> inMST(V, false);

	// Insert the initial vertex into the priority queue
	// and initialize it to 0
	pq.push(make_pair(0, src));
	key[src] = 0;

	/* Loop until priority queue is empty */
	while (!pq.empty())
	{
		// The first vertex of the pair is the initial key of the
		// vertex, to extract it from the priority queue.
		// The vertex label is stored in the second of the pair (it is
		// it has to be done like this to keep the vertices
		// of the sorted key (the key must be the first element in par)
		int u = pq.top().second;
		pq.pop();

		// Different key values ​​for the same vertex can exist in the priority queue.
		// The one with the lowest key value is always processed first.
		// So ignore the rest.
		if (inMST[u] == true)
		{
			continue;
		}

		inMST[u] = true; // include the priority vertex in the minimum spanning tree

		// 'i' is used to get all adjacent vertices of a vertex
		list<pair<int, int>>::iterator i;
		for (i = adj[u].begin(); i != adj[u].end(); ++i)
		{
			// Get the vertex label and the weight of the current neighbor from u.
			int v = (*i).first;
			int weight = (*i).second;

			// If v is not in the minimum spanning tree and the weight of (u,v) is less
			// than the current key of v
			if (inMST[v] == false && key[v] > weight)
			{
				// v key update
				key[v] = weight;
				pq.push(make_pair(key[v], v));
				parent[v] = u;
			}
		}
	}

	// Print the borders of the minimum spanning tree using the parent array
	for (int i = 1; i < V; ++i)
	{
		printf("%d - %d\n", parent[i], i);
		datos.push_back({parent[i], i});
	}
}

vector<iPair> Prim::getDatos()
{
	return datos;
}
