#undef UNICODE

#include <windows.h>
#include <stdio.h>

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
	if (!RegisterClass(&wcApp)){
		MessageBox(NULL, "Class hasn't been registered", "RegisterClass", MB_OK);
		return 0;
	}

	hWnd = CreateWindow(szClassName, "Simple Windows Program", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, 0, hInstance, 0);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&msg, 0, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	static RECT rect;
	static int time=0;
	static char str[100];

	switch (uMsg)
	{
	case WM_CREATE:
		SetTimer(hWnd, 1, 1000, NULL);
		break;
	case WM_TIMER:
		++time;
		InvalidateRect(hWnd, &rect, TRUE);
		break;
	case WM_CHAR:
		switch (wParam)
		{
		case VK_EXECUTE:
			SetTimer(hWnd, 1, 1000, NULL);
			break;
		case VK_INSERT:
			KillTimer(hWnd, 1);
			break;
		case VK_PAUSE:
			KillTimer(hWnd, 1);
			time = 0;
			SetTimer(hWnd, 1, 1000, NULL);
			break;
		}
		InvalidateRect(hWnd, &rect, TRUE);
		break;
	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);
		GetClientRect(hWnd, &rect);
		Ellipse(hdc, rect.right / 2 - 50, rect.bottom / 2 - 50, rect.right / 2 + 50, rect.bottom / 2 + 50);
		sprintf_s(str, "%d", time);
		DrawText(hdc, str, -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
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