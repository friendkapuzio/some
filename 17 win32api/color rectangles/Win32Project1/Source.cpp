#undef UNICODE

#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

char szClassName[] = "ClassName";

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE HPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd;
	MSG msg;
	WNDCLASS wcApp;

	// Заполняем структуру класса окна 
	wcApp.lpszClassName = szClassName;
	wcApp.hInstance = hInstance;
	wcApp.lpfnWndProc = WndProc;
	wcApp.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcApp.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcApp.lpszMenuName = 0;
	wcApp.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wcApp.style = CS_HREDRAW | CS_VREDRAW;
	wcApp.cbClsExtra = 0;
	wcApp.cbWndExtra = 0;

	// Регистрируем класс окна
	if (!RegisterClass(&wcApp))
	{
		MessageBox(NULL, "Class hasn't been registered", "RegisterClass", MB_OK);
		return 0;
	}

	hWnd = CreateWindow(szClassName, "Simple Windows Program", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, 0, hInstance, 0);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&msg, 0, 0, 0)) 
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rect;
	switch (uMsg)
	{
	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);
		GetClientRect(hWnd, &rect);
		int y = rect.bottom/30, x = rect.right/30;
		for (int i = 1; i < 15; ++i)
		{
			HBRUSH brush = CreateSolidBrush(RGB(i * 12, i * 12, i * 12));
			SelectObject(hdc, brush);
			Rectangle(hdc, rect.left + x*i, rect.top + y*i, rect.right - x*i, rect.bottom - y*i);
			RECT rec;
			SetRect(&rec, rect.left + x*i, rect.top + y*i, rect.right - x*i, rect.bottom - y*i);
			FillRect(hdc, &rec, brush);
			DeleteObject(brush);
		}
		EndPaint(hWnd, &ps);
		break;
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return (DefWindowProc(hWnd, uMsg, wParam, lParam));
	}
	return (0);
}