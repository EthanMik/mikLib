#pragma once

/**
 * @brief General-use odometry class with X_position, Y_position, and
 * orientation_deg being the relevant outputs. This works for one
 * and two-tracker systems, and needs a gyro to get input angle.
 */
class odom
{
public:
	/**
	 * @brief Setter method for tracker center distances.
	 * The forward tracker center distance is the horizontal distance from the 
	 * center of the robot to the center of the wheel the sensor is measuring.
	 * The sideways tracker center distance is the vertical distance from the 
	 * center of the robot to the center of the sideways wheel being measured.
	 * If there's really no sideways wheel we set the center distance to 0 and
	 * pretend the wheel never spins, which is equivalent to a no-drift robot.
	 * 
	 * @param ForwardTracker_center_distance A horizontal distance to the wheel center in inches.
	 * @param SidewaysTracker_center_distance A vertical distance to the wheel center in inches.
	 */
	void set_physical_distances(float ForwardTracker_center_distance, float SidewaysTracker_center_distance);

	/**
	 * Resets the position, including tracking wheels.
	 * Position is field-centric, and orientation is such that 0 degrees
	 * is in the positive Y direction. Orientation can be provided with 
	 * some flexibility, including less than 0 and greater than 360.
	 * 
	 * @param position Field-centric x and y position of the robot.
	 * @param orientation_deg Field-centered, clockwise-positive, orientation.
	 * @param ForwardTracker_position Current position of the sensor in inches.
	 * @param SidewaysTracker_position Current position of the sensor in inches.
	 */
	void set_position(point position, float orientation_deg, float ForwardTracker_position, float SidewaysTracker_position);

	/**
	 * Does the odometry math to update position
	 * Uses the Pilons arc method outline here: https://wiki.purduesigbots.com/software/odometry
	 * All the deltas are done by getting member variables and comparing them to 
	 * the input. Ultimately this all works to update the public member variable
	 * X_position. This function needs to be run at 200Hz or so for best results.
	 * 
	 * @param ForwardTracker_position Current position of the sensor in inches.
	 * @param SidewaysTracker_position Current position of the sensor in inches.
	 * @param orientation_deg Field-centered, clockwise-positive, orientation.
	 */
	void update_position(float ForwardTracker_position, float SidewaysTracker_position, float orientation_deg);

	point position;
	float orientation_deg; 

private:
	float ForwardTracker_center_distance;
	float SidewaysTracker_center_distance;
	float ForwardTracker_position;
	float SideWaysTracker_position;
};