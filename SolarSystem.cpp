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
#include "Moon.h"
#include "Mars.h"
#include "Jupiter.h"
#include "Saturn.h"
#include "Uranus.h"
#include "Neptune.h"
#include "Camera.h"

#define TEXTURE_NUMBER 12

struct XYZ {
	double x, y, z;
}C;
struct Orbit {
	double x, z;
	double degree = 0;
};

//로켓 관련 변수
double Spd = 5;

//윈도우 관련 변수
int ww = 1600, wh = 900;

//마우스 관련 변수
double ox, oy; //클릭한 좌표
double mx, my; //마우스 움직인 좌표

//행성 변수
double Speed = 100;
double loop_x, loop_z;

//bool 트리거
bool rotate = false, c_rotate = true, reverse = false;
bool projection = true, model = true;
bool drag = false, wheel_drag = false;

//조명 변수
GLfloat EmissionLight[] = { 0.6f, 0.6f, 0.6f, 1.0f };
GLfloat AmbientLight[] = { 0.2f, 0.2f, 1.0f, 1.0f };
GLfloat DiffuseLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat SpecularLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat lightPos[] = { 31.0f, 0.0f, 0.0f, 1.0f };
int SHINE = 100;


GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLubyte *pBytes; // 데이터를 가리킬 포인터
BITMAPINFO *info; // 비트맵 헤더 저장할 변수
GLubyte * TexBits;
GLuint textures[TEXTURE_NUMBER];
GLubyte * LoadDIBitMap(const char *filename, BITMAPINFO **info)
{
	FILE *fp;
	GLubyte *bits;
	int bitsize, infosize;
	BITMAPFILEHEADER header;
	// 바이너리 읽기 모드로 파일을 연다
	if ((fp = fopen(filename, "rb")) == NULL)
		return NULL;
	// 비트맵 파일 헤더를 읽는다.
	if (fread(&header, sizeof(BITMAPFILEHEADER), 1, fp) < 1) {
		fclose(fp);
		return NULL;
	}
	// 파일이 BMP 파일인지 확인한다.
	if (header.bfType != 'MB') {
		fclose(fp);
		return NULL;
	}
	// BITMAPINFOHEADER 위치로 간다.
	infosize = header.bfOffBits - sizeof(BITMAPFILEHEADER);
	// 비트맵 이미지 데이터를 넣을 메모리 할당을 한다.
	if ((*info = (BITMAPINFO *)malloc(infosize)) == NULL) {
		fclose(fp);
		exit(0);
		return NULL;
	}
	// 비트맵 인포 헤더를 읽는다.
	if (fread(*info, 1, infosize, fp) < (unsigned int)infosize) {
		free(*info);
		fclose(fp);
		return NULL;
	}
	// 비트맵의 크기 설정
	if ((bitsize = (*info)->bmiHeader.biSizeImage) == 0)
		bitsize = ((*info)->bmiHeader.biWidth*(*info)->bmiHeader.biBitCount + 7) / 8.0 * abs((*info)->bmiHeader.biHeight);
	// 비트맵의 크기만큼 메모리를 할당한다.
	if ((bits = (unsigned char *)malloc(bitsize)) == NULL) {
		free(*info);
		fclose(fp);
		return NULL;
	}
	// 비트맵 데이터를 bit(GLubyte 타입)에 저장한다.
	if (fread(bits, 1, bitsize, fp) < (unsigned int)bitsize) {
		free(*info); free(bits);
		fclose(fp);
		return NULL;
	}
	fclose(fp);
	return bits;
}
void initTextures() {
	glGenTextures(TEXTURE_NUMBER, textures); //텍스처 이름을 생성한다. n:생성되어야할 텍스처이름의 수 

	glBindTexture(GL_TEXTURE_2D, textures[0]); // 텍스처링 할 객체에 텍스처를 연결해준다.
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

	glBindTexture(GL_TEXTURE_2D, textures[9]);
	pBytes = LoadDIBitMap("BackGround.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 2048, 1024, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, textures[10]);
	pBytes = LoadDIBitMap("SaturnRing.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 2048, 125, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, textures[11]);
	pBytes = LoadDIBitMap("Moon.bmp", &info);
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
void Timer(int value);
void Motion(int x, int y);
void Fix_Camera(void);
void Show_Info(void);
void drawTorus(double r, double c, int rSeg, int cSeg);
void StarRotationTimerFunction(int value);
void mul(double m1, double m2, double m3);
double * mul_vertex(double x, double y, double z, double xx, double yy, double zz);
double get_dist(double sx, double sy, double sz, double dx, double dy, double dz);
double abs(double x)
{
	return (x > 0) ? x : -x;
}

void CreateSphere(XYZ c, double r, int n);
void CreateSpaceShip(void);

//마우스 움직임에 대한 translate 처리 함수
void MouseTranslated(void);

void main(int argc, char *argv[])
{
	srand(time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100); // 윈도우의 위치지정
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT); // 윈도우의 크기 지정
	glutCreateWindow("TheSolarSystem"); // 윈도우 생성 (윈도우 이름)
	initTextures();
	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutTimerFunc(TIMERDELAY, Timer, 1);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);
	glutMouseWheelFunc(MouseWheel);
	glutMotionFunc(Motion);
	glutTimerFunc(10, StarRotationTimerFunction, 1);
	glutMainLoop();
}
// 윈도우 출력 함수
GLvoid drawScene(GLvoid)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glLoadIdentity();


	glMatrixMode(GL_PROJECTION);

	Reshape(ww, wh);
	MouseTranslated();

	//카메라 이동 변환
	mul(Camera.rtx, Camera.rty, Camera.rtz);//카메라 회전 변환
	glTranslated(Camera.mvx, Camera.mvy, Camera.mvz);
	CreateSpaceShip();
	
	//카메라 EYE, AY, UP 벡터로 시점 설정
	Fix_Camera();//고정 뷰일 때, 함수 실행됨
	glMatrixMode(GL_MODELVIEW);
	gluLookAt(Camera.EYEx, Camera.EYEy, Camera.EYEz,
		Camera.ATx, Camera.ATy, Camera.ATz,
		Camera.UPx, Camera.UPy, Camera.UPz);


	////////////////////////////////////////////
	glBindTexture(GL_TEXTURE_2D, textures[9]);
	CreateSphere(C, 5000, 10);
	///////////////////////////////////////////

	glColor3f(1, 1, 1);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	glMaterialfv(GL_FRONT, GL_SPECULAR, DiffuseLight);
	glMaterialfv(GL_FRONT, GL_SPECULAR, SpecularLight);
	glMaterialfv(GL_FRONT, GL_EMISSION, EmissionLight);
	glMateriali(GL_FRONT, GL_SHININESS, SHINE);

	glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, SpecularLight);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glEnable(GL_LIGHT0);
	glEnable(GL_SHADE_MODEL);

	//태양
	glPushMatrix();
	glTranslated(Sun.xPos, Sun.yPos, Sun.zPos);
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	glRotated(Sun.Rotation, 0, 1, 0);
	CreateSphere(C, Sun.Radius, 50);
	glPopMatrix();

	GLfloat EmissionLight[] = { 0.06f, 0.06f, 0.06f, 1.0f };
	glMaterialfv(GL_FRONT, GL_EMISSION, EmissionLight);

	//수성
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 360; i++) {
		loop_x = Mercury.xPos * cos(Mercury.Orbit_Degree * PI / 180);
		loop_z = Mercury.xPos * sin(Mercury.Orbit_Degree * PI / 180);
		glVertex3f(loop_x, 0, loop_z);
		Mercury.Orbit_Degree++;
	}
	glEnd();
	glEnable(GL_LIGHTING);
	Mercury.Orbit_Degree = 0;
	glBindTexture(GL_TEXTURE_2D, textures[1]);
	glRotated(Mercury.Revolution, 0, 1, 0);
	glTranslated(Mercury.xPos, Mercury.yPos, Mercury.zPos);
	glRotated(Mercury.Rotation, 0, 1, 0);
	CreateSphere(C, Mercury.Radius, 50);
	glPopMatrix();

	//금성
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 360; i++) {
		loop_x = Venus.xPos * cos(Venus.Orbit_Degree * PI / 180);
		loop_z = Venus.xPos * sin(Venus.Orbit_Degree * PI / 180);
		glVertex3f(loop_x, 0, loop_z);
		Venus.Orbit_Degree++;
	}
	glEnd();
	glEnable(GL_LIGHTING);
	Venus.Orbit_Degree = 0;
	glBindTexture(GL_TEXTURE_2D, textures[2]);
	glRotated(Venus.Revolution, 0, 1, 0);
	glTranslated(Venus.xPos, Venus.yPos, Venus.zPos);
	glRotated(Venus.Rotation, 0, 1, 0);
	CreateSphere(C, Venus.Radius, 50);
	glPopMatrix();

	//지구
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 360; i++) {
		loop_x = Earth.xPos * cos(Earth.Orbit_Degree * PI / 180);
		loop_z = Earth.xPos * sin(Earth.Orbit_Degree * PI / 180);
		glVertex3f(loop_x, 0, loop_z);
		Earth.Orbit_Degree++;
	}
	glEnd();
	glEnable(GL_LIGHTING);
	Earth.Orbit_Degree = 0;
	glBindTexture(GL_TEXTURE_2D, textures[3]);
	glRotated(Earth.Revolution, 0, 1, 0);
	glTranslated(Earth.xPos, Earth.yPos, Earth.zPos);
	glRotated(Earth.Rotation, 0, 1, 0);
	CreateSphere(C, Earth.Radius, 50);
	glPopMatrix();

	//달
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, textures[11]);
	glRotated(Earth.Revolution, 0, 1, 0);
	glTranslated(Earth.xPos, Earth.yPos, Earth.zPos);
	glRotated(Moon.Revolution, 0, 1, 0);
	glTranslated(Moon.Radius * 8, 0, 0);
	glRotated(Moon.Rotation, 0, 1, 0);
	CreateSphere(C, Moon.Radius, 50);
	glPopMatrix();

	//화성
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 360; i++) {
		loop_x = Mars.xPos * cos(Mars.Orbit_Degree * PI / 180);
		loop_z = Mars.xPos * sin(Mars.Orbit_Degree * PI / 180);
		glVertex3f(loop_x, 0, loop_z);
		Mars.Orbit_Degree++;
	}
	glEnd();
	glEnable(GL_LIGHTING);
	Mars.Orbit_Degree = 0;
	glBindTexture(GL_TEXTURE_2D, textures[4]);
	glRotated(Mars.Revolution, 0, 1, 0);
	glTranslated(Mars.xPos, Mars.yPos, Mars.zPos);
	glRotated(Mars.Rotation, 0, 1, 0);
	CreateSphere(C, Mars.Radius, 50);
	glPopMatrix();

	//목성
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 360; i++) {
		loop_x = Jupiter.xPos * cos(Jupiter.Orbit_Degree * PI / 180);
		loop_z = Jupiter.xPos * sin(Jupiter.Orbit_Degree * PI / 180);
		glVertex3f(loop_x, 0, loop_z);
		Jupiter.Orbit_Degree++;
	}
	glEnd();
	glEnable(GL_LIGHTING);
	Jupiter.Orbit_Degree = 0;
	glBindTexture(GL_TEXTURE_2D, textures[5]);
	glRotated(Jupiter.Revolution, 0, 1, 0);
	glTranslated(Jupiter.xPos, Jupiter.yPos, Jupiter.zPos);
	glRotated(Jupiter.Rotation, 0, 1, 0);
	CreateSphere(C, Jupiter.Radius, 50);
	glPopMatrix();

	//토성
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 360; i++) {
		loop_x = Saturn.xPos * cos(Saturn.Orbit_Degree * PI / 180);
		loop_z = Saturn.xPos * sin(Saturn.Orbit_Degree * PI / 180);
		glVertex3f(loop_x, 0, loop_z);
		Saturn.Orbit_Degree++;
	}
	glEnd();
	glEnable(GL_LIGHTING);
	Saturn.Orbit_Degree = 0;
	glBindTexture(GL_TEXTURE_2D, textures[6]);
	glRotated(Saturn.Revolution, 0, 1, 0);
	glTranslated(Saturn.xPos, Saturn.yPos, Saturn.zPos);
	glRotated(Saturn.Rotation, 0, 1, 0);
	CreateSphere(C, Saturn.Radius, 50);
	////////////////////////////////////////////////////////////////
	glRotated(90, 1, 0, 0);
	glScaled(1, 1, 0.01);
	drawTorus(20, 80, 50, 50);
	///////////////////////////////////////////////////////////////
	glPopMatrix();

	//천왕성
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 360; i++) {
		loop_x = Uranus.xPos * cos(Uranus.Orbit_Degree * PI / 180);
		loop_z = Uranus.xPos * sin(Uranus.Orbit_Degree * PI / 180);
		glVertex3f(loop_x, 0, loop_z);
		Uranus.Orbit_Degree++;
	}
	glEnd();
	glEnable(GL_LIGHTING);
	Uranus.Orbit_Degree = 0;
	glBindTexture(GL_TEXTURE_2D, textures[7]);
	glRotated(Uranus.Revolution, 0, 1, 0);
	glTranslated(Uranus.xPos, Uranus.yPos, Uranus.zPos);
	glRotated(Uranus.Rotation, 0, 1, 0);
	CreateSphere(C, Uranus.Radius, 50);
	glPopMatrix();

	//해왕성
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 360; i++) {
		loop_x = Neptune.xPos * cos(Neptune.Orbit_Degree * PI / 180);
		loop_z = Neptune.xPos * sin(Neptune.Orbit_Degree * PI / 180);
		glVertex3f(loop_x, 0, loop_z);
		Neptune.Orbit_Degree++;
	}
	glEnd();
	glEnable(GL_LIGHTING);
	Neptune.Orbit_Degree = 0;
	glBindTexture(GL_TEXTURE_2D, textures[8]);
	glRotated(Neptune.Revolution, 0, 1, 0);
	glTranslated(Neptune.xPos, Neptune.yPos, Neptune.zPos);
	glRotated(Neptune.Rotation, 0, 1, 0);
	CreateSphere(C, Neptune.Radius, 50);
	glPopMatrix();
	Show_Info();

	glutSwapBuffers();
	//glFlush(); // 화면에 출력하기
}
GLvoid Reshape(int w, int h)
{
	//화면을 초기화 하기 위해서는 밖에서 reshape를 불러야함.
	//밖에서도 reshape를 부르기 위해 전역변수 w, h 초기화
	ww = w, wh = h;

	//뷰포트 변환 설정
	glViewport(0, 0, w, h);

	// 투영 행렬 스택 재설정
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//-- 투영은 직각 투영 또는 원근 투영 중 한 개를 설정한다.
	// 1. 클리핑 공간 설정: 원근 투영인 경우
	gluPerspective(60.0f, (double)w / (double)h, 1.0, 10000.0);
	glFrustum(SCREEN_WIDTH_MIN, SCREEN_WIDTH_MAX, SCREEN_HEIGHT_MIN, SCREEN_HEIGHT_MAX, SCREEN_DEPTH_MIN, SCREEN_DEPTH_MAX);
	glTranslatef(0.0, 0.0, -2000.0); // 투영 공간을 화면 안쪽으로 이동하여 시야를 확보한다.

	// 2. 클리핑 공간 설정: 직각 투영인 경우
	//glOrtho(-400.0, 400.0, -300.0, 300.0, -400.0, 400.0);

	// 모델 뷰 행렬 스택 재설정
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//gluLookAt(0.0, 100.0, 100.0, 0.0, 0.0, -100.0, 0.0, 1.0, 0.0);
}

void Mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		if (Camera.view_type() == 'N') return;
		drag = true;
		ox = x; oy = y;
		mx = x; my = y;
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		drag = false;
	}
	else if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) {
		if (Camera.view_type() == 'N') return;
		if (Camera.Planet_Selection != 0)return;
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
	if (Camera.Planet_Selection != 0)return;
	double dist = get_dist(400, 400, 0, x, y, 0);

	int dx = 800 - x; int dy = y - 450;
	if (dir > 0) {
		Camera.move_front(CAMERA_MOVE * 3);
		if (dist != 0 && Camera.view_type() != 'N') {
			if (dx != 0)Camera.move_right(dx * CAMERA_MOVE * 3 / dist);
			if (dy != 0)Camera.move_up(dy * CAMERA_MOVE * 3 / dist);
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
void Timer(int value)
{
	if (Camera.Planet_Selection == 10)
	{
		double * mlv = mul_vertex(Camera.rtx, Camera.rty, Camera.rtz, 0, 0, Spd);

		Camera.move_front(mlv[2]);
		Camera.move_up(mlv[1]);
		Camera.move_right(mlv[0]);
	}
	glutPostRedisplay();
	glutTimerFunc(TIMERDELAY, Timer, 1);
}
void Keyboard(unsigned char key, int x, int y)
{
	char Camera_Type = Camera.view_type();
	switch (key) {
	case 'w':
		if (Camera_Type == 'N') return;
		if (Camera.Planet_Selection != 0)return;
		Camera.move_up(-CAMERA_MOVE);
		break;
	case 'a':
		if (Camera_Type == 'N') return;
		if (Camera.Planet_Selection != 0)return;
		Camera.move_left(-CAMERA_MOVE);
		break;
	case 's':
		if (Camera_Type == 'N') return;
		if (Camera.Planet_Selection != 0)return;
		Camera.move_down(-CAMERA_MOVE);
		break;
	case 'd':
		if (Camera_Type == 'N') return;
		if (Camera.Planet_Selection != 0)return;
		Camera.move_right(-CAMERA_MOVE);
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
	case 'e':case 'E':
		Camera.Planet_Selection = 0;
		Camera.invalidate_values();
		Camera.set_pos(0, 900, 1600);
		break;
	case '0':
		Camera.Planet_Selection = 10;
		Camera.invalidate_values();
		Camera.set_pos(0, 900, 1600);
		break;
	case '1'://태양
		Camera.Planet_Selection = 1;
		Camera.invalidate_values();
		Camera.set_pos(0, 0, 0);
		Camera.move_front(2000 - Sun.Radius * 2);
		Camera.move_left(Sun.Radius);
		break;
	case '2'://수성
		Camera.Planet_Selection = 2;
		Camera.invalidate_values();
		Camera.set_pos(0, 0, 0);
		Camera.move_front(2000 - Mercury.Radius * 3);
		Camera.move_left(Mercury.Radius);
		break;
	case '3'://금성
		Camera.Planet_Selection = 3;
		Camera.invalidate_values();
		Camera.set_pos(0, 0, 0);
		Camera.move_front(2000 - Venus.Radius * 3);
		Camera.move_left(Venus.Radius);
		break;
	case '4'://지구
		Camera.Planet_Selection = 4;
		Camera.invalidate_values();
		Camera.set_pos(0, 0, 0);
		Camera.move_front(2000 - Earth.Radius * 3);
		Camera.move_left(Earth.Radius);
		break;
	case '5'://화성
		Camera.Planet_Selection = 5;
		Camera.invalidate_values();
		Camera.set_pos(0, 0, 0);
		Camera.move_front(2000 - Mars.Radius * 3);
		Camera.move_left(Mars.Radius);
		break;
	case '6'://목성
		Camera.Planet_Selection = 6;
		Camera.invalidate_values();
		Camera.set_pos(0, 0, 0);
		Camera.move_front(2000 - Jupiter.Radius * 3);
		Camera.move_left(Jupiter.Radius);
		break;
	case '7'://토성
		Camera.Planet_Selection = 7;
		Camera.invalidate_values();
		Camera.set_pos(0, 0, 0);
		Camera.move_front(2000 - Saturn.Radius * 3);
		Camera.move_left(Saturn.Radius);
		break;
	case '8'://천왕성
		Camera.Planet_Selection = 8;
		Camera.invalidate_values();
		Camera.set_pos(0, 0, 0);
		Camera.move_front(2000 - Uranus.Radius * 3);
		Camera.move_left(Uranus.Radius);
		break;
	case '9'://해왕성
		Camera.Planet_Selection = 9;
		Camera.invalidate_values();
		Camera.set_pos(0, 0, 0);
		Camera.move_front(2000 - Neptune.Radius * 3);
		Camera.move_left(Neptune.Radius);
		break;
	case '+':
		if (Camera.Planet_Selection != 10)
			Speed *= 10;
		else
			Spd *= 2;
		break;
	case '-':
		if (Camera.Planet_Selection != 10)
			Speed /= 10;
		else
			Spd /= 2;
		break;
	case 'i':
		if (Camera_Type == 'N') return;
		Camera.invalidate_values();
		break;
	case 'r':
		if (Camera_Type == 'N') return;
		Camera.rotatey(CAMERA_MOVE / 2.0);
		break;
	case 'R':
		if (Camera_Type == 'N') return;
		Camera.rotatey(-CAMERA_MOVE / 2.0);
		break;
	case 'Q': //종료
		glutDestroyWindow(glutCreateWindow("TheSolarSystem"));
		exit(0);
	}
	glutPostRedisplay();
}
void MouseTranslated(void)
{
	if (ox == mx && oy == my)
		return;
	int dx = mx - ox; int dy = my - oy;

	if (wheel_drag) {
		Camera.move_right(-dx);
		Camera.move_down(-dy);
	}
	else if (drag) {
		Camera.rty -= dx / 10.0;
		Camera.rtx -= dy / 10.0;
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
		ratio_c = cos((Mercury.Revolution) * PI / 180);
		ratio_s = sin(-(Mercury.Revolution) * PI / 180);
		eyex = (Mercury.xPos) * ratio_c;
		eyey = Mercury.yPos;
		eyez = (Mercury.xPos) * ratio_s;
		ratio_c = cos((Mercury.Revolution + 80) * PI / 180);
		ratio_s = sin(-(Mercury.Revolution + 80) * PI / 180);
		Camera.set_pos(eyex, eyey + Mercury.Radius / 3.0, eyez);
		Camera.set_at(eyex - Mercury.Radius* ratio_c, eyey, eyez - Mercury.Radius * ratio_s);
		break;
	case 3:
		ratio_c = cos(Venus.Revolution * PI / 180);
		ratio_s = sin(-Venus.Revolution * PI / 180);
		eyex = (Venus.xPos)* ratio_c;
		eyey = Venus.yPos;
		eyez = (Venus.xPos) * ratio_s;
		ratio_c = cos((Venus.Revolution + 80) * PI / 180);
		ratio_s = sin(-(Venus.Revolution + 80) * PI / 180);
		Camera.set_pos(eyex, eyey + Venus.Radius / 3.0, eyez);
		Camera.set_at(eyex - Venus.Radius * ratio_c, eyey, eyez - Venus.Radius * ratio_s);
		break;
	case 4:
		ratio_c = cos(Earth.Revolution * PI / 180);
		ratio_s = sin(-Earth.Revolution * PI / 180);
		eyex = (Earth.xPos)* ratio_c;
		eyey = Earth.yPos;
		eyez = (Earth.xPos) * ratio_s;
		ratio_c = cos((Earth.Revolution + 80) * PI / 180);
		ratio_s = sin(-(Earth.Revolution + 80) * PI / 180);
		Camera.set_pos(eyex, eyey + Earth.Radius / 3.0, eyez);
		Camera.set_at(eyex - Venus.Radius * ratio_c, eyey, eyez - Venus.Radius * ratio_s);
		break;
	case 5:
		ratio_c = cos(Mars.Revolution * PI / 180);
		ratio_s = sin(-Mars.Revolution * PI / 180);
		eyex = (Mars.xPos)* ratio_c;
		eyey = Mars.yPos;
		eyez = (Mars.xPos) * ratio_s;
		ratio_c = cos((Mars.Revolution + 80) * PI / 180);
		ratio_s = sin(-(Mars.Revolution + 80) * PI / 180);
		Camera.set_pos(eyex, eyey + Mars.Radius / 3.0, eyez);
		Camera.set_at(eyex - Mars.Radius * ratio_c, eyey, eyez - Mars.Radius * ratio_s);
		break;
	case 6:
		ratio_c = cos(Jupiter.Revolution * PI / 180);
		ratio_s = sin(-Jupiter.Revolution * PI / 180);
		eyex = (Jupiter.xPos)* ratio_c;
		eyey = Jupiter.yPos;
		eyez = (Jupiter.xPos) * ratio_s;
		ratio_c = cos((Jupiter.Revolution + 80) * PI / 180);
		ratio_s = sin(-(Jupiter.Revolution + 80) * PI / 180);
		Camera.set_pos(eyex, eyey + Jupiter.Radius / 3.0, eyez);
		Camera.set_at(eyex - Jupiter.Radius * ratio_c, eyey, eyez - Jupiter.Radius * ratio_s);
		break;
	case 7:
		ratio_c = cos(Saturn.Revolution * PI / 180);
		ratio_s = sin(-Saturn.Revolution * PI / 180);
		eyex = (Saturn.xPos)* ratio_c;
		eyey = Saturn.yPos;
		eyez = (Saturn.xPos) * ratio_s;
		ratio_c = cos((Saturn.Revolution + 80) * PI / 180);
		ratio_s = sin(-(Saturn.Revolution + 80) * PI / 180);
		Camera.set_pos(eyex, eyey + Saturn.Radius / 3.0, eyez);
		Camera.set_at(eyex - Saturn.Radius * ratio_c, eyey, eyez - Saturn.Radius * ratio_s);
		break;
	case 8:
		ratio_c = cos(Uranus.Revolution * PI / 180);
		ratio_s = sin(-Uranus.Revolution * PI / 180);
		eyex = (Uranus.xPos)* ratio_c;
		eyey = Uranus.yPos;
		eyez = (Uranus.xPos) * ratio_s;
		ratio_c = cos((Uranus.Revolution + 80) * PI / 180);
		ratio_s = sin(-(Uranus.Revolution + 80) * PI / 180);
		Camera.set_pos(eyex, eyey + Uranus.Radius / 3.0, eyez);
		Camera.set_at(eyex - Uranus.Radius * ratio_c, eyey, eyez - Uranus.Radius * ratio_s);
		break;
	case 9:
		ratio_c = cos(Neptune.Revolution * PI / 180);
		ratio_s = sin(-Neptune.Revolution * PI / 180);
		eyex = (Neptune.xPos)* ratio_c;
		eyey = Neptune.yPos;
		eyez = (Neptune.xPos) * ratio_s;
		ratio_c = cos((Neptune.Revolution + 80) * PI / 180);
		ratio_s = sin(-(Neptune.Revolution + 80) * PI / 180);
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
	//수성
	if (Mercury.Rotation < 360)
		Mercury.Rotation += STAR_ROTATION_HOUR_PER_mSECOND / Mercury.Roation_Cycle * Speed;
	else
		Mercury.Rotation = 0;
	if (Mercury.Revolution < 360)
		Mercury.Revolution += STAR_ROTATION_HOUR_PER_mSECOND / Mercury.Revolution_Cycle * Speed;
	else
		Mercury.Revolution = 0;
	//금성
	if (Venus.Rotation < 360)
		Venus.Rotation += STAR_ROTATION_HOUR_PER_mSECOND / Venus.Roation_Cycle * Speed;
	else
		Venus.Rotation = 0;
	if (Venus.Revolution < 360)
		Venus.Revolution += STAR_ROTATION_HOUR_PER_mSECOND / Venus.Revolution_Cycle * Speed;
	else
		Venus.Revolution = 0;
	//지구
	if (Earth.Rotation < 360)
		Earth.Rotation += STAR_ROTATION_HOUR_PER_mSECOND / Earth.Roation_Cycle * Speed;
	else
		Earth.Rotation = 0;
	if (Earth.Revolution < 360)
		Earth.Revolution += STAR_ROTATION_HOUR_PER_mSECOND / Earth.Revolution_Cycle * Speed;
	else
		Earth.Revolution = 0;
	//달
	if (Moon.Rotation < 360)
		Moon.Rotation += STAR_ROTATION_HOUR_PER_mSECOND / Moon.Roation_Cycle * Speed;
	else
		Moon.Rotation = 0;
	if (Moon.Revolution < 360)
		Moon.Revolution += STAR_ROTATION_HOUR_PER_mSECOND / Moon.Revolution_Cycle * Speed;
	else
		Moon.Revolution = 0;
	//화성
	if (Mars.Rotation < 360)
		Mars.Rotation += STAR_ROTATION_HOUR_PER_mSECOND / Mars.Roation_Cycle * Speed;
	else
		Mars.Rotation = 0;
	if (Mars.Revolution < 360)
		Mars.Revolution += STAR_ROTATION_HOUR_PER_mSECOND / Mars.Revolution_Cycle * Speed;
	else
		Mars.Revolution = 0;
	//목성
	if (Jupiter.Rotation < 360)
		Jupiter.Rotation += STAR_ROTATION_HOUR_PER_mSECOND / Jupiter.Roation_Cycle * Speed;
	else
		Jupiter.Rotation = 0;
	if (Jupiter.Revolution < 360)
		Jupiter.Revolution += STAR_ROTATION_HOUR_PER_mSECOND / Jupiter.Revolution_Cycle * Speed;
	else
		Jupiter.Revolution = 0;
	//토성
	if (Saturn.Rotation < 360)
		Saturn.Rotation += STAR_ROTATION_HOUR_PER_mSECOND / Saturn.Roation_Cycle * Speed;
	else
		Saturn.Rotation = 0;
	if (Saturn.Revolution < 360)
		Saturn.Revolution += STAR_ROTATION_HOUR_PER_mSECOND / Saturn.Revolution_Cycle * Speed;
	else
		Saturn.Revolution = 0;
	//천왕성
	if (Uranus.Rotation < 360)
		Uranus.Rotation += STAR_ROTATION_HOUR_PER_mSECOND / Uranus.Roation_Cycle * Speed;
	else
		Uranus.Rotation = 0;
	if (Uranus.Revolution < 360)
		Uranus.Revolution += STAR_ROTATION_HOUR_PER_mSECOND / Uranus.Revolution_Cycle * Speed;
	else
		Uranus.Revolution = 0;
	//해왕성
	if (Neptune.Rotation < 360)
		Neptune.Rotation += STAR_ROTATION_HOUR_PER_mSECOND / Neptune.Roation_Cycle * Speed;
	else
		Neptune.Rotation = 0;
	if (Neptune.Revolution < 360)
		Neptune.Revolution += STAR_ROTATION_HOUR_PER_mSECOND / Neptune.Revolution_Cycle * Speed;
	else
		Neptune.Revolution = 0;
	glutPostRedisplay(); // 화면 재 출력
	glutTimerFunc(10, StarRotationTimerFunction, 1); // 타이머함수 재 설정
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
double * mul_vertex(double x, double y, double z, double xx, double yy, double zz)
{
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

	GLdouble vtx[] = { 0, 0, 0, 1 };
	for (int i = 0; i < 4; i++)
	{
		vtx[i] = xx * total[0 + 4*i] + yy * total[1 + 4 *i] + zz * total[2 + 4 * i];
	}
	return vtx;
}
double get_dist(double sx, double sy, double sz, double dx, double dy, double dz)
{
	return sqrt((sx - dx)*(sx - dx) + (sy - dy)*(sy - dy) + (sz - dz)*(sz - dz));
}
void Show_Info(void) {
	if (Camera.view_type() == 'N') {
		glDisable(GL_LIGHTING);
		glDisable(GL_DEPTH_TEST);
		glColor3d(1, 1, 0);
		switch (Camera.Planet_Selection)
		{
		case 1: //태양
			glPushMatrix();
			glTranslated(Sun.xPos, Sun.yPos, Sun.zPos);
			for (int i = 0; i < 11; i++) {
				glRasterPos3f(Sun.xPos + 700, Sun.yPos - 100 - i * 100, Sun.zPos + 450 + i * 12);
				int len = (int)strlen(Sun.info[i]);
				for (int j = 0; j < len; j++) {
					glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int)Sun.info[i][j]);
				}
			}
			glPopMatrix();
			break;
		case 2: //수성
			glPushMatrix();
			glRotated(Mercury.Revolution, 0, 1, 0);
			glTranslated(Mercury.xPos, Mercury.yPos, Mercury.zPos);
			glRotated(-150, 0, 1, 0);
			for (int i = 0; i < 11; i++) {
				glRasterPos3f(Mercury.Radius*1.5, Mercury.yPos + Mercury.Radius - i * Mercury.Radius / 5, Mercury.zPos);
				int len = (int)strlen(Mercury.info[i]);
				for (int j = 0; j < len; j++) {
					glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int)Mercury.info[i][j]);
				}
			}
			glPopMatrix();
			break;
		case 3: //금성
			glPushMatrix();
			glRotated(Venus.Revolution, 0, 1, 0);
			glTranslated(Venus.xPos, Venus.yPos, Venus.zPos);
			glRotated(-150, 0, 1, 0);
			for (int i = 0; i < 11; i++) {
				glRasterPos3f(Venus.Radius*1.5, Venus.yPos + Venus.Radius - i * Venus.Radius / 5, Venus.zPos);
				int len = (int)strlen(Venus.info[i]);
				for (int j = 0; j < len; j++) {
					glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int)Venus.info[i][j]);
				}
			}
			glPopMatrix();
			break;
		case 4: //지구
			glPushMatrix();
			glRotated(Earth.Revolution, 0, 1, 0);
			glTranslated(Earth.xPos, Earth.yPos, Earth.zPos);
			glRotated(-150, 0, 1, 0);
			for (int i = 0; i < 11; i++) {
				glRasterPos3f(Earth.Radius*1.5, Earth.yPos + Earth.Radius - i * Earth.Radius / 5, Earth.zPos);
				int len = (int)strlen(Earth.info[i]);
				for (int j = 0; j < len; j++) {
					glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int)Earth.info[i][j]);
				}
			}
			glPopMatrix();
			break;
		case 5: //화성
			glPushMatrix();
			glRotated(Mars.Revolution, 0, 1, 0);
			glTranslated(Mars.xPos, Mars.yPos, Mars.zPos);
			glRotated(-150, 0, 1, 0);
			for (int i = 0; i < 11; i++) {
				glRasterPos3f(Mars.Radius*1.5, Mars.yPos + Mars.Radius - i * Mars.Radius / 5, Mars.zPos);
				int len = (int)strlen(Mars.info[i]);
				for (int j = 0; j < len; j++) {
					glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int)Mars.info[i][j]);
				}
			}
			glPopMatrix();
			break;
		case 6: //목성
			glPushMatrix();
			glRotated(Jupiter.Revolution, 0, 1, 0);
			glTranslated(Jupiter.xPos, Jupiter.yPos, Jupiter.zPos);
			glRotated(-150, 0, 1, 0);
			for (int i = 0; i < 11; i++) {
				glRasterPos3f(Jupiter.Radius*1.5, Jupiter.yPos + Jupiter.Radius - i * Jupiter.Radius / 5, Jupiter.zPos);
				int len = (int)strlen(Jupiter.info[i]);
				for (int j = 0; j < len; j++) {
					glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int)Jupiter.info[i][j]);
				}
			}
			glPopMatrix();
			break;
		case 7: //토성
			glPushMatrix();
			glRotated(Saturn.Revolution, 0, 1, 0);
			glTranslated(Saturn.xPos, Saturn.yPos, Saturn.zPos);
			glRotated(-150, 0, 1, 0);
			for (int i = 0; i < 11; i++) {
				glRasterPos3f(Saturn.Radius*1.5, Saturn.yPos + Saturn.Radius - i * Saturn.Radius / 5, Saturn.zPos);
				int len = (int)strlen(Saturn.info[i]);
				for (int j = 0; j < len; j++) {
					glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int)Saturn.info[i][j]);
				}
			}
			glPopMatrix();
			break;
		case 8: //천왕성
			glPushMatrix();
			glRotated(Uranus.Revolution, 0, 1, 0);
			glTranslated(Uranus.xPos, Uranus.yPos, Uranus.zPos);
			glRotated(-150, 0, 1, 0);
			for (int i = 0; i < 11; i++) {
				glRasterPos3f(Uranus.Radius*1.5, Uranus.yPos + Uranus.Radius - i * Uranus.Radius / 5, Uranus.zPos);
				int len = (int)strlen(Uranus.info[i]);
				for (int j = 0; j < len; j++) {
					glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int)Uranus.info[i][j]);
				}
			}
			glPopMatrix();
			break;
		case 9: //해왕성
			glPushMatrix();
			glRotated(Neptune.Revolution, 0, 1, 0);
			glTranslated(Neptune.xPos, Neptune.yPos, Neptune.zPos);
			glRotated(-150, 0, 1, 0);
			for (int i = 0; i < 11; i++) {
				glRasterPos3f(Neptune.Radius*1.5, Neptune.yPos + Neptune.Radius - i * Neptune.Radius / 5, Neptune.zPos);
				int len = (int)strlen(Neptune.info[i]);
				for (int j = 0; j < len; j++) {
					glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int)Neptune.info[i][j]);
				}
			}
			glPopMatrix();
			break;
		}
		glEnable(GL_LIGHTING);
		glEnable(GL_DEPTH_TEST);
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
	for (j = 0; j < n / 2; j++) {
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
void CreateSpaceShip(void) {
	if (Camera.Planet_Selection != 10)return;

	glPushMatrix();
	glLoadIdentity();
	glTranslated(0,0, Camera.EYEz + 387.5);
	glRotated(-60, 1, 0, 0);

	//머리
	glPushMatrix();
	glColor3f(0.4, 0.4, 0.4);
	glRotated(-90, 1, 0, 0);
	glutSolidCone(1, 2, 10, 10);
	glColor3f(1, 1, 1);
	glutWireCone(1, 2, 10, 10);
	glPopMatrix();

	//몸통
	glPushMatrix();
	glColor3f(0.9, 0.9, 0.9);
	glTranslated(0, -6, 0);
	glRotated(-90, 1, 0, 0);

	glPushMatrix();
	glTranslated(0, 0.5, 3);
	glScaled(0.2, 0.1, 0.6);
	glutSolidCube(10);
	glColor3f(0.2, 0.2, 0.2);
	glutWireCube(10);
	glPopMatrix();

	glColor3f(0.9, 0.9, 0.9);
	glutSolidCylinder(1, 6, 10, 10);
	glColor3f(0.2, 0.2, 0.2);
	glutWireCylinder(1, 6, 10, 10);
	glPopMatrix();

	//팔
	glPushMatrix();
	glColor3f(0.5, 0.5, 0.5);
	glTranslated(0, -2.8, -0.3);

	glBegin(GL_TRIANGLES);
	glVertex3f(0, 3, 0);
	glVertex3f(-3.5, -3, 0);
	glVertex3f(3.5, -3, 0);

	glVertex3f(0, -3, -0.5);
	glVertex3f(-3.5, -3, -0.5);
	glVertex3f(3.5, -3, -0.5);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(0, 3, 0);
	glVertex3f(-3.5, -3, 0);
	glVertex3f(-3.5, -3, -0.5);
	glVertex3f(0, 3, -0.5);

	glVertex3f(0, 3, 0);
	glVertex3f(3.5, -3, 0);
	glVertex3f(3.5, -3, -0.5);
	glVertex3f(0, 3, -0.5);

	glVertex3f(-3.5, -3, 0);
	glVertex3f(-3.5, -3, -0.5);
	glVertex3f(3.5, -3, -0.5);
	glVertex3f(3.5, -3, 0);
	glEnd();
	glPopMatrix();

	//추진체
	glPushMatrix();
	glColor3f(0.2, 0.2, 0.2);
	glTranslated(0, -2.8, -0.3);

	glTranslated(-0.5, -3.6, 0);
	glRotated(-90, 1, 0, 0);
	glutSolidCone(0.4, 1, 30, 30);
	glutWireCone(0.4, 1, 30, 30);

	glTranslated(1, 0, 0);
	glutSolidCone(0.4, 1, 30, 30);
	glutWireCone(0.4, 1, 30, 30);
	glPopMatrix();

	glPushMatrix();

	glTranslated(-0.5, -3.6, 0);
	glRotated(-90, 1, 0, 0);
	glTranslated(0, 0.3, -3.1);
	glPushMatrix();
	glDisable(GL_LIGHTING);
	double rand_colors[20];
	rand_colors[0] = rand() % 20;
	for (int i = 0; i < 20; i++) {
		if (i != 0)
			rand_colors[i] = rand_colors[0] * (1 - i / 20.0);
	}
	for (int i = 0; i < 20; i++)
	{
		glTranslated(0, 0, -i * 0.05);
		glColor3d(1, 1- rand_colors[i] /20.0, 0);
		glutSolidSphere(0.4, 30, 30);
	}

	glPopMatrix();
	glTranslated(1, 0, 0);
	for (int i = 0; i < 20; i++)
	{
		glTranslated(0, 0, -i * 0.05);
		glColor3d(1, 1 - rand_colors[i] / 20.0, 0);
		glutSolidSphere(0.4, 30, 30);
	}
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPopMatrix();
	glColor3d(1, 1, 1);
}
void drawTorus(double r = 0.07, double c = 0.15, int rSeg = 16, int cSeg = 8) {

	/*
	r = torus ring radius
	c = torus tube radius
	rSeg, cSeg = number of segments/detail
	*/
	glEnable(GL_TEXTURE_2D);
	glFrontFace(GL_CW);
	glBindTexture(GL_TEXTURE_2D, textures[10]);
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	const double TAU = 2 * PI;

	for (int i = 0; i < rSeg; i++) {
		glBegin(GL_QUAD_STRIP);
		for (int j = 0; j <= cSeg; j++) {
			for (int k = 0; k <= 1; k++) {
				double s = (i + k) % rSeg + 0.5;
				double t = j % (cSeg + 1);

				double x = (c + r * cos(s * TAU / rSeg)) * cos(t * TAU / cSeg);
				double y = (c + r * cos(s * TAU / rSeg)) * sin(t * TAU / cSeg);
				double z = r * sin(s * TAU / rSeg);

				double u = (i + k) / (float)rSeg;
				double v = t / (float)cSeg;

				glTexCoord2d(u, v);
				glNormal3f(2 * x, 2 * y, 2 * z);
				glVertex3d(2 * x, 2 * y, 2 * z);
			}
		}
		glEnd();
	}
	glFrontFace(GL_CCW);
	glDisable(GL_TEXTURE_2D);
}