/**
 * File Name: DesignSet.h
 *
 * Description:
 * 디자인을 위한 색상 정의 및 함수 정의
 **/
#include <Windows.h>
#include <string>

enum color {
	black, blue, green, skyblue, red,
	purple, yellow, white, grey, lightBlue,
	lightGreen, lightSkyblue, lightRed,
	lightPurple, lightYellow, darkWhite
};

// Adornment
void changeColor(int);
void printLogo();
void printContent(std::string);
void printAccontMenu(int);
void printSuspension(int);

// system("cls");