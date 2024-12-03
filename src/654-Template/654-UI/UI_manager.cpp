#include "vex.h"

std::vector<std::shared_ptr<screen>> UI_render_queue;

void UI_run() {    
  auto main_bg = UI_crt_bg(UI_crt_img("background_main.png", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, UI_distance_units::pixels));
  
  auto main_bg_scr = UI_crt_scr(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
  main_bg_scr->add_UI_component(main_bg);

  auto selector_panel_scr = UI_crt_scr(0, 0, SCREEN_WIDTH + 100, 45);
  selector_panel_scr->add_scroll_bar(UI_crt_rec(0, 0, 40, 3, 0x00434343, UI_distance_units::pixels), screen::alignment::BOTTOM);

  UI_crt_console_scr();

  for (int i = 0; i < 20; ++i) {
    UI_console_scr_add();
  }

  auto console_btn = UI_crt_tgl(
    UI_crt_img("console_button.png", 0, 0, 160, 45, UI_distance_units::pixels),
    UI_crt_img("console_button_pressed.png", 0, 0, 160, 45, UI_distance_units::pixels),
    nullptr, 1
  );
  console_btn->set_callback([=](){ 
      UI_execute_selector_toggles(console_btn, selector_panel_scr, true);
      UI_display_screens({UI_console_scr, selector_panel_scr}); 
    } 
  );

  auto auton_btn = UI_crt_tgl(
    UI_crt_img("console_button.png", 160, 0, 160, 45, UI_distance_units::pixels),
    UI_crt_img("console_button_pressed.png", 160, 0, 160, 45, UI_distance_units::pixels),
    nullptr, 1
  );
  auton_btn->set_callback([=](){ 
      UI_execute_selector_toggles(auton_btn, selector_panel_scr, true);
      UI_display_screens({main_bg_scr, selector_panel_scr}); 
    } 
  );

  auto config_btn = UI_crt_tgl(
    UI_crt_img("console_button.png", 320, 0, 160, 45, UI_distance_units::pixels),
    UI_crt_img("console_button_pressed.png", 320, 0, 160, 45, UI_distance_units::pixels),
    nullptr, 1
  );
  config_btn->set_callback([=](){ 
      UI_execute_selector_toggles(config_btn, selector_panel_scr, true);
      UI_display_screens({main_bg_scr, selector_panel_scr}); 
    } 
  );

  selector_panel_scr->add_UI_components({console_btn, auton_btn, config_btn});

  UI_render_queue = {UI_console_scr, selector_panel_scr};
  UI_display_render_queue();
}

void UI_display_screen(std::shared_ptr<screen> scr) {
  while(true) {
    scr->render();
    // task::sleep(35);
    Brain.Screen.render(true, false);
  }
}

void UI_display_render_queue() {
  while(true) {
    for (const auto& screen : UI_render_queue) {
      screen->render();
    }
    // task::sleep(35);
    Brain.Screen.render(true, false);
  }
}

void UI_execute_selector_toggles(std::shared_ptr<UI_component> tgl, std::shared_ptr<screen> scr, bool lock_toggles) {
  int tgl_id = tgl->get_ID();
  if (tgl_id <= 0) { return; }

  auto* toggle_component = static_cast<toggle*>(tgl.get());

  if (toggle_component->get_toggle_state() == true && lock_toggles) {
    toggle_component->lock_toggle();
  }

  for (const auto& component : scr->get_UI_components()) {
    if (component == tgl) continue;
    if (tgl_id == component->get_ID()) {
      auto* toggle_component = static_cast<toggle*>(component.get());
      toggle_component->unpress();
    }
  }
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

int bruh() {
  return 1;
}