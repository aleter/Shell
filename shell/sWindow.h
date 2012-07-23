#pragma once


#include <windows.h>


class sWindow
{
public:
	sWindow(void);
	~sWindow(void);
	
private:
	HWND window;
	static long int _stdcall WindowProcedure(HWND _window,unsigned int _message,WPARAM _wParam,LPARAM _lParam);
    long int Message(HWND window,unsigned int msg,WPARAM wp,LPARAM lp);
	void redraw();
	void mouseMove(int,int);
	void resize(unsigned int , unsigned int );

	unsigned int _height; 
	unsigned int _width; 
	unsigned int _v_corner; 
	unsigned int _h_corner; 
	int _posX;
	int _posY;

};

