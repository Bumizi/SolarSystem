#include "BasicSetUp.h"
#include "Mars.h"

struct Star_Jupiter {
	double xPos = Mars.xPos + Mars.Radius + DISTANCE_FROM_MARS_TO_JUPITER + 112, yPos = 0, zPos = 0; //��ġ ��ǥ (ȭ��+6+200+112, 0, 0)
	double Radius = 112; //������ 112
	int RGB[3] = { 162, 42, 42 }; //����(162, 42, 42)
	double Roation_Cycle = STAR_ROTATION_HOUR_PER_mSECOND * 10; //���� �ֱ� 10�ð�
	double Rotation = 0;
	double Revolution_Cycle = STAR_REVOLUTION_DAY_PER_mSECOND * 4332; //���� �ֱ� 4332��
	double Revolution = 0;
}Jupiter;