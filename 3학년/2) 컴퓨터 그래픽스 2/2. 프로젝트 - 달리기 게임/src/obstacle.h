#pragma once
struct Pos {
	int allObj;						// 전체 오브젝트 수
	int objNum;						// 현재 오브젝트 번호
	double x, y, z;					// 위치
	bool visible = true;
};


class Position {
private:

public:
	Pos pos1();
	Pos pos2();
	Pos pos3();
	Pos pos4();
	Pos pos5();
};
