#include "BasicSetUp.h"
#include "Mars.h"

struct Star_Jupiter {
	double xPos = Mars.xPos + Mars.Radius + DISTANCE_FROM_MARS_TO_JUPITER + 112, yPos = 0, zPos = 0; //위치 좌표 (화성+6+200+112, 0, 0)
	double Radius = 112; //반지름 112
	int RGB[3] = { 162, 42, 42 }; //갈색(162, 42, 42)
	double Roation_Cycle = STAR_ROTATION_HOUR_PER_mSECOND * 10; //자전 주기 10시간
	double Rotation = 0;
	double Revolution_Cycle = STAR_REVOLUTION_DAY_PER_mSECOND * 4332; //공전 주기 4332일
	double Revolution = 0;
}Jupiter;