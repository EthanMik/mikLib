#include "654-Template/motor_chain.h"
#include "654-Template/manual_drive.h"
#include "654-Template/auton_drive.h"
#include "robot-config.h"
#include "util.h"
#include "vex.h"

#include <vector>

class PID {
public:
    float error = 0;
    float kp = 0;
    float ki = 0;
    float kd = 0;
    float p = 0;
    float i = 0;
    float d = 0;
    float starti = 0;
    float settle_error = 0;
    float settle_time = 0;
    float timeout = 0;
    float accumulated_error = 0;
    float previous_error = 0;
    float output = 0;
    float time_spent_settled = 0;
    float time_spent_running = 0;

    PID(float error, float kp, float ki, float kd, float starti, float settle_error, float settle_time, float timeout);

    PID(float error, float kp, float ki, float kd, float starti);

    float compute(float error, bool is_tracking = false);

    bool is_settled();

    void print_PID() const;

private:
    std::vector<std::vector<float>> pid_data;

    std::vector<std::vector<float>> track_PID(float data1, float data2, float data3, float data4);

};