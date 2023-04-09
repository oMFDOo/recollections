#include <windows.h>
#include <TCHAR.H>
#include <math.h>
#include <iostream>
#include <algorithm>
using namespace std;

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

#define BOX 140

struct Positon {
	int x1, y1, x2, y2;
};

void setZero(bool input[32]);							// 배열 초기화용
int clickPosition(Positon num[4][8], int x, int y);		// 클릭한 박스 번호 반환

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	HPEN pen, oldPen;
	static Positon num[4][8];	// 사각형 범위 저장
	static int inputX, inputY;	// 입력 x,y 좌표
	static int clickNum;		// 클릭된 사각형 번호
	static int count;			// 유효 입력 횟수
	static bool click;			// 클릭 여부
	static bool isClick[32];	// 클릭된 박스인가
	static bool isOdd[32];		// 그려야할 색상 판단

	switch (iMsg)
	{
	case WM_CREATE:
		count = click = clickNum = inputX = inputY = 0;
		setZero(isClick);
		setZero(isOdd);

		// 각 박스 번호 저장
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 8; j++) {
				num[i][j].x1 = j * BOX;
				num[i][j].y1 = i * BOX;
				num[i][j].x2 = (j + 1) * BOX;
				num[i][j].y2 = (i + 1) * BOX;
			}
		}
		break;
	case WM_LBUTTONUP:
		inputX = LOWORD(lParam);
		inputY = HIWORD(lParam);
		clickNum = clickPosition(num, inputX, inputY);

		// 한 번 입력된 곳 다시 누르면 무시
		if (isClick[clickNum] == false) {
			isClick[clickNum] = true;
			isOdd[clickNum] = !(count % 2);
			count++;
		}
		click = true;
		InvalidateRgn(hwnd, NULL, true);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		// 그리드 표시
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 8; j++) {
				Rectangle(hdc, j * BOX, i * BOX, (j + 1) * BOX, (i + 1) * BOX);
			}
		}
		if (click) {
			for (int i = 0; i < 32; i++) {
				if (isClick[i]) {
					if (isOdd[i] == true) {
						pen = CreatePen(PS_SOLID, 5, RGB(255, 0, 0));
					}
					else {
						pen = CreatePen(PS_SOLID, 5, RGB(0, 0, 255));
					}
					oldPen = (HPEN)SelectObject(hdc, pen);
					Ellipse(hdc, num[i / 8][i % 8].x1, num[i / 8][i % 8].y1, num[i / 8][i % 8].x2, num[i / 8][i % 8].y2);
					SelectObject(hdc, oldPen);
					DeleteObject(pen);
				}
			}
		}
		EndPaint(hwnd, &ps);
		click = false;
		break;
	case WM_TIMER:

		break;
	case WM_DESTROY:

		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}

void setZero(bool input[32]) {
	for (int i = 0; i < 32; i++) {
		input[i] = false;
	}
}


int clickPosition(Positon num[4][8], int x, int y) {
	int cnt = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 8; j++) {
			if (num[i][j].x1 <= x && x <= num[i][j].x2 && num[i][j].y1 <= y && y <= num[i][j].y2) {
				return cnt;
			}
			cnt++;
		}
	}
	return cnt;
}