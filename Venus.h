#pragma once
#include "BasicSetUp.h"
#include "Mercury.h"

struct Star_Venus {
	double xPos = Mercury.xPos + Mercury.Radius + DISTANCE_FROM_MERCURY_TO_VENUS + 10, yPos = 0, zPos = 0; //��ġ ��ǥ (����+4+50+10, 0, 0)
	double Radius = 10; //������ 10
	int RGB[3] = { 120, 120, 0 }; //���(255, 255, 0)
	double Roation_Cycle = STAR_ROTATION_HOUR_PER_mSECOND * 24 * 243; //���� �ֱ� 243��
	double Rotation = 0;
	double Revolution_Cycle = STAR_REVOLUTION_DAY_PER_mSECOND * 224; //���� �ֱ� 224��
	double Revolution = 0;
}Venus;