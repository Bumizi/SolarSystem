#include "BasicSetUp.h"
#include "Venus.h"

struct Earth {
	double xPos = Venus.xPos + Venus.Radius + DISTANCE_FROM_VENUS_TO_EARTH + 12, yPos = 0, zPos = 0; //��ġ ��ǥ (�ݼ�+10+50+12, 0, 0)
	double Radius = 12; //������ 12
	int RGB[3]; //�ʷ�(0, 255, 0)
	double Roation_Cycle = STAR_ROTATION_HOUR_PER_mSECOND * 24 * 1; //���� �ֱ� 1��
	double Rotation = 0;
	double Revolution_Cycle = STAR_REVOLUTION_DAY_PER_mSECOND * 365; //���� �ֱ� 365��
	double Revolution = 0;
}Earth;