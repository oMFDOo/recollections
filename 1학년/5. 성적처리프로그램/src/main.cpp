#include <stdio.h>
#include <string.h>

#pragma warning (disable : 4996)
#define SIZE(value) (sizeof(value) / sizeof(value[0]))

int main( ) {
	FILE* reader = NULL;
	FILE* writer = NULL;

	reader = fopen("score.txt", "r");
	writer = fopen("score_result.txt", "w");

	if (reader == NULL || writer == NULL) {
		printf("파일 열기 실패\n");
		return 0;
	}

	printf("파일 열기 성공\n");

	double scoreList[5] = { 0 };
	
	for (int i = 0; i < 6; i++) {
		char name[10] = { 0 };
		fscanf(reader, "%s", name);
		fprintf(writer, "%s\t", name);
	}
	fprintf(writer, "평균\n");

	int cnt;
	for (cnt = 0; 1; cnt++) {
		char name[10] = { 0 };
		fscanf(reader, "%s", name);

		if (feof(reader)) {
			break;
		}

		fprintf(writer, "%s\t", name);
		
		double sum = 0;
		for (int i = 0; i < SIZE(scoreList); i++) {
			int score;
			fscanf(reader, "%d", &score);
			fprintf(writer, "%d\t", score);

			scoreList[i] += score;
			sum += score;
		}
		sum /= SIZE(scoreList);

		fprintf(writer, "%.2lf\n", sum);
	}

	double sum = 0;
	fprintf(writer, "평균\t");
	for (int i = 0; i < SIZE(scoreList); i++) {
		double avg = scoreList[i] / cnt;
		fprintf(writer, "%.2lf\t", avg);
		sum += avg;
	}
	fprintf(writer, "%.2lf", sum / SIZE(scoreList));


	fclose(writer);
	fclose(reader);
}