#pragma once
#include "BasicSetUp.h"
#include "Saturn.h"

struct Star_Uranus {
	double xPos = Saturn.xPos + Saturn.Radius + DISTANCE_FROM_SATURN_TO_URANUS + 38, yPos = 0, zPos = 0; //위치 좌표 (토성+90+100+38, 0, 0)
	double Radius = 38; //반지름 38
	double Orbit_Degree = 0;
	int RGB[3] = { 0, 120, 120 }; //하늘(0, 255, 255)
	double Roation_Cycle = STAR_ROTATION_HOUR_PER_mSECOND * 17; //자전 주기 17시간
	double Rotation = 0;
	double Revolution_Cycle = STAR_REVOLUTION_DAY_PER_mSECOND * 30688; //공전 주기 30688일
	double Revolution = 0;
	const char info[11][60] = { { "Name   :   Uranus" },{ "Diameter   :   51,118 km" },{ "Volume   :   6.834 x 10^13 km^3 " },{ "Mass   :   8.6832 x 10^25 kg" },
	{ "Rotation Period   :   17 Hour" },{ "Orbital Period   :   30,707 Day (84.07 Year)" },{ "Surface Gravity   :   0.88 G" },{ "Atmosphere   :   Hydrogen(83%), Helium(15%)" },
	{ "Surface Temperature (max)   :   -216 'C" }, { "Surface Temperature (min)   :   -224 'C" }, { "Satellites   :   27" } };
}Uranus;