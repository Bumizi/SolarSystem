#pragma once
#include "BasicSetUp.h"
#include "Sun.h"

struct Star_Mercury {
	double xPos = Sun.Radius + DISTANCE_FROM_SUN_TO_MERCURY + 4, yPos = 0, zPos = 0; //위치 좌표 (250+100+4, 0, 0)
	double Radius = 4; //반지름 4
	double Orbit_Degree = 0;
	int RGB[3] = { 120, 120, 120 }; //회색(120, 120, 120)
	double Roation_Cycle = STAR_ROTATION_HOUR_PER_mSECOND * 24 * 58; //자전 주기 58일
	double Rotation = 0;
	double Revolution_Cycle = STAR_REVOLUTION_DAY_PER_mSECOND * 88; //공전 주기 88일
	double Revolution = 0;
	const char info[11][60] = { { "Name   :   Mercury" },{ "Diameter   :   4,879 km" },{ "Volume   :   6.083 x 10^10 km^3 " },{ "Mass   :   3.023 x 10^23 kg" },
	{ "Rotation Period   :   58 Day" },{ "Orbital Period   :   88 Day" },{ "Surface Gravity   :   0.37 G" },{ "Atmosphere   :   Oxygen(42%), Sodium(29%)" },
	{ "Surface Temperature (max)   :   427 'C" },{ "Surface Temperature (min)   :   -173 'C" },{ "Satellites   :   0" } };
}Mercury;