#include "Warshall.h";

// constructor
Warshall::Warshall(int vexnum, int edge)
{
	// Inicializa el n mero de v rtices y aristas
	this->vexnum = vexnum;
	this->edge = edge;
	// Open the space and assign initial values ​​for the adjacency matrix
	arc = new int *[this->vexnum];
	dis = new int *[this->vexnum];
	path = new int *[this->vexnum];
	for (int i = 0; i < this->vexnum; i++)
	{
		arc[i] = new int[this->vexnum];
		dis[i] = new int[this->vexnum];
		path[i] = new int[this->vexnum];
		for (int k = 0; k < this->vexnum; k++)
		{
			// The adjacency matrix is ​​initialized to infinity
			arc[i][k] = INT_MAX;
		}
	}
}
// destructor
Warshall::~Warshall()
{

	for (int i = 0; i < this->vexnum; i++)
	{
		delete this->arc[i];
		delete this->dis[i];
		delete this->path[i];
	}
	delete dis;
	delete arc;
	delete path;
}

// Check if the input edge and vertex values ​​are valid, and you can calculate it yourself:
// The relationship between the number of vertices and the number of edges is: ((Vexnum * (Vexnum-1)) / 2) <edge
bool Warshall::check(int Vexnum, int edge)
{
	if (Vexnum <= 0 || edge <= 0 || ((Vexnum * (Vexnum - 1)) / 2) < edge)
		return false;
	return true;
}

// judge if the border information we entered is legal each time
// Vertices are numbered 1
bool Warshall::check_edge_value(int start, int end, int weight)
{
	if (start < 1 || end < 1 || start > vexnum || end > vexnum || weight < 0)
	{
		return false;
	}
	return true;
}

// This method manages to add the start, end and weight of the graph to the dynamic array
// where the necessary will be stored.
void Warshall::createGraph(int a, int b, int p)
{
	int count = 0;
	// First determine if the border information is legal
	while (!this->check_edge_value(a, b, p))
	{
		cout << "La informaci�n ingresada es ilegal, vuelva a ingresar" << endl;
	}
	// Assign the corresponding points in the adjacency matrix
	arc[a - 1][b - 1] = p;
	// Add this line of code to the undirected graph
	if (kind == 2)
		arc[b - 1][a - 1] = p;
	++count;
}
// This method prints the adjacency matrix, created according to the data entered by the user.
void Warshall::print()
{
	cout << "La matriz de adyacencia del gr�fico es:" << endl;
	int count_row = 0; // Print the label of the line
	int count_col = 0; // print the column label
	// Start printing
	while (count_row != this->vexnum)
	{
		count_col = 0;
		while (count_col != this->vexnum)
		{
			if (arc[count_row][count_col] == INT_MAX)
				cout << "#"
					 << " ";
			else
				cout << arc[count_row][count_col] << " ";
			++count_col;
		}
		cout << endl;
		++count_row;
	}
}

// This method is able to execute floyd's algorithm and go
// adding the paths to the address array named path.
void Warshall::Floyd()
{
	int row = 0;
	int col = 0;
	for (row = 0; row < this->vexnum; row++)
	{
		for (col = 0; col < this->vexnum; col++)
		{
			// Initialize matrix D to the value of the adjacency matrix
			this->dis[row][col] = this->arc[row][col];
			// The initial value of the matrix P is the index of the final vertex of each edge
			this->path[row][col] = col;
		}
	}

	// Triple loop, used to compute the shortest path to each pair of points
	int temp = 0;
	int select = 0;
	for (temp = 0; temp < this->vexnum; temp++)
	{
		for (row = 0; row < this->vexnum; row++)
		{
			for (col = 0; col < this->vexnum; col++)
			{
				// To avoid overflow, it is necessary to enter a selection value
				select = (dis[row][temp] == INT_MAX || dis[temp][col] == INT_MAX) ? INT_MAX : (dis[row][temp] + dis[temp][col]);
				if (this->dis[row][col] > select)
				{
					// Update our array D
					this->dis[row][col] = select;
					// Update our array P
					this->path[row][col] = this->path[row][temp];
				}
			}
		}
	}
}

// Once the floyd method is executed, the tour matrix will be ready to be printed with the
//  required values. It only prints the route of a path between a start node and an end node.
void Warshall::print_path(char l1, char l2)
{
	cout << "La ruta m�s corta de cada par de v�rtices:" << endl;
	int row = 0;
	int col = 0;
	int temp = 0;
	for (row = 0; row < this->vexnum; row++)
	{
		for (col = row + 1; col < this->vexnum; col++)
		{

			// the if, validates that the path to enter the data is the one requested by the user.
			if (char('A' - 1 + row + 1) == l1 && char('A' - 1 + col + 1) == l2)
			{
				string txt1 = "";
				cout << char('A' - 1 + row + 1) << "---" << char('A' - 1 + col + 1) << " weight: "
					 << this->dis[row][col] << " path: " << char('A' - 1 + row + 1);
				txt1 += char('A' - 1 + row + 1);
				datos.push_back(txt1);
				txt1 = "";
				temp = path[row][col];
				// Each route of the exit route of the loop.
				while (temp != col)
				{
					cout << "-->" << char('A' - 1 + temp + 1);
					txt1 += char('A' - 1 + temp + 1);
					datos.push_back(txt1);
					txt1 = "";
					temp = path[temp][col];
				}
				cout << "-->" << char('A' - 1 + col + 1) << endl;
				txt1 += char('A' - 1 + col + 1);
				datos.push_back(txt1);
				txt1 = "";
			}
		}

		cout << endl;
	}
}

// Returns the necessary data to perform the graphic actions in the view.
vector<string> Warshall::getDatos()
{
	return datos;
}