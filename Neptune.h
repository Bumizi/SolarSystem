#pragma once
#include "BasicSetUp.h"
#include "Uranus.h"

struct Star_Neptune {
	double xPos = Uranus.xPos + Uranus.Radius + DISTANCE_FROM_URANUS_TO_NEPTUNE + 36, yPos = 0, zPos = 0; //위치 좌표 (천왕성+38+100+36, 0, 0)
	double Radius = 36; //반지름 36
	int RGB[3] = { 0, 0, 120 }; //파랑(0, 0, 255)
	double Roation_Cycle = STAR_ROTATION_HOUR_PER_mSECOND * 16; //자전 주기 16시간
	double Rotation = 0;
	double Revolution_Cycle = STAR_REVOLUTION_DAY_PER_mSECOND * 60182; //공전 주기 60182일
	double Revolution = 0;
}Neptune;