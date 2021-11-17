#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "AristaGrafico.h"

using namespace std;
using namespace sf;


AristaGrafico::AristaGrafico() {

}

void AristaGrafico::setX1(int x1) {
	this->x1 = x1;
}

void AristaGrafico::setX2(int x2) {
	this->x2 = x2;
}

void AristaGrafico::setX3(int x3) {
	this->x3 = x3;
}

void AristaGrafico::setY1(int y1) {
	this->y1 = y1;
}

void AristaGrafico::setY2(int y2) {
	this->y2 = y2;
}

void AristaGrafico::setY3(int y3) {
	this->y3 = y3;
}

void AristaGrafico::setPeso(int peso) {
	this->pesoA = peso;
}

void AristaGrafico::setLetra1(string l1) {
	this->letra1 = l1;
}

void AristaGrafico::setLetra2(string l2) {
	this->letra2 = l2;
}

void AristaGrafico::setDirigido(bool dir) {
	this->dirigido = dir;
}

int AristaGrafico::getX1() {
	return x1;
}

int AristaGrafico::getX2() {
	return x2;
}

int AristaGrafico::getX3() {
	return x3;
}

int AristaGrafico::getY1() {
	return y1;
}

int AristaGrafico::getY2() {
	return y2;
}

int AristaGrafico::getY3() {
	return y3;
}

int AristaGrafico::getPeso() {
	return pesoA;
}

string AristaGrafico::getLetra1() {
	return letra1;
}

string AristaGrafico::getLetra2() {
	return letra2;
}

Vertex AristaGrafico::getLinea() {
	return linea[2];
}

bool AristaGrafico::getDirigido() {
	return dirigido;
}

void AristaGrafico::dibujarLinea(RenderWindow* window) {

	linea[0].position = sf::Vector2f(x1, y1);
	linea[0].color = sf::Color::Yellow;
	linea[1].position = sf::Vector2f(x2, y2);
	linea[1].color = sf::Color::Yellow;

	linea->texCoords;

	sf::Text peso;
	sf::Font font;
	if (!font.loadFromFile("Resources/arial.ttf"))
	{
		// error...
	}

	// select the font
	peso.setFont(font);

	// set the string to display
	peso.setString(to_string(pesoA));

	// set the character size
	peso.setCharacterSize(24);

	// set the color
	peso.setFillColor(sf::Color::Green);

	// set the text style
	peso.setStyle(sf::Text::Bold);

	peso.setPosition(calcularTamanio(x1,x2), calcularTamanio(y1, y2));

	window->draw(linea, 2, sf::Lines);
	if (dirigido) {
		Texture texture;
		//tab = new Tablero();
		if (!texture.loadFromFile("Resources/estrella.PNG"))
		{
			cout << "Error al cargar imagen" << endl;
		}
		Sprite sprite(texture);
		sprite.setPosition(calcularFlecha(x1,x2), calcularFlecha(y1, y2));
		window->draw(sprite);
	}
	window->draw(peso);
}

void AristaGrafico::dibujarLineaDijkstra(RenderWindow* window) {

	linea[0].position = sf::Vector2f(x1, y1);
	linea[0].color = sf::Color::Green;
	linea[1].position = sf::Vector2f(x2, y2);
	linea[1].color = sf::Color::Green;

	linea->texCoords;

	sf::Text peso;
	sf::Font font;
	if (!font.loadFromFile("Resources/arial.ttf"))
	{
		// error...
	}

	// select the font
	peso.setFont(font);

	// set the string to display
	peso.setString(to_string(pesoA));

	// set the character size
	peso.setCharacterSize(24);

	// set the color
	peso.setFillColor(sf::Color::Green);

	// set the text style
	peso.setStyle(sf::Text::Bold);

	peso.setPosition(calcularTamanio(x1, x2), calcularTamanio(y1, y2));

	window->draw(linea, 2, sf::Lines);
	if (dirigido) {
		Texture texture;
		//tab = new Tablero();
		if (!texture.loadFromFile("Resources/estrella.PNG"))
		{
			cout << "Error al cargar imagen" << endl;
		}
		Sprite sprite(texture);
		sprite.setPosition(calcularFlecha(x1, x2), calcularFlecha(y1, y2));
		window->draw(sprite);
	}
	window->draw(peso);
}

int AristaGrafico::calcularTamanio(int x, int y) {

	int resultado = 0;

	if (x < y) {
		int datos = (y - x) / 2;
		resultado = x + datos;
	}
	else {
		int datos = (x - y) / 2;
		resultado = y + datos;
	}
	
	return resultado;
}

int AristaGrafico::calcularFlecha(int x, int y) {

	int resultado = 0;

	if (x < y) {
		int datos = (y - x) / 2;
		int aux = datos;
		resultado = (x + datos) + ((aux)-aux / 2);
	}
	else {
		int datos = (x - y) / 2;
		int aux = datos;
		resultado = (y + datos) - ((aux)-aux/2);
	}

	return resultado;
}