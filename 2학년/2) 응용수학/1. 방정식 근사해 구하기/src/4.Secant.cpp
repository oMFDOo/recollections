#include <iostream>
#include <cmath>
using namespace std;

double calFX(double x);
double result(double x0, double x1);
void printGrid();

int main() {
	double saveX = 5.0;	// x0
	double x1 = 4.0;
	int test = 100;

	printGrid();
	cout << "\t5xe^x = 1�� �ٻ��ظ� �Ҽ����� �̿��� ���غ���.\n";
	cout << "\t(x1 : " << x1 << " x0 : " << saveX << ")\n\n";
	printGrid();

	double check = x1;
	for (int i = 0; i < test; i++) {
		x1 = result(x1, saveX);
		printf("\tx %d = %.20lf\n", i+1, x1);

		if ((i + 1) % 5 == 0) cout << endl;

		// �������� ������ ���� ���� ��� ����
		if (check == x1) {
			test = i; cout << "\n"; break;
		}
		saveX = check;
		check = x1;
	}

	printGrid();
	cout << "\t" << test << "���� ������ �ٻ��ش� " << saveX << " �Դϴ�.\n\n";
	printGrid();
}

double result(double x0, double x1) {	// Xn-1 , Xn
	// Xn+1 = Xn - f(Xn)*(Xn-Xn-1 / f(Xn) - f(Xn-1))
	double xn = (double)x1 - (calFX(x1) * (x1 - x0) / (calFX(x1) - calFX(x0)));
	return xn;
}

double calFX(double x) {
	// f(x) = 5x(e^x) - 1
	double result = (double)(5.0 * x * exp(x)) - 1.0;
	return result;
}

void printGrid() {
	cout << "===========================================================\n\n";
}