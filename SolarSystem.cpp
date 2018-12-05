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
#include "Camera.h"

struct Orbit {
	double x, z;
	double degree = 0;
};
Orbit Coor[2], Circle[3], Moon[3];

//ī�޶� ���� ���� ����
int rt_x = 0, rt_y = 0, rt_z = 0, rt = 0, l_rt = 0, r_rt = 0, c_rt = 0;
double cx = 0, cy = 0, cz = 0, big_radian = 200, small_radian = 70, circle_x, circle_z;

//������ ���� ����
int ww = 1600, wh = 900;

//���콺 ���� ����
double ox, oy; //Ŭ���� ��ǥ
double mx, my; //���콺 ������ ��ǥ

//�༺ ����
double Speed = 100;
double loop_x, loop_z;

//bool Ʈ����
bool rotate = false, c_rotate = true, reverse = false;
bool projection = true, model = true;
bool drag = false, wheel_drag = false;

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Mouse(int button, int state, int x, int y);
void MouseWheel(int button, int dir, int x, int y);
void Keyboard(unsigned char key, int x, int y);
void Motion(int x, int y);
void Fix_Camera(void);
void set_at(void);
void StarRotationTimerFunction(int value);
void TimerFunction(int value);
void mul(double m1, double m2, double m3);
double get_dist(double sx, double sy, double sz, double dx, double dy, double dz);
double abs(double x)
{
	return (x > 0) ? x : -x;
}

//���콺 �����ӿ� ���� translate ó�� �Լ�
void MouseTranslated(void);

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
	glutMouseWheelFunc(MouseWheel);
	glutMotionFunc(Motion);
	glutTimerFunc(100, TimerFunction, 1);
	glutTimerFunc(10, StarRotationTimerFunction, 1);
	glutMainLoop();
}
// ������ ��� �Լ�
GLvoid drawScene(GLvoid)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glLoadIdentity();

	glMatrixMode(GL_PROJECTION);
	MouseTranslated();
	Reshape(ww, wh);
	mul(Camera.rtx, Camera.rty, Camera.rtz);//ī�޶� ȸ�� ��ȯ
	//glRotated(Camera.rtx, 1, 0, 0);
	//glRotated(Camera.rty, 0, 1, 0);
	//glRotated(Camera.rtz, 0, 0, 1);
	//ī�޶� �̵� ��ȯ
	glTranslated(Camera.mvx, Camera.mvy, Camera.mvz);
	
	//Camera.invalidate_values();
	//ī�޶� EYE, AY, UP ���ͷ� ���� ����
	glMatrixMode(GL_MODELVIEW);

	Fix_Camera();//���� ���� ��, �Լ� �����
	gluLookAt(Camera.EYEx, Camera.EYEy, Camera.EYEz,
		Camera.ATx, Camera.ATy, Camera.ATz,
		Camera.UPx, Camera.UPy, Camera.UPz);

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
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 360; i++) {
		loop_x = Mercury.xPos * cos(Mercury.Orbit_Degree * PI / 180);
		loop_z = Mercury.xPos * sin(Mercury.Orbit_Degree * PI / 180);
		glVertex3f(loop_x, 0, loop_z);
		Mercury.Orbit_Degree++;
	}
	glEnd();
	Mercury.Orbit_Degree = 0;
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
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 360; i++) {
		loop_x = Venus.xPos * cos(Venus.Orbit_Degree * PI / 180);
		loop_z = Venus.xPos * sin(Venus.Orbit_Degree * PI / 180);
		glVertex3f(loop_x, 0, loop_z);
		Venus.Orbit_Degree++;
	}
	glEnd();
	Venus.Orbit_Degree = 0;
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
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 360; i++) {
		loop_x = Earth.xPos * cos(Earth.Orbit_Degree * PI / 180);
		loop_z = Earth.xPos * sin(Earth.Orbit_Degree * PI / 180);
		glVertex3f(loop_x, 0, loop_z);
		Earth.Orbit_Degree++;
	}
	glEnd();
	Earth.Orbit_Degree = 0;
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
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 360; i++) {
		loop_x = Mars.xPos * cos(Mars.Orbit_Degree * PI / 180);
		loop_z = Mars.xPos * sin(Mars.Orbit_Degree * PI / 180);
		glVertex3f(loop_x, 0, loop_z);
		Mars.Orbit_Degree++;
	}
	glEnd();
	Mars.Orbit_Degree = 0;
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
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 360; i++) {
		loop_x = Jupiter.xPos * cos(Jupiter.Orbit_Degree * PI / 180);
		loop_z = Jupiter.xPos * sin(Jupiter.Orbit_Degree * PI / 180);
		glVertex3f(loop_x, 0, loop_z);
		Jupiter.Orbit_Degree++;
	}
	glEnd();
	Jupiter.Orbit_Degree = 0;
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
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 360; i++) {
		loop_x = Saturn.xPos * cos(Saturn.Orbit_Degree * PI / 180);
		loop_z = Saturn.xPos * sin(Saturn.Orbit_Degree * PI / 180);
		glVertex3f(loop_x, 0, loop_z);
		Saturn.Orbit_Degree++;
	}
	glEnd();
	Saturn.Orbit_Degree = 0;
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
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 360; i++) {
		loop_x = Uranus.xPos * cos(Uranus.Orbit_Degree * PI / 180);
		loop_z = Uranus.xPos * sin(Uranus.Orbit_Degree * PI / 180);
		glVertex3f(loop_x, 0, loop_z);
		Uranus.Orbit_Degree++;
	}
	glEnd();
	Uranus.Orbit_Degree = 0;
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
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 360; i++) {
		loop_x = Neptune.xPos * cos(Neptune.Orbit_Degree * PI / 180);
		loop_z = Neptune.xPos * sin(Neptune.Orbit_Degree * PI / 180);
		glVertex3f(loop_x, 0, loop_z);
		Neptune.Orbit_Degree++;
	}
	glEnd();
	Neptune.Orbit_Degree = 0;
	glRotated(Neptune.Revolution, 0, 1, 0);
	glTranslated(Neptune.xPos, Neptune.yPos, Neptune.zPos);
	glRotated(Neptune.Rotation, 0, 1, 0);
	glColor3b(Neptune.RGB[0], Neptune.RGB[1], Neptune.RGB[2]);
	glutSolidSphere(Neptune.Radius, 30, 30);
	glColor3f(1, 1, 1);
	glutWireSphere(Neptune.Radius, 30, 30);
	glPopMatrix();


	glutSwapBuffers();
	//glFlush(); // ȭ�鿡 ����ϱ�
}
GLvoid Reshape(int w, int h)
{
	//ȭ���� �ʱ�ȭ �ϱ� ���ؼ��� �ۿ��� reshape�� �ҷ�����.
	//�ۿ����� reshape�� �θ��� ���� �������� w, h �ʱ�ȭ
	ww = w, wh = h;

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
		drag = true;
		ox = x; oy = y;
		mx = x; my = y;
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		drag = false;
	}
	else if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) {
		wheel_drag = true;
		ox = x; oy = y;
		mx = x; my = y;
	}
	else if (button == GLUT_MIDDLE_BUTTON && state == GLUT_UP) {
		wheel_drag = false;
	}
	glutPostRedisplay();
}
void MouseWheel(int button, int dir, int x, int y) {
	double dist = get_dist(400, 400, 0, x, y, 0);
	int dx = 800 - x; int dy = y - 450;
	if (dir > 0) {
		Camera.move_front(CAMERA_MOVE * 3);
		if (dist != 0 && Camera.view_type() != 'N') {
			if(dx != 0)Camera.move_right(dx * CAMERA_MOVE * 3 / dist);
			if(dy != 0)Camera.move_up(dy * CAMERA_MOVE * 3 / dist);
		}
	}
	else {
		Camera.move_back(CAMERA_MOVE * 3);
	}
}
void Motion(int x, int y) {
	if (drag) {
		mx = x; my = y;
	}
	else if (wheel_drag) {
		mx = x; my = y;
	}
}
void Keyboard(unsigned char key, int x, int y)
{
	char Camera_Type = Camera.view_type();
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
		if (Camera_Type == 'N') return;
		Camera.move_up(CAMERA_MOVE);
		break;
	case 'a':
		if (Camera_Type == 'N') return;
		Camera.move_left(CAMERA_MOVE);
		break;
	case 's':
		if (Camera_Type == 'N') return;
		Camera.move_down(CAMERA_MOVE);
		break;
	case 'd':
		if (Camera_Type == 'N') return;
		Camera.move_right(CAMERA_MOVE);
		break;
	case 't':case 'T':
		Camera.Planet_Selection = 0;
		Camera.invalidate_values();
		Camera.set_pos(0, 900, 0);
		break;
	case 'f':case 'F':
		Camera.Planet_Selection = 0;
		Camera.invalidate_values();
		Camera.set_pos(0, 0, 1600);
		break;
	case '1'://�¾�
		Camera.Planet_Selection = 1;
		Camera.invalidate_values();
		Camera.set_pos(0, 0, 0);
		Camera.move_front(2000 - Sun.Radius * 2);
		break;
	case '2'://����
		Camera.Planet_Selection = 2;
		Camera.invalidate_values();
		Camera.set_pos(0, 0, 0);
		Camera.move_front(2000 - Mercury.Radius * 2);
		break;
	case '3'://�ݼ�
		Camera.Planet_Selection = 3;
		Camera.invalidate_values();
		Camera.set_pos(0, 0, 0);
		Camera.move_front(2000 - Venus.Radius * 2);
		break;
	case '4'://����
		Camera.Planet_Selection = 4;
		Camera.invalidate_values();
		Camera.set_pos(0, 0, 0);
		Camera.move_front(2000 - Earth.Radius * 2);
		break;
	case '5'://ȭ��
		Camera.Planet_Selection = 5;
		Camera.invalidate_values();
		Camera.set_pos(0, 0, 0);
		Camera.move_front(2000 - Mars.Radius * 2);
		break;
	case '6'://��
		Camera.Planet_Selection = 6;
		Camera.invalidate_values();
		Camera.set_pos(0, 0, 0);
		Camera.move_front(2000 - Jupiter.Radius * 2);
		break;
	case '7'://�伺
		Camera.Planet_Selection = 7;
		Camera.invalidate_values();
		Camera.set_pos(0, 0, 0);
		Camera.move_front(2000 - Saturn.Radius * 2);
		break;
	case '8'://õ�ռ�
		Camera.Planet_Selection = 8;
		Camera.invalidate_values();
		Camera.set_pos(0, 0, 0);
		Camera.move_front(2000 - Uranus.Radius * 2);
		break;
	case '9'://�ؿռ�
		Camera.Planet_Selection = 9;
		Camera.invalidate_values();
		Camera.set_pos(0, 0, 0);
		Camera.move_front(2000 - Neptune.Radius * 2);
		break;
	case '+':
		Speed *= 10;
		break;
	case '-':
		Speed /= 10;
		break;
	case 'i':
		Camera.invalidate_values();
		break;
	case 'r':
		if (Camera_Type == 'N') return;
		Camera.rotatez(CAMERA_MOVE / 2.0);
		break;
	case 'R':
		if (Camera_Type == 'N') return;
		Camera.rotatez(-CAMERA_MOVE / 2.0);
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
	if(Camera.view_type() == 'N')

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
void MouseTranslated(void)
{
	static double tx, ty;
	if (ox == mx && oy == my)
		return;
	int dx = mx - ox; int dy = my - oy;

	if (wheel_drag) {
		Camera.EYEx += dx;
		Camera.EYEy -= dy;
		Camera.ATx += dx;
		Camera.ATy -= dy;
	}
	else if (drag) {
		Camera.rty -= dx / 10.0;
		Camera.rtx -= dy / 10.0;
		tx += Camera.rtx, ty += Camera.rty;
	}

	ox = mx, oy = my;
}
void Fix_Camera(void)
{
	if (Camera.view_type() != 'N')return;

	double eyex, eyey, eyez;
	double ratio_c, ratio_s;

	switch (Camera.Planet_Selection)
	{
	case 1:
		eyex = Sun.xPos - Sun.Radius;
		eyey = Sun.yPos + Sun.Radius;
		eyez = Sun.zPos;
		Camera.set_pos(eyex, eyey, eyez);
		break;
	case 2://
		ratio_c = cos(Mercury.Revolution * PI / 180);
		ratio_s = sin(-Mercury.Revolution * PI / 180);
		eyex = (Mercury.xPos - Mercury.Radius) * ratio_c ;
		eyey = Mercury.yPos;
		eyez = (Mercury.xPos - Mercury.Radius) * ratio_s ;
		Camera.set_pos(eyex, eyey + Mercury.Radius / 3.0 , eyez - Mercury.Radius);
		Camera.set_at(eyex, eyey, eyez);
		break;
	case 3:
		ratio_c = cos(Venus.Revolution * PI / 180);
		ratio_s = sin(-Venus.Revolution * PI / 180);
		eyex = (Venus.xPos - Venus.Radius)* ratio_c;
		eyey = Venus.yPos;
		eyez = (Venus.xPos - Venus.Radius) * ratio_s;
		Camera.set_pos(eyex, eyey + Venus.Radius / 3.0, eyez - Venus.Radius);
		Camera.set_at(eyex, eyey, eyez);
		break;
	case 4:
		ratio_c = cos(Earth.Revolution * PI / 180);
		ratio_s = sin(-Earth.Revolution * PI / 180);
		eyex = (Earth.xPos - Earth.Radius)* ratio_c;
		eyey = Earth.yPos;
		eyez = (Earth.xPos - Earth.Radius) * ratio_s;
		Camera.set_pos(eyex, eyey + Earth.Radius / 3.0, eyez - Earth.Radius);
		Camera.set_at(eyex, eyey, eyez);
		break;
	case 5:
		ratio_c = cos(Mars.Revolution * PI / 180);
		ratio_s = sin(-Mars.Revolution * PI / 180);
		eyex = (Mars.xPos - Mars.Radius)* ratio_c;
		eyey = Mars.yPos + Mars.Radius;
		eyez = (Mars.xPos - Mars.Radius) * ratio_s;
		Camera.set_pos(eyex, eyey + Mars.Radius / 3.0, eyez - Mars.Radius);
		Camera.set_at(eyex, eyey, eyez);
		break;
	case 6:
		ratio_c = cos(Jupiter.Revolution * PI / 180);
		ratio_s = sin(-Jupiter.Revolution * PI / 180);
		eyex = (Jupiter.xPos - Jupiter.Radius)* ratio_c;
		eyey = Jupiter.yPos + Jupiter.Radius;
		eyez = (Jupiter.xPos - Jupiter.Radius) * ratio_s;
		Camera.set_pos(eyex, eyey + Jupiter.Radius / 3.0, eyez - Jupiter.Radius);
		Camera.set_at(eyex, eyey, eyez);
		break;
	case 7:
		ratio_c = cos(Saturn.Revolution * PI / 180);
		ratio_s = sin(-Saturn.Revolution * PI / 180);
		eyex = (Saturn.xPos - Saturn.Radius)* ratio_c;
		eyey = Saturn.yPos + Saturn.Radius;
		eyez = (Saturn.xPos - Saturn.Radius) * ratio_s;
		Camera.set_pos(eyex, eyey + Saturn.Radius / 3.0, eyez - Saturn.Radius);
		Camera.set_at(eyex, eyey, eyez);
		break;
	case 8:
		ratio_c = cos(Uranus.Revolution * PI / 180);
		ratio_s = sin(-Uranus.Revolution * PI / 180);
		eyex = (Uranus.xPos - Uranus.Radius)* ratio_c;
		eyey = Uranus.yPos + Uranus.Radius;
		eyez = (Uranus.xPos - Uranus.Radius) * ratio_s;
		Camera.set_pos(eyex, eyey + Uranus.Radius / 3.0, eyez - Uranus.Radius);
		Camera.set_at(eyex, eyey, eyez);
		break;
	case 9:
		ratio_c = cos(Neptune.Revolution * PI / 180);
		ratio_s = sin(-Neptune.Revolution * PI / 180);
		eyex = (Neptune.xPos - Neptune.Radius)* ratio_c;
		eyey = Neptune.yPos + Neptune.Radius;
		eyez = (Neptune.xPos - Neptune.Radius) * ratio_s;
		Camera.set_pos(eyex, eyey + Neptune.Radius / 3.0, eyez - Neptune.Radius);
		Camera.set_at(eyex, eyey, eyez);
		break;
	}
}
void StarRotationTimerFunction(int value) {
	if (Sun.Rotation < 360)
		Sun.Rotation += STAR_ROTATION_HOUR_PER_mSECOND / Sun.Rotation_Cycle * Speed;
	else
		Sun.Rotation = 0;
	//����
	if (Mercury.Rotation < 360)
		Mercury.Rotation += STAR_ROTATION_HOUR_PER_mSECOND/ Mercury.Roation_Cycle * Speed;
	else
		Mercury.Rotation = 0;
	if (Mercury.Revolution < 360)
		Mercury.Revolution += STAR_ROTATION_HOUR_PER_mSECOND / Mercury.Revolution_Cycle * Speed;
	else
		Mercury.Revolution = 0;
	//�ݼ�
	if (Venus.Rotation < 360)
		Venus.Rotation += STAR_ROTATION_HOUR_PER_mSECOND / Venus.Roation_Cycle * Speed;
	else
		Venus.Rotation = 0;
	if (Venus.Revolution < 360)
		Venus.Revolution += STAR_ROTATION_HOUR_PER_mSECOND / Venus.Revolution_Cycle * Speed;
	else
		Venus.Revolution = 0;
	//����
	if (Earth.Rotation < 360)
		Earth.Rotation += STAR_ROTATION_HOUR_PER_mSECOND / Earth.Roation_Cycle * Speed;
	else
		Earth.Rotation = 0;
	if (Earth.Revolution < 360)
		Earth.Revolution += STAR_ROTATION_HOUR_PER_mSECOND / Earth.Revolution_Cycle * Speed;
	else
		Earth.Revolution = 0;
	//ȭ��
	if (Mars.Rotation < 360)
		Mars.Rotation += STAR_ROTATION_HOUR_PER_mSECOND / Mars.Roation_Cycle * Speed;
	else
		Mars.Rotation = 0;
	if (Mars.Revolution < 360)
		Mars.Revolution += STAR_ROTATION_HOUR_PER_mSECOND / Mars.Revolution_Cycle * Speed;
	else
		Mars.Revolution = 0;
	//��
	if (Jupiter.Rotation < 360)
		Jupiter.Rotation += STAR_ROTATION_HOUR_PER_mSECOND / Jupiter.Roation_Cycle * Speed;
	else
		Jupiter.Rotation = 0;
	if (Jupiter.Revolution < 360)
		Jupiter.Revolution += STAR_ROTATION_HOUR_PER_mSECOND / Jupiter.Revolution_Cycle * Speed;
	else
		Jupiter.Revolution = 0;
	//�伺
	if (Saturn.Rotation < 360)
		Saturn.Rotation += STAR_ROTATION_HOUR_PER_mSECOND / Saturn.Roation_Cycle * Speed;
	else
		Saturn.Rotation = 0;
	if (Saturn.Revolution < 360)
		Saturn.Revolution += STAR_ROTATION_HOUR_PER_mSECOND / Saturn.Revolution_Cycle * Speed;
	else
		Saturn.Revolution = 0;
	//õ�ռ�
	if (Uranus.Rotation < 360)
		Uranus.Rotation += STAR_ROTATION_HOUR_PER_mSECOND / Uranus.Roation_Cycle * Speed;
	else
		Uranus.Rotation = 0;
	if (Uranus.Revolution < 360)
		Uranus.Revolution += STAR_ROTATION_HOUR_PER_mSECOND / Uranus.Revolution_Cycle * Speed;
	else
		Uranus.Revolution = 0;
	//�ؿռ�
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
void mul(double x, double y, double z)
{
	glTranslated(0, 0, 2000.0);
	double rrx = x * PI / 180, rry = y * PI / 180, rrz = z * PI / 180;

	GLdouble m1[16] = {
		1, 0, 0, 0,
		0, cos(rrx), sin(rrx), 0,
		0, -sin(rrx), cos(rrx), 0,
		0, 0, 0, 1
	};
	GLdouble m2[16] = {
		cos(rry), 0, -sin(rry), 0,
		0, 1, 0, 0,
		sin(rry), 0, cos(rry), 0,
		0, 0, 0, 1
	};
	GLdouble m3[16] = {
		cos(rrz), sin(rrz), 0, 0,
		-sin(rrz), cos(rrz), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};
	GLdouble tmp[16] = {
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0
	};
	GLdouble total[16] = {
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0
	};

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				tmp[i * 4 + j] += m1[i * 4 + k] * m2[k * 4 + j];
			}
		}
	}
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				total[i * 4 + j] += m3[i * 4 + k] * tmp[k * 4 + j];
			}
		}
	}

	glMultMatrixd(total);
	glTranslated(0, 0, -2000.0);
}
double get_dist(double sx, double sy, double sz, double dx, double dy, double dz)
{
	return sqrt((sx - dx)*(sx - dx) + (sy - dy)*(sy - dy) + (sz - dz)*(sz - dz));
}