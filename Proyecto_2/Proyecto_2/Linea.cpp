#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "Linea.h"

using namespace std;
using namespace sf;


Linea::Linea() {

}

void Linea::setX1(int x1) {
	this->x1 = x1;
}

void Linea::setX2(int x2) {
	this->x2 = x2;
}

void Linea::setY1(int y1) {
	this->y1 = y1;
}

void Linea::setY2(int y2) {
	this->y2 = y2;
}

void Linea::setLetra1(string lt1) {
	this->letra1 = lt1;
}

void Linea::setLetra2(string lt2) {
	this->letra2 = lt2;
}

void Linea::setPeso(int peso) {
	this->pesoA = peso;
}

int Linea::getX1() {
	return x1;
}

int Linea::getX2() {
	return x2;
}

int Linea::getY1() {
	return y1;
}

int Linea::getY2() {
	return y2;
}

int Linea::getPeso() {
	return pesoA;
}

string Linea::getLetra1() {
	return letra1;
}

string Linea::getLetra2() {
	return letra2;
}

Vertex Linea::getLinea() {
	return linea[2];
}

void Linea::dibujarLinea(RenderWindow *window) {

	linea[0].position = sf::Vector2f(x1, y1);
	linea[0].color = sf::Color::Yellow;
	linea[1].position = sf::Vector2f(x2, y2);
	linea[1].color = sf::Color::Yellow;

	circle1.setRadius(5);
	circle2.setRadius(5);

	// change the number of sides (points) to 100
	circle1.setPointCount(100);
	circle2.setPointCount(100);

	circle1.setPosition(x1-6, y1-6);
	circle2.setPosition(x2 - 6, y2 - 6);

	sf::Text text1;
	sf::Text text2;
	sf::Text peso;
	sf::Font font;
	if (!font.loadFromFile("Resources/arial.ttf"))
	{
		// error...
	}

	// select the font
	text1.setFont(font); // font is a sf::Font
	text2.setFont(font);
	peso.setFont(font);

	// set the string to display
	text1.setString(letra1);
	text2.setString(letra2);
	peso.setString(to_string(pesoA));

	// set the character size
	text1.setCharacterSize(24); // in pixels, not points!
	text2.setCharacterSize(24);
	peso.setCharacterSize(24);

	// set the color
	text1.setFillColor(sf::Color::Red);
	text2.setFillColor(sf::Color::Red);
	peso.setFillColor(sf::Color::Red);

	// set the text style
	text1.setStyle(sf::Text::Bold);
	text2.setStyle(sf::Text::Bold);
	peso.setStyle(sf::Text::Bold);

	text1.setPosition(x1-8, y1);
	text2.setPosition(x2-8, y2);
	peso.setPosition(1900-x1, y2-y1);

	
	window->draw(linea,2,sf::Lines);
	window->draw(circle1);
	window->draw(circle2);
	window->draw(text1);
	window->draw(text2);
	window->draw(peso);
}