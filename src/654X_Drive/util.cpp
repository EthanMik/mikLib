#include "vex.h"

float clamp(float input, float min, float max) {
    if (input > max) {
        return max;
    }
    if (input < min) {
        return min;
    }
    return input;
}

float deadband(float input, float width){
  if (fabs(input) < width){
    return(0);
  }
  return(input);
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

void to_normalized_vector(std::vector<float> vector){
  float length = sqrt(vector[0] * vector[0] + vector[1] * vector[1]);
  vector[0] /= length;
  vector[1] /= length;
}

std::vector<float> to_normalized_vector(float angle) {
  float radians = to_rad(angle);
  float x = cosf(radians);
  float y = sinf(radians);
  std::vector<float> coordinates {x, y};
  return(coordinates);
}
//√( (x2 - x1)^2 + (y2 - y1)^2 + (z2 - z1)^2 )
float get_vector_distance(std::vector<float> v1, std::vector<float> v2) {
  return sqrt(pow(v2[0] - v1[0], 2) + pow(v2[1] - v1[1], 2));
}

float reduce_negative_180_to_180(float angle) {
  while(!(angle >= -180 && angle < 180)) {
    if(angle < -180) { 
      angle += 360; 
    }
    if(angle >= 180) { 
      angle -= 360; 
    }
  }
  return(angle);
}

float reduce_negative_90_to_90(float angle) {
  while(!(angle >= -90 && angle < 90)) {
    if( angle < -90 ) { angle += 180; }
    if(angle >= 90) { angle -= 180; }
  }
  return(angle);
}

float reduce_0_to_360(float angle) {
  while(!(angle >= 0 && angle < 360)) {
    if(angle < 0) { 
      angle += 360; 
    }
    if(angle >= 360) { 
      angle -= 360;
    }
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
