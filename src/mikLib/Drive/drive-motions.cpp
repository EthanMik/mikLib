#include "vex.h"

void Chassis::drive_distance(float distance, drive_distance_params p) {
    // Tasks can only use data from global scope
    desired_distance = distance;

    // Default heading to current heading if not specified
    if (std::isnan(p.heading)) desired_heading = get_absolute_heading();
    else desired_heading = p.heading;

    mirror(desired_heading, x_pos_mirrored_, y_pos_mirrored_);

    drive_distance_params_buffer = p;

    // Create PID; exit error is only applied if min voltage is non zero
    pid = PID(p.drive_k.p, p.drive_k.i, p.drive_k.d, p.drive_k.starti, p.settle_error, p.settle_time, p.exit_error, p.timeout);
    pid_2 = PID(p.heading_k.p, p.heading_k.i, p.heading_k.d, p.heading_k.starti);

    motion_running = true;
    active_min_voltage = p.min_voltage;
    distance_traveled = 0;
    percent_traveled = 0;
    distance_from_target = fabs(distance);

    drive_task = vex::task([](){
        // Read from global scope
        const float distance = chassis.desired_distance;
        const float heading = chassis.desired_heading;
        drive_distance_params& p = chassis.drive_distance_params_buffer;

        const float total_distance = fabs(distance);
        float drive_start_position = chassis.get_forward_tracker_position();
        float current_position = drive_start_position;

        float drive_error = distance + drive_start_position - current_position;
        float prev_drive_error = drive_error;
        float prev_heading_output = 0;
        float prev_drive_output = 0;

        while (!chassis.pid.is_settled()) {
            current_position = chassis.get_forward_tracker_position();

            drive_error = distance + drive_start_position - current_position;
            chassis.distance_traveled += fabs(drive_error - prev_drive_error);
            chassis.percent_traveled = fmin(100, (chassis.distance_traveled / total_distance) * 100);
            chassis.distance_from_target = fabs(drive_error);
            prev_drive_error = drive_error;

            float heading_error = reduce_negative_180_to_180(heading - chassis.get_absolute_heading());
            float drive_output = chassis.pid.compute(drive_error);
            float heading_output = chassis.pid_2.compute(heading_error);

            drive_output = clamp(drive_output, -p.max_voltage, p.max_voltage);
            heading_output = clamp(heading_output, -p.heading_max_voltage, p.heading_max_voltage);

            // Disable drive slew when robot is close to target
            drive_output = slew_scaling(drive_output, prev_drive_output, p.slew, fabs(drive_error) > constants.drive_cutoff);
            heading_output = slew_scaling(heading_output, prev_heading_output, p.heading_slew);

            drive_output = clamp_min_voltage(drive_output, p.min_voltage);

            chassis.drive_with_voltage(drive_output + heading_output, drive_output - heading_output);

            prev_drive_output = drive_output;
            prev_heading_output = heading_output;

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


void Chassis::drive_to_point(float X_position, float Y_position, drive_to_point_params p) {
    mirror(X_position, Y_position, x_pos_mirrored_, y_pos_mirrored_);
    
    // Tasks can only use data from global scope
    desired_X_position = X_position;
    desired_Y_position = Y_position;
    desired_heading = to_deg(atan2(X_position - get_X_position(), Y_position - get_Y_position()));
    drive_to_point_params_buffer = p;
    
    pid = PID(p.drive_k.p, p.drive_k.i, p.drive_k.d, p.drive_k.starti, p.settle_error, p.settle_time, 0, p.timeout);
    pid_2 = PID(p.heading_k.p, p.heading_k.i, p.heading_k.d, p.heading_k.starti);

    motion_running = true;
    active_min_voltage = p.min_voltage;
    distance_traveled = 0;
    percent_traveled = 0;
    distance_from_target = hypot(X_position - get_X_position(), Y_position - get_Y_position());

    drive_task = vex::task([](){
        // Read from global scope
        const float x = chassis.desired_X_position;
        const float y = chassis.desired_Y_position;
        const float heading = chassis.desired_heading;
        drive_to_point_params& p = chassis.drive_to_point_params_buffer;

        bool line_settled = false;
        bool prev_line_settled = is_line_settled(x, y, heading, chassis.get_X_position(), chassis.get_Y_position(), p.exit_error);
        float drive_error = hypot(x - chassis.get_X_position(), y - chassis.get_Y_position());
        const float total_distance = drive_error;

        float prev_drive_error = drive_error;
        float prev_drive_output = 0;
        float prev_heading_output = 0;
        float locked_heading = heading;
        bool heading_locked = false;

        while (!chassis.pid.is_settled()){
            // When robot crosses the target, exit the motion
            line_settled = is_line_settled(x, y, heading, chassis.get_X_position(), chassis.get_Y_position(), p.exit_error);
            if (!(line_settled == prev_line_settled) && p.min_voltage != 0) { break; }
            prev_line_settled = line_settled;

            float desired_heading = to_deg(atan2(x - chassis.get_X_position(), y - chassis.get_Y_position()));

            drive_error = hypot(x - chassis.get_X_position(), y - chassis.get_Y_position());
            float heading_error = reduce_negative_180_to_180(desired_heading - chassis.get_absolute_heading());

            // Update distance traveled
            chassis.distance_traveled += fabs(drive_error - prev_drive_error);
            chassis.percent_traveled = fmin(100, (chassis.distance_traveled / total_distance) * 100);
            chassis.distance_from_target = drive_error;
            prev_drive_error = drive_error;


            float drive_output = chassis.pid.compute(drive_error);
            float heading_scale_factor = cos(to_rad(heading_error)); // Cosine scaling optimization
            drive_output *= heading_scale_factor;

            // Lock heading when robot is close to target
            if (drive_error < constants.drive_cutoff) {
                if (!heading_locked) {
                    locked_heading = desired_heading;
                    heading_locked = true;
                }
                heading_error = reduce_negative_180_to_180(locked_heading - chassis.get_absolute_heading());
            }

            heading_error = reduce_negative_90_to_90(heading_error);

            float heading_output = chassis.pid_2.compute(heading_error);

            drive_output = clamp(drive_output, -fabs(heading_scale_factor) * p.max_voltage, fabs(heading_scale_factor) * p.max_voltage);
            heading_output = clamp(heading_output, -p.heading_max_voltage, p.heading_max_voltage);

            // Disable drive slew when robot is close to target
            drive_output = slew_scaling(drive_output, prev_drive_output, p.slew, fabs(drive_error) > constants.drive_cutoff);

            heading_output = slew_scaling(heading_output, prev_heading_output, p.heading_slew);

            drive_output = clamp_min_voltage(drive_output, p.min_voltage);
    
            prev_drive_output = drive_output;
            prev_heading_output = heading_output;

            chassis.drive_with_voltage(left_voltage_scaling(drive_output, heading_output), right_voltage_scaling(drive_output, heading_output));
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

void Chassis::drive_to_pose(float X_position, float Y_position, float angle, drive_to_pose_params p) {
    mirror(X_position, Y_position, angle, x_pos_mirrored_, y_pos_mirrored_);

    // Tasks can only use data from global scope
    desired_X_position = X_position;
    desired_Y_position = Y_position;
    desired_angle = angle;
    desired_heading = angle;
    drive_to_pose_params_buffer = p;

    pid = PID(p.drive_k.p, p.drive_k.i, p.drive_k.d, p.drive_k.starti, p.settle_error, p.settle_time, 0, p.timeout);
    pid_2 = PID(p.heading_k.p, p.heading_k.i, p.heading_k.d, p.heading_k.starti);

    motion_running = true;
    active_min_voltage = p.min_voltage;
    distance_traveled = 0;
    percent_traveled = 0;
    distance_from_target = hypot(X_position - get_X_position(), Y_position - get_Y_position());

    drive_task = vex::task([](){
        const float forward_prioritization = 95; // How much the robot will prioritize going forward, > 90 means it will choose forward direction more by 5 degrees
        const float settling_max_voltage = 6; // What speed to clamp max voltage to when robot is settling, can be overriden by min

        // Read from global scope
        const float x = chassis.desired_X_position;
        const float y = chassis.desired_Y_position;
        float angle = chassis.desired_angle;
        drive_to_pose_params& p = chassis.drive_to_pose_params_buffer;

        // Determine drive direction; if undefined, choose based on initial heading error
        const float intial_heading_error = reduce_negative_180_to_180(to_deg(atan2(x - chassis.get_X_position(), y - chassis.get_Y_position())) - chassis.get_absolute_heading());
        bool reverse = p.direction == vex::directionType::rev;
        if (p.direction == vex::directionType::undefined) {
            reverse = fabs(intial_heading_error) > forward_prioritization;
        }
        // Flip target angle when reversing so the carrot point stays behind the robot
        if (reverse) reduce_0_to_360(angle += 180);
        bool settling = false;
        bool prev_crossed_line = is_line_settled(x, y, angle, chassis.get_X_position(), chassis.get_Y_position(), p.exit_error);

        // Carrot point is a moving target projected behind the final pose, scaled by remaining distance
        float target_distance = hypot(x - chassis.get_X_position(), y - chassis.get_Y_position());
        const float total_distance = target_distance;
        float carrot_x = x - sin(to_rad(angle)) * (p.lead * target_distance);
        float carrot_y = y - cos(to_rad(angle)) * (p.lead * target_distance);
        float drive_error = hypot(carrot_x - chassis.get_X_position(), carrot_y - chassis.get_Y_position());
        float prev_drive_error = drive_error;

        float prev_drive_output = 0;

        while (!chassis.pid.is_settled()){
            target_distance = hypot(x - chassis.get_X_position(), y - chassis.get_Y_position());
            carrot_x = x - sin(to_rad(angle)) * (p.lead * target_distance);
            carrot_y = y - cos(to_rad(angle)) * (p.lead * target_distance);

            if (settling) {
                carrot_x = x;
                carrot_y = y;
            }

            // Enter settling phase when robot is close to target
            if (target_distance < constants.drive_cutoff && !settling) {
                settling = true;
                p.max_voltage = fmax(fabs(prev_drive_output), settling_max_voltage); 
            }

            // Check if robot has crossed the target line; exit if min voltage is non zero
            float line_settled = is_line_settled(x, y, angle, chassis.get_X_position(), chassis.get_Y_position(), p.exit_error);
            float carrot_settled = is_line_settled(x, y, angle, carrot_x, carrot_y, p.exit_error);
            bool crossed_line = line_settled == carrot_settled;

            if (!crossed_line && prev_crossed_line && p.min_voltage != 0 && settling) { break; }
            prev_crossed_line = crossed_line;

            drive_error = hypot(carrot_x - chassis.get_X_position(), carrot_y - chassis.get_Y_position());
            float current_heading = chassis.get_absolute_heading();
            // Flip current heading when reversing so heading error is computed from the rear
            if (reverse) current_heading += 180;

            float heading_error = reduce_negative_180_to_180(to_deg(atan2(carrot_x - chassis.get_X_position(), carrot_y - chassis.get_Y_position())) - current_heading);

            if (settling) {
                // Use cosine-projected distance to target for smoother deceleration
                drive_error = target_distance;
                drive_error *= cos(to_rad(reduce_negative_180_to_180(to_deg(atan2(x - chassis.get_X_position(), y - chassis.get_Y_position())) - chassis.get_absolute_heading())));
                heading_error = reduce_negative_180_to_180(angle - current_heading);
            } else {
                // Sign drive error by whether the robot is facing toward or away from the carrot
                drive_error *= sign(cos(to_rad(reduce_negative_180_to_180(to_deg(atan2(carrot_x - chassis.get_X_position(), carrot_y - chassis.get_Y_position())) - chassis.get_absolute_heading()))));
            }

            chassis.distance_traveled += fabs(drive_error - prev_drive_error);
            chassis.percent_traveled = fmin(100, (chassis.distance_traveled / total_distance) * 100);
            chassis.distance_from_target = target_distance;
            prev_drive_error = drive_error;

            float drive_output = chassis.pid.compute(drive_error);
            float heading_output = chassis.pid_2.compute(heading_error);

            heading_output = clamp(heading_output, -p.heading_max_voltage, p.heading_max_voltage);
            drive_output = clamp(drive_output, -p.max_voltage, p.max_voltage);

            // Disable slew during settling
            drive_output = slew_scaling(drive_output, prev_drive_output, p.slew, !settling);
            // Limit voltage to prevent slipping into the wrong arc
            drive_output = clamp_max_slip(drive_output, chassis.get_X_position(), chassis.get_Y_position(), current_heading, carrot_x, carrot_y, p.drift);
            // Scale down drive output when heading error is large to prevent overturning
            drive_output = overturn_scaling(drive_output, heading_output, p.max_voltage);

            // Enforce drive direction before settling
            if (!reverse && !settling) drive_output = fmax(drive_output, 0);
            else if (reverse && !settling) drive_output = fmin(drive_output, 0);

            drive_output = clamp_min_voltage(drive_output, p.min_voltage);

            chassis.drive_with_voltage(left_voltage_scaling(drive_output, heading_output), right_voltage_scaling(drive_output, heading_output));

            prev_drive_output = drive_output;

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

// Grab motor groups based on their names, this code is kinda sketchy but works without blowing up chassis constructor
static mik::motor_group left_front_motors = chassis.left_drive.getMotorsKeyword("front");
static mik::motor_group left_back_motors = chassis.left_drive.getMotorsKeyword("back");
static mik::motor_group right_front_motors = chassis.right_drive.getMotorsKeyword("front");
static mik::motor_group right_back_motors = chassis.right_drive.getMotorsKeyword("back");

void Chassis::holonomic_to_pose(float X_position, float Y_position, float angle, holonomic_to_pose_params p) {
    mirror(X_position, Y_position, angle, x_pos_mirrored_, y_pos_mirrored_);

    desired_X_position = X_position;
    desired_Y_position = Y_position;
    desired_angle = angle;
    holonomic_to_pose_params_buffer = p;

    pid = PID(p.drive_k.p, p.drive_k.i, p.drive_k.d, p.drive_k.starti, p.settle_error, p.settle_time, 0, p.timeout);
    pid_2 = PID(p.heading_k.p, p.heading_k.i, p.heading_k.d, p.heading_k.starti, p.turn_settle_error, p.turn_settle_time, 0, p.timeout);
    float target_distance = hypot(X_position - chassis.get_X_position(), Y_position - chassis.get_Y_position());

    motion_running = true;
    active_min_voltage = p.min_voltage;
    distance_traveled = 0;
    distance_from_target = target_distance;
    percent_traveled = 0;

    drive_task = vex::task([](){
        const float x = chassis.desired_X_position;
        const float y = chassis.desired_Y_position;
        const float angle = chassis.desired_angle;
        holonomic_to_pose_params& p = chassis.holonomic_to_pose_params_buffer;

        const float heading = to_deg(atan2(x - chassis.get_X_position(), y - chassis.get_Y_position()));
        bool line_settled = false;
        bool prev_line_settled = is_line_settled(x, y, heading, chassis.get_X_position(), chassis.get_Y_position(), p.exit_error);
        float drive_error = hypot(x - chassis.get_X_position(), y - chassis.get_Y_position());
        const float total_distance = drive_error;
        float prev_drive_error = drive_error;
        float prev_drive_output = 0;

        while (!(chassis.pid.is_settled() && chassis.pid_2.is_settled())) {
            float heading = to_deg(atan2(x - chassis.get_X_position(), y - chassis.get_Y_position()));
            line_settled = is_line_settled(x, y, heading, chassis.get_X_position(), chassis.get_Y_position(), p.exit_error);
            if (!(line_settled == prev_line_settled) && p.min_voltage != 0) { break; }
            prev_line_settled = line_settled;

            drive_error = hypot(x - chassis.get_X_position(), y - chassis.get_Y_position());
            float turn_error = reduce_negative_180_to_180(angle - chassis.get_absolute_heading());

            chassis.distance_traveled += fabs(drive_error - prev_drive_error);
            chassis.distance_from_target = drive_error;
            chassis.percent_traveled = fmin(100, (chassis.distance_traveled / total_distance) * 100);
            prev_drive_error = drive_error;

            float drive_output = chassis.pid.compute(drive_error);
            float turn_output  = chassis.pid_2.compute(turn_error);

            drive_output = clamp(drive_output, -p.max_voltage, p.max_voltage);
            turn_output  = clamp(turn_output, -p.heading_max_voltage, p.heading_max_voltage);

            drive_output = slew_scaling(drive_output, prev_drive_output, p.slew, fabs(drive_error) > constants.drive_cutoff);
            drive_output = clamp_min_voltage(drive_output, p.min_voltage);

            float heading_to_target = atan2(y - chassis.get_Y_position(), x - chassis.get_X_position());
            float current_angle = to_rad(chassis.get_absolute_heading());

            left_front_motors.spin(fwd, drive_output * cos(current_angle + heading_to_target - M_PI / 4) + turn_output, volt);
            left_back_motors.spin(fwd,  drive_output * cos(-current_angle - heading_to_target + 3 * M_PI / 4) + turn_output, volt);
            right_front_motors.spin(fwd, drive_output * cos(-current_angle - heading_to_target + 3 * M_PI / 4) - turn_output, volt);
            right_back_motors.spin(fwd,  drive_output * cos(current_angle + heading_to_target - M_PI / 4) - turn_output, volt);

            prev_drive_output = drive_output;

            vex::task::sleep(10);
        }

        chassis.motion_running = false;
        if (p.min_voltage == 0) { chassis.stop_drive(chassis.stop_behavior); }

        return 0;
    });

    if (p.wait) { this->wait(); }
}

namespace mik {
    struct path {
        float x, y;
        float heading;
        float curvature;
        float velocity;
        float acceleration;
        float distance;
    };
}

static std::vector<mik::path> motion_profile(const bezier& segment, follow_path_params p) {
    struct coeffs { point cubic, quadratic, linear, constant; };

    point cubic = { -segment.start.x + 3 * segment.c1.x - 3 * segment.c2.x + segment.end.x, -segment.start.y + 3*segment.c1.y - 3*segment.c2.y + segment.end.y }; 
    point quadratic = { 3 * segment.start.x - 6 * segment.c1.x + 3 * segment.c2.x, 3 * segment.start.y - 6 * segment.c1.y + 3 * segment.c2.y };
    point linear = { -3 * segment.start.x + 3 * segment.c1.x, -3 * segment.start.y + 3 * segment.c1.y };
    point constant = { segment.start.x, segment.start.y };

    std::vector<mik::path> path;
    float distance = 0.0;
    float t = 0.0;

    while (t < 1.0) {
        float ct = fminf(t, 1.f);

        point p = { cubic.x * t * t * t + quadratic.x * t * t + linear.x * t + constant.x, cubic.y * t * t * t + quadratic.y*t*t + linear.y*t + constant.y };
        point p_d1 = { 3 * cubic.x * t * t + 2 * quadratic.x * t + linear.x, 3 * cubic.y * t * t + 2 * quadratic.y*t + linear.y };
        point p_d2 = { 6 * cubic.x*t + 2 * quadratic.x, 6 * cubic.y*t + 2 * quadratic.y };

        float speed = hypotf(p_d1.x, p_d1.y);
        float heading  = speed > 1e-7f ? atan2f(p_d1.y, p_d1.x) : 0.0;
        float curvature = speed > 1e-7f ? (p_d1.x * p_d2.y - p_d1.y * p_d2.x) / (speed * speed * speed) : 0.0;

        if (!path.empty()) {
            float dx = p.x - path.back().x;
            float dy = p.y - path.back().y;
            distance += hypotf(dx, dy);
        }

        path.push_back({ p.x, p.y, heading, curvature, 0, 0, distance });

        float step = speed > 1e-7f ? 0.5 / speed : 0.5;
        t += step;
    }

    int points = path.size();

    for (int i = 0; i < points; ++i) {
        float k = fabsf(path[i].curvature);
        float v_wheel = p.max_velocity;
        float v_friction = p.max_velocity;

        if (k > 1e-6f) {
            v_wheel = 2.f * p.max_velocity / (2.0 + track_width * k);
            v_friction = sqrtf(p.friction / k);
        }

        path[i].velocity = fminf(p.max_velocity, fminf(v_wheel, v_friction));
    }

    path[0].velocity = 0.0;
    for (int i = 1; i < points; ++i) {
        float ds = path[i].distance - path[i - 1].distance;
        path[i].velocity = fminf(path[i].velocity, sqrtf(path[i - 1].velocity * path[i - 1].velocity + 2.f * p.max_accel * ds));
    }

    path[points - 1].velocity = 0.0;
    for (int i = points - 2; i >= 0; --i) {
        float ds = path[i + 1].distance - path[i].distance;
        path[i].velocity = fminf(path[i].velocity, sqrtf(path[i + 1].velocity * path[i + 1].velocity + 2.f * p.max_accel * ds));
    }

    for (int i = 0; i < points; ++i) {
        float dv, ds;
        if (i == 0) {
            dv = path[1].velocity - path[0].velocity;
            ds = path[1].distance - path[0].distance;
        } else if (i == points - 1) {
            dv = path[points - 1].velocity - path[points - 2].velocity;
            ds = path[points - 1].distance - path[points - 2].distance;
        } else {
            dv = path[i + 1].velocity - path[i - 1].velocity;
            ds = path[i + 1].distance - path[i - 1].distance;
        }
        path[i].acceleration = ds > 1e-7f ? path[i].velocity * dv / ds : 0.0;
    }

    return path;
}

void Chassis::follow_path(bezier segment, follow_path_params p) {
    std::vector<mik::path> path;
    int points = path.size();

    int closest_idx = 0;
    int search = 60;

    for (int elapsed = 0; elapsed < p.timeout; elapsed += 10) {
        int search_end = fmin(closest_idx + search, points - 1);

        for (int i = closest_idx + 1; i < search_end; ++i) {
            float dist_to_closest = dist({ path[closest_idx].x, path[closest_idx].y }, { get_X_position(), get_Y_position() });
            float dist_to_current = dist({ path[i].x, path[i].y }, { get_X_position(), get_Y_position() });
            if (dist_to_current < dist_to_closest) closest_idx = i;
        }

        float dist_to_end = dist({ path[points - 1].x, path[points - 1].y}, { get_X_position(), get_Y_position() });
        if (closest_idx >= points - 1 || dist_to_end < p.lookahead * 0.5) break;


        float target_distance = fmin(path[closest_idx].distance + p.lookahead, path[points - 1].distance);

        int lookahead_idx = closest_idx;
        while (lookahead_idx < points - 1 && path[lookahead_idx].distance < target_distance) {
            ++lookahead_idx;
        }

        mik::path lookahead_point = path[lookahead_idx];
        if (lookahead_idx > 0) {
            float prev_distance = path[lookahead_idx - 1].distance;
            float next_distance  = path[lookahead_idx].distance;
            if (next_distance > prev_distance) {
                float a = (target_distance - prev_distance) / (next_distance  - prev_distance);
                mik::path prev = path[lookahead_idx - 1];
                mik::path current = path[lookahead_idx];
                lookahead_point = {
                    .x = prev.x + a * (current.x - prev.x),
                    .y = prev.y + a * (current.y - prev.y),
                };            
            }
        }

        // curvature
        
        float delta_x = lookahead_point.x - get_X_position();
        float delta_y = lookahead_point.y - get_Y_position();

        float heading = to_rad(get_absolute_heading());
        float forward = delta_x * sinf(heading) + delta_y * cosf(heading);
        float right = delta_x * cosf(heading) - delta_y * sinf(heading);

        float distance_squared = forward * forward + right * right;
        float curvature = distance_squared > 1e-7 ? 
            (2.0 * right / distance_squared) : 0;

        float target_vel = path[closest_idx].velocity;
        float target_acc = path[closest_idx].acceleration;

        float target_left_vel = target_vel * (1.0 + curvature * track_width * 0.5);
        float target_right_vel = target_vel * (1.0 - curvature * track_width * 0.5);

        float ratio = fmax(fabsf(target_left_vel), fabsf(target_right_vel));
        if (ratio > p.max_velocity) { 
            target_left_vel *= p.max_velocity / ratio;
            target_right_vel *= p.max_velocity / ratio;
        }

        float left_output = p.kS * sign(target_left_vel) + p.kV * target_left_vel + p.kA * target_acc;
        float right_output = p.kS * sign(target_right_vel) + p.kV * target_right_vel + p.kA * target_acc;

        left_output = clamp(left_output, -12, 12);
        right_output = clamp(right_output, -12, 12);

        drive_with_voltage(left_output, right_output);
        task::sleep(10);
    }
    stop_drive(stop_behavior);
}