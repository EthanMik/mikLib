#include "mikLib/drive.h"

Chassis::Chassis(mik::motor_group left_drive, mik::motor_group right_drive, int inertial_port,
    double inertial_scale, bool force_calibrate_inertial, double wheel_diameter,
    double drivetrain_rpm, int forward_tracker_port, double forward_tracker_diameter,
    double forward_tracker_center_distance, int sideways_tracker_port, double sideways_tracker_diameter,
    double sideways_tracker_center_distance, mik::distance_reset reset_sensors
):

    tracker_mode(forward_tracker_port != PORT0 ? mik::tracker_mode::FORWARD_TRACKER : mik::tracker_mode::MOTOR_ENCODER),

    forward_tracker(forward_tracker_port),
    sideways_tracker(sideways_tracker_port),
    inertial(inertial_port),

    left_drive(left_drive),
    right_drive(right_drive),

    reset_sensors(reset_sensors),

    sideways_tracker_used(sideways_tracker_port != PORT0),

    inertial_scale(inertial_scale),
    force_calibrate_inertial(force_calibrate_inertial), 

    wheel_diameter(wheel_diameter),
    drivetrain_rpm(drivetrain_rpm),

    drive_in_to_deg_ratio(0),

    forward_tracker_diameter(forward_tracker_diameter),
    forward_tracker_center_distance(forward_tracker_center_distance),
    forward_tracker_inch_to_deg_ratio(M_PI * forward_tracker_diameter / 360.0),

    sideways_tracker_diameter(sideways_tracker_diameter),
    sideways_tracker_center_distance(sideways_tracker_center_distance),
    sideways_tracker_inch_to_deg_ratio(M_PI * sideways_tracker_diameter / 360.0)
{
    float motor_rpm;
    switch (right_drive.getMotors()[0].gear_cartridge()) {
        case vex::gearSetting::ratio6_1:  motor_rpm = 600; break;
        case vex::gearSetting::ratio18_1: motor_rpm = 200; break;
        case vex::gearSetting::ratio36_1: motor_rpm = 100; break;
    }
    drive_in_to_deg_ratio = (drivetrain_rpm / motor_rpm) / 360.0 * M_PI * fabs(wheel_diameter);

    odom.set_physical_distances(
        tracker_mode == mik::tracker_mode::MOTOR_ENCODER ? 0 : forward_tracker_center_distance, 
        sideways_tracker_center_distance
    );
}

void Chassis::set_control_constants(float control_throttle_deadband, float control_throttle_min_output, float control_throttle_curve_gain, float control_turn_deadband, float control_turn_min_output, float control_turn_curve_gain, float control_desaturate_bias) {
    constants.control_throttle_deadband = control_throttle_deadband;
    constants.control_throttle_min_output = control_throttle_min_output;
    constants.control_throttle_curve_gain = control_throttle_curve_gain;
    constants.control_turn_deadband = control_turn_deadband;
    constants.control_turn_min_output = control_turn_min_output;
    constants.control_turn_curve_gain = control_turn_curve_gain;
    constants.control_desaturate_bias = control_desaturate_bias;
}

void Chassis::set_turn_constants(float turn_max_voltage, float turn_kp, float turn_ki, float turn_kd, float turn_starti, float turn_slew) {
    constants.turn_max_voltage = turn_max_voltage;
    constants.turn_kp = turn_kp;
    constants.turn_ki = turn_ki;
    constants.turn_kd = turn_kd;
    constants.turn_starti = turn_starti;
    constants.turn_slew = turn_slew;
} 

void Chassis::set_drive_constants(float drive_max_voltage, float drive_kp, float drive_ki, float drive_kd, float drive_starti, float drive_slew) {
    constants.drive_max_voltage = drive_max_voltage;
    constants.drive_kp = drive_kp;
    constants.drive_ki = drive_ki;
    constants.drive_kd = drive_kd;
    constants.drive_starti = drive_starti;
    constants.drive_slew = drive_slew;
} 

void Chassis::set_heading_constants(float heading_max_voltage, float heading_kp, float heading_ki, float heading_kd, float heading_starti, float heading_slew) {
    constants.heading_max_voltage = heading_max_voltage;
    constants.heading_kp = heading_kp;
    constants.heading_ki = heading_ki;
    constants.heading_kd = heading_kd;
    constants.heading_starti = heading_starti;
    constants.heading_slew = heading_slew;

}

void Chassis::set_swing_constants(float swing_max_voltage, float swing_kp, float swing_ki, float swing_kd, float swing_starti, float swing_slew) {
    constants.swing_max_voltage = swing_max_voltage;
    constants.swing_kp = swing_kp;
    constants.swing_ki = swing_ki;
    constants.swing_kd = swing_kd;
    constants.swing_starti = swing_starti;
    constants.swing_slew = swing_slew;
} 

void Chassis::set_turn_exit_conditions(float turn_settle_error, float turn_settle_time, float turn_large_settle_error, float turn_large_settle_time, float turn_timeout) {
    constants.turn_settle_error = turn_settle_error;
    constants.turn_settle_time = turn_settle_time;
    constants.turn_large_settle_error = turn_large_settle_error;
    constants.turn_large_settle_time = turn_large_settle_time;
    constants.turn_timeout = turn_timeout;
}

void Chassis::set_drive_exit_conditions(float drive_settle_error, float drive_settle_time, float drive_large_settle_error, float drive_large_settle_time, float drive_timeout) {
    constants.drive_settle_error = drive_settle_error;
    constants.drive_settle_time = drive_settle_time;
    constants.drive_large_settle_error = drive_large_settle_error;
    constants.drive_large_settle_time = drive_large_settle_time;
    constants.drive_timeout = drive_timeout;
}

void Chassis::set_swing_exit_conditions(float swing_settle_error, float swing_settle_time, float swing_large_settle_error, float swing_large_settle_time, float swing_timeout) {
    constants.swing_settle_error = swing_settle_error;
    constants.swing_settle_time = swing_settle_time;
    constants.swing_large_settle_error = swing_large_settle_error;
    constants.swing_large_settle_time = swing_large_settle_time;
    constants.swing_timeout = swing_timeout;
}


void Chassis::set_tracking_offsets(float forward_tracker_center_distance, float sideways_tracker_center_distance) {
    odom.set_physical_distances(forward_tracker_center_distance, sideways_tracker_center_distance);
}

void Chassis::set_brake_type(vex::brakeType brake) {
    left_drive.setStopping(brake);
    right_drive.setStopping(brake);
    chassis.stop_behavior = brake;
}

void Chassis::wait() {
    while(motion_running) {
        task::sleep(10);
    }
}

void Chassis::wait_until(float units) {
    while (distance_traveled < units && motion_running) {
        task::sleep(10);
    }
}

void Chassis::wait_until(float units, vex::percentUnits percent_units) {
    while (percent_traveled < units && motion_running) {
        task::sleep(10);
    }
} 

bool Chassis::is_in_motion() {
    return motion_running;
}

void Chassis::cancel_motion() {
    drive_task.stop();
    motion_running = false;
    if (active_min_voltage == 0) { stop_drive(chassis.stop_behavior); }
}

void Chassis::update_drive_max_voltage(float drive_max_voltage) {
    g_drive_distance_params_buffer.max_voltage = drive_max_voltage;
    g_drive_to_point_params_buffer.max_voltage = drive_max_voltage;
    g_drive_to_pose_params_buffer.max_voltage = drive_max_voltage;
}

void Chassis::drive_with_voltage(float left_voltage, float right_voltage){
    left_drive.spin(vex::fwd, left_voltage, volt);
    right_drive.spin(vex::fwd, right_voltage, volt);
}

void Chassis::stop_drive(vex::brakeType brake) {
    if (brake == vex::brakeType::undefined) {
        left_drive.spin(fwd, 0, volt);
        right_drive.spin(fwd, 0, volt);
    } else {
        left_drive.stop(brake);
        right_drive.stop(brake);
    }
}

void Chassis::calibrate_inertial() {
	calibrating = true;
	inertial.calibrate();

	while (inertial.isCalibrating()) {
		vex::task::sleep(25);
	}

    if (!force_calibrate_inertial) {
        calibrating = false;
        return;
    }

  	// Recalibrate inertial until it is within calibration threshold
  	float starting_rotation = chassis.inertial.rotation();
  	task::sleep(1000);
	if (std::abs(chassis.inertial.rotation() - starting_rotation) > minimum_calibration_error) {
		Controller.rumble("-");
		calibrate_inertial();
  	}
  	calibrating = false;
}


float Chassis::get_absolute_heading(){ 
    return reduce_0_to_360(inertial.rotation() * 360.0 / inertial_scale); 
}

void Chassis::mirror_all_auton_x_pos() {
    x_pos_mirrored_ = true;
}

void Chassis::mirror_all_auton_y_pos() {
    y_pos_mirrored_ = true;
}

void Chassis::disable_mirroring() {
    x_pos_mirrored_ = false;
    y_pos_mirrored_ = false;
}

bool Chassis::x_pos_mirrored() { return x_pos_mirrored_; }
bool Chassis::y_pos_mirrored() { return y_pos_mirrored_; }

float Chassis::get_motor_encoder_position() {
    return (get_left_drive_position() + get_right_drive_position()) / 2.0;
}

float Chassis::get_left_drive_position(int index) {
    if (index == -1) {
        return left_drive.averagePosition(deg) * drive_in_to_deg_ratio; 
    }
    return left_drive.getMotors()[index].position(deg) * drive_in_to_deg_ratio; 
}

float Chassis::get_right_drive_position(int index) {
    if (index == -1) {
        return right_drive.averagePosition(deg) * drive_in_to_deg_ratio; 
    }
    return right_drive.getMotors()[index].position(deg) * drive_in_to_deg_ratio; 
} 

float Chassis::get_forward_tracker_position() {
    if (tracker_mode == mik::tracker_mode::MOTOR_ENCODER) {
        return get_motor_encoder_position();
    }
    return forward_tracker.position(vex::deg) * forward_tracker_inch_to_deg_ratio;
}

float Chassis::get_sideways_tracker_position() {
    if (!sideways_tracker_used) return 0;
    return sideways_tracker.position(vex::deg) * sideways_tracker_inch_to_deg_ratio;
}

void Chassis::position_track() {
    while(1) {
        odom.update_position(get_forward_tracker_position(), get_sideways_tracker_position(), get_absolute_heading());
        vex::task::sleep(5);
    }
}

int Chassis::position_track_task(){
    chassis.position_track();
    return 0;
}

void Chassis::set_heading(float orientation_deg){
    inertial.setRotation(orientation_deg * inertial_scale / 360.0, deg);
}

void Chassis::set_coordinates(float X_position, float Y_position, float orientation_deg) {
    if (position_tracking) { odom_task.stop(); }
    position_tracking = true;
    forward_tracker.resetPosition();
    sideways_tracker.resetPosition();
    right_drive.resetPosition();
    left_drive.resetPosition();

    mirror(X_position, Y_position, orientation_deg, x_pos_mirrored_, y_pos_mirrored_);

    odom.set_position({X_position, Y_position}, orientation_deg, get_forward_tracker_position(), get_sideways_tracker_position());
    set_heading(orientation_deg);
    odom_task = vex::task(position_track_task);
    odom_task.setPriority(0);
}

float Chassis::get_X_position() {
    return odom.position.x;
}

float Chassis::get_Y_position() {
    return odom.position.y;
}

bool Chassis::reset_axis(distance_position sensor_position, float max_reset_distance, int reset_attempts) {
    return reset_axis(sensor_position, auto_detect_wall, max_reset_distance, reset_attempts);
}

bool Chassis::reset_axis(distance_position sensor_position, wall_position wall_position, float max_reset_distance, int reset_attempts) {
    const float odom_x = get_X_position();
    const float odom_y = get_Y_position();

    auto wall = reset_sensors.get_wall_facing(sensor_position, odom_x, odom_y, get_absolute_heading());

    const float new_pos = reset_sensors.get_reset_axis_pos(sensor_position, wall_position, odom_x, odom_y, get_absolute_heading(), reset_attempts);

    bool reset_x;
    if (wall_position == wall_position::AUTO) {
        reset_x = (wall != "Top Wall" && wall != "Bottom Wall");
    } else {
        reset_x = (wall_position != wall_position::TOP_WALL && wall_position != wall_position::BOTTOM_WALL);
    }

    if (reset_x && std::abs(new_pos - odom_x) < max_reset_distance) {
        chassis.set_coordinates(new_pos, odom_y, get_absolute_heading());
        print("Reset Odom X Position on " + wall + " Sucessfully", mik::green);
        print("Old: (" + to_string(odom_x) + ", " + to_string(odom_y) + ")" + " -> " + " New: (" + to_string(new_pos) + ", " + to_string(odom_y) + ")", mik::bright_green);
        return true;
    }
    if (!reset_x && std::abs(new_pos - odom_y) < max_reset_distance) {
        chassis.set_coordinates(odom_x, new_pos, get_absolute_heading());
        print("Reset Odom Y Position on " + wall + " Sucessfully", mik::green);
        print("Old: (" + to_string(odom_x) + ", " + to_string(odom_y) + ")" + " -> " + " New: (" + to_string(odom_x) + ", " + to_string(new_pos) + ")", mik::bright_green);
        return true;
    } 
    
    if (reset_x) {
        print("Reset Odom X Position on " + wall + " Failed", mik::red);
        print("Old: (" + to_string(odom_x) + ", " + to_string(odom_y) + ")" + " -> " + " New: (" + to_string(new_pos) + ", " + to_string(odom_y) + ")", mik::bright_red);
    } else {
        print("Reset Odom Y Position on " + wall + " Failed", mik::red);
        print("Old: (" + to_string(odom_x) + ", " + to_string(odom_y) + ")" + " -> " + " New: (" + to_string(odom_x) + ", " + to_string(new_pos) + ")", mik::bright_red);
    }

    return false;
}

void Chassis::disable_control() {
    control_disabled = true;
} 

void Chassis::enable_control() {
    control_disabled = false;
}

static float curve(float input, float deadband, float min_output, float curve_gain) {
    if (fabs(input) <= deadband) { return 0; }
    const float g = fabs(input) - deadband;
    const float g_max = 100 - deadband;
    const float raw_curve = pow(curve_gain, g - 100) * g * sign(input);
    const float raw_curve_max = pow(curve_gain, g_max - 100) * g_max;
    return (100.0 - min_output) / (100) * raw_curve * 100 / raw_curve_max + min_output * sign(input);
}

void Chassis::split_arcade_curved() {
    float throttle = vex::controller(vex::primary).Axis3.value();
    float turn = vex::controller(vex::primary).Axis1.value();
    throttle = std::round(curve(throttle, constants.control_throttle_deadband, constants.control_throttle_min_output, constants.control_throttle_curve_gain));
    turn = std::round(curve(turn, constants.control_turn_deadband, constants.control_turn_min_output, constants.control_turn_curve_gain));
    if (std::fabs(throttle) + std::fabs(turn) > 100) {
        float raw_turn = turn;
        float raw_throttle = throttle;
        throttle *= (1 - constants.control_desaturate_bias * std::fabs(raw_turn / 100.0f));
        turn *= (1 - (1 - constants.control_desaturate_bias) * std::fabs(raw_throttle / 100.0f));
    }
    left_drive.spin(vex::fwd, percent_to_volt(throttle + turn), volt);
    right_drive.spin(vex::fwd, percent_to_volt(throttle - turn), volt);
}

void Chassis::split_arcade() {
    float throttle = deadband(vex::controller(vex::primary).Axis3.value(), constants.control_throttle_deadband);
    float turn = deadband(vex::controller(vex::primary).Axis1.value(), constants.control_turn_deadband);
    left_drive.spin(vex::fwd, percent_to_volt(throttle + turn), volt);
    right_drive.spin(vex::fwd, percent_to_volt(throttle - turn), volt);
}

void Chassis::tank() {
    float left_throttle = deadband(controller(primary).Axis3.value(), constants.control_throttle_deadband);
    float right_throttle = deadband(controller(primary).Axis2.value(), constants.control_throttle_deadband);
    left_drive.spin(fwd, percent_to_volt(left_throttle), volt);
    right_drive.spin(fwd, percent_to_volt(right_throttle), volt);
}

void Chassis::tank_curved() {
    float left_throttle = controller(primary).Axis3.value();
    float right_throttle = controller(primary).Axis2.value();
    left_throttle = std::round(curve(left_throttle, constants.control_throttle_deadband, constants.control_throttle_min_output, constants.control_throttle_curve_gain));
    right_throttle = std::round(curve(right_throttle, constants.control_throttle_deadband, constants.control_throttle_min_output, constants.control_throttle_curve_gain));
    left_drive.spin(fwd, percent_to_volt(left_throttle), volt);
    right_drive.spin(fwd, percent_to_volt(right_throttle), volt);
}

void Chassis::control(drive_mode dm) {
    if (control_disabled) { 
        stop_drive(chassis.stop_behavior);
        return;
    }
    selected_drive_mode = dm;

    switch (dm) {
        case drive_mode::SPLIT_ARCADE:
            split_arcade();
            return;
        case drive_mode::SPLIT_ARCADE_CURVED:
            split_arcade_curved();
            return;
        case drive_mode::TANK:
            tank();
            return;
        case drive_mode::TANK_CURVED:
            tank_curved();
            return;
    }
}