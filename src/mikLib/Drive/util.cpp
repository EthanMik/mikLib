#include "vex.h"


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
    return (angle_deg / (180.0 / M_PI));
}

float to_deg(float angle_rad) {
    return (angle_rad * (180.0 / M_PI));
}

float reduce_negative_180_to_180(float angle) {
    while(!(angle >= -180 && angle < 180)) {
        if(angle < -180) { angle += 360; }
        if(angle >= 180) { angle -= 360; }
    }
    return angle;
}

float reduce_negative_90_to_90(float angle) {
    while(!(angle >= -90 && angle < 90)) {
        if(angle < -90) { angle += 180; }
        if(angle >= 90) { angle -= 180; }
    }
    return angle;
}

float reduce_0_to_360(float angle) {
    while(!(angle >= 0 && angle < 360)) {
        if(angle < 0) { angle += 360; }
        if(angle >= 360) { angle -= 360; }
    }
    return angle;
}

float mirror_angle(float angle, bool mirror) { 
    if (mirror) {
        return reduce_0_to_360(360 - angle);
    }
    return angle;
}

mik::direction mirror_direction(mik::direction dir, bool mirror) {
    if (mirror) {
        if (dir == mik::direction::CW) {
            return mik::direction::CCW;
        }
        if (dir == mik::direction::CCW) {
            return mik::direction::CW;
        }
    }
    return dir;
}

float mirror_x(float x, bool mirror) {
    if (mirror) {
        return -x;
    }
    return x;
}

float mirror_y(float y, bool mirror) {
    if (mirror) {
        return -y;
    }
    return y;
}

float angle_error(float error, mik::direction dir) {
    switch (dir)
    {
    case mik::direction::CW:
        return error < 0 ? error + 360 : error;
    case mik::direction::CCW:
        return error > 0 ? error - 360 : error;
    case mik::direction::FASTEST:
        return reduce_negative_180_to_180(error);
    }
}

bool is_line_settled(float desired_X, float desired_Y, float desired_angle_deg, float current_X, float current_Y){
    return (desired_Y - current_Y) * cos(to_rad(desired_angle_deg)) <= -(desired_X - current_X) * sin(to_rad(desired_angle_deg));
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
    if(drive_output < 0 && drive_output > -drive_min_voltage) {
        return -drive_min_voltage;
    }
    if(drive_output > 0 && drive_output < drive_min_voltage) {
        return drive_min_voltage;
    }
    return drive_output;
}

float dist(point p1, point p2) {
    return std::hypot(p2.x - p1.x, p2.y - p1.y);
}

std::vector<point> line_circle_intersections(point center, float radius, point p1, point p2) {
    std::vector<point> intersections = {};

    // Subtract the circle's center to offset the system to origin.
    point offset_1 = point {p1.x - center.x, p1.y - center.y};
    point offset_2 = point {p2.x - center.x, p2.y - center.y};

    double dx = offset_2.x - offset_1.x;
    double dy = offset_2.y - offset_1.y;
    double dr = dist(offset_1, offset_2);
    double D = (offset_1.x * offset_2.y) - (offset_1.y * offset_2.x); // Cross product of offset 1 and 2
    double discriminant = std::pow(radius, 2) * std::pow(dr, 2) - std::pow(D, 2);

    // If our discriminant is greater than or equal to 0, the line formed as a slope of
    // point_1 and point_2 intersects the circle at least once.
    if (discriminant >= 0) {
        // https://mathworld.wolfram.com/Circle-LineIntersection.html
        point solution_1 = point {
            (D * dy + sign(dy) * dx * std::sqrt(discriminant)) / std::pow(dr, 2) + center.x,
            (-D * dx + fabs(dy) * std::sqrt(discriminant)) / std::pow(dr, 2) + center.y
        };
        point solution_2 = point {
            (D * dy - sign(dy) * dx * std::sqrt(discriminant)) / std::pow(dr, 2) + center.x,
            (-D * dx - fabs(dy) * std::sqrt(discriminant)) / std::pow(dr, 2) + center.y
        };

        // Find the bounded intersections.
        // solution_1 and solution_2 are assumed to be true when the line formed as a slope between point_1 and point_2
        // extends infinitely, however we only want to consider intersections that are part of a line segment *between*
        // point_1 and point_2.

        // Find the minimum coordinates for each line (p1 and p2 being the start and end of the segment)
        double min_x = std::min(p1.x, p2.x);
        double max_x = std::max(p1.x, p2.x);
        double min_y = std::min(p1.y, p2.y);
        double max_y = std::max(p1.y, p2.y);

        // Solution 1 intersects the circle within the bounds of point_1 and point_2
        if ((solution_1.x >= min_x && solution_1.x <= max_x) && (solution_1.y >= min_y && solution_1.y <= max_y)) {
            intersections.push_back(solution_1);
        }

        // Solution 2 intersects the circle within the bounds of point_1 and point_2
        if ((solution_2.x >= min_x && solution_2.x <= max_x) && (solution_2.y >= min_y && solution_2.y <= max_y)) {
            intersections.push_back(solution_2);
        }
    }

    return intersections;
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

            if (data_line.find(duplicate_word) != std::string::npos) {
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
    return Brain.ThreeWirePort.Port[port];
}

std::string to_string_float(float num, int precision, bool remove_trailing_zero) {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(precision) << num;
    std::string str = oss.str();
    if (remove_trailing_zero) {
        str.erase(str.find_last_not_of('0') + 1);
        if (!str.empty() && str.back() == '.')
            str.pop_back();
        if (str == "-0")
            str = "0";
    }

    return str;
}