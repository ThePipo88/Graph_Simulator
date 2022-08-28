#include <SFML/Graphics.hpp>
#include <iostream>
#include <functional>
#include <algorithm>
#include <queue>
#include <list>

using namespace std;

class Warshall
{

private:
	int vexnum; // Number of vertices of the graph.
	int edge;	// Number of edges of the graph
	int **arc;	// adjacency matrix
	int **dis;	// Record the shortest path information for each vertex
	int **path; // Record the information of each shortest path
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
