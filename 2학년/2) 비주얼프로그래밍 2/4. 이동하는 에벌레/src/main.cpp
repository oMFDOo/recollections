#include <windows.h>
#include <TCHAR.H>
#include <math.h>
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
	HWND     hwnd;
	MSG		 msg;
	WNDCLASS WndClass;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = _T("20193148 황진주 9주차 과제");
	RegisterClass(&WndClass);
	hwnd = CreateWindow(_T("20193148 황진주 9주차 과제"),
		_T("20193148 황진주 9주차 과제"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL
	);
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;
}



LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	static POINT mainCircle = { 60, 20 };
	static POINT nextCircle = { 20, 20 };

	switch (iMsg)
	{
	case WM_CREATE:
		break;
	case WM_KEYDOWN:
	{
		RECT size;
		GetClientRect(hwnd, &size);
		size.right = size.right / 40 * 40;
		size.bottom = size.bottom / 40 * 40;

		switch (wParam)
		{
		case VK_LEFT:
			if (mainCircle.x > 40) {
				nextCircle = mainCircle;
				mainCircle.x -= 40;
			}
			break;
		case VK_RIGHT:
			if (mainCircle.x < size.right - 20) {
				nextCircle = mainCircle;
				mainCircle.x += 40;
			}
			break;
		case VK_UP:
			if (mainCircle.y > 40) {
				nextCircle = mainCircle;
				mainCircle.y -= 40;
			}
			break;
		case VK_DOWN:
			if (mainCircle.y < size.bottom - 20) {
				nextCircle = mainCircle;
				mainCircle.y += 40;
			}
			break;
		}
		InvalidateRect(hwnd, NULL, TRUE);
	}
	case WM_PAINT:
	{
		hdc = BeginPaint(hwnd, &ps);
		RECT size;
		GetClientRect(hwnd, &size);
		Rectangle(hdc, 0, 0, size.right / 40 * 40, size.bottom / 40 * 40);

		HPEN red = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
		HPEN blue = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
		HPEN oldPen = (HPEN)SelectObject(hdc, red);
		Ellipse(hdc, mainCircle.x - 20, mainCircle.y - 20, mainCircle.x + 20, mainCircle.y + 20);
		SelectObject(hdc, blue);
		Ellipse(hdc, nextCircle.x - 20, nextCircle.y - 20, nextCircle.x + 20, nextCircle.y + 20);
		SelectObject(hdc, oldPen);
		DeleteObject(red);
		DeleteObject(blue);



		EndPaint(hwnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}
