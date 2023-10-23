#include <Windows.h>

bool running = true;

struct Render_State {
	int height, width;
	void* memory;
	BITMAPINFO bitmap_info;
};
Render_State render_state;

#include "renderer.cpp"


LRESULT CALLBACK window_callback(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lparam)
{
	LRESULT result = 0;
	switch (uMsg) {
	case WM_CLOSE:
	case WM_DESTROY: {
		running = false;
		}break;

	case WM_SIZE: {
		RECT rect;
		GetClientRect(hwnd, &rect);
		render_state.width = rect.right - rect.left;
		render_state.height = rect.bottom - rect.top;

		int size = render_state.width * render_state.height * sizeof(unsigned int);

		if (render_state.memory) VirtualFree(render_state.memory, 0, MEM_RELEASE);
		render_state.memory = VirtualAlloc(0, size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

		render_state.bitmap_info.bmiHeader.biSize = sizeof(render_state.bitmap_info.bmiHeader);
		render_state.bitmap_info.bmiHeader.biWidth = render_state.width;
		render_state.bitmap_info.bmiHeader.biHeight = render_state.height;
		render_state.bitmap_info.bmiHeader.biPlanes = 1;
		render_state.bitmap_info.bmiHeader.biBitCount = 32;
		render_state.bitmap_info.bmiHeader.biCompression = BI_RGB;

	}break;

	default: {
		result = DefWindowProc(hwnd, uMsg, wParam, lparam);
	}
		   return result;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lparam);
}

int winmain(HINSTANCE hinstance, HINSTANCE hprevinstance, LPSTR lpcmdline, int nShowCmd)
{
	//Create window Class
	WNDCLASS window_class = {};
	window_class.style = CS_HREDRAW | CS_VREDRAW;
	window_class.lpszClassName = "Game Window Class";
	window_class.lpfnWndProc; //Call back function

	// Registar Class
	RegisterClass(&window_class);

	//Create window
	HWND window = CreateWindow(window_class.lpszClassName, "PONG",WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT,CW_USEDEFAULT, 1200, 720, 0, 0, hinstance, 0);
	HDC hdc = GetDC(window);

	//Game Loop
	while (running) {
		//input
		MSG message;
		while (PeekMessage(&message, window, 0, 0, PM_REMOVE)) {
			TranslateMessage(&message);
			DispatchMessage(&message);
		}

		//Simulate
		clear_screen(0xff5500);
		draw_rect(50,50,200,500,0xff0000);

		//Render
		StretchDIBits(hdc, 0, 0, render_state.width, render_state.height, 0, 0, render_state.width, render_state.height, render_state.memory, &render_state.bitmap_info, DIB_RGB_COLORS, SRCCOPY);

	}

}