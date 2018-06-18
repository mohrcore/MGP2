#include <Windows.h>

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

HWND createWin32Window(int x, int y, int w, int h)
{
	WNDCLASS wclass = { 0 };
	wclass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wclass.lpfnWndProc = (WNDPROC)WindowProc;

	return CreateWindow(0, "M3DFW WIN32", WS_OVERLAPPEDWINDOW | WS_VISIBLE, x, y, w, h, 0, 0, g_hInstance, 0);
}

HWND m3dfw_win32__createWindow(int w, int h)
{
	HWND window = createWin32Window(0, 0, w, h);

	HDC dc = GetDC(window);
	SetPixelFormat(dc, ChoosePixelFormat(dc, &win32_pfd), &win32_pfd);

	HGLRC gl_context = wglCreateContext(dc);
	wglMakeCurrent(dc, gl_context);

	return window;
}

int main();