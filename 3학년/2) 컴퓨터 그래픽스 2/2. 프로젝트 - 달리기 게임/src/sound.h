#pragma once
#include <windows.h>
#pragma comment(lib,"winmm.lib") 
#include <mmsystem.h>
#include <stdlib.h>
#include <time.h>
#include<stdio.h>
#include<Windows.h>
#include<string>
#include <Digitalv.h>
#include <Digitalv.h>

/*
SND_ASYNC // 재생중에도 프로그램이 계속 돌아감
SND_SYNC // 재생이 끝나야 프로그램이 돌아감
SND_FILENAME // 매개변수가 사운드 파일의 이름일 경우
SND_LOOP // 반복재생 (SND_ASYNC와 같이 써야함..)
SND_PURGE // 재생중지
*/

// mic를 이용한 동시 소리 재생
MCI_OPEN_PARMS openBgm;//파일을 로드
MCI_PLAY_PARMS playBgm;//파일을 재생
MCI_OPEN_PARMS openShuffleSound;//파일을 로드
MCI_PLAY_PARMS playShuffleSound;//파일을 재생

#define BGM "./sound/MP_엉뚱한 작당모의.mp3" //BGM 경로 지정
#define BGM1 "./sound/walk1.wav" //BGM 경로 지정
#define BGM2 "./sound/walk2.wav" //BGM 경로 지정
#define BGM3 "./sound/jump.wav" //BGM 경로 지정
#define BGM5 "./sound/getCoin.wav" //BGM 경로 지정
#define BGM6 "./sound/icu.wav" //BGM 경로 지정

int dwID;
void playingBgm() {
	openBgm.lpstrElementName = TEXT(BGM); //파일 오픈
	openBgm.lpstrDeviceType = TEXT("mpegvideo"); //mp3 형식
	mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&openBgm);
	dwID = openBgm.wDeviceID;
	mciSendCommand(dwID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID)&openBgm); //음악 반복 재생
}

void playingBgm2(bool work) {
	openBgm.lpstrElementName = TEXT(BGM1); //파일 오픈
	openBgm.lpstrDeviceType = TEXT("mpegvideo"); //mp3 형식
	mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&openBgm);
	dwID = openBgm.wDeviceID;
	if(work){
		mciSendCommand(dwID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID)&openBgm); //음악 반복 재생
	}
	else mciSendCommand(dwID, MCI_CLOSE, 0, (DWORD)(LPVOID)&openBgm); //음악 반복 재생
}

void playingBgm3(bool work) {
	openBgm.lpstrElementName = TEXT(BGM2); //파일 오픈
	openBgm.lpstrDeviceType = TEXT("mpegvideo"); //mp3 형식
	mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&openBgm);
	dwID = openBgm.wDeviceID;
	if (work) {
		mciSendCommand(dwID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID)&openBgm); //음악 반복 재생
	}
	else mciSendCommand(dwID, MCI_CLOSE, 0, (DWORD)(LPVOID)&openBgm); //음악 반복 재생
}

void playingBgm4(bool work) {
	openBgm.lpstrElementName = TEXT(BGM3); //파일 오픈
	openBgm.lpstrDeviceType = TEXT("mpegvideo"); //mp3 형식
	mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&openBgm);
	dwID = openBgm.wDeviceID;
	if (work) {
		mciSendCommand(dwID, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&openBgm); //음악 반복 재생
	}
	else mciSendCommand(dwID, MCI_CLOSE, 0, (DWORD)(LPVOID)&openBgm); //음악 반복 재생
}


void playingBgm5(bool work) {
	openBgm.lpstrElementName = TEXT(BGM5); //파일 오픈
	openBgm.lpstrDeviceType = TEXT("mpegvideo"); //mp3 형식
	mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&openBgm);
	dwID = openBgm.wDeviceID;
	if (work) {
		mciSendCommand(dwID, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&openBgm); //음악 반복 재생
	}
	else mciSendCommand(dwID, MCI_CLOSE, 0, (DWORD)(LPVOID)&openBgm); //음악 반복 재생
}

void playingBgm6(bool work) {
	openBgm.lpstrElementName = TEXT(BGM5); //파일 오픈
	openBgm.lpstrDeviceType = TEXT("mpegvideo"); //mp3 형식
	mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&openBgm);
	dwID = openBgm.wDeviceID;
	if (work) {
		mciSendCommand(dwID, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&openBgm); //음악 반복 재생
	}
	else mciSendCommand(dwID, MCI_CLOSE, 0, (DWORD)(LPVOID)&openBgm); //음악 반복 재생
}

void playingShuffleSound(std::wstring name) {
	openShuffleSound.lpstrElementName = name.c_str(); //파일 오픈
	openShuffleSound.lpstrDeviceType = TEXT("mpegvideo"); //mp3 형식
	mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&openShuffleSound);
	dwID = openShuffleSound.wDeviceID;
	mciSendCommand(dwID, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&openShuffleSound); //음악을 한 번 재생
	Sleep(4000); //효과음이 재생될 때까지 정지했다가
	mciSendCommand(dwID, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL); //음원 재생 위치를 처음으로 초기화
}


void playSound(int track) {
	//if (track == 1) {
	//	srand(time(NULL));
	//	track = 1 + (rand() % 6);
	//}

	//printf("Track : %d\n", track);

	playingBgm4(false);
	playingBgm5(false);
	playingBgm6(false);

	switch (track) {
		// 게임시작
	case 0:
		playingBgm();
		playingShuffleSound(TEXT("./sound/gameStartNa.wav"));
		break;
		// 차차탈출
	case 1:
		//playingBgm4(false);
		//playingBgm3(false);
		//playingBgm2(true);
		//playingShuffleSound(TEXT("./sound/walk1.wav"));
		break;
	case 2:
		//playingBgm4(false);
		//playingBgm2(false);
		//playingBgm4(false);
		//playingBgm3(true);
		//playingShuffleSound(TEXT("./sound/walk2.wav"));
		break;
	case 3:
		//playingBgm2(false);
		playingBgm4(true);
		break;
	case 4:
		playingBgm5(true);
		break;
	case 5:
		playingBgm6(true);
		break;
	case 6:
		PlaySound(TEXT("./sound/ready.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_NODEFAULT);
		break;
	case 7:
		playingShuffleSound(TEXT("./sound/gameClearNa.wav"));
		break;
	case 8:
		playingShuffleSound(TEXT("./sound/gameOverNa.wav"));
		break;
	}
}
