#pragma once

#include "vex.h"
  
namespace mik {

class distance : public vex::distance {

public:
    /** 
     * @brief Creates a new distance sensor object that contains its position and offset from tracking center, on the port specified.
     * @param index The port index for this sensor. The index is zero-based.
     * @param position The face of the robot that the distance sensor is mounted to.
     * @param x_center_offset The horizontal offset from the tracking center, right is +, left is -
     * @param y_center_offset The vertical offset from the tracking center, forward is +, backwards is -
     */
    distance(int port, mik::distance_position position, float x_center_offset, float y_center_offset);

    /** @return The port in PORT# format. */
    const std::string port() const;

    /** @return The position of the distance sensor. */
    mik::distance_position position() const;

    /** @return The horizontal offset */
    float x_center_offset() const;

    /** @return The vertical offset */
    float y_center_offset() const;

    /** @return Sets the vertical offset */
    void x_center_offset(float new_offset);

    /** @return Sets the horizontal offset */
    void y_center_offset(float new_offset);
    
    /** @return The name of the sensor, based on position */
    const std::string name() const;
    
private:
    std::string to_sensor_name(mik::distance_position sensor_pos);
        
    int port_;
    mik::distance_position position_;
    float x_center_offset_;
    float y_center_offset_;
    std::string name_;
};

class distance_reset {
public:
    /** Wraps mik::distance sensors into a group. Two distance sensors perpendicular to each other should be enough,
     * As you can reset both coords at once if the sensors are facing two different walls.
     * Ex: A front or back sensor with a left or right sensor with the robot in a corner.
     */
    distance_reset(const std::vector<mik::distance>& distance_sensors);
    
    /** 
     * @brief Gets an X or Y position of the robot based on the heading and distance from a wall.
     * The distance sensor must be facing the desired wall with no obstruction in order to work.
     * Choosing to reset off a top or bottom wall will reset the robots y positon, and a left or right
     * wall resetting the robots x position.
     * 
     * @param sensor_pos The side of the robot that the distance sensor is mounted.
     * @param wall_pos The wall that is being looked at by desired distance sensor.
     * @param max_reset_distance The maxiumum allowed of distance in inches that an odom axis can be changed.
     * 
     * @return A new x or y coordinate based on the wall desired sensor is faced at.
     */
    float get_reset_axis_pos(mik::distance_position sensor_pos, mik::wall_position wall_pos, float angle);
    
    /** @returns vector containing all mik::distance sensors. */
    std::vector<mik::distance>& get_distance_sensors();
    
private:
    float to_sensor_offset_constant(mik::distance_position sensor_pos);
    float to_wall_pos_constant(mik::wall_position wall_pos);
    float to_wall_angle_constant(mik::wall_position wall_pos);

    std::vector<mik::distance> distance_sensors;
};
}