#include "vex.h"

void UI_manager::run() {    
    // std::unordered_map<std::function<void()>, int> id;
    // std::vector<std::vector<int>> states;

    std::shared_ptr<UI_component> background = std::make_shared<image>("background.png", 0.0, 0.0, 5, 2.5, distance_units::pixels);

    screen* start_screen = new screen(0, 0, 700, 240);
    start_screen->add_UI_component(background);

    // screen* print_values_screen_1 = new screen(0, 0, 480, 240, {background});
    // screen* macros_screen_1 = new screen(0, 0, 480, 240, {background});
    // screen* drive_mode_screen_1 = new screen(0, 0, 480, 240, {background});

    std::shared_ptr<UI_component> print_values = std::make_shared<button>("print_values_button.png", "print_values_button_pressed.png", 30, 200, 50, 50, distance_units::pixels, std::function<void()>(UI_manager::click));
    std::shared_ptr<UI_component> print_values1 = std::make_shared<button>("print_values_button.png", "print_values_button_pressed.png", 100, 200, 50, 50, distance_units::pixels, std::function<void()>(UI_manager::click));
    std::shared_ptr<UI_component> print_values2 = std::make_shared<button>("print_values_button.png", "print_values_button_pressed.png", 170, 200, 50, 50, distance_units::pixels, std::function<void()>(UI_manager::click));
    std::shared_ptr<UI_component> print_values3 = std::make_shared<button>("print_values_button.png", "print_values_button_pressed.png", 240, 200, 50, 50, distance_units::pixels, std::function<void()>(UI_manager::click));
    // button print_values = button("print_values_button.png", "print_values_button_pressed.png", 0.18, 2.08, 1.36, 0.36, distance_units::inches, std::function<void(screen*)>(UI_manager::display_screen), print_values_screen_1);
    // button macro = button("macros_button.png", "macros_button_pressed.png", 1.82, 2.08, 1.36, 0.36, distance_units::inches, std::function<void(screen*)>(UI_manager::display_screen), macros_screen_1);
    // button drive_mode = button("drive_mode_button.png", "drive_mode_button_pressed.png", 3.46, 2.08, 1.36, 0.36, distance_units::inches, std::function<void(screen*)>(UI_manager::display_screen), drive_mode_screen_1);
    // start_screen->set_buttons({print_values, macro, drive_mode});
    start_screen->add_UI_components({print_values, print_values1, print_values2, print_values3});

    // std::shared_ptr<UI_component> _print_values = std::make_shared<button>("print_values_button.png", "print_values_button_pressed.png", 0.18, 1.78, 1.36, 0.36, distance_units::inches, std::function<void(screen*)>(UI_manager::display_screen), start_screen);
    // std::shared_ptr<UI_component> coordinates = std::make_shared<toggle>("coordinates_button.png", "coordinates_button_pressed.png", 0.18, 1.33, 1.36, 0.36, distance_units::inches, std::function<void()>(UI_manager::click));
    // std::shared_ptr<UI_component> clicking = std::make_shared<button>("coordinates_button.png", "coordinates_button_pressed.png", 0.18, 0.8, 1.36, 0.36, distance_units::inches, std::function<void(screen*)>(UI_manager::run_toggles), print_values_screen_1);

    // button temperature = button("temperature_button.png", "temperature_button_pressed.png", 0.18, 0.91, 1.36, 0.36, distance_units::inches, UI_manager::click);
    // button torque = button("torque_button.png", "torque_button_pressed.png", 0.18, 0.5, 1.36, 0.36, distance_units::inches, UI_manager::click);
    // print_values_screen_1->set_buttons({macro, drive_mode, _print_values, coordinates, temperature, torque});
    // print_values_screen_1->add_UI_components({_print_values, coordinates, clicking});

    // button _macros = button("macros_button.png", "macros_button_pressed.png", 1.82, 1.78, 1.36, 0.36, distance_units::inches, std::function<void(screen*)>(UI_manager::display_screen), start_screen);
    // button spin_all_motors = button("spin_all_motors_button.png", "spin_all_motors_button_pressed.png", 1.82, 1.32, 1.36, 0.36, distance_units::inches, UI_manager::click);
    // macros_screen_1->set_buttons({drive_mode, print_values, _macros, spin_all_motors});

    // button _drive_mode = button("drive_mode_button.png", "drive_mode_button_pressed.png", 3.46, 1.78, 1.36, 0.36, distance_units::inches, std::function<void(screen*)>(UI_manager::display_screen), start_screen);
    // button manual = button("manual_button.png", "manual_button_pressed.png", 3.46, 1.32, 1.36, 0.36, distance_units::inches, UI_manager::click);
    // drive_mode_screen_1->set_buttons({macro, print_values, _drive_mode, manual});

    display_screen(start_screen);
}

void UI_manager::click() {
  UI_manager ui;
  ui.run();
}

void UI_manager::display_screen(screen* scr) {
  while(true) {
    scr->render();
    task::sleep(20);
    Brain.Screen.render();
  }
}

void UI_manager::run_toggles(screen* scr) {
  scr->execute_toggles();
}

std::unordered_map<int, std::function<void()>> UI_manager::queue;

void UI_manager::setup_queue_whitelist(const std::vector<std::vector<int>>& states) {
  for (auto& state : states) {
    whitelist.push_back(state); 
  }
}

void UI_manager::add_function_to_queue(std::function<void()> function, int id) {
  queue.insert(std::make_pair(id, function));
  Brain.Screen.printAt(30, 60, "%d", id);
  function();
}

void UI_manager::flush_queue() {
  queue.clear();
}

UI_manager::~UI_manager() {
  delete start_screen;
  // delete print_values_screen_1;
  // delete macros_screen_1;
  // delete drive_mode_screen_1;
}
