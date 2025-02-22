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

void manual_drive::initialize_user_control() {
  assembly.start_time = Brain.Timer.time(vex::timeUnits::sec);
  chassis.override_brake_type(vex::brakeType::undefined);
  LB_goto_state = INACTIVE;

  vex::task async_LB([](){
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

  vex::task unjam_intake_task([](){
    while(1) {
      while (assembly.unjam_intake) {
        double start = assembly.intake_encoder.position(deg);
        vex::task::sleep(100);
        double end = assembly.intake_encoder.position(deg);
  
        if (end - start < 1) {
          assembly.is_reversing = true;
          assembly.intake_motor.spinFor(directionType::rev, 100, rotationUnits::deg, 600, velocityUnits::rpm, true);
          assembly.is_reversing = false;
        }
        vex::this_thread::sleep_for(50);
      }
      vex::this_thread::sleep_for(100);
    }
    return 0;
  });

}

void manual_drive::intake() {
  if (Controller.ButtonDown.pressing()) {
    assembly.unjam_intake = true;
    assembly.is_intaking_ring_halfway = true;

    vex::task intake_ring_halfway_task([](){
      assembly.intake_override = true;
      int timeout_start = Brain.Timer.time(vex::timeUnits::sec);
      while (1) {
          assembly.intake_motor.spin(fwd, 12, volt);
          if (assembly.ring_distance_sensor.objectDistance(mm) < 50) {
            assembly.intake_motor.stop(brake);
            vex::this_thread::sleep_for(100);
            assembly.intake_override = false;
            assembly.is_intaking_ring_halfway = true;
            break;
          }
          if (Brain.Timer.time(vex::timeUnits::sec) - timeout_start > 5) {
            assembly.intake_override = false;
            assembly.is_intaking_ring_halfway = true;
            break;
          }
          if (Controller.ButtonL2.pressing() || Controller.ButtonR2.pressing()) {
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
    intake_motor.spin(vex::fwd, -12, vex::volt);
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
  if (ring_color_sensor.isNearObject() && ring_color_sensor.hue() < color_max && ring_color_sensor.hue() > color_min && !ring_detected) {
    ring_detected = true;

    current_position = std::fmod(intake_encoder.position(vex::rotationUnits::deg), full_rotation);
    if (current_position < 0) {
        current_position += full_rotation;
    }

    auto forward_distance = [&](double target, double current) {
        double diff = std::fmod((target - current + full_rotation), full_rotation);
        return diff;
    };

    double min_distance = full_rotation;
    for (const auto& target : hook_positions) {
        double distance = forward_distance(target, current_position);
        if (distance > 0 && distance < min_distance) {
            min_distance = distance;
            target_position = target;
        }
    }
  }

  if (ring_detected) {
    float angle = std::fmod(intake_encoder.position(deg), full_rotation);

    if(angle < 0) {
      angle += full_rotation;
    }

    float error = target_position - angle;

    if (std::abs(error) < 10 || error < 0) {
      float start = intake_encoder.position(deg);
      while (std::abs(intake_encoder.position(deg) - start) < 60) {
        assembly.intake_motor.spin(fwd, -12, volt);
        task::sleep(10);
      }
      ring_detected = false;
      assembly.intake_motor.stop(brake);
      assembly.intake_motor.stop(coast);
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

void manual_drive::lady_brown() {
    bool active_state = Controller.ButtonR1.pressing();
    bool scoring_state = Controller.ButtonL1.pressing();
    bool holding_state = Controller.ButtonB.pressing();

    if (active_state && !prev_active_state) {
      is_active = !is_active;

      if (is_holding) {
        is_holding = false;
      }
    }
    prev_active_state = active_state;
    
    if (scoring_state && !prev_scoring_state) {
      is_scoring = !is_scoring;

      if (is_holding) {
        is_holding = false;
      }
      if (prev_state == SCORING) {
        is_active = true;
      }
      // if (is_scoring && !is_active) {
      //   is_scoring = false;
      // }
    }
    prev_scoring_state = scoring_state;

    if (holding_state && !prev_holding_state && is_active) {
      is_holding = !is_holding;
    }
    prev_holding_state = holding_state;
    Brain.Screen.printAt(30, 30, "%d", is_holding);

    if (active_state && scoring_state && (Brain.Timer.time(vex::timeUnits::msec) - LB_override_cooldown > 500)) {
      Controller.rumble(".");
      LB_override_cooldown = Brain.Timer.time(vex::timeUnits::msec);
      LB_override = !LB_override;
    }

    if (is_scoring && !is_holding) {
      if (prev_state != SCORING) {
        intake_override = true;
        intake_motor.spinFor(-30, vex::rotationUnits::deg, true);
        intake_override = false;
      }
      LB_goto_state = SCORING;
      prev_state = SCORING;
    }
    else if (is_active && !is_scoring && !is_holding) {
      is_scoring = false;
      LB_goto_state = ACTIVE;
      
      if (prev_state == SCORING) {
        if (std::abs(LB_encoder.angle(deg) - ACTIVE) < 8) {
            intake_motor.spinFor(30, vex::rotationUnits::deg, true);
            prev_state = ACTIVE;
          }
        } else {
          prev_state = ACTIVE;
        }
      }
    else if (!is_active && !is_scoring && !is_holding) {
      is_scoring = false;
      LB_goto_state = INACTIVE;
      prev_state = INACTIVE;
    }
    else if (!is_active && is_scoring && !is_holding) {
      is_scoring = false;
      LB_goto_state = INACTIVE;
      prev_state = INACTIVE;
    } else if (is_holding && is_active && !is_scoring) {
      is_scoring = false;
      is_active = false;
      LB_goto_state = HOLDING;
      prev_state = HOLDING;
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

  int state = assembly.LB_goto_state;

  while(turnPID.is_settled() == false) {
    float error = reduce_negative_180_to_180(angle - reduce_0_to_360(LB_encoder.angle()));
    float output = turnPID.compute(error);

    output = clamp(output, -LB_max_voltage, LB_max_voltage);

    if (buffer_data) {
      add_to_graph_buffer({angle, (output / LB_max_voltage) * 100, reduce_0_to_360(LB_encoder.angle())});
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
  bool doinker_state = Controller.ButtonX.pressing();
  bool rush_state = Controller.ButtonY.pressing();
  // bool lift_state = Controller.ButtonUp.pressing();

  if (doinker_state && !prev_doinker_state) {
    is_extended_doinker = !is_extended_doinker;
    doinker_piston.set(is_extended_doinker);
  }
  if (rush_state && !prev_rush_state) {
    is_extended_rush = !is_extended_rush;
    rush_piston.set(is_extended_rush);
  }
  // if (lift_state) {
  //   lift_piston.set(false);
  // } else {
  //   lift_piston.set(true);
  // }

  prev_rush_state = rush_state;
  prev_doinker_state = doinker_state;
}

void manual_drive::match_timer() {
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
}

void manual_drive::align_robot() {
  bool align_state = Controller.ButtonA.pressing();


  if (align_state && !prev_align_state) {
    vex::task async_aligner([](){
      chassis.brake_is_overrided = false;
      chassis.drive_on_PID(2.5);
      chassis.override_brake_type(vex::brakeType::undefined);
      vex::task::sleep(20);
      return 0;
    });
  }

  prev_align_state = align_state;

  if (std::abs(deadband(Controller.Axis1.position(), 5) || std::abs(deadband(Controller.Axis3.position(), 5)) > 0)) {
    async_aligner.stop();
  }

}