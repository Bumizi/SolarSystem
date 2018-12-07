#pragma once
#include "BasicSetUp.h"
#include "Mercury.h"

struct Star_Venus {
	double xPos = Mercury.xPos + Mercury.Radius + DISTANCE_FROM_MERCURY_TO_VENUS + 10, yPos = 0, zPos = 0; //위치 좌표 (수성+4+50+10, 0, 0)
	double Radius = 10; //반지름 10
	double Orbit_Degree = 0;
	int RGB[3] = { 120, 120, 0 }; //노랑(255, 255, 0)
	double Roation_Cycle = STAR_ROTATION_HOUR_PER_mSECOND * 24 * 243; //자전 주기 243일
	double Rotation = 0;
	double Revolution_Cycle = STAR_REVOLUTION_DAY_PER_mSECOND * 224; //공전 주기 224일
	double Revolution = 0;
	const char info[11][60] = { { "Name : Venus" },{ "Diameter : 12,103 km" },{ "Volume : 9.28 x 10^11 km^3 " },{ "Mass : 4.8685 x 10^24 kg" },
	{ "Rotation Period : 243 Day" },{ "Orbital Period : 224 Day" },{ "Surface Gravity : 0.904 G" },{ "Atmosphere : Carbon Dioxide(96%), Nitrogen(3%)" },
	{ "Surface Temperature (max) : 500 'C" },{ "Surface Temperature (min) : -45 'C" },{ "Satellites : 0" } };
}Venus;