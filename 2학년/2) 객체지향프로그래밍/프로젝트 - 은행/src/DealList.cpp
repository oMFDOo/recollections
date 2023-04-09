/**
 * File Name: DealList.cpp
 *
 * Description:
 * 계정 정보 저장하는 DealList의 함수 구현
 **/

#include <iostream>
#include <time.h>
#include "DealList.h"
#include <iomanip>

using namespace std;

/**
* Function Name: DealList 생성자
* Description: 생성자
* @param: int balance, int money, int year, int month, int date, string addresseID, string message
* @return: x
*
**/
DealList::DealList(int balance, int money, string addressID, string message) {
    char date[100] = { 0 };
    time_t timer = time(NULL);
    struct tm tm_info;
    localtime_s(&tm_info, &timer);

    this->balance = balance;
    this->money = money;
    strftime(date, sizeof(date), "%Y-%m-%d %H:%M:%S", &tm_info);
    this->timestamp = date;

    this->addressID = addressID;
    this->message = message;
}

DealList::DealList() {
    this->balance = 0;
    this->money = -1;
    this->timestamp = "";

    this->addressID = "";
    this->message = "";
}

/**
* Function Name: setInfo
* Description: 리스트 정보 설정
* @param: int balance, int money, int year, int month, int date, string addresseID, string message
* @return: void
*
**/
void DealList::setInfo(int balance, int money, string timestamp, string addresseID, string message) {
    this->balance = balance;
    this->money = money;
    this->timestamp = timestamp;


    this->addressID = addresseID;
    this->message = message;
}

/**
* Function Name: getInfo
* Description: DealList 정보를 가져옴
* @param: void
* @return: DealList&
*
* Author: Jeong MinGyu
**/
DealList& DealList::getInfo() {
    return *this;
}

/**
* Function Name: operator<< 
* Description: DealList의 << 연산자 중복 (friend)
* @param: ostream&
* @return: ostream& os, const DealList& dl
*
**/
ostream& operator<<(ostream& os, const DealList& dl)
{
    os << " " << left << setw(25)
       << dl.timestamp << left << setw(15) 
       << dl.addressID << left << setw(25)
       << dl.message << left << setw(15)
       << dl.money << left << setw(15)
       << dl.balance << endl;
    return os;
}
