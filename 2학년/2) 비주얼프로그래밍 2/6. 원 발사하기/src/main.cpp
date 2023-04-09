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
	WndClass.lpszClassName = _T("20193148 황진주");
	RegisterClass(&WndClass);
	hwnd = CreateWindow(_T("20193148 황진주"),
		_T("20193148 황진주"),
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

#define BSIZE 20

double LengthPts(int x1, int y1, int x2, int y2) {
	return(sqrt((float)(x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

bool InCircle(int x, int y, int mx, int my) {
	if (LengthPts(x, y, mx, my) < BSIZE) {
		return true;
	}
	return false;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	HBRUSH hBrush, oldBrush;
	HPEN hPen, oldPen;
	static int startX, startY, oldX, oldY;
	static bool	Drag, Selection, Move;
	static int mx, my;
	static int cnt;
	int endX, endY;

	switch (iMsg)
	{
	case WM_CREATE:
		cnt = 10;
		startX = oldX = 20;
		startY = oldY = 20;
		Drag = Selection = Move = false;
		break;
	case WM_LBUTTONDOWN:
		mx = LOWORD(lParam);
		my = HIWORD(lParam);
		if (InCircle(startX, startY, mx, my)) {
			Drag = Selection = true;
			InvalidateRgn(hwnd, NULL, true);
		}
		break;
	case WM_LBUTTONUP:
		if (cnt >= 10) KillTimer(hwnd, 1);
		mx = LOWORD(lParam);
		my = HIWORD(lParam);
		if (Move) {
			oldX = startX;
			oldY = startY;
			cnt = 0;
			SetTimer(hwnd, 1, 10, NULL);
		}
		Drag = Selection = Move = false;
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		if (Selection) {
			hPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
			oldPen = (HPEN)SelectObject(hdc, hPen);
			hBrush = CreateSolidBrush(RGB(0, 255, 0));
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
		}
		Ellipse(hdc, startX - BSIZE, startY - BSIZE, startX + BSIZE, startY + BSIZE);
		EndPaint(hwnd, &ps);
		break;
	case WM_TIMER:
		if (cnt < 9) {
			startX += (mx - oldX) / 10;
			startY += (my - oldY) / 10;
			cnt++;
			InvalidateRgn(hwnd, NULL, true);
		}
		else if (cnt == 9) {
			startX = mx;
			startY = my;
			oldX = startX;
			oldY = startY;
			cnt++;
			InvalidateRgn(hwnd, NULL, true);
		}
		break;
	case WM_MOUSEMOVE:
		hdc = GetDC(hwnd);
		if (Drag && Selection && cnt >= 10) {
			SetROP2(hdc, R2_XORPEN);
			SelectObject(hdc, (HPEN)GetStockObject(WHITE_PEN));
			endX = LOWORD(lParam);
			endY = HIWORD(lParam);
			MoveToEx(hdc, startX, startY, NULL);
			LineTo(hdc, oldX, oldY);
			MoveToEx(hdc, startX, startY, NULL);
			LineTo(hdc, endX, endY);
			oldX = endX; oldY = endY;
			Move = true;
		}
		ReleaseDC(hwnd, hdc);
		break;
	case WM_DESTROY:

		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}