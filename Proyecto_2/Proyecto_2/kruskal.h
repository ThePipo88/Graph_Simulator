#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

typedef pair<int, int> iPair;

class kruskal{

private:
	int V, E;
	vector< pair<int, iPair> > edges;
	vector<iPair> datos;
public:

	kruskal(int V, int E);
	void agregarArista(int u, int v, int w);
	int kruskalAlg();
	vector<iPair> getDatos();
};


class Conjuntos {
private:
	int* parent, * rnk;
	int n;
public:
	Conjuntos(int n);
	int encontrar(int u);
	void unir(int x, int y);
};

struct DKrustal {
	int ini;
	int fin;
};