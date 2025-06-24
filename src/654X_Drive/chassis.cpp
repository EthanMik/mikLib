#include "vex.h"

using namespace vex;

Chassis::Chassis(mik::motor_group left_drive, mik::motor_group right_drive, int inertial_port, float wheel_diameter, float wheel_ratio, float inertial_scale, int forward_tracker_port, float forward_tracker_diameter, 
  float forward_tracker_center_distance, int sideways_tracker_port, float sideways_tracker_diameter, float sideways_tracker_center_distance):
   
    forward_tracker_port(forward_tracker_port),
    sideways_tracker_port(sideways_tracker_port),
    inertial_port(inertial_port),
    
    forward_tracker(forward_tracker_port),
    sideways_tracker(sideways_tracker_port),
    inertial(inertial_port),
    
    left_drive(left_drive),
    right_drive(right_drive),

    wheel_diameter(wheel_diameter),
    wheel_ratio(wheel_ratio),
    drive_inch_to_deg_ratio(wheel_ratio / 360.0 * M_PI * wheel_diameter),
    inertial_scale(inertial_scale),
    
    forward_tracker_diameter(forward_tracker_diameter),
    forward_tracker_center_distance(forward_tracker_center_distance),
    forward_tracker_inch_to_deg_ratio(M_PI * forward_tracker_diameter / 360.0),
    
    sideways_tracker_diameter(sideways_tracker_diameter),
    sideways_tracker_center_distance(sideways_tracker_center_distance),
    sideways_tracker_inch_to_deg_ratio(M_PI * sideways_tracker_diameter / 360.0)
{
  odom.set_physical_distances(forward_tracker_center_distance, sideways_tracker_center_distance);
}

void Chassis::set_turn_constants(float turn_max_voltage, float turn_kp, float turn_ki, float turn_kd, float turn_starti, float turn_settle_error, float turn_tolerance, float turn_settle_time, float turn_timeout) {
  this->turn_max_voltage = turn_max_voltage;
  this->turn_kp = turn_kp;
  this->turn_ki = turn_ki;
  this->turn_kd = turn_kd;
  this->turn_starti = turn_starti;
  this->turn_settle_error = turn_settle_error;
  this->turn_tolerance = turn_tolerance;
  this->turn_settle_time = turn_settle_time;
  this->turn_timeout = turn_timeout;
}

void Chassis::set_drive_constants(float drive_max_voltage, float drive_kp, float drive_ki, float drive_kd, float drive_starti, float drive_settle_error, float drive_settle_time, float drive_timeout) {
  this->drive_max_voltage = drive_max_voltage;
  this->drive_kp = drive_kp;
  this->drive_ki = drive_ki;
  this->drive_kd = drive_kd;
  this->drive_starti = drive_starti;
  this->drive_settle_error = drive_settle_error;
  this->drive_settle_time = drive_settle_time;
  this->drive_timeout = drive_timeout;
}

void Chassis::set_heading_constants(float heading_max_voltage, float heading_kp, float heading_ki, float heading_kd, float heading_starti) {
  this->heading_max_voltage = heading_max_voltage;
  this->heading_kp = heading_kp;
  this->heading_ki = heading_ki;
  this->heading_kd = heading_kd;
  this->heading_starti = heading_starti;
}

void Chassis::set_swing_constants(float swing_max_voltage, float swing_kp, float swing_ki, float swing_kd, float swing_starti, float swing_settle_error, float swing_tolerance, float swing_settle_time, float swing_timeout){
  this->swing_max_voltage = swing_max_voltage;
  this->swing_kp = swing_kp;
  this->swing_ki = swing_ki;
  this->swing_kd = swing_kd;
  this->swing_starti = swing_starti;
  this->swing_settle_error = swing_settle_error;
  this->swing_tolerance = swing_tolerance;
  this->swing_settle_time = swing_settle_time;
  this->swing_timeout = swing_timeout;
} 

void Chassis::set_brake_type(vex::brakeType brake) {
  left_drive.set_stopping(brake);
  right_drive.set_stopping(brake);
}

void Chassis::wait() {
  while(motion_running) {
    task::sleep(50);
  }
}

void Chassis::wait(float units) {
  while (distance_traveled < units && motion_running) {
    task::sleep(10);
  }
}

void Chassis::drive_with_voltage(float leftVoltage, float rightVoltage){
  left_drive.spin(vex::fwd, leftVoltage, VOLT);
  right_drive.spin(vex::fwd, rightVoltage, VOLT);
}

void Chassis::stop_drive(vex::brakeType brake) {
  left_drive.stop(brake);
  right_drive.stop(brake);
}

float Chassis::get_absolute_heading(){ 
  return(reduce_0_to_360(inertial.rotation() * 360.0 / inertial_scale)); 
}

float Chassis::get_heading(){ 
  return(360 - reduce_0_to_360(inertial.rotation())); 
}

float Chassis::get_left_position_in(){
  return(left_drive.get_position(vex::deg) * drive_inch_to_deg_ratio);
}

float Chassis::get_right_position_in(){
  return(right_drive.get_position(vex::deg) * drive_inch_to_deg_ratio);
}

void Chassis::turn(float angle, bool wait) {
  turn(angle, direction::DEFAULT, turn_max_voltage, turn_settle_error, turn_settle_time, turn_timeout, turn_kp, turn_ki, turn_kd, turn_starti, wait);
}

void Chassis::turn(float angle, float turn_max_voltage, bool wait) {
  turn(angle, direction::DEFAULT, turn_max_voltage, turn_settle_error, turn_settle_time, turn_timeout, turn_kp, turn_ki, turn_kd, turn_starti, wait);
}

void Chassis::turn(float angle, direction dir, bool wait) {
  turn(angle, dir, turn_max_voltage, turn_settle_error, turn_settle_time, turn_timeout, turn_kp, turn_ki, turn_kd, turn_starti, wait);
}

void Chassis::turn(float angle, float turn_max_voltage, float turn_settle_error, float turn_settle_time, float turn_timeout, bool wait) {
  turn(angle, dir, turn_max_voltage, turn_settle_error, turn_settle_time, turn_timeout, turn_kp, turn_ki, turn_kd, turn_starti, wait);
}

void Chassis::turn(float angle, direction dir, float turn_max_voltage, float turn_settle_error, float turn_settle_time, float turn_timeout, float turn_kp, float turn_ki, float turn_kd, float turn_starti, bool wait) {
  desired_heading = angle;
  this->dir = dir;
  this->turn_max_voltage = turn_max_voltage;
  pid = PID(reduce_negative_180_to_180(desired_heading - get_absolute_heading()), turn_kp, turn_ki, turn_kd, turn_starti, turn_settle_error, turn_settle_time, turn_timeout);
  motion_running = true;
  distance_traveled = 0;
  drive_task = vex::task([](){
    float error = reduce_negative_180_to_180(chassis.desired_heading - chassis.get_absolute_heading());
    if (chassis.dir == direction::CW) { error = std::abs(error); }
    if (chassis.dir == direction::CCW) { error = -std::abs(error); }
    float prev_error = error;

    while(chassis.pid.is_settled() == false) {
      error = reduce_negative_180_to_180(chassis.desired_heading - chassis.get_absolute_heading());
      
      if (chassis.dir == direction::CW && std::abs(error) > chassis.turn_tolerance) { error = std::abs(error); } 
      if (chassis.dir == direction::CCW && std::abs(error) > chassis.turn_tolerance) { error = -std::abs(error); }
      chassis.distance_traveled += std::abs(error - prev_error);
      prev_error = error;
      float output = chassis.pid.compute(error);
      output = clamp(output, -chassis.turn_max_voltage, chassis.turn_max_voltage);
  
      chassis.drive_with_voltage(output, -output);
      vex::task::sleep(10); 
    }
  
    chassis.motion_running = false;
    if (!chassis.motion_chaining) { chassis.stop_drive(hold); }

    return 0;
  });
  if (wait) { this->wait(); }
}

void Chassis::drive(float distance, bool wait) {
  drive(distance, get_absolute_heading(), drive_max_voltage, heading_max_voltage, drive_settle_error, drive_settle_time, drive_timeout, drive_kp, drive_ki, drive_kd, drive_starti, heading_kp, heading_ki, heading_kd, heading_starti, wait);
}

void Chassis::drive(float distance, float heading, bool wait) {
  drive(distance, heading, drive_max_voltage, heading_max_voltage, drive_settle_error, drive_settle_time, drive_timeout, drive_kp, drive_ki, drive_kd, drive_starti, heading_kp, heading_ki, heading_kd, heading_starti, wait);
}

void Chassis::drive(float distance, float heading, float drive_max_voltage, bool wait) {
  drive(distance, heading, drive_max_voltage, heading_max_voltage, drive_settle_error, drive_settle_time, drive_timeout, drive_kp, drive_ki, drive_kd, drive_starti, heading_kp, heading_ki, heading_kd, heading_starti, wait);
}

void Chassis::drive(float distance, float drive_max_voltage, float drive_settle_error, float drive_settle_time, float drive_timeout, bool wait) {
  drive(distance, get_absolute_heading(), drive_max_voltage, heading_max_voltage, drive_settle_error, drive_settle_time, drive_timeout, drive_kp, drive_ki, drive_kd, drive_starti, heading_kp, heading_ki, heading_kd, heading_starti, wait);
}

void Chassis::drive(float distance, float heading, float drive_max_voltage, float heading_max_voltage, float drive_settle_error, float drive_settle_time, float drive_timeout, float drive_kp, float drive_ki, float drive_kd, float drive_starti, float heading_kp, float heading_ki, float heading_kd, float heading_starti, bool wait){
  desired_heading = heading;
  desired_distance = distance;
  this->drive_max_voltage = drive_max_voltage;
  this->heading_max_voltage = heading_max_voltage;
  pid = PID(distance, drive_kp, drive_ki, drive_kd, drive_starti, drive_settle_error, drive_settle_time, drive_timeout);
  pid_2 = PID(reduce_negative_180_to_180(desired_heading - get_absolute_heading()), heading_kp, heading_ki, heading_kd, heading_starti);
  
  motion_running = true;
  distance_traveled = 0;

  drive_task = vex::task([](){
    float drive_start_position = chassis.get_ForwardTracker_position();
    float current_position = drive_start_position;
    float drive_error = chassis.desired_distance + drive_start_position - current_position;
    float prev_drive_error = drive_error;

    while(chassis.pid.is_settled() == false) {
      current_position = chassis.get_ForwardTracker_position();
  
      drive_error = chassis.desired_distance + drive_start_position - current_position;
      chassis.distance_traveled += std::abs(drive_error - prev_drive_error);
      prev_drive_error = drive_error;

      float heading_error = reduce_negative_180_to_180(chassis.desired_heading - chassis.get_absolute_heading());
      float drive_output = chassis.pid.compute(drive_error);
      float heading_output = chassis.pid_2.compute(heading_error);
  
      drive_output = clamp(drive_output, -chassis.drive_max_voltage, chassis.drive_max_voltage);
      heading_output = clamp(heading_output, -chassis.heading_max_voltage, chassis.heading_max_voltage);
  
      chassis.drive_with_voltage(drive_output + heading_output, drive_output - heading_output);
      vex::task::sleep(10);
    }

    chassis.motion_running = false;
    if (!chassis.motion_chaining) { chassis.stop_drive(hold); }

    return 0;
  });
  if (wait) {
    this->wait();
  }
}

void Chassis::left_swing(float angle, bool wait) {
  left_swing(angle, direction::DEFAULT, swing_max_voltage, swing_settle_error, swing_settle_time, swing_timeout, swing_kp, swing_ki, swing_kd, swing_starti, wait);
}

void Chassis::left_swing(float angle, float swing_max_voltage, bool wait) {
  left_swing(angle, direction::DEFAULT, swing_max_voltage, swing_settle_error, swing_settle_time, swing_timeout, swing_kp, swing_ki, swing_kd, swing_starti, wait);
}

void Chassis::left_swing(float angle, direction dir, bool wait) {
  left_swing(angle, dir, swing_max_voltage, swing_settle_error, swing_settle_time, swing_timeout, swing_kp, swing_ki, swing_kd, swing_starti, wait);
}

void Chassis::left_swing(float angle, float swing_max_voltage, float swing_settle_error, float swing_settle_time, float swing_timeout, bool wait) {
  left_swing(angle, direction::DEFAULT, swing_max_voltage, swing_settle_error, swing_settle_time, swing_timeout, swing_kp, swing_ki, swing_kd, swing_starti, wait);
} 

void Chassis::left_swing(float angle, direction dir, float swing_max_voltage, float swing_settle_error, float swing_settle_time, float swing_timeout, float swing_kp, float swing_ki, float swing_kd, float swing_starti, bool wait) {
  desired_heading = angle;
  this->dir = dir;
  this->swing_max_voltage = swing_max_voltage;
  pid = PID(reduce_negative_180_to_180(desired_heading - get_absolute_heading()), swing_kp, swing_ki, swing_kd, swing_starti, swing_settle_error, swing_settle_time, swing_timeout);
  motion_running = true;
  distance_traveled = 0;

  drive_task = vex::task([](){
    float error = reduce_negative_180_to_180(chassis.desired_heading - chassis.get_absolute_heading());
    if (chassis.dir == direction::CW) { error = std::abs(error); }
    if (chassis.dir == direction::CCW) { error = -std::abs(error); }
    float prev_error = error;

    while(!chassis.pid.is_settled()) {
      error  = reduce_negative_180_to_180(chassis.desired_heading - chassis.get_absolute_heading());
      
      if (chassis.dir == direction::CW && std::abs(error) > chassis.swing_tolerance) { error = std::abs(error); } 
      if (chassis.dir == direction::CCW && std::abs(error) > chassis.swing_tolerance) { error = -std::abs(error); }
      chassis.distance_traveled += std::abs(error - prev_error);
      prev_error = error;
      float output = chassis.pid.compute(error);
      output = clamp(output, -chassis.swing_max_voltage, chassis.swing_max_voltage);
  
      chassis.left_drive.spin(fwd, output, VOLT);
      chassis.right_drive.stop(hold);
  
      vex::task::sleep(10);
    }

    chassis.motion_running = false;
    if (!chassis.motion_chaining) { chassis.stop_drive(hold); }

    return 0;
  });
  if (wait) { this->wait(); }
}

void Chassis::right_swing(float angle, bool wait) {
  right_swing(angle, direction::DEFAULT, swing_max_voltage, swing_settle_error, swing_settle_time, swing_timeout, swing_kp, swing_ki, swing_kd, swing_starti, wait);
}

void Chassis::right_swing(float angle, float swing_max_voltage, bool wait) {
  right_swing(angle, direction::DEFAULT, swing_max_voltage, swing_settle_error, swing_settle_time, swing_timeout, swing_kp, swing_ki, swing_kd, swing_starti, wait);
}

void Chassis::right_swing(float angle, direction dir, bool wait) {
  right_swing(angle, dir, swing_max_voltage, swing_settle_error, swing_settle_time, swing_timeout, swing_kp, swing_ki, swing_kd, swing_starti, wait);
}

void Chassis::right_swing(float angle, float swing_max_voltage, float swing_settle_error, float swing_settle_time, float swing_timeout, bool wait) {
  right_swing(angle, direction::DEFAULT, swing_max_voltage, swing_settle_error, swing_settle_time, swing_timeout, swing_kp, swing_ki, swing_kd, swing_starti, wait);
}

void Chassis::right_swing(float angle, direction dir, float swing_max_voltage, float swing_settle_error, float swing_settle_time, float swing_timeout, float swing_kp, float swing_ki, float swing_kd, float swing_starti, bool wait) {
  desired_heading = angle;
  this->dir = dir;
  this->swing_max_voltage = swing_max_voltage;
  pid = PID(reduce_negative_180_to_180(desired_heading - get_absolute_heading()), swing_kp, swing_ki, swing_kd, swing_starti, swing_settle_error, swing_settle_time, swing_timeout);
  motion_running = true;
  distance_traveled = 0;

  drive_task = vex::task([](){
    float error = reduce_negative_180_to_180(chassis.desired_heading - chassis.get_absolute_heading());
    if (chassis.dir == direction::CW) { error = std::abs(error); }
    if (chassis.dir == direction::CCW) { error = -std::abs(error); }
    float prev_error = error;

    while(!chassis.pid.is_settled()) {
      error  = reduce_negative_180_to_180(chassis.desired_heading - chassis.get_absolute_heading());
      
      if (chassis.dir == direction::CW && std::abs(error) > chassis.swing_tolerance) { error = std::abs(error); } 
      if (chassis.dir == direction::CCW && std::abs(error) > chassis.swing_tolerance) { error = -std::abs(error); }
      chassis.distance_traveled += std::abs(error - prev_error);
      prev_error = error;
      float output = chassis.pid.compute(error);
      output = clamp(output, -chassis.swing_max_voltage, chassis.swing_max_voltage);
  
      chassis.right_drive.spin(vex::reverse, output, VOLT);
      chassis.left_drive.stop(vex::hold);
  
      vex::task::sleep(10);
    }

    chassis.motion_running = false;
    if (!chassis.motion_chaining) { chassis.stop_drive(hold); }

    return 0;
  });
  if (wait) { this->wait(); }
}

void Chassis::enable_motion_chaining() {
  motion_chaining = true;
}

void Chassis::disable_motion_chaining() {
  motion_chaining = false;
}

float Chassis::get_ForwardTracker_position() {
    return(forward_tracker.position(vex::deg) * forward_tracker_inch_to_deg_ratio);
}

float Chassis::get_SidewaysTracker_position() {
    return(sideways_tracker.position(vex::deg) * sideways_tracker_inch_to_deg_ratio);
}

void Chassis::position_track() {
  while(1) {
    odom.update_position(get_ForwardTracker_position(), get_SidewaysTracker_position(), get_absolute_heading());
    vex::task::sleep(5);
  }
}

int Chassis::position_track_task(){
  chassis.position_track();
  return(0);
}

void Chassis::set_heading(float orientation_deg){
  inertial.setRotation(orientation_deg, vex::deg);
}

void Chassis::set_coordinates(float X_position, float Y_position, float orientation_deg) {
  position_tracking = true;
  forward_tracker.resetPosition();
  sideways_tracker.resetPosition();
  odom.set_position(X_position, Y_position, orientation_deg, get_ForwardTracker_position(), get_SidewaysTracker_position());
  set_heading(orientation_deg);
  odom_task = vex::task(position_track_task);
  odom_task.setPriority(0);
}

float Chassis::get_X_position() {
  return(odom.X_position);
}

float Chassis::get_Y_position() {
  return(odom.Y_position);
}

void Chassis::turn_to_point(float X_position, float Y_position, bool wait){
  turn_to_point(X_position, Y_position, 0, direction::DEFAULT, turn_max_voltage, turn_settle_error, turn_settle_time, turn_timeout, turn_kp, turn_ki, turn_kd, turn_starti, wait);
}

void Chassis::turn_to_point(float X_position, float Y_position, direction dir, bool wait) {
  turn_to_point(X_position, Y_position, 0, dir, turn_max_voltage, turn_settle_error, turn_settle_time, turn_timeout, turn_kp, turn_ki, turn_kd, turn_starti, wait);
}

void Chassis::turn_to_point(float X_position, float Y_position, float angle_offset, bool wait) {
  turn_to_point(X_position, Y_position, angle_offset, direction::DEFAULT, turn_max_voltage, turn_settle_error, turn_settle_time, turn_timeout, turn_kp, turn_ki, turn_kd, turn_starti, wait);
}

void Chassis::turn_to_point(float X_position, float Y_position, float angle_offset, float turn_max_voltage, float turn_settle_error, float turn_settle_time, float turn_timeout, bool wait) {
  turn_to_point(X_position, Y_position, angle_offset, direction::DEFAULT, turn_max_voltage, turn_settle_error, turn_settle_time, turn_timeout, turn_kp, turn_ki, turn_kd, turn_starti, wait);
}

void Chassis::turn_to_point(float X_position, float Y_position, float angle_offset, direction dir, float turn_max_voltage, float turn_settle_error, float turn_settle_time, float turn_timeout, float turn_kp, float turn_ki, float turn_kd, float turn_starti, bool wait){
  desired_X = X_position;
  desired_Y = Y_position;
  this->dir = dir;
  this->angle_offset = angle_offset;
  float start_angle = to_deg(atan2((X_position - get_X_position()), (Y_position - get_Y_position())));
  float start_error = reduce_negative_180_to_180(start_angle - get_absolute_heading() + angle_offset);
  pid = PID(start_error, turn_kp, turn_ki, turn_kd, turn_starti, turn_settle_error, turn_settle_time, turn_timeout);

  motion_running = true;
  distance_traveled = 0;

  drive_task = vex::task([](){
    float angle = to_deg(atan2((chassis.desired_X - chassis.get_X_position()), (chassis.desired_Y - chassis.get_Y_position())));
    float error = reduce_negative_180_to_180(angle - chassis.get_absolute_heading() + chassis.angle_offset);
    if (chassis.dir == direction::CW) { error = std::abs(error); }
    if (chassis.dir == direction::CCW) { error = -std::abs(error); }
    float prev_error = error;

    while(!chassis.pid.is_settled()){
      float angle = to_deg(atan2((chassis.desired_X - chassis.get_X_position()), (chassis.desired_Y - chassis.get_Y_position())));
      float error = reduce_negative_180_to_180(angle - chassis.get_absolute_heading() + chassis.angle_offset);
      if (chassis.dir == direction::CW && std::abs(error) > chassis.turn_tolerance) { error = std::abs(error); } 
      if (chassis.dir == direction::CCW && std::abs(error) > chassis.turn_tolerance) { error = -std::abs(error); }
      chassis.distance_traveled += std::abs(error - prev_error);
      prev_error = error;

      float output = chassis.pid.compute(error);
      output = clamp(output, -chassis.turn_max_voltage, chassis.turn_max_voltage);

      chassis.drive_with_voltage(output, -output);
      task::sleep(10);
    }

    chassis.motion_running = false;
    if (!chassis.motion_chaining) { chassis.stop_drive(hold); }

    return 0;
  });
  if (wait) { this->wait(); }
}

void Chassis::drive_to_point(float X_position, float Y_position, bool wait){
  drive_to_point(X_position, Y_position, drive_min_voltage, drive_max_voltage, heading_max_voltage, drive_settle_error, drive_settle_time, drive_timeout, drive_kp, drive_ki, drive_kd, drive_starti, heading_kp, heading_ki, heading_kd, heading_starti, wait);
}

void Chassis::drive_to_point(float X_position, float Y_position, float drive_min_voltage, float drive_max_voltage, float heading_max_voltage, bool wait) {
  drive_to_point(X_position, Y_position, drive_min_voltage, drive_max_voltage, heading_max_voltage, drive_settle_error, drive_settle_time, drive_timeout, drive_kp, drive_ki, drive_kd, drive_starti, heading_kp, heading_ki, heading_kd, heading_starti, wait);
}

void Chassis::drive_to_point(float X_position, float Y_position, float drive_min_voltage, float drive_max_voltage, float heading_max_voltage, float drive_settle_error, float drive_settle_time, float drive_timeout, bool wait) {
  drive_to_point(X_position, Y_position, drive_min_voltage, drive_max_voltage, heading_max_voltage, drive_settle_error, drive_settle_time, drive_timeout, drive_kp, drive_ki, drive_kd, drive_starti, heading_kp, heading_ki, heading_kd, heading_starti, wait);
}

void Chassis::drive_to_point(float X_position, float Y_position, float drive_min_voltage, float drive_max_voltage, float heading_max_voltage, float drive_settle_error, float drive_settle_time, float drive_timeout, float drive_kp, float drive_ki, float drive_kd, float drive_starti, float heading_kp, float heading_ki, float heading_kd, float heading_starti, bool wait){
  desired_X = X_position;
  desired_Y = Y_position;
  this->drive_min_voltage = drive_min_voltage;
  this->drive_max_voltage = drive_max_voltage;
  this->heading_max_voltage = heading_max_voltage;
  this->drive_settle_error = drive_settle_error;
  pid = PID(hypot(X_position - get_X_position(), Y_position-get_Y_position()), drive_kp, drive_ki, drive_kd, drive_starti, drive_settle_error, drive_settle_time, drive_timeout);
  desired_heading = to_deg(atan2(X_position - get_X_position(),Y_position - get_Y_position()));
  pid_2 = PID(desired_heading - get_absolute_heading(), heading_kp, heading_ki, heading_kd, heading_starti);

  motion_running = true;
  distance_traveled = 0;

  drive_task = vex::task([](){
    bool line_settled = false;
    bool prev_line_settled = is_line_settled(chassis.desired_X, chassis.desired_Y, chassis.desired_heading, chassis.get_X_position(), chassis.get_Y_position());
    float drive_error = hypot(chassis.desired_X - chassis.get_X_position(), chassis.desired_Y - chassis.get_Y_position());
    float prev_drive_error = drive_error;

    while(!chassis.pid.is_settled()){
      line_settled = is_line_settled(chassis.desired_X, chassis.desired_Y, chassis.desired_heading, chassis.get_X_position(), chassis.get_Y_position());
      if (line_settled && !prev_line_settled) { break; }
      prev_line_settled = line_settled;
  
      drive_error = hypot(chassis.desired_X - chassis.get_X_position(), chassis.desired_Y - chassis.get_Y_position());
      chassis.distance_traveled += std::abs(drive_error - prev_drive_error);
      prev_drive_error = drive_error;

      float heading_error = reduce_negative_180_to_180(to_deg(atan2(chassis.desired_X - chassis.get_X_position(), chassis.desired_Y- chassis.get_Y_position())) - chassis.get_absolute_heading());
      float drive_output = chassis.pid.compute(drive_error);
  
      float heading_scale_factor = cos(to_rad(heading_error));
      drive_output *= heading_scale_factor;
      heading_error = reduce_negative_90_to_90(heading_error);
      float heading_output = chassis.pid_2.compute(heading_error);
      
      if (drive_error < chassis.drive_settle_error) { heading_output = 0; }
  
      drive_output = clamp(drive_output, -fabs(heading_scale_factor) * chassis.drive_max_voltage, fabs(heading_scale_factor) * chassis.drive_max_voltage);
      heading_output = clamp(heading_output, -chassis.heading_max_voltage, chassis.heading_max_voltage);
  
      drive_output = clamp_min_voltage(drive_output, chassis.drive_min_voltage);
  
      chassis.drive_with_voltage(left_voltage_scaling(drive_output, heading_output), right_voltage_scaling(drive_output, heading_output));
      vex::task::sleep(10);
    }

    chassis.motion_running = false;
    if (!chassis.motion_chaining) { chassis.stop_drive(hold); }

    return 0;
  });

  if (wait) { this->wait(); }
}

void Chassis::drive_to_pose(float X_position, float Y_position, float angle, bool wait) {
  drive_to_pose(X_position, Y_position, angle, boomerang_lead, boomerang_setback, drive_min_voltage, drive_max_voltage, heading_max_voltage, drive_settle_error, drive_settle_time, drive_timeout, drive_kp, drive_ki, drive_kd, drive_starti, heading_kp, heading_ki, heading_kd, heading_starti, wait);
}

void Chassis::drive_to_pose(float X_position, float Y_position, float angle, float lead, float setback, float drive_min_voltage, bool wait) {
  drive_to_pose(X_position, Y_position, angle, lead, setback, drive_min_voltage, drive_max_voltage, heading_max_voltage, drive_settle_error, drive_settle_time, drive_timeout, drive_kp, drive_ki, drive_kd, drive_starti, heading_kp, heading_ki, heading_kd, heading_starti, wait);
}

void Chassis::drive_to_pose(float X_position, float Y_position, float angle, float lead, float setback, float drive_min_voltage, float drive_max_voltage, float heading_max_voltage, bool wait) {
  drive_to_pose(X_position, Y_position, angle, lead, setback, drive_min_voltage, drive_max_voltage, heading_max_voltage, drive_settle_error, drive_settle_time, drive_timeout, drive_kp, drive_ki, drive_kd, drive_starti, heading_kp, heading_ki, heading_kd, heading_starti, wait);
}

void Chassis::drive_to_pose(float X_position, float Y_position, float angle, float lead, float setback, float drive_min_voltage, float drive_max_voltage, float heading_max_voltage, float drive_settle_error, float drive_settle_time, float drive_timeout, bool wait) {
  drive_to_pose(X_position, Y_position, angle, lead, setback, drive_min_voltage, drive_max_voltage, heading_max_voltage, drive_settle_error, drive_settle_time, drive_timeout, drive_kp, drive_ki, drive_kd, drive_starti, heading_kp, heading_ki, heading_kd, heading_starti, wait);
}

void Chassis::drive_to_pose(float X_position, float Y_position, float angle, float lead, float setback, float drive_min_voltage, float drive_max_voltage, float heading_max_voltage, float drive_settle_error, float drive_settle_time, float drive_timeout, float drive_kp, float drive_ki, float drive_kd, float drive_starti, float heading_kp, float heading_ki, float heading_kd, float heading_starti, bool wait){
  desired_X = X_position;
  desired_Y = Y_position;
  desired_heading = angle;
  this->drive_min_voltage = drive_min_voltage;
  this->drive_max_voltage = drive_max_voltage;
  this->heading_max_voltage = heading_max_voltage;
  this->drive_settle_error = drive_settle_error;
  this->boomerang_lead = lead;
  this->boomerang_setback = setback;
  float target_distance = hypot(X_position - get_X_position(), Y_position - get_Y_position());
  pid = PID(target_distance, drive_kp, drive_ki, drive_kd, drive_starti, drive_settle_error, drive_settle_time, drive_timeout);
  pid_2 = PID(to_deg(atan2(X_position - get_X_position(), Y_position - get_Y_position())) - get_absolute_heading(), heading_kp, heading_ki, heading_kd, heading_starti);
  
  motion_running = true;
  distance_traveled = 0;

  drive_task = vex::task([](){
    bool line_settled = is_line_settled(chassis.desired_X, chassis.desired_Y, chassis.desired_heading, chassis.get_X_position(), chassis.get_Y_position());
    bool prev_line_settled = is_line_settled(chassis.desired_X, chassis.desired_Y, chassis.desired_heading, chassis.get_X_position(), chassis.get_Y_position());
    bool crossed_center_line = false;
    bool center_line_side = is_line_settled(chassis.desired_X, chassis.desired_Y, chassis.desired_heading + 90, chassis.get_X_position(), chassis.get_Y_position());
    bool prev_center_line_side = center_line_side;

    float target_distance = hypot(chassis.desired_X - chassis.get_X_position(), chassis.desired_Y - chassis.get_Y_position());
    float carrot_X = chassis.desired_X- sin(to_rad(chassis.desired_heading)) * (chassis.boomerang_lead * target_distance + chassis.boomerang_setback);
    float carrot_Y = chassis.desired_Y - cos(to_rad(chassis.desired_heading)) * (chassis.boomerang_lead * target_distance + chassis.boomerang_setback);
    float drive_error = hypot(carrot_X - chassis.get_X_position(), carrot_Y - chassis.get_Y_position());
    float prev_drive_error = drive_error;

    while(!chassis.pid.is_settled()){
      line_settled = is_line_settled(chassis.desired_X, chassis.desired_Y, chassis.desired_heading, chassis.get_X_position(), chassis.get_Y_position());
      if(line_settled && !prev_line_settled){ break; }
      prev_line_settled = line_settled;
  
      center_line_side = is_line_settled(chassis.desired_X, chassis.desired_Y, chassis.desired_heading+90, chassis.get_X_position(), chassis.get_Y_position());
      if(center_line_side != prev_center_line_side){
        crossed_center_line = true;
      }
  
      target_distance = hypot(chassis.desired_X - chassis.get_X_position(), chassis.desired_Y - chassis.get_Y_position());
  
      carrot_X = chassis.desired_X- sin(to_rad(chassis.desired_heading)) * (chassis.boomerang_lead * target_distance + chassis.boomerang_setback);
      carrot_Y = chassis.desired_Y - cos(to_rad(chassis.desired_heading)) * (chassis.boomerang_lead * target_distance + chassis.boomerang_setback);
  
      drive_error = hypot(carrot_X - chassis.get_X_position(), carrot_Y - chassis.get_Y_position());
      chassis.distance_traveled += std::abs(drive_error - prev_drive_error);
      prev_drive_error = drive_error;

      float heading_error = reduce_negative_180_to_180(to_deg(atan2(carrot_X - chassis.get_X_position(), carrot_Y - chassis.get_Y_position())) - chassis.get_absolute_heading());
  
      if (drive_error < chassis.drive_settle_error || crossed_center_line || drive_error < chassis.boomerang_setback) { 
        heading_error = reduce_negative_180_to_180(chassis.desired_heading - chassis.get_absolute_heading()); 
        drive_error = target_distance;
      }
      
      float drive_output = chassis.pid.compute(drive_error);
  
      float heading_scale_factor = cos(to_rad(heading_error));
      drive_output*=heading_scale_factor;
      heading_error = reduce_negative_90_to_90(heading_error);
      float heading_output = chassis.pid_2.compute(heading_error);
  
      drive_output = clamp(drive_output, -fabs(heading_scale_factor) * chassis.drive_max_voltage, fabs(heading_scale_factor) * chassis.drive_max_voltage);
      heading_output = clamp(heading_output, -chassis.heading_max_voltage, chassis.heading_max_voltage);
  
      drive_output = clamp_min_voltage(drive_output, chassis.drive_min_voltage);
  
      chassis.drive_with_voltage(left_voltage_scaling(drive_output, heading_output), right_voltage_scaling(drive_output, heading_output));
      vex::task::sleep(10);
    }

    chassis.motion_running = false;
    if (!chassis.motion_chaining) { chassis.stop_drive(hold); }

    return 0;
  });

  if (wait) { this->wait(); }
}

void Chassis::disable_control() {
  control_disabled = true;
} 

void Chassis::enable_control() {
  control_disabled = false;
}

void Chassis::split_arcade() {
  float throttle = deadband(vex::controller(vex::primary).Axis3.value(), 5);
  float turn = deadband(vex::controller(vex::primary).Axis1.value(), 5);
  chassis.left_drive.spin(vex::fwd, percent_to_volt(throttle + turn), VOLT);
  chassis.right_drive.spin(vex::fwd, percent_to_volt(throttle - turn), VOLT);
}

void Chassis::split_arcade_squared() {
  float throttle = deadband_squared(vex::controller(vex::primary).Axis3.value(), 5);
  float turn = deadband_squared(vex::controller(vex::primary).Axis1.value(), 5);
  chassis.left_drive.spin(vex::fwd, percent_to_volt(throttle + turn), VOLT);
  chassis.right_drive.spin(vex::fwd, percent_to_volt(throttle - turn), VOLT); 
}

void Chassis::arcade_left() {
  float throttle = deadband(vex::controller(vex::primary).Axis3.value(), 5);
  float turn = deadband(vex::controller(vex::primary).Axis4.value(), 5);
  chassis.left_drive.spin (vex::fwd, percent_to_volt(throttle + turn), VOLT);
  chassis.right_drive.spin(vex::fwd, percent_to_volt(throttle - turn), VOLT);
}

void Chassis::arcade_right() {
  float throttle = deadband(vex::controller(vex::primary).Axis2.value(), 5);
  float turn = deadband(vex::controller(vex::primary).Axis1.value(), 5);
  chassis.left_drive.spin (vex::fwd, percent_to_volt(throttle + turn), VOLT);
  chassis.right_drive.spin(vex::fwd, percent_to_volt(throttle - turn), VOLT);
}

void Chassis::tank() {
  float left_throttle = deadband(controller(primary).Axis3.value(), 5);
  float right_throttle = deadband(controller(primary).Axis2.value(), 5);
  chassis.left_drive.spin(fwd, percent_to_volt(left_throttle), VOLT);
  chassis.right_drive.spin(fwd, percent_to_volt(right_throttle), VOLT);
}

void Chassis::tank_squared() {
  float left_throttle = deadband_squared(controller(primary).Axis3.value(), 5);
  float right_throttle = deadband_squared(controller(primary).Axis2.value(), 5);
  chassis.left_drive.spin(fwd, percent_to_volt(left_throttle), VOLT);
  chassis.right_drive.spin(fwd, percent_to_volt(right_throttle), VOLT);
}

void Chassis::control(drive_mode dm) {
  if (control_disabled) { 
    chassis.stop_drive(coast);
    return;
  }

  switch (dm)
  {
  case drive_mode::SPLIT_ARCADE:
    split_arcade();
    return;
  case drive_mode::SPLIT_ARCADE_SQUARED:
    split_arcade_squared();
    return;
  case drive_mode::ARCADE_LEFT:
    arcade_left();
    return;
  case drive_mode::ARCADE_RIGHT:
    arcade_right();
    return;
  case drive_mode::TANK:
    tank();
    return;
  case drive_mode::TANK_SQUARED:
    tank_squared();
    return;
  }
}