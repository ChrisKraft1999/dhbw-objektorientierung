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
		this-> x_laenge = bild.width(); // holt Figurbreite
		this-> y_laenge = bild.height(); // holt Figurhoehe
		if (x >= (x_groesse_rahmen - x_laenge)) {
			x = x_groesse_rahmen - x_laenge;
		} // Block rechten Rand
		if (x <= 0) {
			x = 0;
		} // Block linken Rand
		if (y >= (y_groesse_rahmen - y_laenge)) {
			y = y_groesse_rahmen - y_laenge;
		} // Blockt unteren Rand
		if (y <= 0) {
			y = 0;
		} // Blockt oberen Rand
		this-> x_pos = x;
		this-> y_pos = y;
	}
	void leben_geben(int l = 2) {
		this->leben = l;
	} // Legt Leben der Figur fest
	void treffer() {
		this-> leben = leben - 1;
	} // reduziert das Leben einer Figur um 1

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
		y_pos -= 5;
	}
};

class GameWindow : public Gosu::Window
{
public:
	GameWindow()
		: Window(x_groesse_rahmen, y_groesse_rahmen)
		,Gegner1("GegnerTyp1.png")
		,Gegner2("GegnerTyp1.png")
		,Gegner3("GegnerTyp1.png")
		,Gegner4("GegnerTyp1.png")
		,Gegner5("GegnerTyp1.png")
		,Gegner6("GegnerTyp1.png")
		,Gegner7("GegnerTyp1.png")
		,Gegner8("GegnerTyp1.png")
		,Gegner9("GegnerTyp1.png")
		,Gegner10("GegnerTyp1.png")
		,Gegner11("GegnerTyp1.png")
		,Gegner12("GegnerTyp1.png")
		,Spieler("SpielerTyp1.png")
	{
		set_caption("Github Test"); // Name lautet nicht Qwertz
		Spieler.positioniere(275, 725); // Spieler spawnen
		
		// Figuren existent machen
		Spieler.leben_geben(10);
		Gegner1.leben_geben();
		Gegner2.leben_geben();
		Gegner3.leben_geben();
		Gegner4.leben_geben();
		Gegner5.leben_geben();
		Gegner6.leben_geben();
		Gegner7.leben_geben();
		Gegner8.leben_geben();
		Gegner9.leben_geben();
		Gegner10.leben_geben();
		Gegner11.leben_geben();
		Gegner12.leben_geben();	
	}
	Schuss schuss1;
	Figur Spieler, Gegner1, Gegner2, Gegner3, Gegner4, Gegner5, Gegner6, Gegner7, Gegner8, Gegner9, Gegner10, Gegner11, Gegner12;
	std::vector<Schuss> s;
	int i = 0;
	

	// wird bis zu 60x pro Sekunde aufgerufen.
	// Wenn die Grafikkarte oder der Prozessor nicht mehr hinterherkommen,
	// dann werden `draw` Aufrufe ausgelassen und die Framerate sinkt
	void draw() override {
		if (Gegner1.leben != 0) {
			Gegner1.bild.draw(Gegner1.x_pos, Gegner1.y_pos, 0.0);
		} // Zeichenen wenn Leben vorhanden
		if (Gegner2.leben != 0) {
			Gegner2.bild.draw(Gegner2.x_pos, Gegner2.y_pos, 0.0);
		} // Zeichenen wenn Leben vorhanden
		if (Gegner3.leben != 0) {
			Gegner3.bild.draw(Gegner3.x_pos, Gegner3.y_pos, 0.0);
		} // Zeichenen wenn Leben vorhanden
		if (Gegner4.leben != 0) {
			Gegner4.bild.draw(Gegner4.x_pos, Gegner4.y_pos, 0.0);
		} // Zeichenen wenn Leben vorhanden
		if (Gegner5.leben != 0) {
			Gegner5.bild.draw(Gegner5.x_pos, Gegner5.y_pos, 0.0);
		} // Zeichenen wenn Leben vorhanden
		if (Gegner6.leben != 0) {
			Gegner6.bild.draw(Gegner6.x_pos, Gegner6.y_pos, 0.0);
		} // Zeichenen wenn Leben vorhanden
		if (Gegner7.leben != 0) {
			Gegner7.bild.draw(Gegner7.x_pos, Gegner7.y_pos, 0.0);
		} // Zeichenen wenn Leben vorhanden
		if (Gegner8.leben != 0) {
			Gegner8.bild.draw(Gegner8.x_pos, Gegner8.y_pos, 0.0);
		} // Zeichenen wenn Leben vorhanden
		if (Gegner9.leben != 0) {
			Gegner9.bild.draw(Gegner9.x_pos, Gegner9.y_pos, 0.0);
		} // Zeichenen wenn Leben vorhanden
		if (Gegner10.leben != 0) {
			Gegner10.bild.draw(Gegner10.x_pos, Gegner10.y_pos, 0.0);
		} // Zeichenen wenn Leben vorhanden
		if (Gegner11.leben != 0) {
			Gegner11.bild.draw(Gegner11.x_pos, Gegner11.y_pos, 0.0);
		} // Zeichenen wenn Leben vorhanden
		if (Gegner12.leben != 0) {
			Gegner12.bild.draw(Gegner12.x_pos, Gegner12.y_pos, 0.0);
		} // Zeichenen wenn Leben vorhanden
		if (Spieler.leben != 0) {
			Spieler.bild.draw(Spieler.x_pos, Spieler.y_pos, 0.0);
		} // Zeichenen wenn Leben vorhanden
		Gegner1.bild.draw(Gegner1.x_pos, Gegner1.y_pos, 0.0);
		Spieler.bild.draw(Spieler.x_pos, Spieler.y_pos, 0.0);
		schuss1.draw();
	}
	
	// Wird 60x pro Sekunde aufgerufen
	void update() override
	{
		Gegner1.positioniere(0, 0);
		Gegner2.positioniere(50, 0);
		Gegner3.positioniere(100, 0);
		Gegner4.positioniere(150, 0);
		Gegner5.positioniere(200, 0);
		Gegner6.positioniere(250, 0);
		Gegner7.positioniere(300, 0);
		Gegner8.positioniere(350, 0);
		Gegner9.positioniere(400, 0);
		Gegner10.positioniere(450, 0);
		Gegner11.positioniere(500, 0);
		Gegner12.positioniere(550, 0);
		Spieler.positioniere(Spieler.x_pos, Spieler.y_pos);
		
		// Postion von Spieler mit w,a,s,d anpassen
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


	/*Links:
	https://github.com/ChrisKraft1999/dhbw-objektorientierung
	https://www.libgosu.org/cpp/struct_gosu_1_1_touch.html
	https://de.wikibooks.org/wiki/C%2B%2B-Programmierung:_Vector
	*/