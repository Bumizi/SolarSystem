#include <GL/freeglut.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "BasicSetUp.h"
#include "CameraManipulationSetUp.h"
#include "Sun.h"
#include "Mercury.h"
#include "Venus.h"
#include "Earth.h"
#include "Mars.h"
#include "Jupiter.h"
#include "Saturn.h"
#include "Uranus.h"
#include "Neptune.h"

Star_Sun Sun;
Star_Mercury Mercury;
Star_Venus Venus;
Star_Earth Earth;
Star_Mars Mars;
Star_Jupiter Jupiter;
Star_Saturn Saturn;
Star_Uranus Uranus;
Star_Neptune Neptune;

struct Orbit {
	double x, z;
	double degree = 0;
};
Orbit Coor[2], Circle[3], Moon[3];
int rt_x = 0, rt_y = 0, rt_z = 0, rt = 0, l_rt = 0, r_rt = 0, c_rt = 0;
double cx = 0, cy = 0, cz = 0, big_radian = 200, small_radian = 70, circle_x, circle_z;
bool rotate = false, c_rotate = true, reverse = false;
bool projection = true, model = true;

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Mouse(int button, int state, int x, int y);
void Keyboard(unsigned char key, int x, int y);
void Motion(int x, int y);
void TimerFunction(int value);

void main(int argc, char *argv[])
{
	srand(time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100); // 윈도우의 위치지정
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT); // 윈도우의 크기 지정
	glutCreateWindow("TheSolarSystem"); // 윈도우 생성 (윈도우 이름)
	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);
	glutPassiveMotionFunc(Motion);
	glutTimerFunc(100, TimerFunction, 1);
	glutMainLoop();
}
// 윈도우 출력 함수
GLvoid drawScene(GLvoid)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if(rotate)
		glRotated(rt, rt_x, rt_y, rt_z);
	gluLookAt(cx, cy + 900, cz + 1600, 0.0 + cx, 0.0 + cy, 0.0 + cz, 0.0, 1.0, 0.0);

	/*
	glColor3f(0.0, 0.0, 1.0);
	if (model)
		glutSolidSphere(60, 30, 30);
	else 
		glutWireSphere(60, 20, 20);
	*/

	//태양
	glPushMatrix();
	glTranslated(Sun.xPos, Sun.yPos, Sun.zPos);
	glColor3d(Sun.RGB[0], Sun.RGB[1], Sun.RGB[2]);
	glutSolidSphere(Sun.Radius, 30, 30);
	glutWireSphere(Sun.Radius, 30, 30);
	glPopMatrix();

	//수성
	glPushMatrix();
	glTranslated(Mercury.xPos, Mercury.yPos, Mercury.zPos);
	glColor3d(Mercury.RGB[0], Mercury.RGB[1], Mercury.RGB[2]);
	glutSolidSphere(Mercury.Radius, 30, 30);
	glutWireSphere(Mercury.Radius, 30, 30);
	glPopMatrix();

	//금성
	glPushMatrix();
	glTranslated(Venus.xPos, Venus.yPos, Venus.zPos);
	glColor3d(Venus.RGB[0], Venus.RGB[1], Venus.RGB[2]);
	glutSolidSphere(Venus.Radius, 30, 30);
	glutWireSphere(Venus.Radius, 30, 30);
	glPopMatrix();

	//지구
	glPushMatrix();
	glTranslated(Earth.xPos, Earth.yPos, Earth.zPos);
	glColor3d(Earth.RGB[0], Earth.RGB[1], Earth.RGB[2]);
	glutSolidSphere(Earth.Radius, 30, 30);
	glutWireSphere(Earth.Radius, 30, 30);
	glPopMatrix();

	//화성
	glPushMatrix();
	glTranslated(Mars.xPos, Mars.yPos, Mars.zPos);
	glColor3d(Mars.RGB[0], Mars.RGB[1], Mars.RGB[2]);
	glutSolidSphere(Mars.Radius, 30, 30);
	glutWireSphere(Mars.Radius, 30, 30);
	glPopMatrix();

	//목성
	glPushMatrix();
	glTranslated(Jupiter.xPos, Jupiter.yPos, Jupiter.zPos);
	glColor3d(Jupiter.RGB[0], Jupiter.RGB[1], Jupiter.RGB[2]);
	glutSolidSphere(Jupiter.Radius, 30, 30);
	glutWireSphere(Jupiter.Radius, 30, 30);
	glPopMatrix();

	//토성
	glPushMatrix();
	glTranslated(Saturn.xPos, Saturn.yPos, Saturn.zPos);
	glColor3d(Saturn.RGB[0], Saturn.RGB[1], Saturn.RGB[2]);
	glutSolidSphere(Saturn.Radius, 30, 30);
	glutWireSphere(Saturn.Radius, 30, 30);
	glPopMatrix();

	//천왕성
	glPushMatrix();
	glTranslated(Uranus.xPos, Uranus.yPos, Uranus.zPos);
	glColor3d(Uranus.RGB[0], Uranus.RGB[1], Uranus.RGB[2]);
	glutSolidSphere(Uranus.Radius, 30, 30);
	glutWireSphere(Uranus.Radius, 30, 30);
	glPopMatrix();

	//해왕성
	glPushMatrix();
	glTranslated(Neptune.xPos, Neptune.yPos, Neptune.zPos);
	glColor3d(Neptune.RGB[0], Neptune.RGB[1], Neptune.RGB[2]);
	glutSolidSphere(Neptune.Radius, 30, 30);
	glutWireSphere(Neptune.Radius, 30, 30);
	glPopMatrix();


	/*
	//궤도
	glColor3f(1.0, 1.0, 1.0);
	for (int i = 0; i <= 360; i++) {
		Coor[0].x = big_radian * cos(Coor[0].degree* PI);
		Coor[0].z = big_radian * sin(Coor[0].degree* PI);
		if(Coor[0].degree < 360)
			Coor[0].degree += 1;
		else
			Coor[0].degree = 0;
		if (Coor[1].degree < 360)
			Coor[1].degree += 1;
		else
			Coor[1].degree = 0;
		Coor[1].x = big_radian * cos(Coor[1].degree* PI);
		Coor[1].z = big_radian * sin(Coor[1].degree* PI);
		glBegin(GL_LINES);
		glVertex3f(Coor[0].x, 0.0, Coor[0].z);
		glVertex3f(Coor[1].x, 0.0, Coor[1].z);
		glEnd();

		glPushMatrix();
		glRotated(45, 0, 0, 1);
		glBegin(GL_LINES);
		glVertex3f(Coor[0].x, 0.0, Coor[0].z);
		glVertex3f(Coor[1].x, 0.0, Coor[1].z);
		glEnd();
		glPopMatrix();

		glPushMatrix();
		glRotated(-45, 0, 0, 1);
		glBegin(GL_LINES);
		glVertex3f(Coor[0].x, 0.0, Coor[0].z);
		glVertex3f(Coor[1].x, 0.0, Coor[1].z);
		glEnd();
		glPopMatrix();
	}
	for (int i = 0; i <= 360; i++) {
		Coor[0].x = small_radian * cos(Coor[0].degree* PI);
		Coor[0].z = small_radian * sin(Coor[0].degree* PI);
		if (Coor[0].degree < 360)
			Coor[0].degree += 1;
		else
			Coor[0].degree = 0;
		if (Coor[1].degree < 360)
			Coor[1].degree += 1;
		else
			Coor[1].degree = 0;
		Coor[1].x = small_radian * cos(Coor[1].degree* PI);
		Coor[1].z = small_radian * sin(Coor[1].degree* PI);
		glPushMatrix();
		glTranslated(Circle[0].x, 0.0, Circle[0].z);
		glBegin(GL_LINES);
		glVertex3f(Coor[0].x, 0.0, Coor[0].z);
		glVertex3f(Coor[1].x, 0.0, Coor[1].z);
		glEnd();
		glPopMatrix();

		glPushMatrix();
		glRotated(45, 0, 0, 1);
		glTranslated(Circle[1].x, 0.0, Circle[1].z);
		glBegin(GL_LINES);
		glVertex3f(Coor[0].x, 0.0, Coor[0].z);
		glVertex3f(Coor[1].x, 0.0, Coor[1].z);
		glEnd();
		glPopMatrix();

		glPushMatrix();
		glRotated(-45, 0, 0, 1);
		glTranslated(Circle[2].x, 0.0, Circle[2].z);
		glBegin(GL_LINES);
		glVertex3f(Coor[0].x, 0.0, Coor[0].z);
		glVertex3f(Coor[1].x, 0.0, Coor[1].z);
		glEnd();
		glPopMatrix();
	}
	
	//큰 공전원
	glColor3f(1.0, 1.0, 0.0);
	for (int i = 0; i < 3; i++) {
		glPushMatrix();
		if (i == 0) {
			glTranslated(Circle[i].x, 0.0, Circle[i].z);
			if (model)
				glutSolidSphere(30, 30, 30);
			else
				glutWireSphere(30, 20, 20);
		}
		else if (i == 1) {
			glRotated(45, 0, 0, 1);
			glTranslated(Circle[i].x, 0.0, Circle[i].z);
			if (model)
				glutSolidSphere(30, 30, 30);
			else
				glutWireSphere(30, 20, 20);
		}
		else {
			glRotated(-45, 0, 0, 1);
			glTranslated(Circle[i].x, 0.0, Circle[i].z);
			if (model)
				glutSolidSphere(30, 30, 30);
			else
				glutWireSphere(30, 20, 20);
		}
		glPopMatrix();
	}

	glColor3f(0.0, 1.0, 1.0);
	//작은 공전원
	for (int i = 0; i < 3; i++) {
		glPushMatrix();
		if (i == 0) {
			glTranslated(Circle[i].x + Moon[i].x, 0.0, Circle[i].z + Moon[i].z);
			if (model)
				glutSolidSphere(10, 30, 30);
			else
				glutWireSphere(10, 20, 20);
		}
		else if (i == 1) {
			glRotated(45, 0, 0, 1);
			glTranslated(Circle[i].x + Moon[i].x, 0.0, Circle[i].z + Moon[i].z);
			if (model)
				glutSolidSphere(10, 30, 30);
			else
				glutWireSphere(10, 20, 20);
		}
		else {
			glRotated(-45, 0, 0, 1);
			glTranslated(Circle[i].x + Moon[i].x, 0.0, Circle[i].z + Moon[i].z);
			if (model)
				glutSolidSphere(10, 30, 30);
			else
				glutWireSphere(10, 20, 20);
		}
		glPopMatrix();
	}
	*/
	glutSwapBuffers();
	//glFlush(); // 화면에 출력하기
}
GLvoid Reshape(int w, int h)
{
	//뷰포트 변환 설정
	glViewport(0, 0, w, h);

	// 투영 행렬 스택 재설정
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (projection) {
		//-- 투영은 직각 투영 또는 원근 투영 중 한 개를 설정한다.
		// 1. 클리핑 공간 설정: 원근 투영인 경우
		gluPerspective(60.0f, w / h, 1.0, 10000.0);
		glFrustum(SCREEN_WIDTH_MIN, SCREEN_WIDTH_MAX, SCREEN_HEIGHT_MIN, SCREEN_HEIGHT_MAX, SCREEN_DEPTH_MIN, SCREEN_DEPTH_MAX);
		glTranslatef(0.0, 0.0, -1000.0); // 투영 공간을 화면 안쪽으로 이동하여 시야를 확보한다.
	}
	else {
		// 2. 클리핑 공간 설정: 직각 투영인 경우
		glOrtho(-400.0, 400.0, -300.0, 300.0, -400.0, 400.0);
	}

	// 모델 뷰 행렬 스택 재설정
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//gluLookAt(0.0, 100.0, 100.0, 0.0, 0.0, -100.0, 0.0, 1.0, 0.0);
}

void Mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		
	}

	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		
	}
	glutPostRedisplay();
}
void Motion(int x, int y) {
	
}
void Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'X':
		if (!reverse)
			reverse = true;
		else
			reverse = false;
		if (!rotate) {
			rotate = true;
			rt_x = 1, rt_y = 0, rt_z = 0;
			rt = 0;
		}
		else
			rotate = false;
		break;
	case 'x':
		reverse = false;
		if (!rotate) {
			rotate = true;
			rt_x = 1, rt_y = 0, rt_z = 0;
			rt = 0;
		}
		else
			rotate = false;
		break;
	case 'Y':
		if (!reverse)
			reverse = true;
		else
			reverse = false;
		if (!rotate) {
			rotate = true;
			rt_x = 0, rt_y = 1, rt_z = 0;
			rt = 0;
		}
		else
			rotate = false;
		break;
	case 'y':
		reverse = false;
		if (!rotate) {
			rotate = true;
			rt_x = 0, rt_y = 1, rt_z = 0;
			rt = 0;
		}
		else
			rotate = false;
		break;
	case 'Z':
		if (!reverse)
			reverse = true;
		else
			reverse = false;
		if (!rotate) {
			rotate = true;
			rt_x = 0, rt_y = 0, rt_z = 1;
			rt = 0;
		}
		else
			rotate = false;
		break;
	case 'z':
		reverse = false;
		if (!rotate) {
			rotate = true;
			rt_x = 0, rt_y = 0, rt_z = 1;
			rt = 0;
		}
		else
			rotate = false;
		break;
	case 'w':
		cy += 5;
		break;
	case 'a':
		cx -= 5;
		break;
	case 's':
		cy -= 5;
		break;
	case 'd':
		cx += 5;
		break;
	case '+':
		cz -= 10;
		break;
	case '-':
		cz += 10;
		break;
	case 'i':
		cx = 0, cy = 50, cz = 50;
		break;
	case 'm':
		if (!model)
			model = true;
		else
			model = false;
		break;
	case 'p':
		if (!projection)
			projection = true;
		else
			projection = false;
		Reshape(WINDOW_WIDTH, WINDOW_HEIGHT);
		break;
	case 'Q': //종료
		glutDestroyWindow(glutCreateWindow("TheSolarSystem"));
		exit(0);
	}
	glutPostRedisplay();
}
void TimerFunction(int value) {
	if (rotate) {
		if (!reverse) {
			if (rt < 360)
				rt++;
			else
				rt = 0;
		}
		else {
			if (rt > -360)
				rt--;
			else
				rt = 0;
		}
	}
	if (c_rotate) {
		if (!reverse) {
			if (c_rt < 360)
				c_rt++;
			else
				c_rt = 0;
		}
		else {
			if (c_rt > -360)
				c_rt--;
			else
				c_rt = 0;
		}
	}

	for (int i = 0; i < 3; i++) {
		if (Circle[i].degree < 360) {
			if (i == 0)
				Circle[i].degree++;
			else if (i == 1)
				Circle[i].degree += 2;
			else
				Circle[i].degree += 3;
			Circle[i].x = big_radian * cos(Circle[i].degree* PI);
			Circle[i].z = big_radian * sin(Circle[i].degree* PI);
		}
		else
			Circle[i].degree = 0;
	}

	for (int i = 0; i < 3; i++) {
		if (Moon[i].degree < 360) {
			Moon[i].degree++;
			Moon[i].x = small_radian * cos(Circle[i].degree* PI);
			Moon[i].z = small_radian * sin(Circle[i].degree* PI);
		}
		else
			Moon[i].degree = 0;
	}
	glutPostRedisplay(); // 화면 재 출력
	glutTimerFunc(10, TimerFunction, 1); // 타이머함수 재 설정
}