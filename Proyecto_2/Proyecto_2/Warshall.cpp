#include "Warshall.h";

// constructor
Warshall::Warshall(int vexnum, int edge) {
	// Inicializa el número de vértices y aristas
	this->vexnum = vexnum;
	this->edge = edge;
	// Abrir el espacio y asignar valores iniciales para la matriz de adyacencia
	arc = new int* [this->vexnum];
	dis = new int* [this->vexnum];
	path = new int* [this->vexnum];
	for (int i = 0; i < this->vexnum; i++) {
		arc[i] = new int[this->vexnum];
		dis[i] = new int[this->vexnum];
		path[i] = new int[this->vexnum];
		for (int k = 0; k < this->vexnum; k++) {
			// La matriz de adyacencia se inicializa al infinito
			arc[i][k] = INT_MAX;
		}
	}
}
// Destructor
Warshall::~Warshall() {

	for (int i = 0; i < this->vexnum; i++) {
		delete this->arc[i];
		delete this->dis[i];
		delete this->path[i];

	}
	delete dis;
	delete arc;
	delete path;
}

// Comprueba si los valores de borde de entrada y vértice son válidos, y puedes calcularlo tú mismo:
// La relación entre el número de vértices y el número de aristas es: ((Vexnum * (Vexnum-1)) / 2) <edge
bool Warshall::check(int Vexnum, int edge) {
	if (Vexnum <= 0 || edge <= 0 || ((Vexnum * (Vexnum - 1)) / 2) < edge)
		return false;
	return true;
}

// juzga si la información del borde que ingresamos es legal cada vez
// Los vértices están numerados de 1
bool Warshall::check_edge_value(int start, int end, int weight) {
	if (start<1 || end<1 || start>vexnum || end>vexnum || weight < 0) {
		return false;
	}
	return true;
}


// Este metodo logra agregar el inicio, fin y el peso del grafo a la matriz dinamica
// donde se almacenará lo necesario.
void Warshall::createGraph(int a, int b, int p) {
	int count = 0;
	// Primero determine si la información de borde es legal
	while (!this->check_edge_value(a, b, p)) {
		cout << "La información ingresada es ilegal, vuelva a ingresar" << endl;
	}
	// Asigna los puntos correspondientes en la matriz de adyacencia
	arc[a - 1][b - 1] = p;
	// Agregue esta línea de código al gráfico no dirigido
	if (kind == 2)
		arc[b - 1][a - 1] = p;
	++count;
}
//Este metodo imprime la matriz de adyacencia, creada según los datos ingresados por el usuario.
void Warshall::print() {
	cout << "La matriz de adyacencia del gráfico es:" << endl;
	int count_row = 0; // Imprime la etiqueta de la línea
	int count_col = 0; // Imprime la etiqueta de la columna
	// Comienza a imprimir
	while (count_row != this->vexnum) {
		count_col = 0;
		while (count_col != this->vexnum) {
			if (arc[count_row][count_col] == INT_MAX)
				cout << "#" << " ";
			else
				cout << arc[count_row][count_col] << " ";
			++count_col;
		}
		cout << endl;
		++count_row;
	}
}


//Este metodo es capaz de ejecutar el algoritmo de floyd e ir
//añadiendo los caminos a la matriz de direcciones llamada path.
void Warshall::Floyd() {
	int row = 0;
	int col = 0;
	for (row = 0; row < this->vexnum; row++) {
		for (col = 0; col < this->vexnum; col++) {
			// Inicializa la matriz D al valor de la matriz de adyacencia
			this->dis[row][col] = this->arc[row][col];
			// El valor inicial de la matriz P es el índice del vértice final de cada borde
			this->path[row][col] = col;
		}
	}

	// Triple loop, usado para calcular la ruta más corta de cada par de puntos
	int temp = 0;
	int select = 0;
	for (temp = 0; temp < this->vexnum; temp++) {
		for (row = 0; row < this->vexnum; row++) {
			for (col = 0; col < this->vexnum; col++) {
				// Para evitar el desbordamiento, es necesario introducir un valor de selección
				select = (dis[row][temp] == INT_MAX || dis[temp][col] == INT_MAX) ? INT_MAX : (dis[row][temp] + dis[temp][col]);
				if (this->dis[row][col] > select) {
					// Actualiza nuestra matriz D
					this->dis[row][col] = select;
					// Actualiza nuestra matriz P
					this->path[row][col] = this->path[row][temp];
				}
			}
		}
	}
}


//Una vez ejecutado el metodo floyd, la matriz de recorridos estará lista para ser impresa con los
// valores necesarios. Solamente imprime la ruta de un camino entre un nodo de inicio y otro nodo final.
void Warshall::print_path(char l1, char l2) {
	cout << "La ruta más corta de cada par de vértices:" << endl;
	int row = 0;
	int col = 0;
	int temp = 0;
	for (row = 0; row < this->vexnum; row++) {
		for (col = row + 1; col < this->vexnum; col++) {


			//el if, valida que el camino a ingresar en los datos sean los solicitados por el usuario.
			if (char('A' - 1 + row + 1) == l1 && char('A' - 1 + col + 1) == l2) {
				string txt1 = "";
				cout << char('A' - 1 + row + 1) << "---" << char('A' - 1 + col + 1) << " weight: "
					<< this->dis[row][col] << " path: " << char('A' - 1 + row + 1);
				txt1 += char('A' - 1 + row + 1);
				datos.push_back(txt1);
				txt1 = "";
				temp = path[row][col];
				// Cada ruta de la ruta de salida del bucle.
				while (temp != col) {
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

//Devuelve los datos necesarios para realizar las acciones graficas en la vista.
vector<string> Warshall::getDatos() {
	return datos;
}