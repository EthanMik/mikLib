#include "vex.h"

using namespace mik;
using namespace vex;

controller_btn::controller_btn(bool is_btn, std::string unpressed_state, std::string pressed_state, std::function<void()> callback) :
    is_btn(is_btn), unpressed_state(unpressed_state), pressed_state(pressed_state), callback(callback)
{
    state_label = unpressed_state;
};

controller_btn::controller_btn(bool really_stupid_exception_that_shouldnt_exist_but_i_dont_want_to_make_another_class, std::function<void()> callback) :
    callback(callback), exception(really_stupid_exception_that_shouldnt_exist_but_i_dont_want_to_make_another_class)
{
    state_label = "[" + to_string(auton_scr->var_num) + "]";
};

std::string controller_btn::get_state_label() { return state_label; }
bool controller_btn::get_state() { 
    if (exception) {
        return exception;
    }
    return state;
}
void controller_btn::unpush() { state = true; push(); }
void controller_btn::enable_full_override(std::string lbl) { state_label = lbl; full_override = true; }
void controller_btn::change_state(bool is_pressed) {
    if (is_pressed) {
        state = true;
        state_label = pressed_state;
    } else {
        state = false;
        state_label = unpressed_state;
    }
}
void controller_btn::disable_full_override() { 
    full_override = false;
    if (state) {
        state_label = pressed_state;
    } else {
        state_label = unpressed_state;
    } 
}

bool controller_btn::push() {
    if (full_override) {
        return false;
    }
    if (exception) {
        callback();
        state_label = "[" + to_string(auton_scr->var_num) + "]";
        return false;
    }

    state = !state;
    if (state) {
        state_label = pressed_state;
    } else {
        state_label = unpressed_state;
    }
    if (is_btn && state) {
        vex::task::sleep(500);
        state_label = unpressed_state;
        state = false;
        callback();
        return state;
    }
    callback();

    return state;
}


UI_auton_screen::UI_auton_screen() {
    UI_crt_auton_scr();
}

std::shared_ptr<screen> UI_auton_screen::get_auton_screen() {
    return(UI_auton_scr);
}

void UI_auton_screen::start_auton() {
    auton_run = vex::task([](){
        auton_scr->disable_controller_overlay();
        auton_scr->exit_auton_task();
        disable_user_control = true;
        auton_scr->auto_running = true;
        auton_scr->queue_autons(false, false, false);
        auton_scr->auto_running = false;
        disable_user_control = false;
        return 0;
    });
}

void UI_auton_screen::exit_auton_task() {
    controller_scr_input = vex::task([](){
    auton_scr->input_overlay = true;
    while(auton_scr->input_overlay) {
        if (Controller.ButtonB.pressing()) {
            task::sleep(200);
            auton_scr->auto_running = false;
            auton_scr->auton_run.stop();
            chassis.stop_drive(vex::brakeType::hold);
            assembly.stop_motors(vex::brakeType::hold);
            task::sleep(500);
            chassis.stop_drive(vex::brakeType::coast);
            assembly.stop_motors(vex::brakeType::coast);
            auton_scr->restart_controller_overlay();
        }
        task::sleep(50);
    }
    return 0;
});
}

void UI_auton_screen::end_auton() {
    disable_controller_overlay();
    auto_running = false;
    auton_run.stop();
}

void UI_auton_screen::UI_crt_auton_scr() {
    UI_auton_scr = UI_crt_scr(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT - 45);

    auto bg = UI_crt_bg(UI_crt_rec(0, 45, SCREEN_WIDTH, SCREEN_HEIGHT - 45, vex::color::black, UI_distance_units::pixels));
    auto red_blue_tgl_lbl = UI_crt_gfx(UI_crt_img("red_blue_toggle_label.png", 13, 49, 204, 41, UI_distance_units::pixels));
    auto red_blue_tgl_txt = UI_crt_gfx({UI_crt_txt("Blue", 37, 78, UI_distance_units::pixels), UI_crt_txt("Red", 165, 78, UI_distance_units::pixels)});
    
    auto rings_goal_tgl_lbl = UI_crt_gfx(UI_crt_img("rings_goal_toggle_label.png", 13, 97, 204, 41, UI_distance_units::pixels));
    auto rings_goal_tgl_txt = UI_crt_gfx({UI_crt_txt("Left ", 37, 78+49, UI_distance_units::pixels), UI_crt_txt("Right", 155, 78+49, UI_distance_units::pixels)});
    
    auto quals_elims_tgl_lbl = UI_crt_gfx(UI_crt_img("quals_elims_toggle_label.png", 13, 145, 204, 41, UI_distance_units::pixels));
    auto quals_elims_tgl_txt = UI_crt_gfx({UI_crt_txt("Quals ", 34, 78+49+47, UI_distance_units::pixels), UI_crt_txt("Elims", 155, 78+49+47, UI_distance_units::pixels)});
    
    auto off_sawp_tgl_lbl = UI_crt_gfx(UI_crt_img("off_skills_toggle_label.png", 13, 193, 204, 41, UI_distance_units::pixels));
    auto off_sawp_tgl_txt = UI_crt_gfx({UI_crt_txt("Off ", 43, 78+49+47+48, UI_distance_units::pixels), UI_crt_txt("Sawp", 162, 78+49+47+48, UI_distance_units::pixels)});

    auto red_blue_btn = UI_crt_btn(UI_crt_img("", 94, 60, 43, 24, UI_distance_units::pixels), [this](){  UI_select_auton(autons::RED_BLUE); flip_toggle_controller({0, 0}, red_blue); save_auton_SD(); });
    red_blue_tgl = UI_crt_tgl(UI_crt_img("blue_toggle.png", 94, 60, 43, 24, UI_distance_units::pixels));
    red_blue_tgl->set_states(UI_crt_img("default_toggle.png", 94, 60, 43, 24, UI_distance_units::pixels), UI_crt_img("red_toggle.png", 94, 60, 43, 24, UI_distance_units::pixels));
    
    auto rings_goal_btn = UI_crt_btn(UI_crt_img("", 94, 108, 43, 24, UI_distance_units::pixels), [this](){ UI_select_auton(autons::RINGS_GOAL); flip_toggle_controller({0, 1}, rings_goal); save_auton_SD(); });
    rings_goal_tgl = UI_crt_tgl(UI_crt_img("rings_toggle.png", 94, 108, 43, 24, UI_distance_units::pixels));
    rings_goal_tgl->set_states(UI_crt_img("default_toggle.png", 94, 108, 43, 24, UI_distance_units::pixels), UI_crt_img("goal_toggle.png", 94, 108, 43, 24, UI_distance_units::pixels));
    
    auto quals_elims_btn = UI_crt_btn(UI_crt_img("", 94, 156, 43, 24, UI_distance_units::pixels), [this](){ UI_select_auton(autons::QUALS_ELIMS); flip_toggle_controller({0, 2}, quals_elims); save_auton_SD(); });
    quals_elims_tgl = UI_crt_tgl(UI_crt_img("quals_toggle.png", 94, 156, 43, 24, UI_distance_units::pixels));
    quals_elims_tgl->set_states(UI_crt_img("default_toggle.png", 94, 156, 43, 24, UI_distance_units::pixels), UI_crt_img("elims_toggle.png", 94, 156, 43, 24, UI_distance_units::pixels));
    
    auto off_sawp_btn = UI_crt_btn(UI_crt_img("", 94, 204, 43, 24, UI_distance_units::pixels), [this](){ UI_select_auton(autons::OFF_SAWP); flip_toggle_controller({1, 0}, off_sawp); save_auton_SD(); });
    off_sawp_tgl = UI_crt_tgl(UI_crt_img("off_toggle.png", 94, 204, 43, 24, UI_distance_units::pixels));
        off_sawp_tgl->set_states(UI_crt_img("default_toggle.png", 94, 204, 43, 24, UI_distance_units::pixels), UI_crt_img("skills_toggle.png", 94, 204, 43, 24, UI_distance_units::pixels));
    off_sawp_ID = off_sawp_tgl->get_ID();
    
    auto show_alignment_btn = UI_crt_btn(UI_crt_img("show_alignment_button.png", 278-10, 200, 172, 30, UI_distance_units::pixels), nullptr);
        show_alignment_btn->set_states(UI_crt_img("show_alignment_button_pressed.png", 278-10, 200, 172, 30, UI_distance_units::pixels), nullptr); 
        show_alignment_btn->set_callback([this](){ queue_autons(true, false, false); });

    auto heading_btn = UI_crt_btn(UI_crt_img("heading_bg.png", 276-10, 50, 170, 76, UI_distance_units::pixels), [](){ calibrate_inertial(); });
        heading_btn->set_states(UI_crt_img("heading_bg_calibrate.png", 276-10, 50, 170, 76, UI_distance_units::pixels), UI_crt_img("heading_bg_calibrate.png", 276-10, 50, 170, 76, UI_distance_units::pixels));

    auto heading_lbl = UI_crt_lbl("", [](){ return chassis.get_absolute_heading(); }, 350-10, 75, UI_distance_units::pixels);
    auto x_lbl = UI_crt_lbl("", [](){ return chassis.get_X_position(); }, 350-10, 95, UI_distance_units::pixels);
    auto y_lbl = UI_crt_lbl("", [](){ return chassis.get_Y_position(); }, 350-10, 115, UI_distance_units::pixels);

    auto description_box_btn = UI_crt_btn(UI_crt_img("description_text_box.png", 278-10, 138, 173, 51, UI_distance_units::pixels), [this](){ show_auton(); });
        description_box_btn->set_states(UI_crt_img("description_text_box_pressed.png", 278-10, 138, 173, 51, UI_distance_units::pixels), UI_crt_img("description_text_box_pressed.png", 278-10, 138, 173, 90, UI_distance_units::pixels));

    auto description_box = UI_crt_txtbox("", text_align::LEFT, UI_crt_img("", 278-10, 138, 173, 90, UI_distance_units::pixels));
        description_textbox = static_cast<textbox*>(description_box.get());

    auto _auton_img = UI_crt_gfx(UI_crt_img("", 15, 40, 0, 0, UI_distance_units::pixels));
        auton_img = static_cast<graphic*>(_auton_img.get());

    auto prev_auto_var_btn = UI_crt_btn(UI_crt_img("left_auton_arrow.png", 2.48, 1.225, .45, 1, UI_distance_units::inches), [this](){ prev_var(); cursor_position.first = 1; cursor_position.second = 2; save_auton_SD(var_num-1);  });
        prev_auto_var_btn->set_states(UI_crt_img("left_auton_arrow_pressed.png", 2.48, 1.5, .45, .5, UI_distance_units::inches), UI_crt_img("left_auton_arrow_pressed.png", 2.48, 1.5, .45, .5, UI_distance_units::inches));
    
    auto next_auto_var_btn = UI_crt_btn(UI_crt_img("right_auton_arrow.png", 4.67, 1.225, .45, 1, UI_distance_units::inches), [this](){ next_var(); cursor_position.first = 1; cursor_position.second = 2; save_auton_SD(var_num-1); });
        next_auto_var_btn->set_states(UI_crt_img("right_auton_arrow_pressed.png", 4.67, 1.5, .45, .5, UI_distance_units::inches), UI_crt_img("right_auton_arrow_pressed.png", 4.67, 1.5, .45, .5, UI_distance_units::inches));
    
    UI_auton_scr->add_UI_components({bg, red_blue_tgl_lbl, red_blue_tgl_txt, rings_goal_tgl_lbl, rings_goal_tgl_txt, quals_elims_tgl_lbl, quals_elims_tgl_txt,
        off_sawp_tgl_lbl, off_sawp_tgl_txt, red_blue_btn, red_blue_tgl, rings_goal_btn, rings_goal_tgl, quals_elims_btn, quals_elims_tgl, 
        off_sawp_btn, off_sawp_tgl, show_alignment_btn, prev_auto_var_btn, next_auto_var_btn, description_box_btn, description_box, _auton_img, heading_btn, heading_lbl, x_lbl, y_lbl});
    
    set_description();
}

void UI_auton_screen::UI_select_auton(autons auton) {
    switch (auton)
    {
    case autons::RED_BLUE:
        auto_max_time = 15;
        red_blue = !red_blue;
        break;
        case autons::RINGS_GOAL:
        auto_max_time = 15;
        rings_goal = !rings_goal;
        break;
        case autons::QUALS_ELIMS:
        auto_max_time = 15;
        quals_elims = !quals_elims;
        break;    
        case autons::OFF_SAWP:
        auto_max_time = 15;
        off_sawp = !off_sawp;
        break;
        case autons::OFF_SKILLS:
        auto_max_time = 60;
        off_skills = !off_skills;
        break;
    }

    if (off_sawp && quals_elims) {
        for (const auto& component : UI_auton_scr->get_UI_components()) {
            if (off_sawp_ID == component->get_ID()) {
                auto* toggle_component = static_cast<toggle*>(component.get());
                toggle_component->unpress();
            }
        }
        control_panel[1][0].unpush();
        off_sawp = false;
    }
    if (off_skills) {
        control_panel[0][0].enable_full_override("[###]");
        control_panel[0][1].enable_full_override("[###]");
        control_panel[0][2].enable_full_override("[###]");
        control_panel[1][0].enable_full_override("[###]");
    } else {
        control_panel[0][0].disable_full_override();
        control_panel[0][1].disable_full_override();
        control_panel[0][2].disable_full_override();
        control_panel[1][0].disable_full_override();  
    }

    set_description();
}

bool UI_auton_screen::set_description() {
    UI_auton_scr->refresh();    
    queue_autons(false, true, false);
    description_textbox->set_text(output);
    description_output = output;
    if (output == "") {
        return false;
    }
    return true; 
}

void UI_auton_screen::set_description(std::string text) {
    description_textbox->set_text(text);
    description_output = text;
}

void UI_auton_screen::queue_autons(bool calibrating, bool set_description, bool set_lineup) {    
    if (!calibrating && !set_description && !set_lineup && time_limit) {
        start_time_limit();
    }

    if (off_skills) { output = skills(calibrating, var, set_description, set_lineup); return; }

    if (!red_blue && !rings_goal && !quals_elims && !off_sawp) { output = template_auto(calibrating, var, set_description, set_lineup); return; }
    if (!red_blue && !rings_goal && !quals_elims &&  off_sawp) { output = blue_left_sawp(calibrating, var, set_description, set_lineup); return; }
    if (!red_blue && !rings_goal &&  quals_elims && !off_sawp) { output = blue_left_elim(calibrating, var, set_description, set_lineup); return; }

    if (!red_blue &&  rings_goal && !quals_elims && !off_sawp) { output = blue_right_winpoint(calibrating, var, set_description, set_lineup); return; }
    if (!red_blue &&  rings_goal && !quals_elims &&  off_sawp) { output = blue_right_sawp(calibrating, var, set_description, set_lineup); return; }
    if (!red_blue &&  rings_goal &&  quals_elims && !off_sawp) { output = blue_right_elim(calibrating, var, set_description, set_lineup); return; }

    if ( red_blue && !rings_goal && !quals_elims && !off_sawp) { output = red_left_winpoint(calibrating, var, set_description, set_lineup); return; }
    if ( red_blue && !rings_goal && !quals_elims &&  off_sawp) { output = red_left_sawp(calibrating, var, set_description, set_lineup); return; }
    if ( red_blue && !rings_goal &&  quals_elims && !off_sawp) { output = red_left_elim(calibrating, var, set_description, set_lineup); return; }

    if ( red_blue &&  rings_goal && !quals_elims && !off_sawp) { output = red_right_winpoint(calibrating, var, set_description, set_lineup); return; }
    if ( red_blue &&  rings_goal && !quals_elims &&  off_sawp) { output = red_right_sawp(calibrating, var, set_description, set_lineup); return; }
    if ( red_blue &&  rings_goal &&  quals_elims && !off_sawp) { output = red_right_elim(calibrating, var, set_description, set_lineup); return; }
}

void UI_auton_screen::show_auton() {  
    is_showing_auton = !is_showing_auton;
    if (!is_showing_auton) {
        auton_img->blacklist_ID();
    }
    if (is_showing_auton) {
        auton_img->whitelist_ID();
    }
    
    UI_auton_scr->refresh();
    queue_autons(false, false, true);
    auton_img->replace_graphic(UI_crt_img(output, 15, 40, 0, 0, UI_distance_units::pixels));
}

void UI_auton_screen::start_time_limit() {
    controller_scr_overlay.stop();
    Controller.Screen.clearScreen();
    controller_scr_overlay = vex::task([](){
        float start_time = Brain.Timer.time(vex::timeUnits::sec);
        while(auton_scr->auto_running) {
            if (Brain.Timer.time(vex::timeUnits::sec) - start_time >= auton_scr->auto_max_time) {
                chassis.stop_drive(vex::brakeType::coast);
                std::abort();
            }

            Controller.Screen.setCursor(2, 1);
            Controller.Screen.print("           ");
            Controller.Screen.print(Brain.Timer.time(vex::timeUnits::sec) - start_time);
            Controller.Screen.print("  ");

            vex::task::sleep(10);
        }
        return 0;
    });
}

void UI_auton_screen::enable_time_limit() {
    time_limit = !time_limit;
}

void UI_auton_screen::next_var() {
    ++var_num;
    if (var_num > 9) {
        var_num = 1;
    }
    var = int_to_auto_variation(var_num);

    if (!set_description()) {
        set_description(("Auto Variation: " + to_string(var_num)));
    }
}

void UI_auton_screen::prev_var() {
    --var_num;
    if (var_num < 1) {
        var_num = 1;
    }
    var = int_to_auto_variation(var_num);

    if (!set_description()) {
        set_description(("Auto Variation: " + to_string(var_num)));
    }
}

void UI_auton_screen::save_auton_SD(int count) {
    if (!Brain.SDcard.isInserted()) { return; }
    int r = auton_scr->cursor_position.first;
    int c = auton_scr->cursor_position.second;
    std::string id = to_string(r) + " " + to_string(c);
    std::string id_full = to_string(r) + " " + to_string(c) + " " + to_string(count);
    if (count > 1) {
        remove_duplicates_SD_file("auton.txt", id);
        write_to_SD_file("auton.txt", id_full);
        return;
    }
    if (auton_scr->control_panel[r][c].get_state()) {
        write_to_SD_file("auton.txt", id_full);
    } else {
        remove_duplicates_SD_file("auton.txt", id);
    }
}

void UI_auton_screen::set_previous_selected_auto() {
    std::vector<std::string> output = get_SD_file_txt("auton.txt");

    for (auto it = output.rbegin(); it != output.rend(); ++it) {
        int r = 0, c = 0, count = 0;
        std::stringstream ss(*it);
        if (ss >> r >> c >> count) {}

        for (size_t i = 0; i < count; ++i) {
            auton_scr->control_panel[r][c].push();
        }
    }
}

void UI_auton_screen::flip_toggle_controller(std::pair<int, int> cursor_position, bool state) {
    this->cursor_position = cursor_position;
    int r = auton_scr->cursor_position.first;
    int c = auton_scr->cursor_position.second;
    control_panel[r][c].change_state(state);
}


void UI_auton_screen::flip_toggle(std::shared_ptr<UI_component> tgl, bool state) {
    auto* toggle_component = static_cast<toggle*>(tgl.get());
    if (!state) {
        toggle_component->unpress();
    } else {
        toggle_component->press();
    }
}

auto_variation UI_auton_screen::int_to_auto_variation(int num) {
    switch (num)
    {
        case 1: return auto_variation::ONE;
        case 2: return auto_variation::TWO;
        case 3: return auto_variation::THREE;  
        case 4: return auto_variation::FOUR;  
        case 5: return auto_variation::FIVE;  
        case 6: return auto_variation::SIX;  
        case 7: return auto_variation::SEVEN;  
        case 8: return auto_variation::EIGHT;  
        case 9: return auto_variation::NINE; 
        default: return auto_variation::ONE;
    }
}

void UI_auton_screen::controller_description_scr() {
    controller_scr_overlay.stop();
    Controller.Screen.clearScreen();
    controller_scr_overlay = vex::task([](){
        std::vector<std::string> wrapped_text;
        std::vector<std::string> words;
        std::istringstream iss(auton_scr->description_output);
        std::string word;

        while (iss >> word)
            words.push_back(word);
        
        std::string line;
        for (int i = 0; i < words.size(); ++i) {
            if (Brain.Screen.getStringWidth((line + words[i] + " ").c_str()) > 200) {
                wrapped_text.push_back(line);
                line = "";
            }
            line += words[i] + " ";
        }
        wrapped_text.push_back(line);

        int newline = 20;
        for (int i = 0; i < wrapped_text.size(); ++i) {
            Controller.Screen.setCursor(i + 1, 1);
            Controller.Screen.print(wrapped_text[i].c_str());
            newline+=20;
        }
        
        return 0;
    });
}

void UI_auton_screen::controller_selector_scr() {
    controller_scr_overlay.stop();
    Controller.Screen.clearScreen();
    controller_scr_overlay = vex::task([](){
        while(1) {         
            if (auton_scr->controller_row_max > 3) {
                auton_scr->controller_row_max--;
                auton_scr->controller_row_min--;
            }
            if (auton_scr->cursor_position.first >= 3) {
                auton_scr->controller_row_max++;
                auton_scr->controller_row_min++;
            }

            for (size_t i = auton_scr->controller_row_min; i < auton_scr->controller_row_max; ++i) {
                Controller.Screen.setCursor(i + 1 - auton_scr->controller_row_min, 1);
                
                for (size_t j = 0; j < auton_scr->control_panel[i].size(); ++j) {
                    std::string space = "  ";
                    if (auton_scr->cursor_position.first == i && auton_scr->cursor_position.second == j) {
                        space = "< ";
                    }
                    Controller.Screen.print((auton_scr->control_panel[i][j].get_state_label() + space).c_str());
                }
                Controller.Screen.print("                   ");
            }
            task::sleep(50);
        }
        return 0;
    });
}

void UI_auton_screen::controller_calibrate_scr() {
    controller_scr_overlay.stop();
    Controller.Screen.clearScreen();
    controller_scr_overlay = vex::task([](){ 
        while(1) {
            Controller.Screen.setCursor(1, 1);
            Controller.Screen.print(("Theta: " + to_string_float(chassis.get_absolute_heading())).c_str());
            Controller.Screen.setCursor(2, 1);
            Controller.Screen.print(("X: "+ to_string_float(chassis.get_X_position())).c_str());
            Controller.Screen.setCursor(3, 1);
            Controller.Screen.print(("Y: " + to_string_float(chassis.get_Y_position())).c_str());
            task::sleep(50);
        }
        return 0;
    });
}

void UI_auton_screen::controller_default_scr() {
    controller_scr_overlay = vex::task([](){
        std::string battery;
        std::string time = "00:00";
        while(1) {
            int time_sec = Brain.Timer.time(vex::timeUnits::sec);
            std::string sec = to_string(time_sec % 60);
            sec = sec.size() <= 1 ? "0" + sec : sec;
            std::string min = to_string(time_sec / 60);
            min = min.size() <= 1 ? "0" + min : min;

            time = min + ":" + sec + "       ";

            int battery_percent = Brain.Battery.capacity();
            
            Controller.Screen.setCursor(1, 1);
            Controller.Screen.print((to_string(battery_percent) + "'/,").c_str());
            Controller.Screen.setCursor(1, 12);
            Controller.Screen.print((time).c_str());
            vex::task::sleep(1000);
        }
        return 0;
    });
}

void UI_auton_screen::disable_controller_overlay() {
    disable_user_control = false; 
    controller_scr_input.stop();
    auton_scr->input_overlay = false;
    controller_scr_overlay.stop(); 
    Controller.Screen.clearScreen();
}

void UI_auton_screen::enable_controller_overlay() {
    disable_user_control = true;
    control_panel = {
        {{controller_btn(false, "[Blue]", "[Red]", [this](){ UI_select_auton(autons::RED_BLUE); flip_toggle(red_blue_tgl, red_blue); save_auton_SD(); } )},
         {controller_btn(false, "[Left]", "[Right]", [this](){ UI_select_auton(autons::RINGS_GOAL); flip_toggle(rings_goal_tgl, rings_goal); save_auton_SD(); })},
         {controller_btn(false, "[Qual]", "[Elim]", [this](){ UI_select_auton(autons::QUALS_ELIMS); flip_toggle(quals_elims_tgl, quals_elims); save_auton_SD(); })}}, 

        {{controller_btn(false, "[Off]", "[Sawp]", [this](){ UI_select_auton(autons::OFF_SAWP); flip_toggle(off_sawp_tgl, off_sawp); save_auton_SD(); } )}, 
         {controller_btn(false, "[Off]", "[Skills]", [this](){ UI_select_auton(autons::OFF_SKILLS); flip_toggle(config_scr->macro_10_bg_tgl, off_skills); save_auton_SD(); } )}, 
         {controller_btn(true, [this](){ next_var(); cursor_position.first = 1; cursor_position.second = 2; save_auton_SD(var_num-1); } )}}, 

        {{controller_btn(true, "[Desc]", "[###]", [this](){ controller_description_scr(); } )}, 
         {controller_btn(true, "[Calib]", "[###]", [this](){ controller_calibrate_scr(); queue_autons(true, false, false); } )},
         {controller_btn(true, "[Run]", "[##]", [](){ auton_scr->start_auton(); })}},

        {{controller_btn(false, "[Off]", "[Time Limit]", [this](){ enable_time_limit(); flip_toggle(config_scr->macro_4_bg_tgl, time_limit); save_auton_SD(); } )}, 
         {controller_btn(true, "[Inertial]", "[...]", [](){ calibrate_inertial(); } )}, 
         {controller_btn(true, "[_]", "[#]", [](){} )}}
    };
    
    
    set_previous_selected_auto();
    restart_controller_overlay();
}

void UI_auton_screen::restart_controller_overlay() {
    controller_selector_scr();

    controller_scr_input = vex::task([](){
        bool is_exiting = false;
        bool prev_exiting_state = false;
        int exit_start_time = 0;
        auton_scr->input_overlay = true;

        while(auton_scr->input_overlay) {
            if (Controller.ButtonUp.pressing()) {
                if (auton_scr->cursor_position.first > 0) {
                    auton_scr->cursor_position.first--;
                }
                task::sleep(200);
            }
            if (Controller.ButtonDown.pressing()) {
                if (auton_scr->cursor_position.first < auton_scr->control_panel.size() - 1) {
                    auton_scr->cursor_position.first++;
                }
                task::sleep(200);
            }
            if (Controller.ButtonRight.pressing()) {
                if (auton_scr->cursor_position.second < 2) {
                    auton_scr->cursor_position.second++;
                }
                task::sleep(200);
            }
            if (Controller.ButtonLeft.pressing()) {
                if (auton_scr->cursor_position.second > 0) {
                    auton_scr->cursor_position.second--;
                }
                task::sleep(200);
            }
            if (Controller.ButtonA.pressing()) {
                UI_select_scr(auton_scr->get_auton_screen());
                int r = auton_scr->cursor_position.first;
                int c = auton_scr->cursor_position.second;
                auton_scr->control_panel[r][c].push();
                task::sleep(200);
            }
            if (Controller.ButtonB.pressing()) {
                is_exiting = true;
                if (!prev_exiting_state) {
                    exit_start_time = Brain.Timer.time(vex::timeUnits::msec);
                }
                auton_scr->controller_selector_scr();
                task::sleep(200);
            } else {
                is_exiting = false;
            }
            prev_exiting_state = is_exiting;
            if ((is_exiting && Brain.Timer.time(vex::timeUnits::msec) - exit_start_time > 600) 
                || Controller.ButtonX.pressing()
                || std::abs(deadband(vex::controller(vex::primary).Axis1.value(), 15)) > 0
                || std::abs(deadband(vex::controller(vex::primary).Axis2.value(), 15)) > 0
                || std::abs(deadband(vex::controller(vex::primary).Axis3.value(), 15)) > 0
                || std::abs(deadband(vex::controller(vex::primary).Axis4.value(), 15)) > 0
            ) 
            {
                task::sleep(200);
                auton_scr->disable_controller_overlay();
                auton_scr->controller_default_scr();
                break;
            } 
            task::sleep(50);
        }
        return 0;
    });
}
