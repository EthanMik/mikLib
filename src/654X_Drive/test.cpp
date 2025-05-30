#include "vex.h"

using namespace vex;

pid_data data;
std::function<void()> test_func;

void test_drive() {
  data.variables = { {"drive_kp : ", chassis.drive_kp}, {"drive_ki: ", chassis.drive_ki}, {"drive_kd: ", chassis.drive_kd},
    {"heading_kp: ", chassis.heading_kp }, {"heading_ki: ", chassis.heading_ki}, {"heading_kd: ", chassis.heading_kd}
  };
  graph_scr->set_plot_bounds(360, 0, 0, 5000, 1, 1);
  graph_scr->set_plot({
    [](double x){ return chassis.get_ForwardTracker_position(); }, 
    [](double x){ return chassis.desired_distance; }
  },
    {{"D_Actual", 0x002E8B59}, 
    {"D_SetPoint", 0x00FA8072}}
  );

  test_func = [](){
    graph_scr->reset_graph();
    graph_scr->graph();

    chassis.drive_on_PID(6);
    chassis.drive_on_PID(12);
    chassis.drive_on_PID(18);
    chassis.drive_on_PID(-36);
  };

  PID_tuner();
}

void test_turn() {
  mogo_constants();
  data.variables = { {"turn_kp: ", chassis.turn_kp}, {"turn_ki: ", chassis.turn_ki}, {"turn_kd: ", chassis.turn_kd} };
  graph_scr->set_plot_bounds(360, 0, 0, 5000, 1, 1);
  graph_scr->set_plot({
    [](double x){ return chassis.get_absolute_heading(); }, 
    [](double x){ return chassis.desired_heading; }},
    {{"ActualValue", 0x002E8B59}, 
    {"SetPoint", 0x00FA8072}}
  );

  test_func = [](){
    graph_scr->reset_graph();
    graph_scr->graph();

    chassis.turn_on_PID(5);
    chassis.turn_on_PID(30);
    chassis.turn_on_PID(90);
    chassis.turn_on_PID(225);
    chassis.turn_on_PID(0);
  };

  PID_tuner();
}

void test_swing() {
  mogo_constants();
  data.variables = { {"swing_kp: ", chassis.swing_kp }, {"swing_ki: ", chassis.swing_ki }, {"swing_kd: ", chassis.swing_kd } };
  graph_scr->set_plot_bounds(360, 0, 0, 3000, 1, 1);
  graph_scr->set_plot({
    [](double x){ return chassis.get_absolute_heading(); }, 
    [](double x){ return chassis.desired_heading; }},
    {{"ActualValue", 0x002E8B59}, 
    {"SetPoint", 0x00FA8072}}
  );

  test_func = [](){
    graph_scr->reset_graph();
    graph_scr->graph();
    
    chassis.left_swing_to_angle(110);
    chassis.right_swing_to_angle(0);
  };

  PID_tuner();
}

void test_full() {
  chassis.drive_on_PID(24);
  chassis.turn_on_PID(-45);
  chassis.drive_on_PID(-36);
  chassis.right_swing_to_angle(-90);
  chassis.drive_on_PID(24);
  chassis.turn_on_PID(0);
}

void test_odom() {
  chassis.set_coordinates(0, 0, 0);
  chassis.turn_to_point(24, 24);
  chassis.drive_to_point(24,24);
  chassis.drive_to_point(0,0);
  chassis.turn_on_PID(0);
}

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
  vex::task test;

  vex::task user_contol([](){
    while(1) {
      assembly.mogo_clamp();
      chassis.split_arcade();
      vex::this_thread::sleep_for(5);
    }
    return 0;
  });

  vex::task update_screen([](){
    static int flicker = 0;
    while(1) {
    data.max = std::max(3, data.index+1);
    data.min = data.max - 3;

    int j = 0;
    for(int i = data.min; i < data.max; ++i) {
      Controller.Screen.setCursor(j+1, 1);
      j++;
      std::string var = to_string_float(data.variables[i].second);
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
      Controller.Screen.print((data.variables[i].first + var).c_str());
      
      if (data.index == i) { 
        if (data.needs_update) {
          data.variables[i].second += data.modifier;
          data.needs_update = false;
        }
        Controller.Screen.print("<   "); 
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
      if (data.index < data.variables.size() - 1) { data.index++; }
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
    if (Controller.ButtonX.pressing()) {
      user_contol.suspend();
      test = vex::task([](){
        test_func();
        return 0;
      });
    }
    if (Controller.ButtonB.pressing()) {
      user_contol.resume();
      test.stop();
      chassis.stop_drive(vex::coast);
      task::sleep(200);
    }
    task::sleep(20);
  }
}

void config_spin_all_motors() {
  UI_select_scr(console_scr->get_console_screen()); 
  disable_user_control = true;
  vex::task spin_mtrs([](){
    for (hzn::motor& motor : chassis.left_drive.motor_constructor) { 
      std::string data = (motor.name + ": PORT" + to_string_int((motor.mtr.index() + 1)) + ", Dir: fwd");
      console_scr->add(std::string(data), [](){ return ""; });
      motor.mtr.spin(fwd, 2, volt);
      vex::task::sleep(1000);
      motor.mtr.stop();
      vex::task::sleep(1000);
    }
    for (hzn::motor& motor : chassis.right_drive.motor_constructor) {      
      std::string data = (motor.name + ": PORT" + to_string_int((motor.mtr.index() + 1)) + ", Dir: fwd");
      console_scr->add(std::string(data), [](){ return ""; });
      motor.mtr.spin(fwd, 2, volt);
      vex::task::sleep(1000);
      motor.mtr.stop();
      vex::task::sleep(1000);
    }
    disable_user_control = false;
    return 0;
  });
}

void config_motor_wattage() {
  console_scr->add("right_drive: ", []() { return chassis.right_drive.get_wattage(); });
  console_scr->add("left_drive: ", []() { return chassis.left_drive.get_wattage(); });

  for (size_t i = 0; i < chassis.left_drive.motors.size(); ++i) {
    size_t index = i;
    console_scr->add(chassis.left_drive.motor_constructor[index].name + ": ", [index]() { return chassis.left_drive.motors[index].power(); });
  }
  for (size_t i = 0; i < chassis.right_drive.motors.size(); ++i) {
    size_t index = i;
    console_scr->add(chassis.right_drive.motor_constructor[index].name + ": ", [index]() { return chassis.right_drive.motors[index].power(); });
  }

  UI_select_scr(console_scr->get_console_screen()); 
}

void config_motor_temp() {
  console_scr->add("right_drive: ", []() { return chassis.right_drive.get_temp(); });
  console_scr->add("left_drive: ", []() { return chassis.left_drive.get_temp(); });

  for (size_t i = 0; i < chassis.left_drive.motors.size(); ++i) {
    size_t index = i;
    console_scr->add(chassis.left_drive.motor_constructor[index].name + ": ", [index]() { return chassis.left_drive.motors[index].temperature(vex::temperatureUnits::fahrenheit); });
  }
  for (size_t i = 0; i < chassis.right_drive.motors.size(); ++i) {
    size_t index = i;
    console_scr->add(chassis.right_drive.motor_constructor[index].name + ": ", [index]() { return chassis.right_drive.motors[index].temperature(vex::temperatureUnits::fahrenheit); });
  }

  UI_select_scr(console_scr->get_console_screen()); 
}

void config_odom_data() {
  if (!chassis.position_tracking) {
    chassis.set_coordinates(0, 0, 0);
  }

  console_scr->add("X: ", [](){ return chassis.get_X_position(); });
  console_scr->add("Y: ", [](){ return chassis.get_Y_position(); });
  console_scr->add("Heading: ", [](){ return chassis.get_absolute_heading(); });
  console_scr->add("Forward_Tracker: ", [](){ return chassis.get_ForwardTracker_position(); });
  console_scr->add("Sideways_Tracker: ", [](){ return chassis.get_SidewaysTracker_position(); });

  UI_select_scr(console_scr->get_console_screen()); 
}


void config_skills_driver_run() {
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

  vex::task timer([](){
    float start_time = Brain.Timer.time(vex::timeUnits::sec);
    float current_time = start_time;
    float max_time = 60;
    float elapsed_time = 0;
    int time_remaining = 0;
    while(1) {
      current_time = Brain.Timer.time(vex::timeUnits::sec);
      elapsed_time = current_time - start_time;
      time_remaining = max_time - elapsed_time;

      switch (time_remaining)
      {
      case 30:
        Controller.rumble((".-"));
      case 15:
        Controller.rumble(("."));
        break;
      case 5:
        Controller.rumble((".-"));
        break;
      case 0:
        Controller.rumble(("."));
        chassis.stop_drive(vex::brake);
        disable_user_control = true;
        std::abort();
        break;
      default:
        break;
      }
      
      Controller.Screen.setCursor(1, 1);
      Controller.Screen.print("           ");
      Controller.Screen.print(time_remaining);
      Controller.Screen.print("  ");
    }
    return 0;
  });
}

void config_test_three_wire_port(port port) {
  vex::digital_out dig_out = Brain.ThreeWirePort.Port[port];
  dig_out.set(!dig_out.value());
}

void print(float num) {
    printf("%f\n", num);
    fflush(stdout);
}
void print(std::string str) {
    printf("%s\n", str.c_str());
    fflush(stdout);
}
void print(const char* str) {
    printf("%s\n", str);
    fflush(stdout);
}
void print(int num) {
    printf("%d\n", num);
    fflush(stdout);
}
void print(bool boolean) {
    printf("%d\n", boolean);
    fflush(stdout);
}
void print(uint32_t num) {
    printf("%u\n", num);
    fflush(stdout);
}
void print(double num) {
    printf("%f\n", num);
    fflush(stdout);
}
void print(long num) {
    printf("%ld\n", num);
    fflush(stdout);
}
void print(long long num) {
    printf("%lld\n", num);
    fflush(stdout);
}
void print(unsigned long long num) {
    printf("%llu\n", num);
    fflush(stdout);
}
void print(unsigned int num) {
    printf("%u\n", num);
    fflush(stdout);
}
void print(char c) {
    printf("%c\n", c);
    fflush(stdout);
}
