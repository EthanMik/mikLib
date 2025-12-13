#include "vex.h"

void odom45::set_physical_distances(float long_offset, float lat_offset) {
    this->lat_offset = lat_offset;
    this->long_offset = long_offset;
}

void odom45::set_position(point position, float orientation_deg, float lat_position, float long_position) {
    this->lat_position = lat_position;
    this->long_position = long_position;
    this->position = position;
    this->orientation_deg = orientation_deg;
}

void odom45::update_position(float long_position, float lat_position, float orientation_deg) {
    // Deltas
    double d_lat  = lat_position  - this->lat_position;
    double d_long = long_position - this->long_position;
    double d_head = orientation_deg - this->orientation_deg;

    // Update stored states
    this->lat_position = lat_position;
    this->long_position = long_position;
    this->orientation_deg = orientation_deg;

    // Normalize heading delta to [-180, 180]
    d_head = reduce_negative_180_to_180(d_head);

    if (d_lat == 0.0 && d_long == 0.0 && d_head == 0.0) return;

    // 45° wheel mixing (treat long as FR, lat as FL)
    const double inv_sqrt2 = 1.0 / std::sqrt(2.0);

    double raw_fr = d_long;
    double raw_fl = d_lat;

    double raw_fwd  = (raw_fr + raw_fl) * inv_sqrt2;
    double raw_side = (raw_fr - raw_fl) * inv_sqrt2;

    // Arc-adjust with offsets
    double local_off_lat, local_off_long;
    if (std::fabs(d_head) > 1e-9) {
        double dht_rad = d_head * (M_PI / 180.0);
        double s = std::sin(dht_rad / 2.0);

        local_off_lat  = 2.0 * s * (raw_side / dht_rad + lat_offset);
        local_off_long = 2.0 * s * (raw_fwd  / dht_rad + long_offset);
    } else {
        local_off_lat  = raw_side;
        local_off_long = raw_fwd;
    }

    // Average angle
    double avga_deg = reduce_negative_180_to_180(orientation_deg - 0.5 * d_head);

    // Polar rotate (same as step)
    double polar_r = std::sqrt(local_off_lat * local_off_lat +
                               local_off_long * local_off_long);

    double polar_angle = std::atan2(local_off_long, local_off_lat) - to_rad(avga_deg);

    // forward -> +Y, right -> +X
    double dX = polar_r * std::cos(polar_angle);
    double dY = polar_r * std::sin(polar_angle);

    position.x += dX;
    position.y += dY;
}
