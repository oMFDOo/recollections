#pragma once
#pragma once

#include <time.h>
#include <stdlib.h>
#include <Windows.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>

using namespace std;

#define col GetStdHandle(STD_OUTPUT_HANDLE) // �ܼ�â�� �ڵ����� �ޱ�

#define BLACK SetConsoleTextAttribute(col, 0x0000);
#define RED SetConsoleTextAttribute(col, 0x000c); // ������
#define BLUE SetConsoleTextAttribute(col, 0x0001 | 0x0008); // �Ķ���
#define HIGH SetConsoleTextAttribute(col, 0x000a); // ���λ�
#define WHITE SetConsoleTextAttribute(col, 0x000f); // ���
#define SKY SetConsoleTextAttribute(col, 0x000b); // �ϴû�
#define YEL SetConsoleTextAttribute(col, 0x000e); // �����
#define HIG SetConsoleTextAttribute(col, 0x000d); // ������
#define GOLD SetConsoleTextAttribute(col, 0x0006); // �ݻ�
#define JAJU SetConsoleTextAttribute(col, 0x0005); // ���ֻ�
#define PII SetConsoleTextAttribute(col, 0x0004); // �ǻ�
#define GREEN SetConsoleTextAttribute(col, 0x0002); // ���
#define VIO SetConsoleTextAttribute(col, 0x0001 | 0x0008 | 0x000c); // �����
#define UP 72
#define DOWN 80 
#define LEFT 75 
#define RIGHT 77
#define ENTER 13

#pragma comment (lib,"winmm.lib")	

//////////////////////////////// �׸��� /////////////////////////////////////////
void removeCursor(void)
{ // Ŀ���� �Ⱥ��̰� �Ѵ�

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

void showCursor(void) { // Ŀ���� ���̰� �Ѵ�
	CONSOLE_CURSOR_INFO curInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curInfo.bVisible = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}

void cls(int bg_color, int text_color) // ȭ�� �����
{
	char cmd[100];
	int fg_color = 0;
	system("cls");
	sprintf_s(cmd, 100, "COLOR %x%x", bg_color, text_color);
	system(cmd);

}

// �ֿܼ� ������ �� ���
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
