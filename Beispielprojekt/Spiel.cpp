#include "stdafx.h"

#include <Gosu/Gosu.hpp>
#include <Gosu/AutoLink.hpp>

#include <vector>
#include <string>
#include <iostream>

#include "Vektor2d.h"

// Simulationsgeschwindigkeit
const double DT = 100.0;

const int x_groesse_rahmen = 600;
const int y_groesse_rahmen = 800;

class Figur {
public:
	int x_pos;
	int y_pos;
	int x_laenge;
	int y_laenge;
	int leben;
	Gosu::Image bild;
	void positioniere(int x, int y) {
		this-> x_laenge = bild.width();
		this-> y_laenge = bild.height();
		if (x > (x_groesse_rahmen - x_laenge)) {
			x = x_groesse_rahmen - x_laenge;
		}
		if (y > (y_groesse_rahmen - y_laenge)) {
			y = y_groesse_rahmen - y_laenge;
		}
		this-> x_pos = x;
		this-> y_pos = y;
	}
	Figur(std::string dateiname) : bild(dateiname)
	{}
};


class GameWindow : public Gosu::Window
{
public:
	GameWindow()
		: Window(x_groesse_rahmen, y_groesse_rahmen), Gegner1("GegnerTyp1.png")
	{
		set_caption("Github Test"); // Name lautet nicht Qwertz
	}
	Figur Gegner1;

	// wird bis zu 60x pro Sekunde aufgerufen.
	// Wenn die Grafikkarte oder der Prozessor nicht mehr hinterherkommen,
	// dann werden `draw` Aufrufe ausgelassen und die Framerate sinkt
	void draw() override{
		Gegner1.bild.draw(Gegner1.x_pos, Gegner1.y_pos, 0.0);
	}

	// Wird 60x pro Sekunde aufgerufen
	void update() override{
		Gegner1.positioniere(100, 100);
	}
};

// C++ Hauptprogramm
int main()
{
	GameWindow window;
	window.show();
}
