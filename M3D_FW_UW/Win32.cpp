#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <iostream>

//#include <M3DFW.h>

#include "EXPORT.h"

HINSTANCE g_hInstance;

BOOL WINAPI _stdcall DllMain(_In_ HINSTANCE hInstance, _In_ DWORD fdwReason, _In_ HINSTANCE hPrevInstance)
{
	g_hInstance = hInstance;

	return TRUE;
}

PIXELFORMATDESCRIPTOR win32_pfd = {
	sizeof(PIXELFORMATDESCRIPTOR),
	1,
	PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    //Flags
	PFD_TYPE_RGBA,            //The kind of framebuffer. RGBA or palette.
	32,                        //Colordepth of the framebuffer.
	0, 0, 0, 0, 0, 0,
	0,
	0,
	0,
	0, 0, 0, 0,
	24,                        //Number of bits for the depthbuffer
	8,                        //Number of bits for the stencilbuffer
	0,                        //Number of Aux buffers in the framebuffer.
	PFD_MAIN_PLANE,
	0,
	0, 0, 0
};


LRESULT CALLBACK WindowProc(HWND window, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//switch (msg)
	//{
	//case WM_CREATE:

	//	break;

	//case WM_CLOSE:


	//}

	return DefWindowProc(window, msg, wParam, lParam);
}

HWND createWin32Window(int x, int y, int w, int h, HWND parent)
{
	WNDCLASS wclass = { 0 };
	wclass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wclass.lpfnWndProc = (WNDPROC)WindowProc;
	wclass.hInstance = g_hInstance;
	wclass.hbrBackground = (HBRUSH)(COLOR_BACKGROUND);
	wclass.lpszClassName = "M3DFWRWININDOW";

	if (!RegisterClass(&wclass))
		std::cout << "Cannot register WNDCLASS for rendering window!";

	return CreateWindow("M3DFWRWININDOW", "M3DFW WIN32", WS_VISIBLE | WS_CHILD, x, y, w, h, parent, NULL, g_hInstance, NULL);
}

//HWND createWin32Window(int x, int y, int w, int h)
//{
//	return CreateWindowEx(
//
//	)
//}

HRESULT EXPORT m3dfw_win32__prepareWinCtx(HWND window)
{
	HDC dc;
	int pixel_format;
	HGLRC gl_context;

	if (!(dc = GetDC(window)))
	{
		MessageBox(NULL, "Can't create a GL device context!", "ERROR!", MB_OK);
		return FALSE;
	}
	if (!(pixel_format = ChoosePixelFormat(dc, &win32_pfd)))
	{
		MessageBox(NULL, "Can't find a suitable pixel format!", "ERROR!", MB_OK);
		return FALSE;
	}
	if (!SetPixelFormat(dc, pixel_format, &win32_pfd))
	{
		MessageBox(NULL, "Can't set a pixel format!", "ERROR!", MB_OK);
		return FALSE;
	}
	if (!(gl_context = wglCreateContext(dc)))
	{
		MessageBox(NULL, "Can't create OpenGL context!", "ERROR!", MB_OK);
		return FALSE;
	}
	if (!wglMakeCurrent(dc, gl_context))
	{
		MessageBox(NULL, "Can;t activate OpenGL context!", "ERROR!", MB_OK);
		return FALSE;
	}

	return TRUE;
}

HWND EXPORT m3dfw_win32__createWindow(int w, int h, HWND parent)
{
	HWND window = createWin32Window(0, 0, w, h, parent);

	m3dfw_win32__prepareWinCtx(window);

	return window;
}