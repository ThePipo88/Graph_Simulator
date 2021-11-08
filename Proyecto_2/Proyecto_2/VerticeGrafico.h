#include <SFML/Graphics.hpp>
#include <iostream>
#include <stack>

using namespace std;
using namespace sf;

class VerticeGrafico {

private:

	Vertex linea[2];
	CircleShape circle1;
	CircleShape circle2;

	string letra1 = "";
	string letra2 = "";
	int pesoA = 0;
	int x1 = 0;
	int y1 = 0;
	int x2 = 0;
	int y2 = 0;

public:

	VerticeGrafico();

	void setX1(int x1);

	void setY1(int x1);

	void setLetra1(string lt1);

	int getX1();

	int getY1();

	string getLetra1();

	void dibujarVertice(RenderWindow* window);
};