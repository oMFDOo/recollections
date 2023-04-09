#include <iostream>
#include <cmath>
using namespace std;

double calFX(double x);
double calFPX(double x);
double result(double x);
void printGrid();

int main() {
	double saveX = 5.0;
	int test = 100;

	printGrid();
	cout << "\t5xe^x = 1�� �ٻ��ظ� ���Ϲ���� �̿��� ���غ���.\n";
	cout << "\t(�ʱⰪ : " << saveX << ")\n\n";
	printGrid();
	
	double check = saveX;	
	for (int i = 0; i < test && calFPX(saveX) != 0; i++) {
		saveX = result(saveX);
		printf("\tx %d = %.25lf\n", i + 1, saveX);
		
		if ((i + 1) % 5 == 0) cout << endl;

		// �������� ������ ���� ���� ��� ����
		if (check == saveX) {
			test = i; cout << "\n"; break;
		}
		check = saveX;
	}

	printGrid();
	cout << "\t" << test << "���� ������ �ٻ��ش� " << saveX << " �Դϴ�.\n\n";
	printGrid();
}

double result(double x) {
	// xn = xn-1 - (f(xn-1) / f'(xn-1))
	double xn = (double)x - (double)(calFX(x) / calFPX(x));
	return xn;
}

double calFX(double x) {
	// f(x) = 5x(e^x) - 1
	double result = (double)(5.0 * x * exp(x)) - 1.0;
	return result;
}

double calFPX(double x) {
	// f'(x) = 5(e^x) + 5x(e^x)
	double result = (double)(5.0 * exp(x)) + (double)(5.0 * x * exp(x));
	return result;
}

void printGrid() {
	cout << "===========================================================\n\n";
}