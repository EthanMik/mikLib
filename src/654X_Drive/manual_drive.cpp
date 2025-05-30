#include "vex.h"

using namespace vex;

manual_drive::manual_drive(hzn::motor_group LB_motors, int LB_encoder_port, hzn::motor intake_motor, int intake_encoder_port, int ring_color_sensor_port, int ring_distance_sensor_port, int mogo_clamp_piston_port, int doinker_piston_port, int rush_piston_port, int lift_piston_port) :
  LB_motors(LB_motors),
  LB_encoder(LB_encoder_port),
  intake_motor(intake_motor.mtr),
  intake_encoder(intake_encoder_port),
  ring_color_sensor(ring_color_sensor_port),
  ring_distance_sensor(ring_distance_sensor_port),
  mogo_clamp_piston(Brain.ThreeWirePort.Port[mogo_clamp_piston_port]),
  doinker_piston(Brain.ThreeWirePort.Port[doinker_piston_port]),
  rush_piston(Brain.ThreeWirePort.Port[rush_piston_port]),
  lift_piston(Brain.ThreeWirePort.Port[lift_piston_port])
{};

void manual_drive::init_LB() {
  assembly.LB_goto_state = INACTIVE;

  async_LB = vex::task([](){
    while (1) {
      if (!assembly.LB_override) {
        assembly.move_LB_to_angle(assembly.LB_goto_state);
      }
      if (assembly.LB_override) {
        assembly.lady_brown_manual();
        assembly.is_scoring = false;
        assembly.is_active = false;
      }
      vex::task::sleep(20);
    }

    return 0;
  });
}

void manual_drive::initialize_user_control() {
  start_time = Brain.Timer.time(vex::timeUnits::sec);
  assembly.lift_piston.set(false);
  assembly.doinker_piston.set(false);
  LB_move_task.stop();
  chassis.override_brake_type(vex::brakeType::undefined);  

  _unjam_intake_task.stop();
  unjam_intake_task();
}

void manual_drive::unjam_intake_task() {
  _unjam_intake_task = vex::task([](){
    while(1) {
      while (assembly.unjam_intake) {
        double start = assembly.intake_motor.position(deg);
        vex::task::sleep(100);
        double end = assembly.intake_motor.position(deg);
  
        if (end - start < 1) {
          assembly.is_reversing = true;
          assembly.intake_motor.spinFor(directionType::rev, 100, rotationUnits::deg, 600, velocityUnits::rpm, true);
          assembly.is_reversing = false;
          assembly.intake_motor.spin(fwd, 12, volt);
        }
        vex::this_thread::sleep_for(50);
      }
      vex::this_thread::sleep_for(100);
    }
    return 0;
  });
}

void manual_drive::intake() {
  if (Controller.ButtonL2.pressing() && Controller.ButtonR2.pressing()) {
    assembly.unjam_intake = true;
    assembly.is_intaking_ring_halfway = true;

    vex::task intake_ring_halfway_task([](){
      assembly.intake_override = true;
      int timeout_start = Brain.Timer.time(vex::timeUnits::sec);
      while (1) {
          assembly.intake_motor.spin(fwd, 12, volt);
          if (assembly.ring_distance_sensor.objectDistance(mm) < 50) {
            assembly.intake_motor.stop(brake);
            assembly.intake_override = false;
            assembly.is_intaking_ring_halfway = true;
            break;
          }
          if (Brain.Timer.time(vex::timeUnits::sec) - timeout_start > 5) {
            assembly.intake_override = false;
            assembly.is_intaking_ring_halfway = true;
            break;
          }
          
          if (Brain.Timer.time(vex::timeUnits::sec) - timeout_start > 1 && (Controller.ButtonL2.pressing() || Controller.ButtonR2.pressing())) {
            assembly.intake_override = false;
            assembly.is_intaking_ring_halfway = true;
            break;
          }
          vex::this_thread::sleep_for(50);
          
      }
      return 0;
    });
  }

  if (Controller.ButtonR2.pressing()) {
    if (LB_goto_state != ACTIVE) {
      unjam_intake = true;
    }
    
    if (!is_reversing) {
      intake_motor.spin(vex::fwd, 12, vex::volt);
    }

    if (is_sorting) {
      ring_sort();
    }    
  }
  else if (Controller.ButtonL2.pressing()) {
    unjam_intake = false;
    intake_motor.spin(vex::fwd, -6, vex::volt);
  }
  else if (!intake_override) {
    unjam_intake = false;
    intake_motor.stop(vex::brake);
  } else if (!is_intaking_ring_halfway) {
    unjam_intake = false;
  }
}

void manual_drive::select_ring_sort_mode(color_sort opposing_color) {
    switch (opposing_color)
    {
    case color_sort::NONE:
      is_sorting = false;
      opposing_color = color_sort::NONE;
      Controller.Screen.setCursor(1, 1);
      Controller.Screen.print("SORTING: NONE");
      break;
    case color_sort::RED:
      is_sorting = true;
      opposing_color = color_sort::RED;
      this->color_min = 0;
      this->color_max = 35;
      Controller.Screen.setCursor(1, 1);
      Controller.Screen.print("SORTING: RED ");
      break;
    case color_sort::BLUE:
      is_sorting = true;
      opposing_color = color_sort::BLUE;
      this->color_min = 180;
      this->color_max = 310;
      Controller.Screen.setCursor(1, 1);
      Controller.Screen.print("SORTING: BLUE");
    }
}

void manual_drive::select_ring_sort_mode() {
  if (Controller.ButtonLeft.pressing() && std::abs(Brain.Timer.time(msec) - color_swap_cooldown) > 500) {
    color_sort_mode++;
    if (color_sort_mode > 2) {
      color_sort_mode = 0;
    }
    color_swap_cooldown = Brain.Timer.time(msec);

    switch (color_sort_mode)
    {
      case 0:
      select_ring_sort_mode(color_sort::NONE);
      break;
    case 1:
      select_ring_sort_mode(color_sort::RED);
      break;
    case 2:
      select_ring_sort_mode(color_sort::BLUE);
      break;
    default:
      break;
    }
  }
}

bool manual_drive::ring_sort() {
  if (ring_distance_sensor.objectDistance(mm) < 50) {
    ring_distance_close = true;
    distance_start = intake_motor.position(vex::rotationUnits::deg);
  }

  if (ring_distance_close && std::abs(intake_motor.position(vex::rotationUnits::deg) - distance_start) > 500) {
    ring_distance_close = false;
  }

  if (ring_color_sensor.hue() < color_max && ring_color_sensor.hue() > color_min && !ring_detected) {
    ring_detected = true;

    current_position = std::fmod(intake_motor.position(vex::rotationUnits::deg), full_rotation);
    if (current_position < 0) {
        current_position += full_rotation;
    }
    
    int min = current_position - hook_positions[0];
    target_position = hook_positions[0];
    for (size_t i = 0; i < hook_positions.size(); ++i) {
      int pos = current_position - hook_positions[i];
      if (pos < min && pos > 0) {
        target_position = hook_positions[i];
      }
    }
  }
  
  if (ring_detected) {
    unjam_intake = false;
    float angle = std::fmod(intake_motor.position(deg), full_rotation);

    if(angle < 0) {
      angle += full_rotation;
    }

    float error = target_position - angle;

    if (std::abs(error) < 5 || error < 0) {
      float start = intake_motor.position(deg);
      assembly.intake_motor.spinFor(directionType::rev, 40, rotationUnits::deg, 600, velocityUnits::rpm, true);

      ring_detected = false;
      ring_distance_close = false;
      assembly.intake_motor.stop(brake);
      assembly.intake_motor.stop(coast);
      unjam_intake = true;
      assembly.intake_motor.spin(fwd, 12, volt);
      return true;
    }
  }
  return false;
}

void manual_drive::lady_brown_manual() {
   if (Controller.ButtonL1.pressing()) {
      LB_motors.spin(vex::fwd, 12, velocity_units::volt);
    } else if (Controller.ButtonR1.pressing()) {
      LB_motors.spin(vex::fwd, -12, velocity_units::volt);
    } else {
      LB_motors.stop();
    }
}

void manual_drive::LB_state_manager(int state) {
  switch (state)
  {
  case ACTIVE:
    LB_goto_state = ACTIVE;
    break;
  case INACTIVE:
    LB_goto_state = INACTIVE;
    break;
  case HOLDING:
    LB_goto_state = HOLDING;
    break;
  case SCORING:
    if (prev_state != SCORING) {
      vex::task([](){
        assembly.intake_override = true;
        assembly.intake_motor.spinFor(-30, vex::rotationUnits::deg, true);
        assembly.intake_override = false;
        return 0;
      });
    }
    LB_goto_state = SCORING;
    break;
  case HANG:
    LB_goto_state = HANG;
    break;
  case DESCORE_TOP:
    LB_goto_state = DESCORE_TOP;
    break;
  case DECSCORE_BOTTOM:
    LB_goto_state = DECSCORE_BOTTOM;
    break;
  default:
    break;
  }

  prev_state = state;
  LB_reset_states();
} 

void manual_drive::LB_reset_states() {
  bool prev = LB_states[LB_prev_state].get();
  for (int i = 0; i < LB_states.size(); ++i) {
    LB_states[i].get() = false;
  }

  LB_states[LB_prev_state].get() = prev;
}

void manual_drive::lady_brown() {
    bool active_state = Controller.ButtonR1.pressing();
    bool scoring_state = Controller.ButtonL1.pressing();
    bool holding_state = Controller.ButtonB.pressing();
    bool hanging_state = Controller.ButtonDown.pressing();
    bool descoring_top_state = Controller.ButtonUp.pressing();
    bool descoring_bot_state = Controller.ButtonX.pressing();

    if (active_state && scoring_state && (Brain.Timer.time(vex::timeUnits::msec) - LB_override_cooldown > 500)) {
      Controller.rumble(".");
      LB_override_cooldown = Brain.Timer.time(vex::timeUnits::msec);
      LB_override = !LB_override;
    }

    if (active_state && !prev_active_state) {
      is_active = !is_active;
      LB_prev_state = 1;
      if (is_active && prev_state != ACTIVE) {
        LB_queued_state = ACTIVE;
      }
      if (!is_active || prev_state == ACTIVE) {
        LB_queued_state = INACTIVE;
        is_active = false;
      }
    }
    prev_active_state = active_state;
    
    if (scoring_state && !prev_scoring_state) {
      LB_prev_state = 0;
      is_scoring = !is_scoring;
      if (is_scoring) {
        LB_queued_state = SCORING;
      }
      if (!is_scoring) {
        LB_queued_state = ACTIVE;
      }
    }
    prev_scoring_state = scoring_state;

    if (holding_state && !prev_holding_state) {
      LB_prev_state = 2;
      is_holding = !is_holding;
      if (is_holding) {
        LB_queued_state = HOLDING;
      }
      if (!is_holding) {
        LB_queued_state = ACTIVE;
      }
    }
    prev_holding_state = holding_state;

    if (hanging_state && !prev_hanging_state) {
      LB_prev_state = 3;
      is_hanging = !is_hanging;
      if (is_hanging) {
        LB_queued_state = HANG;
      }
      if (!is_hanging) {
        LB_queued_state = ACTIVE;
      }
    }
    prev_hanging_state = hanging_state;

    if (descoring_top_state && !prev_descoring_top_state) {
      LB_prev_state = 4;
      is_descoring_top = !is_descoring_top;
      if (is_descoring_top) {
        LB_queued_state = DESCORE_TOP;
      }
      if (!is_descoring_top) {
        LB_queued_state = ACTIVE;
      }
    }
    prev_descoring_top_state = descoring_top_state;

    if (descoring_bot_state && !prev_descoring_bot_state) {
      LB_prev_state = 5;
      is_descoring_bot = !is_descoring_bot;

      if (is_descoring_bot) {
        LB_queued_state = DECSCORE_BOTTOM;
      }
      if (!is_descoring_bot) {
        LB_queued_state = ACTIVE;
      }
    }
    prev_descoring_bot_state = descoring_bot_state;

    LB_state_manager(LB_queued_state);
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
  float start_angle = reduce_0_to_360(LB_encoder.angle());
  PID turnPID(reduce_negative_180_to_180(angle - reduce_0_to_360(LB_encoder.angle())), LB_kp, LB_ki, LB_kd, LB_starti, LB_settle_error, LB_settle_time, LB_timeout);

  int state = assembly.LB_goto_state;

  while(turnPID.is_settled() == false) {
    float error = reduce_negative_180_to_180(angle - reduce_0_to_360(LB_encoder.angle()));
    if (start_angle > angle || angle > 300) {
      if (error > 0) {
        if (error < -25 || error > 25) {
          error = -error;
        }
      }
    }
    if (start_angle < angle && angle < 300 || start_angle > 300) {
      if (error < 0) {
        if (error < -25 || error > 25) {
          error = std::abs(error);
        }
      }
    }
    
    float output = turnPID.compute(error);
    
    output = clamp(output, -LB_max_voltage, LB_max_voltage);

    if (buffer_data) {
      // add_to_graph_buffer({angle, (output / LB_max_voltage) * 100, reduce_0_to_360(LB_encoder.angle())});
    }
    if (assembly.LB_goto_state != state) {
      break;
    }

    LB_motors.spin(vex::fwd, output, velocity_units::volt);
    vex::task::sleep(10); 
  }

  LB_motors.stop(vex::brake);
}

void manual_drive::mogo_clamp() {
  bool clamp_state = Controller.ButtonRight.pressing();

    if (clamp_state && !prev_clamp_state) {
      is_clamping = !is_clamping;
      mogo_clamp_piston.set(is_clamping);
    }

    prev_clamp_state = clamp_state;
}

void manual_drive::doinker() {
  bool doinker_state = Controller.ButtonUp.pressing();
  bool rush_state = Controller.ButtonY.pressing();
  bool lift_state = false;

  if (doinker_state && !prev_doinker_state) {
    is_extended_doinker = !is_extended_doinker;
    doinker_piston.set(is_extended_doinker);
  }
  if (rush_state && !prev_rush_state) {
    is_extended_rush = !is_extended_rush;
    rush_piston.set(is_extended_rush);
  }
  if (lift_state && !prev_lift_state) {
    is_extended_lift = !is_extended_lift;
    lift_piston.set(is_extended_lift);
  }

  prev_lift_state = lift_state;
  prev_rush_state = rush_state;
  prev_doinker_state = doinker_state;
}

void manual_drive::match_timer() {
    int time_elapsed = Brain.Timer.time(vex::timeUnits::sec) - start_time; 
    time_remaining = 60 - time_elapsed;
    
    switch (time_remaining)
    {
    case 30:
      Controller.rumble((".-"));
    case 15:
      Controller.rumble(("."));
      break;
    case 0:
      Controller.rumble((".-"));
    case -5:
      Controller.rumble(("."));
      chassis.stop_drive(vex::brake);
      exit(1);
      break;
    default:
      break;
  }
}

void manual_drive::align_robot() {
  bool align_state = Controller.ButtonA.pressing();


  if (align_state && !prev_align_state) {
    vex::task async_aligner([](){
      assembly.is_aligning = true;
      chassis.brake_is_overrided = false;
      chassis.drive_on_PID(-6.3);
      chassis.override_brake_type(vex::brakeType::undefined);
      vex::task::sleep(20);
      assembly.is_aligning = false;
      return 0;
    });
  }

  prev_align_state = align_state;

  if (std::abs(deadband(Controller.Axis1.position(), 5) || std::abs(deadband(Controller.Axis3.position(), 5)) > 0)) {
    assembly.is_aligning = false;
    async_aligner.stop();
  }

}