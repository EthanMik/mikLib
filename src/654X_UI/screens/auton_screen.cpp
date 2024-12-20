#include "vex.h"

UI_auton_screen::UI_auton_screen() {
    UI_crt_auton_scr();
}

std::shared_ptr<screen> UI_auton_screen::get_auton_screen() {
    return(UI_auton_scr);
}

void UI_auton_screen::UI_crt_auton_scr() {
    UI_auton_scr = UI_crt_scr(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT - 45);

    auto bg = UI_crt_bg(UI_crt_rec(0, 45, SCREEN_WIDTH, SCREEN_HEIGHT - 45, vex::color::black, UI_distance_units::pixels));
    auto red_blue_tgl_lbl = UI_crt_gfx(UI_crt_img("red_blue_toggle_label.png", 13, 49, 204, 41, UI_distance_units::pixels));
    auto rings_goal_tgl_lbl = UI_crt_gfx(UI_crt_img("rings_goal_toggle_label.png", 13, 97, 204, 41, UI_distance_units::pixels));
    auto quals_elims_tgl_lbl = UI_crt_gfx(UI_crt_img("quals_elims_toggle_label.png", 13, 145, 204, 41, UI_distance_units::pixels));
    auto off_skills_tgl_lbl = UI_crt_gfx(UI_crt_img("off_skills_toggle_label.png", 13, 193, 204, 41, UI_distance_units::pixels));

    auto red_blue_tgl = UI_crt_tgl(UI_crt_img("blue_toggle.png", 94, 60, 43, 24, UI_distance_units::pixels));
        red_blue_tgl->set_states(nullptr, UI_crt_img("red_toggle.png", 94, 57, 43, 24, UI_distance_units::pixels));
        red_blue_tgl->set_callback([this](){ UI_select_auton(UI_RED_BLUE_BIT); });

    auto rings_goal_tgl = UI_crt_tgl(UI_crt_img("rings_toggle.png", 94, 108, 43, 24, UI_distance_units::pixels));
        rings_goal_tgl->set_states(nullptr, UI_crt_img("goal_toggle.png", 94, 57, 43, 24, UI_distance_units::pixels));
        rings_goal_tgl->set_callback([this](){ UI_select_auton(UI_RINGS_GOAL_BIT); });

    auto quals_elims_tgl = UI_crt_tgl(UI_crt_img("quals_toggle.png", 94, 156, 43, 24, UI_distance_units::pixels));
        quals_elims_tgl->set_states(nullptr, UI_crt_img("elims_toggle.png", 94, 57, 43, 24, UI_distance_units::pixels));
        quals_elims_tgl->set_callback([this](){ UI_select_auton(UI_QUALS_ELIMS_BIT); });
        
    auto off_skills_tgl = UI_crt_tgl(UI_crt_img("off_toggle.png", 94, 204, 43, 24, UI_distance_units::pixels));
        off_skills_tgl->set_states(nullptr, UI_crt_img("skills_toggle.png", 94, 57, 43, 24, UI_distance_units::pixels));
        off_skills_tgl->set_callback([this](){ UI_select_auton(UI_OFF_SKILLS_BIT); });

    auto divider = UI_crt_gfx(UI_crt_img("divider.png", 233, 53, 11, 177, UI_distance_units::pixels));

    auto show_alignment_btn = UI_crt_btn(UI_crt_img("show_alignment_button.png", 278, 200, 172, 30, UI_distance_units::pixels), nullptr);
        show_alignment_btn->set_states(UI_crt_img("show_alignment_button_pressed.png", 278, 200, 172, 30, UI_distance_units::pixels), nullptr); 

    auto description_box = UI_crt_gfx({
        UI_crt_img("description_text_box.png", 278, 98, 173, 90, UI_distance_units::pixels),
        UI_crt_txt("Description...", 225, 94, UI_distance_units::pixels)
    });
    


    UI_auton_scr->add_UI_components({bg, red_blue_tgl_lbl, rings_goal_tgl_lbl, quals_elims_tgl_lbl, 
        off_skills_tgl_lbl, red_blue_tgl, rings_goal_tgl, quals_elims_tgl, 
        off_skills_tgl, divider, show_alignment_btn, description_box});
}

void UI_auton_screen::UI_select_auton(int bit) {
    int bit_mask = 1 << bit;
    UI_auton_selected |= bit_mask;

    if (UI_auton_selected & UI_OFF_SKILLS_MASK) {

    }
}
