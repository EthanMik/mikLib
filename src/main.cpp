#include "vex.h"

using namespace vex;
using namespace mik;

static int run_UI() {
  UI_controller_auton_selector();
  UI_render();
  return 0;
}

void pre_auton() {
  init();
  default_constants();
  task UI(run_UI);
}

void auton(void) {
  auton_scr->start_auton();
}

void user_control(void) {
  while (calibrating) { task::sleep(50); }

  // auton_scr->end_auton();
  assembly.initialize_user_control();

  // How you want your drivetrain to stop during driver
  chassis.set_brake_type(brakeType::coast);

  while (1) {
    if (!disable_user_control) {
      // Add your user control code here
      chassis.control(drive_mode::SPLIT_ARCADE_CURVED);

      assembly.select_ring_sort_mode();
      assembly.intake();
      assembly.lady_brown();
      assembly.mogo_clamp();
      assembly.doinker();
      assembly.align_robot();
    }
    vex::task::sleep(5);
  }
}

std::vector<point> path = {
    {  0.000,   0.000 },
    { -0.149,   1.994 },
    { -0.225,   3.993 },
    { -0.220,   5.992 },
    { -0.100,   7.988 },
    {  0.134,   9.974 },
    {  0.515,  11.937 },
    {  1.071,  13.857 },
    {  1.825,  15.708 },
    {  2.800,  17.452 },
    {  4.018,  19.036 },
    {  5.462,  20.416 },
    {  7.097,  21.564 },
    {  8.884,  22.459 },
    { 10.769,  23.123 },
    { 12.714,  23.582 },
    { 14.693,  23.867 },
    { 16.688,  24.004 },
    { 18.688,  24.018 },
    { 20.686,  23.931 },
    { 22.678,  23.760 },
    { 23.554,  23.664 },
    { 23.554,  23.664 },
};

std::vector<point> path_2 = {
    {  0.000,   0.000 },
    { -0.098,   1.997 },
    { -0.004,   3.993 },
    {  0.419,   5.944 },
    {  1.314,   7.722 },
    {  2.789,   9.053 },
    {  4.622,   9.831 },
    {  6.588,  10.189 },
    {  8.582,  10.324 },
    { 10.582,  10.364 },
    { 12.582,  10.406 },
    { 14.576,  10.542 },
    { 16.547,  10.871 },
    { 18.439,  11.506 },
    { 20.138,  12.549 },
    { 21.491,  14.014 },
    { 22.444,  15.768 },
    { 23.037,  17.676 },
    { 23.393,  19.643 },
    { 23.536,  21.637 },
    { 23.554,  23.664 },
    { 23.554,  23.664 },
};


int main() {
  Competition.autonomous(auton);
  Competition.drivercontrol(user_control);

  pre_auton();
  
  while (1) {
    task::sleep(100);
  }
}
