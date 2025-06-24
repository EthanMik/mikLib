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

float normalize_to_volt(float normalized_percent) {
  return (normalized_percent * 12.0);
}

float volt_to_percent(float volt) {
  return (volt / 12.0) * 100.0;
}

float volt_to_normalized(float volt) {
  return volt / 12.0;
}

float to_rad(float angle_deg) {
  return(angle_deg / (180.0 / M_PI));
}

float to_deg(float angle_rad) {
  return(angle_rad * (180.0 / M_PI));
}

float reverse_angle(float angle) {
  if (angle > 0) { angle -= 180; }
  else { angle += 180; }
  return angle;
}

float reduce_negative_180_to_180(float angle) {
  while(!(angle >= -180 && angle < 180)) {
    if(angle < -180) { angle += 360; }
    if(angle >= 180) { angle -= 360; }
  }
  return(angle);
}

float reduce_negative_90_to_90(float angle) {
  while(!(angle >= -90 && angle < 90)) {
    if(angle < -90) { angle += 180; }
    if(angle >= 90) { angle -= 180; }
  }
  return(angle);
}

float reduce_0_to_360(float angle) {
  while(!(angle >= 0 && angle < 360)) {
    if(angle < 0) { angle += 360; }
    if(angle >= 360) { angle -= 360; }
  }
  return(angle);
}

bool is_line_settled(float desired_X, float desired_Y, float desired_angle_deg, float current_X, float current_Y){
  return( (desired_Y - current_Y) * cos(to_rad(desired_angle_deg)) <= -(desired_X-current_X) * sin(to_rad(desired_angle_deg)) );
}

float left_voltage_scaling(float drive_output, float heading_output) {
  float ratio = std::max(std::fabs(drive_output + heading_output), std::fabs(drive_output - heading_output)) / 12.0;
  if (ratio > 1) {
    return (drive_output + heading_output) / ratio;
  }
  return drive_output + heading_output;
}

float right_voltage_scaling(float drive_output, float heading_output) {
  float ratio = std::max(std::fabs(drive_output + heading_output), std::fabs(drive_output - heading_output))/12.0;
  if (ratio > 1) {
    return (drive_output - heading_output) / ratio;
  }
  return drive_output - heading_output;
}

float clamp_min_voltage(float drive_output, float drive_min_voltage) {
  if(drive_output < 0 && drive_output > -drive_min_voltage){
      return -drive_min_voltage;
  }
  if(drive_output > 0 && drive_output < drive_min_voltage){
    return drive_min_voltage;
  }
  return drive_output;
}

std::vector<char> get_SD_file_char(const std::string& file_name) {
  if (!Brain.SDcard.isInserted()) { return {' '}; }

  int file_size = Brain.SDcard.size(file_name.c_str());
  std::vector<char> buffer(file_size);
  Brain.SDcard.loadfile(file_name.c_str(), reinterpret_cast<uint8_t*>(buffer.data()), file_size);
  return buffer;
}

std::vector<std::string> get_SD_file_txt(const std::string& file_name) {
  if (!Brain.SDcard.isInserted()) { return {""}; }

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

void remove_duplicates_SD_file(const std::string& file_name, const std::string& duplicate_word) {
  if (!Brain.SDcard.isInserted()) { return; }

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


void wipe_SD_file(const std::string& file_name) {
  if (!Brain.SDcard.isInserted()) { return; }
  Brain.SDcard.savefile(file_name.c_str(), nullptr, 0);
}

void write_to_SD_file(const std::string& file_name, const std::string& data) {
  if (!Brain.SDcard.isInserted()) { return; }
  std::string output = "";
  output += ("\n" + data);
  std::vector<uint8_t> name_buffer(output.begin(), output.end());
  Brain.SDcard.appendfile(file_name.c_str(), name_buffer.data(), name_buffer.size());
}

void print(float num) {
    printf("%f\n", num);
    fflush(stdout);
}
void print(std::string str) {
    printf("%s\n", str.c_str());
    fflush(stdout);
}
void print(const char* str) {
    printf("%s\n", str);
    fflush(stdout);
}
void print(int num) {
    printf("%d\n", num);
    fflush(stdout);
}
void print(bool boolean) {
    printf("%d\n", boolean);
    fflush(stdout);
}
void print(double num) {
    printf("%f\n", num);
    fflush(stdout);
}
void print(long num) {
    printf("%ld\n", num);
    fflush(stdout);
}
void print(long long num) {
    printf("%lld\n", num);
    fflush(stdout);
}
void print(unsigned long long num) {
    printf("%llu\n", num);
    fflush(stdout);
}
void print(unsigned int num) {
    printf("%u\n", num);
    fflush(stdout);
}
void print(char c) {
    printf("%c\n", c);
    fflush(stdout);
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