#include "vex.h"

using namespace vex;

pid_data data;
std::function<void()> test_func;

void test_drive() {
  data.variables = { {"drive_kp : ", chassis.drive_kp}, {"drive_ki: ", chassis.drive_ki}, {"drive_kd: ", chassis.drive_kd},
    {"heading_kp: ", chassis.heading_kp }, {"heading_ki: ", chassis.heading_ki}, {"heading_kd: ", chassis.heading_kd}
  };
  graph_scr->set_plot_bounds(360, 0, 0, 30, 0.2, 1);
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
  data.variables = { {"turn_kp: ", chassis.turn_kp}, {"turn_ki: ", chassis.turn_ki}, {"turn_kd: ", chassis.turn_kd} };
  graph_scr->set_plot_bounds(360, 0, 0, 30, 0.2, 1);
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
  data.variables = { {"swing_kp: ", chassis.swing_kp }, {"swing_ki: ", chassis.swing_ki }, {"swing_kd: ", chassis.swing_kd } };
  graph_scr->set_plot_bounds(360, 0, 0, 30, 0.2, 1);
  graph_scr->set_plot({
    [](double x){ return chassis.get_absolute_heading(); }, 
    [](double x){ return chassis.desired_heading; }},
    {{"ActualValue", 0x002E8B59}, 
    {"SetPoint", 0x00FA8072}}
  );

  test_func = [](){
    graph_scr->reset_graph();
    graph_scr->graph();
    
    chassis.left_swing_to_angle(90);
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

void test_spin_all_motors(std::vector<hzn::motor_group> motor_chains) {
    for (hzn::motor_group& motor_chain : motor_chains) {
      for (vex::motor& motor : motor_chain.motors) {
          Brain.Screen.clearLine();
          Brain.Screen.print("Spinning motor at PORT %d", (motor.index() + 1));
          Brain.Screen.newLine();
          motor.spinFor(1, vex::sec);
          vex::task::sleep(2000);
      }
      vex::task::sleep(1000);
    }
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


void test_serial_output() {
    double count = 0;
    while (true) {
        printf("%f\n", count);
        fflush(stdout);
        vex::task::sleep(100);
        count++;
    }
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

int print_vector_to_serial(const std::string& name, const std::vector<float>& vector) {
    printf("%s\n", name.c_str());
    fflush(stdout);
    vex::task::sleep(100);

    for(size_t i = 0; i < vector.size(); ++i) {
      printf("%f\n", vector[i]);
      fflush(stdout);
      vex::task::sleep(50);
    }
    printf("%f\n\n");
    fflush(stdout);
    vex::task::sleep(50);
    return 0;
}

void print_coordinates(){
  chassis.set_coordinates(0, 0, 0);
  // vex::distance dis = vex::distance(vex::PORT21);
  while(true){
    Brain.Screen.clearScreen();
    Brain.Screen.printAt(0, 50, "X: %f", chassis.get_X_position());
    Brain.Screen.printAt(0, 70, "Y: %f", chassis.get_Y_position());
    Brain.Screen.printAt(0, 90, "Heading: %f", chassis.get_absolute_heading());
    Brain.Screen.printAt(0, 110, "ForwardTracker: %f", chassis.get_ForwardTracker_position());
    Brain.Screen.printAt(0, 130, "SidewaysTracker: %f", chassis.get_SidewaysTracker_position());
    // float hypotnuse = dis.objectDistance(vex::inches);
    // Brain.Screen.printAt(0, 150, "Distance sensor: %f", hypotnuse);
    // float theta = to_rad(chassis.get_absolute_heading());

    // Brain.Screen.printAt(0, 170, "X adjusted: %f", -hypotnuse * sin(theta));
    // Brain.Screen.printAt(0, 190, "Y adjusted: %f", 62 + (hypotnuse * cos(theta) - 7.7));
    vex::task::sleep(20);
  }
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
}