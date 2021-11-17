#include <SFML/Graphics.hpp>
#include <iostream>
#include <functional>  
#include <algorithm>  
#include <queue>
#include <list>

using namespace std;

class Warshall{

private:
	int vexnum;   // Número de vértices del gráfico.
	int edge;     // Número de aristas del gráfico
	int** arc;   // matriz de adyacencia
	int** dis;   // Registre la información de la ruta más corta de cada vértice
	int** path;  // Registra la información de cada ruta más corta
	int kind = 1;
	vector<string> datos;
public:
	Warshall(int vexnum, int edge);
	~Warshall();
	void createGraph(int a, int b, int p);
	void print();
	void Floyd();
	void print_path(char l1, char l2);
	bool check(int Vexnum, int edge);
	bool check_edge_value(int start, int end, int weight);
	vector<string> getDatos();
};
