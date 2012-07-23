#pragma once


#include <windows.h>

long __stdcall WindowProcedure( HWND window, unsigned int msg, WPARAM wp, LPARAM lp );

class sWindow
{
public:
	sWindow(void);
	~sWindow(void);
	void loop();
private:
	HWND hwnd;


};

