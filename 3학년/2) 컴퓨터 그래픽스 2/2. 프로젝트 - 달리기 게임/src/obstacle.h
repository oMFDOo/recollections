#pragma once
struct Pos {
	int allObj;						// ��ü ������Ʈ ��
	int objNum;						// ���� ������Ʈ ��ȣ
	double x, y, z;					// ��ġ
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
