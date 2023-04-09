/**
 * File Name: HighCreditAccount.cpp
 *
 * Description:
 * HighCreditAccount 객체를 구성하기 위한 멤버 함수 정의 파일
 **/
#include <iostream>
#include <iomanip>
#include <string>
#include "HighCreditAccount.h"
#include "Account.h"
#include "DesignSet.h"

using namespace std;

double HighCreditAccount::interestRate[4] = { 0.07, 0.05, 0.03, 0 };

HighCreditAccount::HighCreditAccount() :Account(0, 0, NULL) {
	this->accID = 0;
	this->balance = 0;
	this->cusName = 0;
	this->grade = 0;
	this->addInterestRate = 0;
};

HighCreditAccount::HighCreditAccount(int ID, int money, char* name) :Account(ID, money, name) {
	if (this->balance >= SET_A) { this->grade = 1; this->addInterestRate = interestRate[this->grade - 1]; }
	else if (this->balance >= SET_B) { this->grade = 2; this->addInterestRate = interestRate[this->grade - 1]; }
	else if (this->balance >= SET_C) { this->grade = 3; this->addInterestRate = interestRate[this->grade - 1]; }
	else { this->grade = 4; this->addInterestRate = interestRate[this->grade - 1]; }
}

/**
* Function Name: SetGrade / GetGrade
* Description: 계좌등급 설정 및 반환
* @param: void / void
* @return: void / int
*
**/
void HighCreditAccount::SetGrade() {
	if (this->balance >= SET_A) {
		this->grade = GRADE_A;
		this->addInterestRate = interestRate[this->grade - 1];
	}
	else if (this->balance >= SET_B) {
		this->grade = GRADE_B;
		this->addInterestRate = interestRate[this->grade - 1];
	}
	else if (this->balance >= SET_C) {
		this->grade = GRADE_C;
		this->addInterestRate = interestRate[this->grade - 1];
	}
	else {
		this->grade = GRADE_D; this->addInterestRate = interestRate[this->grade - 1];
	}
}

int HighCreditAccount::GetGrade() {
	return this->grade;
}

/**
* Function Name: Deposit
* Description: 입금
* @param: int money
* @return: void
*
**/
void HighCreditAccount::Deposit(int money) {
	Account::Deposit(money); //기본 이자
	int interest = (int)(money * addInterestRate);
	balance += interest; //등급별 이자
	if (interest) AddDealList(balance, interest, "우대이자", "-");
	SetGrade();
}


/**
* Function Name: ShowAccInfo
* Description: info 출력
* @param: void
* @return: void
*
**/
void HighCreditAccount::ShowAccInfo() const {
	Account::ShowAccInfo();
	cout << "HighCredit" << left << setw(15);
	string gradeString;

	switch (grade)
	{
	case GRADE_A:
		gradeString = "A등급"; break;
	case GRADE_B: 
		gradeString = "B등급"; break;
	case GRADE_C:
		gradeString = "C등급"; break;
	case GRADE_D:
		gradeString = "등급없음"; break;
	default:
		break;
	}

	cout << gradeString << left << setw(15);
	cout << (Account::interestRate + addInterestRate) << left << setw(15);
	if (activation) { changeColor(lightBlue); cout << "계좌 활성화" << endl; }
	else { changeColor(lightRed); cout << "계좌 정지" << endl; }

	changeColor(darkWhite);
}

/**
* Function Name: Transfer
* Description: 송금 후 등급 설정
* @param: void
* @return: int
*
**/
int HighCreditAccount::Transfer(int money, Account& accAccount) {
	Account::Transfer(money, accAccount);
	this->SetGrade();
	return money;
}

/**
* Function Name: Withdraw
* Description: 출금 후 등급 설정
* @param: int money
* @return: int
*
**/
int HighCreditAccount::Withdraw(int money) {
	int result = Account::Withdraw(money);
	SetGrade();
	return result;
}

/**
* Function Name: NointerestRateDeposit
* Description: 이자 없는 입금 후 등급 설정
* @param: int money
* @return: void
*
**/
void HighCreditAccount::NointerestRateDeposit(int money) {
	Account::NointerestRateDeposit(money);
	this->SetGrade();
}