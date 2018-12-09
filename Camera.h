#pragma once
#define _USE_MATH_DEFINES
#include <math.h>

struct Camera {
	double EYEx = 0, EYEy = 900, EYEz = 1600;
	double ATx = 0, ATy = 0, ATz = 0;
	double UPx = 0, UPy = 1, UPz = 0;
	double rtx = 0, rty = 0, rtz = 0;
	double mvx = 0, mvy = 0, mvz = 0;
	int Planet_Selection = 0;
	void set_pos(double x, double y, double z);
	char view_type(void);
	void move_up(double value);
	void move_down(double value);
	void move_left(double value);
	void move_right(double value);
	void move_front(double value);
	void move_back(double value);
	void invalidate_values(void);
	void rotatex(double value);
	void rotatey(double value);
	void rotatez(double value);
	void set_at(double x, double y, double z);
}Camera;

//현재 카메라 뷰의 종류를 알아냄
char Camera::view_type(void) {
	if (EYEx == 0 && EYEy == 900 && EYEz == 1600)
		return 'D';
	if (EYEx == 0 && EYEy == 900 && EYEz == 0)
		return 'T';
	if (EYEx == 0 && EYEy == 0 && EYEz == 1600)
		return 'F';
	return 'N';
}

//카메라 이동에 쓰임
void Camera::move_up(double value) {
	mvy += value;
}
void Camera::move_down(double value) {
	mvy -= value;
}
void Camera::move_left(double value) {
	mvx -= value;
}
void Camera::move_right(double value) {
	mvx += value;
}
void Camera::move_front(double value) {
	mvz += value;
}
void Camera::move_back(double value) {
	mvz -= value;
}

//초기화
void Camera::invalidate_values(void) {
	mvx = 0, mvy = 0, mvz = 0;
	rtx = 0, rty = 0, rtz = 0;
}

//카메라 회전 함수
void Camera::rotatex(double value)
{
	rtx += value;
	if (rtx > 360) rtx -= 360;
	if (rtx < 0) rtx += 360;
}
void Camera::rotatey(double value)
{
	rty += value;
	if (rty > 360) rty -= 360;
	if (rty < 0) rty += 360;
}
void Camera::rotatez(double value)
{
	rtz += value;
	if (rtz > 360) rtz -= 360;
	if (rtz < 0) rtz += 360;
}

//탑뷰(0, 900, 0)
//프런트 뷰(0, 0, 1600)
//디폴트 뷰(0, 900, 1600)
//카메라 위치 변경 시 쓰임
void Camera::set_pos(double x, double y, double z) {
	EYEx = x, EYEy = y, EYEz = z;
	
	//printf("EYE값 변경 : %lf, %lf, %lf\n", EYEx, EYEy, EYEz);
	switch (view_type())
	{
	case 'T':
		ATx = 0, ATy = 0, ATz = -1;
		break;
	case 'F':case 'D':
		ATx = 0, ATy = 1, ATz = 0;
		break;
	}
}

void Camera::set_at(double x, double y, double z)
{
	ATx = x; ATy = y; ATz = z;
}

