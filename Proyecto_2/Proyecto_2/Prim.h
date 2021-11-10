#include <SFML/Graphics.hpp>
#include <iostream>
#include <functional>  
#include <algorithm>  
#include <queue>
#include <list>

using namespace std;

typedef pair<int, int> iPair;

class Prim {

private:
	int V;
	list< pair<int, int> >* adj;
	vector<iPair> datos;
public:
	Prim(int V);
	void anadirArista(int u, int v, int w);
	void prim();
	vector<iPair> getDatos();
};
