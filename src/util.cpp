#include "654-Template/motor_chain.h"
#include "654-Template/manual_drive.h"
#include "654-Template/auton_drive.h"
#include "robot-config.h"
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

float rpm_to_volt(float rpm, float maxRPM) {
    rpm = clamp(rpm, 0, maxRPM);
    return ((rpm / maxRPM) * 12.0);
}

float percent_to_volt(float percent) {
    return (percent * 12.0 / 100.0);
}

float normalize_to_volt(float normalized_percent) {
    return (normalized_percent * 12.0);
}

float volt_to_rpm(float volt, double maxRPM) {
    return (volt / 12.0) * maxRPM;
}

float volt_to_percent(float volt) {
    return (volt / 12.0) * 100.0;
}

float volt_to_normalized(float volt) {
    return volt / 12.0;
}