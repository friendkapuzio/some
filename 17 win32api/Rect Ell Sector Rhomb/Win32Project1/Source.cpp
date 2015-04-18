#undef UNICODE

#include <windows.h>
#include <cmath>

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
	RECT rect;

	switch (uMsg) {
	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);
		GetClientRect(hWnd, &rect);
		HPEN pen = CreatePen(PS_SOLID, 3, RGB(150, 150, 150));
		HBRUSH brush = CreateSolidBrush(RGB(255, 170, 255));
		SetBkMode(hdc, TRANSPARENT);
		SelectObject(hdc, pen);
		SelectObject(hdc, brush);
		MoveToEx(hdc, rect.right / 2, 0, NULL);
		LineTo(hdc, rect.right / 2, rect.bottom);
		MoveToEx(hdc, 0, rect.bottom / 2, NULL);
		LineTo(hdc, rect.right, rect.bottom / 2);
		RECT rec;

		SetRect(&rec, 0, 0, rect.right / 2, rect.bottom / 2);
		Rectangle(hdc, rec.left + 30, rec.top + 30, rec.right - 30, rec.bottom - 30);
		DrawText(hdc, "Rectangle", -1, &rec, DT_SINGLELINE | DT_CENTER | DT_BOTTOM);

		DeleteObject(brush);
		brush = CreateHatchBrush(HS_BDIAGONAL, RGB(255, 0, 0));
		SelectObject(hdc, brush);
		SetRect(&rec, 0, rect.bottom / 2, rect.right/2, rect.bottom);
		Ellipse(hdc, 30, rect.bottom / 2+30, rect.right / 2-30, rect.bottom-30);
		DrawText(hdc, "Ellipse", -1, &rec, DT_SINGLELINE | DT_CENTER | DT_BOTTOM);

		DeleteObject(brush);
		HBITMAP bmp = (HBITMAP)LoadImage(NULL, "star.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		brush = CreatePatternBrush(bmp);
		SelectObject(hdc, brush);
		SetRect(&rec, rect.right / 2, 0, rect.right, rect.bottom / 2);
		Pie(hdc, rec.left + 30, 30, rec.right - 30, rec.bottom - 30, rec.right, rec.bottom / 2, rec.right, rec.bottom / 2 - (rec.right - 30.0)*sqrt(3)/12.0);
		DrawText(hdc, "Sector", -1, &rec, DT_SINGLELINE | DT_CENTER | DT_BOTTOM);

		SetRect(&rec, rect.right / 2, rect.bottom / 2, rect.right, rect.bottom);
		MoveToEx(hdc, rect.right*3/4, rect.top +rec.top +30, NULL);
		LineTo(hdc, rect.right/2 + 30, rect.bottom*3/4);
		LineTo(hdc, rect.right*3/4 , rec.bottom - 30);
		LineTo(hdc, rec.right - 30, rect.bottom*3/4);
		LineTo(hdc, rect.right * 3 / 4, rect.top + rec.top + 30);
		DrawText(hdc, "Rhomb", -1, &rec, DT_SINGLELINE | DT_CENTER | DT_BOTTOM);

		DeleteObject(pen);
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