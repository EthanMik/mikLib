#include "vex.h"

static std::vector<std::shared_ptr<screen>> UI_render_queue;
static std::vector<std::shared_ptr<screen>> UI_render_buffer;

static std::shared_ptr<UI_console_screen> console_scr = std::make_shared<UI_console_screen>();
std::shared_ptr<UI_auton_screen> auton_scr = std::make_shared<UI_auton_screen>();

static bool is_screen_swapping = false;

void UI_init() {
  auto main_bg = UI_crt_gfx(UI_crt_img("background_main.png", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, UI_distance_units::pixels));
  auto main_bg_scr = UI_crt_scr(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
  main_bg_scr->add_UI_component(main_bg);

  auto selector_panel_scr = UI_crt_scr(0, 0, SCREEN_WIDTH + 400, 45);
  selector_panel_scr->add_scroll_bar(UI_crt_rec(0, 0, 40, 3, 0x00434343, UI_distance_units::pixels), screen::alignment::BOTTOM);

  auto console_tgl = UI_crt_tgl(
    UI_crt_img("console_button.png", 0, 0, 160, 45, UI_distance_units::pixels),
    nullptr, 1
  );
  console_tgl->set_states(UI_crt_rec(160, 0, 160, 45, vex::color::red, UI_distance_units::pixels), UI_crt_img("console_button_pressed.png", 0, 0, 160, 45, UI_distance_units::pixels));
  console_tgl->set_callback([=](){ 
      UI_execute_selector_toggles(console_tgl, selector_panel_scr, true);
      UI_swap_screens({console_scr->get_console_screen(), selector_panel_scr}); 
    } 
  );

  auto auton_tgl = UI_crt_tgl(
    UI_crt_img("auton_button.png", 160, 0, 160, 45, UI_distance_units::pixels),
    nullptr, 1
  );
  auton_tgl->set_states(UI_crt_rec(160, 0, 160, 45, vex::color::red, UI_distance_units::pixels), UI_crt_img("auton_button_pressed.png", 160, 0, 160, 45, UI_distance_units::pixels));
  auton_tgl->set_callback([=](){ 
      UI_execute_selector_toggles(auton_tgl, selector_panel_scr, true);
      UI_swap_screens({auton_scr->get_auton_screen(), selector_panel_scr}); 
    } 
  );
  auto config_tgl = UI_crt_tgl(
    UI_crt_img("config_button.png", 320, 0, 160, 45, UI_distance_units::pixels),
    nullptr, 1
  );
  config_tgl->set_states(UI_crt_rec(160, 0, 160, 45, vex::color::red,UI_distance_units::pixels), UI_crt_img("config_button_pressed.png", 320, 0, 160, 45, UI_distance_units::pixels));
  config_tgl->set_callback([=](){ 
      UI_execute_selector_toggles(config_tgl, selector_panel_scr, true);
      UI_swap_screens({main_bg_scr, selector_panel_scr}); 
      console_scr->add(chassis.turn_ki);
    } 
  );

  auto temp_tgl = UI_crt_tgl(
    UI_crt_img("console_button.png", 480, 0, 160, 45, UI_distance_units::pixels),
    nullptr, 1
  );
  temp_tgl->set_states(UI_crt_rec(160, 0, 160, 45, vex::color::red, UI_distance_units::pixels), UI_crt_img("console_button_pressed.png", 320, 0, 160, 45, UI_distance_units::pixels));

  auto temp_tgl2 = UI_crt_tgl(
    UI_crt_img("console_button.png", 640, 0, 160, 45, UI_distance_units::pixels),
    nullptr, 1
  );
  temp_tgl2->set_states(UI_crt_rec(160, 0, 160, 45, vex::color::red, UI_distance_units::pixels), UI_crt_img("console_button_pressed.png", 320, 0, 160, 45, UI_distance_units::pixels));


  selector_panel_scr->add_UI_components({console_tgl, auton_tgl, config_tgl, temp_tgl, temp_tgl2});
  UI_render_queue = {main_bg_scr, selector_panel_scr};
}

void UI_swap_screens(const std::vector<std::shared_ptr<screen>>& scr) {
  UI_render_buffer = scr;
  is_screen_swapping = true;
}

void UI_render() {
  bool local_needs_render_update = false;
  bool full_refresh = false;
  std::vector<std::shared_ptr<screen>> temp;

  while (true) {
    if (is_screen_swapping) {
      full_refresh = true;
      is_screen_swapping = false;

      UI_render_queue = UI_render_buffer;
      temp = UI_render_queue;
      UI_render_buffer.clear();
    }
    
    if (!full_refresh) {
      for (const auto& screen : UI_render_queue) {
        if (screen->needs_update()) {
          temp.push_back(screen);
          local_needs_render_update = true;
          break;
        }
      }
    }

    UI_update_cursor_position(temp[0]);

    while (local_needs_render_update || full_refresh) {
      for (const auto& screen : temp) {
        screen->render();
      }
      if (Brain.Screen.render(true, true)) {  
        local_needs_render_update = false;
        full_refresh = false;
      }
      vex::this_thread::sleep_for(10);
    }
    temp.clear();

    vex::this_thread::sleep_for(10);
  }
}

void UI_execute_selector_toggles(std::shared_ptr<UI_component> tgl, std::shared_ptr<screen> scr, bool lock_toggles) {
  int tgl_id = UI_decode_toggle_group(tgl->get_ID());

  if (tgl_id <= 0) { return; }

  auto* toggle_component = static_cast<toggle*>(tgl.get());

  if (toggle_component->get_toggle_state() == true && lock_toggles) {
    toggle_component->lock_toggle();
  }

  for (const auto& component : scr->get_UI_components()) {
    if (component == tgl) continue;
    if (tgl_id == UI_decode_toggle_group(component->get_ID())) {
      auto* toggle_component = static_cast<toggle*>(component.get());
      toggle_component->unpress();
    }
  }
}
