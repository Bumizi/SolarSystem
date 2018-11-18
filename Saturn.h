#include "BasicSetUp.h"
#include "Jupiter.h"

struct Saturn {
	double xPos = Jupiter.xPos + Jupiter.Radius + DISTANCE_FROM_JUPITER_TO_SATURN + 90, yPos = 0, zPos = 0; //��ġ ��ǥ (��+112+150+90, 0, 0)
	double Radius = 90; //������ 90
	int RGB[3]; //Ȳ��(218, 165, 32)
	double Roation_Cycle = STAR_ROTATION_HOUR_PER_mSECOND * 10; //���� �ֱ� 10�ð�
	double Rotation = 0;
	double Revolution_Cycle = STAR_REVOLUTION_DAY_PER_mSECOND * 10759; //���� �ֱ� 10759��
	double Revolution = 0;
}Saturn;