#include <SFML/Graphics.hpp>
#include <iostream>
#include <functional>  
#include <algorithm>  
#include <queue>
#include <list>

using namespace std;

class Warshall{

private:
	int vexnum;   // N�mero de v�rtices del gr�fico.
	int edge;     // N�mero de aristas del gr�fico
	int** arc;   // matriz de adyacencia
	int** dis;   // Registre la informaci�n de la ruta m�s corta de cada v�rtice
	int** path;  // Registra la informaci�n de cada ruta m�s corta
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
