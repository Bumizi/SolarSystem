#pragma once
#include "BasicSetUp.h"
#include "Saturn.h"

struct Star_Uranus {
	double xPos = Saturn.xPos + Saturn.Radius + DISTANCE_FROM_SATURN_TO_URANUS + 38, yPos = 0, zPos = 0; //위치 좌표 (토성+90+100+38, 0, 0)
	double Radius = 38; //반지름 38
	int RGB[3] = { 0, 120, 120 }; //하늘(0, 255, 255)
	double Roation_Cycle = STAR_ROTATION_HOUR_PER_mSECOND * 17; //자전 주기 17시간
	double Rotation = 0;
	double Revolution_Cycle = STAR_REVOLUTION_DAY_PER_mSECOND * 30688; //공전 주기 30688일
	double Revolution = 0;
}Uranus;