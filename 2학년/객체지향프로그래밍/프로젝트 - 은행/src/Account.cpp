/** 
 * File Name: Account.cpp
 *
 * Description:
 * Account 객체를 구성하기 위한 멤버 함수 정의 파일
 **/

#include <iostream>
#include <conio.h>
#include <cstring>
#include <queue>
#include <stack>
#include <string>
#include <iomanip>
#include "Account.h"
#include "HighCreditAccount.h"
#include "DealList.h"
#include "DesignSet.h"

using namespace std;

Account::Account() {
	this->accID = 0;
	this->wrongCnt = 0;
	this->balance = 0;
	this->cusName = 0;
	this->interestRate = 0.01;
	this->activation = true;
	this->pass = "1111";
}

Account::Account(int ID, int money, char* name) 
	: accID(ID), balance(money), interestRate(0.01)
{
	this->activation = true;
	this->wrongCnt = 0;
	this->pass = InputPw();
	AddDealList(money, money, "계좌개설", "-");
	cusName = new char[strlen(name) + 1];

	strcpy_s(cusName, (strlen(name) + 1), name);

	system("cls");
	changeColor(lightGreen); cout << "알림"; changeColor(darkWhite);
	cout << " : 계좌 개설 완료";
}

Account::Account(const Account& ref)
	: accID(ref.accID), balance(ref.balance), interestRate(ref.interestRate)
{
	pass = ref.pass;
	cusName = new char[strlen(ref.cusName) + 1];
	strcpy_s(cusName, (strlen(ref.cusName) + 1), ref.cusName);
}

/**
* Function Name: GetAccID
* Description: 계좌번호를 반환.
* @param: void
* @return: accID(int)
*
**/
int Account::GetAccID() const { return accID; }

/**
* Function Name: Deposit
* Description: 입금.
* @param: int
* @return: void
*
**/
void Account::Deposit(int money)
{

	int interest = (int)(money * interestRate);	// 기본 이자
	balance += interest;
	if(interest) AddDealList(balance, interest, "예금이자", "-");
	
	string msg;
	cout << "\t\t\t\t\t입금 메시지 : "; changeColor(lightGreen);
	cin >> msg; changeColor(darkWhite);

	system("cls");
	balance += money;
	if (money) AddDealList(balance, money, "현금 입금", msg);
	
}
/**
* Function Name: NointerestRateDeposit
* Description: 이체 시 받는 계좌 잔액 증가.
* @param: int
* @return: void
*
**/
void Account::NointerestRateDeposit(int money){
	balance += money;
}

/**
* Function Name: Withdraw
* Description: 출금
*	출금 성공시 잔액 반환
*	실패시 오류 코드(음수) 반환
*	ERR_LACK(-1) : 잔액 부족 
* @param: int 출금액
* @return: int 잔액
*
**/
int Account::Withdraw(int money)
{
	if (balance < money)
		return ERR_LACK;

	string msg;
	cout << "\t\t\t\t\t출금 메시지 : ";
	cin >> msg;

	balance -= money;
	if (money) AddDealList(balance, -money, "현금 출금", msg);
	return balance;
}
/**
* Function Name: ShowAccInfo
* Description: 계좌 정보 출력.
* @param: void
* @return: void
*
**/
void Account::ShowAccInfo() const
{
	cout << " " << left << setw(15)
		<< accID << left << setw(15)
		<< cusName << left << setw(15) 
		<< balance << left << setw(15);
}

/**
* Function Name: PrintDealList
* Description: 최근 거래 내역 출력.
* @param: void
* @return: void
*
**/
void Account::PrintDealList() const {
	queue<DealList*> copy = dealList;
	stack<DealList*> sortRecent;
	
	while (copy.size())
	{
		sortRecent.push(copy.front());
		copy.pop();
	}

	while(sortRecent.size()){
		cout << *(sortRecent.top());
		sortRecent.pop();
	}
}

/**
* Function Name: AddDealList
* Description: 최근 거래 내역 추가.
* @param: int balance, int money, int year, int month, int date, string addressID, string message
* @return: void
*
**/
void Account::AddDealList(int balance, int money, string name, string message) {
	if (dealList.size() == DEAL_LIST_MAX) {
		delete dealList.front();
		dealList.pop();
	}
	
	dealList.push(new DealList(balance, money, name, message));
}

Account::~Account()
{
	delete[]cusName;
}

/**
* Function Name: Transfer
* Description: 이체
* @param: int money, Account accAccount
* @return: int
*
**/
int Account::Transfer(int money, Account& accAccount) {//받는 계좌
	int fee;
	string msg;

	if (this->balance >= SET_A) fee = 100;
	else if (this->balance < SET_A && this->balance >= SET_B) fee = 300;
	else if (this->balance < SET_B && this->balance > SET_C) fee = 500;
	else fee = 700;

	if (this->balance >= fee + money) {
		cout << "\t\t\t\t\t송금 메시지 : "; changeColor(lightGreen);
		cin >> msg; changeColor(darkWhite);

		balance -= money;
		this->AddDealList(this->getBalance(), -money, this->cusName, msg);
		balance -= fee;
		this->AddDealList(this->getBalance(), -fee, "송금수수료", "-");
		
		accAccount.NointerestRateDeposit(money);
		accAccount.AddDealList(accAccount.getBalance(), money, accAccount.cusName, msg);
		return money;
	}
	else {
		system("cls");
		changeColor(lightRed); cout << "경고"; changeColor(darkWhite);
		cout << " : 잔액이 부족합니다.";
		return ERR_LACK;
	}	
}

/**
* Function Name: getbalance
* Description: 잔액 조회
* @param: balance
* @return: int
*
**/
int Account::getBalance(){
	return this->balance;
}

/**
* Function Name: GetStatus
* Description: 계좌 활성화 여부 확인
* @param: void
* @return: bool
*
**/
bool Account::GetStatus() {
	return this->activation;
}

/**
* Function Name: ToggleStatus
* Description: 계좌 활성화
* @param: void
* @return: bool
*
**/
bool Account::ToggleStatus() {
	return this->activation = this->activation ? false : true;
}

/**
* Function Name: GetPW
* Description: 비밀번호 조회
* @param: void
* @return: string
*
**/
string Account::GetPW() {
	return this->pass;
}

/**
* Function Name: SetPW
* Description: 비밀번호 변경
* @param: string;
* @return: void
*
**/
void Account::SetPW(string PW) {
	this->pass = PW;
}

/**
* Function Name: InputPw
* Description: 비밀번호 입력
* @param: void
* @return: string
*
**/
string Account::InputPw() {
	fflush(stdin);
	string pass;

	cout << "\t\t\t\t\t비밀번호 입력: ____\b\b\b\b";
	for (int i = 0; i < 4; i++)
	{
		changeColor(lightGreen);
		pass += _getch();
		cout << "*";
		changeColor(darkWhite);
	}
	fflush(stdin);
	cout << endl;
	return pass;
}

/**
* Function Name: addWorngPW
* Description: 비밀번호 틀린 횟수 증가 && 횟수 초과시 계좌 정지
* @param: bool(false - 초기화, true - 증가)
* @return: int(비밀번호 틀릿 횟수)
*
* Author: Jeong MinGyu
**/
int Account::ChageWorngPW(bool mode) {
	if (mode) {
		++(this->wrongCnt);
		//TODO 아래 3회 횟수 고정해둔거 기호 상수로 빼주세요.
		if (this->wrongCnt >= 3 && this->GetStatus()) {
			this->ToggleStatus();
		}
		return this->wrongCnt;
	}
	return this->wrongCnt = 0;
}