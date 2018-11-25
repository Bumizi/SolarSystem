#pragma once
#define _USE_MATH_DEFINES
#include <math.h>

struct Camera {
	double EYEx = 0, EYEy = 900, EYEz = 1600;
	double ATx = 0, ATy = 0, ATz = 0;
	double UPx = 0, UPy = 1, UPz = 0;
	double rtx = 0, rty = 0, rtz = 0;
	double mvx = 0, mvy = 0, mvz = 0;
	void set_pos(double x, double y, double z);
	char view_type(void);
	void move_up(double value);
	void move_down(double value);
	void move_left(double value);
	void move_right(double value);
	void move_front(double value);
	void move_back(double value);
	void invalidate_values(void);
	void rotate(double x, double y, double z);
}Camera;

//���� ī�޶� ���� ������ �˾Ƴ�
char Camera::view_type(void) {
	if (EYEx == 0 && EYEy == 900 && EYEz == 1600)
		return 'D';
	if (EYEx == 0 && EYEy == 900 && EYEz == 0)
		return 'T';
	if (EYEx == 0 && EYEy == 0 && EYEz == 1600)
		return 'F';
	return 'N';
}

//ī�޶� �̵��� ����
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

//���� �Ŀ� ȸ���� ���߰� ���ִ� �Լ�
//�� �Լ��� ���ٸ� �� �� ������ �� ��� ����� ����.
void Camera::invalidate_values(void) {
	mvx = 0, mvy = 0, mvz = 0;
	rtx = 0, rty = 0, rtz = 0;
}


//ž��(0, 900, 0)
//����Ʈ ��(0, 0, 1600)
//����Ʈ ��(0, 900, 1600)
//ī�޶� ��ġ ���� �� ����
void Camera::set_pos(double x, double y, double z) {
	EYEx = x, EYEy = y, EYEz = z;
	mvx = 0, mvy = 0, mvz = 0;
	printf("EYE�� ���� : %lf, %lf, %lf\n", EYEx, EYEy, EYEz);
	switch (view_type())
	{
	case 'T':
		ATx = 0, ATy = 0, ATz = -1;
		break;
	case 'F':
		ATx = 0, ATy = 1, ATz = 0;
		break;
	}
}