#include "654-Template/motor_chain.h"
#include "654-Template/manual_drive.h"
#include "654-Template/PID.h"
#include "robot-config.h"
#include "util.h"
#include "vex.h"

using namespace vex;

auton_drive::auton_drive(motor_chain leftDrive, motor_chain rightDrive):
    leftDrive(leftDrive),
    rightDrive(rightDrive)
{    
}

void auton_drive::turn_on_PID(float angle, float turn_max_voltage, float turn_settle_error, float turn_settle_time, float turn_timeout, float turn_kp, float turn_ki, float turn_kd, float turn_starti)
{
  PID turnPID(reduce_negative_180_to_180(angle - reduce_0_to_360(Inertial.rotation())), turn_kp, turn_ki, turn_kd, turn_starti, turn_settle_error, turn_settle_time, turn_timeout);
  
  while(turnPID.is_settled() == false)
  {
    float error = reduce_negative_180_to_180(angle - reduce_0_to_360(Inertial.rotation()));
    float output = turnPID.compute(error);

    output = clamp(output, -turn_max_voltage, turn_max_voltage);

    drive_with_voltage(output, -output);
    task::sleep(10); 
  }

  printMatrix(turnPID.matrix);

  leftDrive.stop(hold);
  rightDrive.stop(hold);
}

void auton_drive::drive_with_voltage(float leftVoltage, float rightVoltage){
  leftDrive.spin(fwd, leftVoltage, velocity_units::volt);
  rightDrive.spin(fwd, rightVoltage, velocity_units::volt);
}

void auton_drive::printMatrix(std::vector<std::vector<float>> matrix) const {
  for (const auto &row : matrix) {
          printf("%f,%f,%f, %f\n", row[0],  row[1], row[2], row[3]);
          fflush(stdout);
          wait(100, msec);
      }
  }


