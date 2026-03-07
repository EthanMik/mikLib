#include "vex.h"

void odom45::set_physical_distances(float right_tracker_center_distance, float left_tracker_center_distance) {
    this->right_tracker_center_distance = right_tracker_center_distance;
    this->left_tracker_center_distance = left_tracker_center_distance;
}

void odom45::set_position(point position, float orientation_deg, float right_tracker_position, float left_tracker_position) {
    this->right_tracker_position = right_tracker_position;
    this->left_tracker_position = left_tracker_position;
    this->position = position;
    this->orientation_deg = orientation_deg;
}

void odom45::update_position(float right_tracker_position, float left_tracker_position, float orientation_deg) {
    float right_delta = right_tracker_position - this->right_tracker_position;
    float left_delta = left_tracker_position - this->left_tracker_position;
    float orientation_delta = orientation_deg - this->orientation_deg;

    this->right_tracker_position = right_tracker_position;
    this->left_tracker_position = left_tracker_position;
    this->orientation_deg = orientation_deg;
    
    orientation_delta = reduce_negative_180_to_180(orientation_delta);
    float orientation_delta_rad = to_rad(orientation_delta);

    if (right_delta == 0.0 && left_delta == 0.0 && orientation_delta == 0.0) return;

    const float inv_sqrt2 = 1.0 / sqrt(2.0);

    float forward  = (right_delta + left_delta) * inv_sqrt2;
    float side = (right_delta - left_delta) * inv_sqrt2;

    float local_X_position;
    float local_Y_position;

    if (fabs(orientation_delta) == 0) {
        local_X_position  = side;
        local_Y_position = forward;
    } else {
        local_X_position = (2 * sin(orientation_delta_rad / 2)) * ((side / orientation_delta_rad) + right_tracker_center_distance); 
        local_Y_position = (2 * sin(orientation_delta_rad / 2)) * ((forward / orientation_delta_rad) + left_tracker_center_distance);
    }

    float avg_heading_deg = reduce_negative_180_to_180(orientation_deg - 0.5f * orientation_delta);

    float polar_r = sqrt(local_X_position * local_X_position + local_Y_position * local_Y_position);
    float polar_angle = atan2(local_Y_position, local_X_position) - to_rad(avg_heading_deg);

    float dX = polar_r * cos(polar_angle);
    float dY = polar_r * sin(polar_angle);

    position.x += dX;
    position.y += dY;
}
