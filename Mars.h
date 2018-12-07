#pragma once
#include "BasicSetUp.h"
#include "Earth.h"

struct Star_Mars {
	double xPos = Earth.xPos + Earth.Radius + DISTANCE_FROM_EARTH_TO_MARS + 6, yPos = 0, zPos = 0; //위치 좌표 (지구+12+50+6, 0, 0)
	double Radius = 6; //반지름 6
	double Orbit_Degree = 0;
	int RGB[3] = { 120, 0, 0 }; //빨강(255, 0, 0)
	double Roation_Cycle = STAR_ROTATION_HOUR_PER_mSECOND * 24 * 1; //자전 주기 1일
	double Rotation = 0;
	double Revolution_Cycle = STAR_REVOLUTION_DAY_PER_mSECOND * 687; //공전 주기 687일
	double Revolution = 0;
	const char info[11][60] = { { "Name : Mars" },{ "Diameter : 6,779 km" },{ "Volume : 1.6310 x 10^11 km^3 " },{ "Mass : 6.4171 x 10^23 kg" },
	{ "Rotation Period : 1 Day" },{ "Orbital Period : 687 Day (1.8 Year)" },{ "Surface Gravity : 0.37 G" },{ "Atmosphere : Carbon Dioxide(95%), Nitrogen(2%)" },
	{ "Surface Temperature (max) : 20 'C" },{ "Surface Temperature (min) : -140 'C" }, { "Satellites : Phobos, Deimos" } };
}Mars;