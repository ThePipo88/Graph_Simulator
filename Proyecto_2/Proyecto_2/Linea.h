#include <SFML/Graphics.hpp>
#include <iostream>
#include <stack>

using namespace std;
using namespace sf;

class Linea {

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

	Linea();

	void setX1(int x1);

	void setX2(int x2);

	void setY1(int x1);

	void setY2(int x2);

	void setLetra1(string lt1);

	void setLetra2(string lt2);

	void setPeso(int ps);

	int getX1();

	int getX2();

	int getY1();

	int getY2();

    string getLetra1();

	string getLetra2();

	Vertex getLinea();

	int getPeso();

	void dibujarLinea(RenderWindow *window);
};
