#pragma once
#include "BasicSetUp.h"

struct Star_Sun {
	double xPos = 0, yPos = 0, zPos = 0; //위치 좌표 (0, 0, 0)
	double Radius = 250; //반지름 250
	int RGB[3] = { 100, 48, 17 }; //주황(200, 96, 35)
	double Rotation_Cycle = STAR_ROTATION_HOUR_PER_mSECOND * 24 * 27; //자전 주기 27일
	double Rotation = 0;

	//const char* string = "string sample";
	const char info[11][60] = { {"Name   :   The Sun"}, {"Diameter   :   1,392,684 km"},{ "Volume   :   1.41 x 10^18 km^3 " }, {"Mass   :   1.98855 x 10^30 kg"},
	{ "Luminous Intensity   :   3.846 x 10^26 W" }, {"Rotation Period   :   27 Day"}, { "Surface Gravity   :  28 G" }, {"Atmosphere   :   Hydrogen(73%), Helium(24%)"},
	{"Surface Temperature   :   5,500 `C"}, {"Center Temperature   :   15,000,000 `C"}};
}Sun;