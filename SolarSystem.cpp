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

#define TEXTURE_NUMBER 9

struct XYZ {
	double x, y, z;
}C;
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
GLubyte *pBytes; // �����͸� ����ų ������
BITMAPINFO *info; // ��Ʈ�� ��� ������ ����
GLubyte * TexBits;
GLuint textures[TEXTURE_NUMBER];
GLubyte * LoadDIBitMap(const char *filename, BITMAPINFO **info)
{
	FILE *fp;
	GLubyte *bits;
	int bitsize, infosize;
	BITMAPFILEHEADER header;
	// ���̳ʸ� �б� ���� ������ ����
	if ((fp = fopen(filename, "rb")) == NULL)
		return NULL;
	// ��Ʈ�� ���� ����� �д´�.
	if (fread(&header, sizeof(BITMAPFILEHEADER), 1, fp) < 1) {
		fclose(fp);
		return NULL;
	}
	// ������ BMP �������� Ȯ���Ѵ�.
	if (header.bfType != 'MB') {
		fclose(fp);
		return NULL;
	}
	// BITMAPINFOHEADER ��ġ�� ����.
	infosize = header.bfOffBits - sizeof(BITMAPFILEHEADER);
	// ��Ʈ�� �̹��� �����͸� ���� �޸� �Ҵ��� �Ѵ�.
	if ((*info = (BITMAPINFO *)malloc(infosize)) == NULL) {
		fclose(fp);
		exit(0);
		return NULL;
	}
	// ��Ʈ�� ���� ����� �д´�.
	if (fread(*info, 1, infosize, fp) < (unsigned int)infosize) {
		free(*info);
		fclose(fp);
		return NULL;
	}
	// ��Ʈ���� ũ�� ����
	if ((bitsize = (*info)->bmiHeader.biSizeImage) == 0)
		bitsize = ((*info)->bmiHeader.biWidth*(*info)->bmiHeader.biBitCount + 7) / 8.0 * abs((*info)->bmiHeader.biHeight);
	// ��Ʈ���� ũ�⸸ŭ �޸𸮸� �Ҵ��Ѵ�.
	if ((bits = (unsigned char *)malloc(bitsize)) == NULL) {
		free(*info);
		fclose(fp);
		return NULL;
	}
	// ��Ʈ�� �����͸� bit(GLubyte Ÿ��)�� �����Ѵ�.
	if (fread(bits, 1, bitsize, fp) < (unsigned int)bitsize) {
		free(*info); free(bits);
		fclose(fp);
		return NULL;
	}
	fclose(fp);
	return bits;
}
void initTextures() {
	glGenTextures(TEXTURE_NUMBER, textures); //�ؽ�ó �̸��� �����Ѵ�. n:�����Ǿ���� �ؽ�ó�̸��� �� 

	glBindTexture(GL_TEXTURE_2D, textures[0]); // �ؽ�ó�� �� ��ü�� �ؽ�ó�� �������ش�.
	pBytes = LoadDIBitMap("Sun.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 2048, 1024, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
	
	glBindTexture(GL_TEXTURE_2D, textures[1]);
	pBytes = LoadDIBitMap("Mercury.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 2048, 1024, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, textures[2]);
	pBytes = LoadDIBitMap("Venus.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 2048, 1024, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
	
	glBindTexture(GL_TEXTURE_2D, textures[3]);
	pBytes = LoadDIBitMap("Earth.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 2048, 1024, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, textures[4]);
	pBytes = LoadDIBitMap("Mars.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 2048, 1024, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, textures[5]);
	pBytes = LoadDIBitMap("Jupiter.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 2048, 1024, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, textures[6]);
	pBytes = LoadDIBitMap("Saturn.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 2048, 1024, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, textures[7]);
	pBytes = LoadDIBitMap("Uranus.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 2048, 1024, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, textures[8]);
	pBytes = LoadDIBitMap("Neptune.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 2048, 1024, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
}
void Mouse(int button, int state, int x, int y);
void MouseWheel(int button, int dir, int x, int y);
void Keyboard(unsigned char key, int x, int y);
void Motion(int x, int y);
void Fix_Camera(void);
void Show_Info(void);
void StarRotationTimerFunction(int value);
void TimerFunction(int value);
void mul(double m1, double m2, double m3);
double get_dist(double sx, double sy, double sz, double dx, double dy, double dz);
double abs(double x)
{
	return (x > 0) ? x : -x;
}

void CreateSphere(XYZ c, double r, int n);

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
	initTextures();
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

	////////////////////////////////////////////
	Show_Info();	
	///////////////////////////////////////////

	glColor3f(1, 1, 1);

	//�¾�
	glPushMatrix();
	glTranslated(Sun.xPos, Sun.yPos, Sun.zPos);
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	glRotated(Sun.Rotation, 0, 1, 0);
	//glColor3b(Sun.RGB[0], Sun.RGB[1], Sun.RGB[2]);
	//C.x = Sun.xPos, C.y = Sun.yPos, C.z = Sun.zPos;
	CreateSphere(C, Sun.Radius, 128);
	//glutSolidSphere(Sun.Radius, 128, 128);
	
	//glColor3f(1, 1, 1);
	//glutWireSphere(Sun.Radius+10, 15, 15);
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
	glBindTexture(GL_TEXTURE_2D, textures[1]);
	glRotated(Mercury.Revolution, 0, 1, 0);
	glTranslated(Mercury.xPos, Mercury.yPos, Mercury.zPos);
	glRotated(Mercury.Rotation, 0, 1, 0);
	//glColor3b(Mercury.RGB[0], Mercury.RGB[1], Mercury.RGB[2]);
	//C.x = Mercury.xPos, C.y = Mercury.yPos, C.z = Mercury.zPos;
	CreateSphere(C, Mercury.Radius, 128);
	//glutSolidSphere(Mercury.Radius, 128, 128);
	
	//glColor3f(1, 1, 1);
	//glutWireSphere(Mercury.Radius + 10, 15, 15);
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
	glBindTexture(GL_TEXTURE_2D, textures[2]);
	glRotated(Venus.Revolution, 0, 1, 0);
	glTranslated(Venus.xPos, Venus.yPos, Venus.zPos);
	glRotated(Venus.Rotation, 0, 1, 0);
	//glColor3b(Venus.RGB[0], Venus.RGB[1], Venus.RGB[2]);
	//C.x = Venus.xPos, C.y = Venus.yPos, C.z = Venus.zPos;
	CreateSphere(C, Venus.Radius, 128);
	//glutSolidSphere(Venus.Radius, 128, 128);
	//glColor3f(1, 1, 1);
	//glutWireSphere(Venus.Radius + 10, 15, 15);
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
	glBindTexture(GL_TEXTURE_2D, textures[3]);
	glRotated(Earth.Revolution, 0, 1, 0);
	glTranslated(Earth.xPos, Earth.yPos, Earth.zPos);
	glRotated(Earth.Rotation, 0, 1, 0);
	//glColor3b(Earth.RGB[0], Earth.RGB[1], Earth.RGB[2]);
	//C.x = Earth.xPos, C.y = Earth.yPos, C.z = Earth.zPos;
	CreateSphere(C, Earth.Radius, 128);
	//glutSolidSphere(Earth.Radius, 128, 128);
	//glColor3f(1, 1, 1);
	//glutWireSphere(Earth.Radius + 10, 15, 15);
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
	glBindTexture(GL_TEXTURE_2D, textures[4]);
	glRotated(Mars.Revolution, 0, 1, 0);
	glTranslated(Mars.xPos, Mars.yPos, Mars.zPos);
	glRotated(Mars.Rotation, 0, 1, 0);
	//glColor3b(Mars.RGB[0], Mars.RGB[1], Mars.RGB[2]);
	//C.x = Mars.xPos, C.y = Mars.yPos, C.z = Mars.zPos;
	CreateSphere(C, Mars.Radius, 128);
	//glutSolidSphere(Mars.Radius, 128, 128);
	//glColor3f(1, 1, 1);
	//glutWireSphere(Mars.Radius + 10, 15, 15);
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
	glBindTexture(GL_TEXTURE_2D, textures[5]);
	glRotated(Jupiter.Revolution, 0, 1, 0);
	glTranslated(Jupiter.xPos, Jupiter.yPos, Jupiter.zPos);
	glRotated(Jupiter.Rotation, 0, 1, 0);
	//glColor3b(Jupiter.RGB[0], Jupiter.RGB[1], Jupiter.RGB[2]);
	//C.x = Jupiter.xPos, C.y = Jupiter.yPos, C.z = Jupiter.zPos;
	CreateSphere(C, Jupiter.Radius, 128);
	//glutSolidSphere(Jupiter.Radius, 128, 128);
	//glColor3f(1, 1, 1);
	//glutWireSphere(Jupiter.Radius + 10, 15, 15);
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
	glBindTexture(GL_TEXTURE_2D, textures[6]);
	glRotated(Saturn.Revolution, 0, 1, 0);
	glTranslated(Saturn.xPos, Saturn.yPos, Saturn.zPos);
	glRotated(Saturn.Rotation, 0, 1, 0);
	//glColor3b(Saturn.RGB[0], Saturn.RGB[1], Saturn.RGB[2]);
	//C.x = Saturn.xPos, C.y = Saturn.yPos, C.z = Saturn.zPos;
	CreateSphere(C, Saturn.Radius, 128);
	//glutSolidSphere(Saturn.Radius, 128, 128);
	//glColor3f(1, 1, 1);
	//glutWireSphere(Saturn.Radius, 30, 30);
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
	glBindTexture(GL_TEXTURE_2D, textures[7]);
	glRotated(Uranus.Revolution, 0, 1, 0);
	glTranslated(Uranus.xPos, Uranus.yPos, Uranus.zPos);
	glRotated(Uranus.Rotation, 0, 1, 0);
	//glColor3b(Uranus.RGB[0], Uranus.RGB[1], Uranus.RGB[2]);
	//C.x = Uranus.xPos, C.y = Uranus.yPos, C.z = Uranus.zPos;
	CreateSphere(C, Uranus.Radius, 128);
	//glutSolidSphere(Uranus.Radius, 128, 128);
	//glColor3f(1, 1, 1);
	//glutWireSphere(Uranus.Radius, 30, 30);
	glPopMatrix();

	//�ؿռ�
	glPushMatrix();
	Show_Info();
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 360; i++) {
		loop_x = Neptune.xPos * cos(Neptune.Orbit_Degree * PI / 180);
		loop_z = Neptune.xPos * sin(Neptune.Orbit_Degree * PI / 180);
		glVertex3f(loop_x, 0, loop_z);
		Neptune.Orbit_Degree++;
	}
	glEnd();
	Neptune.Orbit_Degree = 0;
	glBindTexture(GL_TEXTURE_2D, textures[8]);
	glRotated(Neptune.Revolution, 0, 1, 0);
	glTranslated(Neptune.xPos, Neptune.yPos, Neptune.zPos);
	glRotated(Neptune.Rotation, 0, 1, 0);
	//glColor3b(Neptune.RGB[0], Neptune.RGB[1], Neptune.RGB[2]);
	//C.x = Neptune.xPos, C.y = Neptune.yPos, C.z = Neptune.zPos;
	CreateSphere(C, Neptune.Radius, 128);
	//glutSolidSphere(Neptune.Radius, 128, 128);
	//glColor3f(1, 1, 1);
	//glutWireSphere(Neptune.Radius, 30, 30);
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
		Camera.move_left(Sun.Radius);
		break;
	case '2'://����
		Camera.Planet_Selection = 2;
		Camera.invalidate_values();
		Camera.set_pos(0, 0, 0);
		Camera.move_front(2000 - Mercury.Radius * 3);
		Camera.move_left(Mercury.Radius);
		break;
	case '3'://�ݼ�
		Camera.Planet_Selection = 3;
		Camera.invalidate_values();
		Camera.set_pos(0, 0, 0);
		Camera.move_front(2000 - Venus.Radius * 3);
		Camera.move_left(Venus.Radius);
		break;
	case '4'://����
		Camera.Planet_Selection = 4;
		Camera.invalidate_values();
		Camera.set_pos(0, 0, 0);
		Camera.move_front(2000 - Earth.Radius * 3);
		Camera.move_left(Earth.Radius);
		break;
	case '5'://ȭ��
		Camera.Planet_Selection = 5;
		Camera.invalidate_values();
		Camera.set_pos(0, 0, 0);
		Camera.move_front(2000 - Mars.Radius * 3);
		Camera.move_left(Mars.Radius);
		break;
	case '6'://��
		Camera.Planet_Selection = 6;
		Camera.invalidate_values();
		Camera.set_pos(0, 0, 0);
		Camera.move_front(2000 - Jupiter.Radius * 3);
		Camera.move_left(Jupiter.Radius);
		break;
	case '7'://�伺
		Camera.Planet_Selection = 7;
		Camera.invalidate_values();
		Camera.set_pos(0, 0, 0);
		Camera.move_front(2000 - Saturn.Radius * 3);
		Camera.move_left(Saturn.Radius);
		break;
	case '8'://õ�ռ�
		Camera.Planet_Selection = 8;
		Camera.invalidate_values();
		Camera.set_pos(0, 0, 0);
		Camera.move_front(2000 - Uranus.Radius * 3);
		Camera.move_left(Uranus.Radius);
		break;
	case '9'://�ؿռ�
		Camera.Planet_Selection = 9;
		Camera.invalidate_values();
		Camera.set_pos(0, 0, 0);
		Camera.move_front(2000 - Neptune.Radius * 3);
		Camera.move_left(Neptune.Radius);
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
		Camera.set_at(eyex + Sun.Radius, eyey - Sun.Radius, eyez);
		break;
	case 2://
		ratio_c = cos(Mercury.Revolution * PI / 180);
		ratio_s = sin(-Mercury.Revolution * PI / 180);
		eyex = (Mercury.xPos) * ratio_c;
		eyey = Mercury.yPos;
		eyez = (Mercury.xPos) * ratio_s;
		ratio_c = cos((Mercury.Revolution - 45) * PI / 180);
		ratio_s = sin(-(Mercury.Revolution - 45) * PI / 180);
		Camera.set_pos(eyex, eyey + Mercury.Radius / 3.0, eyez);
		Camera.set_at(eyex - Mercury.Radius* ratio_c, eyey, eyez - Mercury.Radius * ratio_s);
		break;
	case 3:
		ratio_c = cos(Venus.Revolution * PI / 180);
		ratio_s = sin(-Venus.Revolution * PI / 180);
		eyex = (Venus.xPos)* ratio_c;
		eyey = Venus.yPos;
		eyez = (Venus.xPos) * ratio_s;
		ratio_c = cos((Venus.Revolution - 45) * PI / 180);
		ratio_s = sin(-(Venus.Revolution - 45) * PI / 180);
		Camera.set_pos(eyex, eyey + Venus.Radius / 3.0, eyez);
		Camera.set_at(eyex - Venus.Radius * ratio_c, eyey, eyez - Venus.Radius * ratio_s);
		break;
	case 4:
		ratio_c = cos(Earth.Revolution * PI / 180);
		ratio_s = sin(-Earth.Revolution * PI / 180);
		eyex = (Earth.xPos)* ratio_c;
		eyey = Earth.yPos;
		eyez = (Earth.xPos) * ratio_s;
		ratio_c = cos((Earth.Revolution - 45) * PI / 180);
		ratio_s = sin(-(Earth.Revolution - 45) * PI / 180);
		Camera.set_pos(eyex, eyey + Earth.Radius / 3.0, eyez);
		Camera.set_at(eyex - Venus.Radius * ratio_c, eyey, eyez - Venus.Radius * ratio_s);
		break;
	case 5:
		ratio_c = cos(Mars.Revolution * PI / 180);
		ratio_s = sin(-Mars.Revolution * PI / 180);
		eyex = (Mars.xPos)* ratio_c;
		eyey = Mars.yPos;
		eyez = (Mars.xPos) * ratio_s;
		ratio_c = cos((Mars.Revolution - 45) * PI / 180);
		ratio_s = sin(-(Mars.Revolution - 45) * PI / 180);
		Camera.set_pos(eyex, eyey + Mars.Radius / 3.0, eyez);
		Camera.set_at(eyex - Mars.Radius * ratio_c, eyey, eyez - Mars.Radius * ratio_s);
		break;
	case 6:
		ratio_c = cos(Jupiter.Revolution * PI / 180);
		ratio_s = sin(-Jupiter.Revolution * PI / 180);
		eyex = (Jupiter.xPos)* ratio_c;
		eyey = Jupiter.yPos;
		eyez = (Jupiter.xPos) * ratio_s;
		ratio_c = cos((Jupiter.Revolution - 45) * PI / 180);
		ratio_s = sin(-(Jupiter.Revolution - 45) * PI / 180);
		Camera.set_pos(eyex, eyey + Jupiter.Radius / 3.0, eyez);
		Camera.set_at(eyex - Jupiter.Radius * ratio_c, eyey, eyez - Jupiter.Radius * ratio_s);
		break;
	case 7:
		ratio_c = cos(Saturn.Revolution * PI / 180);
		ratio_s = sin(-Saturn.Revolution * PI / 180);
		eyex = (Saturn.xPos)* ratio_c;
		eyey = Saturn.yPos;
		eyez = (Saturn.xPos) * ratio_s;
		ratio_c = cos((Saturn.Revolution - 45) * PI / 180);
		ratio_s = sin(-(Saturn.Revolution - 45) * PI / 180);
		Camera.set_pos(eyex, eyey + Saturn.Radius / 3.0, eyez);
		Camera.set_at(eyex - Saturn.Radius * ratio_c, eyey, eyez - Saturn.Radius * ratio_s);
		break;
	case 8:
		ratio_c = cos(Uranus.Revolution * PI / 180);
		ratio_s = sin(-Uranus.Revolution * PI / 180);
		eyex = (Uranus.xPos)* ratio_c;
		eyey = Uranus.yPos;
		eyez = (Uranus.xPos) * ratio_s;
		ratio_c = cos((Uranus.Revolution - 45) * PI / 180);
		ratio_s = sin(-(Uranus.Revolution - 45) * PI / 180);
		Camera.set_pos(eyex, eyey + Uranus.Radius / 3.0, eyez);
		Camera.set_at(eyex - Uranus.Radius * ratio_c, eyey, eyez - Uranus.Radius * ratio_s);
		break;
	case 9:
		ratio_c = cos(Neptune.Revolution * PI / 180);
		ratio_s = sin(-Neptune.Revolution * PI / 180);
		eyex = (Neptune.xPos)* ratio_c;
		eyey = Neptune.yPos;
		eyez = (Neptune.xPos) * ratio_s;
		ratio_c = cos((Neptune.Revolution - 45) * PI / 180);
		ratio_s = sin(-(Neptune.Revolution - 45) * PI / 180);
		Camera.set_pos(eyex, eyey + Neptune.Radius / 3.0, eyez);
		Camera.set_at(eyex - Neptune.Radius * ratio_c, eyey, eyez - Neptune.Radius * ratio_s);
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
void Show_Info(void) {
	if (Camera.view_type() == 'N') {
		switch (Camera.Planet_Selection)
		{
		case 1: //�¾�
			glPushMatrix();
			glTranslated(Sun.xPos, Sun.yPos, Sun.zPos);
			for (int i = 0; i < 11; i++) {
				glRasterPos3f(Sun.xPos + 1000, Sun.yPos - 100 - i * 100, Sun.zPos + 500 + i * 12);
				int len = (int)strlen(Sun.info[i]);
				for (int j = 0; j < len; j++) {
					glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int)Sun.info[i][j]);
				}
			}
			glPopMatrix();
			break;
		case 2: //����
			glPushMatrix();
			glRotated(Mercury.Revolution, 0, 1, 0);
			glTranslated(Mercury.xPos, Mercury.yPos, Mercury.zPos);
			for (int i = 0; i < 11; i++) {
				glRasterPos3f(Mercury.Radius*1.5, Mercury.yPos + Mercury.Radius - i * Mercury.Radius/11, Mercury.zPos);
				int len = (int)strlen(Mercury.info[i]);
				for (int j = 0; j < len; j++) {
					glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int)Mercury.info[i][j]);
				}
			}
			glPopMatrix();
			break;
		case 3: //�ݼ�
			glPushMatrix();
			glRotated(Venus.Revolution, 0, 1, 0);
			glTranslated(Venus.xPos, Venus.yPos, Venus.zPos);
			for (int i = 0; i < 11; i++) {
				glRasterPos3f(Venus.Radius*1.5, Venus.yPos + Venus.Radius - i * Venus.Radius/11, Venus.zPos);
				int len = (int)strlen(Venus.info[i]);
				for (int j = 0; j < len; j++) {
					glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int)Venus.info[i][j]);
				}
			}
			glPopMatrix();
			break;
		case 4: //����
			glPushMatrix();
			glRotated(Earth.Revolution, 0, 1, 0);
			glTranslated(Earth.xPos, Earth.yPos, Earth.zPos);
			for (int i = 0; i < 11; i++) {
				glRasterPos3f(Earth.Radius*1.5, Earth.yPos + Earth.Radius - i * Earth.Radius / 11, Earth.zPos);
				int len = (int)strlen(Earth.info[i]);
				for (int j = 0; j < len; j++) {
					glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int)Earth.info[i][j]);
				}
			}
			glPopMatrix();
			break;
		case 5: //ȭ��
			glPushMatrix();
			glRotated(Mars.Revolution, 0, 1, 0);
			glTranslated(Mars.xPos, Mars.yPos, Mars.zPos);
			for (int i = 0; i < 11; i++) {
				glRasterPos3f(Mars.Radius*1.5, Mars.yPos + Mars.Radius - i * Mars.Radius / 11, Mars.zPos);
				int len = (int)strlen(Mars.info[i]);
				for (int j = 0; j < len; j++) {
					glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int)Mars.info[i][j]);
				}
			}
			glPopMatrix();
			break;
		case 6: //��
			glPushMatrix();
			glRotated(Jupiter.Revolution, 0, 1, 0);
			glTranslated(Jupiter.xPos, Jupiter.yPos, Jupiter.zPos);
			for (int i = 0; i < 11; i++) {
				glRasterPos3f(Jupiter.Radius*1.5, Jupiter.yPos + Jupiter.Radius - i * Jupiter.Radius / 11, Jupiter.zPos);
				int len = (int)strlen(Jupiter.info[i]);
				for (int j = 0; j < len; j++) {
					glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int)Jupiter.info[i][j]);
				}
			}
			glPopMatrix();
			break;
		case 7: //�伺
			glPushMatrix();
			glRotated(Saturn.Revolution, 0, 1, 0);
			glTranslated(Saturn.xPos, Saturn.yPos, Saturn.zPos);
			for (int i = 0; i < 11; i++) {
				glRasterPos3f(Saturn.Radius*1.5, Saturn.yPos + Saturn.Radius - i * Saturn.Radius / 11, Saturn.zPos);
				int len = (int)strlen(Saturn.info[i]);
				for (int j = 0; j < len; j++) {
					glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int)Saturn.info[i][j]);
				}
			}
			glPopMatrix();
			break;
		case 8: //õ�ռ�
			glPushMatrix();
			glRotated(Uranus.Revolution, 0, 1, 0);
			glTranslated(Uranus.xPos, Uranus.yPos, Uranus.zPos);
			for (int i = 0; i < 11; i++) {
				glRasterPos3f(Uranus.Radius*1.5, Uranus.yPos + Uranus.Radius - i * Uranus.Radius / 11, Uranus.zPos);
				int len = (int)strlen(Uranus.info[i]);
				for (int j = 0; j < len; j++) {
					glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int)Uranus.info[i][j]);
				}
			}
			glPopMatrix();
			break;
		case 9: //�ؿռ�
			glPushMatrix();
			glRotated(Neptune.Revolution, 0, 1, 0);
			glTranslated(Neptune.xPos, Neptune.yPos, Neptune.zPos);
			for (int i = 0; i < 11; i++) {
				glRasterPos3f(Neptune.Radius*1.5, Neptune.yPos + Neptune.Radius - i * Neptune.Radius / 11, Neptune.zPos);
				int len = (int)strlen(Neptune.info[i]);
				for (int j = 0; j < len; j++) {
					glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int)Neptune.info[i][j]);
				}
			}
			glPopMatrix();
			break;
		}
	}
}

void CreateSphere(XYZ c, double r, int n) {
	/* Create a sphere centered at c, with radius r, and precision n 
	Draw a point for zero radius spheres */ 
	int i, j; double theta1, theta2, theta3;
	XYZ e, p;

	glEnable(GL_TEXTURE_2D);

	if (r < 0)
		r = -r; 
	if (n < 0) 
		n = -n; 
	if (n < 4 || r <= 0) {
		glBegin(GL_POINTS);
		glVertex3f(c.x, c.y, c.z);
		glEnd();
		return;
	} 
	for (j = 0; j<n / 2; j++) {
		theta1 = j * TWOPI / n - PID2; 
		theta2 = (j + 1) * TWOPI / n - PID2; 
		glBegin(GL_QUAD_STRIP); 
		for (i = 0; i <= n; i++) { 
			theta3 = i * TWOPI / n;

			e.x = cos(theta2) * cos(theta3); 
			e.y = sin(theta2); 
			e.z = cos(theta2) * sin(theta3); 
			p.x = c.x + r * e.x; 
			p.y = c.y + r * e.y; 
			p.z = c.z + r * e.z; 

			glNormal3f(e.x, e.y, e.z); 
			glTexCoord2f(i / (double)n, 2 * (j + 1) / (double)n); 
			glVertex3f(p.x, p.y, p.z); 

			e.x = cos(theta1) * cos(theta3); 
			e.y = sin(theta1); 
			e.z = cos(theta1) * sin(theta3); 
			p.x = c.x + r * e.x; 
			p.y = c.y + r * e.y; 
			p.z = c.z + r * e.z; 

			glNormal3f(e.x, e.y, e.z); 
			glTexCoord2f(i / (double)n, 2 * j / (double)n); 
			glVertex3f(p.x, p.y, p.z); 
		} 
		glEnd(); 
	}
	glDisable(GL_TEXTURE_2D);
}