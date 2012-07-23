#include "sWindow.h"

#include <windows.h>
#include <iostream>


long __stdcall WindowProcedure( HWND window, unsigned int msg, WPARAM wp, LPARAM lp )
{
	switch(msg)
    {
        case WM_DESTROY:
            std::cout << "\ndestroying window\n" ;
            PostQuitMessage(0) ;
            return 0L ;
        case WM_LBUTTONDOWN:
            std::cout << "\nmouse left button down at (" << LOWORD(lp)
                      << ',' << HIWORD(lp) << ")\n" ;
            // fall thru
        default:
            std::cout << '.' ;
            return DefWindowProc( window, msg, wp, lp ) ;
    }
}

sWindow::sWindow(void)
{
	std::cout << "hello world!\n" ;
    const char* const myclass = "myclass" ;
    WNDCLASSEX wndclass = { sizeof(WNDCLASSEX), CS_DBLCLKS, WindowProcedure,
                            0, 0, GetModuleHandle(0), LoadIcon(0,IDI_APPLICATION),
                            LoadCursor(0,IDC_ARROW), HBRUSH(COLOR_WINDOW+1),
                            0, myclass, LoadIcon(0,IDI_APPLICATION) } ;
    if( RegisterClassEx(&wndclass) )
    {
		POINT * mass = new POINT[8]; 

		mass[0].x = 0;
		mass[0].y = 10;
		mass[1].x = 10;
		mass[1].y = 0;
		mass[2].x = 90;
		mass[2].y = 0;
		mass[3].x = 100;
		mass[3].y = 10;
		mass[4].x = 100;
		mass[4].y = 90;
		mass[5].x = 90;
		mass[5].y = 100;
		mass[6].x = 10;
		mass[6].y = 100;
		mass[7].x = 0;
		mass[7].y = 90;

		


		HRGN rgn = CreatePolygonRgn(const_cast<const POINT*>(mass),8, WINDING);
        HWND window = CreateWindowEx( 0, myclass, "title",
                   WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
                   CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, GetModuleHandle(0), this ) ;
        if(window)
        {
            ShowWindow( window, SW_SHOWDEFAULT ) ;
			SetWindowRgn(window,rgn,FALSE);

			SetWindowLong(window, GWL_STYLE, GetWindowLong(window, GWL_STYLE) & ~WS_BORDER & ~WS_SIZEBOX & ~WS_DLGFRAME );
			SetWindowPos(window, HWND_TOP, 50, 50, 100, 100, SWP_FRAMECHANGED);

            MSG msg ;
			while( GetMessage( &msg, 0, 0, 0 ) ) DispatchMessage(&msg) ;	
        }
    }
}


sWindow::~sWindow(void)
{
}


void sWindow::loop()
{
	 
}