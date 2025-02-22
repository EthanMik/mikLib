#include "vex.h"

using namespace vex;

// static vex::task _intake_fallback_task;
// static vex::task _color_sort_task;
// static vex::task _intake_ring_halway_task;

// void initialize_auton() {
//   _intake_fallback_task = vex::task(intake_fallback_task);
//   _color_sort_task = vex::task(color_sort_task);
//   _intake_ring_halway_task = vex::task(intake_ring_halfway_task);

//   _intake_fallback_task.suspend();
//   _color_sort_task.suspend();
//   _intake_ring_halway_task.suspend();
// }

// int color_sort_task() {
//   while(1) {
//     if (assembly.ring_sort()) {
//       assembly.intake_motor.spin(fwd, 12, volt);
//     }
//     vex::this_thread::sleep_for(50);
//   }
//   return 0;
// }

// int intake_fallback_task() {
//     while (is_intake_fallback) {
//       double start = assembly.intake_encoder.position(deg);
//       vex::task::sleep(250);
//       double end = assembly.intake_encoder.position(deg);

//       if (end - start < 1) {
//           assembly.intake_motor.spinFor(directionType::rev, 150, rotationUnits::deg, 600, velocityUnits::rpm, true);
//           assembly.intake_motor.spin(directionType::fwd, 12, voltageUnits::volt);
//       }
//       vex::this_thread::sleep_for(50);
//     }
//     return 0;
// }

// int intake_ring_halfway_task() {
//   int timeout_start = Brain.Timer.time(vex::timeUnits::sec);
//    while (1) {
//       assembly.intake_motor.spin(fwd, 11, volt);
//       if (assembly.ring_distance_sensor.objectDistance(vex::distanceUnits::mm) < 120) {
//         _intake_fallback_task.suspend();

//         assembly.intake_motor.stop();
//         vex::this_thread::sleep_for(100);
//         _intake_ring_halway_task.suspend();
//       }
//       if (Brain.Timer.time(vex::timeUnits::sec) - timeout_start > 5) {
//         _intake_ring_halway_task.suspend();
//         _intake_fallback_task.suspend();
//         timeout_start = Brain.Timer.time(vex::timeUnits::sec);
//       }
//       vex::this_thread::sleep_for(50);

//   }
//   return 0;
// }

void four_ring_red(void) {
  static bool is_intake_fallback = false;

  assembly.select_ring_sort_mode(color_sort::BLUE);
  
  vex::task _color_sort_task([](){
    while(1) {
      if (assembly.ring_sort()) {
        assembly.intake_motor.spin(fwd, 12, volt);
      }
      vex::this_thread::sleep_for(50);
    }
    return 0;
  });

  vex::task _intake_fallback_task([](){
    while (is_intake_fallback) {
      double start = assembly.intake_encoder.position(deg);
      vex::task::sleep(250);
      double end = assembly.intake_encoder.position(deg);

      if (end - start < 1) {
          assembly.intake_motor.spinFor(directionType::rev, 150, rotationUnits::deg, 600, velocityUnits::rpm, true);
          assembly.intake_motor.spin(directionType::fwd, 12, voltageUnits::volt);
      }
      vex::this_thread::sleep_for(50);
    }
    return 0;
  });

  // Deploy piston and grab rings, and pull back
  assembly.rush_piston.set(true);

  vex::task _intake_ring_halway_task([](){
    int timeout_start = Brain.Timer.time(vex::timeUnits::sec);
    while (1) {
        assembly.intake_motor.spin(fwd, 9.5, volt);
        if (assembly.ring_color_sensor.isNearObject()) {
          assembly.intake_motor.stop();
          vex::this_thread::sleep_for(100);
          break;
        }
        if (Brain.Timer.time(vex::timeUnits::sec) - timeout_start > 5) {
          break;
        }
        vex::this_thread::sleep_for(50);

    }
    return 0;
  });

  chassis.drive_on_PID(43);
  chassis.drive_on_PID(-18);  

  // Pull back through rings and clamp goal
  chassis.turn_max_voltage = 8;
  chassis.turn_on_PID(30);
  chassis.drive_max_voltage = 8;
  chassis.drive_on_PID(-13);
  task::sleep(250);
  assembly.rush_piston.set(false);
  chassis.turn_on_PID(237);
  chassis.drive_max_voltage = 6;
  chassis.drive_on_PID(-22);
  assembly.mogo_clamp_piston.set(true);
  task::sleep(100);
  
  // Turn to stack of 3 rings
  chassis.turn_on_PID(280);
  
  is_intake_fallback = true;
  assembly.intake_motor.spin(fwd, 12, volt);

  // Intake rings and turn to preload
  chassis.drive_max_voltage = 6;
  chassis.drive_on_PID(24);
  task::sleep(1000);
  chassis.turn_settle_time = 500;
  chassis.turn_on_PID(143);

  chassis.drive_max_voltage = 8;

  // Intake preload and intake double stack
  chassis.drive_on_PID(34);
  _intake_fallback_task.stop();
  _intake_ring_halway_task.stop();
  chassis.turn_on_PID(112);
  chassis.drive_max_voltage = 4;
  chassis.drive_on_PID(35);
  assembly.doinker_piston.set(true);
}

void four_ring_blue(void) {
  chassis.drive_max_voltage = 5;
  chassis.drive_on_PID(-31);
  assembly.mogo_clamp_piston.set(true);
  task::sleep(1000);
  assembly.intake_motor.spin(fwd, 12, volt);
  task::sleep(5000);
  
  assembly.intake_motor.stop();

}
void one_ring_red(void) {
  assembly.select_ring_sort_mode(color_sort::BLUE);

  chassis.drive_max_voltage = 5;
  chassis.drive_on_PID(-31);
  assembly.mogo_clamp_piston.set(true);
  task::sleep(1000);
  assembly.intake_motor.spin(fwd, 12, volt);
  task::sleep(5000);
  
  assembly.intake_motor.stop();

}
void one_ring_blue(void) {
  assembly.select_ring_sort_mode(color_sort::RED);

  chassis.drive_max_voltage = 5;
  chassis.drive_on_PID(-31);
  assembly.mogo_clamp_piston.set(true);
  task::sleep(1000);
  assembly.intake_motor.spin(fwd, 12, volt);
  task::sleep(5000);
  
  assembly.intake_motor.stop();
}

void skills(void) {
assembly.intake_motor.spin(fwd, 12, volt);
task::sleep(400);
assembly.intake_motor.stop();

chassis.turn_to_point(-47.577, -0.858);
chassis.drive_to_point(-47.577, -0.858);

chassis.turn_to_point(-47.577, -24.232, true);
chassis.drive_max_voltage = 5;
chassis.drive_to_point(-47.577, -24.232);
assembly.mogo_clamp_piston.set(true);
task::sleep(400);
chassis.drive_max_voltage = 8;

chassis.turn_to_point(-23.48, -23.991);
assembly.intake_motor.spin(fwd, 12, volt);
chassis.drive_to_point(-23.48, -23.991);

chassis.turn_to_point(0.135, -47.124);
chassis.drive_to_point(0.135, -47.124);

chassis.turn_to_point(23.75, -47.365);
chassis.drive_to_point(23.75, -47.365);

chassis.turn_to_point(0.135, -47.365);
chassis.drive_to_point(0.135, -47.365);

chassis.turn_to_point(-0.106, -63.51);
chassis.drive_to_point(-0.106, -63.51);

}

void path_test(void) {
  chassis.set_coordinates(-55.3, -131.9, 0);
}

void win_point(void) {
chassis.set_coordinates(-59.947, 12.311, 230);
assembly.move_LB_to_angle(SCORING);
assembly.unjam_intake = false;

vex::task down = vex::task([](){
  assembly.move_LB_to_angle(INACTIVE);
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


chassis.turn_to_point(-21.186, 24.402, true);
chassis.drive_max_voltage = 6;
chassis.drive_to_point(-21.186, 24.402);

assembly.mogo_clamp_piston.set(true);
mogo_constants();
task::sleep(200);

chassis.turn_to_point(-8.891, 37.832);
assembly.intake_motor.spin(fwd, 12, volt);
chassis.drive_to_point(-8.891, 37.832);

assembly.unjam_intake = true;
chassis.right_swing_to_angle(0);

chassis.drive_to_point(-8.05, 60.8);

}
