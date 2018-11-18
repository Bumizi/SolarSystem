#include "BasicSetUp.h"
#include "Sun.h"

struct Mercury {
	double xPos = Sun.Radius + DISTANCE_FROM_SUN_TO_MERCURY + 4, yPos = 0, zPos = 0; //��ġ ��ǥ (250+100+4, 0, 0)
	double Radius = 4; //������ 4
	int RGB[3]; //ȸ��(120, 120, 120)
	double Roation_Cycle = STAR_ROTATION_HOUR_PER_mSECOND * 24 * 58; //���� �ֱ� 58��
	double Rotation = 0;
	double Revolution_Cycle = STAR_REVOLUTION_DAY_PER_mSECOND * 88; //���� �ֱ� 88��
	double Revolution = 0;
}Mercury;