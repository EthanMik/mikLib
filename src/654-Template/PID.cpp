#include "654-Template/motor_chain.h"
#include "654-Template/manual_drive.h"
#include "654-Template/auton_drive.h"
#include "654-Template/PID.h"
#include "robot-config.h"
#include "vex.h"

PID::PID(float error, float kp, float ki, float kd, float starti) :
  error(error),
  kp(kp),
  ki(ki),
  kd(kd),
  starti(starti)
{
  matrix = std::vector<std::vector<float>>(1, std::vector<float>(4, 0));
};

PID::PID(float error, float kp, float ki, float kd, float starti, float settle_error, float settle_time, float timeout) :
  error(error),
  kp(kp),
  ki(ki),
  kd(kd),
  starti(starti),
  settle_error(settle_error),
  settle_time(settle_time),
  timeout(timeout)
{
  matrix = std::vector<std::vector<float>>(1, std::vector<float>(4, 0));
};

float PID::compute(float error) {
  if (fabs(error) < starti){
    accumulated_error += error;
  }
  if ((error > 0 && previous_error < 0) || (error < 0 && previous_error > 0)) { 
    accumulated_error = 0; 
  }

  p = kp * error;
  i = ki * accumulated_error;
  d = kd * (error-previous_error);

  output = p + i + d;

  track_PID(p, i, d, output);

  previous_error = error;

  if(fabs(error) < settle_error) {
    time_spent_settled += 10;
  } else {
    time_spent_settled = 0;
  }

  time_spent_running += 10;

  return output;
}

bool PID::is_settled(){
  if (time_spent_running > timeout && timeout != 0) {
    return(true);
  }
  if (time_spent_settled > settle_time) {
    return(true);
  }
  return(false);
}

std::vector<std::vector<float>> PID::track_PID(float data1, float data2, float data3, float data4) {
    matrix.push_back({data1, data2, data3, data4});
    
    return matrix;
}
