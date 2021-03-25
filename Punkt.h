#ifndef PNKT_H_
#define PNKT_H_

#include "Vec2D.h"

class Punkt {
  private:
	TCanvas* canvas;
	TColor color;

  public:
	float r;
	Vec2D vec, pos;

	Punkt(TCanvas* canvas, float r) : canvas(canvas), vec(0, 0), pos(0, 0), r(r) {
		pos = Vec2D(random(canvas->ClipRect.Right), random(canvas->ClipRect.Bottom));
		vec = Vec2D(float(random(200)) / 100 - 1.0, float(random(200)) / 100 - 1.0);
		color = (TColor)RGB(random(180) + 40, random(180) + 40, random(180) + 40);
	}

	void Draw() {
		canvas->Brush->Color = color;
		canvas->Pen->Style = psClear;
		canvas->Ellipse(pos.x - r, pos.y - r, pos.x + r, pos.y + r);
	};
};

#endif
