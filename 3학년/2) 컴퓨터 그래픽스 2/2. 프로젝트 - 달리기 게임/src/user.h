#pragma once
#include <time.h>
#include <string>
using namespace std;

class User {
public:
    User() {
        life = 10;
        coin = 0;
        name = "user";
        gameStart = clock();
    };
    int setLife(int point);
    int setCoin(int point);
    string setName(string name);
    string getName();
    clock_t getStartTime();
private:
    int life;
    int coin;
    std::string name;
    clock_t gameStart;
};