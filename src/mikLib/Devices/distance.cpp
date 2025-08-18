#include "vex.h"

using namespace mik;

#define WALL_TOP_Y     70
#define WALL_BOTTOM_Y -70
#define WALL_LEFT_X   -70
#define WALL_RIGHT_X   70

#define WALL_TOP_ANGLE_OFFSET    270
#define WALL_BOTTOM_ANGLE_OFFSET 270
#define WALL_LEFT_ANGLE_OFFSET    90
#define WALL_RIGHT_ANGLE_OFFSET   90

#define SENSOR_FRONT_ANGLE_OFFSET   0
#define SENSOR_BACK_ANGLE_OFFSET  180
#define SENSOR_LEFT_ANGLE_OFFSET   90
#define SENSOR_RIGHT_ANGLE_OFFSET 270

mik::distance::distance(int port, distance_position position, float x_center_offset, float y_center_offset) :
    vex::distance(port), port_(port), position_(position), x_center_offset_(x_center_offset), y_center_offset_(y_center_offset), name_(to_sensor_name(position))
{};

const std::string mik::distance::port() const { return "PORT" + to_string(port_ + 1); }
distance_position mik::distance::position() const { return position_; }
float mik::distance::x_center_offset() const { return x_center_offset_; }
float mik::distance::y_center_offset() const { return y_center_offset_; }
void mik::distance::x_center_offset(float new_offset) { x_center_offset_ = new_offset; }
void mik::distance::y_center_offset(float new_offset) { y_center_offset_ = new_offset; }
const std::string mik::distance::name() const { return name_; }

mik::distance_reset::distance_reset(const std::vector<mik::distance>& distance_sensors) :
    distance_sensors(distance_sensors)
{};

float mik::distance_reset::get_reset_axis_pos(distance_position sensor_position, wall_position wall_position, float angle) {
    int index = -1;
    for (size_t i = 0; i < distance_sensors.size(); ++i) {
        if (distance_sensors[i].position() == sensor_position) {
            index = i;
        }
    }
    if (index < 0) { return 0; }
    
    const float sensor_offset = to_sensor_offset_constant(sensor_position);
    const float wall_offset = to_wall_angle_constant(wall_position);
    const float wall_pos = to_wall_pos_constant(wall_position);
    
    const float distance = distance_sensors[index].objectDistance(inches);
    const float x_offset = distance_sensors[index].x_center_offset();
    const float y_offset = distance_sensors[index].y_center_offset();
    const float theta = angle + wall_offset + sensor_offset; 

    const bool reset_x = (wall_position == wall_position::LEFT_WALL || wall_position == wall_position::RIGHT_WALL);
    const bool reset_y = (wall_position == wall_position::TOP_WALL || wall_position == wall_position::BOTTOM_WALL);
    
    if (reset_x) {
        return wall_pos + (cos(to_rad(theta)) * distance) - (cos(to_rad(angle)) * x_offset) - (sin(to_rad(angle)) * y_offset);
    }
    if (reset_y) {
        return wall_pos + (sin(to_rad(theta)) * distance) + (sin(to_rad(angle)) * x_offset) - (cos(to_rad(angle)) * y_offset);
    }

    return NAN;
}

std::vector<mik::distance>& mik::distance_reset::get_distance_sensors() {
    return distance_sensors;
}

std::string mik::distance::to_sensor_name(distance_position sensor_pos) {
    switch (sensor_pos) {
        case distance_position::FRONT_SENSOR:
            return "front_distance_sensor";
        case distance_position::REAR_SENSOR:
            return "rear_distance_sensor";
        case distance_position::LEFT_SENSOR:
            return "left_distance_sensor";
        case distance_position::RIGHT_SENSOR:
            return "right_distance_sensor";
    }
}

float mik::distance_reset::to_sensor_offset_constant(distance_position sensor_pos) {
    switch (sensor_pos) {
        case distance_position::FRONT_SENSOR:
            return SENSOR_FRONT_ANGLE_OFFSET;
        case distance_position::REAR_SENSOR:
            return SENSOR_BACK_ANGLE_OFFSET;
        case distance_position::LEFT_SENSOR:
            return SENSOR_LEFT_ANGLE_OFFSET;
        case distance_position::RIGHT_SENSOR:
            return SENSOR_RIGHT_ANGLE_OFFSET;
    }
}

float mik::distance_reset::to_wall_pos_constant(wall_position wall_pos) {
    switch (wall_pos) {
        case wall_position::TOP_WALL:
            return WALL_TOP_Y;
        case wall_position::BOTTOM_WALL:
            return WALL_BOTTOM_Y;
        case wall_position::LEFT_WALL:
            return WALL_LEFT_X;
        case wall_position::RIGHT_WALL:
            return WALL_RIGHT_X;
    }
}

float mik::distance_reset::to_wall_angle_constant(wall_position wall_pos) {
    switch (wall_pos) {
        case wall_position::TOP_WALL:
            return WALL_TOP_ANGLE_OFFSET;
        case wall_position::BOTTOM_WALL:
            return WALL_BOTTOM_ANGLE_OFFSET;
        case wall_position::LEFT_WALL:
            return WALL_LEFT_ANGLE_OFFSET;
        case wall_position::RIGHT_WALL:
            return WALL_RIGHT_ANGLE_OFFSET;
    }
}
