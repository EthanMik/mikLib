#pragma once

#include "vex.h"

class odom45
{
public:
	void set_physical_distances(float right_tracker_center_distance, float left_tracker_center_distance);
	void set_position(point position, float orientation_deg, float right_tracker_position, float left_tracker_position);
	void update_position(float right_tracker_position, float left_tracker_position, float orientation_deg);

	point position;
	float orientation_deg;

private:
	float right_tracker_center_distance;
	float left_tracker_center_distance;

	float right_tracker_position;
	float left_tracker_position;
};