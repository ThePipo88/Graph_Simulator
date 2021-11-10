#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "VerticeGrafico.h"

using namespace std;
using namespace sf;


VerticeGrafico::VerticeGrafico() {

}

void VerticeGrafico::setX1(int x1) {
	this->x1 = x1;
}


void VerticeGrafico::setY1(int y1) {
	this->y1 = y1;
}

void VerticeGrafico::setLetra1(string lt1) {
	this->letra1 = lt1;
}

void VerticeGrafico::setNumero(int n) {
	numero = n;
}

int VerticeGrafico::getX1() {
	return x1;
}

int VerticeGrafico::getY1() {
	return y1;
}

string VerticeGrafico::getLetra1() {
	return letra1;
}

int VerticeGrafico::getNumero() {
	return numero;
}

void VerticeGrafico::dibujarVertice(RenderWindow* window) {

	circle1.setRadius(5);

	// change the number of sides (points) to 100
	circle1.setPointCount(100);

	circle1.setPosition(x1 - 6, y1 - 6);

	sf::Text text1;
	sf::Font font;
	if (!font.loadFromFile("Resources/arial.ttf"))
	{
		// error...
	}

	// select the font
	text1.setFont(font); // font is a sf::Font

	// set the string to display
	text1.setString(letra1);

	// set the character size
	text1.setCharacterSize(24); // in pixels, not points!

	// set the color
	text1.setFillColor(sf::Color::Red);

	// set the text style
	text1.setStyle(sf::Text::Bold);

	text1.setPosition(x1 - 8, y1);

	window->draw(circle1);
	window->draw(text1);
}