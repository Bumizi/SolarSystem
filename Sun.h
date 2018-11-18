#include "BasicSetUp.h"

struct Star_Sun {
	double xPos = 0, yPos = 0, zPos = 0; //위치 좌표 (0, 0, 0)
	double Radius = 250; //반지름 250
	int RGB[3] = { 200, 96, 35 }; //주황(200, 96, 35)
	double Rotation_Cycle = STAR_ROTATION_HOUR_PER_mSECOND * 24 * 27; //자전 주기 27일
	double Rotation = 0;
}Sun;