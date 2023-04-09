/**
 * File Name:  main.cpp
 *
 * Description: 은행 시뮬레이션 메인 프로그램
 **/
#include <iostream>
#include "Account.h"
#include "AccountHandler.h"
#include "DesignSet.h"

using namespace std;	

enum SelectMenu{ MAKE = 1, DEPOSIT, WITHDRAW, TRANSFER,INQUIRE, HISTORY,SUSPENSION, EXIT };

int main(void)
{
	string input;
	AccountHandler manager;
	int choice;

	system("mode con cols=105 lines=50");
	
	while (1)
	{          
		cin.clear();
		manager.ShowMenu();
		cout << "\t\t\t\t\t\t- 선택: "; changeColor(lightGreen);
		cin >> input;  changeColor(darkWhite);
		choice = atoi(input.c_str());
		cout << endl;

		switch (choice)
		{
		case MAKE:
			system("cls");
			manager.MakeAccount();
			break;
		case DEPOSIT:
			system("cls");
			manager.DepositMoney();
			break;
		case WITHDRAW:
			system("cls");
			manager.WithdrawMoney();
			break;
		case TRANSFER:
			system("cls");
			manager.TransferMoney();
			break;
		case INQUIRE:
			system("cls");
			manager.ShowAllAccInfo();
			system("cls");
			break;
		case HISTORY:
			system("cls");
			manager.ShowTransactHistory();
			system("cls");
			break;
		case SUSPENSION:
			system("cls");
			manager.AccountSuspension();
			break;
		case EXIT:
			return 0;
		default:
			system("cls");
			changeColor(red);
			cout << "경고";
			changeColor(darkWhite);
			cout << " : 올바른 업무 번호를 선택해주세요.";
		}
	}

	return 0;
}