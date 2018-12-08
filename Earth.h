#pragma once
#include "BasicSetUp.h"
#include "Venus.h"

struct Star_Earth {
	double xPos = Venus.xPos + Venus.Radius + DISTANCE_FROM_VENUS_TO_EARTH + 12, yPos = 0, zPos = 0; //위치 좌표 (금성+10+50+12, 0, 0)
	double Radius = 12; //반지름 12
	double Orbit_Degree = 0;
	int RGB[3] = { 0,120,0 }; //초록(0, 255, 0)
	double Roation_Cycle = STAR_ROTATION_HOUR_PER_mSECOND * 24 * 1; //자전 주기 1일
	double Rotation = 0;
	double Revolution_Cycle = STAR_REVOLUTION_DAY_PER_mSECOND * 365; //공전 주기 365일
	double Revolution = 0;
	const char info[11][60] = { { "Name   :   Earth" },{ "Diameter   :   12,756 km" },{ "Volume   :   1.0832 x 10^12 km^3 " },{ "Mass   :   5.9736 x 10^24 kg" },
	{ "Rotation Period   :   27 Day" }, { "Orbital Period   :   365 Day" }, { "Surface Gravity   :   1 G" },{ "Atmosphere   :   Nitrogen(78%), Oxygen(21%)" },
	{ "Surface Temperature (max)   :   57 'C" },{ "Surface Temperature (min)   :   -89 'C" } , { "Satellites   :   Moon" } };
}Earth;