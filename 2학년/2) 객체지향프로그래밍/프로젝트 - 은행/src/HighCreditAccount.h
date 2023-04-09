/**
 * File Name: HighCreditAccount.h
 *
 * Description:
 * HighCreditAccount 정보를 저장하기 위한 클래스 정의
 **/
#pragma once
#include "Account.h"

// 통장 유형3 : 등급별 이체 수수료 차등 (ex) A - 없음, B - 50%........)
class HighCreditAccount : public Account {
private:
	enum Grade { GRADE_A = 1, GRADE_B, GRADE_C, GRADE_D }; //등급번호
	int grade;
	double addInterestRate;
	static double interestRate[4];
	void SetGrade();

public:
	HighCreditAccount();
	HighCreditAccount(int ID, int money, char* name);
	void Deposit(int money);
	int GetGrade();
	void ShowAccInfo() const;
	int Transfer(int money, Account& accAccount);
	int Withdraw(int money);
	void NointerestRateDeposit(int money);
};
