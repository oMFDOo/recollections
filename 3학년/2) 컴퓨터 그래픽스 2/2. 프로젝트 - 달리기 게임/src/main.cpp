#define _CRT_SECURE_NO_WARNINGS  //����� ������� 2015 �̻��� �������� scanf���� ���� ���� ���ִ� ��

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

// �� ���� ����
bool loadImg = true;

// ��ֹ� ��ġ
double obstacleZ[5] = { 0, 1, 2, 3, 4 };
int drawCoinStartIdx = 0, drawCoinEndIdx = 10;
int drawObstacleStartIdx = 0, drawObstacleEndIdx = 10;
int drawLineStartIdx = 0, drawLineEndIdx = 10;
int maxCoin = 0, maxObstacle = 0, maxLine = 0;

// ĳ���� ����
double jump = 0.0;
clock_t jumpStart, jumpIng;
int isjump = 0;
int jumpTurm = 600;

// ĳ���� �¿�
double goLR = 0;

// ī�޶� ���� ��� ����
int cameraLook = 0;

// �ؽ�ó �ε�
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
float h = 0.25; //������ ���� ���� ����
float a = 0.01f;//������ ���� ���� ����


float userT = 0; //���� �⺻ �ӵ� ���� ����
float userMove = 0; //���� ��ġ ����
float userSpeed = 0.0; //���� ���� �ӵ� ���� ����

float enemyT1 = 0; //��1 �⺻ �ӵ� ���� ����
float enemy1Speed = 0; //�� 1 ���� �ӵ� ���� ����

float enemyT2 = 0; //��2 �ӵ� ���� ����
float enemy2Speed = 0; //�� 2 ���� �ӵ� ���� ����

float enemyT3 = 0; //��3 �ӵ� ���� ����
float enemy3Speed = 0; //�� 3 ���� �ӵ� ���� ����

float enemyT4 = 0; //��4 �ӵ� ���� ����
float enemy4Speed = 0; //�� 4 ���� �ӵ� ���� ����

GLUquadricObj* cyl;	//��� �� ������Ʈ
GLUquadricObj* cylTree;	//��� �� ������Ʈ

GLfloat eyeX = 0, eyeY = 0, eyeZ = 0; //ī�޶��� ���� ������ ���� ����
GLfloat initX = 0, initY = 0;   //���콺 Ŭ�� �������� �ʱ� ��ġ
GLfloat delta = 0.1;            //���콺 �����Ͻ� ���� ������ ���� ����
GLfloat zzz = 1;   //ī�޶� ���� ������ ���� ����
GLfloat aaa = 0.1; //ī�޶� ���� ������ ���� ����

Cylinder tunnel;

//����
typedef enum Color {
	BLACK_, DARK_BLUE, DARK_GREEN, DARK_SKYBLUE,
	DARK_RED, DARK_VOILET, DAKR_YELLOW, GRAY,
	DARK_GRAY, BLUE_, GREEN_, SKYBLUE, RED_, VIOLET,
	YELLOW, WHITE_,
};

void MyMouseClick(GLint Button, GLint State, GLint X, GLint Y);  //Ŭ���� ���� ��������
void MyMouseMove(GLint X, GLint Y); //ī�޶��� ��ġ�� ��ȯ ��Ŵ
void InitLight(); //���� 
void MyIdle(); //���̵�
void MyKeyboard(unsigned char KeyPressed, int X, int Y); //Ű����
void MyDisplay();
void MySpecial(int key, int x, int y); //Ư��Ű Ű����
void MyInit(); //�ؽ��� ��� �Լ�
// �ؽ��Ŀ� �߰� �Լ�
int loadGLTextures(int i);
int drawGLScene(int pos, int object);

void enemySet(float a, float r, float g, float b, float pibo, float t, float enemySpeed);
// ��� ������ִ� �Լ�,   a ��ġ ����, rgb,  pibo �Ǻ� ���� ����, �� �ɸ��͸��� �⺻ �ӵ� ����, ���� �ӵ� ����

void userSet(float a, float r, float g, float b); // ������
void enemySetSpeed(); //���� �ӵ� �����ϰ� �ο�
void board(); //�ٴ� ��
void tree1(int posL); //����1
void tree2(int posL); //����2
void finishLine(int posL);  //�ǴϽ� ���� �޸��� ���� ��
void gameOverCheck(); //���� ���� üũ

// ��ġ �о����
void readPos(char* fileDir);
Pos coinPosition[1000];
Pos obstaclePosition[1000];
Pos linePosition[1000];

bool isCoinVisible(int posD);
bool isObstacleVisible(int posD);
bool isLineVisiable(int posD);
bool checkCoin(int i); // �浹 ó��
bool checkObstacle(int i);
bool checkTreeL(int i);
bool checkTreeR(int i);
bool checkLine(int i);
User user;
bool IsInput = false;
double collisionLight = 0.0;

// �������
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
	intro_start();  //������� intro�� �ִ� ���� ���� cmdâ�� �����ִ� �Լ�

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(800, 200);

	glutCreateWindow("OpenGL Sample Drawing");
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();//������� ������ķ� �ʱ�ȭ
	gluPerspective(20, 1, 0.1, 1000);

	//������� ī�޶� �ʱ�ȭ�� ���� ����� ��
	//gluLookAt
	cam.set(0, 40, 9,	//���� ��ǥ
		0, 0, 0,	//�ٶ󺸴� ��
		0, 1, 0);	//������ 

	InitLight(); //���� �ʱ�ȭ
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
	// && �ؽ��� �׸��� ���     �� ������ �ٽ�!  -> �ؽ��� ����,  �������� ��ǥ�� ���߸� ��
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, objectTexture.GetWidth(), objectTexture.GetHeight(), GL_BGR_EXT, GL_UNSIGNED_BYTE, objectTexture.m_lpImage); //mip map�� �������

	return true;
}

int drawGLScene(int posD, int object)			// Here's Where We Do All The Drawing
{
	// �� ��ġ ����
	glClearDepth(1.0f);                   // Set background depth to farthest
	glEnable(GL_TEXTURE_2D);
	glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
	glShadeModel(GL_SMOOTH);   // Enable smooth shading
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections

	glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix

	loadGLTextures(0);

	if (object == 0) {
		if (coinPosition[posD].visible == true) {
			// �ؽ��� �ҷ�����
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
		// && �ؽ��� �׸��� ���     �� ������ �ٽ�!  -> �ؽ��� ����,  �������� ��ǥ�� ���߸� ��
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, enemyTexture.GetWidth(), enemyTexture.GetHeight(), GL_BGR_EXT, GL_UNSIGNED_BYTE, enemyTexture.m_lpImage); //mip map�� �������

		// �� ��ġ ����
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
			cam.set(0 + eyeX + goLR + cameraMoveX, 2 + eyeY + cameraMoveY, 7 + eyeZ - 0.1 + userMove,	//���� ��ǥ
				0 + goLR, 2, -0.1 + userMove,	//�ٶ󺸴� ��
				0, 1, 0);	//������ 
			cameraMoveY -= 0.1;
			cameraMoveX -= 0.2;
		}
		float mat_diffuse1[4] = { 0.1, 0.4, 0.6, 1 }; // �߰�  ��� ����
		float mat_diffuse2[4] = { 1.0, 1.0 ,0.7, 1 }; // �߰�  �� ����


		// ���� �ϱ�
		jumpIng = clock();
		// �ö󰡱�
		if (isjump && jumpIng - jumpStart < jumpTurm) {
			// ����ð� �������� ���� ������ �־���.
			// +1 �Ͽ� 0�� ������ ���� ����
			jump += (double)(jumpTurm + 1 - (jumpIng - jumpStart)) / 2000.0;
		}
		// ��������
		if (isjump && jumpIng - jumpStart >= jumpTurm && jumpIng - jumpStart < (jumpTurm * 2)) {
			// �ö� �ð��� ����
			jump += -(double)(jumpIng - jumpStart - (jumpTurm + 1)) / 2000.0;
			if (jump - 0.002 > 0) {
			}
		}
		// ��������
		if (isjump && jumpIng - jumpStart >= (jumpTurm * 2)) {
			isjump = 0;
			jump = 0.0;
		}


		cyl = gluNewQuadric();
		gluQuadricDrawStyle(cyl, GLU_FILL);	//������ �׷���

		cylTree = gluNewQuadric();
		gluQuadricDrawStyle(cylTree, GLU_FILL);	//������ �׷���

		glEnable(GL_DEPTH_TEST); // Enable depth testing for z-culling
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);


		glDisable(GL_LIGHTING);	//���� ���ٰ�
		glPushMatrix();
		text();
		glPopMatrix();
		glEnable(GL_LIGHTING); // �ٽ� Ŵ


		for (int i = drawCoinStartIdx; i < drawCoinEndIdx; i++) {
			// �������� : ��
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
				//���� 1
				glPushMatrix();
				tree1(i);
				glPopMatrix();
				//���� 2
				glPushMatrix();
				tree2(i);
				glPopMatrix();
			}
		}



		//�ٴ�	
		//glDisable(GL_LIGHTING);	//���� ���ٰ�
		glPushMatrix();
		board();
		glPopMatrix();
		//glEnable(GL_LIGHTING); // �ٽ� Ŵ



		//user
		userSet(0, 0.1, 0.4, 0.6);

		glFlush();
		glutPostRedisplay();      //�����츦 �ٽ� �׸����� ��û
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
		cout << "\t\t\t\t\t==> �г����� �Է��ϼ��� : ";
		textcolor(DARK_VOILET, SKYBLUE);
		cin >> temp;
		IsInput = true;
		user.setName(temp);
		textcolor(WHITE_, BLACK_);
		cout << "\t\t\t====================================================================\n\n";
		textcolor(DARK_SKYBLUE, BLACK_);
		cout << "\t\t\t\t\t\t���� ���۹�!\n\n";
		textcolor(WHITE_, BLACK_);
		cout << "\t\t\t====================================================================\n";
		cout << "\t\t\t\t\t\t�� �� : ĳ���� �ӵ� ����\n";
		cout << "\t\t\t\t\t\t�� �� : ĳ���� �¿� �̵�\n";
		cout << "\t\t\t\t\t\t<space bar> : ����\n";
		cout << "\t\t\t\t\t\tW, S : ī�޶� ��/�Ʒ� ������ȯ\n";
		cout << "\t\t\t\t\t\t1, 2, 3 : ī�޶� ��/��/�� ������ȯ\n";
		cout << "\t\t\t\t\t\t���콺 Ŭ�� : ���� ������ȯ\n\n\n";

		cout << "\t\t\t====================================================================\n\n";
		cout << "\t\t\t\t\t\t���� �ȳ�!\n\n";
		cout << "\t\t\t====================================================================\n";
		textcolor(DARK_SKYBLUE, BLACK_);
		cout << "\t\t\t\t\t - ���� ���� 30���� ������ ����!\n";
		textcolor(WHITE_, BLACK_);
		cout << "\t\t\t\t\t - Life 10���� ��� �����ϸ� ���ФФ�!\n";

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
			// ���� ����
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
		ofstream writeFile("./gameData/rank.txt", ios::app); //�� ������ ���� ����
		string tempUserName = user.getName();
		tempUserName += " " + to_string(endTime) + " ms";
		//������ ���ȴ��� Ȯ��
		if (writeFile.is_open()) {
			writeFile << tempUserName << endl;
		}
		writeFile.close();

		string dummy;
		ifstream ifs;        // �Է½�Ʈ�� ifs ��ü ����
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
		cout << "\t\t" << userName << "���� " << userRankResult << "�� �Դϴ�!\n";
		textcolor(WHITE_, BLACK_);
		cout << "\t\t" << "�� Ŭ���� �ð� : " << to_string(endTime) << "\n\n";
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
	//������ �ӵ��� �����ϰ� �ο���
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
	float mat_diffuse1[4] = { 0.9, 0.8, 0.9, 1 }; // ������
	float mat_diffuse2[4] = { 0.64, 0.29, 0.64, 1 }; // ���� ��

	if (checkTreeL(posL) == true) {
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse1); // �߰�
		glTranslatef(-3, -0.5, linePosition[posL].z);
		glRotatef(270, 1, 0, 0);
		gluCylinder(cylTree, 0.3, 0.3, 2.0, 20, 1);

		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse2); // �߰�
		glTranslatef(0.0, 0, 2.0);
		gluCylinder(cylTree, 0.6, 0, 1.5, 20, 1);
	}
}
void tree2(int posL) {
	float mat_diffuse1[4] = { 0.9, 0.8, 0.9, 1 }; // ������
	float mat_diffuse2[4] = { 0.64, 0.29, 0.64, 1 }; // ���� ��

	if (checkTreeR(posL) == true) {
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse1); // �߰�
		glTranslatef(3, -0.5, linePosition[posL].z);
		glRotatef(270, 1, 0, 0);
		gluCylinder(cylTree, 0.3, 0.3, 2.0, 20, 1);

		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse2); // �߰�
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
	// && �ؽ��� �׸��� ���     �� ������ �ٽ�!  -> �ؽ��� ����,  �������� ��ǥ�� ���߸� ��
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, boardTexture.GetWidth(), boardTexture.GetHeight(), GL_BGR_EXT, GL_UNSIGNED_BYTE, boardTexture.m_lpImage); //mip map�� �������

	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	glTranslatef(0, 0,userMove);
	glRotatef(135, 1, 0, 0);
	glScalef(30, 80000, 30);
	tunnel.Draw();
	glPopMatrix();
	glBegin(GL_QUADS);
	//�ؽ��Ĵ� 0���� 1����
	//�տ����� �ؽ��� ��ǥ,  �������� gl�� ��ü ��ǥ
	//�ؽ����� ������ ������ �����ؼ� ��ü�� ����
	//1���� ū ���� �� �� gl�� �ȼ��� �׳� �� �����Ŵ
	//glColor3f(0.0, 0.0, 0.4);
	glTexCoord2f(0.0, 0.0); glVertex3f(-4.0, -0.6, -800.0);	// ���ϴ�
	glTexCoord2f(0.0, 1.0); glVertex3f(4.0, -0.6, -800.0);	// ���ϴ�
	glTexCoord2f(25.0, 1.0); glVertex3f(4.0, -0.6, 10.0);	// ����
	glTexCoord2f(25.0, 0.0); glVertex3f(-4.0, -0.6, 10.0);	// �»��

	//glTexCoord2f(0.0, 0.0); glVertex3f(-10.0, -10.0, -17.8);	// ���ϴ�
	//glTexCoord2f(0.0, 1.0); glVertex3f(10.0, -10.0, -17.8);	// ���ϴ�
	//glTexCoord2f(1.0, 1.0); glVertex3f(10.0, 10.0, -17.8);	// ����
	//glTexCoord2f(1.0, 0.0); glVertex3f(-10.0, 10.0, -17.8);	// �»��
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void userSet(float a, float r, float g, float b)
{
	float mat_diffuse1[4] = { r, g, b, 1 }; // �� ����
	float mat_diffuse2[4] = { 1.0, 0.9, 0.9, 1 }; // ��� ������ ����

	float material_diffuse1[] = { 0.3, 0.1, 0.4, 1.0 };
	float material_diffuse2[] = { 0.3, 0.1, 0.4, 1.0 };


	//���� ���� üũ!!
	char temp[5];
	strcpy(temp, "User");
	gameOverCheck();

	glPushMatrix();
	glTranslatef(a + goLR, (sin(userT * 0.1) + 1) / 20 + jump, -0.1 + userMove);
	// 1. ����
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse1); // �߰�
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	gluCylinder(cyl, 0.27, 0.12, 0.6, 20, 1);
	glRotatef(90, 1, 0, 0);

	// 1. �Ӹ�
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse2); // �߰�
	glTranslatef(0, 0.68, 0);
	glutSolidSphere(0.3, 20, 20);

	// ���� ì
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse1);
	glTranslatef(0.0, 0.10, 0.12);
	glRotatef(-50, 1.0f, 0.0f, 0.0f);
	gluCylinder(cyl, 0.45, 0.01, 0.3, 20, 1);

	// ���� ��
	glPushMatrix();
	glutSolidCone(0.3, 0.7, 100, 100);
	glPopMatrix();
	glPopMatrix();

	//glutSolidSphere(0.17, 20, 20);
	glPopMatrix();
	// 1. ����
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse1);
	glTranslatef(-0.2, 0.35, 0);	//���� �������� 0.05�̰� �Ǹ����� �������� 0.1�̹Ƿ� 0.15��ŭ �������� �߽����� ��, �׸� �����ϱ�!
	glutSolidSphere(0.05, 20, 20);
	glRotatef(sin(userT * 0.1) * 90 + 90, 1, 0, 0);
	gluCylinder(cyl, 0.05, 0.05, 0.2, 20, 1);

	//2. �Ȳ�ġ���� �ȿ� ��
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse2);
	//glPushMatrix();
	glTranslatef(0.0, 0.0, 0.2);	//���� �������� 0.05�̰� �Ǹ����� �������� 0.1�̹Ƿ� 0.15��ŭ �������� �߽����� ��, �׸� �����ϱ�!
	glutSolidSphere(0.05, 20, 20);
	glRotatef(sin(userT * 0.1) * 45 + 45, 1, 0, 0);
	gluCylinder(cyl, 0.05, 0.05, 0.2, 20, 1);

	//3. ��! ���� ������ �پ������Ƿ� Ǫ�� �� �ʿ� ����
	glTranslatef(0.0, 0.0, 0.2);	//���� �������� 0.05�̰� �Ǹ����� �������� 0.1�̹Ƿ� 0.15��ŭ �������� �߽����� ��, �׸� �����ϱ�!
	glutSolidSphere(0.08, 20, 20);
	//glPopMatrix();
	glPopMatrix();


	// 1. ������
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse1);
	glTranslatef(0.2, 0.35, 0);	//���� �������� 0.05�̰� �Ǹ����� �������� 0.1�̹Ƿ� 0.15��ŭ �������� �߽����� ��, �׸� �����ϱ�!
	glutSolidSphere(0.05, 20, 20);
	glRotatef(sin(-userT * 0.1) * 90 + 90, 1, 0, 0);
	gluCylinder(cyl, 0.05, 0.05, 0.2, 20, 1);

	//2. �Ȳ�ġ���� �ȿ� ��
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse2);
	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.2);	//���� �������� 0.05�̰� �Ǹ����� �������� 0.1�̹Ƿ� 0.15��ŭ �������� �߽����� ��, �׸� �����ϱ�!
	glutSolidSphere(0.05, 20, 20);
	glRotatef(sin(-userT * 0.1) * 45 + 45, 1, 0, 0);
	gluCylinder(cyl, 0.05, 0.05, 0.2, 20, 1);

	//3. ��! ���� ������ �پ������Ƿ� Ǫ�� �� �ʿ� ����
	glTranslatef(0.0, 0.0, 0.2);	//���� �������� 0.05�̰� �Ǹ����� �������� 0.1�̹Ƿ� 0.15��ŭ �������� �߽����� ��, �׸� �����ϱ�!
	glutSolidSphere(0.08, 20, 20);
	glPopMatrix();
	glPopMatrix();

	// 1. �ٸ�, ������
	// ���� �ٸ�
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse2);
	glTranslatef(-0.07, 0.1, 0);	//���� �������� 0.05�̰� �Ǹ����� �������� 0.1�̹Ƿ� 0.15��ŭ �������� �߽����� ��, �׸� �����ϱ�!
	glutSolidSphere(0.08, 20, 20);
	glRotatef(sin(-userT * 0.1) * 40 + 110, 0.5, 0, 0);
	gluCylinder(cyl, 0.08, 0.06, 0.3, 20, 1);
	//���� �߹ٴ�
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse1);
	glTranslatef(0, -0.03, 0.35);
	glScalef(1.2, 2.0, 1);
	glutSolidCube(0.1);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	// ������ �ٸ�
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse2);
	glTranslatef(0.07, 0.1, 0);	//���� �������� 0.05�̰� �Ǹ����� �������� 0.1�̹Ƿ� 0.15��ŭ �������� �߽����� ��, �׸� �����ϱ�!
	glutSolidSphere(0.08, 20, 20);
	glRotatef(sin(userT * 0.1) * 40 + 110, 0.5, 0, 0);
	gluCylinder(cyl, 0.08, 0.08, 0.3, 20, 1);
	//������ �߹ٴ�
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse1);
	glTranslatef(0, -0.03, 0.35);
	glScalef(1.2, 2.0, 1);
	glutSolidCube(0.1);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();//���� ����
	glPopMatrix();	//��� ����
}

/*
 * glutFunk
 */
void MyIdle()
{
	//�� �ɸ����� �ӵ� ����
	enemyT1 += 0.012f; //�⺻ �ӵ�
	enemyT1 += enemy1Speed; //�߰� �� �ӵ�

	enemyT2 += 0.013f; //�⺻ �ӵ�
	enemyT2 += enemy2Speed; //�߰� �� �ӵ�

	enemyT3 += 0.011f; //�⺻ �ӵ�
	enemyT3 += enemy3Speed; //�߰� �� �ӵ�

	enemyT4 += 0.014f; //�⺻ �ӵ�
	enemyT4 += enemy4Speed; //�߰� �� �ӵ�

	userT += 0.01f; //������ �⺻ �ӵ�
	userT += userSpeed; //�߰� �� �ӵ�


	//������ ��̸� ���� ������ �ӵ��� �ڵ����� ������� �������� ����
	userMove -= userSpeed * 0.1;
	//�ӵ��� 0���� ���� �� ����
	if (userSpeed - 0.00002 > 0)
	{
		userSpeed -= 0.00002;
	}


	//�پ�� ����� �ڿ������� �ϱ� ���ؼ� �پ�� ����� ��� ���� ���Ʒ��� �����̰� ����
	if (h <= 0.25)
		a = +0.001f;
	if (h >= 0.75)
	{
		a = -0.001f;
	}
	h = h + a;
	//ī�޶� ������� ������ �ڵ����� ������ ���� ����
	//aaa -= 0.002;
	//cam.set(-25 + eyeX, 5 + eyeY, 0 + eyeZ + aaa,	//���� ��ǥ
	//	10, 0, 0 + aaa,	//�ٶ󺸴� ��
	//	0, 1, 0);	//������ 

	switch (cameraLook) {
	case 0:
		// �޸��� �޸��
		cam.set(0 + eyeX + goLR, 2 + eyeY, 7 + eyeZ - 0.1 + userMove,	//���� ��ǥ
			0 + goLR, 2, -0.1 + userMove,	//�ٶ󺸴� ��
			0, 1, 0);	//������ 
		break;
	case 1:
		// �޸��� �ո��
		cam.set(0 + eyeX + goLR, 0 + eyeY, -10 - 0.1 + userMove,	//���� ��ǥ
			0 + goLR, 2, -0.1 + userMove,	//�ٶ󺸴� ��
			0, 1, 0);	//������ 
		break;
	case 2:
		// �޸��� �����
		cam.set(-20 + goLR + eyeX, 5 + eyeY, -0.1 + -5 + userMove,	//���� ��ǥ
			20 + goLR, -5, userMove,	//�ٶ󺸴� ��
			0, 1, 0);	//������
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
	case 'w': case 'W':  //y�� ����
		eyeY += 0.3;
		cam.set(0 + eyeX, 8 + eyeY, 9 + eyeZ,	//���� ��ǥ
			0, 0, 0 + aaa,	//�ٶ󺸴� ��
			0, 1, 0);	//������ 
		break;
	case 's': case 'S':  //y�� ������
		eyeY += -0.3;
		cam.set(0 + eyeX, 8 + eyeY, 9 + eyeZ,	//���� ��ǥ
			0, 0, 0 + aaa,	//�ٶ󺸴� ��
			0, 1, 0);	//������ 
		break;
	case 'a': case 'A': //z�� ������
		aaa -= 0.3;
		cam.set(0 + eyeX, 8 + eyeY, 9 + eyeZ,	//���� ��ǥ
			0, 0, 0 + aaa,	//�ٶ󺸴� ��
			0, 1, 0);	//������ 
		break;
	case 'd': case 'D': //z�� �ڷ�
		aaa += 0.3;
		cam.set(0 + eyeX, 8 + eyeY, 9 + eyeZ,	//���� ��ǥ
			0, 0, 0 + aaa,	//�ٶ󺸴� ��
			0, 1, 0);	//������ 
		break;
	case '1':
		// ĳ���� �޸�� ����
		eyeX = 0, eyeY = 0, eyeZ = 0;
		cameraLook = 0;
		break;
	case '2':
		// ĳ���� �ո�� ����
		eyeX = 0, eyeY = 0, eyeZ = 0;
		cameraLook = 1;
		break;
	case '3':
		// ĳ���� ����� ����
		eyeX = 0, eyeY = 0, eyeZ = 0;
		cameraLook = 2;
		break;
	case 32:
		// �ߺ� ������ ����
		if (isjump == 0) {
			isjump = 1;
			jumpStart = clock(); // �ð� ���� ����
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
void MyMouseClick(GLint Button, GLint State, GLint X, GLint Y)  //Ŭ���� ���� ��������
{
	if (Button == GLUT_LEFT_BUTTON && State == GLUT_DOWN)
	{
		initX = X;
	}
}
//ī�޶��� ��ġ�� ��ȯ ��Ŵ
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

	cam.set(0 + eyeX, 8 + eyeY, 9 + eyeZ,	//���� ��ǥ
		0, 0, 0 + aaa,	//�ٶ󺸴� ��
		0, 1, 0);	//������
	glutPostRedisplay();
}


/*
 * light (����)
 */
void InitLight()
{
	GLfloat mat_diffuse[] = { 0.1, 0.0, 0.0, 1.0 };
	GLfloat mat_specular[] = { 0.1, 0.0, 0.0, 1.0 };
	GLfloat mat_ambient[] = { 0.1, 0.0, 0.0, 1.0 };
	GLfloat mat_shininess[] = { 1.0 };

	//0�� ����
	GLfloat light_specular[] = { 1.0, 0.8, 0.9, 1.0 };
	GLfloat light_diffuse[] = { 1.0, 0.6, 0.8, 1.0 };
	GLfloat light_ambient[] = { 1.0, 0.7, 0.6, 1.0 };

	GLfloat light_position[] = { -3, 10, 3.0, 0.0 };	//���� ��ġ �Ҵ�,  �¾�ó�� ������ �Ʒ��� ���� ��

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
 * �ؽ���
 */
void MyInit()
{
	playSound(0);
	// ��׶��� ������ Ŭ���� �Ѵ�.
	glClearColor(0.65, 0.33, 0.21, 0.0);

	if (loadImg) {
		char filename1[20] = "choi.bmp";
		boardTexture.ReadBMP(filename1); // && �׸� ���� ����

		char filename2[20] = "background.bmp";
		objectTexture.ReadBMP(filename2); // && �׸� ���� ����
		loadImg = false;

		char filename3[20] = "enemy.bmp";
		enemyTexture.ReadBMP(filename3); // && �׸� ���� ����
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

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	//Ȯ������϶� ����� ���� ����
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	//GL_LINEAR_MIPMAP_LINEAR : �Ӹ�
	//mip map�� ����ϸ� ����� ���̵����� ǰ���� ������
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR); 
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	//ȯ�濡 ���� ����,  �ؽ��İ� ���� �������� ���� ��ü�� ���ٰ���?,  ��������
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL); // modulate ������



	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // GL_REPEAT, ���ι����� s,  �ؽ��İ� ���� ��ǥ�� ©���� �ݺ��ؼ� ���� ���� = REPEAT
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // GL_REPEAT, ���ι����� t,  �ؽ��İ� ���� ��ǥ�� ©���� �ݺ��ؼ� ���� ���� = REPEAT
}


void readPos(char* fileDir) {
	ifstream ifs;        // �Է½�Ʈ�� ifs ��ü ����
	ifs.open(fileDir);   // ������ a.txt ������ ���ϴ�.
	int testcase, turn;   // �������� ����, �Է� ������ ���� ��ġ
	double num = 0;             // �� ���� ���� ����
	if (ifs.fail()) {
		cout << "\"" << fileDir << "\"" << " ������ ã�� �� �����ϴ�.\n";
	}
	else {
		ifs >> testcase;
		// testcase 1000 �̻� : ���� 
		// testcase -1000 ���� : ��ֹ�
		if (testcase >= 1000) {
			testcase /= 1000;
			maxCoin = testcase;
			for (int i = 0; i < testcase; i++) {
				for (int j = 0; j < 3; j++) {
					ifs >> num;
					coinPosition[i].allObj = testcase;
					coinPosition[i].objNum = testcase * i + j;
					if (j == 0) {
						// ���ι�ȣ�� ������ ��ȯ
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
						// ���ι�ȣ�� ������ ��ȯ
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