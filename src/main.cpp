#include "vex.h"

using namespace vex;

vex::competition Competition;
int current_auton_selection = 0;
bool auto_started = false;

void pre_auton() {
  init();
  default_constants();

  while(!auto_started) {
    Brain.Screen.printAt(5, 20, "Absolute Heading:");
    Brain.Screen.printAt(5, 40, "%f", chassis.get_absolute_heading());
    Brain.Screen.printAt(5, 80, "Auton:");
    switch(current_auton_selection){
      case 0:
        Brain.Screen.printAt(5, 100, "Goalside Red  ");
        goalside_red(true);
        break;
      case 1:
        Brain.Screen.printAt(5, 100, "Goalside Blue ");
        goalside_blue(true);
        break;
      case 2:
        Brain.Screen.printAt(5, 100, "Ringside Red  ");
        ring_side_red(true);
        break;
      case 3:
        Brain.Screen.printAt(5, 100, "Ringside Blue  ");
        ring_side_blue(true);
        break;
      case 4:
        Brain.Screen.printAt(5, 100, "Winpoint Red  ");
        win_point_red(true);
        break;
      case 5:
        Brain.Screen.printAt(5, 100, "Winpoint Blue ");
        win_point_blue(true);
        break;
      case 6:
        Brain.Screen.printAt(5, 100, "SAWP Red      ");
        solo_win_point_red(true);
        break;
        case 7:
        Brain.Screen.printAt(5, 100, "SAWP Blue     ");
        // solo_win_point_blue(true);
        break;
      case 8:
        Brain.Screen.printAt(5, 100, "No Auton      ");
        break;
    }
    if(Brain.Screen.pressing()){
      while(Brain.Screen.pressing()) {}
      current_auton_selection++;
    } else if (current_auton_selection == 9){
      current_auton_selection = 0;
    }
    vex::task::sleep(10);
  }
}

void auton(void) {
  auto_started = true;

  switch (current_auton_selection) { 
    case 0:
      goalside_red();
      break;
    case 1:
      goalside_blue(true);
      break;
    case 2:
      ring_side_red(true);
      break;
    case 3:
      ring_side_blue(true);
      break;
    case 4:
      win_point_red(true);
      break;
    case 5:
      win_point_blue(true);
      break;
    case 6:
      solo_win_point_red(true);
      break;
    case 7:
      // solo_win_point_blue(true);
      break;
    default:
      break;
 }
}

void user_control(void) {
  assembly.initialize_user_control();

  while(1) {
    chassis.split_arcade();
    assembly.select_ring_sort_mode();
    assembly.intake();
    assembly.lady_brown();
    assembly.mogo_clamp();
    assembly.doinker();
    // assembly.match_timer();
    assembly.align_robot();

    vex::task::sleep(5);
  }
}

void UI_temp(void) {
  // auto btn = UI_crt_btn(UI_crt_rec(30, 30, 100, 100, vex::color::red, UI_distance_units::pixels), nullptr);
  //   btn->set_states(UI_crt_rec(30, 30, 100, 100, vex::color::blue, UI_distance_units::pixels), UI_crt_rec(30, 30, 100, 100, vex::color::green, UI_distance_units::pixels));
  
  // auto tgl = UI_crt_tgl(UI_crt_rec(130, 130, 100, 100, vex::color::red, UI_distance_units::pixels), nullptr);
  //   tgl->set_states(UI_crt_rec(130, 130, 100, 100, vex::color::blue, UI_distance_units::pixels), UI_crt_rec(130, 130, 100, 100, vex::color::green, UI_distance_units::pixels));
  
  // auto scr = UI_crt_scr(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
  // scr->add_UI_components({btn, tgl});

  // UI_render_queue = {scr};
  // UI_render();

  // vex::thread UI(test_palette);
}

void skills_driver_run() {
  Controller.Screen.setCursor(1, 1);
  Controller.Screen.print("SKILLS DRIVER RUN               ");
  task::sleep(1000);
  Controller.Screen.setCursor(1, 1);
  Controller.Screen.print("             3                 ");
  Controller.rumble(".");
  task::sleep(1000);
  Controller.Screen.setCursor(1, 1);
  Controller.Screen.print("             2                 ");
  Controller.rumble(".");
  task::sleep(1000);
  Controller.Screen.setCursor(1, 1);
  Controller.Screen.print("             1                 ");
  Controller.rumble(".");
  task::sleep(1000);
  Controller.Screen.setCursor(1, 1);
  Controller.Screen.print("            GO                 ");
  Controller.rumble("-");
  Controller.Screen.setCursor(1, 1);
  Controller.Screen.print("                               ");

  vex::task time_left([](){
    while(1) {
      Controller.Screen.setCursor(1, 1);
      Controller.Screen.print("           ");
      Controller.Screen.print(assembly.time_remaining);
      Controller.Screen.print("  ");
    }
    return 0;
  });

  user_control();
}

struct pid_data
{
  std::vector<std::reference_wrapper<float>> variables = {
    lead_scalar, current_scalar
  };

  int index = 0;
  float modifier = 1;
  float modifer_scale = 1;
  bool needs_update = false;
};

pid_data data;

int get_flicker_index(const std::string &valueStr, int place) {
    int dotPos = valueStr.find('.');
    if (dotPos == (int)std::string::npos) {
        int idx = valueStr.size() - 1 - place; 
        return idx;
    }
    else {
      int idx;
      if (place > 0) {
          idx = dotPos + place; 
      }
      else {
          idx = dotPos - 1 + place;
      }
      return idx;
    }
}

void PID_tuner() {
  // Constants to Tune
  vex::task turn_test;
  chassis.set_turn_constants(12, .437, .0295, 3.486, 15, 1, 300, 3000);

  vex::task update_screen([](){
  static int flicker = 0;

  while(1) {
    for(int i = 0; i < data.variables.size(); ++i) {
      Controller.Screen.setCursor(i+1, 1);
      std::string var = to_string_float(data.variables[i]);
      if(data.index == i) {
        flicker++;
        if(flicker % 2 == 0) {
          int place = static_cast<int>(-std::log10(1.0 / data.modifer_scale));
          int idx = get_flicker_index(var, place);

          if(idx >= 0 && idx < (int)var.size()) {
            if(std::isdigit(var[idx])) {
              if(var[idx] == '1') {
                var[idx] = '-';
              } else {
                var[idx] = '_';
              }
            }
          }
        }
        else{}
      }
      Controller.Screen.print(var.c_str());
      
      if (data.index == i) { 
        if (data.needs_update) {
          data.variables[i] += data.modifier;
          data.needs_update = false;
        }
        Controller.Screen.print("<"); 
      } else { 
        Controller.Screen.print("     "); 
      }
    }

    this_thread::sleep_for(20);
    }
    return 0;
  });

  while(1) {
    if (Controller.ButtonUp.pressing()) {
      if (data.index > 0) { data.index--; }
      task::sleep(200);
    }
    if (Controller.ButtonDown.pressing()) {
      if (data.index < 2) { data.index++; }
      task::sleep(200);
    }
    if (Controller.ButtonRight.pressing()) {
      data.modifier = 1 / data.modifer_scale;
      data.needs_update = true;
      task::sleep(200);
    }
    if (Controller.ButtonLeft.pressing()) {
      data.modifier = -1 / data.modifer_scale;
      data.needs_update = true;
      task::sleep(200);
    }
    if (Controller.ButtonY.pressing()) {
      data.modifer_scale /= 10;
      if (data.modifer_scale < 1) {
        data.modifer_scale = 1;
      }
      task::sleep(200);
    }
    if (Controller.ButtonA.pressing()) {
      data.modifer_scale *= 10;
      if (data.modifer_scale > 100000) {
        data.modifer_scale = 100000;
      }
      task::sleep(200);
    }
    // Testing the constants
    if (Controller.ButtonX.pressing()) {
      turn_test = vex::task([](){
        chassis.set_coordinates(-26, -24, 90);
        chassis.turn_to_point(22, -48);
      
        standardized_vector_movement(0.25, curveNumeroDos);
        // chassis.turn_on_PID(5);
        // task::sleep(200);
        // chassis.turn_on_PID(30);
        // task::sleep(200);
        // chassis.turn_on_PID(90);
        // task::sleep(200);
        // chassis.turn_on_PID(225);
        // task::sleep(200);
        // chassis.turn_on_PID(0);
        return 0;
      });
    }
    if (Controller.ButtonB.pressing()) {
      chassis.stop_drive(vex::coast);
      turn_test.stop();
      task::sleep(200);
    }
    task::sleep(20);
  }
}


int main() {
  init();
  default_constants();
  Controller.Screen.clearScreen();
  //solo_win_point_red(true);
  //task::sleep(10000);
  
  // task::sleep(1000);
  // skills()
  // solo_win_point();
  // win_point();
  // PID_tuner();
  vex::task stop_motors([](){
    while(1) {
      while(Controller.ButtonA.pressing()) {
        chassis.stop_drive(brake);
      }
      task::sleep(50);
    }
    return 0;
  });
  chassis.set_coordinates(-26, -24, 90);
  chassis.turn_to_point(22, -48);

  standardized_vector_movement(0.4, curveNumeroDos);
  // assembly.mogo_clamp_piston.set(true);
  // PID_tuner();
  
  // test_spin_all_motors({chassis.left_drive, chassis.right_drive});
  // skills();
  // skills_driver_run();
  // chassis.set_coordinates(-59, 0, 90);
  // chassis.set_coordinates(0, 0, 0);
  // chassis.drive_max_voltage = 6;

  // 3 inches y
  // 5 inches x


  // while(1) {
  //   if (Controller.ButtonX.pressing()) {
  //       chassis.drive_on_PID(5, 0);
  //       if (chassis.get_absolute_heading() > 0) {
  //         chassis.left_swing_to_angle(0);
  //       } else {
  //         chassis.right_swing_to_angle(0);
  //       }
  //     }
  //     vex::task::sleep(20);
  //   }

  // chassis.set_coordinates(-61, 0, 90);

  // skills();
  // user_control();
  // chassis.set_coordinates(-61.071, 0, 90);

  // user_control();
  // chassis.turn_max_voltage = 8;
  // chassis.drive_with_voltage(3, -3);
  // task::sleep(300);
  // while(chassis.get_absolute_heading() > 0) {
  //   if (chassis.get_absolute_heading() > 0 && chassis.get_absolute_heading() < 2) {
  //     break;
  //   }
  //   task::sleep(10);
  // }
  // chassis.stop_drive(hold);
  


  // four_ring_red();
  // vex::thread odom(print_coordinates);
  // task::sleep(2000);
  // win_point();

  // vex::task hook_pos([](){
  //   while(1) {
  //     // Brain.Screen.printAt(30, 30, "%d", assembly.unjam_intake);
  //   }
  //   return 0;
  // });

  // user_control();

  // // initialize_auton();
  // task::sleep(2000);
  // four_ring_red();
  // user_control();


  // Competition.autonomous(auton);
  // Competition.drivercontrol(user_control);

  // pre_auton();

  // while (true) {
  //   vex::wait(100, vex::msec);
  // }
}