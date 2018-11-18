#include "BasicSetUp.h"
#include "Venus.h"

struct Earth {
	double xPos = Venus.xPos + Venus.Radius + DISTANCE_FROM_VENUS_TO_EARTH + 12, yPos = 0, zPos = 0; //위치 좌표 (금성+10+50+12, 0, 0)
	double Radius = 12; //반지름 12
	int RGB[3]; //초록(0, 255, 0)
	double Roation_Cycle = STAR_ROTATION_HOUR_PER_mSECOND * 24 * 1; //자전 주기 1일
	double Rotation = 0;
	double Revolution_Cycle = STAR_REVOLUTION_DAY_PER_mSECOND * 365; //공전 주기 365일
	double Revolution = 0;
}Earth;