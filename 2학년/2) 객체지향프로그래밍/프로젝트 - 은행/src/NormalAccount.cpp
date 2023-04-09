/**
 * File Name: NormalAccount.cpp
 *
 * Description:
 * NormalAccount 객체를 구성하기 위한 멤버 함수 정의 파일
 **/

#include <iostream>
#include <iomanip>
#include "NormalAccount.h"
#include "Account.h"
#include "DesignSet.h"

using namespace std;

NormalAccount::NormalAccount() :Account(0, 0, NULL) {
	this->addInterestRate = 0.01;
};

NormalAccount::NormalAccount(int ID, int money, char* name) :Account(ID, money, name) {
	this->addInterestRate = 0.01;
}

NormalAccount::NormalAccount(const NormalAccount& ref)
	: Account(ref)
{
	this->cusName = new char[strlen(ref.cusName) + 1];
	strcpy_s(this->cusName, (strlen(ref.cusName) + 1), ref.cusName);
}

/**
* Function Name: Deposit
* Description: 입금
* @param: int money
* @return: void
*
**/
void NormalAccount::Deposit(int money) {
	Account::Deposit(money);
}

/**
* Function Name: ShowAccInfo
* Description: info 출력
* @param: void
* @return: void
*
**/
void NormalAccount::ShowAccInfo() const {
	Account::ShowAccInfo();
	cout << "Normal" << left << setw(15);

	cout << "X" << left << setw(15);
	cout << interestRate + addInterestRate << left << setw(15);
	if (activation) { changeColor(lightBlue); cout << "계좌 활성화" << endl; }
	else { changeColor(lightRed); cout << "계좌 정지" << endl; }

	changeColor(darkWhite);
}
