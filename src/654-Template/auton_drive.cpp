#include "vex.h"

auton_drive::auton_drive(hzn::motor_group left_drive, hzn::motor_group right_drive, int inertial_port, float wheel_diameter, float wheel_ratio, int forward_tracker_port, float forward_tracker_diameter, 
  float forward_tracker_center_distance, int sideways_tracker_port, float sideways_tracker_diameter, float sideways_tracker_center_distance):
   
    wheel_diameter(wheel_diameter),
    wheel_ratio(wheel_ratio),
    drive_inch_to_deg_ratio(wheel_ratio / 360.0 * M_PI * wheel_diameter),

    forward_tracker_diameter(forward_tracker_diameter),
    forward_tracker_center_distance(forward_tracker_center_distance),
    forward_tracker_inch_to_deg_ratio(M_PI * forward_tracker_diameter / 360.0),

    sideways_tracker_diameter(sideways_tracker_diameter),
    sideways_tracker_center_distance(sideways_tracker_center_distance),
    sideways_tracker_inch_to_deg_ratio(M_PI * sideways_tracker_diameter / 360.0),

    forward_tracker(forward_tracker_port),
    sideways_tracker(sideways_tracker_port),
    inertial(inertial_port),

    left_drive(left_drive),
    right_drive(right_drive)
{
  odom.set_physical_distances(forward_tracker_center_distance, sideways_tracker_center_distance);
}

void auton_drive::set_turn_constants(float turn_max_voltage, float turn_kp, float turn_ki, float turn_kd, float turn_starti, float turn_settle_error, float turn_settle_time, float turn_timeout) {
  this->turn_max_voltage = turn_max_voltage;
  this->turn_kp = turn_kp;
  this->turn_ki = turn_ki;
  this->turn_kd = turn_kd;
  this->turn_starti = turn_starti;
  this->turn_settle_error = turn_settle_error;
  this->turn_settle_time = turn_settle_time;
  this->turn_timeout = turn_timeout;
}

void auton_drive::set_drive_constants(float drive_max_voltage, float drive_kp, float drive_ki, float drive_kd, float drive_starti, float drive_settle_error, float drive_settle_time, float drive_timeout) {
  this->drive_max_voltage = drive_max_voltage;
  this->drive_kp = drive_kp;
  this->drive_ki = drive_ki;
  this->drive_kd = drive_kd;
  this->drive_starti = drive_starti;
  this->drive_settle_error = drive_settle_error;
  this->drive_settle_time = drive_settle_time;
  this->drive_timeout = drive_timeout;
}

void auton_drive::set_heading_constants(float heading_max_voltage, float heading_kp, float heading_ki, float heading_kd, float heading_starti) {
  this->heading_max_voltage = heading_max_voltage;
  this->heading_kp = heading_kp;
  this->heading_ki = heading_ki;
  this->heading_kd = heading_kd;
  this->heading_starti = heading_starti;
}

void auton_drive::drive_with_voltage(float leftVoltage, float rightVoltage){
  left_drive.spin(fwd, leftVoltage, velocity_units::volt);
  right_drive.spin(fwd, rightVoltage, velocity_units::volt);
}

void auton_drive::stop_drive(vex::brakeType brake) {
  left_drive.stop(brake);
  right_drive.stop(brake);
}

float auton_drive::get_absolute_heading(){ 
  return(reduce_0_to_360(inertial.rotation())); 
}

float auton_drive::get_heading(){ 
  return(360 - reduce_0_to_360(inertial.rotation())); 
}

float auton_drive::get_left_position_in(){
  return(left_drive.get_position(deg) * drive_inch_to_deg_ratio);
}

float auton_drive::get_right_position_in(){
  return(right_drive.get_position(deg) * drive_inch_to_deg_ratio);
}

void auton_drive::turn_on_PID(float angle) {
  turn_on_PID(angle, turn_max_voltage, turn_settle_error, turn_settle_error, turn_timeout, turn_kp, turn_ki, turn_kd, turn_starti);
}

void auton_drive::turn_on_PID(float angle, float turn_max_voltage, float turn_settle_error, float turn_settle_time, float turn_timeout, float turn_kp, float turn_ki, float turn_kd, float turn_starti) {
  desired_heading = angle;
  PID turnPID(reduce_negative_180_to_180(angle - get_absolute_heading()), turn_kp, turn_ki, turn_kd, turn_starti, turn_settle_error, turn_settle_time, turn_timeout);
  
  while(turnPID.is_settled() == false)
  {
    float error = reduce_negative_180_to_180(angle - get_absolute_heading());
    float output = turnPID.compute(error);

    output = clamp(output, -turn_max_voltage, turn_max_voltage);

    //test
    // add_to_graph_buffer({angle, (output / turn_max_voltage) * 100, get_absolute_heading()});

    drive_with_voltage(output, -output);
    task::sleep(10); 
  }

  stop_drive(hold);
}

void auton_drive::drive_on_PID(float distance) {
  drive_on_PID(distance, get_absolute_heading(), drive_max_voltage, heading_max_voltage, drive_settle_error, drive_settle_time, drive_timeout, drive_kp, drive_ki, drive_kd, drive_starti, heading_kp, heading_ki, heading_kd, heading_starti);
}

void auton_drive::drive_on_PID(float distance, float heading, float drive_max_voltage, float heading_max_voltage, float drive_settle_error, float drive_settle_time, float drive_timeout, float drive_kp, float drive_ki, float drive_kd, float drive_starti, float heading_kp, float heading_ki, float heading_kd, float heading_starti){
  desired_heading = heading;
  PID drivePID(distance, drive_kp, drive_ki, drive_kd, drive_starti, drive_settle_error, drive_settle_time, drive_timeout);
  PID headingPID(reduce_negative_180_to_180(heading - get_absolute_heading()), heading_kp, heading_ki, heading_kd, heading_starti);
  
  float start_average_position = get_ForwardTracker_position();
  float average_position = start_average_position;

  while(drivePID.is_settled() == false) {
    average_position = get_ForwardTracker_position();

    float drive_error = distance + start_average_position - average_position;

    float heading_error = reduce_negative_180_to_180(heading - get_absolute_heading());
    float drive_output = drivePID.compute(drive_error);
    float heading_output = headingPID.compute(heading_error);

    drive_output = clamp(drive_output, -drive_max_voltage, drive_max_voltage);
    heading_output = clamp(heading_output, -heading_max_voltage, heading_max_voltage);

    drive_with_voltage(drive_output + heading_output, drive_output - heading_output);
    task::sleep(10);
  }

  stop_drive(hold);
}

float auton_drive::get_ForwardTracker_position() {
    return(forward_tracker.position(deg) * forward_tracker_inch_to_deg_ratio);
}

float auton_drive::get_SidewaysTracker_position() {
    return(sideways_tracker.position(deg) * sideways_tracker_inch_to_deg_ratio);
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
  inertial.setRotation(orientation_deg, deg);
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

void auton_drive::turn_to_point(float X_position, float Y_position) {
    turn_to_point(X_position, Y_position, 0, turn_max_voltage, turn_settle_error, turn_settle_time, turn_timeout, turn_kp, turn_ki, turn_kd, turn_starti);
}

void auton_drive::turn_to_point(float X_position, float Y_position, float extra_angle_deg, float turn_max_voltage, float turn_settle_error, float turn_settle_time, float turn_timeout, float turn_kp, float turn_ki, float turn_kd, float turn_starti){
  PID turnPID(reduce_negative_180_to_180(to_deg(atan2(X_position-get_X_position(),Y_position-get_Y_position())) - get_absolute_heading()), turn_kp, turn_ki, turn_kd, turn_starti, turn_settle_error, turn_settle_time, turn_timeout);
  while(turnPID.is_settled() == false){
    float error = reduce_negative_180_to_180(to_deg(atan2(X_position-get_X_position(),Y_position-get_Y_position())) - get_absolute_heading() + extra_angle_deg);
    float output = turnPID.compute(error);
    output = clamp(output, -turn_max_voltage, turn_max_voltage);
    drive_with_voltage(output, -output);
    task::sleep(10);
  }
}

void auton_drive::drive_to_point(float X_position, float Y_position){
  drive_to_point(X_position, Y_position, drive_min_voltage, drive_max_voltage, heading_max_voltage, drive_settle_error, drive_settle_time, drive_timeout, drive_kp, drive_ki, drive_kd, drive_starti, heading_kp, heading_ki, heading_kd, heading_starti);
}

void auton_drive::drive_to_point(float X_position, float Y_position, float drive_min_voltage, float drive_max_voltage, float heading_max_voltage, float drive_settle_error, float drive_settle_time, float drive_timeout, float drive_kp, float drive_ki, float drive_kd, float drive_starti, float heading_kp, float heading_ki, float heading_kd, float heading_starti){
  PID drivePID(hypot(X_position-get_X_position(),Y_position-get_Y_position()), drive_kp, drive_ki, drive_kd, drive_starti, drive_settle_error, drive_settle_time, drive_timeout);
  float start_angle_deg = to_deg(atan2(X_position-get_X_position(),Y_position-get_Y_position()));
  PID headingPID(start_angle_deg-get_absolute_heading(), heading_kp, heading_ki, heading_kd, heading_starti);
  bool line_settled = false;
  bool prev_line_settled = is_line_settled(X_position, Y_position, start_angle_deg, get_X_position(), get_Y_position());
  while(!drivePID.is_settled()){
    line_settled = is_line_settled(X_position, Y_position, start_angle_deg, get_X_position(), get_Y_position());
    if(line_settled && !prev_line_settled){ break; }
    prev_line_settled = line_settled;

    float drive_error = hypot(X_position-get_X_position(),Y_position-get_Y_position());
    float heading_error = reduce_negative_180_to_180(to_deg(atan2(X_position-get_X_position(),Y_position-get_Y_position()))-get_absolute_heading());
    float drive_output = drivePID.compute(drive_error);

    float heading_scale_factor = cos(to_rad(heading_error));
    drive_output*=heading_scale_factor;
    heading_error = reduce_negative_90_to_90(heading_error);
    float heading_output = headingPID.compute(heading_error);
    
    if (drive_error<drive_settle_error) { heading_output = 0; }

    drive_output = clamp(drive_output, -fabs(heading_scale_factor)*drive_max_voltage, fabs(heading_scale_factor)*drive_max_voltage);
    heading_output = clamp(heading_output, -heading_max_voltage, heading_max_voltage);

    drive_output = clamp_min_voltage(drive_output, drive_min_voltage);

    drive_with_voltage(left_voltage_scaling(drive_output, heading_output), right_voltage_scaling(drive_output, heading_output));
    task::sleep(10);
  }
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

void auton_drive::split_arcade() {
  is_reversed = false;
  int direction = 1;
  while (true) {
    float throttle = deadband(controller(primary).Axis3.value(), 5) * direction;
    float turn = deadband(controller(primary).Axis1.value(), 5);

    left_drive.spin(fwd, percent_to_volt(throttle + turn), velocity_units::volt);
    right_drive.spin(fwd, percent_to_volt(throttle - turn), velocity_units::volt);  
    
    if (is_reversed) {
      direction = -1;
    }
    else if (!is_reversed) {
      direction = 1;
    }

    task::sleep(20);
  }  
}