#pragma once
#include "BasicSetUp.h"

struct Star_Sun {
	double xPos = 0, yPos = 0, zPos = 0; //위치 좌표 (0, 0, 0)
	double Radius = 250; //반지름 250
	int RGB[3] = { 100, 48, 17 }; //주황(200, 96, 35)
	double Rotation_Cycle = STAR_ROTATION_HOUR_PER_mSECOND * 24 * 27; //자전 주기 27일
	double Rotation = 0;

	//const char* string = "string sample";
	const char info[10][60] = { {"Name : The Sun"},{"Luminous Intensity : 3.846 x 10^26 W"},{"Diameter : 1,392,684 km"},
	{"Mass : 1.98855 x 10^30 kg"},	{"Rotate Cycle : 27 Day"}, {"Atmosphere : Hydrogen(73%), Helium (24%)"},
	{"Surface Temperature : 5,500 degrees"}, {"Center Temperature : 15,000,000 degrees"}, {"Age : 4.567 billion "}, {"Gravity : 28G"} };
}Sun;