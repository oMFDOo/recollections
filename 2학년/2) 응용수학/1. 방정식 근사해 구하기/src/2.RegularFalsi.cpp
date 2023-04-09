#include <iostream>
#include <cmath>
using namespace std;

double calFX(double x);
double result(double& a, double& b);
void printGrid();

int main() {
	double a = 0.0;
	double b = 5.0;	// x0
	double c = (a + b) / 2.0;
	int test = 1000;

	printGrid();
	cout << "\t5xe^x = 1�� �ٻ��ظ� ������������ �̿��� ���غ���.\n";
	cout << "\t(a : " << a << "\tb : " << b << ")\n\n";
	printGrid();

	double check = a;
	for (int i = 0; ; i++) {
		c = result(a, b);
		printf("\tx %d = %.25lf\n", i + 1, c);

		if ((i + 1) % 5 == 0) cout << endl;

		// �������� ������ ���� ���� ��� ����
		if (c == check) {
			test = i; cout << "\n"; break;
		}
		check = c;
	}

	printGrid();
	cout << "\t" << test << "���� ������ �ٻ��ش� " << b << " �Դϴ�.\n\n";
	printGrid();
}

double result(double& a, double& b) {
	double c = (double)a - calFX(a)*(b-a)/(calFX(b)-calFX(a));
	if (calFX(c) < 0) { a = c; }
	else { b = c; }
	return c;
}

double calFX(double x) {
	// f(x) = 5x(e^x) - 1
	double result = (double)(5.0 * x * exp(x)) - 1.0;
	return result;
}

void printGrid() {
	cout << "===========================================================\n\n";
}