#pragma once

#include "util.h"

class odom45
{
public:
	void set_physical_distances(float long_offset, float lat_offset);
	void set_position(point position, float orientation_deg, float lat_position, float long_position);
	void update_position(float long_position, float lat_position, float orientation_deg);

	point position;
	float orientation_deg;

private:
	float lat_offset;
	float long_offset;

	float long_position;
	float lat_position;
};