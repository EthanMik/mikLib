#include "vex.h"

PID::PID(float error, float kp, float ki, float kd, float starti) :
  error(error),
  kp(kp),
  ki(ki),
  kd(kd),
  starti(starti)
{
  pid_data = std::vector<std::vector<float>>(1, std::vector<float>(4, 0));
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
  pid_data = std::vector<std::vector<float>>(1, std::vector<float>(4, 0));
};

float PID::compute(float error, bool is_tracking) {
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

  if (is_tracking) {
    track_PID(p, i, d, output);
  }

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
    pid_data.push_back({data1, data2, data3, data4});
    
    return pid_data;
}

void PID::print_PID() const {
  for (const auto &row : pid_data) {
          printf("%f,%f,%f, %f\n", row[0],  row[1], row[2], row[3]);
          fflush(stdout);
          wait(100, msec);
      }
  }
