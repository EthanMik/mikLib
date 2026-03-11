#include "mikLib/Devices/distance.h"
#include "mikLib/globals.h"
#include "mikLib/Drive/util.h"
#include "v5.h"
#include "v5_vcs.h"
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>

using namespace mik;

#define WALL_TOP_Y     70.25
#define WALL_BOTTOM_Y -70.25
#define WALL_LEFT_X   -70.25
#define WALL_RIGHT_X   70.25

#define WALL_TOP_ANGLE_OFFSET    270
#define WALL_BOTTOM_ANGLE_OFFSET 270
#define WALL_LEFT_ANGLE_OFFSET    90
#define WALL_RIGHT_ANGLE_OFFSET   90

#define SENSOR_FRONT_ANGLE_OFFSET   0
#define SENSOR_BACK_ANGLE_OFFSET  180
#define SENSOR_LEFT_ANGLE_OFFSET   270
#define SENSOR_RIGHT_ANGLE_OFFSET 90

mik::distance::distance(int port, distance_position position, float x_center_offset, float y_center_offset) :
    vex::distance(port), port_(port), position_(position), x_center_offset_(x_center_offset), y_center_offset_(y_center_offset), name_(to_sensor_name(position))
{};

distance_position mik::distance::position() const { return position_; }
float mik::distance::x_center_offset() const { return x_center_offset_; }
float mik::distance::y_center_offset() const { return y_center_offset_; }
void mik::distance::x_center_offset(float new_offset) { x_center_offset_ = new_offset; }
void mik::distance::y_center_offset(float new_offset) { y_center_offset_ = new_offset; }
const std::string mik::distance::name() const { return name_; }

mik::distance_reset::distance_reset(const std::vector<mik::distance>& distance_sensors) :
    distance_sensors(distance_sensors)
{};

mik::wall_position mik::distance_reset::auto_detect_wall(
    const float distance, const float sensor_offset,
    const float x_offset, const float y_offset,  
    float x, float y, float angle
) {
    const float dx = sin(to_rad(angle + sensor_offset));
    const float dy = cos(to_rad(angle + sensor_offset));

    const float sensor_x = x + x_offset * cos(to_rad(angle)) + y_offset * sin(to_rad(angle));
    const float sensor_y = y - x_offset * sin(to_rad(angle)) + y_offset * cos(to_rad(angle));

    const float t_right  = dx > 0 ? (WALL_RIGHT_X  - sensor_x) / dx : INFINITY;
    const float t_left   = dx < 0 ? (WALL_LEFT_X   - sensor_x) / dx : INFINITY;
    const float t_top    = dy > 0 ? (WALL_TOP_Y    - sensor_y) / dy : INFINITY;
    const float t_bottom = dy < 0 ? (WALL_BOTTOM_Y - sensor_y) / dy : INFINITY;

    const float tMin = std::min({t_right, t_left, t_top, t_bottom});

    if (tMin == t_right)  return wall_position::RIGHT_WALL;
    if (tMin == t_left)   return wall_position::LEFT_WALL;
    if (tMin == t_top)    return wall_position::TOP_WALL;
    return wall_position::BOTTOM_WALL;
}

std::string mik::distance_reset::get_wall_facing(distance_position sensor_position, float x, float y, float angle) {
    int index = -1;
    for (size_t i = 0; i < distance_sensors.size(); ++i) {
        if (distance_sensors[i].position() == sensor_position) {
            index = i;
        }
    }
    if (index < 0) {
        print("Sensor does not exist", mik::red);
        return "";
    }

    const float sensor_offset = to_sensor_offset_constant(sensor_position);
    const float distance = distance_sensors[index].objectDistance(vex::inches);
    const float x_offset = distance_sensors[index].x_center_offset();
    const float y_offset = distance_sensors[index].y_center_offset();

    return to_wall_name(auto_detect_wall(distance, sensor_offset, x_offset, y_offset, x, y, angle));
}

float mik::distance_reset::get_reset_axis_pos(distance_position sensor_position, wall_position wall_position, float x, float y, float angle) {
    int index = -1;
    for (size_t i = 0; i < distance_sensors.size(); ++i) {
        if (distance_sensors[i].position() == sensor_position) {
            index = i;
        }
    }
    if (index < 0) {
        print("Sensor does not exist", mik::red);
        return 0;
    }
    
    const float sensor_offset = to_sensor_offset_constant(sensor_position);
    const float distance = distance_sensors[index].objectDistance(vex::inches);
    const float x_offset = distance_sensors[index].x_center_offset();
    const float y_offset = distance_sensors[index].y_center_offset();

    if (wall_position == wall_position::AUTO) {
        wall_position = auto_detect_wall(distance, sensor_offset, x_offset, y_offset, x, y, angle);
    }
    
    const float wall_offset = to_wall_angle_constant(wall_position);
    const float wall_pos = to_wall_pos_constant(wall_position);
    
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

mik::distance mik::distance_reset::get_distance_sensor(mik::distance_position sensor_pos) {
    for (auto& sensor : distance_sensors) {
        if (sensor.position() == sensor_pos) {
            return sensor;
        }
    }
    return mik::distance(PORT0, sensor_pos, 0, 0);
}   

std::string mik::distance_reset::to_wall_name(mik::wall_position wall_position) {
    switch (wall_position) {
        case wall_position::TOP_WALL:
            return "Top Wall";
        case wall_position::LEFT_WALL:
            return "Left Wall";
        case wall_position::RIGHT_WALL:
            return "Right Wall";
        case wall_position::BOTTOM_WALL:
            return "Bottom Wall";
        case wall_position::AUTO:
            return "Auto";
    }
}

std::string mik::distance::to_sensor_name(distance_position sensor_pos) {
    switch (sensor_pos) {
        case distance_position::FRONT_SENSOR:
            return "Front";
        case distance_position::REAR_SENSOR:
            return "Rear";
        case distance_position::LEFT_SENSOR:
            return "Left";
        case distance_position::RIGHT_SENSOR:
            return "Right";
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
        case wall_position::AUTO:
            return 0;
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
        case wall_position::AUTO:
            return 0;
    }
}
