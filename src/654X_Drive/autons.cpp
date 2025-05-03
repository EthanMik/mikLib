#include "vex.h"

using namespace vex;

static vex::task LB_move_task;

void blue_ringside_winpoint(bool calibrate) { chassis.set_coordinates(100, 200, 180); }
void blue_ringside_sawp(bool calibrate) { print("blue_ringside_sawp"); }
void blue_ringside_elim(bool calibrate) {   
  if (calibrate) {
    chassis.set_coordinates(55, 23.5, 270);
    return;
  }

  assembly.unjam_intake_task();
  stop_intake();
  color_sort_auton(color_sort::BLUE);

  // thread odom(print_coordinates);
  chassis.drive_on_PID(3);
  LB_task(HANG);
  task::sleep(600);

  chassis.drive_on_PID(-6);
  chassis.turn_to_point(21.268, 24.397, true);
  chassis.drive_to_point(21.268, 24.397);
  LB_task(INACTIVE);

  assembly.mogo_clamp_piston.set(true);
  task::sleep(200);
  default_constants();
  chassis.turn_to_point(8, 39);
  start_intake();
  chassis.drive_to_point(8, 39);

  chassis.left_swing_to_angle(0);

  chassis.drive_to_point(8, 54);
  chassis.drive_to_point(13, 29.5);

  chassis.turn_to_point(22, 45);
  chassis.drive_to_point(22, 45);

  chassis.turn_to_point(60.5, 60);
  chassis.drive_to_point(60.5, 60.348);

  chassis.turn_to_point(18.902, 12.154, true);
  drive_until_settled(8,8);
  // chassis.drive_on_PID(5);
  chassis.drive_to_point(47, 46);
  // chassis.drive_on_PID(-10);

  chassis.turn_to_point(47, 3);
  chassis.drive_to_point(47, 18);
  assembly.lift_piston.set(true);
  chassis.drive_to_point(47, 3);
  assembly.lift_piston.set(false);
  task::sleep(200);
  chassis.drive_on_PID(-9);

  
}
void blue_goalside_winpoint(bool calibrate) { print("blue_goalside_winpoint"); }
void blue_goalside_sawp(bool calibrate) { print("blue_goalside_sawp"); }
void blue_goalside_elim(bool calibrate) {
  if (calibrate) {
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
void red_ringside_winpoint(bool calibrate) { print("red_ringside_winpoint"); }
void red_ringside_sawp(bool calibrate) { print("red_ringside_sawp"); }
void red_ringside_elim(bool calibrate) { 
  if (calibrate) {
    chassis.set_coordinates(-55, 23.5, 270);
    return;
  }

  assembly.unjam_intake_task();
  stop_intake();
  color_sort_auton(color_sort::BLUE);
  
  // thread odom(print_coordinates);
  chassis.drive_on_PID(3);
  LB_task(HANG);
  task::sleep(600);
  
  chassis.drive_on_PID(-6);
  chassis.turn_to_point(-21.268, 24.397, true);
  chassis.drive_to_point(-21.268, 24.397);
  LB_task(INACTIVE);

  assembly.mogo_clamp_piston.set(true);
  task::sleep(200);
  default_constants();
  chassis.turn_to_point(-8, 39);
  start_intake();
  chassis.drive_to_point(-8, 39);
  
  chassis.right_swing_to_angle(0);
  
  chassis.drive_to_point(-8, 54);
  chassis.drive_to_point(-13, 29.5);

  chassis.turn_to_point(-22, 45);
  chassis.drive_to_point(-22, 45);

  chassis.turn_to_point(-60.5, 60);
  chassis.drive_to_point(-60.5, 60.348);

  chassis.turn_to_point(-18.902, 12.154, true);
  drive_until_settled(8,8);
  // chassis.drive_on_PID(5);
  chassis.drive_to_point(-47, 46);
  // chassis.drive_on_PID(-10);
  
  chassis.turn_to_point(-47, 3);
  chassis.drive_to_point(-47, 18);
  assembly.lift_piston.set(true);
  chassis.drive_max_voltage = 4;
  chassis.turn_to_point(-47, 7);
  chassis.drive_to_point(-47, 7);
  assembly.lift_piston.set(false);
  task::sleep(200);
  chassis.drive_on_PID(-9);
}



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
    chassis.set_coordinates(-40, 23.5, 90);
    
    task::sleep(500);
    chassis.turn_settle_error = 500;
    chassis.drive_settle_error = 500;
    chassis.turn_settle_error = .01;
    chassis.drive_settle_error = .01;
    chassis.turn_max_voltage = 4.5;
    chassis.drive_max_voltage = 3;
    chassis.drive_on_PID(-10);
    chassis.turn_to_point(-4.73, 42.7);
    chassis.turn_to_point(-4.73, 42.7);

    default_constants();
    task::sleep(500);
    return;
  }
  
  assembly.intake_motor.spin(fwd, 10.5, volt);
  intake_ring_halfway();
  assembly.doinker_piston.set(true);
  chassis.drive_max_voltage = 12;
  chassis.drive_on_PID(45);

  chassis.drive_max_voltage = 7;

  chassis.drive_min_voltage = 3;
  chassis.drive_to_point(-17.924, 29.621);
  chassis.drive_on_PID(-16);

  assembly.doinker_piston.set(false);
  start_intake();
  assembly.mogo_clamp_piston.set(true);
  vex::task::sleep(150);
  default_constants();  
  
  assembly.rush_piston.set(true);
  chassis.turn_to_point(-23.48, 47.5);
  chassis.drive_to_point(-23.48, 47.5);
  assembly.rush_piston.set(false);

  start_intake();
  default_constants();
  chassis.turn_to_point(-61, 58);
  chassis.drive_to_point(-61, 58);
  start_intake();
  chassis.turn_to_point(-71.518, 71.518);
  drive_until_settled(6, 6, 2500, 1000);
  chassis.drive_max_voltage = 5;
  chassis.drive_on_PID(-15);
  chassis.drive_max_voltage = 10;
  chassis.drive_on_PID(10);
  
  chassis.turn_to_point(-47.095, 0);
  chassis.drive_max_voltage = 12;
  chassis.drive_to_point(-47.095, 14);
  chassis.drive_max_voltage = 5;
  assembly.lift_piston.set(true);
  chassis.drive_to_point(-47.095, 0);
  LB_task(ACTIVE);
  assembly.lift_piston.set(false);
  assembly.rush_piston.set(true);
  chassis.turn_to_point(-60, 0);
  assembly.rush_piston.set(false);
  
  start_intake();
  default_constants();
  chassis.drive_to_point(-60, 0);
  drive_until_settled(8, 8, 2000, 500);
  stop_intake();
  LB_task(HANG);
  chassis.drive_on_PID(-8);
  task::sleep(200);
  LB_task(INACTIVE);
  chassis.drive_on_PID(3);
  chassis.right_swing_to_angle(30);

  chassis.stop_drive(coast);
  stop_intake();
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

void skills(bool calibrate) {
  if (calibrate) {
    chassis.set_coordinates(-54.5, 0, 270);
    return;
  }
  // float time = Brain.Timer.time(msec);
  // assembly.unjam_intake_task();
  // stop_intake();

  LB_task(HANG);
  task::sleep(400);
  
  chassis.drive_on_PID(-11);
  assembly.mogo_clamp_piston.set(true);
  vex::task::sleep(150);
  LB_task(INACTIVE);

  chassis.turn_to_point(-24.5, -24);
  start_intake();
  chassis.drive_to_point(-24.5, -24);
  
  chassis.turn_to_point(50.752, -61.884);
  chassis.drive_to_point(50.752, -61.884);
  LB_task(ACTIVE);
  
  chassis.drive_to_point(-0.284, -43);
  
  stop_intake();
  LB_task(HOLDING - 30);
  chassis.turn_to_point(-0.284, -62.694);
  assembly.intake_motor.spin(fwd, 10, volt);
  intake_ring_halfway();
  chassis.drive_to_point(-0.284, -62.694);
  drive_until_settled(8, 8, 1000, 0);

  LB_task(SCORING);
  vex::task::sleep(500);

  LB_move_task.stop();
  
  assembly.set_LB_constants(12, .2, .1, .02, 0, 2, 200, 1500);
  assembly.move_LB_to_angle(ACTIVE);
  default_constants();
  chassis.drive_with_voltage(4, 4);

  start_intake();
  vex::task::sleep(250);
  LB_task(SCORING);
  vex::task::sleep(500);
  chassis.drive_on_PID(-13);

  chassis.drive_to_point(0, -48.488);
  LB_task(INACTIVE);
  
  chassis.turn_to_point(-60.516, -46.973);
  start_intake();
  chassis.drive_to_point(-40.299, -46.973);
  chassis.drive_max_voltage = 6;
  chassis.drive_to_point(-60.516, -46.973);
  chassis.drive_max_voltage = 8;
  chassis.turn_to_point(-47.818, -57.727);
  chassis.drive_to_point(-47.818, -57.727);
  
  chassis.turn_to_point(-58, -61, true);
  chassis.drive_on_PID(-10);
  assembly.mogo_clamp_piston.set(false);
  task::sleep(200);
  
  chassis.drive_on_PID(10);
  stop_intake();
  
  chassis.turn_to_point(-47.336, 27.239, true);
  chassis.drive_to_point(-47.336, 15.239);
  chassis.drive_max_voltage = 6;
  chassis.drive_to_point(-47.336, 21.239);
  chassis.drive_max_voltage = 8;

  assembly.mogo_clamp_piston.set(true);
  task::sleep(200);
  chassis.turn_to_point(-25, 23.5);
  start_intake();
  chassis.drive_to_point(-25, 23.5);

  chassis.turn_to_point(23.5, 47);
  chassis.drive_to_point(23.5, 47);
  LB_task(ACTIVE);
  
  chassis.drive_to_point(0, 43);
  stop_intake();
  LB_task(HOLDING - 30);

  chassis.turn_to_point(0, 62.5);
  start_intake();
  assembly._unjam_intake_task.stop();
  chassis.drive_to_point(0, 62.5);
  drive_until_settled(8, 8, 1000, 0);




  // Stage two of run

  distance_reset();

  // chassis.set_coordinates(0, 54.5, 0);
  // LB_task(INACTIVE);
  // assembly.mogo_clamp_piston.set(true);
  // task::sleep(200);
  
  LB_task(SCORING);
  task::sleep(500);
  chassis.drive_on_PID(-13);
  // chassis.drive_to_point(0, 48);
  LB_task(INACTIVE);


  chassis.turn_to_point(-60.348, 46.854);
  chassis.drive_to_point(-40.299, 46.973);
  chassis.drive_max_voltage = 6;
  chassis.drive_to_point(-60.348, 46.854);
  chassis.drive_max_voltage = 8;

  chassis.turn_to_point(-45.649, 60.589);
  chassis.drive_to_point(-45.649, 60.589);

  chassis.turn_to_point(-61.312, 62.276, true);
  chassis.drive_on_PID(-10);
  assembly.mogo_clamp_piston.set(false);
  task::sleep(150);
  chassis.drive_on_PID(10);
  stop_intake();

  chassis.turn_to_point(47.194, 46.912);

  // chassis.set_coordinates(23.5, 47, 90);
  start_intake();

  LB_task(ACTIVE);
  chassis.drive_to_point(47.194, 46.912);

  chassis.turn_to_point(47, 0, true);
  chassis.drive_to_point(47, 13);
  chassis.drive_max_voltage = 6;
  chassis.drive_to_point(47, 0);
  chassis.drive_max_voltage = 8;
  stop_intake();
  assembly.mogo_clamp_piston.set(true);
  task::sleep(150);

  chassis.turn_to_point(62, 0);
  chassis.drive_to_point(62, 0);

  drive_until_settled(8, 8);

  LB_task(36);
  chassis.drive_on_PID(-8);
  task::sleep(100);
  chassis.drive_to_point(47, 0);
  LB_task(INACTIVE);
  
  chassis.turn_to_point(47, -50);
  
  assembly.unjam_intake_task();
  start_intake();

  chassis.drive_to_point(47, -50);
  chassis.right_swing_to_angle(15, true);
  chassis.drive_on_PID(8);

  chassis.turn_to_point(22.786, -22.786);
  assembly._unjam_intake_task.stop();
  chassis.drive_to_point(22.786, -22.786);
  assembly.intake_motor.spin(fwd, 10, volt);
  intake_ring_halfway();

  chassis.turn_to_point(0.376, 0.106);
  chassis.drive_to_point(0.376, 0.106);
  // assembly.doinker_piston.set(true);
  start_intake();
  chassis.drive_on_PID(4);
  task::sleep(300);
  chassis.turn_to_point(23.75, 23.239);
  stop_intake();
  chassis.drive_to_point(23.75, 23.239);
  start_intake();
  // assembly.doinker_piston.set(false);
  chassis.turn_to_point(47.364, 62.341);
  chassis.drive_to_point(47.364, 62.341);
  
  chassis.turn_to_point(61.992, 70.059, true);
  
  assembly.mogo_clamp_piston.set(false);
  chassis.drive_with_voltage(-12, -12);
  task::sleep(500);
  chassis.stop_drive(hold);

  chassis.drive_max_voltage = 12;
  chassis.drive_to_point(36.08, 38.439);

  chassis.turn_to_point(64.5, -64.5);
  drive_until_settled(12, 12, 2500, 500);
  
  LB_task(DESCORE_TOP);
  chassis.drive_to_point(23.5, -23.5);
  chassis.turn_to_point(0, 0, true);
  drive_until_settled(-6, -6, 2500, 0);
  chassis.stop_drive(coast);

  
  // Brain.Screen.printAt(30, 30, "%f", Brain.Timer.time(msec) - time);
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


void LB_task(int angle, bool override) {
  assembly.LB_goto_state_task = angle;
  LB_move_task = vex::task([](){
    if (assembly.LB_goto_state_task < ACTIVE && std::abs(assembly.LB_encoder.position(deg) - ACTIVE) < 30 ) {
      assembly.intake_motor.spinFor(-30, vex::rotationUnits::deg, true);
    }
    while(1) {
      assembly.move_LB_to_angle(assembly.LB_goto_state_task);
      task::sleep(20);
    }
    return 0;
  });
}

void distance_reset() {
  vex::distance dis = vex::distance(vex::PORT17);
  float hypotnuse = dis.objectDistance(vex::inches);
  float theta = to_rad(chassis.get_absolute_heading());
  float r = hypotnuse + 2.34;
  Brain.Screen.printAt(30, 30, " X: %f", -r * sin(theta));
  Brain.Screen.printAt(30, 50, " Y: %f", (68.5-r) * cos(theta));
  Brain.Screen.printAt(30, 110, " theta: %f", to_rad(chassis.get_absolute_heading()));
  Brain.Screen.printAt(30, 130, " hyp: %f", hypotnuse);
  // chassis.set_coordinates(-hypotnuse * sin(theta), 61 + (hypotnuse * cos(theta) - 6.6), chassis.get_absolute_heading());  
}

void drive_until_settled(float left_voltage, float right_voltage, float timeout, float min_timeout) {
  chassis.drive_with_voltage(left_voltage, right_voltage);

  float start_time = Brain.Timer.time(vex::timeUnits::msec);

  while (1) {
    double start = chassis.forward_tracker.position(deg);
    vex::task::sleep(100);
    double end = chassis.forward_tracker.position(deg);

    if (Brain.Timer.time(vex::timeUnits::msec) - start_time > timeout) {
      chassis.stop_drive(coast);
      break;
    }

    if (std::abs(end - start) < 1 && Brain.Timer.time(vex::timeUnits::msec) - start_time > min_timeout) {
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