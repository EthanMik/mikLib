#include <stdio.h>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <string>
#include "mikLib/Drive/util.h"
#include "mikLib/globals.h"
#include "mikLib/Drive/constants.h"
#include "robot-config.h"


float clamp(float input, float min, float max) {
    if (input > max) { return max; }
    if (input < min) { return min; }
    return input;
}

float deadband(float input, float width){
    if (fabs(input) < width) { return 0; }
    return input;
}

float deadband_squared(float input, float width){
    if (fabs(input) < width) { return 0; }
    if (input > 0) { input = pow(input / 100.0, 2) * 100; }
    else { input = pow(input / 100.0, 2) * -100; }
    return input;
}

float percent_to_volt(float percent) {
    return (percent * 12.0 / 100.0);
}

float volt_to_percent(float volt) {
    return (volt / 12.0) * 100.0;
}

float to_rad(float angle_deg) {
    return angle_deg * (M_PI / 180.0f);
}

float to_deg(float angle_rad) {
    return (angle_rad * (180.0 / M_PI));
}

float reduce_negative_180_to_180(float angle) {
    angle = fmod(angle + 180.0, 360.0);
    if (angle < 0) angle += 360.0;
    return angle - 180.0;
}

float reduce_negative_90_to_90(float angle) {
    angle = fmod(angle + 90.0, 180.0);
    if (angle < 0) angle += 180.0;
    return angle - 90.0;
}

float reduce_0_to_360(float angle) {
    angle = fmod(angle, 360.0);
    if (angle < 0) angle += 360.0;
    return angle;
}

void mirror(float& x, float& y, float& angle, mik::turn_direction& turn_direction, bool mirror_x, bool mirror_y) {
    if (!mirror_x && !mirror_y) return;

    if (mirror_x) {
        x = -x;
        angle = reduce_0_to_360(360 - angle);
    }

    if (mirror_y) {
        y = -y;
        angle = reduce_0_to_360(180 - angle);
    }

    if (mirror_x ^ mirror_y) {
        turn_direction = turn_direction == mik::turn_direction::CW ? mik::turn_direction::CCW : mik::turn_direction::CW;
    }
}

void mirror(float& angle, bool mirror_x, bool mirror_y) {
    float dummy_x = 0, dummy_y = 0;
    mik::turn_direction unused = mik::turn_direction::FASTEST;
    mirror(dummy_x, dummy_y, angle, unused, mirror_x, mirror_y);
}

void mirror(float& x, float& y, float& angle, bool mirror_x, bool mirror_y) {
    mik::turn_direction unused = mik::turn_direction::FASTEST;
    mirror(x, y, angle, unused, mirror_x, mirror_y);
}

void mirror(float& x, float& y, mik::turn_direction& turn_direction, bool mirror_x, bool mirror_y) {
    float dummy_angle = 0;
    mirror(x, y, dummy_angle, turn_direction, mirror_x, mirror_y);
}

void mirror(float& angle, mik::turn_direction& turn_direction, bool mirror_x, bool mirror_y) {
    float dummy_x = 0, dummy_y = 0;
    mirror(dummy_x, dummy_y, angle, turn_direction, mirror_x, mirror_y);
}

void mirror(float& x, float& y, bool mirror_x, bool mirror_y) {
    float dummy_angle = 0;
    mik::turn_direction unused = mik::turn_direction::FASTEST;
    mirror(x, y, dummy_angle, unused, mirror_x, mirror_y);
}

float angle_error(float error, mik::turn_direction dir) {
    switch (dir) {
        case mik::turn_direction::CW:
            return error < 0 ? error + 360 : error;
        case mik::turn_direction::CCW:
            return error > 0 ? error - 360 : error;
        case mik::turn_direction::FASTEST:
            return reduce_negative_180_to_180(error);
    }
}

bool is_line_settled(float desired_X, float desired_Y, float desired_angle_deg, float current_X, float current_Y, float exit_error) {
    return (desired_Y - current_Y) * cos(to_rad(desired_angle_deg)) <= -(desired_X - current_X) * sin(to_rad(desired_angle_deg)) + exit_error;
}

float left_voltage_scaling(float drive_output, float heading_output) {
    float ratio = std::max(std::fabs(drive_output + heading_output), std::fabs(drive_output - heading_output)) / 12.0;
    if (ratio > 1) {
        return (drive_output + heading_output) / ratio;
    }
    return drive_output + heading_output;
}

float right_voltage_scaling(float drive_output, float heading_output) {
    float ratio = std::max(std::fabs(drive_output + heading_output), std::fabs(drive_output - heading_output)) / 12.0;
    if (ratio > 1) {
        return (drive_output - heading_output) / ratio;
    }
    return drive_output - heading_output;
}

float clamp_min_voltage(float drive_output, float drive_min_voltage) {
    if (drive_output < 0 && drive_output > -drive_min_voltage) {
        return -drive_min_voltage;
    }
    if (drive_output > 0 && drive_output < drive_min_voltage) {
        return drive_min_voltage;
    }
    return drive_output;
}

float slew_scaling(float drive_output, float prev_drive_output, float slew, bool apply) {
    float change = drive_output - prev_drive_output;
    if (slew == 0 || !apply) return drive_output;
    if (change > slew) change = slew;
    else if (change < -slew) change = -slew;
    return prev_drive_output + change;
}

float clamp_max_slip(float drive_output, float current_X, float current_Y, float current_angle_deg, float desired_X, float desired_Y, float drift) {
    const float heading = to_rad(current_angle_deg);

    const float perp_dist = fabs(sin(heading) * (desired_Y - current_Y) - cos(heading) * (desired_X - current_X));
    const float dist = hypot(desired_X - current_X, desired_Y - current_Y);

    const float radius = (dist * dist) / (2.0 * perp_dist);
    const float max_slip = sqrt(drift * radius * 9.8);
    return clamp(drive_output, -max_slip, max_slip);  
}

float overturn_scaling(float drive_output, float heading_output, float max_speed) {
    const float overturn = fabs(heading_output) + fabs(drive_output) - max_speed;
    if (overturn > 0) {
        if (drive_output > 0) {
            return drive_output - overturn;
        }
        else if (drive_output < 0) {
            return drive_output + overturn;
        }
    }
    return drive_output;
}

std::vector<mik::path> motion_profile(const mik::bezier& segment, follow_path_params p, float track_width) {
    mik::point cubic = { -segment.start.x + 3 * segment.c1.x - 3 * segment.c2.x + segment.end.x, -segment.start.y + 3*segment.c1.y - 3*segment.c2.y + segment.end.y };
    mik::point quadratic = { 3 * segment.start.x - 6 * segment.c1.x + 3 * segment.c2.x, 3 * segment.start.y - 6 * segment.c1.y + 3 * segment.c2.y };
    mik::point linear = { -3 * segment.start.x + 3 * segment.c1.x, -3 * segment.start.y + 3 * segment.c1.y };
    mik::point constant = { segment.start.x, segment.start.y };
    
    std::vector<mik::path> path;
    float distance = 0.0;
    const float dt = 0.1;
    float t = 0.0;

    path.push_back(mik::path{
        .x = constant.x,
        .y = constant.y,
        .heading = atan2f(linear.y, linear.x),
        .acceleration = 0,
        .velocity = 0,
        .distance = 0,
        .curvature = 0
    });

    mik::path prev_path = path.back();

    while (t < 1.0) {
        mik::point pt = { cubic.x * t * t * t + quadratic.x * t * t + linear.x * t + constant.x, cubic.y * t * t * t + quadratic.y * t * t + linear.y * t + constant.y };
        mik::point pt_d1 = { 3 * cubic.x * t * t + 2 * quadratic.x * t + linear.x, 3 * cubic.y * t * t + 2 * quadratic.y*t + linear.y };
        mik::point pt_d2 = { 6 * cubic.x * t + 2 * quadratic.x, 6 * cubic.y * t + 2 * quadratic.y };
        float speed = sqrt(pt_d1.x * pt_d1.x + pt_d1.y * pt_d1.y);

        float curvature = (pt_d1.x * pt_d2.y - pt_d1.y * pt_d2.x) / (speed * speed * speed);

        float max_speed_curvature = 2 * p.max_velocity / (2 + track_width * fabs(curvature));
        float max_speed_friction = sqrt(p.friction * p.max_accel / (fabs(curvature)));
        float max_speed_accel = sqrt(prev_path.velocity * prev_path.velocity + 2 * p.max_accel * dt);
        float max_speed = fmin(fmin(max_speed_accel, p.max_velocity), fmin(max_speed_curvature, max_speed_friction));

        distance += dist({pt.x, pt.y}, {path.back().x, path.back().y});

        prev_path = mik::path{
            .x = pt.x,
            .y = pt.y,
            .heading = atan2f(pt_d1.y, pt_d1.x),
            .acceleration = 0,
            .velocity = max_speed,
            .distance = distance,
            .curvature = max_speed_curvature
        };

        path.push_back(prev_path);

        float step = dt / speed;
        t += step;
    }

    t = 1.0;
    int i = path.size() - 1;
    float prev_velocity = 0;

    while (t > 0 && i >= 0) {
        mik::point pt = { cubic.x * t * t * t + quadratic.x * t * t + linear.x * t + constant.x, cubic.y * t * t * t + quadratic.y*t*t + linear.y*t + constant.y };
        mik::point pt_d1 = { 3 * cubic.x * t * t + 2 * quadratic.x * t + linear.x, 3 * cubic.y * t * t + 2 * quadratic.y*t + linear.y };
        mik::point pt_d2 = { 6 * cubic.x*t + 2 * quadratic.x, 6 * cubic.y*t + 2 * quadratic.y };

        if (prev_velocity < path[i].velocity) path[i].velocity = prev_velocity;

        if (i < (int)path.size() - 1) {
            float ds = dist({path[i].x, path[i].y}, {path[i + 1].x, path[i + 1].y});
            if (ds > 0) {
                path[i].acceleration = (path[i + 1].velocity * path[i + 1].velocity - path[i].velocity * path[i].velocity) / (2.0 * ds);
            }
        }

        float speed = sqrt(pt_d1.x * pt_d1.x + pt_d1.y * pt_d1.y);

        float curvature = (pt_d1.x * pt_d2.y - pt_d1.y * pt_d2.x) / (speed * speed * speed);

        float max_speed_curvature = 2 * p.max_velocity / (2 + track_width * fabs(curvature));
        float max_speed_friction = sqrt(p.friction * p.max_accel / (fabs(curvature)));
        float max_speed_accel = sqrt(prev_velocity * prev_velocity + 2 * p.max_accel * dt);
        float max_speed = fminf(fminf(max_speed_accel, p.max_velocity), fminf(max_speed_curvature, max_speed_friction));

        prev_velocity = max_speed;

        float step = dt / speed;
        t -= step;
        i--;
    }

    return path;
}

float dist(mik::point p1, mik::point p2) {
    return std::hypot(p2.x - p1.x, p2.y - p1.y);
}

bool SD_text_file_exists(const std::string& file_name) {
    if (!Brain.SDcard.isInserted()) { 
        return false; 
    }
    if (!Brain.SDcard.exists(file_name.c_str())) {
        print((file_name + " NOT FOUND").c_str(), mik::bright_red);
        return false;
    }
    const std::size_t n = file_name.size();
    std::string file_ending = n > 4 ? file_name.substr(n - 4) : file_name;
    if (file_ending != ".txt") {
        print((file_name + " IS NOT A .TXT").c_str(), mik::bright_red);
        return false;
    }

    return true;
}

void wipe_SD_file(const std::string& file_name) {
    if (!SD_text_file_exists(file_name)) { return; }
    Brain.SDcard.savefile(file_name.c_str(), nullptr, 0);
}

void write_to_SD_file(const std::string& file_name, const std::string& data) {
    if (!SD_text_file_exists(file_name)) { return; }

    std::string output = "";
    output += ("\n" + data);
    std::vector<uint8_t> name_buffer(output.begin(), output.end());
    Brain.SDcard.appendfile(file_name.c_str(), name_buffer.data(), name_buffer.size());
}

static std::vector<char> get_SD_file_char(const std::string& file_name) {
    if (!SD_text_file_exists(file_name)) { return {' '}; }

    int file_size = Brain.SDcard.size(file_name.c_str());
    std::vector<char> buffer(file_size);
    Brain.SDcard.loadfile(file_name.c_str(), reinterpret_cast<uint8_t*>(buffer.data()), file_size);
    return buffer;
}


void remove_duplicates_SD_file(const std::string& file_name, const std::string& duplicate_word) {
    if (!SD_text_file_exists(file_name)) { return; }

    std::vector<char> data_arr = get_SD_file_char(file_name);
    std::string data_line;

    std::size_t end = data_arr.size();
    for (std::size_t i = data_arr.size(); i-- > 0; ) {
        if (data_arr[i] == '\n') {
            data_line.assign(data_arr.begin() + i + 1, data_arr.begin() + end);

            if (data_line.find(duplicate_word) == 0) {
                data_arr.erase(data_arr.begin() + i, data_arr.begin() + end);
            }

            end = i;
        }
    }

    std::vector<uint8_t> buffer(data_arr.begin(), data_arr.end());
    Brain.SDcard.savefile(file_name.c_str(), buffer.data(), buffer.size());
}

std::vector<std::string> get_SD_file_txt(const std::string& file_name) {
    if (!SD_text_file_exists(file_name)) { return {""}; }

    std::vector<std::string> sd_output;
    std::vector<char> data_arr = get_SD_file_char(file_name);
    std::string data_line;

    std::size_t end = data_arr.size();
    for (std::size_t i = data_arr.size(); i-- > 0; ) {
        if (data_arr[i] == '\n') {
            data_line.assign(data_arr.begin() + i + 1, data_arr.begin() + end);
            sd_output.push_back(data_line);
            end = i;
        }
    }
    return sd_output;
}

static const char* to_ansi(mik::color clr) {
    switch (clr) {
        case mik::color::BLACK:          return "\x1b[30m";
        case mik::color::RED:            return "\x1b[31m";
        case mik::color::GREEN:          return "\x1b[32m";
        case mik::color::YELLOW:         return "\x1b[33m";
        case mik::color::BLUE:           return "\x1b[34m";
        case mik::color::MAGENTA:        return "\x1b[35m";
        case mik::color::CYAN:           return "\x1b[36m";
        case mik::color::WHITE:          return "\x1b[37m";
        case mik::color::BRIGHT_BLACK:   return "\x1b[90m";
        case mik::color::BRIGHT_RED:     return "\x1b[91m";
        case mik::color::BRIGHT_GREEN:   return "\x1b[92m";
        case mik::color::BRIGHT_YELLOW:  return "\x1b[93m";
        case mik::color::BRIGHT_BLUE:    return "\x1b[94m";
        case mik::color::BRIGHT_MAGENTA: return "\x1b[95m";
        case mik::color::BRIGHT_CYAN:    return "\x1b[96m";
        case mik::color::BRIGHT_WHITE:   return "\x1b[97m";
    }
}

void print(float num, const mik::color& clr) {
    printf("%s%f%s\n", to_ansi(clr), num, "\x1b[0m");
    fflush(stdout);
}

void print(std::string str, const mik::color& clr) {
    printf("%s%s%s\n", to_ansi(clr), str.c_str(), "\x1b[0m");
    fflush(stdout);
}

void print(const char* str, const mik::color& clr) {
    printf("%s%s%s\n", to_ansi(clr), str, "\x1b[0m");
    fflush(stdout);
}

void print(int num, const mik::color& clr) {
    printf("%s%d%s\n", to_ansi(clr), num, "\x1b[0m");
    fflush(stdout);
}

void print(bool boolean, const mik::color& clr) {
    printf("%s%d%s\n", to_ansi(clr), boolean, "\x1b[0m");
    fflush(stdout);
}

void print(double num, const mik::color& clr) {
    printf("%s%f%s\n", to_ansi(clr), num, "\x1b[0m");
    fflush(stdout);
}

void print(long num, const mik::color& clr) {
    printf("%s%ld%s\n", to_ansi(clr), num, "\x1b[0m");
    fflush(stdout);
}

void print(long long num, const mik::color& clr) {
    printf("%s%lld%s\n", to_ansi(clr), num, "\x1b[0m");
    fflush(stdout);
}

void print(unsigned long long num, const mik::color& clr) {
    printf("%s%llu%s\n", to_ansi(clr), num, "\x1b[0m");
    fflush(stdout);
}

void print(unsigned int num, const mik::color& clr) {
    printf("%s%u%s\n", to_ansi(clr), num, "\x1b[0m");
    fflush(stdout);
}

void print(char c, const mik::color& clr) {
    printf("%s%c%s\n", to_ansi(clr), c, "\x1b[0m");
    fflush(stdout);
}

vex::triport::port& to_triport(int port) {
    return Brain.ThreeWirePort.Port[std::abs(port) - 1];
}

vex::triport::port& to_triport(vex::triport& expander, int port) {
    return expander.Port[std::abs(port) - 1];
}

std::string port_to_string(int port) {
    if (port >= 0 && port <= 21) {
        return "PORT" + to_string(port + 1);
    }

    if (port >= -8 && port <= -1) {
        return std::string("PORT_") + char('A' + std::abs(port) - 1);
    }

    return "PORT0";
}

std::string to_string_float(float num, int precision, bool remove_trailing_zero) {
    char buf[32];
    snprintf(buf, sizeof(buf), "%.*f", precision, num);
    std::string str(buf);
    if (remove_trailing_zero && str.find('.') != std::string::npos) {
        str.erase(str.find_last_not_of('0') + 1);
        if (!str.empty() && str.back() == '.')
            str.pop_back();
        if (str == "-0")
            str = "0";
    }

    return str;
}