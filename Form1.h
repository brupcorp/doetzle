#ifndef Form1H
#define Form1H

#pragma resource "Form.dfm"

#include <vcl.h>

#include "PointerList.h"
#include "Punkt.h"

class TForm1 : public TForm {
  __published:
	TTimer* Timer1;
	void EVENT Physics();
	void EVENT DrawIt();
	void EVENT FormResize();
	void EVENT KeyD(TObject*, WORD& Key, TShiftState Shift);

  public:
	int w, h;
	PointerList<Punkt> list;
	EVENT TForm1(TComponent* Owner);
};

extern PACKAGE TForm1* Form1;

#endif
