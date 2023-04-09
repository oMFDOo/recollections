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
SND_ASYNC // ����߿��� ���α׷��� ��� ���ư�
SND_SYNC // ����� ������ ���α׷��� ���ư�
SND_FILENAME // �Ű������� ���� ������ �̸��� ���
SND_LOOP // �ݺ���� (SND_ASYNC�� ���� �����..)
SND_PURGE // �������
*/

// mic�� �̿��� ���� �Ҹ� ���
MCI_OPEN_PARMS openBgm;//������ �ε�
MCI_PLAY_PARMS playBgm;//������ ���
MCI_OPEN_PARMS openShuffleSound;//������ �ε�
MCI_PLAY_PARMS playShuffleSound;//������ ���

#define BGM "./sound/MP_������ �۴����.mp3" //BGM ��� ����
#define BGM1 "./sound/walk1.wav" //BGM ��� ����
#define BGM2 "./sound/walk2.wav" //BGM ��� ����
#define BGM3 "./sound/jump.wav" //BGM ��� ����
#define BGM5 "./sound/getCoin.wav" //BGM ��� ����
#define BGM6 "./sound/icu.wav" //BGM ��� ����

int dwID;
void playingBgm() {
	openBgm.lpstrElementName = TEXT(BGM); //���� ����
	openBgm.lpstrDeviceType = TEXT("mpegvideo"); //mp3 ����
	mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&openBgm);
	dwID = openBgm.wDeviceID;
	mciSendCommand(dwID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID)&openBgm); //���� �ݺ� ���
}

void playingBgm2(bool work) {
	openBgm.lpstrElementName = TEXT(BGM1); //���� ����
	openBgm.lpstrDeviceType = TEXT("mpegvideo"); //mp3 ����
	mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&openBgm);
	dwID = openBgm.wDeviceID;
	if(work){
		mciSendCommand(dwID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID)&openBgm); //���� �ݺ� ���
	}
	else mciSendCommand(dwID, MCI_CLOSE, 0, (DWORD)(LPVOID)&openBgm); //���� �ݺ� ���
}

void playingBgm3(bool work) {
	openBgm.lpstrElementName = TEXT(BGM2); //���� ����
	openBgm.lpstrDeviceType = TEXT("mpegvideo"); //mp3 ����
	mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&openBgm);
	dwID = openBgm.wDeviceID;
	if (work) {
		mciSendCommand(dwID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID)&openBgm); //���� �ݺ� ���
	}
	else mciSendCommand(dwID, MCI_CLOSE, 0, (DWORD)(LPVOID)&openBgm); //���� �ݺ� ���
}

void playingBgm4(bool work) {
	openBgm.lpstrElementName = TEXT(BGM3); //���� ����
	openBgm.lpstrDeviceType = TEXT("mpegvideo"); //mp3 ����
	mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&openBgm);
	dwID = openBgm.wDeviceID;
	if (work) {
		mciSendCommand(dwID, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&openBgm); //���� �ݺ� ���
	}
	else mciSendCommand(dwID, MCI_CLOSE, 0, (DWORD)(LPVOID)&openBgm); //���� �ݺ� ���
}


void playingBgm5(bool work) {
	openBgm.lpstrElementName = TEXT(BGM5); //���� ����
	openBgm.lpstrDeviceType = TEXT("mpegvideo"); //mp3 ����
	mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&openBgm);
	dwID = openBgm.wDeviceID;
	if (work) {
		mciSendCommand(dwID, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&openBgm); //���� �ݺ� ���
	}
	else mciSendCommand(dwID, MCI_CLOSE, 0, (DWORD)(LPVOID)&openBgm); //���� �ݺ� ���
}

void playingBgm6(bool work) {
	openBgm.lpstrElementName = TEXT(BGM5); //���� ����
	openBgm.lpstrDeviceType = TEXT("mpegvideo"); //mp3 ����
	mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&openBgm);
	dwID = openBgm.wDeviceID;
	if (work) {
		mciSendCommand(dwID, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&openBgm); //���� �ݺ� ���
	}
	else mciSendCommand(dwID, MCI_CLOSE, 0, (DWORD)(LPVOID)&openBgm); //���� �ݺ� ���
}

void playingShuffleSound(std::wstring name) {
	openShuffleSound.lpstrElementName = name.c_str(); //���� ����
	openShuffleSound.lpstrDeviceType = TEXT("mpegvideo"); //mp3 ����
	mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&openShuffleSound);
	dwID = openShuffleSound.wDeviceID;
	mciSendCommand(dwID, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&openShuffleSound); //������ �� �� ���
	Sleep(4000); //ȿ������ ����� ������ �����ߴٰ�
	mciSendCommand(dwID, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL); //���� ��� ��ġ�� ó������ �ʱ�ȭ
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
		// ���ӽ���
	case 0:
		playingBgm();
		playingShuffleSound(TEXT("./sound/gameStartNa.wav"));
		break;
		// ����Ż��
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
