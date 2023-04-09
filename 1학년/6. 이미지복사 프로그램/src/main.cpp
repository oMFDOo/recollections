#include <stdio.h>

int main() {

	FILE *src_file, *dst_file;

	// 데이터 저장
	char buffer[1024];
	// 읽은 데이터 카운트
	int r_count;


	src_file = fopen("chacha.bmp", "rb");
	dst_file = fopen("copy.jpg", "wb");

	// 둘 중 하나의 파일라도 불러와지지 않았을 경우 프로그램을 종료함
	if (src_file == NULL || dst_file == NULL) {	

		fprintf(stderr, "파일 열기 오류 \n");
		return 1;
	}

	// 블럭 수 카운트 용
	int cntBlock = 1;


	while ((r_count = fread(buffer, 1, sizeof(buffer), src_file)) > 0) {

		int w_count;

		// 홀수인 경우(count 시작이 1이기 때문)에 버퍼를 비워줌
		if (cntBlock % 2 == 0) {
			for (int i = 0; i < r_count; i++) {
				buffer[i] = 0;
			}
		}

		// 버퍼에 담긴 내용을 1 만큼 r_count까지 dst_file 파일에 써넣음
		w_count = fwrite(buffer, 1, r_count, dst_file);

		// 성공적으로 사용된 데이터 값이 리턴 되는데, 그 값이 음수인 경우의 오류 처리
		if (w_count < 0) {
			fprintf(stderr, "파일 쓰기 오류 \n");
			return 1;
		}

		// 입력값보다 출력값이 적은 경우의 오류처리
		if (w_count < r_count) {
			fprintf(stderr, "미디어 쓰기 오류 \n");
			return 1;
		}
		cntBlock++;
	}

	// 성공 시 출력 메시지
	printf("출력 블럭 수 : %d\n", cntBlock);
	printf("copy.jpg로 이미지 파일이 복사됨 \n");

	// 메모리 누수 방지용
	fclose(src_file);
	fclose(dst_file);

	return 0;
}