#include "bookData.h"

#pragma once
#define SHORTLINE 23
#define LONGLINE 80

using namespace std;

void printDividingLine(int);
void printBookInfo(int);
void printMode(int);
void printMode(int);
void printAllList();
void exit();

// 검색 형식 출력
void printSerchType() {
	system("cls");
	printDividingLine(SHORTLINE + 7);
	cout << "\t원하시는 검색 형식의 번호를 입력해주세요";
	printDividingLine(SHORTLINE + 7);
	cout << "\t\t1. 책 이름으로 검색\n\n";
	cout << "\t\t2. 작가 이름으로 검색\n\n";
}

// 메인 메뉴 출력
// 매개 변수 : 현재 보유 도서 수
void printMode(int book) {
	printDividingLine(SHORTLINE);
	setColor(skyblue, black);
	cout << "\t\t즐겨 찾기 목록\n\n";
	setColor(white, black);
	cout << "\t\t담긴 도서 수 : ";
	setColor(lightYellow, black);
	cout << book;
	setColor(white, black);
	printDividingLine(SHORTLINE);

	cout << "\t\t1) 도서 검색\n\n";
	cout << "\t\t2) 도서 추가\n\n";
	cout << "\t\t3) 도서 삭제\n\n";
	cout << "\t\t4) 모든 도서 보기\n\n\n\n";

	cout << "\t이용할 기능의 ";
	setColor(lightYellow, black);
	cout << "번호"; 
	setColor(white, black);
	cout << "를 입력해주세요.\n\n";
	cout << "\t>> ";

}

// 목록 구분 출력
void printBasic() {
	system("cls");
	printDividingLine(LONGLINE);
	cout << "\t\t도서 목록";
	printDividingLine(LONGLINE);
	setColor(skyblue, black);
	cout << "   도서 번호"
		<< "          도서 이름"
		<< "\t\t\t\t\t\t      저자"
		<< "\t\t  페이지"
		<< "\t\t가격"
		<< "\t\t    출간일" << endl << endl;
	setColor(white, black);
}

// 책 정보 출력
// 매개변수 : 출력할 정보의 인덱스
void printBookInfo(int index) {

	cout.width(7);
	
	cout << "   " << left << setw(15)
		<< index + 1 << left << setw(55)
		<< (LB + index)->name << left << setw(20)
		<< (LB + index)->author << left << setw(20);

	int data;

	data = LB[index].page;
	if (data != 1) {
		cout << data << left << setw(20);
	}
	else {
		cout << "( 미기입 )" << left << setw(20);
	}

	data = LB[index].price;
	if(data != 1) {
		cout << data;
	}
	else {
		cout << "( 미기입 )";
	}

	data= LB[index].publicationDate;
	if (data != 1) {
		cout << data / 10000 << "년 "
			<< (data % 10000) / 100 << "월 "
			<< (data % 100) << "일" << endl;
	}
	else {
		cout << "( 미기입 )" << endl;
	}
	cout << endl;
}

// 구분선 출력
void printDividingLine(int lineLength) {
	setColor(red,black);
	cout << "\n\n";
	while (lineLength--) {
		cout << "♥";
	}
	cout << "\n\n";
	setColor(white, black);
}

// 입력된 모든 리스트 출력
void printAllList() {
	library LB[10];
	for (int i = 0; i < sizeof(presenceOfInfo); i++) {
		if (presenceOfInfo[i]) {
			printBookInfo(i);
		}
	}
}

// 종료
void exit() {
	cout << "\n\n >> 키 입력시 메인 화면으로 돌아갑니다....";
	cin.ignore(50, '\n');
	cin.get();
}