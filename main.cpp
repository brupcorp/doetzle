#include "Form1.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	try {
		Application->Initialize();
		MakeForm(TForm1);
		Application->Run();
	} catch(Exception& e) { Application->ShowException(&e); }
	return 0;
}