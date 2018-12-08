#pragma once
#include "BasicSetUp.h"
#include "Mars.h"

struct Star_Jupiter {
	double xPos = Mars.xPos + Mars.Radius + DISTANCE_FROM_MARS_TO_JUPITER + 112, yPos = 0, zPos = 0; //위치 좌표 (화성+6+200+112, 0, 0)
	double Radius = 112; //반지름 112
	double Orbit_Degree = 0;
	int RGB[3] = { 80, 20, 20 }; //갈색(162, 42, 42)
	double Roation_Cycle = STAR_ROTATION_HOUR_PER_mSECOND * 10; //자전 주기 10시간
	double Rotation = 0;
	double Revolution_Cycle = STAR_REVOLUTION_DAY_PER_mSECOND * 4332; //공전 주기 4332일
	double Revolution = 0;
	const char info[11][60] = { { "Name   :   Jupiter" },{ "Diameter   :   139,822 km" },{ "Volume   :   1.4313 x 10^15 km^3 " },{ "Mass   :   1.8986 x 10^27 kg" },
	{ "Rotation Period   :   10 Hour" },{ "Orbital Period   :   4,332 Day (11.8 Year)" },{ "Surface Gravity   :   25 G" },{ "Atmosphere   :   Hydrogen(89%), Helium(10%)" },
	{ "Surface Temperature (avg)  :   -108 'C" }, { "Satellites   :   79" } };
}Jupiter;