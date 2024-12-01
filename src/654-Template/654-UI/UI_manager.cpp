#include "vex.h"

void UI_run() {    
  auto main_bg = UI_crt_bg(UI_crt_img("background_main.png", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, UI_distance_units::pixels));
  
  auto main_bg_scr = UI_crt_scr(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
  main_bg_scr->add_UI_component(main_bg);

  auto selector_panel_scr = UI_crt_scr(0, 0, SCREEN_WIDTH + 100, 45);
  selector_panel_scr->add_scroll_bar(UI_crt_rec(0, 0, 40, 3, 0x00434343, UI_distance_units::pixels), screen::alignment::BOTTOM);

  UI_crt_console_scr();
  UI_console_scr_add();
  
  auto console_btn = UI_crt_btn(
    UI_crt_img("console_button.png", 0, 0, 160, 50, UI_distance_units::pixels),
    UI_crt_img("console_button_pressed.png", 0, 0, 160, 50, UI_distance_units::pixels),
    [=](){ UI_display_screens({UI_console_scr, selector_panel_scr}); }
  );

  selector_panel_scr->add_UI_components({console_btn});

  UI_display_screens({main_bg_scr, selector_panel_scr});
}

void UI_click(std::shared_ptr<screen> scr) {
  // std::shared_ptr<UI_component> black = std::make_shared<image>(shapes::RECTANGLE, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0x00000000, distance_units::pixels);
  
  while(scr->get_x_pos() > -130) {
    scr->set_x_pos(scr->get_x_pos() - 18);
    Brain.Screen.render();
    task::sleep(35);
    // black->render();
    scr->render();
  }

  UI_run();
}

void UI_display_screen(std::shared_ptr<screen> scr) {
  while(true) {
    scr->render();
    task::sleep(35);
    Brain.Screen.render();
  }
}

void UI_display_screens(const std::vector<std::shared_ptr<screen>>& render_queue) {
  while(true) {
    for (const auto& screen : render_queue) {
      screen->render();
    }
    task::sleep(35);
    Brain.Screen.render();
  }
}

void UI_run_toggles(screen* scr) {
  scr->execute_toggles();
}

int bruh() {
  return 1;
}