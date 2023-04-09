/**
 * File Name: NormalAccount.h
 *
 * Description:
 * NormalAccount의 클래스 내용 정의
 **/
#pragma once
#include "Account.h"

// 통장 유형2 :  추가 이자 있는 거 (high) - A등급 (기본 이자 + A 이자), B등급 (기본 이자 + B 이자), C등급 (기본 이자 + C이자)
class NormalAccount : public Account {
private:
	double addInterestRate;
public:
	NormalAccount();
	NormalAccount(const NormalAccount& ref);
	NormalAccount(int ID, int money, char* name);
	void Deposit(int money);
	void ShowAccInfo() const;
};

