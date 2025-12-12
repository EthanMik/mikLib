#include "vex.h"

void odom45::set_physical_distances(float lat_offset, float long_offset) {
    this->lat_offset = lat_offset;
    this->long_offset = long_offset;
}

void odom45::set_position(point position, float orientation_deg, float lat_position, float long_position) {
    this->lat_position = lat_position;
    this->long_position = long_position;
    this->position = position;
    this->orientation_deg = orientation_deg;
}

void odom45::update_position(float lat_position, float long_position, float orientation_deg) {
    float delta_lat_position  = lat_position  - this->lat_position;
    float delta_long_position = long_position - this->long_position;
    float delta_orientation_deg = orientation_deg - this->orientation_deg;

    this->lat_position = lat_position;
    this->long_position = long_position;
    this->orientation_deg = orientation_deg;

    delta_orientation_deg = reduce_negative_180_to_180(delta_orientation_deg);

    float local_lat_position;
    float local_long_position;

    if (delta_orientation_deg != 0) {
        float delta_orientation_rad = delta_orientation_deg * (M_PI / 180.0);
        float s = sin(delta_orientation_rad / 2.0);

        local_lat_position  = 2.0 * s * (delta_lat_position / delta_orientation_rad + lat_offset);
        local_long_position = 2.0 * s * (delta_long_position   / delta_orientation_rad + long_offset);
    } else {
        local_lat_position  = delta_lat_position;
        local_long_position = delta_long_position;
    }

    double avgDeg = reduce_negative_180_to_180(orientation_deg - 0.5 * delta_orientation_deg);

    double dX =  local_lat_position * cos(to_rad(avgDeg)) + local_long_position * sin(to_rad(avgDeg));
    double dY = -local_lat_position * sin(to_rad(avgDeg)) + local_long_position * cos(to_rad(avgDeg));

    position.x += dX;
    position.y += dY;
}