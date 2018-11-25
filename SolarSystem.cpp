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

struct Orbit {
	double x, z;
	double degree = 0;
};
Orbit Coor[2], Circle[3], Moon[3];

//ī�޶� ���� ���� ����
int rt_x = 0, rt_y = 0, rt_z = 0, rt = 0, l_rt = 0, r_rt = 0, c_rt = 0;
double cx = 0, cy = 0, cz = 0, big_radian = 200, small_radian = 70, circle_x, circle_z;

//�༺ ����
double Speed = 100;

//bool Ʈ����
bool rotate = false, c_rotate = true, reverse = false;
bool projection = true, model = true;

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Mouse(int button, int state, int x, int y);
void Keyboard(unsigned char key, int x, int y);
void Motion(int x, int y);
void StarRotationTimerFunction(int value);
void TimerFunction(int value);

void main(int argc, char *argv[])
{
	srand(time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // ���÷��� ��� ����
	glutInitWindowPosition(100, 100); // �������� ��ġ����
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT); // �������� ũ�� ����
	glutCreateWindow("TheSolarSystem"); // ������ ���� (������ �̸�)
	glutDisplayFunc(drawScene); // ��� �Լ��� ����
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);
	glutPassiveMotionFunc(Motion);
	glutTimerFunc(100, TimerFunction, 1);
	glutTimerFunc(10, StarRotationTimerFunction, 1);
	glutMainLoop();
}
// ������ ��� �Լ�
GLvoid drawScene(GLvoid)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if(rotate)
		glRotated(rt, rt_x, rt_y, rt_z);
	gluLookAt(cx, cy + 10, cz + 10, 0.0 + cx, 0.0 + cy, 0.0 + cz, 0.0, 1.0, 0.0);

	/*
	glColor3f(0.0, 0.0, 1.0);
	if (model)
		glutSolidSphere(60, 30, 30);
	else 
		glutWireSphere(60, 20, 20);
	*/

	//�¾�
	glPushMatrix();
	glTranslated(Sun.xPos, Sun.yPos, Sun.zPos);
	glRotated(Sun.Rotation, 0, 1, 0);
	glColor3b(Sun.RGB[0], Sun.RGB[1], Sun.RGB[2]);
	glutSolidSphere(Sun.Radius, 30, 30);
	glColor3f(1, 1, 1);
	glutWireSphere(Sun.Radius+10, 15, 15);
	glPopMatrix();

	//����
	glPushMatrix();
	glRotated(Mercury.Revolution, 0, 1, 0);
	glTranslated(Mercury.xPos, Mercury.yPos, Mercury.zPos);
	glRotated(Mercury.Rotation, 0, 1, 0);
	glColor3b(Mercury.RGB[0], Mercury.RGB[1], Mercury.RGB[2]);
	glutSolidSphere(Mercury.Radius, 30, 30);
	glColor3f(1, 1, 1);
	glutWireSphere(Mercury.Radius + 10, 15, 15);
	glPopMatrix();

	//�ݼ�
	glPushMatrix();
	glRotated(Venus.Revolution, 0, 1, 0);
	glTranslated(Venus.xPos, Venus.yPos, Venus.zPos);
	glRotated(Venus.Rotation, 0, 1, 0);
	glColor3b(Venus.RGB[0], Venus.RGB[1], Venus.RGB[2]);
	glutSolidSphere(Venus.Radius, 30, 30);
	glColor3f(1, 1, 1);
	glutWireSphere(Venus.Radius + 10, 15, 15);
	glPopMatrix();

	//����
	glPushMatrix();
	glRotated(Earth.Revolution, 0, 1, 0);
	glTranslated(Earth.xPos, Earth.yPos, Earth.zPos);
	glRotated(Earth.Rotation, 0, 1, 0);
	glColor3b(Earth.RGB[0], Earth.RGB[1], Earth.RGB[2]);
	glutSolidSphere(Earth.Radius, 30, 30);
	glColor3f(1, 1, 1);
	glutWireSphere(Earth.Radius + 10, 15, 15);
	glPopMatrix();

	//ȭ��
	glPushMatrix();
	glRotated(Mars.Revolution, 0, 1, 0);
	glTranslated(Mars.xPos, Mars.yPos, Mars.zPos);
	glRotated(Mars.Rotation, 0, 1, 0);
	glColor3b(Mars.RGB[0], Mars.RGB[1], Mars.RGB[2]);
	glutSolidSphere(Mars.Radius, 30, 30);
	glColor3f(1, 1, 1);
	glutWireSphere(Mars.Radius + 10, 15, 15);
	glPopMatrix();

	//��
	glPushMatrix();
	glRotated(Jupiter.Revolution, 0, 1, 0);
	glTranslated(Jupiter.xPos, Jupiter.yPos, Jupiter.zPos);
	glRotated(Jupiter.Rotation, 0, 1, 0);
	glColor3b(Jupiter.RGB[0], Jupiter.RGB[1], Jupiter.RGB[2]);
	glutSolidSphere(Jupiter.Radius, 30, 30);
	glColor3f(1, 1, 1);
	glutWireSphere(Jupiter.Radius + 10, 15, 15);
	glPopMatrix();

	//�伺
	glPushMatrix();
	glRotated(Saturn.Revolution, 0, 1, 0);
	glTranslated(Saturn.xPos, Saturn.yPos, Saturn.zPos);
	glRotated(Saturn.Rotation, 0, 1, 0);
	glColor3b(Saturn.RGB[0], Saturn.RGB[1], Saturn.RGB[2]);
	glutSolidSphere(Saturn.Radius, 30, 30);
	glColor3f(1, 1, 1);
	glutWireSphere(Saturn.Radius, 30, 30);
	glPopMatrix();

	//õ�ռ�
	glPushMatrix();
	glRotated(Uranus.Revolution, 0, 1, 0);
	glTranslated(Uranus.xPos, Uranus.yPos, Uranus.zPos);
	glRotated(Uranus.Rotation, 0, 1, 0);
	glColor3b(Uranus.RGB[0], Uranus.RGB[1], Uranus.RGB[2]);
	glutSolidSphere(Uranus.Radius, 30, 30);
	glColor3f(1, 1, 1);
	glutWireSphere(Uranus.Radius, 30, 30);
	glPopMatrix();

	//�ؿռ�
	glPushMatrix();
	glRotated(Neptune.Revolution, 0, 1, 0);
	glTranslated(Neptune.xPos, Neptune.yPos, Neptune.zPos);
	glRotated(Neptune.Rotation, 0, 1, 0);
	glColor3b(Neptune.RGB[0], Neptune.RGB[1], Neptune.RGB[2]);
	glutSolidSphere(Neptune.Radius, 30, 30);
	glColor3f(1, 1, 1);
	glutWireSphere(Neptune.Radius, 30, 30);
	glPopMatrix();


	/*
	//�˵�
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
	
	//ū ������
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
	//���� ������
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
	//glFlush(); // ȭ�鿡 ����ϱ�
}
GLvoid Reshape(int w, int h)
{
	//����Ʈ ��ȯ ����
	glViewport(0, 0, w, h);

	// ���� ��� ���� �缳��
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//-- ������ ���� ���� �Ǵ� ���� ���� �� �� ���� �����Ѵ�.
	// 1. Ŭ���� ���� ����: ���� ������ ���
	gluPerspective(60.0f, (double)w / (double)h, 1.0, 10000.0);
	glFrustum(SCREEN_WIDTH_MIN, SCREEN_WIDTH_MAX, SCREEN_HEIGHT_MIN, SCREEN_HEIGHT_MAX, SCREEN_DEPTH_MIN, SCREEN_DEPTH_MAX);
	glTranslatef(0.0, 0.0, -2000.0); // ���� ������ ȭ�� �������� �̵��Ͽ� �þ߸� Ȯ���Ѵ�.

	// 2. Ŭ���� ���� ����: ���� ������ ���
	//glOrtho(-400.0, 400.0, -300.0, 300.0, -400.0, 400.0);

	// �� �� ��� ���� �缳��
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
		Speed *= 10;
		break;
	case '-':
		Speed /= 10;
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
	case 'Q': //����
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
	glutPostRedisplay(); // ȭ�� �� ���
	glutTimerFunc(10, TimerFunction, 1); // Ÿ�̸��Լ� �� ����
}
void StarRotationTimerFunction(int value) {
	if (Sun.Rotation < 360)
		Sun.Rotation += STAR_ROTATION_HOUR_PER_mSECOND / Sun.Rotation_Cycle * Speed;
	else
		Sun.Rotation = 0;
	//
	if (Mercury.Rotation < 360)
		Mercury.Rotation += STAR_ROTATION_HOUR_PER_mSECOND/ Mercury.Roation_Cycle * Speed;
	else
		Mercury.Rotation = 0;
	if (Mercury.Revolution < 360)
		Mercury.Revolution += STAR_ROTATION_HOUR_PER_mSECOND / Mercury.Revolution_Cycle * Speed;
	else
		Mercury.Revolution = 0;
	//
	if (Venus.Rotation < 360)
		Venus.Rotation += STAR_ROTATION_HOUR_PER_mSECOND / Venus.Roation_Cycle * Speed;
	else
		Venus.Rotation = 0;
	if (Venus.Revolution < 360)
		Venus.Revolution += STAR_ROTATION_HOUR_PER_mSECOND / Venus.Revolution_Cycle * Speed;
	else
		Venus.Revolution = 0;
	//
	if (Earth.Rotation < 360)
		Earth.Rotation += STAR_ROTATION_HOUR_PER_mSECOND / Earth.Roation_Cycle * Speed;
	else
		Earth.Rotation = 0;
	if (Earth.Revolution < 360)
		Earth.Revolution += STAR_ROTATION_HOUR_PER_mSECOND / Earth.Revolution_Cycle * Speed;
	else
		Earth.Revolution = 0;
	//
	if (Mars.Rotation < 360)
		Mars.Rotation += STAR_ROTATION_HOUR_PER_mSECOND / Mars.Roation_Cycle * Speed;
	else
		Mars.Rotation = 0;
	if (Mars.Revolution < 360)
		Mars.Revolution += STAR_ROTATION_HOUR_PER_mSECOND / Mars.Revolution_Cycle * Speed;
	else
		Mars.Revolution = 0;
	//
	if (Jupiter.Rotation < 360)
		Jupiter.Rotation += STAR_ROTATION_HOUR_PER_mSECOND / Jupiter.Roation_Cycle * Speed;
	else
		Jupiter.Rotation = 0;
	if (Jupiter.Revolution < 360)
		Jupiter.Revolution += STAR_ROTATION_HOUR_PER_mSECOND / Jupiter.Revolution_Cycle * Speed;
	else
		Jupiter.Revolution = 0;
	//
	if (Saturn.Rotation < 360)
		Saturn.Rotation += STAR_ROTATION_HOUR_PER_mSECOND / Saturn.Roation_Cycle * Speed;
	else
		Saturn.Rotation = 0;
	if (Saturn.Revolution < 360)
		Saturn.Revolution += STAR_ROTATION_HOUR_PER_mSECOND / Saturn.Revolution_Cycle * Speed;
	else
		Saturn.Revolution = 0;
	//
	if (Uranus.Rotation < 360)
		Uranus.Rotation += STAR_ROTATION_HOUR_PER_mSECOND / Uranus.Roation_Cycle * Speed;
	else
		Uranus.Rotation = 0;
	if (Uranus.Revolution < 360)
		Uranus.Revolution += STAR_ROTATION_HOUR_PER_mSECOND / Uranus.Revolution_Cycle * Speed;
	else
		Uranus.Revolution = 0;
	//
	if (Neptune.Rotation < 360)
		Neptune.Rotation += STAR_ROTATION_HOUR_PER_mSECOND / Neptune.Roation_Cycle * Speed;
	else
		Neptune.Rotation = 0;
	if (Neptune.Revolution < 360)
		Neptune.Revolution += STAR_ROTATION_HOUR_PER_mSECOND / Neptune.Revolution_Cycle * Speed;
	else
		Neptune.Revolution = 0;
	//
	if (rt > -360)
		rt--;
	else
		rt = 0;

	glutPostRedisplay(); // ȭ�� �� ���
	glutTimerFunc(10, StarRotationTimerFunction, 1); // Ÿ�̸��Լ� �� ����
}