#include "vex.h"

manual_drive::manual_drive(hzn::motor_group LB_motors, int LB_encoder_port, hzn::motor intake_motor, int ring_color_sensor_port, int ring_distance_sensor_port, int mogo_clamp_piston_port, int doinker_piston_port) :
  LB_motors(LB_motors),
  LB_encoder(LB_encoder_port),
  intake_motor(intake_motor.mtr),
  ring_color_sensor(ring_color_sensor_port),
  ring_distance_sensor(ring_color_sensor_port),
  mogo_clamp_piston(Brain.ThreeWirePort.Port[mogo_clamp_piston_port]),
  doinker_piston(Brain.ThreeWirePort.Port[doinker_piston_port])
{};

void manual_drive::intake() {
  while (true) {
    if (Controller.ButtonR2.pressing()) {
      intake_motor.spin(fwd, 12, volt);
    }
    else if (Controller.ButtonR1.pressing()) {
      intake_motor.spin(fwd, -12, volt);
    }
    else {
      intake_motor.stop();
    }
    // ring_sort();
    vex::task::sleep(20);
  }
  // bool pressed = false;
  // bool holding = false;

  // while (true) {
  //   float start_time = Brain.timer(sec);

  //   if (Controller.ButtonR1.pressing()) {
  //     pressed = !pressed;

  //     if (pressed) {
  //       intake_motor.spin(fwd, 10, volt);
  //     }
  //     if (!pressed) {
  //       intake_motor.stop();
  //     }     

  //     while (Controller.ButtonR1.pressing()) {
  //       if (Brain.timer(sec) - start_time > 0.3) { 
  //         holding = true;
  //         intake_motor.spin(fwd, 10, volt);
  //       }
  //       task::sleep(20);
  //     }
  //   }
  //   else if (holding) {
  //     holding = false;
  //     intake_motor.stop();
  //   }
  //   task::sleep(20);
  // }
}

void manual_drive::ring_sort() {
  ring_color_sensor.setLightPower(25, pct);
  if (ring_distance_sensor.objectDistance(mm) < 2) {
    if (ring_color_sensor.color() == vex::color::red) {
      task::sleep(200);
      intake_motor.stop(brake);
      task::sleep(500);  
    }
    task::sleep(20);  
  }
}

void manual_drive::lady_brown() {
  bool is_active = false;
  bool is_scoring = false;
  while (true) {
    if (Controller.ButtonX.pressing()) {
      is_active = !is_active;
    }
    else if (Controller.ButtonUp.pressing()) {
      is_scoring = !is_scoring;
    }

    while (Controller.ButtonLeft.pressing()) {
      LB_motors.spin(fwd, 0.5, velocity_units::volt);
    }

    while (Controller.ButtonRight.pressing()) {
      LB_motors.spin(fwd, -0.5, velocity_units::volt);
    }

    if (is_scoring && is_active) {
      state = set_LB_state(LB_state::SCORING);
    }
    else if (is_active && !is_scoring) {
      is_scoring = false;
      state = set_LB_state(LB_state::ACTIVE);
    }
    else if (!is_active && !is_scoring) {
      is_scoring = false;
      state = set_LB_state(LB_state::INACTIVE);
    }
    else if (!is_active && is_scoring) {
      is_scoring = false;
      state = set_LB_state(LB_state::INACTIVE);
    }
    Controller.Screen.setCursor(1, 8);
    Controller.Screen.print(state.c_str());
    task::sleep(20);
  }
}

std::string manual_drive::set_LB_state(LB_state state) {
  switch (state) {
    case LB_state::ACTIVE:
      move_LB_to_angle(static_cast<int>(state));
      return "ACTIVE  ";
    case LB_state::INACTIVE:
      move_LB_to_angle(static_cast<int>(state));
      return "INACTIVE";
    case LB_state::SCORING:
      move_LB_to_angle(static_cast<int>(state));
      return "SCORING ";
  }
}

void manual_drive::set_LB_constants(float LB_max_voltage, float LB_kp, float LB_ki, float LB_kd, float LB_starti, float LB_settle_error, float LB_settle_time, float LB_timeout) {
  this->LB_max_voltage = LB_max_voltage;
  this->LB_kp = LB_kp;
  this->LB_ki = LB_ki;
  this->LB_kd = LB_kd;
  this->LB_starti = LB_starti;
  this->LB_settle_error = LB_settle_error;
  this->LB_settle_time = LB_settle_time;
  this->LB_timeout = LB_timeout;
}

void manual_drive::move_LB_to_angle(float angle, bool buffer_data) {
  move_LB_to_angle(angle, LB_max_voltage, LB_settle_error, LB_settle_error, LB_timeout, LB_kp, LB_ki, LB_kd, LB_starti, buffer_data);
}

void manual_drive::move_LB_to_angle(float angle, float LB_max_voltage, float LB_settle_error, float LB_settle_time, float LB_timeout, float LB_kp, float LB_ki, float LB_kd, float LB_starti, bool buffer_data) {
  desired_angle = angle;
  PID turnPID(reduce_negative_180_to_180(angle - reduce_0_to_360(LB_encoder.angle())), LB_kp, LB_ki, LB_kd, LB_starti, LB_settle_error, LB_settle_time, LB_timeout);
  
  while(turnPID.is_settled() == false) {
    float error = reduce_negative_180_to_180(angle - reduce_0_to_360(LB_encoder.angle()));
    float output = turnPID.compute(error);

    output = clamp(output, -LB_max_voltage, LB_max_voltage);

    if (buffer_data) {
      add_to_graph_buffer({angle, (output / LB_max_voltage) * 100, reduce_0_to_360(LB_encoder.angle())});
    }

    LB_motors.spin(fwd, output, velocity_units::volt);
    task::sleep(10); 
  }

  LB_motors.stop(brake);
}

void manual_drive::mogo_clamp() {
  bool clamping = false;
  while (true) {
    if (Controller.ButtonL1.pressing() || Controller.ButtonL2.pressing()) {
      clamping = !clamping;
      mogo_clamp_piston.set(clamping);
      vex::task::sleep(500);
    }
    vex::task::sleep(20);
  }
}

void manual_drive::doinker() {
  bool extended = false;
  while (true) {
    if (Controller.ButtonY.pressing()) {
      extended = !extended;
      doinker_piston.set(extended);
      vex::task::sleep(500);
    }
    vex::task::sleep(20);
  }
}

void manual_drive::flip_direction() {
  bool reversed = false;
  while (true) {
    if (Controller.ButtonB.pressing()) {
      reversed = !reversed;
      chassis.is_reversed = reversed; 
      task::sleep(500);
    }
  }
}

void manual_drive::user_control_tasks() {
  _intake_task = task(intake_task);
  _split_arcade_task = task(split_arcade_task);
  _lady_brown_task = task(lady_brown_task);
  _mogo_clamp_task = task(mogo_clamp_task);
  _doinker_task = task(_doinker_task);
  _flip_direction_task = task(flip_direction_task);
}

int manual_drive::split_arcade_task(void) {
  chassis.split_arcade();
  return 0;
}

int manual_drive::intake_task(void) {
  assembly.intake();
  return 0;
}

int manual_drive::lady_brown_task(void) {
  assembly.lady_brown();
  return 0;
}

int manual_drive::mogo_clamp_task(void) {
  assembly.mogo_clamp();
  return 0;
}

int manual_drive::doinker_task(void) {
  assembly.doinker();
  return 0;
}

int manual_drive::flip_direction_task(void) {
  assembly.flip_direction();
  return 0;
}