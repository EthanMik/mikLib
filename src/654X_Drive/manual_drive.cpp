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

void manual_drive::LB_intake() {
  ring_color_sensor.setLightPower(100, vex::pct);
  intake_motor.setVelocity(100, vex::pct);

  while (true) {
    intake();
    lady_brown();
    vex::task::sleep(20);
  }
}

void manual_drive::intake() {
  if (Controller.ButtonR2.pressing()) {
    intake_motor.spin(vex::fwd, 12, vex::volt);
    // ring_sort();
  }
  else if (Controller.ButtonR1.pressing()) {
    intake_motor.spin(vex::fwd, -12, vex::volt);
  }
  else if (!intake_override) {
    intake_motor.stop(vex::brake);
  }
}

void manual_drive::ring_sort() {
    if (ring_color_sensor.color() == vex::color::blue && !ring_detected) {
      vex::task::sleep(100);
      intake_override = true;
      intake_motor.spinFor(-800, vex::rotationUnits::deg, true);
      intake_override = false;
    }
}

void manual_drive::lady_brown() {
    if (Controller.ButtonX.pressing()) {
      is_active = !is_active;
    }
    
    if (Controller.ButtonUp.pressing()) {
      is_scoring = !is_scoring;
    }

    while (Controller.ButtonLeft.pressing()) {
      LB_motors.spin(vex::fwd, 12, velocity_units::volt);
      is_scoring = false;
      is_active = false;
      prev_state = INACTIVE;
    }
    while (Controller.ButtonRight.pressing()) {
      LB_motors.spin(vex::fwd, -12, velocity_units::volt);
      is_scoring = false;
      is_active = false;
      prev_state = INACTIVE;
    }
    LB_motors.stop();

    if (is_scoring && is_active) {
      if (prev_state != LB_state::SCORING) {
        intake_override = true;
        intake_motor.spinFor(-30, vex::rotationUnits::deg, true);
        intake_override = false;
      }
      state = set_LB_state(SCORING);
      prev_state = SCORING;
    }
    else if (is_active && !is_scoring) {
      if (prev_state != ACTIVE) {
        is_scoring = false;
        state = set_LB_state(ACTIVE);
        prev_state = ACTIVE;
      }
    }
    else if (!is_active && !is_scoring) {
      if (prev_state != INACTIVE) {
        is_scoring = false;
        state = set_LB_state(INACTIVE);
        prev_state = INACTIVE;
      }
    }
    else if (!is_active && is_scoring) {
      if (prev_state != INACTIVE) {
        is_scoring = false;
        state = set_LB_state(INACTIVE);
        prev_state = INACTIVE;
      }
    }
    Controller.Screen.setCursor(1, 8);
    Controller.Screen.print(state.c_str());
}

std::string manual_drive::set_LB_state(LB_state state) {
  switch (state) {
    case LB_state::ACTIVE:
      move_LB_to_angle(state);
      return "ACTIVE  ";
    case LB_state::INACTIVE:
      move_LB_to_angle(state);
      return "INACTIVE";
    case LB_state::SCORING:
      move_LB_to_angle(state);
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
    if (angle == INACTIVE && Controller.ButtonX.pressing() && turnPID.time_spent_running > 200) {
      is_active = true;
      is_scoring = false;
      break;
    }

    float error = reduce_negative_180_to_180(angle - reduce_0_to_360(LB_encoder.angle()));
    float output = turnPID.compute(error);

    output = clamp(output, -LB_max_voltage, LB_max_voltage);

    if (buffer_data) {
      add_to_graph_buffer({angle, (output / LB_max_voltage) * 100, reduce_0_to_360(LB_encoder.angle())});
    }

    LB_motors.spin(vex::fwd, output, velocity_units::volt);
    vex::task::sleep(10); 
  }

  LB_motors.stop(vex::brake);
}

void manual_drive::mogo_clamp() {
  bool clamping = false;
  while (true) {
    if (Controller.ButtonL1.pressing() || Controller.ButtonL2.pressing()) {
      clamping = !clamping;
      if (clamping) {
        Controller.rumble(("."));
      }
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
      vex::task::sleep(500);
    }
  }
}

void manual_drive::match_timer() {
  int start_time = Brain.Timer.time(vex::timeUnits::sec);

  while (true) {
    int time_elapsed = Brain.Timer.time(vex::timeUnits::sec) - start_time; 
    int time_remaining = 105 - time_elapsed;
    switch (time_remaining)
    {
    case 52:
      Controller.rumble((".-"));
    case 20:
      Controller.rumble(("."));
      break;
    case 15:
      Controller.rumble((".-"));
    case 5:
      Controller.rumble(("."));
      break;
    default:
      break;
    }
    vex::task::sleep(50);
  }
}

void manual_drive::user_control_tasks() {
  _LB_intake_task = vex::task(LB_intake_task);
  _split_arcade_task = vex::task(split_arcade_task);
  _mogo_clamp_task = vex::task(mogo_clamp_task);
  _doinker_task = vex::task(doinker_task);
  _flip_direction_task = vex::task(flip_direction_task);
  _match_timer_task = vex::task(match_timer_task);
}

int manual_drive::LB_intake_task(void) {
  assembly.LB_intake();
  return 0;
}

int manual_drive::split_arcade_task(void) {
  chassis.split_arcade();
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

int manual_drive::match_timer_task(void) {
  assembly.match_timer();
  return 0;
}