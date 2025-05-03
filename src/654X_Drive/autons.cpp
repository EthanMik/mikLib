#include "vex.h"

using namespace vex;

void blue_ringside_winpoint(bool calibrate) { chassis.set_coordinates(100, 200, 180); }
void blue_ringside_sawp(bool calibrate) { print("blue_ringside_sawp"); }
void blue_ringside_elim(bool calibrate) { print("blue_ringside_elim"); }
void blue_goalside_winpoint(bool calibrate) { print("blue_goalside_winpoint"); }
void blue_goalside_sawp(bool calibrate) { print("blue_goalside_sawp"); }
void blue_goalside_elim(bool calibrate) { print("blue_goalside_elim"); }
void red_ringside_winpoint(bool calibrate) { print("red_ringside_winpoint"); }
void red_ringside_sawp(bool calibrate) { print("red_ringside_sawp"); }
void red_ringside_elim(bool calibrate) { print("red_ringside_elim"); }
void red_goalside_winpoint(bool calibrate) { print("red_goalside_winpoint"); }
void red_goalside_sawp(bool calibrate) { print("red_goalside_sawp"); }
void red_goalside_elim(bool calibrate) { print("red_goalside_elim"); }


void solo_win_point_red(bool set_pos) {
  if (set_pos) {
    chassis.set_coordinates(-55, 23.5, 270);
    return;
  }

  assembly.unjam_intake_task();
  stop_intake();
  color_sort_auton(color_sort::BLUE);

  float time = Brain.Timer.time(msec);
  assembly.LB_motors.stop(hold);
  assembly.LB_motors.spin(fwd, -12, velocity_units::volt);
  task::sleep(600);
  LB_task(INACTIVE);
  
  chassis.turn_to_point(-21.7, 24.3, true);
  chassis.drive_max_voltage = 6;
  chassis.drive_to_point(-21.7, 24.3);
  assembly.mogo_clamp_piston.set(true);
  default_constants();
  task::sleep(200);
  start_intake();
  chassis.turn_to_point(-23.588, 44.5);
  chassis.drive_to_point(-23.588, 44.5);
  chassis.turn_to_point(-46.156, 1.749);
  assembly.lift_piston.set(true);
  chassis.drive_to_point(-46.156, 1.749);
  start_intake(false);
  intake_ring_halfway();
  assembly.lift_piston.set(false);
  chassis.drive_on_PID(-8);
  assembly.mogo_clamp_piston.set(false);
  chassis.drive_max_voltage = 12;
  chassis.drive_on_PID(20);

  chassis.turn_to_point(-23.839, -23.327, true);
  chassis.drive_max_voltage = 6;
  chassis.drive_to_point(-23.839, -23.327);
  default_constants();
  assembly.mogo_clamp_piston.set(true);
  task::sleep(200);
  default_constants();
  chassis.turn_to_point(-23.588, -44.5);
  start_intake();
  chassis.drive_to_point(-23.588, -44.5);
  LB_task(SCORING);
  chassis.turn_to_point(-12.307, -24.108);
  chassis.drive_to_point(-12.507, -24.108);
  stop_intake();
  chassis.stop_drive(hold);

  Brain.Screen.printAt(30, 30, "%f", Brain.Timer.time(msec) - time);
}

void solo_win_point_blue(bool set_pos) {
  if (set_pos) {
    chassis.set_coordinates(55, 23.5, 90);
    return;
  }

  assembly.unjam_intake_task();
  stop_intake();
  color_sort_auton(color_sort::RED);

  float time = Brain.Timer.time(msec);
  assembly.LB_motors.stop(hold);
  assembly.LB_motors.spin(fwd, -12, velocity_units::volt);
  task::sleep(600);
  LB_task(INACTIVE);
  
  chassis.turn_to_point(-1.7, 24.3, true);
  chassis.drive_max_voltage = 6;
  chassis.drive_to_point(21.7, 24.3);
  assembly.mogo_clamp_piston.set(true);
  default_constants();
  task::sleep(200);
  start_intake();
  chassis.turn_to_point(23.588, 44.5);
  chassis.drive_to_point(23.588, 44.5);
  chassis.turn_to_point(46.156, 1.749);
  assembly.lift_piston.set(true);
  chassis.drive_to_point(46.156, 1.749);
  start_intake(false);
  intake_ring_halfway();
  assembly.lift_piston.set(false);
  chassis.drive_on_PID(-8);
  assembly.mogo_clamp_piston.set(false);
  chassis.drive_max_voltage = 12;
  chassis.drive_on_PID(20);

  chassis.turn_to_point(23.839, -23.327, true);
  chassis.drive_max_voltage = 6;
  chassis.drive_to_point(23.839, -23.327);
  default_constants();
  assembly.mogo_clamp_piston.set(true);
  task::sleep(200);
  default_constants();
  chassis.turn_to_point(23.588, -44.5);
  start_intake();
  chassis.drive_to_point(23.588, -44.5);
  LB_task(SCORING);
  chassis.turn_to_point(12.307, -24.108);
  chassis.drive_to_point(12.507, -24.108);
  stop_intake();
  chassis.stop_drive(hold);

  Brain.Screen.printAt(30, 30, "%f", Brain.Timer.time(msec) - time);
}

void goalside_red(bool set_pos) {
  if (set_pos) {
    chassis.set_coordinates(-55, -23.5, 270);
    return;
  }

  float time = Brain.Timer.time(msec);
  assembly.unjam_intake_task();
  stop_intake();
  color_sort_auton(color_sort::BLUE);
  chassis.turn_settle_error = 1.5;
  chassis.drive_max_voltage = 6;
  chassis.drive_on_PID(-31);
  assembly.mogo_clamp_piston.set(true);
  task::sleep(200);
  default_constants();
  
  
  chassis.turn_to_point(-44.5, -2);
  start_intake();
  assembly.lift_piston.set(true);
  chassis.drive_to_point(-44.5, -2);
  assembly.lift_piston.set(false);
  task::sleep(100);
  chassis.drive_on_PID(-15);
  chassis.turn_to_point(-22.812, -49.026);
  chassis.drive_to_point(-22.812, -49.026);
  chassis.turn_to_point(-58.23, -60.832);
  chassis.drive_to_point(-58.23, -60.832);
  chassis.turn_to_point(-67.635, -68.436);

  drive_until_settled(7, 7);
  chassis.drive_on_PID(-5.8);
  assembly.lift_piston.set(true);
  
  drive_until_settled(7, 7);
  assembly.lift_piston.set(false);
  chassis.drive_on_PID(-8);
  assembly.rush_piston.set(true);
  chassis.turn_max_voltage = 4;
  task::sleep(400);
  chassis.turn_on_PID(0);
  assembly.rush_piston.set(false);
  assembly.mogo_clamp_piston.set(false);
  chassis.turn_on_PID(45);
  stop_intake();
  chassis.drive_max_voltage = 12;
  chassis.drive_min_voltage = 2;
  chassis.drive_to_point(-16, -47);
  chassis.turn_max_voltage = 10;
  chassis.turn_on_PID(270);
  
  Brain.Screen.printAt(30, 30, "%f", Brain.Timer.time(msec) - time);
}

void goalside_blue(bool set_pos) {
  if (set_pos) {
    chassis.set_coordinates(55, -23.5, 90);
    return;
  }

  float time = Brain.Timer.time(msec);
  assembly.unjam_intake_task();
  stop_intake();
  color_sort_auton(color_sort::RED);
  chassis.turn_settle_error = 1.5;
  chassis.drive_max_voltage = 6;
  chassis.drive_on_PID(-31);
  assembly.mogo_clamp_piston.set(true);
  task::sleep(200);
  default_constants();
  
  chassis.turn_to_point(44.5, -2);
  start_intake();
  assembly.lift_piston.set(true);
  chassis.drive_to_point(44.5, -2);
  assembly.lift_piston.set(false);
  task::sleep(100);
  chassis.drive_on_PID(-15);
  chassis.turn_to_point(22.812, -49.026);
  chassis.drive_to_point(22.812, -49.026);
  chassis.turn_to_point(58.23, -60.832);
  chassis.drive_to_point(58.23, -60.832);
  chassis.turn_to_point(67.635, -68.436);

  drive_until_settled(7, 7);
  chassis.drive_on_PID(-5.8);
  assembly.lift_piston.set(true);
  
  drive_until_settled(7, 7);
  assembly.lift_piston.set(false);
  chassis.drive_on_PID(-8);
  assembly.doinker_piston.set(true);
  chassis.turn_max_voltage = 4;
  task::sleep(400);
  chassis.turn_on_PID(0);
  assembly.doinker_piston.set(false);
  assembly.mogo_clamp_piston.set(false);
  chassis.turn_on_PID(315);
  stop_intake();
  chassis.drive_max_voltage = 12;
  chassis.drive_min_voltage = 2;
  chassis.drive_to_point(16, -47);
  chassis.turn_max_voltage = 10;
  chassis.turn_on_PID(90);
  
  Brain.Screen.printAt(30, 30, "%f", Brain.Timer.time(msec) - time);
}

void ring_side_red(bool set_pos) {
  if (set_pos) {
    chassis.set_coordinates(-55, 23.5, 270);
    return;
  }

  assembly.unjam_intake_task();
  stop_intake();
  color_sort_auton(color_sort::BLUE);
  
  // thread odom(print_coordinates);
  float time = Brain.Timer.time(msec);
  assembly.LB_motors.spin(fwd, -12, velocity_units::volt);
  task::sleep(600);
  LB_task(INACTIVE);

  chassis.turn_to_point(-21.268, 24.397, true);
  chassis.drive_max_voltage = 6;
  chassis.drive_to_point(-21.268, 24.397);

  assembly.mogo_clamp_piston.set(true);
  task::sleep(200);
  default_constants();
  chassis.turn_to_point(-8, 39);
  start_intake();
  chassis.drive_to_point(-8, 39);
  
  chassis.right_swing_to_angle(0);
  
  chassis.drive_to_point(-8, 54);
  chassis.drive_to_point(-8, 39);

  chassis.turn_to_point(-22, 45);
  chassis.drive_to_point(-22, 45);

  chassis.turn_to_point(-62.035, 60.348);
  chassis.drive_to_point(-62.035, 60.348);

  chassis.turn_to_point(-18.902, 12.154, true);
  // chassis.drive_on_PID(5);
  drive_until_settled(8, 8);
  chassis.drive_on_PID(-10);
  
  chassis.turn_to_point(-47.083, 0.146);
  assembly.lift_piston.set(true);
  chassis.drive_to_point(-47.083, 0.146);
  assembly.lift_piston.set(false);
  chassis.drive_on_PID(-9);

  Brain.Screen.printAt(30, 30, "%f", Brain.Timer.time(msec) - time);

}

void ring_side_blue(bool set_pos) {
  if (set_pos) {
    chassis.set_coordinates(55, 23.5, 90);
    return;
  }

  assembly.unjam_intake_task();
  stop_intake();
  color_sort_auton(color_sort::RED);
  
  thread odom(print_coordinates);
  float time = Brain.Timer.time(msec);
  assembly.LB_motors.spin(fwd, -12, velocity_units::volt);
  task::sleep(600);
  LB_task(INACTIVE);

  chassis.turn_to_point(21.268, 24.397, true);
  chassis.drive_max_voltage = 6;
  chassis.drive_to_point(21.268, 24.397);

  assembly.mogo_clamp_piston.set(true);
  task::sleep(200);
  default_constants();
  chassis.turn_to_point(8, 39);
  start_intake();
  chassis.drive_to_point(8, 39);
  
  chassis.left_swing_to_angle(0);
  
  chassis.drive_to_point(8, 54);
  chassis.drive_to_point(8, 39);

  chassis.turn_to_point(22, 45);
  chassis.drive_to_point(22, 45);

  chassis.turn_to_point(62.035, 60.348);
  chassis.drive_to_point(62.035, 60.348);

  chassis.turn_to_point(18.902, 12.154, true);
  // chassis.drive_on_PID(5);
  drive_until_settled(8, 8);
  chassis.drive_on_PID(-10);
  
  chassis.turn_to_point(47.083, 0.146);
  assembly.lift_piston.set(true);
  chassis.drive_to_point(47.083, 0.146);
  assembly.lift_piston.set(false);
  chassis.drive_on_PID(-9);

  Brain.Screen.printAt(30, 30, "%f", Brain.Timer.time(msec) - time);

}

void win_point_red(bool set_pos) {
  if (set_pos) {
    chassis.set_coordinates(-55, 23.5, 270);
    return;
  }

  assembly.unjam_intake_task();
  stop_intake();
  color_sort_auton(color_sort::BLUE);
  
  float time = Brain.Timer.time(msec);
  assembly.LB_motors.spin(fwd, -12, velocity_units::volt);
  task::sleep(600);
  LB_task(INACTIVE);

  chassis.turn_to_point(-21.268, 24.397, true);
  chassis.drive_max_voltage = 6;
  chassis.drive_to_point(-21.268, 24.397);


  assembly.mogo_clamp_piston.set(true);
  task::sleep(200);
  default_constants();
  chassis.turn_to_point(-8, 39);
  start_intake();
  chassis.drive_to_point(-8, 39);
  
  chassis.right_swing_to_angle(0);
  
  chassis.drive_to_point(-8, 54);
  chassis.drive_to_point(-8, 39);

  chassis.turn_to_point(-22, 45);
  chassis.drive_to_point(-22, 45);

  chassis.turn_to_point(-62.035, 60.348);
  chassis.drive_to_point(-62.035, 60.348);

  chassis.turn_to_point(-18.902, 12.154, true);
  // chassis.drive_on_PID(5);
  drive_until_settled(8, 8);
  chassis.drive_on_PID(-10);
  
  chassis.turn_to_point(-19.4, 18.1);
  LB_task(SCORING);
  chassis.drive_to_point(-19.4, 18.1);
  chassis.stop_drive(hold);
  Brain.Screen.printAt(30, 30, "%f", Brain.Timer.time(msec) - time);
}

void win_point_blue(bool set_pos) {
  if (set_pos) {
    chassis.set_coordinates(55, 23.5, 90);
    return;
  }

  assembly.unjam_intake_task();
  stop_intake();
  color_sort_auton(color_sort::RED);
  
  float time = Brain.Timer.time(msec);
  assembly.LB_motors.spin(fwd, -12, velocity_units::volt);
  task::sleep(600);
  LB_task(INACTIVE);

  chassis.turn_to_point(21.268, 24.397, true);
  chassis.drive_max_voltage = 6;
  chassis.drive_to_point(21.268, 24.397);


  assembly.mogo_clamp_piston.set(true);
  task::sleep(200);
  default_constants();
  chassis.turn_to_point(8, 39);
  start_intake();
  chassis.drive_to_point(8, 39);
  
  chassis.left_swing_to_angle(0);
  
  chassis.drive_to_point(8, 54);
  chassis.drive_to_point(8, 39);

  chassis.turn_to_point(22, 45);
  chassis.drive_to_point(22, 45);

  chassis.turn_to_point(62.035, 60.348);
  chassis.drive_to_point(62.035, 60.348);

  chassis.turn_to_point(18.902, 12.154, true);
  // chassis.drive_on_PID(5);
  drive_until_settled(8, 8);
  chassis.drive_on_PID(-10);
  
  chassis.turn_to_point(19.4, 18.1);
  LB_task(SCORING);
  chassis.drive_to_point(19.4, 18.1);
  chassis.stop_drive(hold);
  Brain.Screen.printAt(30, 30, "%f", Brain.Timer.time(msec) - time);
}

void skills(void) {
  float time = Brain.Timer.time(msec);
  assembly.unjam_intake_task();
  
  chassis.set_coordinates(-61, 0, 90);
  
  assembly.intake_motor.spin(fwd, 12, volt);
  task::sleep(400);
  stop_intake();
  
  chassis.drive_to_point(-46.854, -0.135);
  
  chassis.turn_to_point(-47.577, -23.75, true);
  chassis.drive_max_voltage = 6;
  chassis.drive_to_point(-47.577, -23.75);
  default_constants();

  assembly.mogo_clamp_piston.set(true);
  task::sleep(200);
  
  chassis.turn_to_point(-26, -24);
  start_intake();
  chassis.drive_to_point(-26, -24);
  
  chassis.turn_to_point(22, -48);
  LB_task(ACTIVE);
  vex::task unjam_LB([](){
    while (1) {
      if (assembly.ring_distance_sensor.objectDistance(mm) < 50) {
        start_intake(false);
        break;
      }
    }
    return 0;
  });

  chassis.drive_to_point(22, -48);
  
  chassis.turn_to_point(-0.284, -43, true);
  chassis.drive_to_point(-0.284, -43);
  
  stop_intake();
  LB_task(HOLDING - 30);
  chassis.turn_to_point(-0.284, -62.694);
  start_intake(false);
  chassis.drive_to_point(-0.284, -62.694);
  
  drive_until_settled(2.5, 2.5);
  assembly.LB_motors.spin(fwd, -12, velocity_units::volt);
  task::sleep(400);
  LB_task(INACTIVE);

  chassis.turn_to_point(-0.474, -48.488, true);
  chassis.drive_to_point(-0.474, -48.488);
  
  chassis.turn_to_point(-60.516, -46.973);
  start_intake();
  chassis.drive_max_voltage = 6;
  chassis.drive_to_point(-60.516, -46.973);
  chassis.turn_to_point(-47.818, -57.727);
  chassis.drive_to_point(-47.818, -57.727);
  default_constants();
  
  chassis.turn_to_point(-58, -61, true);
  drive_until_settled(-6, -6);
  assembly.intake_motor.spin(fwd, -5, volt);
  assembly.mogo_clamp_piston.set(false);
  task::sleep(100);
  
  chassis.drive_on_PID(10);
  stop_intake();

  // chassis.set_coordinates(-47.5, 0, 0);

  chassis.turn_to_point(-47.336, 27.239, true);
  chassis.drive_max_voltage = 8;
  chassis.drive_to_point(-47.336, 14.564);
  chassis.drive_max_voltage = 4;
  chassis.drive_to_point(-47.336, 27.239);
  default_constants();
  assembly.mogo_clamp_piston.set(true);
  task::sleep(200);
  chassis.turn_settle_error = .25;
  chassis.turn_to_point(-23.721, 23.48);
  start_intake();
  chassis.drive_to_point(-23.721, 23.48);

  chassis.turn_to_point(0, 43);
  chassis.drive_to_point(0, 43);
  LB_task(ACTIVE);
  vex::task unjam_LB2([](){
    while (1) {
      if (assembly.ring_distance_sensor.objectDistance(mm) < 50) {
        start_intake(false);
        break;
      }
    }
    return 0;
  });
  

  chassis.turn_to_point(23.75, 46.854);
  chassis.drive_to_point(23.75, 46.854);
  
  chassis.turn_to_point(0, 43, true);
  stop_intake();
  chassis.drive_to_point(0, 43);
  LB_task(HOLDING - 30);

  chassis.turn_to_point(0, 62);
  start_intake();
  chassis.drive_to_point(0, 62);

  drive_until_settled(4, 4);
  distance_reset();
  chassis.turn_settle_error = 1;
  assembly.LB_motors.spin(fwd, -12, velocity_units::volt);
  task::sleep(400);
  LB_task(INACTIVE);

  chassis.turn_to_point(0, 48, true);
  chassis.drive_to_point(0, 48);
  chassis.drive_max_voltage = 6;
  chassis.turn_to_point(-60.348, 46.854);
  chassis.drive_to_point(-60.348, 46.854);
  default_constants();

  chassis.turn_to_point(-45.649, 60.589);
  chassis.drive_to_point(-45.649, 60.589);

  chassis.turn_to_point(-61.312, 62.276, true);
  drive_until_settled(-6, -6);
  assembly.mogo_clamp_piston.set(false);
  assembly.intake_motor.spin(fwd, -5, volt);
  task::sleep(200);
  chassis.drive_on_PID(10);
  stop_intake();

  chassis.turn_to_point(47.194, 46.912);

  // chassis.set_coordinates(23.5, 47, 90);
  start_intake(false);
  intake_ring_halfway();


  chassis.drive_to_point(47.194, 46.912);

  chassis.turn_to_point(47.762, -9, true);
  chassis.drive_to_point(47.762, -9);

  chassis.turn_to_point(47.573, -0.378);
  chassis.drive_to_point(47.573, -0.378);

  chassis.turn_to_point(62.03, 0, true);
  chassis.drive_to_point(62.03, 0);
  drive_until_settled(-1, -1);
  drive_until_settled(-10, -10);
  chassis.drive_on_PID(2.5);
  assembly.intake_motor.spin(fwd, 12, volt);
  task::sleep(500);
  stop_intake();
  assembly.intake_motor.stop(coast);
  assembly._unjam_intake_task.suspend();
  
  chassis.turn_to_point(54.572, 0);
  chassis.drive_to_point(54.572, 0);
  
  chassis.turn_to_point(61.382, 56.748);
  drive_until_settled(10, 10);
  chassis.drive_on_PID(-8);
  drive_until_settled(7, 7);
  chassis.drive_on_PID(-25);
  
  // chassis.turn_to_point(61.382, -61.748);
  // drive_until_settled(10, 10);
  // chassis.drive_on_PID(-8);
  // drive_until_settled(10, 10);
  // chassis.drive_on_PID(-15);

  // chassis.turn_to_point(13.153, -14.196, true);
  // LB_task(SCORING);
  // chassis.drive_to_point(13.153, -14.196);
  // chassis.drive_max_voltage = 8;
  
  chassis.turn_to_point(47, 30.95, true);
  chassis.drive_to_point(47, 30.95);
  
  chassis.turn_to_point(47, -26.642, true);
  chassis.drive_to_point(47, -14.352);
  
  chassis.turn_max_voltage = 4.5;
  chassis.drive_to_point(47, -30);
  assembly.mogo_clamp_piston.set(true);
  task::sleep(100);

  default_constants();
  start_intake();
  chassis.turn_to_point(59.413, -47.365);
  chassis.drive_to_point(59.413, -47.365);
  
  chassis.turn_to_point(64.233, -64.715, true);
  task::sleep(400);
  assembly.mogo_clamp_piston.set(false);
  drive_until_settled(-10, -10);
  chassis.drive_on_PID(5);
  chassis.drive_on_PID(-5);
  chassis.drive_on_PID(5);
  
  
  Brain.Screen.printAt(30, 30, "%f", Brain.Timer.time(msec) - time);
}


void start_intake(bool unjam_intake) {
  if (unjam_intake) {
    assembly._unjam_intake_task.resume();
  } else {
    assembly._unjam_intake_task.suspend();
  }
  assembly.intake_motor.spin(fwd, 12, volt);
}

void stop_intake() {
  assembly._unjam_intake_task.suspend();
  assembly.intake_motor.stop();
}

void LB_task(int angle) {
  assembly.LB_goto_state_task = angle;
  vex::task task = vex::task([](){
    if (assembly.LB_goto_state_task < ACTIVE) {
      assembly.intake_motor.spinFor(-30, vex::rotationUnits::deg, true);
    }

    assembly.move_LB_to_angle(assembly.LB_goto_state_task);
    return 0;
  });
}

void distance_reset() {
  vex::distance dis = vex::distance(vex::PORT21);
  float hypotnuse = dis.objectDistance(vex::inches);
  float theta = to_rad(chassis.get_absolute_heading());
  chassis.set_coordinates(-hypotnuse * sin(theta), 62 + (hypotnuse * cos(theta) - 7.7), chassis.get_absolute_heading());  
}

void drive_until_settled(float left_voltage, float right_voltage) {
  chassis.drive_with_voltage(left_voltage, right_voltage);


  while (1) {
    double start = chassis.forward_tracker.position(deg);
    vex::task::sleep(100);
    double end = chassis.forward_tracker.position(deg);

    if (std::abs(end - start) < 1) {
      chassis.stop_drive(coast);
      break;
    }
  }
}

void intake_ring_halfway() {
  vex::task intake_ring_halfway_task([](){
    int timeout_start = Brain.Timer.time(vex::timeUnits::sec);
    while (1) {
        if (assembly.ring_distance_sensor.objectDistance(mm) < 50) {
          assembly.intake_motor.stop(brake);
          break;
        }
        if (Brain.Timer.time(vex::timeUnits::sec) - timeout_start > 5) {
          break;
        }
        vex::this_thread::sleep_for(50);

    }
    return 0;
  });
}

void score_LB() {
  assembly.LB_motors.spin(fwd, -12, velocity_units::volt);
  int start_pos = assembly.LB_encoder.position(deg);
  while (!(std::abs(assembly.LB_encoder.position(deg) - start_pos) < (SCORING + 30))) {
    assembly.LB_motors.stop(hold);
  }
}

void color_sort_auton(color_sort color) {
  assembly.select_ring_sort_mode(color);
  
  vex::task _color_sort_task([](){
    while(1) {
      assembly.ring_sort();
      vex::this_thread::sleep_for(50);
    }
    return 0;
  });
}