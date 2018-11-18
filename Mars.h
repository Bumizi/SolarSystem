#include "BasicSetUp.h"
#include "Earth.h"

struct Star_Mars {
	double xPos = Earth.xPos + Earth.Radius + DISTANCE_FROM_EARTH_TO_MARS + 6, yPos = 0, zPos = 0; //��ġ ��ǥ (����+12+50+6, 0, 0)
	double Radius = 6; //������ 6
	int RGB[3] = { 255, 0, 0 }; //����(255, 0, 0)
	double Roation_Cycle = STAR_ROTATION_HOUR_PER_mSECOND * 24 * 1; //���� �ֱ� 1��
	double Rotation = 0;
	double Revolution_Cycle = STAR_REVOLUTION_DAY_PER_mSECOND * 687; //���� �ֱ� 687��
	double Revolution = 0;
}Mars;