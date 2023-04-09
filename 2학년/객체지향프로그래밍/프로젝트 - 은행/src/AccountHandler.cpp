/**
 * File Name: AccountHandler.cpp
 *
 * Description:
 * AccountHandler 클래스 정의 파일
 **/

#include <iostream>
#include "AccountHandler.h"
#include "HighCreditAccount.h"
#include "NormalAccount.h"
#include "DesignSet.h"
#include <iomanip>

using namespace std;
/**
* Function Name: ShowMenu
* Description: 메인 메뉴를 출력한다.
* @param: void
* @return: void
*
**/
void AccountHandler::ShowMenu(void) const
{
	printLogo();
	cout << endl;
	cout << "\t\t    반갑습니다. 국민의 최소한의 이득을 위한 은행 Min Bank입니다." << endl;
	cout << "\t\t\t\t 진행할 "; changeColor(yellow);  cout << "업무의 번호"; changeColor(darkWhite); cout << "를 입력해주세요.\n" << endl;
	cout << "\t+-------------------+  +------------------+  +------------------+  +------------------+  " << endl;
	cout << "\t|   1. 계좌개설     |  |     2. 입 금     |  |     3. 출 금     |  |     4. 송 금     |  " << endl;
	cout << "\t+-------------------+  +------------------+  +------------------+  +------------------+  " << endl;
	cout << endl;
	cout << "\t+-------------------+  +------------------+  +------------------+  +------------------+" << endl;
	cout << "\t| 5. 전체 계좌 출력 |  |   6. 계좌 이력   |  |   7. 계좌 정지   |  |     8. 종 료     |" << endl;
	cout << "\t+-------------------+  +------------------+  +------------------+  +------------------+" << endl;
	cout << endl;
}

/**
* Function Name: MakeAccount
* Description: 계좌 개설.
* @param: void
* @return: void
*
**/
void AccountHandler::MakeAccount(void)
{
	string input;
	int id;
	int type;
	char name[NAME_LEN];
	int balance;

	string content = "계좌개설";
	while (1) {
		printContent(content);
		printAccontMenu(0);
		cout << "\n\t\t\t\t\t계좌 유형 선택 : "; cin >> input; cout << endl;
		type = atoi(input.c_str());
		system("cls");
		if (type <= 0 || type > 2) continue;
		break;
	}
rewrite:
	printContent(content);
	printAccontMenu(type);
	changeColor(darkWhite);
	cout << "\n";
	cout << "\t\t\t\t\t계좌 유형 선택 : "; changeColor(lightGreen); cout << type << endl; changeColor(darkWhite);

	cout << "\t\t\t\t\t계좌ID: "; changeColor(lightGreen); cin >> input;  changeColor(darkWhite);
	id = atoi(input.c_str());
	
	if (id < 0) {
		system("cls"); changeColor(lightRed);
		cout << "경고"; changeColor(darkWhite); 
		cout << " : 계좌 번호를 음수로 사용할 수 없습니다.";
		goto rewrite;
	}
	cout << "\t\t\t\t\t이  름: "; changeColor(lightGreen); cin >> name; changeColor(darkWhite);
	cout << "\t\t\t\t\t입금액: "; changeColor(lightGreen); cin >> input; changeColor(darkWhite);
	balance = atoi(input.c_str()); 
	if (balance < 0) {
		system("cls"); changeColor(lightRed);
		cout << "경고"; changeColor(darkWhite);
		cout << " : 초기 잔액을 음수로 사용할 수 없습니다.";
		goto rewrite;
	}
	cout << endl;

	for (int i = 0; i < accNum; i++)
	{
		if (accArr[i]->GetAccID() == id) {
			system("cls"); changeColor(lightRed);
			cout << "경고"; changeColor(darkWhite);
			cout << " : 동일 계좌ID가 이미 존재합니다.";
			goto rewrite;
		}
	}

	if (type == 1) {
		accArr[accNum++] = new NormalAccount(id, balance, name);
	}
	else if (type == 2) {
		accArr[accNum++] = new HighCreditAccount(id, balance, name);
	}
}

/**
* Function Name: DepositMoney
* Description: 입금.
* @param: void
* @return: void
*
**/
void AccountHandler::DepositMoney(void)
{
	string input;
	int money;
	int id;
	string content = "입 금";
	while (1)
	{
		printContent(content);
		cout << "\t\t\t\t\t계좌ID: "; changeColor(lightGreen); cin >> input; changeColor(darkWhite);
		id = atoi(input.c_str());
		if (id <= 0) {
			system("cls"); changeColor(lightRed);
			cout << "경고"; changeColor(darkWhite);
			cout << " : 올바르지 않은 입력.";

			continue;
		}

		cout << "\t\t\t\t\t입금액: "; changeColor(lightGreen); cin >> input; changeColor(darkWhite);
		money = atoi(input.c_str());

		if (money <= 0) {
			system("cls"); changeColor(lightRed);
			cout << "경고"; changeColor(darkWhite);
			cout << " : 올바르지 않은 입력.";
			
			continue;
		}
		break;
	}
	

	for (int i = 0; i < accNum; i++)
	{
		if(!accArr[i]->GetStatus()){
			system("cls");
			changeColor(lightRed); cout << "경고"; changeColor(darkWhite);
			cout << " : 정지된 계좌입니다.";
			return;
		}
		if (accArr[i]->GetAccID() == id)
		{
			accArr[i]->Deposit(money);
			system("cls");
			changeColor(lightGreen); cout << "알림"; changeColor(darkWhite);
			cout << " : 입금완료";
			return;
		}
	}
	system("cls");
	changeColor(lightRed); cout << "경고"; changeColor(darkWhite);
	cout << " : 유효하지 않은 ID 입니다.";
}

/**
* Function Name: WithdrawMoney
* Description: 출금.
* @param: void
* @return: void
*
**/
void AccountHandler::WithdrawMoney(void)
{
	string input;
	int money;
	int id;

	string content = "출 금";
	while (1)
	{
		printContent(content);
		cout << "\t\t\t\t\t계좌ID: "; changeColor(lightGreen); cin >> input; changeColor(darkWhite);
		id = atoi(input.c_str());
		if (id <= 0) {
			system("cls"); changeColor(lightRed);
			cout << "경고"; changeColor(darkWhite);
			cout << " : 올바르지 않은 입력.";

			continue;
		}
		cout << "\t\t\t\t\t출금액: "; changeColor(lightGreen); cin >> input; changeColor(darkWhite);
		money = atoi(input.c_str());
		if (money <= 0) {
			system("cls"); changeColor(lightRed);
			cout << "경고"; changeColor(darkWhite);
			cout << " : 올바르지 않은 입력.";

			continue;
		}
		break;
	}
	

	for (int i = 0; i < accNum; i++)
	{
		if (accArr[i]->GetAccID() == id)
		{
			if(!accArr[i]->GetStatus()){
				system("cls");
				changeColor(lightRed); cout << "경고"; changeColor(darkWhite);
				cout << " : 정지된 계좌입니다.";
				return;
			}
			//TODO 비번 틀린거 횟수 조절하는 함수 기호 상수로 바꿔주세요
			if (accArr[i]->GetPW() != accArr[i]->InputPw()) {
				system("cls");
				changeColor(lightRed); cout << "경고"; changeColor(darkWhite);

				cout << " : 비밀번호가 다릅니다.";
				cout << "("; changeColor(lightRed);
				cout << accArr[i]->ChageWorngPW(1); changeColor(darkWhite);
				cout << "회 틀림)";
				return;
			}
			else accArr[i]->ChageWorngPW(0);
			if (accArr[i]->Withdraw(money) < 0)
			{
				system("cls");
				changeColor(lightRed); cout << "경고"; changeColor(darkWhite);
				cout << " : 잔액이 부족합니다." << endl << endl;
				return;
			}
			system("cls");
			changeColor(lightGreen); cout << "알림"; changeColor(darkWhite);
			cout << " : 출금완료";
			return;
		}
	}
	system("cls");
	changeColor(lightRed); cout << "경고"; changeColor(darkWhite);
	cout << " : 유효하지 않은 ID 입니다.";
}

/**
* Function Name:TransferMoney
* Description: 송금
* @param: void
* @return: void
*
**/
void AccountHandler::TransferMoney(void) {
	string input;
	int money;
	int id, accid;

 	string content = "송 금";
fstInput:
	while (1) {
		printContent(content); 
		cout << "\t\t\t\t\t내 계좌ID: "; changeColor(lightGreen); cin >> input; changeColor(darkWhite);
		id = atoi(input.c_str());
		if (id <= 0) {
			system("cls"); changeColor(lightRed);
			cout << "경고"; changeColor(darkWhite);
			cout << " : 올바르지 않은 입력.";
			continue;
		}
		break;
	}

	while(1) { 
		cout << "\t\t\t\t\t받을 계좌ID: "; changeColor(lightGreen); cin >> input;  changeColor(darkWhite);
		accid = atoi(input.c_str());
		if (accid <= 0) {
			system("cls"); changeColor(lightRed);
			cout << "경고"; changeColor(darkWhite);
			cout << " : 올바르지 않은 입력.";
			goto fstInput;
		}
		
		if (id == accid)
		{
			system("cls");
			changeColor(lightRed); cout << "\t\t\t\t경고"; changeColor(darkWhite);
			cout << " : 같은ID로 송금할 수 없습니다.\n" << endl;
			goto fstInput;
		}
		break;
	}
	while (1) {
		cout << "\t\t\t\t\t송금액: "; changeColor(lightGreen); cin >> input; changeColor(darkWhite);
		money = atoi(input.c_str());
		if (money <= 0) {
			system("cls"); changeColor(lightRed);
			cout << "경고"; changeColor(darkWhite);
			cout << " : 올바르지 않은 입력.";
			goto fstInput;
		}
		break;
	}
	for (int i = 0; i < accNum; i++)
	{
		if (accArr[i]->GetAccID() == id)
		{
			//TODO 비번 틀린거 횟수 조절하는 함수 기호 상수로 바꿔주세요
			if (accArr[i]->GetPW() != accArr[i]->InputPw()) {
				system("cls");
				changeColor(lightRed); cout << "경고"; changeColor(darkWhite);

				cout << " : 비밀번호가 다릅니다.";
				cout << "("; changeColor(lightRed);
				cout << accArr[i]->ChageWorngPW(1); changeColor(darkWhite);
				cout << "회 틀림)";
				return;
			}
			else accArr[i]->ChageWorngPW(0);
			if(!accArr[i]->GetStatus()){
				system("cls");
				changeColor(lightRed); cout << "경고"; changeColor(darkWhite);
				cout << " : 정지된 계좌입니다.";
				return;
			}
			for (int j = 0; j < accNum; j++)
			{
				if (accArr[j]->GetAccID() == accid)
				{
					if(!accArr[j]->GetStatus()){
						system("cls");
						changeColor(lightRed); cout << "경고"; changeColor(darkWhite);
						cout << " : 이체 상대가 정지된 계좌입니다.";
						return;
					}
							
					if (accArr[i]->Transfer(money, *accArr[j]) > 0) { 
						system("cls");
						changeColor(lightGreen); cout << "알림"; changeColor(darkWhite);
						cout << " : 송금완료";
						return;
					}
					system("cls");
					changeColor(lightRed); cout << "경고"; changeColor(darkWhite);
					cout << " : 잔액이 부족합니다.";
					return;
				}
			}
			system("cls");
			changeColor(lightRed); cout << "경고"; changeColor(darkWhite);
			cout << " : 유효하지 않은 ID 입니다.";
			return;
		}
	}
	system("cls");
	changeColor(lightRed); cout << "경고"; changeColor(darkWhite);
	cout << " : 유효하지 않은 ID 입니다.";
}

/**
* Function Name: ShowAllAccInfo
* Description: 전체 계좌 출력.
* @param: void
* @return: void
*
**/
void AccountHandler::ShowAllAccInfo(void) const
{
	printContent("전체 계좌");
	cout << " " << left << setw(15)
		<< "계좌ID" << left << setw(15)
		<< "이  름" << left << setw(15)
		<< "잔  액" << left << setw(15)
		<< "계좌 정보" << left << setw(15)
		<< "등  급" << left << setw(15)
		<< "이  자" << left << setw(15)
		<< "계좌 활성" << left << setw(15);
	cout << endl;
	cout << " ---------------------------------------------------------------------------------------------------" << endl;
	for (int i = 0; i < accNum; i++)
	{
		accArr[i]->ShowAccInfo();
		cout << endl;
		//accArr[i]->PrintDealList();
	}
	cout << "\n\n >> 엔터키 입력시 메인 화면으로 돌아갑니다....";
	cin.ignore(50, '\n');
	cin.get();
	cin.clear();
}

void AccountHandler::ShowTransactHistory(void) const
{
	printContent("거래 이력");
	for (int i = 0; i < accNum; i++)
	{
		changeColor(lightGreen);
		cout << accArr[i]->GetAccID(); changeColor(darkWhite);
		cout << " 님의 거래내역 입니다.\n\n";
		
		cout << " " << left << setw(25)
			<< "일  시" << left << setw(15)
			<< "거래 내용" << left << setw(25)
			<< "메시지" << left << setw(15)
			<< "변동 금액" << left << setw(15)
			<< "잔  액";
		cout << endl;

		cout << " ===================================================================================================" << endl;
		accArr[i]->PrintDealList();
		cout << endl;
		cout << " ===================================================================================================" << endl << endl << endl;
	}
	cout << "\n\n >> 엔터키 입력시 메인 화면으로 돌아갑니다....";
	cin.ignore(50, '\n');
	cin.get();
	cin.clear(); 
}

/**
* Function Name: AccountSuspension
* Description: 계좌 정지 설정.
* @param: void
* @return: void
*
**/
void AccountHandler::AccountSuspension(void) {
	int id, answer = 0;
	string content = "계좌 정지";
	printContent(content);
	cout << "\t\t\t\t\t\t 계좌ID: "; changeColor(lightGreen); cin >> id; changeColor(darkWhite);
	cout << endl;

	for (int i = 0; i < accNum; i++)
	{
		if (accArr[i]->GetAccID() == id)
		{
			do{
				cout << "\t\t\t\t    계좌 활성화 여부를 변경하시겠습니까?\n\n"<< endl;
				cout << "\t\t\t\t\t현재 계좌 상태 : ";
				if (accArr[i]->GetStatus()) {
					changeColor(lightBlue); cout << "계좌 활성화"; changeColor(darkWhite);
				}
				else {
					changeColor(lightRed); cout << "계좌 정지"; changeColor(darkWhite);
				}
				cout << endl << endl;
				printSuspension(0);


				cout << "\n\n\t\t\t\t\t\t- 선택: "; changeColor(lightGreen);
				cin >> answer;  changeColor(darkWhite);

				switch(answer){
				case 1:
					if(!accArr[i]->GetStatus()) {
					//TODO 비번 틀린거 횟수 조절하는 함수 기호 상수로 바꿔주세요
					if (accArr[i]->GetPW() != accArr[i]->InputPw()) {
						system("cls");
						changeColor(lightRed); cout << "경고"; changeColor(darkWhite);

						cout << " : 비밀번호가 다릅니다.";
						cout << "("; changeColor(lightRed);
						cout << accArr[i]->ChageWorngPW(1); changeColor(darkWhite);
						cout << "회 틀림)";
						return;
					}
					else accArr[i]->ChageWorngPW(0);
					}
					accArr[i]->ToggleStatus();
					system("cls");
				case 2:
					system("cls");
					return;
				default:
					system("cls");
					break;
				} 
			} while (1);
			
			return;
		}
	}
	system("cls");
	changeColor(lightRed); cout << "경고"; changeColor(darkWhite);
	cout << " : 유효하지 않은 ID 입니다.";
}

AccountHandler::AccountHandler() : accNum(0)
{  }

AccountHandler::~AccountHandler()
{
	for (int i = 0; i < accNum; i++)
		delete accArr[i];
}