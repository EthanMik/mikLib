#include "vex.h"

drive_to_point_params g_drive_to_point_params_buffer{};
drive_to_pose_params g_drive_to_pose_params_buffer{};
drive_distance_params g_drive_distance_params_buffer{};

void Chassis::drive_distance(float distance, drive_distance_params p) {
    desired_distance = distance;
    if (std::isnan(p.heading)) desired_heading = get_absolute_heading();
    else desired_heading = p.heading;

    g_drive_distance_params_buffer = p;

    pid = PID(distance, p.drive_k.p, p.drive_k.i, p.drive_k.d, p.drive_k.starti, p.settle_error, p.settle_time, p.large_settle_error, p.large_settle_time, p.min_voltage > 0 ? p.exit_error : 0, p.timeout);
    pid_2 = PID(reduce_negative_180_to_180(desired_heading - get_absolute_heading()), p.heading_k.p, p.heading_k.i, p.heading_k.d, p.heading_k.starti);

    motion_running = true;
    active_min_voltage = p.min_voltage;
    distance_traveled = 0;
    percent_traveled = 0;

    drive_task = vex::task([](){
        const float distance = chassis.desired_distance;
        const float heading = chassis.desired_heading;
        drive_distance_params& p = g_drive_distance_params_buffer;

        const float total_distance = fabs(distance);
        float drive_start_position = chassis.get_forward_tracker_position();
        float current_position = drive_start_position;

        float drive_error = distance + drive_start_position - current_position;
        float prev_drive_error = drive_error;
        float prev_heading_output = 0;
        float prev_drive_output = 0;

        while (chassis.pid.is_settled() == false) {
            current_position = chassis.get_forward_tracker_position();

            drive_error = distance + drive_start_position - current_position;
            chassis.distance_traveled += std::abs(drive_error - prev_drive_error);
            chassis.percent_traveled = std::min(100.0f, (chassis.distance_traveled / total_distance) * 100);
            prev_drive_error = drive_error;

            float heading_error = reduce_negative_180_to_180(heading - chassis.get_absolute_heading());
            float drive_output = chassis.pid.compute(drive_error);
            float heading_output = chassis.pid_2.compute(heading_error);

            drive_output = clamp(drive_output, -p.max_voltage, p.max_voltage);
            heading_output = clamp(heading_output, -p.heading_max_voltage, p.heading_max_voltage);

            drive_output = slew_scaling(drive_output, prev_drive_output, p.slew, fabs(drive_error) > constants.drive_cutoff);
            heading_output = slew_scaling(heading_output, prev_heading_output, p.heading_slew);

            drive_output = clamp_min_voltage(drive_output, p.min_voltage);

            chassis.drive_with_voltage(drive_output + heading_output, drive_output - heading_output);

            prev_drive_output = drive_output;
            prev_heading_output = heading_output;

            vex::task::sleep(10);
        }

        chassis.motion_running = false;
        if (p.min_voltage == 0) { chassis.stop_drive(chassis.stop_behavior); }

        return 0;
    });
    if (p.wait) {
        this->wait();
    }
}


void Chassis::drive_to_point(float X_position, float Y_position, drive_to_point_params p) {
    mirror(X_position, Y_position, x_pos_mirrored_, y_pos_mirrored_);

    desired_X_position = X_position;
    desired_Y_position = Y_position;
    g_drive_to_point_params_buffer = p;

    pid = PID(hypot(X_position - get_X_position(), Y_position - get_Y_position()), p.drive_k.p, p.drive_k.i, p.drive_k.d, p.drive_k.starti, p.settle_error, p.settle_time, p.large_settle_error, p.large_settle_time, 0, p.timeout);
    desired_heading = to_deg(atan2(X_position - get_X_position(), Y_position - get_Y_position()));
    pid_2 = PID(desired_heading - get_absolute_heading(), p.heading_k.p, p.heading_k.i, p.heading_k.d, p.heading_k.starti);

    motion_running = true;
    active_min_voltage = p.min_voltage;
    distance_traveled = 0;
    percent_traveled = 0;

    drive_task = vex::task([](){
        const float x_pos = chassis.desired_X_position;
        const float y_pos = chassis.desired_Y_position;
        const float heading = chassis.desired_heading;
        drive_to_point_params& p = g_drive_to_point_params_buffer;

        const float exit_x = x_pos - sin(to_rad(heading)) * p.exit_error;
        const float exit_y = y_pos - cos(to_rad(heading)) * p.exit_error;

        bool line_settled = false;
        bool prev_line_settled = is_line_settled(exit_x, exit_y, heading, chassis.get_X_position(), chassis.get_Y_position());
        float drive_error = hypot(x_pos - chassis.get_X_position(), y_pos - chassis.get_Y_position());
        const float total_distance = drive_error;

        float prev_drive_error = drive_error;
        float prev_drive_output = 0;
        float prev_heading_output = 0;
        float locked_heading = heading;
        bool heading_locked = false;

        while (!chassis.pid.is_settled()){
            line_settled = is_line_settled(exit_x, exit_y, heading, chassis.get_X_position(), chassis.get_Y_position());
            if (line_settled && !prev_line_settled && p.min_voltage > 0) { break; }
            prev_line_settled = line_settled;

            float desired_heading = to_deg(atan2(x_pos - chassis.get_X_position(), y_pos - chassis.get_Y_position()));
            int drive_sign = 1;
            if (p.drive_direction == mik::drive_direction::REV) {
                desired_heading = reduce_negative_180_to_180(desired_heading + 180);
                drive_sign = -1;
            }

            drive_error = hypot(x_pos - chassis.get_X_position(), y_pos - chassis.get_Y_position());
            chassis.distance_traveled += std::abs(drive_error - prev_drive_error);
            chassis.percent_traveled = std::min(100.0f, (chassis.distance_traveled / total_distance) * 100);
            prev_drive_error = drive_error;

            float heading_error = reduce_negative_180_to_180(desired_heading - chassis.get_absolute_heading());

            float drive_output = chassis.pid.compute(drive_error);
            float heading_scale_factor = cos(to_rad(heading_error));
            if (p.drive_direction != mik::drive_direction::FASTEST) heading_scale_factor = std::max(0.0f, heading_scale_factor);
            drive_output *= heading_scale_factor * drive_sign;

            if (drive_error < constants.drive_cutoff) {
                if (!heading_locked) {
                    locked_heading = desired_heading;
                    heading_locked = true;
                }
                heading_error = reduce_negative_180_to_180(locked_heading - chassis.get_absolute_heading());
            }

            if (p.drive_direction == mik::drive_direction::FASTEST) heading_error = reduce_negative_90_to_90(heading_error);

            float heading_output = chassis.pid_2.compute(heading_error);

            drive_output = clamp(drive_output, -fabs(heading_scale_factor) * p.max_voltage, fabs(heading_scale_factor) * p.max_voltage);
            heading_output = clamp(heading_output, -p.heading_max_voltage, p.heading_max_voltage);

            drive_output = slew_scaling(drive_output, prev_drive_output, p.slew, fabs(drive_error) > constants.drive_cutoff);
            heading_output = slew_scaling(heading_output, prev_heading_output, p.heading_slew);

            drive_output = clamp_min_voltage(drive_output, p.min_voltage);
    
            prev_drive_output = drive_output;
            prev_heading_output = heading_output;

            chassis.drive_with_voltage(left_voltage_scaling(drive_output, heading_output), right_voltage_scaling(drive_output, heading_output));
            vex::task::sleep(10);
        }

        chassis.motion_running = false;
        if (p.min_voltage == 0) { chassis.stop_drive(chassis.stop_behavior); }

        return 0;
    });

    if (p.wait) { this->wait(); }
}

void Chassis::drive_to_pose(float X_position, float Y_position, float angle, drive_to_pose_params p) {
    mirror(X_position, Y_position, angle, x_pos_mirrored_, y_pos_mirrored_);

    desired_X_position = X_position;
    desired_Y_position = Y_position;
    desired_angle = angle;
    desired_heading = angle;
    g_drive_to_pose_params_buffer = p;

    float target_distance = hypot(X_position - get_X_position(), Y_position - get_Y_position());
    pid = PID(target_distance, p.drive_k.p, p.drive_k.i, p.drive_k.d, p.drive_k.starti, p.settle_error, p.settle_time, p.large_settle_error, p.large_settle_time, 0, p.timeout);
    pid_2 = PID(to_deg(atan2(X_position - get_X_position(), Y_position - get_Y_position())) - get_absolute_heading(), p.heading_k.p, p.heading_k.i, p.heading_k.d, p.heading_k.starti);

    motion_running = true;
    active_min_voltage = p.min_voltage;
    distance_traveled = 0;
    percent_traveled = 0;

    drive_task = vex::task([](){
        const float x_pos = chassis.desired_X_position;
        const float y_pos = chassis.desired_Y_position;
        const float angle = chassis.desired_angle;
        drive_to_pose_params& p = g_drive_to_pose_params_buffer;

        const float exit_x = x_pos - sin(to_rad(angle)) * p.exit_error;
        const float exit_y = y_pos - cos(to_rad(angle)) * p.exit_error;

        bool line_settled = is_line_settled(exit_x, exit_y, angle, chassis.get_X_position(), chassis.get_Y_position());
        bool prev_line_settled = is_line_settled(exit_x, exit_y, angle, chassis.get_X_position(), chassis.get_Y_position());
        bool crossed_center_line = false;
        bool center_line_side = is_line_settled(x_pos, y_pos, angle + 90, chassis.get_X_position(), chassis.get_Y_position());
        bool prev_center_line_side = center_line_side;

        float target_distance = hypot(x_pos - chassis.get_X_position(), y_pos - chassis.get_Y_position());
        const float total_distance = target_distance;
        float carrot_X = x_pos - sin(to_rad(angle)) * (p.lead * target_distance + 0);
        float carrot_Y = y_pos - cos(to_rad(angle)) * (p.lead * target_distance + 0);
        float drive_error = hypot(carrot_X - chassis.get_X_position(), carrot_Y - chassis.get_Y_position());
        float prev_drive_error = drive_error;

        float prev_drive_output = 0;

        while (!chassis.pid.is_settled()){
            line_settled = is_line_settled(exit_x, exit_y, angle, chassis.get_X_position(), chassis.get_Y_position());
            if (line_settled && !prev_line_settled && p.min_voltage > 0) { break; }
            prev_line_settled = line_settled;

            center_line_side = is_line_settled(x_pos, y_pos, angle + 90, chassis.get_X_position(), chassis.get_Y_position());
            if (center_line_side != prev_center_line_side) {
                crossed_center_line = true;
            }

            target_distance = hypot(x_pos - chassis.get_X_position(), y_pos - chassis.get_Y_position());

            carrot_X = x_pos - sin(to_rad(angle)) * (p.lead * target_distance + 0);
            carrot_Y = y_pos - cos(to_rad(angle)) * (p.lead * target_distance + 0);

            drive_error = hypot(carrot_X - chassis.get_X_position(), carrot_Y - chassis.get_Y_position());

            float heading_error = reduce_negative_180_to_180(to_deg(atan2(carrot_X - chassis.get_X_position(), carrot_Y - chassis.get_Y_position())) - chassis.get_absolute_heading());
            int drive_sign = 1;

            chassis.distance_traveled += std::abs(drive_error - prev_drive_error);
            chassis.percent_traveled = std::min(100.0f, (chassis.distance_traveled / total_distance) * 100);
            prev_drive_error = drive_error;

            if (drive_error < 7.5 || crossed_center_line || drive_error < 0) { 
                heading_error = reduce_negative_180_to_180(angle - chassis.get_absolute_heading()); 
                drive_error = target_distance;
            }

            // if (p.drive_direction == mik::drive_direction::REV) {
            //     heading_error = reduce_negative_180_to_180(heading_error + 180);
            //     drive_sign = -1;
            // }
            
            float drive_output = chassis.pid.compute(drive_error);

            float heading_scale_factor = cos(to_rad(heading_error));
            // if (p.drive_direction != mik::drive_direction::FASTEST) heading_scale_factor = std::max(0.0f, heading_scale_factor);

            drive_output *= heading_scale_factor * drive_sign;

            /* if (p.drive_direction == mik::drive_direction::FASTEST) */ 
            heading_error = reduce_negative_90_to_90(heading_error);
            float heading_output = chassis.pid_2.compute(heading_error);

            drive_output = clamp(drive_output, -fabs(heading_scale_factor) * p.max_voltage, fabs(heading_scale_factor) * p.max_voltage);
            heading_output = clamp(heading_output, -p.heading_max_voltage, p.heading_max_voltage);
            
            drive_output = slew_scaling(drive_output, prev_drive_output, p.slew, fabs(drive_error) > constants.drive_cutoff);
            drive_output = clamp_max_slip(drive_output, chassis.get_X_position(), chassis.get_Y_position(), chassis.get_absolute_heading(), carrot_X, carrot_Y, p.drift);
            drive_output = overturn_scaling(drive_output, heading_output, p.max_voltage * fabs(heading_scale_factor));
            drive_output = clamp_min_voltage(drive_output, p.min_voltage);        

            chassis.drive_with_voltage(left_voltage_scaling(drive_output, heading_output), right_voltage_scaling(drive_output, heading_output));

            prev_drive_output = drive_output;

            vex::task::sleep(10);
        }

        chassis.motion_running = false;
        if (p.min_voltage == 0) { chassis.stop_drive(chassis.stop_behavior); }

        return 0;
    });

    if (p.wait) { this->wait(); }
}