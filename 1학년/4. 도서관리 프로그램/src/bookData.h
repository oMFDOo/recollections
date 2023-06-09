#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>
#include <limits>

#define endl "\n"

#pragma once

bool presenceOfInfo[10];
int matchPoint[sizeof(presenceOfInfo)];

// 색상 정의
enum color {
	black, blue, green, skyblue, red,
	purple, yellow, white, grey, lightBlue,
	lightGreen, lightSkyblue, lightRed,
	lightPurple, lightYellow, darkWhite
};

// 색 설정
void setColor(int color, int bgcolor) {

	color &= 0xf;
	bgcolor &= 0xf;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (bgcolor << 4) | color);

}

// 도서 정보 구조체
struct library {
	int page;
	int price;
	int publicationDate;
	std::string name;
	std::string author;
};

// 기본 입력값
library LB[10] = {
		{300, 12500, 20191130, "김한규의 국가(2019)", "김한규"},
		{348, 48200, 20130325, "이상한 나라의 밍키", "김밍키"},
		{172, 14500, 20190126, "현수막개론", "낙타"},
		{1568, 18700, 20040211, "잠 못 이루는 협곡에", "승미"},
		{593, 34000, 20080402, "진주의 파티플랜", "나방신"},
		{120, 8000, 1, "경주, 역사의 중심에 서다. - 개정판", "동건"},
		{312, 11000, 20170328, "단체로 무친 사회 - 반사회적 행동의 목격", "이승훈"},
};