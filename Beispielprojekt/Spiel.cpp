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
	void positioniere(int x = 100, int y = 100) {
		this-> x_laenge = bild.width();
		this-> y_laenge = bild.height();
		if (x >= (x_groesse_rahmen - x_laenge)) {
			x = x_groesse_rahmen - x_laenge;
		}
		if (x <= 0) {
			x = 0;
		}
		if (y >= (y_groesse_rahmen - y_laenge)) {
			y = y_groesse_rahmen - y_laenge;
		}
		if (y <= 0) {
			y = 0;
		}
		this-> x_pos = x;
		this-> y_pos = y;
	}

	Figur(std::string dateiname) : bild(dateiname)
	{}
};

class Schuss {
public:
	int x_pos;
	int y_pos;
	
	Schuss(int x_pos, int y_pos) {
		this->x_pos = x_pos;
		this->y_pos = y_pos;
	}
	Schuss() 
	{};

	void draw() {
		Gosu::Graphics::draw_rect(x_pos, y_pos, 2, 10, Gosu::Color::RED, 0.0);
	}

	void update() {
		y_pos -= 2;
	}
};

class GameWindow : public Gosu::Window
{
public:
	GameWindow()
		: Window(x_groesse_rahmen, y_groesse_rahmen)
		,Gegner1("GegnerTyp1.png")
		,Spieler("SpielerTyp1.png")
	{
		set_caption("Github Test"); // Name lautet nicht Qwertz
		Spieler.positioniere(275, 800); // Spieler Spawnen
	}
	Figur Spieler, Gegner1;
	Schuss schuss1;

	// wird bis zu 60x pro Sekunde aufgerufen.
	// Wenn die Grafikkarte oder der Prozessor nicht mehr hinterherkommen,
	// dann werden `draw` Aufrufe ausgelassen und die Framerate sinkt
	void draw() override {
		Gegner1.bild.draw(Gegner1.x_pos, Gegner1.y_pos, 0.0);
		Spieler.bild.draw(Spieler.x_pos, Spieler.y_pos, 0.0);
		schuss1.draw();
	}
	
	// Wird 60x pro Sekunde aufgerufen
	void update() override
	{
		Gegner1.positioniere(Gegner1.x_pos, Gegner1.y_pos);
		Spieler.positioniere(Spieler.x_pos, Spieler.y_pos);
		if (input().down(Gosu::Button::Button(26))) {
			Spieler.y_pos -= 2;
		}
		if (input().down(Gosu::Button::Button(22))) {
			Spieler.y_pos += 2;
		}
		if (input().down(Gosu::Button::Button(4))) {
			Spieler.x_pos -= 2;
		}
		if (input().down(Gosu::Button::Button(7))) {
			Spieler.x_pos += 2;
		}
		if (input().down(Gosu::MS_LEFT)) {
			schuss1.x_pos = Spieler.x_pos + 24;
			schuss1.y_pos = Spieler.y_pos;
		}
		schuss1.update();
	};
};
	// C++ Hauptprogramm
	int main()
	{
		GameWindow window;
		window.show();
	}