#include "stdafx.h"

#include <Gosu/Gosu.hpp>
#include <Gosu/AutoLink.hpp>

#include <vector>
#include <string>
#include <iostream>

#include "Vektor2d.h"

// Simulationsgeschwindigkeit
const double DT = 100.0;

class Figur {
public:
	int x_pos;
	int y_pos;
	int leben;
	Gosu::Image bild;
	void positioniere(int x, int y) {
		bild.draw(x, y, 0.0);
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
		: Window(800, 600), Gegner1("GegnerTyp1.png")
	{
		set_caption("Github Test"); // Name lautet nicht Qwertz
	}
	Figur Gegner1;

	// wird bis zu 60x pro Sekunde aufgerufen.
	// Wenn die Grafikkarte oder der Prozessor nicht mehr hinterherkommen,
	// dann werden `draw` Aufrufe ausgelassen und die Framerate sinkt
	void draw() override{
		Gegner1.positioniere(100,100);
	}

	// Wird 60x pro Sekunde aufgerufen
	void update() override
	{
		if (input().down(KB_W)) {
			Gegner1.y_pos++;
		}
	}
};

// C++ Hauptprogramm
int main()
{
	GameWindow window;
	window.show();
}
