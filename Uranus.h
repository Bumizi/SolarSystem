#pragma once
#include "BasicSetUp.h"
#include "Saturn.h"

struct Star_Uranus {
	double xPos = Saturn.xPos + Saturn.Radius + DISTANCE_FROM_SATURN_TO_URANUS + 38, yPos = 0, zPos = 0; //��ġ ��ǥ (�伺+90+100+38, 0, 0)
	double Radius = 38; //������ 38
	int RGB[3] = { 0, 120, 120 }; //�ϴ�(0, 255, 255)
	double Roation_Cycle = STAR_ROTATION_HOUR_PER_mSECOND * 17; //���� �ֱ� 17�ð�
	double Rotation = 0;
	double Revolution_Cycle = STAR_REVOLUTION_DAY_PER_mSECOND * 30688; //���� �ֱ� 30688��
	double Revolution = 0;
}Uranus;