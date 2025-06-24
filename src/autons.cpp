#include "vex.h"

using namespace vex;

vex::task LB_move_task;

void mogo_constants(void) {
  chassis.set_turn_constants(12, .47, .0235, 5.086, 15, 1.5, 20, 75, 2000);
  chassis.set_swing_constants(12, 1.31, .0325, 8.676, 15, 1.5, 20, 75, 2000);
}

void default_constants(void) {
  chassis.set_turn_constants(12, .437, .0215, 3.686, 15, 1.5, 20, 75, 2000);
  chassis.set_drive_constants(10, 1.5, 0, 10, 0, 1, 75, 3000);
  chassis.set_heading_constants(6, .4, 0, 1, 0);
  chassis.set_swing_constants(12, .437, .0295, 3.486, 15, 1.25, 20, 75, 3000);
  assembly.set_LB_constants(12, .2, .1, .02, 0, .5, 200, 3000);
}

void odom_constants(void) {
  default_constants();
  chassis.heading_max_voltage = 10;
  chassis.turn_max_voltage = 12;
  chassis.drive_max_voltage = 8;
  chassis.drive_settle_error = 3;
  chassis.boomerang_lead = .5;
  chassis.drive_min_voltage = 0;
}

std::string template_auto(bool calibrate, auto_variation var, bool get_name, bool get_lineup) {
  /* The first variation will be this auto */
  if (var == ONE) {}

  /* We declare and allow a second variation of this auto; 
  You may want this if you want a different movements in the same starting configuration */
  if (var == TWO) { return template_auto_other_variation(calibrate, get_name, get_lineup); }

  if (get_lineup) { /* Provide a png of the auto route (optional) */ return "template_1_route.png"; }
  if (get_name) { /* Give a desciption of your auto */ return "template auto 1: scores 4 game objects"; }
  if (calibrate) {
    /* Initialize robots starting position "https://path.jerryio.com/" and/or add extra movements to line up robots 
    starting position ## IF MOVING DURING CALIBRATION DO BEFORE FIELD CONTROLLER PLUG IN ## */
    chassis.set_coordinates(55, 23.5, 90);
    
    /* Example of turning before auto is ran */
    chassis.turn_max_voltage = 6; 
    chassis.turn(45);

    return "";
  }
    
  /* We now run the auto */ 
  chassis.drive(10);
  chassis.drive(-10);

  return "";
}
std::string template_auto_other_variation(bool calibrate, bool get_name, bool get_lineup) {
  if (get_lineup) { return "template_2_route.png"; }
  if (get_name) { return "template auto 2: scores 2 game objects"; }
  if (calibrate) {
    chassis.set_coordinates(55, 23.5, 90);
    return "";
  }
  
  chassis.drive(20);
  chassis.drive(-20);

  return "";
}

std::string blue_left_winpoint(bool calibrate, auto_variation var, bool get_name, bool get_lineup) {
  if (get_lineup) {
    return "";
  }
  if (get_name) {
    return "Blue Ringside Winpoint: 4+1";
  }
  if (calibrate) {
    chassis.set_coordinates(55, 23.5, 90);
    return "";
  }

  // assembly.unjam_intake_task();
  // stop_intake();
  color_sort_auton(color_sort::RED);
  chassis.drive(3);
  LB_task(36);
  task::sleep(500);
  
  chassis.drive(-6);
  chassis.turn_to_point(33.999, 20.267, true);
  chassis.drive_to_point(33.999, 20.267);
  chassis.drive_max_voltage = 6;
  chassis.drive(-8);
  chassis.drive_max_voltage = 12;
  LB_task(INACTIVE);
  
  assembly.mogo_clamp_piston.set(true);
  task::sleep(100);
  mogo_constants();
  chassis.turn_to_point(8, 39);
  start_intake();
  chassis.drive_to_point(8, 39);
  
  chassis.left_swing(0);
  
  chassis.drive_to_point(8, 57);
  chassis.drive_to_point(15.247, 27.654);

  chassis.turn_to_point(22, 45);
  chassis.drive_to_point(22, 45);
  
  chassis.turn_to_point(54.455, 55.496);

  chassis.turn_to_point(54.5, 55.5);
  chassis.drive_to_point(54.5, 55.5);
  start_intake();
  chassis.turn_to_point(71.518, 71.518);
  drive_until_settled(7, 7, 2500, 1000);
  chassis.drive_max_voltage = 5;
  chassis.drive(-15);
  chassis.drive_max_voltage = 10;
  chassis.drive(10);

  chassis.drive(-10);

  chassis.turn_to_point(18.278, 16.668);
  LB_task(DESCORE_TOP);
  chassis.drive_to_point(18.278, 16.668);
  LB_move_task.stop();
  assembly.LB_motors.spin(fwd, -2, VOLT);

  return "";
 }
std::string blue_left_sawp(bool calibrate, auto_variation var, bool get_name, bool get_lineup) { 
  if (get_lineup) {
    return "";
  }
  if (get_name) {
    return "Blue Ringside Sawp: (3,2)+1";
  }
  return "";
}
std::string blue_left_elim(bool calibrate, auto_variation var, bool get_name, bool get_lineup) {   
  if (get_lineup) {
    return "";
  }
  if (get_name) {
    return "Blue Ring Rush: 6+1";
  }
  if (calibrate) {
    chassis.set_coordinates(40, 23.5, 270);
    assembly.is_aligning = true;
    task::sleep(500);
    chassis.turn_settle_error = 500;
    chassis.drive_settle_error = 500;
    chassis.turn_settle_error = .01;
    chassis.drive_settle_error = .01;
    chassis.turn_max_voltage = 4.5;
    chassis.drive_max_voltage = 3;
    chassis.drive(-10);
    chassis.turn_to_point(4.73, 42.7);
    chassis.turn_to_point(4.73, 42.7);
    
    default_constants();
    task::sleep(500);
    assembly.is_aligning = false;
    return "";
  }
  
  assembly.intake_motor.spin(fwd, 10.5, volt);
  intake_ring_halfway();

  assembly.rush_piston.set(true);
  chassis.drive_max_voltage = 12;
  chassis.drive(45);

  chassis.drive_max_voltage = 7;

  chassis.drive_min_voltage = 3;
  chassis.drive_to_point(17.924, 29.621);
  chassis.drive(-16);

  assembly.rush_piston.set(false);
  start_intake();
  assembly.mogo_clamp_piston.set(true);
  default_constants();  
  
  assembly.doinker_piston.set(true);
  chassis.turn_to_point(23.48, 47.5);
  chassis.drive_to_point(23.48, 47.5);
  task::sleep(300);
  assembly.doinker_piston.set(false);

  start_intake();
  default_constants();
  chassis.turn_to_point(54.5, 55.5);
  chassis.drive_to_point(54.5, 55.5);
  start_intake();
  chassis.turn_to_point(71.518, 71.518);
  drive_until_settled(7, 7, 2500, 1000);
  chassis.drive_max_voltage = 5;
  chassis.drive(-15);
  chassis.drive_max_voltage = 10;
  chassis.drive(10);
  
  chassis.turn_to_point(47.095, 0);
  chassis.drive_max_voltage = 12;
  chassis.drive_to_point(47.095, 14);
  chassis.drive_max_voltage = 5;
  assembly.lift_piston.set(true);
  chassis.drive_to_point(47.095, 0);
  LB_task(ACTIVE);
  assembly.lift_piston.set(false);
  assembly.doinker_piston.set(true);
  chassis.turn_to_point(60, 0);
  assembly.doinker_piston.set(false);
  
  start_intake();
  default_constants();
  chassis.drive_to_point(60, 0);
  drive_until_settled(8, 8, 2000, 500);
  stop_intake();
  LB_task(37);
  chassis.drive(-8);
  task::sleep(200);
  chassis.left_swing(30);

  chassis.stop_drive(coast);
  stop_intake();
  return "";
}
std::string blue_right_winpoint(bool calibrate, auto_variation var, bool get_name, bool get_lineup) {
  if (get_lineup) {
    return "";
  }
  if (get_name) {
    return "Blue Goalside Winpoint: 5";
  }
  return "";
}
std::string blue_right_sawp(bool calibrate, auto_variation var, bool get_name, bool get_lineup) { 
  if (get_lineup) {
    return "";
  }
  if (get_name) {
    return "";
  }
  return "";
}
std::string blue_right_elim(bool calibrate, auto_variation var, bool get_name, bool get_lineup) {
  if (get_lineup) {
    return "";
  }
  if (get_name) {
    return "Blue Driver Goalrush: 6";
  }
  if (calibrate) {
    chassis.set_coordinates(55, -23.5, 90);
    return "";
  }

  color_sort_auton(color_sort::RED);
  LB_task(INACTIVE);

  chassis.drive_to_point(36.412, -23.901);
  chassis.drive_max_voltage = 6;
  chassis.drive_to_point(28.009, -23.901);
  assembly.mogo_clamp_piston.set(true);
  task::sleep(150);

  mogo_constants();
  chassis.turn_to_point(8.216, -4.668);
  assembly.doinker_piston.set(true);
  default_constants();
  chassis.drive(23.5);
  chassis.drive_to_point(6.226, -7.547);
  default_constants();
  // chassis.turn_starti = 0;
  chassis.turn_to_point(-7.096, -3.9);
  assembly.rush_piston.set(true);
  task::sleep(150);
  chassis.drive_to_point(38.466, -33.611);
  assembly.rush_piston.set(false);
  assembly.doinker_piston.set(false);
  task::sleep(100);
  start_intake();
  
  default_constants();
  mogo_constants();
  chassis.turn_to_point(32.491, -18.86);
  chassis.drive_to_point(32.491, -18.86);
  
  chassis.turn_to_point(26.604, -26.871);
  chassis.drive(10);
  // chassis.swing_max_voltage = 8;
  // chassis.right_swing(180);
  // chassis.turn_to_point(23.715, -49.857);
  chassis.drive_to_point(23.715, -47.9);
  
  chassis.turn_to_point(58.908, -57.495);
  chassis.drive_to_point(58.908, -57.495);
  
  chassis.turn_to_point(71.5, -71.5);
  task::sleep(100);
  
  drive_until_settled(6, 6, 2500, 850);
  chassis.drive_max_voltage = 5;
  chassis.drive(-15);
  chassis.drive_max_voltage = 10;
  chassis.drive(10);
  chassis.drive(-5);
  
  assembly.rush_piston.set(true);
  chassis.turn_max_voltage = 8;
  chassis.turn(340);
  assembly.mogo_clamp_piston.set(false);
  chassis.stop_drive(coast);
  return "";
}

std::string red_left_winpoint(bool calibrate, auto_variation var, bool get_name, bool get_lineup) { 
  if (get_lineup) {
    return "";
  }
  if (get_name) {
    return "Red Ringside Winpoint: 4+1";
  }
  if (calibrate) {
    chassis.set_coordinates(-55, 23.5, 270);
    return "";
  }

  
  // assembly.unjam_intake_task();
  // stop_intake();
  color_sort_auton(color_sort::BLUE);
  
  chassis.drive(3);
  LB_task(36);
  task::sleep(500);
  
  chassis.drive(-6);
  // chassis.drive_to_pose(-21.3, 24.4, 40);
  chassis.turn_to_point(-33.999, 20.267, 180.0f);
  chassis.drive_to_point(-33.999, 20.267);
  chassis.drive_max_voltage = 6;
  chassis.drive(-8);
  chassis.drive_max_voltage = 12;
  LB_task(INACTIVE);
  
  assembly.mogo_clamp_piston.set(true);
  task::sleep(100);
  mogo_constants();
  chassis.turn_to_point(-8, 39);
  start_intake();
  chassis.drive_to_point(-8, 39);
  
  chassis.right_swing(0);
  
  chassis.drive_to_point(-8, 57);
  chassis.drive_to_point(-15.247, 27.654);

  chassis.turn_to_point(-22, 45);
  chassis.drive_to_point(-22, 45);
  
  chassis.turn_to_point(-54.455, 55.496);

  chassis.turn_to_point(-54.5, 55.5);
  chassis.drive_to_point(-54.5, 55.5);
  start_intake();
  chassis.turn_to_point(-71.518, 71.518);
  drive_until_settled(7, 7, 2500, 1000);
  chassis.drive_max_voltage = 5;
  chassis.drive(-15);
  chassis.drive_max_voltage = 10;
  chassis.drive(10);

  chassis.drive(-10);

  chassis.turn_to_point(-18.278, 16.668);
  LB_task(DESCORE_TOP);
  chassis.drive_to_point(-18.278, 16.668);
  LB_move_task.stop();
  assembly.LB_motors.spin(fwd, -2, VOLT);
  
  return "";
}
std::string red_left_sawp(bool calibrate, auto_variation var, bool get_name, bool get_lineup) { 
  if (get_lineup) {
    return "";
  }
  if (get_name) {
    return "Red Ringside Sawp: (3,2)+1";
  }
  if (calibrate) {
    chassis.set_coordinates(-55, 23.5, 270);
    return "";
  }

  
  // assembly.unjam_intake_task();
  // stop_intake();
  color_sort_auton(color_sort::BLUE);
  
  chassis.drive(3);
  LB_task(36);
  task::sleep(500);
  
  // chassis.drive(-6);
  // chassis.turn_to_point(-34.806, 17.97, true);
  chassis.drive_to_point(-34.806, 17.97);
  chassis.drive_max_voltage = 6;
  chassis.drive(-9);
  chassis.drive_max_voltage = 12;
  LB_task(INACTIVE);
  
  assembly.mogo_clamp_piston.set(true);
  task::sleep(150);
  mogo_constants();
  chassis.turn_to_point(-8, 39);
  start_intake();
  chassis.drive_to_point(-8, 39);
  
  chassis.right_swing(0);
  
  chassis.drive_to_point(-8, 57);
  chassis.drive_to_point(-10.133, 35.609);

  chassis.turn_to_point(-22, 45);
  chassis.drive_to_point(-22, 45);


  chassis.turn_to_point(-47.068, 0);
  assembly.lift_piston.set(true);
  stop_intake();
  assembly.intake_motor.spin(fwd, 10.5, volt);
  intake_ring_halfway();
  chassis.drive_to_point(-47.068, 0);

  assembly.lift_piston.set(false);
  assembly.mogo_clamp_piston.set(false);
  chassis.drive_max_voltage = 12;

  default_constants();
  chassis.turn_to_point(-31.536, -15.531, true);
  chassis.drive_to_point(-31.536, -15.531);
  chassis.drive_max_voltage = 6;
  chassis.drive(-9);
  chassis.drive_max_voltage = 12;
  assembly.mogo_clamp_piston.set(true);
  mogo_constants();
  chassis.turn_to_point(-23.588, -46.874);
  start_intake();
  chassis.drive_max_voltage = 12;
  chassis.drive_to_point(-23.588, -46.874);
  LB_task(DESCORE_TOP);
  start_intake();
  chassis.turn_to_point(-15.058, -25.191);
  start_intake();
  chassis.drive_to_point(-15.058, -25.191);
  LB_move_task.stop();
  assembly.LB_motors.spin(fwd, -2, VOLT);
  return "";
}
std::string red_left_elim(bool calibrate, auto_variation var, bool get_name, bool get_lineup) { 
  if (get_lineup) {
    return "";
  }
  if (get_name) {
    return "Red Ring Rush: 6+1";
  }
  if (calibrate) {
    chassis.set_coordinates(-40, 23.5, 90);
    
    task::sleep(500);
    chassis.turn_settle_error = 500;
    chassis.drive_settle_error = 500;
    chassis.turn_settle_error = .01;
    chassis.drive_settle_error = .01;
    chassis.turn_max_voltage = 4.5;
    chassis.drive_max_voltage = 3;
    chassis.drive(-10);
    chassis.turn_to_point(-4.73, 42.7);
    chassis.turn_to_point(-4.73, 42.7);

    default_constants();
    task::sleep(500);
    return "";
  }
  
  assembly.intake_motor.spin(fwd, 10.5, volt);
  intake_ring_halfway();
  assembly.doinker_piston.set(true);
  chassis.drive_max_voltage = 12;
  chassis.drive(45);

  chassis.drive_max_voltage = 7;

  chassis.drive_min_voltage = 3;
  chassis.drive_to_point(-17.924, 29.621);
  chassis.drive(-16);

  assembly.doinker_piston.set(false);
  start_intake();
  assembly.mogo_clamp_piston.set(true);
  default_constants();  
  
  assembly.rush_piston.set(true);
  chassis.turn_to_point(-23.48, 47.5);
  chassis.drive_to_point(-23.48, 47.5);
  task::sleep(300);
  assembly.rush_piston.set(false);

  start_intake();
  default_constants();
  chassis.turn_to_point(-54.5, 55.5);
  chassis.drive_to_point(-54.5, 55.5);
  start_intake();
  chassis.turn_to_point(-71.518, 71.518);
  drive_until_settled(7, 7, 2500, 1000);
  chassis.drive_max_voltage = 5;
  chassis.drive(-15);
  chassis.drive_max_voltage = 10;
  chassis.drive(10);
  
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
  LB_task(37);
  chassis.drive(-8);
  task::sleep(200);
  chassis.right_swing(30);

  chassis.stop_drive(coast);
  stop_intake();
  return "";
}
std::string red_right_winpoint(bool calibrate, auto_variation var, bool get_name, bool get_lineup) { 
  if (get_lineup) {
    return "";
  }
  if (get_name) {
    return "Red Goalside Winpoint: 5";
  }
  return "";
}
std::string red_right_sawp(bool calibrate, auto_variation var, bool get_name, bool get_lineup) {
  if (get_lineup) {
    return "";
  }
  if (get_name) {
    return "Red Goalside Sawp: (2,1)+1";
  }
  return "";
}
std::string red_right_elim(bool calibrate, auto_variation var, bool get_name, bool get_lineup) {   
  if (get_lineup) {
    return "red_goalside_elim_auto.png";
  }
  if (get_name) {
    return "Red Driver Goalrush: 6";
  }
  if (calibrate) {
    chassis.set_coordinates(-55, -23.5, 270);
    return "";
  }
  color_sort_auton(color_sort::BLUE);

  chassis.drive(3);
  LB_task(36);
  task::sleep(500);
  
  chassis.drive(-6);
  chassis.turn_to_point(-33.999, -20.267, true);
  chassis.drive_to_point(-33.999, -20.267);
  chassis.drive_max_voltage = 6;
  chassis.drive(-8);
  chassis.drive_max_voltage = 12;
  LB_task(INACTIVE);
  
  assembly.mogo_clamp_piston.set(true);
  task::sleep(100);

  mogo_constants();
  chassis.turn_to_point(-8.216, -4.668);
  assembly.rush_piston.set(true);
  default_constants();
  chassis.drive(23.5);
  mogo_constants();
  // chassis.turn_max_voltage = 2;
  chassis.turn(70);

  // chassis.turn_to_point(15.058, 10.986);
  assembly.doinker_piston.set(true);
  task::sleep(150);
  chassis.drive_to_point(-38.466, -33.611);
  assembly.doinker_piston.set(false);
  assembly.rush_piston.set(false);
  task::sleep(100);
  start_intake();

  default_constants();
  mogo_constants();
  chassis.turn(0);
  chassis.drive(8);
  // chassis.drive_to_point(-32.491, -18.86);
  // chassis.turn_to_point(-26.604, -26.871);
  chassis.left_swing(180);

  // chassis.drive(10);
  // chassis.swing_max_voltage = 8;
  // chassis.right_swing(180);
  // chassis.turn_to_point(23.715, -49.857);
  chassis.drive_to_point(-23.715, -47.9);

  chassis.left_swing(230);
  // chassis.turn_to_point(-58.908, -57.495);
  chassis.drive(30);

  chassis.turn_to_point(-71.5, -71.5);
  task::sleep(100);

  drive_until_settled(6, 6, 2500, 850);
  chassis.drive_max_voltage = 5;
  chassis.drive(-15);
  chassis.drive_max_voltage = 10;
  chassis.drive(10);
  chassis.drive(-5);

  assembly.rush_piston.set(true);
  chassis.turn_max_voltage = 8;
  chassis.turn(90);
  assembly.mogo_clamp_piston.set(false);
  chassis.stop_drive(coast);
  return "";
}

std::string skills(bool calibrate, auto_variation var, bool get_name, bool get_lineup) {
  if (get_lineup) {
    return "";
  }
  if (get_name) {
    return "Skills";
  }
  if (calibrate) {
    chassis.set_coordinates(-54.5, 0, 270);
    return "";
  }
  // float time = Brain.Timer.time(msec);
  // assembly.unjam_intake_task();
  // stop_intake();
  color_sort_auton(color_sort::BLUE);

  LB_task(HANG);
  task::sleep(400);
  
  chassis.drive(-13);
  assembly.mogo_clamp_piston.set(true);
  task::sleep(200);
  LB_task(INACTIVE);
  mogo_constants();

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

  assembly.async_LB.suspend();
  
  assembly.set_LB_constants(12, .2, .1, .02, 0, 2, 200, 1500);
  assembly.move_LB_to_angle(ACTIVE);
  default_constants();
  mogo_constants();
  chassis.drive_with_voltage(4, 4);

  start_intake();
  vex::task::sleep(250);
  assembly.async_LB.resume();
  LB_task(SCORING);
  vex::task::sleep(500);
  chassis.drive(-13);

  LB_task(INACTIVE);
  
  chassis.turn_to_point(-60.516, -46.973);
  start_intake();
  // chassis.drive_to_point(-40.299, -46.973);
  // chassis.drive_max_voltage = 6;
  chassis.drive_to_point(-60.516, -46.973);
  task::sleep(500);
  chassis.drive_max_voltage = 8;
  chassis.turn_to_point(-47.818, -57.727);
  chassis.drive_to_point(-47.818, -57.727);
  
  chassis.turn_to_point(-58, -61, true);
  chassis.drive(-10);
  assembly.mogo_clamp_piston.set(false);
  task::sleep(150);
  default_constants();
  
  chassis.drive(10);
  stop_intake();
  
  chassis.turn_to_point(-47.336, 27.239, true);
  chassis.drive_to_point(-47.336, 15.239);
  chassis.drive_max_voltage = 6;
  chassis.drive_to_point(-47.336, 21.239);
  chassis.drive_max_voltage = 8;

  assembly.mogo_clamp_piston.set(true);
  mogo_constants();
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
  chassis.drive(-13);
  // chassis.drive_to_point(0, 48);
  LB_task(INACTIVE);


  chassis.turn_to_point(-60.348, 46.854);
  // chassis.drive_to_point(-40.299, 46.973);
  // chassis.drive_max_voltage = 6;  
  chassis.drive_to_point(-60.348, 46.854);
  task::sleep(500);
  chassis.drive_max_voltage = 8;

  chassis.turn_to_point(-45.649, 60.589);
  chassis.drive_to_point(-45.649, 60.589);

  chassis.turn_to_point(-61.312, 62.276, true);
  chassis.drive(-13);
  assembly.mogo_clamp_piston.set(false);
  task::sleep(150);
  default_constants();
  chassis.drive(10);
  stop_intake();

  chassis.turn_to_point(47.194, 46.912);

  // chassis.set_coordinates(23.5, 47, 90);
  start_intake();

  LB_task(ACTIVE);
  chassis.drive_max_voltage = 12;
  chassis.drive_to_point(47.194, 46.912);

  chassis.turn_to_point(47, 0, true);
  chassis.drive_to_point(47, 10);
  chassis.drive_max_voltage = 6;
  chassis.drive(-10);
  chassis.drive_max_voltage = 8;
  stop_intake();
  assembly.mogo_clamp_piston.set(true);
  mogo_constants();

  chassis.turn_to_point(62, 0);
  chassis.drive_to_point(62, 0);

  drive_until_settled(8, 8);

  LB_task(36);
  chassis.drive(-8);
  task::sleep(100);
  chassis.drive(4);
  chassis.drive_to_point(47, 0);
  LB_task(INACTIVE);
  
  chassis.turn_to_point(47, -50);
  
  assembly.unjam_intake_task();
  start_intake();

  chassis.drive_to_point(47, -50);
  chassis.right_swing(15, true);
  chassis.drive(8);

  chassis.turn_to_point(22.786, -22.786);
  assembly._unjam_intake_task.stop();
  chassis.drive_max_voltage = 12;
  chassis.drive_to_point(22.786, -22.786);
  assembly.intake_motor.spin(fwd, 10, volt);
  intake_ring_halfway();

  chassis.turn_to_point(0.376, 0.106);
  chassis.drive_to_point(0.376, 0.106);
  // assembly.doinker_piston.set(true);
  start_intake();
  chassis.drive(4);
  task::sleep(300);
  stop_intake();
  chassis.turn_to_point(23.75, 23.239);
  chassis.drive_to_point(23.75, 23.239);
  start_intake();
  // assembly.doinker_piston.set(false);

  // chassis.turn_to_point(47.364, 62.341);

  chassis.drive_to_point(47.364, 62.341);
  
  chassis.turn_to_point(61.992, 70.059, true);
  
  assembly.mogo_clamp_piston.set(false);
  default_constants();
  chassis.drive_with_voltage(-12, -12);
  stop_intake();
  task::sleep(650);
  chassis.stop_drive(hold);

  chassis.drive_max_voltage = 12;
  chassis.drive_to_point(36.08, 38.439);
  stop_intake();

  chassis.turn_to_point(64.5, -64.5);
  stop_intake();
  drive_until_settled(12, 12, 2500, 500);
  
  LB_task(DESCORE_TOP);


  vex::task stop([](){
    while(1) {
      assembly.intake_motor.stop(brake);
      task::sleep(5);
    }
  return 0;});

  chassis.drive_to_point(18.5, -18.5);
  chassis.turn_to_point(0, 0, true);
  drive_until_settled(-6, -6, 2500, 0);
  chassis.stop_drive(coast);

  return "";
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
  if (assembly.LB_goto_state < ACTIVE && std::abs(assembly.LB_encoder.position(deg) - ACTIVE) < 30 ) {
    assembly.intake_motor.spinFor(-30, vex::rotationUnits::deg, true);
  }
  assembly.LB_goto_state = angle;
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