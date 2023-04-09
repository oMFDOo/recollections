#include <windows.h>
#include <TCHAR.H>

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
	WndClass.lpszClassName = _T("20193148 황진주 5주차 과제");
	RegisterClass(&WndClass);
	hwnd = CreateWindow(_T("20193148 황진주 5주차 과제"),
		_T("20193148 황진주 5주차 과제"),
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

// 사각형 출력
void paint(HWND hwnd, HDC hdc, COLORREF color, RECT R) {

	HBRUSH hBrush, oldBrush;
	hBrush = CreateSolidBrush(color);			  // 브러쉬 값 설정
	oldBrush = (HBRUSH)SelectObject(hdc, hBrush); //  hdc등록 및 사용한 브러쉬 값 저장해두기
	Rectangle(hdc, R.left, R.top, R.right, R.bottom);
	SelectObject(hdc, oldBrush);				  // 내부 칠하기
	DeleteObject(hBrush);						  // 브러쉬 핸들 삭제
}

struct REC {
	RECT r;
	COLORREF color;
	WPARAM key;
	TCHAR str[10];
};

#define SIZE 4

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	static REC R[SIZE] = {
		{{ 100, 180, 180, 260 }, RGB(255, 255, 255), VK_LEFT , _T("왼쪽")  },
		{{ 180, 100, 260, 180 }, RGB(255, 255, 255), VK_UP	 , _T("위쪽")  },
		{{ 260, 180, 340, 260 }, RGB(255, 255, 255), VK_RIGHT, _T("오른쪽")},
		{{ 180, 260, 260, 340 }, RGB(255, 255, 255), VK_DOWN , _T("아래쪽")}
	};

	static COLORREF colorR1, colorR2, colorR3, colorR4;
	COLORREF white = RGB(255, 255, 255);
	UINT center = DT_SINGLELINE | DT_CENTER | DT_VCENTER;

	switch (iMsg)
	{
	case WM_CREATE:
		break;
	case WM_KEYDOWN:
		for (int i = 0; i < SIZE; i++) {
			if (wParam == R[i].key) {
				R[i].color = RGB(255, 0, 0);
			}
		}
		InvalidateRgn(hwnd, NULL, FALSE);
		break;
	case WM_KEYUP:
		for (int i = 0; i < SIZE; i++) {
			if (wParam == R[i].key) {
				R[i].color = RGB(255, 255, 255);
			}
		}
		InvalidateRgn(hwnd, NULL, FALSE);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		for (int i = 0; i < SIZE; i++) {
			paint(hwnd, hdc, R[i].color, R[i].r);
			// 배경이 흰색일 때만 글자 출력
			if (R[i].color == white) {
				DrawText(hdc, R[i].str, _tcslen(R[i].str), &R[i].r, center);
			}
		}

		EndPaint(hwnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}