#include <math.h>
#include <time>

#include "Form1.h"
#include "str.h"

#define IN_BOUNDS(vec, r, szX, szY) vec.x - r >= 0 && vec.x + r <= szX&& vec.y - r >= 0 && vec.y + r <= szY

char speed = 4;
bool collision = false;

EVENT TForm1::TForm1(TComponent* Owner) : TForm(Owner) {
	randomize();
	list.append(new Punkt(Canvas, 15));
	DoubleBuffered = true;
}

// physics
void EVENT TForm1::Physics() {
	for(Iter<Punkt> i = list.begin(); i != list.end(); i++) {
		Punkt& p = *i;

		Vec2D preCalc = p.pos + p.vec * speed;

		if(collision) { // collision with others
			for(Iter<Punkt> j = list.begin(); j != list.end(); j++) {
				Punkt& p2 = *j;

				if(&p == &p2) continue;

				if(preCalc.dist(p2.pos) < p.r + p2.r) {
					p.vec = p.vec.getRebounced(p2.vec);
					preCalc = p.pos + p.vec * speed; // recalc new pos
				}
			}
			preCalc = p.pos + p.vec * speed; // recalc new pos
		}

		if(IN_BOUNDS(preCalc, p.r, w, h)) { // in bounding box
			p.pos = preCalc;
		} else {
			if(preCalc.x + p.r > w || preCalc.x - p.r < 0) { // x bounds
				p.vec.invertX();
				p.pos.x = w - p.r - (preCalc.x - p.r < 0) * (w - p.r * 2);
			}

			if(preCalc.y + p.r > h || preCalc.y - p.r < 0) { // y bounds
				p.vec.invertY();
				p.pos.y = h - p.r - (preCalc.y - p.r < 0) * (h - p.r * 2);
			}
		}
	}

	InvalidateRect(Handle, 0, true); // draw it
}

void EVENT TForm1::DrawIt() {
	for(unsigned i = 0; i < list.length(); i++) list[i].Draw();
}

void EVENT TForm1::FormResize() {
	w = Canvas->ClipRect.Right;
	h = Canvas->ClipRect.Bottom;
}

void EVENT TForm1::KeyD(TObject* Sender, WORD& Key, TShiftState Shift) {
	switch(Key) {
	case 0x20: list.append(new Punkt(Canvas, 15)); break;
	case 0x25: speed--; break;
	case 0x27: speed++; break;
	case 0x26: collision = !collision; break;
	}
	Caption = str("Es sind momentan " + list.length() + " Dötzle zu sehen! Geschwindigkeit: " + (int)speed + ", Kollision " +
				  (collision ? "Aktiv" : "Inaktiv"));
}
