#include "stdafx.h"

#include <Gosu/Gosu.hpp>
#include <Gosu/AutoLink.hpp>

#include <vector>
#include <string>
#include <iostream>
#include <list>
#include "Vektor2d.h"

// Simulationsgeschwindigkeit
const double DT = 100.0;

const int x_groesse_rahmen = 600;
const int y_groesse_rahmen = 800;

class Figur {
public:
	double x_pos;
	double y_pos;
	int x_laenge;
	int y_laenge;
	int leben = 1;
	Gosu::Image bild;
	void positioniere(double x = 100, double y = 100) {
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
	Figur Spieler;
	std::list<Figur> Gegnerliste_1;
	std::list<Schuss> Schussliste;
	int i = 0;
	int cnt = 0;
	int Anzahl_Gegner = 12;


public:

		GameWindow() : Window(x_groesse_rahmen, y_groesse_rahmen), Spieler("SpielerTyp1.png")
	{
		
		for (int i = 0; i < Anzahl_Gegner; i++){
			Gegnerliste_1.push_back(Figur("GegnerTyp1.png"));
			Gegnerliste_1.back().positioniere(i * 50, 0);
		}

		set_caption("Github Test"); // Name lautet nicht Qwertz
		Spieler.positioniere(275, 725); // Spieler spawnen
		
		// Figuren existent machen
		Spieler.leben_geben(10);
	}
	

	// wird bis zu 60x pro Sekunde aufgerufen.
	// Wenn die Grafikkarte oder der Prozessor nicht mehr hinterherkommen,
	// dann werden `draw` Aufrufe ausgelassen und die Framerate sinkt
	void draw() override {
		for (auto i = Gegnerliste_1.begin(); i != Gegnerliste_1.end(); i++) {
			i->bild.draw(i->x_pos, i->y_pos, 0.0);
		}
		for (auto i = Schussliste.begin(); i != Schussliste.end(); i++) {
			i->draw();
		}
		Spieler.bild.draw(Spieler.x_pos, Spieler.y_pos, 0.0);
		}
	
	// Wird 60x pro Sekunde aufgerufen
	void update() override
	{
		for (auto i = Gegnerliste_1.begin(); i != Gegnerliste_1.end(); i++) {
			i->positioniere(i->x_pos, i->y_pos + 0.5);
		}
		
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
		// Schießen
		cnt++;
		if (input().down(Gosu::MS_LEFT)) {
			if (cnt >= 30) {
				Schussliste.push_back(Schuss());
				Schussliste.back().x_pos = Spieler.x_pos + 24;
				Schussliste.back().y_pos = Spieler.y_pos;
				cnt = 0;
			}
		}
		for (auto i = Schussliste.begin(); i != Schussliste.end(); i++) {
			i->update();
		}

		for (auto i = Schussliste.begin(); i != Schussliste.end(); i++) {
			auto j = Gegnerliste_1.begin();
			while ( j != Gegnerliste_1.end()) {
				if (i->x_pos >= j->x_pos && i->x_pos <= j->x_pos + j->x_laenge) {
					if (i->y_pos <= j->y_pos + j->y_laenge && i->y_pos >= j->y_pos) {
						j->treffer();
						if (j->leben == 0) {
							j = Gegnerliste_1.erase(j);
							continue;
						}
					}
				}
				j++;
			}
		}
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