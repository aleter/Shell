#include "sWindow.h"

#include <windows.h>
#include <iostream>




sWindow::sWindow(void):
		_height(200),
		_width(400),
		_v_corner(10),
		_h_corner(10),
		_posX(50),
		_posY(50)
{
	std::cout << "hello world!\n" ;
    const char* const myclass = "myclass" ;
    WNDCLASSEX wndclass = { sizeof(WNDCLASSEX), CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW, WindowProcedure,
                            0, 0, GetModuleHandle(0), LoadIcon(0,IDI_APPLICATION),
                            LoadCursor(0,IDC_ARROW), HBRUSH(COLOR_WINDOW+1),
                            0, myclass, LoadIcon(0,IDI_APPLICATION) } ;
    if( RegisterClassEx(&wndclass) )
    {

		


		
        window = CreateWindowEx( 0, myclass, "title",
                   WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
                   CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, GetModuleHandle(0), this ) ;
		SetWindowLong(window,GWL_USERDATA,(long int)this);
        if(window)
        {
            ShowWindow( window, SW_SHOWDEFAULT ) ;
			SetWindowLong(window, GWL_STYLE, GetWindowLong(window, GWL_STYLE) & ~WS_BORDER & ~WS_SIZEBOX & ~WS_DLGFRAME );
			resize(200,400);

            MSG msg ;
			while( GetMessage( &msg, 0, 0, 0 ) ) DispatchMessage(&msg) ;	
        }
    }
}


long __stdcall sWindow::WindowProcedure( HWND window, unsigned int msg, WPARAM wp, LPARAM lp )
{
	sWindow* application=0;

  if(msg==WM_NCCREATE)
    application=(sWindow*)lp;
  else
    application=(sWindow*)GetWindowLong(window,GWL_USERDATA);

  return application->Message(window,msg,wp,lp);
}

long int sWindow::Message(HWND window,unsigned int msg,WPARAM wp,LPARAM lp)
{
	switch(msg)
    {
        case WM_DESTROY:
            std::cout << "\ndestroying window\n" ;
            PostQuitMessage(0) ;
            return 0L ;
		case WM_PAINT:
			std::cout << "redraw";
			redraw();
		case WM_MOUSEMOVE:
			mouseMove(GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam));

        case WM_LBUTTONDOWN:
            std::cout << "\nmouse left button down at (" << LOWORD(lp)
                      << ',' << HIWORD(lp) << ")\n" ;
            // fall thru
        default:
            std::cout << '.' ;
            return DefWindowProc( window, msg, wp, lp ) ;
    }
}

sWindow::~sWindow(void)
{
}


void sWindow::redraw()
{
	 
}

void sWindow::mouseMove(int x, int y)
{
	 
}

void sWindow::resize(unsigned int h, unsigned int w)
{

	_height = h;
	_width = w;

	POINT * mass = new POINT[8]; 

	mass[0].x = 0;
	mass[0].y = _v_corner;
	mass[1].x = _h_corner;
	mass[1].y = 0;
	mass[2].x = _width - _h_corner;
	mass[2].y = 0;
	mass[3].x = _width;
	mass[3].y = _v_corner;
	mass[4].x = _width;
	mass[4].y = _height - _v_corner;
	mass[5].x = _width - _h_corner;;
	mass[5].y = _height;
	mass[6].x = _h_corner;
	mass[6].y = _height;
	mass[7].x = 0;
	mass[7].y = _height - _v_corner;
	HRGN rgn = CreatePolygonRgn(const_cast<const POINT*>(mass),8, WINDING);
	SetWindowRgn(window,rgn,FALSE);

	SetWindowLong(window, GWL_STYLE, GetWindowLong(window, GWL_STYLE) & ~WS_BORDER & ~WS_SIZEBOX & ~WS_DLGFRAME );
	SetWindowPos(window, HWND_TOP, _posX, _posY, _width, _height, SWP_FRAMECHANGED);


}