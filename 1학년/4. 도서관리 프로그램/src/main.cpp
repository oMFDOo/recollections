#include "bookData.h"
#include "searchBook.h"
#include "mode.h"

using namespace std;

#define COMMENT ((int)4294967296+1)
#define endl "\n"

bool pyeonHae;


int main() {
	// 페이지수, 가격, 출간일, 책이름, 작가, 출판사
	// 콘솔 크기 조정
	system("mode con cols=180 lines=40");
	while (COMMENT) {
		setColor(white, black);		// 색상 초기화
		system("cls");				// 화면 초기화
		printMode(checkOverflow());	// 모드 출력

		checkOverflow();			// 정보 입력 확인 bool배열 정돈 및 추가 가능 여부 확인
		int mode = selectMode();	// 사용 모드 선택

		if (mode == 1) {			// 1. 도서 검색
			searchInfo();
			exit();
		}
		else if (mode == 2) {		// 2. 도서 추가
			addBook();
			exit();
		}
		else if (mode == 3) {		// 3. 도서 삭제
			deleteBook();
			exit();
		}
		else if (mode == 4) {		// 4. 도서 전체 출력
			printBasic();
			sortString(checkOverflow());
			printAllList();
			selectsort();
			exit();
		}
	}
}