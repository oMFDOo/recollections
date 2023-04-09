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
	cout << "\t5xe^x = 1의 근사해를 뉴턴방식을 이용해 구해보자.\n";
	cout << "\t(초기값 : " << saveX << ")\n\n";
	printGrid();
	
	double check = saveX;	
	for (int i = 0; i < test && calFPX(saveX) != 0; i++) {
		saveX = result(saveX);
		printf("\tx %d = %.25lf\n", i + 1, saveX);
		
		if ((i + 1) % 5 == 0) cout << endl;

		// 이전값과 동일한 값이 나온 경우 종료
		if (check == saveX) {
			test = i; cout << "\n"; break;
		}
		check = saveX;
	}

	printGrid();
	cout << "\t" << test << "번의 연산결과 근사해는 " << saveX << " 입니다.\n\n";
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