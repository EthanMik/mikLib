#include "654-Template/motor_chain.h"
#include "654-Template/manual_drive.h"
#include "654-Template/auton_drive.h"
#include "robot-config.h"
#include "vex.h"

#include <vector>
#include <type_traits>

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

float to_rad(float angle_deg){
  return(angle_deg / (180.0 / M_PI));
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
