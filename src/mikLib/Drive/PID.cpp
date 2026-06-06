#include "mikLib/drive.h"

PID::PID() {};

PID::PID(float kp, float ki, float kd) :
    kp(kp),
    ki(ki),
    kd(kd)
{};

PID::PID(float kp, float ki, float kd, float starti) :
    kp(kp),
    ki(ki),
    kd(kd),
    starti(starti)
{};

PID::PID(float kp, float ki, float kd, float starti, float settle_error, float settle_time, float exit_error, float timeout, float stall_timeout) :
    kp(kp),
    ki(ki),
    kd(kd),
    starti(starti),
    settle_error(settle_error),
    settle_time(settle_time),
    exit_error(exit_error),
    timeout(timeout),
    stall_timeout(stall_timeout)
{};

float PID::compute(float error) {
    if (fabs(error) < starti){
        accumulated_error += error;
    }
    if (sign(error) != sign(previous_error)) { 
        accumulated_error = 0; 
    }

    float derivative = error - previous_error;
    output = kp * error + ki * accumulated_error + kd * (derivative);

    previous_error = error;

    if(fabs(error) < settle_error) {
        time_spent_settled += 10;
    } else {
        time_spent_settled = 0;
    }

    if (fabs(error) < exit_error && exit_error != 0) {
        exiting = true;
    }

    if (fabs(derivative) < 0.05) {
        time_spent_stalled += 10;
    } else {
        time_spent_stalled = 0;
    }

    time_spent_running += 10;

    return output;
}

bool PID::is_settled(){
    if (time_spent_stalled > stall_timeout && stall_timeout != 0 && timeout != 0) {
        return true;
    }
    if (time_spent_running > timeout && timeout != 0) {
        return true;
    }
    if (time_spent_settled > settle_time) {
        return true;
    }
    if (exiting) {
        exiting = false;
        return true;
    }
    return false;
}

