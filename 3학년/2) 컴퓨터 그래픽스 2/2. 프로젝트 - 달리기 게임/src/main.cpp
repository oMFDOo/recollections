#define _CRT_SECURE_NO_WARNINGS  //비쥬얼 스투디오 2015 이상의 버전에서 scanf같은 것을 쓰게 해주는 것

#include "dib.h"
#include "GL/glew.h"
#include "GL/glut.h"
#include "math.h"
#include "Camera.h"
#include "intro.h"
#include "sound.h"
#include "object.h"
#include "obstacle.h"
#include "user.h"
#include <stdio.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// 한 번만 실행
bool loadImg = true;

// 장애물 위치
double obstacleZ[5] = { 0, 1, 2, 3, 4 };
int drawCoinStartIdx = 0, drawCoinEndIdx = 10;
int drawObstacleStartIdx = 0, drawObstacleEndIdx = 10;
int drawLineStartIdx = 0, drawLineEndIdx = 10;
int maxCoin = 0, maxObstacle = 0, maxLine = 0;

// 캐릭터 점프
double jump = 0.0;
clock_t jumpStart, jumpIng;
int isjump = 0;
int jumpTurm = 600;

// 캐릭터 좌우
double goLR = 0;

// 카메라 시점 모드 조정
int cameraLook = 0;

// 텍스처 로드
MyDib boardTexture, objectTexture, enemyTexture;
Sphere sphere;

GLuint	texture[8];			// Storage For One Texture
float xrot, yrot, zrot;
float turnAroundAngle = 0.0;
int shapeRotate = 0;

/* Global variables */
char title[] = "3D Shapes with animation";
GLfloat anglePyramid = 0.0f;  // Rotational angle for pyramid 
GLfloat angleCube = 0.0f;     // Rotational angle for cube 
int refreshMills = 1;        // refresh interval in milliseconds 
double posx = 5.0f, posy = 2.0f, posz = 0;

Camera cam;
float h = 0.25; //점프를 위한 공용 변수
float a = 0.01f;//점프를 위한 공용 변수


float userT = 0; //유저 기본 속도 조절 변수
float userMove = 0; //유저 위치 변수
float userSpeed = 0.0; //유저 유동 속도 조절 변수

float enemyT1 = 0; //적1 기본 속도 조절 변수
float enemy1Speed = 0; //적 1 유동 속도 조절 변수

float enemyT2 = 0; //적2 속도 조절 변수
float enemy2Speed = 0; //적 2 유동 속도 조절 변수

float enemyT3 = 0; //적3 속도 조절 변수
float enemy3Speed = 0; //적 3 유동 속도 조절 변수

float enemyT4 = 0; //적4 속도 조절 변수
float enemy4Speed = 0; //적 4 유동 속도 조절 변수

GLUquadricObj* cyl;	//곡선이 들어간 오브젝트
GLUquadricObj* cylTree;	//곡선이 들어간 오브젝트

GLfloat eyeX = 0, eyeY = 0, eyeZ = 0; //카메라의 시점 변경을 위한 변수
GLfloat initX = 0, initY = 0;   //마우스 클릭 했을때의 초기 위치
GLfloat delta = 0.1;            //마우스 움직일시 시점 변경을 위한 변수
GLfloat zzz = 1;   //카메라 시점 변경을 위한 변수
GLfloat aaa = 0.1; //카메라 시점 변경을 위한 변수

Cylinder tunnel;

//색상
typedef enum Color {
	BLACK_, DARK_BLUE, DARK_GREEN, DARK_SKYBLUE,
	DARK_RED, DARK_VOILET, DAKR_YELLOW, GRAY,
	DARK_GRAY, BLUE_, GREEN_, SKYBLUE, RED_, VIOLET,
	YELLOW, WHITE_,
};

void MyMouseClick(GLint Button, GLint State, GLint X, GLint Y);  //클릭한 점을 기준으로
void MyMouseMove(GLint X, GLint Y); //카메라의 위치를 변환 시킴
void InitLight(); //조명 
void MyIdle(); //아이들
void MyKeyboard(unsigned char KeyPressed, int X, int Y); //키보드
void MyDisplay();
void MySpecial(int key, int x, int y); //특수키 키보드
void MyInit(); //텍스쳐 사용 함수
// 텍스쳐용 추가 함수
int loadGLTextures(int i);
int drawGLScene(int pos, int object);

void enemySet(float a, float r, float g, float b, float pibo, float t, float enemySpeed);
// 사람 만들어주는 함수,   a 위치 조정, rgb,  pibo 피부 색깔 조정, 각 케릭터마다 기본 속도 조절, 유동 속도 조절

void userSet(float a, float r, float g, float b); // 유저용
void enemySetSpeed(); //적들 속도 랜덤하게 부여
void board(); //바닥 판
void tree1(int posL); //나무1
void tree2(int posL); //나무2
void finishLine(int posL);  //피니시 라인 달리기 끝에 줄
void gameOverCheck(); //게임 오버 체크

// 위치 읽어오기
void readPos(char* fileDir);
Pos coinPosition[1000];
Pos obstaclePosition[1000];
Pos linePosition[1000];

bool isCoinVisible(int posD);
bool isObstacleVisible(int posD);
bool isLineVisiable(int posD);
bool checkCoin(int i); // 충돌 처리
bool checkObstacle(int i);
bool checkTreeL(int i);
bool checkTreeR(int i);
bool checkLine(int i);
User user;
bool IsInput = false;
double collisionLight = 0.0;

// 글자출력
void text();
void isGameOver();

struct rankUser {
	string name;
	int time;
	int idx;
};

rankUser rankUserSet[1000];

void reshape(GLsizei width, GLsizei height);
int main(int argc, char** argv)
{
	intro_start();  //헤더파일 intro에 있는 게임 설명 cmd창을 보여주는 함수

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(800, 200);

	glutCreateWindow("OpenGL Sample Drawing");
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();//현재행렬 단위행렬로 초기화
	gluPerspective(20, 1, 0.1, 1000);

	//사용전에 카메라 초기화를 먼저 해줘야 함
	//gluLookAt
	cam.set(0, 40, 9,	//눈의 좌표
		0, 0, 0,	//바라보는 점
		0, 1, 0);	//업벡터 

	InitLight(); //조명 초기화
	MyInit();

	glutDisplayFunc(MyDisplay);
	glutReshapeFunc(reshape);
	glutIdleFunc(MyIdle);
	glutMouseFunc(MyMouseClick);
	glutMotionFunc(MyMouseMove);
	glutKeyboardFunc(MyKeyboard);
	glutSpecialFunc(MySpecial);
	glutMainLoop();

	return 0;
}

/* Handler for window re-size event. Called back when the window first appears and
whenever the window is re-sized with its new width and height */
void reshape(GLsizei width, GLsizei height) {  // GLsizei for non-negative integer
	// Compute aspect ratio of the new window
	if (height == 0) height = 1;                // To prevent divide by 0
	GLfloat aspect = (GLfloat)width / (GLfloat)height;

	// Set the viewport to cover the new window
	glViewport(0, 0, width, height);

	// Set the aspect ratio of the clipping volume to match the viewport
	glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
	glLoadIdentity();             // Reset
	// Enable perspective projection with fovy, aspect, zNear and zFar
	gluPerspective(45.0f, aspect, 0.1f, 100.0f);
}


int loadGLTextures(int i)         // Load Bitmaps And Convert To Textures
{
	//const char imgName[] = "/.";
	///* load an image file directly as a new OpenGL texture */
	//texture[i] = SOIL_load_OGL_texture
	//(imgName, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	//if (texture[i] == 0)
	//	return false;
	//
	//// Typical Texture Generation Using ;Data From The Bitmap
	//glBindTexture(GL_TEXTURE_2D, texture[i]);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//glTexImage2D(GL_TEXTURE_2D, 0, 3, objectTexture.GetWidth(), objectTexture.GetHeight(), 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, objectTexture.m_lpImage);
	// && 텍스쳐 그림에 사용     이 세줄이 핵심!  -> 텍스쳐 사용법,  나머지는 좌표만 맞추면 됨
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, objectTexture.GetWidth(), objectTexture.GetHeight(), GL_BGR_EXT, GL_UNSIGNED_BYTE, objectTexture.m_lpImage); //mip map을 만들어줌

	return true;
}

int drawGLScene(int posD, int object)			// Here's Where We Do All The Drawing
{
	// 구 위치 선정
	glClearDepth(1.0f);                   // Set background depth to farthest
	glEnable(GL_TEXTURE_2D);
	glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
	glShadeModel(GL_SMOOTH);   // Enable smooth shading
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections

	glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix

	loadGLTextures(0);

	if (object == 0) {
		if (coinPosition[posD].visible == true) {
			// 텍스쳐 불러오기
			glTranslatef(coinPosition[posD].x, coinPosition[posD].y, coinPosition[posD].z);
			glRotatef(shapeRotate, 0.0, -1.0, 0.0);

			//glBindTexture(GL_TEXTURE_2D, texture[1]);
			glScalef(0.4, 0.4, 0.2);
			sphere.Draw();
			glEnd();
		}
	}
	else if (object == 1) {
		glTexImage2D(GL_TEXTURE_2D, 0, 3, enemyTexture.GetWidth(), enemyTexture.GetHeight(), 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, enemyTexture.m_lpImage);
		// && 텍스쳐 그림에 사용     이 세줄이 핵심!  -> 텍스쳐 사용법,  나머지는 좌표만 맞추면 됨
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, enemyTexture.GetWidth(), enemyTexture.GetHeight(), GL_BGR_EXT, GL_UNSIGNED_BYTE, enemyTexture.m_lpImage); //mip map을 만들어줌

		// 구 위치 선정
		glTranslatef(obstaclePosition[posD].x, obstaclePosition[posD].y, obstaclePosition[posD].z);
		glScalef(0.5, 0.4, 0.5);
		sphere.Draw();
	}

	shapeRotate += 1;
	glutSwapBuffers();  // Swap the front and back frame buffers (double buffering)

	glEnd();
	return TRUE;
}


/*
 * MyDisplay
 */
bool startCameraMove = true;
double cameraMoveX = 16.0, cameraMoveY = 8.0;
void MyDisplay()
{
	if (IsInput == true) {
		if (startCameraMove) {
			if (cameraMoveY - 0.02 <= 0.0) {
				startCameraMove = false;
				playSound(6);
			}
			cam.set(0 + eyeX + goLR + cameraMoveX, 2 + eyeY + cameraMoveY, 7 + eyeZ - 0.1 + userMove,	//눈의 좌표
				0 + goLR, 2, -0.1 + userMove,	//바라보는 점
				0, 1, 0);	//업벡터 
			cameraMoveY -= 0.1;
			cameraMoveX -= 0.2;
		}
		float mat_diffuse1[4] = { 0.1, 0.4, 0.6, 1 }; // 추가  사람 색깔
		float mat_diffuse2[4] = { 1.0, 1.0 ,0.7, 1 }; // 추가  옷 색깔


		// 점프 하기
		jumpIng = clock();
		// 올라가기
		if (isjump && jumpIng - jumpStart < jumpTurm) {
			// 진행시간 기준으로 높이 가속을 주었다.
			// +1 하여 0을 나누는 일을 없앰
			jump += (double)(jumpTurm + 1 - (jumpIng - jumpStart)) / 2000.0;
		}
		// 내려가기
		if (isjump && jumpIng - jumpStart >= jumpTurm && jumpIng - jumpStart < (jumpTurm * 2)) {
			// 올라간 시간은 빼줌
			jump += -(double)(jumpIng - jumpStart - (jumpTurm + 1)) / 2000.0;
			if (jump - 0.002 > 0) {
			}
		}
		// 점프종료
		if (isjump && jumpIng - jumpStart >= (jumpTurm * 2)) {
			isjump = 0;
			jump = 0.0;
		}


		cyl = gluNewQuadric();
		gluQuadricDrawStyle(cyl, GLU_FILL);	//면으로 그려줘

		cylTree = gluNewQuadric();
		gluQuadricDrawStyle(cylTree, GLU_FILL);	//면으로 그려줘

		glEnable(GL_DEPTH_TEST); // Enable depth testing for z-culling
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);


		glDisable(GL_LIGHTING);	//조명 껏다가
		glPushMatrix();
		text();
		glPopMatrix();
		glEnable(GL_LIGHTING); // 다시 킴


		for (int i = drawCoinStartIdx; i < drawCoinEndIdx; i++) {
			// 도형도형 : 구
			if (coinPosition[i].visible == false) {
				continue;
			}
			else if (checkCoin(i) == false) {
				playSound(4);
				continue;
			}
			glPushMatrix();
			if (isCoinVisible(i) == true) {
				drawGLScene(i, 0);
			}
			glPopMatrix();

		}


		for (int i = drawObstacleStartIdx; i < drawObstacleEndIdx; i++) {
			if (obstaclePosition[i].visible == false) {
				continue;
			}
			else if (checkObstacle(i) == false) {
				playSound(5);
				continue;
			}
			glPushMatrix();
			if (isObstacleVisible(i) == true) {
				drawGLScene(i, 1);
			}
			glPopMatrix();

		}

		////finish line

		for (int i = drawLineStartIdx; i < drawLineEndIdx; i++) {
			if (isLineVisiable(i)) {
				glPushMatrix();
				finishLine(i);
				glPopMatrix();
				//나무 1
				glPushMatrix();
				tree1(i);
				glPopMatrix();
				//나무 2
				glPushMatrix();
				tree2(i);
				glPopMatrix();
			}
		}



		//바닥	
		//glDisable(GL_LIGHTING);	//조명 껏다가
		glPushMatrix();
		board();
		glPopMatrix();
		//glEnable(GL_LIGHTING); // 다시 킴



		//user
		userSet(0, 0.1, 0.4, 0.6);

		glFlush();
		glutPostRedisplay();      //윈도우를 다시 그리도록 요청
	}
	else {
		textcolor(RED_, BLACK_);
		cout << "\t _      _  _    _    _         _    _  _  _          _       _____                _                 \n";
		cout << "\t| |    (_)| |  | |  | |       | |  | |(_)| |        | |     |  ___|              | |                \n";
		cout << "\t| |     _ | |_ | |_ | |  ___  | |  | | _ | |_   ___ | |__   | |__   _   _  _ __  | |__    ___   ___ \n";
		cout << "\t| |    | || __|| __|| | / _ \\ | |/\\| || || __| / __|| '_ \\  |  __| | | | || '_ \\ | '_ \\  / _ \\ / _ \\ \n";
		cout << "\t| |____| || |_ | |_ | ||  __/ \\  /\\  /| || |_ | (__ | | | | | |___ | |_| || | | || | | ||  __/|  __/\\ \n";
		cout << "\t\\_____/|_| \\__| \\__||_| \\___|  \\/  \\/ |_| \\__| \\___||_| |_| \\____/  \\__,_||_| |_||_| |_| \\___| \\___|\n\n";

		string temp;
		textcolor(GREEN_, BLACK_);
		cout << "\t\t\t\t\t==> 닉네임을 입력하세요 : ";
		textcolor(DARK_VOILET, SKYBLUE);
		cin >> temp;
		IsInput = true;
		user.setName(temp);
		textcolor(WHITE_, BLACK_);
		cout << "\t\t\t====================================================================\n\n";
		textcolor(DARK_SKYBLUE, BLACK_);
		cout << "\t\t\t\t\t\t게임 조작법!\n\n";
		textcolor(WHITE_, BLACK_);
		cout << "\t\t\t====================================================================\n";
		cout << "\t\t\t\t\t\t↑ ↓ : 캐릭터 속도 증가\n";
		cout << "\t\t\t\t\t\t← → : 캐릭터 좌우 이동\n";
		cout << "\t\t\t\t\t\t<space bar> : 점프\n";
		cout << "\t\t\t\t\t\tW, S : 카메라 위/아래 시점변환\n";
		cout << "\t\t\t\t\t\t1, 2, 3 : 카메라 뒤/앞/옆 시점변환\n";
		cout << "\t\t\t\t\t\t마우스 클릭 : 시점 자유변환\n\n\n";

		cout << "\t\t\t====================================================================\n\n";
		cout << "\t\t\t\t\t\t게임 안내!\n\n";
		cout << "\t\t\t====================================================================\n";
		textcolor(DARK_SKYBLUE, BLACK_);
		cout << "\t\t\t\t\t - 은희가 코인 30개를 모으면 성공!\n";
		textcolor(WHITE_, BLACK_);
		cout << "\t\t\t\t\t - Life 10개를 모두 소진하면 실패ㅠㅠ!\n";

	}
}

bool isCoinVisible(int posD) {
	bool flag = coinPosition[posD].z < userMove + 5.0;
	if (flag == false) {
		if (maxCoin - 10 > drawCoinEndIdx) {
			drawCoinEndIdx++;
			drawCoinStartIdx++;
		}
	}
	return flag;
}

bool isObstacleVisible(int posD) {
	bool flag = obstaclePosition[posD].z < userMove + 5.0;
	if (flag == false) {
		if (maxObstacle - 10 > drawObstacleEndIdx) {
			drawObstacleEndIdx++;
			drawObstacleStartIdx++;
		}
	}
	return flag;
}

bool isLineVisiable(int posD) {
	bool flag = linePosition[posD].z < userMove + 5.0;
	if (flag == false) {
		if (maxLine - 10 > drawLineEndIdx) {
			drawLineEndIdx++;
			drawLineStartIdx++;
		}
	}
	return flag;
}

bool checkCoin(int i) {
	if (coinPosition[i].x - 1.0 <= goLR && coinPosition[i].x + 1.0 >= goLR &&
		coinPosition[i].y - 1.0 <= jump && coinPosition[i].y + 1.0 >= jump &&
		coinPosition[i].z + 0.2 >= -0.1 + userMove && coinPosition[i].z - 0.2 <= -0.1 + userMove) {
		coinPosition[i].visible = false;
		if (coinPosition[i].objNum != -1) {
			user.setCoin(1);
			PlaySound(TEXT("./sound/getCoin.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_NODEFAULT);
			coinPosition[i].objNum = -1;
		}
		return false;
	}
	return true;
}

bool checkObstacle(int i) {
	if (obstaclePosition[i].x - 0.8 <= goLR && obstaclePosition[i].x + 0.8 >= goLR &&
		obstaclePosition[i].y - 0.8 <= jump && obstaclePosition[i].y + 0.8 >= jump &&
		obstaclePosition[i].z + 0.2>= -0.1 + userMove && obstaclePosition[i].z - 0.2 <= -0.1 + userMove) {
		obstaclePosition[i].visible = false;
		if (user.setLife(0) > 0 && obstaclePosition[i].objNum != -1) {
			user.setLife(-1);
			PlaySound(TEXT("./sound/icu.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_NODEFAULT);
			// 조명 설정
			collisionLight = -0.8;
			obstaclePosition[i].objNum = -1;
		}
		return false;
	}
	return true;
}


bool checkTreeL(int i) {
	if (-3 + 0.3 > goLR && -3 - 0.3 < goLR && linePosition[i].z >= -0.1 + userMove) {
		if (user.setLife(0) > 0 && linePosition[i].objNum != -1) {
			linePosition[i].objNum = -1;
			user.setLife(-1);
			PlaySound(TEXT("./sound/icu.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_NODEFAULT);
		}
		return false;
	}
	return true;
}

bool checkTreeR(int i) {
	if (3 + 0.3 > goLR && 3 - 0.3 < goLR && linePosition[i].z >= -0.1 + userMove) {
		if (user.setLife(0) > 0 && linePosition[i].objNum != -1) {
			linePosition[i].objNum = -1;
			user.setLife(-1);
			PlaySound(TEXT("./sound/icu.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_NODEFAULT);
		}
		return false;
	}
	return true;
}

bool checkLine(int i) {
	if (
		linePosition[i].x >= jump && linePosition[i].x <= jump + 1.0 &&
		linePosition[i].y >= jump && linePosition[i].y <= jump + 1.0 &&
		linePosition[i].z - 0.2 <= 0.1 + userMove &&
		linePosition[i].z + 0.2 >= 0.1 + userMove
		) {
		if (user.setLife(0) > 0 && linePosition[i].objNum != -1) {
			linePosition[i].objNum = -1;
			user.setLife(-1);
			PlaySound(TEXT("./sound/icu.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_NODEFAULT);
		}
		linePosition[i].visible = false;
		return false;
	}
	return true;
}


/*
 * game configure
 */

int clearTimeBox[1000] = { 0 };
string clearUserBox[1000];


void gameOverCheck() {
	if (user.setCoin(0) == 30) {
		playSound(7);
		clock_t endTime = clock();
		endTime -= user.getStartTime();
		ofstream writeFile("./gameData/rank.txt", ios::app); //쓸 목적의 파일 선언
		string tempUserName = user.getName();
		tempUserName += " " + to_string(endTime) + " ms";
		//파일이 열렸는지 확인
		if (writeFile.is_open()) {
			writeFile << tempUserName << endl;
		}
		writeFile.close();

		string dummy;
		ifstream ifs;        // 입력스트림 ifs 객체 생성
		ifs.open("./gameData/rank.txt");
		int userCount = 0;
		int start = 0;
		int turn = 0;
		while (!ifs.eof()) {
			string inputLine;
			getline(ifs, inputLine);
			for (int i = 0; i < inputLine.length(); i++) {
				if (inputLine[i] == ' ' && turn%2 == 0) {
					rankUserSet[userCount].name = inputLine.substr(start, i);
					start = i+1;
					turn++;
				}
				else if (inputLine[i] == ' ' && turn%2 == 1) {
					rankUserSet[userCount].time = stoi(inputLine.substr(start, i));
					turn++;
					start = 0;
					break;
				}
			}
			userCount++;
		}

		string userName = user.getName();
		int userRankResult = 0;

		for (int i = 0; i < userCount; i++) { 
			for (int j = 0; j < userCount-1 - i; j++) { 
				if (rankUserSet[j].time > rankUserSet[j + 1].time) {
					string name = rankUserSet[j].name;
					if (userName == name) userRankResult = j + 1;
					int time = rankUserSet[j].time, idx = rankUserSet[j].idx;
					rankUserSet[j].name = rankUserSet[j+1].name;
					rankUserSet[j].time = rankUserSet[j+1].time;
					rankUserSet[j].idx  = rankUserSet[j+1].idx;
					rankUserSet[j + 1].name = name;
					rankUserSet[j + 1].time = time;
					rankUserSet[j + 1].idx = idx;
				} 
			} 
		}
		system("cls");
		cout << "\n\n\n";
		cout << "--------------------------------------------------------\n\n";
		textcolor(DAKR_YELLOW, BLACK_);
		cout << "\t\t" << userName << "님은 " << userRankResult << "등 입니다!\n";
		textcolor(WHITE_, BLACK_);
		cout << "\t\t" << "총 클리어 시간 : " << to_string(endTime) << "\n\n";
		cout << "--------------------------------------------------------\n\n";

		for (int i = 1; i < userCount; i++) {
			if(i == userRankResult) textcolor(BLACK_, WHITE_);
			cout << '\t' << i << ". \t" << rankUserSet[i].name << "\t\t" << rankUserSet[i].time << " ms" << endl;
			if (i == userRankResult) textcolor(WHITE_, BLACK_);
		}
		exit(1);
	}
	if (user.setLife(0) == -100) {
		playSound(8);
		exit(1);
	}
}
void enemySetSpeed()
{
	//적들의 속도를 랜덤하게 부여함
	srand((int)time(NULL));

	int k = (rand() % 15) + 1;
	float random = (rand() % 10) + 1;
	enemy1Speed = random * 0.00015 * k;

	k = (rand() % 20) + 1;
	random = (rand() % 10) + 1;
	enemy2Speed = random * 0.00015 * k;

	k = (rand() % 25) + 1;
	random = (rand() % 10) + 1;
	enemy3Speed = random * 0.00015 * k;

	k = (rand() % 10) + 1;
	random = (rand() % 10) + 1;
	enemy4Speed = random * 0.00015 * k;
}
void tree1(int posL) {
	float mat_diffuse1[4] = { 0.9, 0.8, 0.9, 1 }; // 나뭇잎
	float mat_diffuse2[4] = { 0.64, 0.29, 0.64, 1 }; // 나무 잎

	if (checkTreeL(posL) == true) {
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse1); // 추가
		glTranslatef(-3, -0.5, linePosition[posL].z);
		glRotatef(270, 1, 0, 0);
		gluCylinder(cylTree, 0.3, 0.3, 2.0, 20, 1);

		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse2); // 추가
		glTranslatef(0.0, 0, 2.0);
		gluCylinder(cylTree, 0.6, 0, 1.5, 20, 1);
	}
}
void tree2(int posL) {
	float mat_diffuse1[4] = { 0.9, 0.8, 0.9, 1 }; // 나뭇잎
	float mat_diffuse2[4] = { 0.64, 0.29, 0.64, 1 }; // 나무 잎

	if (checkTreeR(posL) == true) {
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse1); // 추가
		glTranslatef(3, -0.5, linePosition[posL].z);
		glRotatef(270, 1, 0, 0);
		gluCylinder(cylTree, 0.3, 0.3, 2.0, 20, 1);

		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse2); // 추가
		glTranslatef(0.0, 0, 2.0);
		gluCylinder(cylTree, 0.6, 0, 1.5, 20, 1);
	}
}
void finishLine(int posL) {
	glDisable(GL_TEXTURE_2D);

	if (linePosition[posL].visible == true) {
		if (checkLine(posL) == true) {
			glBegin(GL_POLYGON);
			glColor3f(0.8, 0.8, 0.8);
			glVertex3f(-3, linePosition[posL].x, linePosition[posL].z);
			glVertex3f(3, linePosition[posL].x, linePosition[posL].z);
			glVertex3f(3, linePosition[posL].y, linePosition[posL].z);
			glVertex3f(-3, linePosition[posL].y, linePosition[posL].z);
			glEnable(GL_TEXTURE_2D);
		}
	}
	glEnd();
}


void board()
{

	glTexImage2D(GL_TEXTURE_2D, 0, 3, boardTexture.GetWidth(), boardTexture.GetHeight(), 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, boardTexture.m_lpImage);
	// && 텍스쳐 그림에 사용     이 세줄이 핵심!  -> 텍스쳐 사용법,  나머지는 좌표만 맞추면 됨
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, boardTexture.GetWidth(), boardTexture.GetHeight(), GL_BGR_EXT, GL_UNSIGNED_BYTE, boardTexture.m_lpImage); //mip map을 만들어줌

	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	glTranslatef(0, 0,userMove);
	glRotatef(135, 1, 0, 0);
	glScalef(30, 80000, 30);
	tunnel.Draw();
	glPopMatrix();
	glBegin(GL_QUADS);
	//텍스쳐는 0에서 1까지
	//앞에것이 텍스쳐 좌표,  오른쪽이 gl의 물체 좌표
	//텍스쳐의 각각의 정점을 대응해서 물체에 붙임
	//1보다 큰 값을 줄 시 gl이 픽셀을 그냥 쭉 연장시킴
	//glColor3f(0.0, 0.0, 0.4);
	glTexCoord2f(0.0, 0.0); glVertex3f(-4.0, -0.6, -800.0);	// 좌하단
	glTexCoord2f(0.0, 1.0); glVertex3f(4.0, -0.6, -800.0);	// 우하단
	glTexCoord2f(25.0, 1.0); glVertex3f(4.0, -0.6, 10.0);	// 우상단
	glTexCoord2f(25.0, 0.0); glVertex3f(-4.0, -0.6, 10.0);	// 좌상단

	//glTexCoord2f(0.0, 0.0); glVertex3f(-10.0, -10.0, -17.8);	// 좌하단
	//glTexCoord2f(0.0, 1.0); glVertex3f(10.0, -10.0, -17.8);	// 우하단
	//glTexCoord2f(1.0, 1.0); glVertex3f(10.0, 10.0, -17.8);	// 우상단
	//glTexCoord2f(1.0, 0.0); glVertex3f(-10.0, 10.0, -17.8);	// 좌상단
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void userSet(float a, float r, float g, float b)
{
	float mat_diffuse1[4] = { r, g, b, 1 }; // 옷 색깔
	float mat_diffuse2[4] = { 1.0, 0.9, 0.9, 1 }; // 사람 색깔은 고정

	float material_diffuse1[] = { 0.3, 0.1, 0.4, 1.0 };
	float material_diffuse2[] = { 0.3, 0.1, 0.4, 1.0 };


	//게임 오버 체크!!
	char temp[5];
	strcpy(temp, "User");
	gameOverCheck();

	glPushMatrix();
	glTranslatef(a + goLR, (sin(userT * 0.1) + 1) / 20 + jump, -0.1 + userMove);
	// 1. 몸통
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse1); // 추가
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	gluCylinder(cyl, 0.27, 0.12, 0.6, 20, 1);
	glRotatef(90, 1, 0, 0);

	// 1. 머리
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse2); // 추가
	glTranslatef(0, 0.68, 0);
	glutSolidSphere(0.3, 20, 20);

	// 모자 챙
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse1);
	glTranslatef(0.0, 0.10, 0.12);
	glRotatef(-50, 1.0f, 0.0f, 0.0f);
	gluCylinder(cyl, 0.45, 0.01, 0.3, 20, 1);

	// 모자 뿔
	glPushMatrix();
	glutSolidCone(0.3, 0.7, 100, 100);
	glPopMatrix();
	glPopMatrix();

	//glutSolidSphere(0.17, 20, 20);
	glPopMatrix();
	// 1. 왼팔
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse1);
	glTranslatef(-0.2, 0.35, 0);	//공의 반지름이 0.05이고 실린더의 반지름이 0.1이므로 0.15만큼 움직여야 중심으로 감, 그림 생각하기!
	glutSolidSphere(0.05, 20, 20);
	glRotatef(sin(userT * 0.1) * 90 + 90, 1, 0, 0);
	gluCylinder(cyl, 0.05, 0.05, 0.2, 20, 1);

	//2. 팔꿈치부터 안에 팔
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse2);
	//glPushMatrix();
	glTranslatef(0.0, 0.0, 0.2);	//공의 반지름이 0.05이고 실린더의 반지름이 0.1이므로 0.15만큼 움직여야 중심으로 감, 그림 생각하기!
	glutSolidSphere(0.05, 20, 20);
	glRotatef(sin(userT * 0.1) * 45 + 45, 1, 0, 0);
	gluCylinder(cyl, 0.05, 0.05, 0.2, 20, 1);

	//3. 팔! 팔은 어차피 붙어있으므로 푸시 팝 필요 없음
	glTranslatef(0.0, 0.0, 0.2);	//공의 반지름이 0.05이고 실린더의 반지름이 0.1이므로 0.15만큼 움직여야 중심으로 감, 그림 생각하기!
	glutSolidSphere(0.08, 20, 20);
	//glPopMatrix();
	glPopMatrix();


	// 1. 오른팔
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse1);
	glTranslatef(0.2, 0.35, 0);	//공의 반지름이 0.05이고 실린더의 반지름이 0.1이므로 0.15만큼 움직여야 중심으로 감, 그림 생각하기!
	glutSolidSphere(0.05, 20, 20);
	glRotatef(sin(-userT * 0.1) * 90 + 90, 1, 0, 0);
	gluCylinder(cyl, 0.05, 0.05, 0.2, 20, 1);

	//2. 팔꿈치부터 안에 팔
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse2);
	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.2);	//공의 반지름이 0.05이고 실린더의 반지름이 0.1이므로 0.15만큼 움직여야 중심으로 감, 그림 생각하기!
	glutSolidSphere(0.05, 20, 20);
	glRotatef(sin(-userT * 0.1) * 45 + 45, 1, 0, 0);
	gluCylinder(cyl, 0.05, 0.05, 0.2, 20, 1);

	//3. 팔! 팔은 어차피 붙어있으므로 푸시 팝 필요 없음
	glTranslatef(0.0, 0.0, 0.2);	//공의 반지름이 0.05이고 실린더의 반지름이 0.1이므로 0.15만큼 움직여야 중심으로 감, 그림 생각하기!
	glutSolidSphere(0.08, 20, 20);
	glPopMatrix();
	glPopMatrix();

	// 1. 다리, 엉덩이
	// 왼쪽 다리
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse2);
	glTranslatef(-0.07, 0.1, 0);	//공의 반지름이 0.05이고 실린더의 반지름이 0.1이므로 0.15만큼 움직여야 중심으로 감, 그림 생각하기!
	glutSolidSphere(0.08, 20, 20);
	glRotatef(sin(-userT * 0.1) * 40 + 110, 0.5, 0, 0);
	gluCylinder(cyl, 0.08, 0.06, 0.3, 20, 1);
	//왼쪽 발바닥
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse1);
	glTranslatef(0, -0.03, 0.35);
	glScalef(1.2, 2.0, 1);
	glutSolidCube(0.1);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	// 오른쪽 다리
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse2);
	glTranslatef(0.07, 0.1, 0);	//공의 반지름이 0.05이고 실린더의 반지름이 0.1이므로 0.15만큼 움직여야 중심으로 감, 그림 생각하기!
	glutSolidSphere(0.08, 20, 20);
	glRotatef(sin(userT * 0.1) * 40 + 110, 0.5, 0, 0);
	gluCylinder(cyl, 0.08, 0.08, 0.3, 20, 1);
	//오른쪽 발바닥
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse1);
	glTranslatef(0, -0.03, 0.35);
	glScalef(1.2, 2.0, 1);
	glutSolidCube(0.1);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();//몸통 종료
	glPopMatrix();	//사람 종료
}

/*
 * glutFunk
 */
void MyIdle()
{
	//각 케릭터의 속도 조절
	enemyT1 += 0.012f; //기본 속도
	enemyT1 += enemy1Speed; //추가 된 속도

	enemyT2 += 0.013f; //기본 속도
	enemyT2 += enemy2Speed; //추가 된 속도

	enemyT3 += 0.011f; //기본 속도
	enemyT3 += enemy3Speed; //추가 된 속도

	enemyT4 += 0.014f; //기본 속도
	enemyT4 += enemy4Speed; //추가 된 속도

	userT += 0.01f; //유저의 기본 속도
	userT += userSpeed; //추가 된 속도


	//게임의 재미를 위해 유저의 속도가 자동으로 어느정도 떨어지게 만듬
	userMove -= userSpeed * 0.1;
	//속도가 0보다 작을 수 없음
	if (userSpeed - 0.00002 > 0)
	{
		userSpeed -= 0.00002;
	}


	//뛰어가는 모습을 자연스럽게 하기 위해서 뛰어가는 모습중 어느 정도 위아래로 움직이게 만듬
	if (h <= 0.25)
		a = +0.001f;
	if (h >= 0.75)
	{
		a = -0.001f;
	}
	h = h + a;
	//카메라도 어느정도 빠르게 자동으로 앞으로 가게 만듦
	//aaa -= 0.002;
	//cam.set(-25 + eyeX, 5 + eyeY, 0 + eyeZ + aaa,	//눈의 좌표
	//	10, 0, 0 + aaa,	//바라보는 점
	//	0, 1, 0);	//업벡터 

	switch (cameraLook) {
	case 0:
		// 달리는 뒷모습
		cam.set(0 + eyeX + goLR, 2 + eyeY, 7 + eyeZ - 0.1 + userMove,	//눈의 좌표
			0 + goLR, 2, -0.1 + userMove,	//바라보는 점
			0, 1, 0);	//업벡터 
		break;
	case 1:
		// 달리는 앞모습
		cam.set(0 + eyeX + goLR, 0 + eyeY, -10 - 0.1 + userMove,	//눈의 좌표
			0 + goLR, 2, -0.1 + userMove,	//바라보는 점
			0, 1, 0);	//업벡터 
		break;
	case 2:
		// 달리는 옆모습
		cam.set(-20 + goLR + eyeX, 5 + eyeY, -0.1 + -5 + userMove,	//눈의 좌표
			20 + goLR, -5, userMove,	//바라보는 점
			0, 1, 0);	//업벡터
		break;
	default:
		break;
	}
	glutPostRedisplay();
}
void MyKeyboard(unsigned char KeyPressed, int X, int Y)
{


	switch (KeyPressed)
	{
	case 'w': case 'W':  //y축 위로
		eyeY += 0.3;
		cam.set(0 + eyeX, 8 + eyeY, 9 + eyeZ,	//눈의 좌표
			0, 0, 0 + aaa,	//바라보는 점
			0, 1, 0);	//업벡터 
		break;
	case 's': case 'S':  //y축 밑으로
		eyeY += -0.3;
		cam.set(0 + eyeX, 8 + eyeY, 9 + eyeZ,	//눈의 좌표
			0, 0, 0 + aaa,	//바라보는 점
			0, 1, 0);	//업벡터 
		break;
	case 'a': case 'A': //z축 앞으로
		aaa -= 0.3;
		cam.set(0 + eyeX, 8 + eyeY, 9 + eyeZ,	//눈의 좌표
			0, 0, 0 + aaa,	//바라보는 점
			0, 1, 0);	//업벡터 
		break;
	case 'd': case 'D': //z축 뒤로
		aaa += 0.3;
		cam.set(0 + eyeX, 8 + eyeY, 9 + eyeZ,	//눈의 좌표
			0, 0, 0 + aaa,	//바라보는 점
			0, 1, 0);	//업벡터 
		break;
	case '1':
		// 캐릭터 뒷모습 보기
		eyeX = 0, eyeY = 0, eyeZ = 0;
		cameraLook = 0;
		break;
	case '2':
		// 캐릭터 앞모습 보기
		eyeX = 0, eyeY = 0, eyeZ = 0;
		cameraLook = 1;
		break;
	case '3':
		// 캐릭터 옆모습 보기
		eyeX = 0, eyeY = 0, eyeZ = 0;
		cameraLook = 2;
		break;
	case 32:
		// 중복 점프를 막음
		if (isjump == 0) {
			isjump = 1;
			jumpStart = clock(); // 시간 측정 시작
			playSound(3);
			break;
		}
	}
	glutPostRedisplay();
}

bool runToggle = true;
void MySpecial(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		if (goLR > -3.0) {
			goLR -= 0.1;
		}
		break;
	case GLUT_KEY_RIGHT:
		if (goLR < 3.0) {
			goLR += 0.1;
		}
		break;
	case GLUT_KEY_DOWN:
		if (runToggle) {
			//playSound(2);
			userSpeed += 0.04;
			runToggle != runToggle;
		}
		break;
	case GLUT_KEY_UP:
		if (runToggle) {
			//playSound(1);
			userSpeed += 0.04;
			runToggle != runToggle;
		}
		break;
	}


	glutPostRedisplay();
}
void MyMouseClick(GLint Button, GLint State, GLint X, GLint Y)  //클릭한 점을 기준으로
{
	if (Button == GLUT_LEFT_BUTTON && State == GLUT_DOWN)
	{
		initX = X;
	}
}
//카메라의 위치를 변환 시킴
void MyMouseMove(GLint X, GLint Y) {
	if (X > initX) {
		eyeX -= delta;
		eyeZ -= delta * zzz;
	}
	if (X < initX) {
		eyeX += delta;
		eyeZ += delta * zzz;
	}
	if (eyeX > 12) {
		eyeX = 12;
	}
	if (eyeX < -10) {
		eyeX = -10;
	}
	if (eyeZ > 10) {
		eyeZ = 10;
	}
	if (eyeZ < -8) {
		eyeZ = -8;
	}
	if (eyeZ > 2) {
		zzz *= -1;
	}

	cam.set(0 + eyeX, 8 + eyeY, 9 + eyeZ,	//눈의 좌표
		0, 0, 0 + aaa,	//바라보는 점
		0, 1, 0);	//업벡터
	glutPostRedisplay();
}


/*
 * light (조명)
 */
void InitLight()
{
	GLfloat mat_diffuse[] = { 0.1, 0.0, 0.0, 1.0 };
	GLfloat mat_specular[] = { 0.1, 0.0, 0.0, 1.0 };
	GLfloat mat_ambient[] = { 0.1, 0.0, 0.0, 1.0 };
	GLfloat mat_shininess[] = { 1.0 };

	//0번 조명
	GLfloat light_specular[] = { 1.0, 0.8, 0.9, 1.0 };
	GLfloat light_diffuse[] = { 1.0, 0.6, 0.8, 1.0 };
	GLfloat light_ambient[] = { 1.0, 0.7, 0.6, 1.0 };

	GLfloat light_position[] = { -3, 10, 3.0, 0.0 };	//조명 위치 할당,  태양처럼 위에서 아래로 내려 쬠

	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);

	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
}


/*
 * 텍스쳐
 */
void MyInit()
{
	playSound(0);
	// 백그라운드 색상을 클리어 한다.
	glClearColor(0.65, 0.33, 0.21, 0.0);

	if (loadImg) {
		char filename1[20] = "choi.bmp";
		boardTexture.ReadBMP(filename1); // && 그림 파일 리드

		char filename2[20] = "background.bmp";
		objectTexture.ReadBMP(filename2); // && 그림 파일 리드
		loadImg = false;

		char filename3[20] = "enemy.bmp";
		enemyTexture.ReadBMP(filename3); // && 그림 파일 리드
		loadImg = false;

		char coinData[] = "./gameData/coin.txt";
		readPos(coinData);

		char obstacleData[] = "./gameData/obstacle.txt";
		readPos(obstacleData);

		char lineData[] = "./gameData/line.txt";
		readPos(lineData);
	}

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP); // GL_REPEAT
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP); // GL_REPEAT

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	//확장관계일때 양방향 선형 보간
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	//GL_LINEAR_MIPMAP_LINEAR : 밉맵
	//mip map을 사용하면 비용은 많이들지만 품질이 좋아짐
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR); 
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	//환경에 대한 설정,  텍스쳐가 지엘 덮었을때 원래 물체를 없앨건지?,  섞을건지
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL); // modulate 섞어줌



	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // GL_REPEAT, 가로방향이 s,  텍스쳐가 만약 좌표가 짤려도 반복해서 갖다 붙임 = REPEAT
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // GL_REPEAT, 세로방향이 t,  텍스쳐가 만약 좌표가 짤려도 반복해서 갖다 붙임 = REPEAT
}


void readPos(char* fileDir) {
	ifstream ifs;        // 입력스트림 ifs 객체 생성
	ifs.open(fileDir);   // 기존의 a.txt 파일을 엽니다.
	int testcase, turn;   // 데이터의 개수, 입력 데이터 저장 위치
	double num = 0;             // 두 개의 변수 선언
	if (ifs.fail()) {
		cout << "\"" << fileDir << "\"" << " 파일을 찾을 수 없습니다.\n";
	}
	else {
		ifs >> testcase;
		// testcase 1000 이상 : 코인 
		// testcase -1000 이하 : 장애물
		if (testcase >= 1000) {
			testcase /= 1000;
			maxCoin = testcase;
			for (int i = 0; i < testcase; i++) {
				for (int j = 0; j < 3; j++) {
					ifs >> num;
					coinPosition[i].allObj = testcase;
					coinPosition[i].objNum = testcase * i + j;
					if (j == 0) {
						// 라인번호를 값으로 변환
						if (num == 1) num = -3;
						else if (num == 2) num = -1.5;
						else if (num == 3) num = 0;
						else if (num == 4) num = 1.5;
						else if (num == 5) num = 3;
						coinPosition[i].x = num;
					}
					else if (j == 1) {
						coinPosition[i].y = num;
					}
					else if (j == 2) {
						coinPosition[i].z = num;
					}
				}
			}
		}
		else if (-1000 < testcase) {
			maxObstacle = testcase;
			for (int i = 0; i < testcase; i++) {
				for (int j = 0; j < 3; j++) {
					ifs >> num;
					obstaclePosition[i].allObj = testcase;
					obstaclePosition[i].objNum = testcase * i + j;
					if (j == 0) {
						// 라인번호를 값으로 변환
						if (num == 1) num = -3;
						else if (num == 2) num = -1.5;
						else if (num == 3) num = 0;
						else if (num == 4) num = 1.5;
						else if (num == 5) num = 3;
						obstaclePosition[i].x = num;
					}
					else if (j == 1) {
						obstaclePosition[i].y = num;
					}
					else if (j == 2) {
						obstaclePosition[i].z = num;
					}
				}
			}
		}
		else {
			testcase *= -1;
			testcase /= 1000;
			maxLine = testcase;
			for (int i = 0; i < testcase; i++) {
				for (int j = 0; j < 3; j++) {
					ifs >> num;
					obstaclePosition[i].allObj = testcase;
					obstaclePosition[i].objNum = testcase * i + j;
					if (j == 0) {
						linePosition[i].x = num;
					}
					else if (j == 1) {
						linePosition[i].y = num;
					}
					else if (j == 2) {
						linePosition[i].z = num;
					}
				}
			}
		}
	}
	ifs.close();
}

void text() {
	char text[32];
	sprintf(text, "Heart : %d RemainCoin : %d", user.setLife(0), 30 - user.setCoin(0));
	glColor3f(10, 10, 10);
	glRasterPos3f(-4 + goLR, 9, userMove - 15);
	for (int i = 0; text[i] != '\0'; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
}