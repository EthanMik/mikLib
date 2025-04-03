#include "vex.h"

using namespace vex;

std::vector<std::vector<float>> graph_buffer;

void test_palette() {
  UI_init();
  UI_render();
}

void test() {
  Brain.Screen.printAt(30, 30, "test");
  exit(1);
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
      vex::task::sleep(2000);
    }
}

void test_print_motor_torque(std::vector<hzn::motor_group> motor_chains) {
  while (true) {
    int y_pos = 50;
    for (hzn::motor_group& motor_chain : motor_chains) {
      for (vex::motor& motor : motor_chain.motors) {
        Brain.Screen.printAt(0, y_pos, "PORT %d TORQUE: %d", motor.index() + 1, motor.torque());
        y_pos += 20;
      }
    }
    vex::task::sleep(2000);
  }
}

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
  // chassis.set_coordinates(0, 0, 0);
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

void add_to_graph_buffer(std::vector<float> data) {
  graph_buffer.push_back(data);
}

void clear_graph_buffer() {
  graph_buffer.clear();
}

void graph() {
  for (const auto &row : graph_buffer) {
    for (size_t i = 0; i < row.size(); ++i) {
      printf("%f", row[i]);
      if (i != row.size() - 1) {
        printf(",");
      } 
    }
    printf("\n");
    fflush(stdout);
    vex::task::sleep(100);
  }
  clear_graph_buffer();
}