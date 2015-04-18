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
	static int color = 0;
	static int prevcolor = 0;
	switch (uMsg)
	{
	case WM_CREATE:
		SetTimer(hWnd, 1, 1000, NULL);
		break;
	case WM_TIMER:
		if (prevcolor == 0 && color == 1)
			++color;
		else if (prevcolor == 2 && color == 1)
			--color;
		else if (color == 0)
		{
			++color;
			prevcolor = 0;
		}
		else
		{
			--color;
			prevcolor = 2;
		}
		InvalidateRect(hWnd, &rect, TRUE);
		break;
	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);
		GetClientRect(hWnd, &rect);
		HBRUSH brush = CreateSolidBrush(RGB(120, 120, 120));
		SelectObject(hdc, brush);
		Rectangle(hdc, rect.right/2 - rect.right/10, rect.bottom/50 , rect.right/2+rect.right/10, rect.bottom*49/50);
		RECT rec;
		SetRect(&rec, rect.right / 2 - rect.right / 10, rect.bottom / 50, rect.right / 2 + rect.right / 10, rect.bottom * 49 / 50);
		DeleteObject(brush);
		if (color == 0)
		{
			brush = CreateSolidBrush(RGB(255, 0, 0));
		}
		else
		{
			brush = CreateSolidBrush(RGB(170, 0, 0));
		}
		SelectObject(hdc, brush);
		Ellipse(hdc, rec.left, rec.top, rec.right, rec.bottom / 3);
		DeleteObject(brush);
		if(color == 1)
		{
			brush = CreateSolidBrush(RGB(255, 255, 0));
		}
		else
		{
			brush = CreateSolidBrush(RGB(170, 170, 0));
		}
		SelectObject(hdc, brush);
		Ellipse(hdc, rec.left, rec.top + rec.bottom / 3, rec.right, rec.bottom * 2 / 3);
		DeleteObject(brush);
		if (color == 2)
		{
			brush = CreateSolidBrush(RGB(0, 255, 0));
		}
		else
		{
			brush = CreateSolidBrush(RGB(0, 170, 0));
		}
		
		SelectObject(hdc, brush);
		Ellipse(hdc, rec.left, rec.top + rec.bottom*2 / 3, rec.right, rec.bottom);
		DeleteObject(brush);

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