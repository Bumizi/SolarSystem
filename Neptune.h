#pragma once
#include "BasicSetUp.h"
#include "Uranus.h"

struct Star_Neptune {
	double xPos = Uranus.xPos + Uranus.Radius + DISTANCE_FROM_URANUS_TO_NEPTUNE + 36, yPos = 0, zPos = 0; //��ġ ��ǥ (õ�ռ�+38+100+36, 0, 0)
	double Radius = 36; //������ 36
	int RGB[3] = { 0, 0, 120 }; //�Ķ�(0, 0, 255)
	double Roation_Cycle = STAR_ROTATION_HOUR_PER_mSECOND * 16; //���� �ֱ� 16�ð�
	double Rotation = 0;
	double Revolution_Cycle = STAR_REVOLUTION_DAY_PER_mSECOND * 60182; //���� �ֱ� 60182��
	double Revolution = 0;
}Neptune;