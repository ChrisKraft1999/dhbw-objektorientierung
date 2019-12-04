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
	double x_pos;
	double y_pos;
	
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
	std::list<Figur> Gegnerliste_0;
	std::list<Figur> Gegnerliste_1;
	std::list<Figur> Gegnerliste_2;
	std::list<Figur> Gegnerliste_3;
	std::list<Figur> Gegnerliste_4;
	std::list<Figur> Gegnerliste_5;
	std::list<Schuss> Schussliste;
	int i = 0;
	int cnt = 0;
	double tempo = 0;
	int level = 0; 
	int Anzahl_Gegner = 12;


public:
	Gosu::Image gameover;
	bool game_over = FALSE;
	
	GameWindow() : Window(x_groesse_rahmen, y_groesse_rahmen), Spieler("SpielerTyp1.png"), gameover("game-over.jpg")
	{
		// Gegnerwelle 1
		for (int i = 0; i < Anzahl_Gegner; i++) {
			Gegnerliste_1.push_back(Figur("GegnerTyp1.png"));
			Gegnerliste_1.back().positioniere(i * 50, 0);
		}
		// Gegnerwelle 2
		for (int i = 0; i < Anzahl_Gegner; i++){
			Gegnerliste_2.push_back(Figur("GegnerTyp1.png"));
			if (i % 2) {
				Gegnerliste_2.back().positioniere(i * 50, 0);
			}
			else {
				Gegnerliste_2.back().positioniere(i * 50, 50);
			}
		}
		// Gegnerwelle 3
		for (int i = 0; i < Anzahl_Gegner; i++) {
			Gegnerliste_3.push_back(Figur("GegnerTyp1.png"));
			if (i == ((Anzahl_Gegner / 2) -1)) {
				Gegnerliste_3.back().positioniere((i-1) * 50, 50);
			}
			else if (i == (Anzahl_Gegner / 2)) {
				Gegnerliste_3.back().positioniere((i + 1) * 50, 50);
			}
			else {
				Gegnerliste_3.back().positioniere(i * 50, 0);
			}
		}
		// Gegnerwelle 4
		for (int i = 0; i < Anzahl_Gegner; i++) {
			Gegnerliste_4.push_back(Figur("GegnerTyp1.png"));
			if (i <= ((Anzahl_Gegner / 2) - 1)) {
				Gegnerliste_4.back().positioniere(i * 50, i * 50);
			}
			else {
				Gegnerliste_4.back().positioniere(i * 50, (Anzahl_Gegner * 50) - (i * 50) - 50);
			}
		}
		// Gegnerwelle 5
		for (int i = 0; i < (Anzahl_Gegner + 10); i++) {
			Gegnerliste_5.push_back(Figur("GegnerTyp1.png"));
			if (i < Anzahl_Gegner) {
				Gegnerliste_5.back().positioniere(i * 50, 0);
			}
			else if (i <= (Anzahl_Gegner + 4)) {
				Gegnerliste_5.back().positioniere((i - Anzahl_Gegner) * 50 + 50, (i - Anzahl_Gegner) * 50 + 50);
			}
			else {
				Gegnerliste_5.back().positioniere(((i + 1) - Anzahl_Gegner) * 50, (Anzahl_Gegner * 50) - (((i + 1) - Anzahl_Gegner) * 50) - 50);
			}
		}

		set_caption("Github Test"); // Name lautet nicht Qwertz
		Spieler.positioniere(275, 725); // Spieler spawnen
		
		Spieler.leben_geben(10);
	}
	

	// wird bis zu 60x pro Sekunde aufgerufen.
	// Wenn die Grafikkarte oder der Prozessor nicht mehr hinterherkommen,
	// dann werden `draw` Aufrufe ausgelassen und die Framerate sinkt
	void draw() override {
		// Zeichne Gegner
		for (auto i = Gegnerliste_0.begin(); i != Gegnerliste_0.end(); i++) {
			i->bild.draw(i->x_pos, i->y_pos, 0.0);
		}
		// Zeichne Gameover
		if (game_over == TRUE) {
			gameover.draw(90, 259, 0.0);
		}
		else {
			// Zeichne Spieler
			Spieler.bild.draw(Spieler.x_pos, Spieler.y_pos, 0.0);
			// Zeichne Schüsse
			for (auto i = Schussliste.begin(); i != Schussliste.end(); i++) {
				i->draw();
			}
		}
	}
	
	// Wird 60x pro Sekunde aufgerufen
	void update() override
	{
		if (input().down(Gosu::Button::Button(21))) {
			level = 0;
			game_over = FALSE;
			Gegnerliste_0.clear();
		}
		// Gegner bewegen
		for (auto i = Gegnerliste_0.begin(); i != Gegnerliste_0.end(); i++) {
			i->positioniere(i->x_pos, i->y_pos + tempo);
		}
		
		// Gameover Test
		for (auto i = Gegnerliste_0.begin(); i != Gegnerliste_0.end(); i++) {
			if (i->y_pos >= (y_groesse_rahmen - i->y_laenge)) {
				game_over = TRUE;
			}
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
		// Schuss cooldown
		cnt++;
		if (input().down(Gosu::MS_LEFT)) {
			if (cnt >= 30) {
				Schussliste.push_back(Schuss());
				Schussliste.back().x_pos = Spieler.x_pos + 24;
				Schussliste.back().y_pos = Spieler.y_pos;
				cnt = 0;
			}
		}

		// Schuss bewegt sich
		for (auto i = Schussliste.begin(); i != Schussliste.end(); i++) {
			i->update();
		} 

		// Auf Treffer testen
		auto i = Schussliste.begin();
		while ( i != Schussliste.end()) {
			auto j = Gegnerliste_0.begin();
			while ( j != Gegnerliste_0.end() && i != Schussliste.end()) {
				if (i->x_pos >= j->x_pos && i->x_pos <= j->x_pos + j->x_laenge) {
					if (i->y_pos <= j->y_pos + j->y_laenge && i->y_pos >= j->y_pos) {
						j->treffer();
						i = Schussliste.erase(i);
						if (j->leben == 0) {
							j = Gegnerliste_0.erase(j);
							continue;
						}
					}
				}
				else if (i->y_pos <= 0) {
					i = Schussliste.erase(i);
				}
				j++;
			}
			if (i != Schussliste.end()) { i++; }
		}

		// Wenn Gegner leer Level Erhöhen
		if (Gegnerliste_0.begin() == Gegnerliste_0.end()) {
			level++;
			switch (level) {
			case 1: tempo = 0.5; Gegnerliste_0 = Gegnerliste_1;  break;
			case 2: tempo = 1.0; Gegnerliste_0 = Gegnerliste_2;  break;
			case 3: tempo = 1.0; Gegnerliste_0 = Gegnerliste_3;  break;
			case 4: tempo = 1.0; Gegnerliste_0 = Gegnerliste_4;  break;
			case 5: tempo = 1.0; Gegnerliste_0 = Gegnerliste_5;  break;
			default: tempo = 0.5;  break;
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