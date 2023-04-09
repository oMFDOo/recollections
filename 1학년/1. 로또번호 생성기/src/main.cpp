#include <stdio.h>
#include <random>
#include <time.h>

int main()  {
	printf("숫자를 출력할 수를 입력해주세요. :");
	
	int turn;
	scanf("%d", &turn);
	
	srand(time(NULL));
	for (int i = 0; i < turn; i++) {
		int cnt = 1;
		int a = 0,
			b = 0,
			c = 0,
			d = 0,
			e = 0,
			f = 0;

		while (cnt <= 6) {
			int temp = rand() % 45 + 1;
			switch (cnt) {
			case 1:
				a = temp;
				cnt++;
				break;
			case 2:
				if (a != temp) {
					b = temp;
					cnt++;
				}
				break;
			case 3:
				if (a != temp) {
					if (b != temp) {
						c = temp;
						cnt++;
					}
				}
				break;
			case 4:
				if (a != temp) {
					if (b != temp) {
						if (c != temp) {
							d = temp;
							cnt++;
						}
					}
				}
				break;
			case 5:
				if (a != temp) {
					if (b != temp) {
						if (c != temp) {
							if (d != temp) {
								e = temp;
								cnt++;
							}
						}
					}
				}
				break;
			case 6:
				if (a != temp) {
					if (b != temp) {
						if (c != temp) {
							if (d != temp) {
								if (e != temp) {
									f = temp;
									cnt++;
								}
							}
						}
					}
				}
				break;
			}
		}
		printf("\n%d번째로 추출 된 숫자는 %d %d %d %d %d %d 입니다.\n",i+1, a, b, c, d, e, f);
	}
}