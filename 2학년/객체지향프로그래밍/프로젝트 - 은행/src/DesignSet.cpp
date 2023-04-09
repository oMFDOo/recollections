#include "DesignSet.h"
#include <Windows.h>
#include <iostream>
#include <string>

using namespace std;

void changeColor(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
void printLogo() {
	cout << endl;
	changeColor(lightSkyblue);
	cout << "+====================================================================================================+" << endl;
	cout << "||\t\t\t\t\t\t\t\t\t\t\t\t    ||" << endl;
	cout << "||\t\t\t\t\t\t\t\t\t\t\t\t    ||" << endl;
	cout << "||\t::::    ::::  ::::::::::: ::::    :::  :::::::::      :::     ::::    ::: :::    :::\t    ||\n";
	cout << "||\t+:+:+: :+:+:+     :+:     :+:+:   :+:  :+:    :+:   :+: :+:   :+:+:   :+: :+:   :+:\t    ||\n";
	cout << "||\t+:+ +:+:+ +:+     +:+     :+:+:+  +:+  +:+    +:+  +:+   +:+  :+:+:+  +:+ +:+  +:+\t    ||\n";
	changeColor(skyblue);
	cout << "||\t+#+  +:+  +#+     +#+     +#+ +:+ +#+  +#++:++#+  +#++:++#++: +#+ +:+ +#+ +#++:++\t    ||\n";
	cout << "||\t+#+       +#+     +#+     +#+  +#+#+#  +#+    +#+ +#+     +#+ +#+  +#+#+# +#+  +#+\t    ||\n";
	cout << "||\t#+#       #+#     #+#     #+#   #+#+#  #+#    #+# #+#     #+# #+#   #+#+# #+#   #+#\t    ||\n";
	changeColor(blue);
	cout << "||\t###       ### ########### ###    ####  #########  ###     ### ###    #### ###    ###\t    ||\n";
	cout << "||\t\t\t\t\t\t\t\t\t\t\t\t    ||" << endl;
	cout << "||\t\t\t\t\t\t\t\t\t\t\t\t    ||" << endl;
	cout << "+====================================================================================================+";
	changeColor(darkWhite);
	cout << endl << endl;
}

void printContent(string content) {
	cout << endl;
	changeColor(blue);cout << "+=======";changeColor(lightBlue); cout << "================"; 
	changeColor(skyblue); cout << "======================================================";changeColor(lightBlue); cout << "================";
	changeColor(blue); cout << "=======+"<<endl;
	changeColor(blue); cout << "||\t\t\t\t\t\t\t\t\t\t\t\t    ||" << endl;
	changeColor(blue); cout << "||";
	changeColor(white); cout << "\t\t\t\t\t\t>>" << content << "<<"; 
	changeColor(blue); cout << "\t\t\t\t\t    ||" << endl;
	changeColor(blue); cout << "||\t\t\t\t\t\t\t\t\t\t\t\t    ||" << endl;
	changeColor(blue); cout << "+======="; changeColor(lightBlue); cout << "================";
	changeColor(skyblue); cout << "======================================================"; changeColor(lightBlue); cout << "================";
	changeColor(blue); cout << "=======+" << endl<<endl;
	changeColor(darkWhite);
}

void printAccontMenu(int type) {
	int color1 = darkWhite, color2 = darkWhite;
	if (type == 1) {
		color1 = lightYellow;
	}
	else if (type == 2) {
		color2 = lightYellow;
	}
	changeColor(color1); cout << "\t\t\t+-------------------------+"; changeColor(color2); cout << "  +-------------------------+" << endl;
	changeColor(color1); cout << "\t\t\t|     1. 입출금 계좌      |"; changeColor(color2); cout << "  |      2. 신용 계좌       |" << endl;
	changeColor(color1); cout << "\t\t\t|     (NormalAccount)     |"; changeColor(color2); cout << "  |   (HighCreditAccount)   |" << endl;
	changeColor(color1); cout << "\t\t\t+-------------------------+"; changeColor(color2); cout << "  +-------------------------+" << endl;
}

void printSuspension(int type) {
	int color1 = darkWhite, color2 = darkWhite;
	if (type == 1) {
		color1 = lightYellow;
	}
	else if (type == 2) {
		color2 = lightYellow;
	}
	changeColor(color1); cout << "\t\t\t\t  +------------------+"; changeColor(color2); cout << "  +------------------+" << endl;
	changeColor(color1); cout << "\t\t\t\t  |     1. 변 경     |"; changeColor(color2); cout << "  |     2. 취 소     |" << endl;
	changeColor(color1); cout << "\t\t\t\t  +------------------+"; changeColor(color2); cout << "  +------------------+ " << endl;
}