#include "BasicSetUp.h"
#include "Jupiter.h"

struct Saturn {
	double xPos = Jupiter.xPos + Jupiter.Radius + DISTANCE_FROM_JUPITER_TO_SATURN + 90, yPos = 0, zPos = 0; //위치 좌표 (목성+112+150+90, 0, 0)
	double Radius = 90; //반지름 90
	int RGB[3]; //황토(218, 165, 32)
	double Roation_Cycle = STAR_ROTATION_HOUR_PER_mSECOND * 10; //자전 주기 10시간
	double Rotation = 0;
	double Revolution_Cycle = STAR_REVOLUTION_DAY_PER_mSECOND * 10759; //공전 주기 10759일
	double Revolution = 0;
}Saturn;