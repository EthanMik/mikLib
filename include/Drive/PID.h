#pragma once

#include "vex.h"

class PID {
public:
    PID();

    /**
     * @brief PID constructor with P, I, D.
     * 
     * @param kp Proportional constant.
     * @param ki Integral constant.
     * @param kd Derivative constant.
     */
    PID(float kp, float ki, float kd);

    /**
     * @brief PID constructor with P, I, D, and starti.
     * Starti keeps the I term at 0 until error is less than starti.
     * 
     * @param error Difference in desired and current position.
     * @param kp Proportional constant.
     * @param ki Integral constant.
     * @param kd Derivative constant.
     * @param starti Maximum error to start integrating.
     */
    PID(float error, float kp, float ki, float kd, float starti);

    /**
     * @brief PID constructor with settling inputs.
     * The settling system works like this: The robot is settled
     * when error is less than settle_error for a duration of settle_time,
     * or if the function has gone on for longer than timeout. Otherwise
     * it is not settled. Starti keeps the I term at 0 until error is less 
     * than starti.
     * 
     * @param error Difference in desired and current position.
     * @param kp Proportional constant.
     * @param ki Integral constant.
     * @param kd Derivative constant.
     * @param starti Maximum error to start integrating.
     * @param settle_error Maximum error to be considered settled.
     * @param settle_time Minimum time to be considered settled.
     * @param timeout Time after which to give up and move on. Using 0 will not time out movement.
     */
    PID(float error, float kp, float ki, float kd, float starti, float settle_error, float settle_time, float timeout);

    /**
     * @brief Computes the output power based on the error.
     * Typical PID calculation with some optimizations: When the robot crosses
     * error=0, the i-term gets reset to 0. And, of course, the robot only
     * accumulates i-term when error is less than starti.
     * 
     * @param error Difference in desired and current position.
     * @return Output power.
     */
    float compute(float error);

    /**
     * @brief Computes whether or not the movement has settled.
     * The robot is considered settled when error is less than settle_error 
     * for a duration of settle_time, or if the function has gone on for 
     * longer than timeout. Otherwise it is not settled.
     * 
     * @return Whether the movement is settled.
     */
    bool is_settled();

    float error = 0;
    float kp = 0;
    float ki = 0;
    float kd = 0;
    float starti = 0;
    float settle_error = 0;
    float settle_time = 0;
    float timeout = 0;
    float accumulated_error = 0;
    float previous_error = 0;
    float output = 0;
    float time_spent_settled = 0;
    float time_spent_running = 0;
};