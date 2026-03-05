#include "mikLib/drive.h"

void odom::set_physical_distances(float forward_tracker_center_distance, float sideways_tracker_center_distance){
    this->forward_tracker_center_distance = forward_tracker_center_distance;
    this->sideways_tracker_center_distance = sideways_tracker_center_distance;
}

void odom::set_position(point position, float orientation_deg, float forward_tracker_position, float sideways_tracker_position){
    this->forward_tracker_position = forward_tracker_position;
    this->sideways_tracker_position = sideways_tracker_position;
    this->position = position;
    this->orientation_deg = orientation_deg;
}

void odom::update_position(float forward_tracker_position, float sideways_tracker_position, float orientation_deg){
    float forward_delta = forward_tracker_position - this->forward_tracker_position;
    float sideways_delta = sideways_tracker_position - this->sideways_tracker_position;

    this->forward_tracker_position = forward_tracker_position;
    this->sideways_tracker_position = sideways_tracker_position;

    float orientation_rad = to_rad(orientation_deg);
    float prev_orientation_rad = to_rad(this->orientation_deg);
    float orientation_delta_rad = orientation_rad - prev_orientation_rad;

    this->orientation_deg = orientation_deg;
    
    float local_X_position;
    float local_Y_position;

    // All of the following lines are pretty well documented in 5225A's Into to Position Tracking 
    // Document at http://thepilons.ca/wp-content/uploads/2018/10/Tracking.pdf 

    if (fabs(orientation_delta_rad) < 1e-7) {
        local_X_position = sideways_delta;
        local_Y_position = forward_delta;
    } else {
        local_X_position = (2 * sin(orientation_delta_rad / 2)) * ((sideways_delta / orientation_delta_rad) + sideways_tracker_center_distance); 
        local_Y_position = (2 * sin(orientation_delta_rad / 2)) * ((forward_delta / orientation_delta_rad) + forward_tracker_center_distance);
    }

    float local_polar_angle;
    float local_polar_length;

    if (fabs(local_X_position) < 1e-7 && fabs(local_Y_position) < 1e-7){
        local_polar_angle = 0;
        local_polar_length = 0;
    } else {
        local_polar_angle = atan2(local_Y_position, local_X_position); 
        local_polar_length = sqrt(pow(local_X_position, 2) + pow(local_Y_position, 2)); 
    }

    float global_polar_angle = local_polar_angle - prev_orientation_rad - (orientation_delta_rad / 2);

    float X_position_delta = local_polar_length * cos(global_polar_angle); 
    float Y_position_delta = local_polar_length * sin(global_polar_angle);

    position.x += X_position_delta;
    position.y += Y_position_delta;
}