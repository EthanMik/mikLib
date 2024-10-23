#include "654-Template/motor_chain.h"
#include "654-Template/manual_drive.h"
#include "654-Template/PID.h"
#include "robot-config.h"
#include "util.h"
#include "vex.h"

using namespace vex;

auton_drive::auton_drive(motor_chain leftDrive, motor_chain rightDrive, float Wheel_diameter, float Wheel_ratio, int ForwardTracker_port, float ForwardTracker_diameter, 
  float ForwardTracker_center_distance, int SidewaysTracker_port, float SidewaysTracker_diameter, float SidewaysTracker_center_distance):
   
    Wheel_diameter(Wheel_diameter),
    Wheel_ratio(Wheel_ratio),
    Drive_in_to_deg_ratio(Wheel_ratio / 360.0 * M_PI* Wheel_diameter),

    ForwardTracker_diameter(ForwardTracker_diameter),
    ForwardTracker_center_distance(ForwardTracker_center_distance),
    ForwardTracker_in_to_deg_ratio(M_PI * ForwardTracker_diameter / 360.0),

    SidewaysTracker_diameter(SidewaysTracker_diameter),
    SidewaysTracker_center_distance(SidewaysTracker_center_distance),
    SidewaysTracker_in_to_deg_ratio(M_PI * SidewaysTracker_diameter / 360.0),
  
    leftDrive(leftDrive),
    rightDrive(rightDrive),

    forwardTracker(ForwardTracker_port),
    sidewaysTracker(SidewaysTracker_port)
{
  odom.set_physical_distances(ForwardTracker_center_distance, SidewaysTracker_center_distance);
}

void auton_drive::drive_with_voltage(float leftVoltage, float rightVoltage){
  leftDrive.spin(fwd, leftVoltage, velocity_units::volt);
  rightDrive.spin(fwd, rightVoltage, velocity_units::volt);
}

void auton_drive::stop_drive(vex::brakeType brake) {
  leftDrive.stop(brake);
  rightDrive.stop(brake);
}

float auton_drive::get_absolute_heading(){ 
  return(reduce_0_to_360(Inertial.rotation())); 
}

float auton_drive::get_heading(){ 
  return(360-reduce_0_to_360(Inertial.rotation())); 
}

float auton_drive::get_left_position_in(){
  return(leftDrive.get_position(deg) * Drive_in_to_deg_ratio);
}

float auton_drive::get_right_position_in(){
  return(rightDrive.get_position(deg) * Drive_in_to_deg_ratio);
}

void auton_drive::turn_on_PID(float angle, float turn_max_voltage, float turn_settle_error, float turn_settle_time, float turn_timeout, float turn_kp, float turn_ki, float turn_kd, float turn_starti) {
  desired_heading = angle;
  PID turnPID(reduce_negative_180_to_180(angle - get_absolute_heading()), turn_kp, turn_ki, turn_kd, turn_starti, turn_settle_error, turn_settle_time, turn_timeout);
  
  while(turnPID.is_settled() == false)
  {
    float error = reduce_negative_180_to_180(angle - get_absolute_heading());
    float output = turnPID.compute(error, track_pid);

    output = clamp(output, -turn_max_voltage, turn_max_voltage);

    drive_with_voltage(output, -output);
    task::sleep(10); 
  }

  if (track_pid) {
    turnPID.print_PID();    
  }

  stop_drive(hold);
}

void auton_drive::drive_on_PID(float distance, float heading, float drive_max_voltage, float heading_max_voltage, float drive_settle_error, float drive_settle_time, float drive_timeout, float drive_kp, float drive_ki, float drive_kd, float drive_starti, float heading_kp, float heading_ki, float heading_kd, float heading_starti){
  desired_heading = heading;
  PID drivePID(distance, drive_kp, drive_ki, drive_kd, drive_starti, drive_settle_error, drive_settle_time, drive_timeout);
  PID headingPID(reduce_negative_180_to_180(heading - get_absolute_heading()), heading_kp, heading_ki, heading_kd, heading_starti);
  
  float start_average_position = (get_left_position_in() + get_right_position_in()) / 2.0;
  float average_position = start_average_position;

  while(drivePID.is_settled() == false) {
    average_position = (get_left_position_in() + get_right_position_in()) / 2.0;

    float drive_error = distance + start_average_position - average_position;
    float heading_error = reduce_negative_180_to_180(heading - get_absolute_heading());
    float drive_output = drivePID.compute(drive_error, track_pid);
    float heading_output = headingPID.compute(heading_error);

    drive_output = clamp(drive_output, -drive_max_voltage, drive_max_voltage);
    heading_output = clamp(heading_output, -heading_max_voltage, heading_max_voltage);

    drive_with_voltage(drive_output + heading_output, drive_output - heading_output);
    task::sleep(10);
  }

  if (track_pid) {
    drivePID.print_PID();    
  }

  stop_drive(hold);
}

float auton_drive::get_ForwardTracker_position() {
    return(forwardTracker.position(deg) * ForwardTracker_in_to_deg_ratio);
}

float auton_drive::get_SidewaysTracker_position() {
    return(sidewaysTracker.position(deg) * SidewaysTracker_in_to_deg_ratio);
}

void auton_drive::position_track() {
  while(true) {
    odom.update_position(get_ForwardTracker_position(), get_SidewaysTracker_position(), get_absolute_heading());
    task::sleep(5);
  }
}

int auton_drive::position_track_task(){
  chassis.position_track();
  return(0);
}

void auton_drive::set_heading(float orientation_deg){
  Inertial.setRotation(orientation_deg, deg);
}

void auton_drive::set_coordinates(float X_position, float Y_position, float orientation_deg) {
  odom.set_position(X_position, Y_position, orientation_deg, get_ForwardTracker_position(), get_SidewaysTracker_position());
  set_heading(orientation_deg);
  odom_task = task(position_track_task);
}

float auton_drive::get_X_position() {
  return(odom.X_position);
}

float auton_drive::get_Y_position() {
  return(odom.Y_position);
}

std::vector<float> auton_drive::get_position_vector() {
  std::vector<float> coordinates {odom.X_position, odom.Y_position};  
  return(coordinates);
} 

void auton_drive::drive_to_pose(float X_position, float Y_position, float angle, float lead, float setback, float drive_min_voltage, float drive_max_voltage, float heading_max_voltage, float drive_settle_error, float drive_settle_time, float drive_timeout, float drive_kp, float drive_ki, float drive_kd, float drive_starti, float heading_kp, float heading_ki, float heading_kd, float heading_starti){
  float target_distance = hypot(X_position-get_X_position(),Y_position-get_Y_position());
  PID drivePID(target_distance, drive_kp, drive_ki, drive_kd, drive_starti, drive_settle_error, drive_settle_time, drive_timeout);
  PID headingPID(to_deg(atan2(X_position-get_X_position(),Y_position-get_Y_position())) - get_absolute_heading(), heading_kp, heading_ki, heading_kd, heading_starti);
  bool line_settled = is_line_settled(X_position, Y_position, angle, get_X_position(), get_Y_position());
  bool prev_line_settled = is_line_settled(X_position, Y_position, angle, get_X_position(), get_Y_position());
  bool crossed_center_line = false;
  bool center_line_side = is_line_settled(X_position, Y_position, angle+90, get_X_position(), get_Y_position());
  bool prev_center_line_side = center_line_side;
  while(!drivePID.is_settled()){
    line_settled = is_line_settled(X_position, Y_position, angle, get_X_position(), get_Y_position());
    if(line_settled && !prev_line_settled){ break; }
    prev_line_settled = line_settled;

    center_line_side = is_line_settled(X_position, Y_position, angle+90, get_X_position(), get_Y_position());
    if(center_line_side != prev_center_line_side){
      crossed_center_line = true;
    }

    target_distance = hypot(X_position-get_X_position(),Y_position-get_Y_position());

    float carrot_X = X_position - sin(to_rad(angle)) * (lead * target_distance + setback);
    float carrot_Y = Y_position - cos(to_rad(angle)) * (lead * target_distance + setback);

    float drive_error = hypot(carrot_X-get_X_position(), carrot_Y - get_Y_position());
    float heading_error = reduce_negative_180_to_180(to_deg(atan2(carrot_X - get_X_position(),carrot_Y-get_Y_position()))-get_absolute_heading());

    if (drive_error < drive_settle_error || crossed_center_line || drive_error < setback) { 
      heading_error = reduce_negative_180_to_180(angle - get_absolute_heading()); 
      drive_error = target_distance;
    }
    
    float drive_output = drivePID.compute(drive_error);

    float heading_scale_factor = cos(to_rad(heading_error));
    drive_output*=heading_scale_factor;
    heading_error = reduce_negative_90_to_90(heading_error);
    float heading_output = headingPID.compute(heading_error);

    drive_output = clamp(drive_output, -fabs(heading_scale_factor)*drive_max_voltage, fabs(heading_scale_factor)*drive_max_voltage);
    heading_output = clamp(heading_output, -heading_max_voltage, heading_max_voltage);

    drive_output = clamp_min_voltage(drive_output, drive_min_voltage);

    drive_with_voltage(left_voltage_scaling(drive_output, heading_output), right_voltage_scaling(drive_output, heading_output));
    task::sleep(10);
  }
}




