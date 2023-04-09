#pragma once
#pragma once

#include <time.h>
#include <stdlib.h>
#include <Windows.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>

using namespace std;

#define col GetStdHandle(STD_OUTPUT_HANDLE) // 콘솔창의 핸들정보 받기

#define BLACK SetConsoleTextAttribute(col, 0x0000);
#define RED SetConsoleTextAttribute(col, 0x000c); // 빨간색
#define BLUE SetConsoleTextAttribute(col, 0x0001 | 0x0008); // 파란색
#define HIGH SetConsoleTextAttribute(col, 0x000a); // 연두색
#define WHITE SetConsoleTextAttribute(col, 0x000f); // 흰색
#define SKY SetConsoleTextAttribute(col, 0x000b); // 하늘색
#define YEL SetConsoleTextAttribute(col, 0x000e); // 노랑색
#define HIG SetConsoleTextAttribute(col, 0x000d); // 형광색
#define GOLD SetConsoleTextAttribute(col, 0x0006); // 금색
#define JAJU SetConsoleTextAttribute(col, 0x0005); // 자주색
#define PII SetConsoleTextAttribute(col, 0x0004); // 피색
#define GREEN SetConsoleTextAttribute(col, 0x0002); // 녹색
#define VIO SetConsoleTextAttribute(col, 0x0001 | 0x0008 | 0x000c); // 보라색
#define UP 72
#define DOWN 80 
#define LEFT 75 
#define RIGHT 77
#define ENTER 13

#pragma comment (lib,"winmm.lib")	

//////////////////////////////// 그리기 /////////////////////////////////////////
void removeCursor(void)
{ // 커서를 안보이게 한다

	CONSOLE_CURSOR_INFO curInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curInfo.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}
void gotoxy(int x, int y)
{
	COORD pos = { (short)x, (short)y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void textcolor(int fg_color, int bg_color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), fg_color | bg_color << 4);
}

void showCursor(void) { // 커서를 보이게 한다
	CONSOLE_CURSOR_INFO curInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curInfo.bVisible = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}

void cls(int bg_color, int text_color) // 화면 지우기
{
	char cmd[100];
	int fg_color = 0;
	system("cls");
	sprintf_s(cmd, 100, "COLOR %x%x", bg_color, text_color);
	system(cmd);

}

// 콘솔에 시작할 때 출력
//string a[20] = {
//	"=============================================================================================================\n",
//	"=============================================================================================================\n\n",
//	" _      _  _    _    _         _    _  _  _          _       _____                _\n" ,
//	"| |    (_)| |  | |  | |       | |  | |(_)| |        | |     |  ___|              | |\n" ,
//	"| |     _ | |_ | |_ | |  ___  | |  | | _ | |_   ___ | |__   | |__   _   _  _ __  | |__    ___   ___\n" ,
//	"| |    | || __ || __|| | / _ \\ | |/\\| || || __| / __ || '_ \\  |  __| | | | || '_ \\ | '_ \\  / _ \\ / _ \\\n",
//	"| |____| || |_ | |_ | ||  __ / \\ / \\  /| || |_ | (__ | | | | | |___ | |_| || | | || | | ||  __/|  __ /\n",
//	"\\_____/|_ | \\__ | \\__ || _ | \\___ | \\ / \\/ |_ | \\__ | \\___ || _| |_ | \\____ / \\__,_ || _| |_ || _| |_ | \\___ | \\___ |\n\n",
//	"=============================================================================================================\n",
//	"=============================================================================================================\n"
//};

void intro_start() {
	removeCursor();
}
