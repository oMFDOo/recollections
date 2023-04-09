#include "user.h"
#include <string.h>
using namespace std;

int User::setLife(int point) {
    this->life += point;
    return this->life;
}

int User::setCoin(int point) {
    this->coin += point;
    return this->coin;
}

string User::setName(string name) {
    this->name = name;
    return this->name;
}

string User::getName() {
    return this->name;
}

clock_t User::getStartTime() {
    return this->gameStart;
}