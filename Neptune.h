#pragma once
#include "BasicSetUp.h"
#include "Uranus.h"

struct Star_Neptune {
	double xPos = Uranus.xPos + Uranus.Radius + DISTANCE_FROM_URANUS_TO_NEPTUNE + 36, yPos = 0, zPos = 0; //위치 좌표 (천왕성+38+100+36, 0, 0)
	double Radius = 36; //반지름 36
	double Orbit_Degree = 0;
	int RGB[3] = { 0, 0, 120 }; //파랑(0, 0, 255)
	double Roation_Cycle = STAR_ROTATION_HOUR_PER_mSECOND * 16; //자전 주기 16시간
	double Rotation = 0;
	double Revolution_Cycle = STAR_REVOLUTION_DAY_PER_mSECOND * 60182; //공전 주기 60182일
	double Revolution = 0;
	const char info[11][60] = { { "Name   :   Neptune" },{ "Diameter   :   49,528 km" },{ "Volume   :   6.254 x 10^13 km^3 " },{ "Mass   :   1.0243 x 10^26 kg" },
	{ "Rotation Period   :   16 Hour" },{ "Orbital Period   :   60,223 Day (164.8 Year)" },{ "Surface Gravity   :   1.14 G" },{ "Atmosphere   :   Hydrogen(80%), Helium(19%)" },
	{ "Surface Temperature (avg)   :   -218 'C" }, { "Satellites   :   14" } };
}Neptune;