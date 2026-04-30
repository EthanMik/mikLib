#include "vex.h"

void Chassis::turn(float target_angle, float angle_offset, swing_to_angle_params p, turn_type type) {
    // Tasks can only use data from global scope
    desired_angle = target_angle;
    desired_angle_offset = angle_offset;
    turn_params_buffer = p;
    turn_type_buffer = type;

    // Create PID; exit error is only applied if min voltage is non zero
    pid = PID(p.k.p, p.k.i, p.k.d, p.k.starti, p.settle_error, p.settle_time, p.exit_error, p.timeout);

    motion_running = true;
    active_min_voltage = p.min_voltage;
    distance_traveled = 0;
    percent_traveled = 0;

    drive_task = vex::task([](){
        // Read from global scope
        const float angle = chassis.desired_angle;
        const float angle_offset = chassis.desired_angle_offset;
        swing_to_angle_params& p = chassis.turn_params_buffer;
        const turn_type type = chassis.turn_type_buffer;

        bool crossed = false;
        float raw_error = angle_error(angle - chassis.get_absolute_heading() + angle_offset);
        float error = angle_error(angle - chassis.get_absolute_heading() + angle_offset, p.direction);
        const float total_distance = fabs(error);
        float prev_error = error;
        float prev_raw_error = raw_error;
        float prev_output = 0;

        while (!chassis.pid.is_settled()) {
            raw_error = angle_error(angle - chassis.get_absolute_heading() + angle_offset);

            // Check if robot has crossed the target, when robot is crossed it will no longer lock to CW or CCW
            if (sign(raw_error) != sign(prev_raw_error)) { crossed = true; }
            prev_raw_error = raw_error;

            error = crossed ? raw_error : angle_error(angle - chassis.get_absolute_heading() + angle_offset, p.direction);

            // If robot crosses target and min voltage is non zero immediately exit
            if (p.min_voltage != 0 && sign(error) != sign(prev_error)) break;
            chassis.distance_traveled += fabs(error - prev_error);
            chassis.percent_traveled = fmin(100, (chassis.distance_traveled / total_distance) * 100);

            prev_error = error;

            float output = chassis.pid.compute(error);
            output = clamp(output, -p.max_voltage, p.max_voltage);
            // Disable slew when robot is close to target
            output = slew_scaling(output, prev_output, p.slew, fabs(error) > constants.turn_cutoff);

            output = clamp_min_voltage(output, p.min_voltage);

            // Determine sides of drivetrain that turn
            switch (type) {
                case turn_type::TURN:
                    chassis.drive_with_voltage(output, -output);
                    break;
                case turn_type::LEFT_SWING:
                    chassis.left_drive.spin(fwd, output, volt);
                    if (p.opposite_voltage != 0) {
                        chassis.right_drive.spin(fwd, p.opposite_voltage * (output / p.max_voltage), volt);
                    } else {
                        chassis.right_drive.stop(hold);
                    }
                    break;
                case turn_type::RIGHT_SWING:
                    chassis.right_drive.spin(reverse, output, volt);
                    if (p.opposite_voltage != 0) {
                        chassis.left_drive.spin(reverse, p.opposite_voltage * (output / p.max_voltage), volt);
                    } else {
                        chassis.left_drive.stop(hold);
                    }
                    break;
            }

            prev_output = output;
            vex::task::sleep(10);
        }

        chassis.motion_running = false;

        // Stop the chassis if min voltage is non zero, default is coast
        if (p.min_voltage == 0) { chassis.stop_drive(chassis.stop_behavior); } 

        return 0;
    });
    // Hold the task if wait is true
    if (p.wait) { this->wait(); }
}

void Chassis::turn_to_angle(float angle, turn_to_angle_params p) {
    mirror(angle, p.direction, x_pos_mirrored_, y_pos_mirrored_);
    turn(angle, 0, {
        .direction = p.direction,
        .min_voltage = p.min_voltage,
        .max_voltage = p.max_voltage,
        .exit_error = p.exit_error,
        .settle_error = p.settle_error,
        .settle_time = p.settle_time,
        .timeout = p.timeout,
        .slew = p.slew,
        .wait = p.wait,
        .k = {p.k.p, p.k.i, p.k.d, p.k.starti},
    }, turn_type::TURN);
}

void Chassis::left_swing_to_angle(float angle, swing_to_angle_params p) {
    mirror(angle, p.direction, x_pos_mirrored_, y_pos_mirrored_);
    turn(angle, 0, p, turn_type::LEFT_SWING);
}

void Chassis::right_swing_to_angle(float angle, swing_to_angle_params p) {
    mirror(angle, p.direction, x_pos_mirrored_, y_pos_mirrored_);
    turn(angle, 0, p, turn_type::RIGHT_SWING);
}

void Chassis::turn_to_point(float X_position, float Y_position, turn_to_point_params p) {
    mirror(X_position, Y_position, p.direction, x_pos_mirrored_, y_pos_mirrored_);
    desired_X_position = X_position;
    desired_Y_position = Y_position;
    float angle = to_deg(atan2(X_position - get_X_position(), Y_position - get_Y_position()));
    turn(angle, p.angle_offset, {
        .direction = p.direction,
        .min_voltage = p.min_voltage,
        .max_voltage = p.max_voltage,
        .exit_error = p.exit_error,
        .settle_error = p.settle_error,
        .settle_time = p.settle_time,
        .timeout = p.timeout,
        .slew = p.slew,
        .wait = p.wait,
        .k = {p.k.p, p.k.i, p.k.d, p.k.starti},
    }, turn_type::TURN);
}

void Chassis::left_swing_to_point(float X_position, float Y_position, swing_to_point_params p) {
    mirror(X_position, Y_position, p.direction, x_pos_mirrored_, y_pos_mirrored_);
    desired_X_position = X_position;
    desired_Y_position = Y_position;
    float angle = to_deg(atan2(X_position - get_X_position(), Y_position - get_Y_position()));
    turn(angle, p.angle_offset, {
        .direction = p.direction,
        .min_voltage = p.min_voltage,
        .max_voltage = p.max_voltage,
        .opposite_voltage = p.opposite_voltage,
        .exit_error = p.exit_error,
        .settle_error = p.settle_error,
        .settle_time = p.settle_time,
        .timeout = p.timeout,
        .slew = p.slew,
        .wait = p.wait,
        .k = p.k,
    }, turn_type::LEFT_SWING);
}

void Chassis::right_swing_to_point(float X_position, float Y_position, swing_to_point_params p) {
    mirror(X_position, Y_position, p.direction, x_pos_mirrored_, y_pos_mirrored_);
    desired_X_position = X_position;
    desired_Y_position = Y_position;
    float angle = to_deg(atan2(X_position - get_X_position(), Y_position - get_Y_position()));
    turn(angle, p.angle_offset, {
        .direction = p.direction,
        .min_voltage = p.min_voltage,
        .max_voltage = p.max_voltage,
        .opposite_voltage = p.opposite_voltage,
        .exit_error = p.exit_error,
        .settle_error = p.settle_error,
        .settle_time = p.settle_time,
        .timeout = p.timeout,
        .slew = p.slew,
        .wait = p.wait,
        .k = p.k,
    }, turn_type::RIGHT_SWING);
}
