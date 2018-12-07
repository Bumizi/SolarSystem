#pragma once
#include "BasicSetUp.h"
#include "Jupiter.h"

struct Star_Saturn {
	double xPos = Jupiter.xPos + Jupiter.Radius + DISTANCE_FROM_JUPITER_TO_SATURN + 90, yPos = 0, zPos = 0; //��ġ ��ǥ (��+112+150+90, 0, 0)
	double Radius = 90; //������ 90
	double Orbit_Degree = 0;
	int RGB[3] = { 109, 82, 16 }; //Ȳ��(218, 165, 32)
	double Roation_Cycle = STAR_ROTATION_HOUR_PER_mSECOND * 10; //���� �ֱ� 10�ð�
	double Rotation = 0;
	double Revolution_Cycle = STAR_REVOLUTION_DAY_PER_mSECOND * 10759; //���� �ֱ� 10759��
	double Revolution = 0;
	const char info[11][60] = { { "Name : Saturn" },{ "Diameter : 120,536 km" },{ "Volume : 8.27 x 10^14 km^3 " },{ "Mass : 5.6846 x 10^26 kg" },
	{ "Rotation Period : 10 Hour" },{ "Orbital Period : 10,759 Day (29.4 Year)" },{ "Surface Gravity : 1.06 G" },{ "Atmosphere : Hydrogen(96%), Helium(3%)" },
	{ "Surface Temperature (avg) : -139 'C" },{ "Satellites : 62" } };
}Saturn;