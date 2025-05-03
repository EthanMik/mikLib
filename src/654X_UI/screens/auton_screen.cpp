#include "vex.h"

UI_auton_screen::UI_auton_screen() {
    UI_crt_auton_scr();
}

std::shared_ptr<screen> UI_auton_screen::get_auton_screen() {
    return(UI_auton_scr);
}

void UI_auton_screen::start_auton() {
    queue_autons(false);
}

void UI_auton_screen::UI_crt_auton_scr() {
    UI_auton_scr = UI_crt_scr(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT - 45);

    auto bg = UI_crt_bg(UI_crt_rec(0, 45, SCREEN_WIDTH, SCREEN_HEIGHT - 45, vex::color::black, UI_distance_units::pixels));
    auto red_blue_tgl_lbl = UI_crt_gfx(UI_crt_img("red_blue_toggle_label.png", 13, 49, 204, 41, UI_distance_units::pixels));
    auto rings_goal_tgl_lbl = UI_crt_gfx(UI_crt_img("rings_goal_toggle_label.png", 13, 97, 204, 41, UI_distance_units::pixels));
    auto quals_elims_tgl_lbl = UI_crt_gfx(UI_crt_img("quals_elims_toggle_label.png", 13, 145, 204, 41, UI_distance_units::pixels));
    auto off_sawp_tgl_lbl = UI_crt_gfx(UI_crt_img("off_skills_toggle_label.png", 13, 193, 204, 41, UI_distance_units::pixels));

    auto red_blue_btn = UI_crt_btn(UI_crt_img("", 94, 60, 43, 24, UI_distance_units::pixels), [this](){ UI_select_auton(autons::RED_BLUE); });
    auto red_blue_tgl = UI_crt_tgl(UI_crt_img("blue_toggle.png", 94, 60, 43, 24, UI_distance_units::pixels));
    red_blue_tgl->set_states(UI_crt_img("default_toggle.png", 94, 57, 43, 24, UI_distance_units::pixels), UI_crt_img("red_toggle.png", 94, 57, 43, 24, UI_distance_units::pixels));
    
    auto rings_goal_btn = UI_crt_btn(UI_crt_img("", 94, 108, 43, 24, UI_distance_units::pixels), [this](){ UI_select_auton(autons::RINGS_GOAL); });
    auto rings_goal_tgl = UI_crt_tgl(UI_crt_img("rings_toggle.png", 94, 108, 43, 24, UI_distance_units::pixels));
    rings_goal_tgl->set_states(UI_crt_img("default_toggle.png", 94, 108, 43, 24, UI_distance_units::pixels), UI_crt_img("goal_toggle.png", 94, 57, 43, 24, UI_distance_units::pixels));
    
    auto quals_elims_btn = UI_crt_btn(UI_crt_img("", 94, 156, 43, 24, UI_distance_units::pixels), [this](){ UI_select_auton(autons::QUALS_ELIMS); });
    auto quals_elims_tgl = UI_crt_tgl(UI_crt_img("quals_toggle.png", 94, 156, 43, 24, UI_distance_units::pixels));
    quals_elims_tgl->set_states(UI_crt_img("default_toggle.png", 94, 156, 43, 24, UI_distance_units::pixels), UI_crt_img("elims_toggle.png", 94, 57, 43, 24, UI_distance_units::pixels));
    
    auto off_sawp_btn = UI_crt_btn(UI_crt_img("", 94, 204, 43, 24, UI_distance_units::pixels), [this](){ UI_select_auton(autons::OFF_SAWP); });
    auto off_sawp_tgl = UI_crt_tgl(UI_crt_img("off_toggle.png", 94, 204, 43, 24, UI_distance_units::pixels));
        off_sawp_tgl->set_states(UI_crt_img("default_toggle.png", 94, 204, 43, 24, UI_distance_units::pixels), UI_crt_img("skills_toggle.png", 94, 57, 43, 24, UI_distance_units::pixels));
    off_sawp_ID = off_sawp_tgl->get_ID();
    
    auto divider = UI_crt_gfx(UI_crt_img("divider.png", 243, 53, 11, 177, UI_distance_units::pixels));

    auto show_alignment_btn = UI_crt_btn(UI_crt_img("show_alignment_button.png", 278, 200, 172, 30, UI_distance_units::pixels), nullptr);
        show_alignment_btn->set_states(UI_crt_img("show_alignment_button_pressed.png", 278, 200, 172, 30, UI_distance_units::pixels), nullptr); 
        show_alignment_btn->set_callback([this](){ queue_autons(true); });

    auto heading_btn = UI_crt_btn(UI_crt_img("heading_bg.png", 276, 50, 170, 76, UI_distance_units::pixels), [](){ calibrate_inertial(); });
        heading_btn->set_states(UI_crt_img("heading_bg_calibrate.png", 276, 50, 170, 76, UI_distance_units::pixels), UI_crt_img("heading_bg_calibrate.png", 276, 50, 170, 76, UI_distance_units::pixels));

    auto heading_lbl = UI_crt_lbl("", [](){ return chassis.get_absolute_heading(); }, 350, 75, UI_distance_units::pixels);
    auto x_lbl = UI_crt_lbl("", [](){ return chassis.get_X_position(); }, 350, 95, UI_distance_units::pixels);
    auto y_lbl = UI_crt_lbl("", [](){ return chassis.get_Y_position(); }, 350, 115, UI_distance_units::pixels);

    auto description_box_btn = UI_crt_btn(UI_crt_img("description_text_box.png", 278, 138, 173, 51, UI_distance_units::pixels), [this](){ show_auton(); });
        description_box_btn->set_states(UI_crt_img("description_text_box_pressed.png", 278, 138, 173, 51, UI_distance_units::pixels), UI_crt_img("description_text_box_pressed.png", 278, 138, 173, 90, UI_distance_units::pixels));

    auto description_box = UI_crt_txtbox("", UI_crt_img("", 278, 138, 173, 90, UI_distance_units::pixels));
        description_textbox = static_cast<textbox*>(description_box.get());

    auto _auton_img = UI_crt_gfx(UI_crt_img("", 15, 40, 188, 173, UI_distance_units::pixels));
        auton_img = static_cast<graphic*>(_auton_img.get());

    UI_auton_scr->add_UI_components({bg, red_blue_tgl_lbl, rings_goal_tgl_lbl, quals_elims_tgl_lbl, 
        off_sawp_tgl_lbl, red_blue_btn, red_blue_tgl, rings_goal_btn, rings_goal_tgl, quals_elims_btn, quals_elims_tgl, 
        off_sawp_btn, off_sawp_tgl, divider, show_alignment_btn, description_box_btn, description_box, _auton_img, heading_btn, heading_lbl, x_lbl, y_lbl});
    
    set_description();
}

void UI_auton_screen::UI_select_auton(autons auton) {
    switch (auton)
    {
    case autons::RED_BLUE:
        red_blue = !red_blue;
        break;
    case autons::RINGS_GOAL:
        rings_goal = !rings_goal;
        break;
    case autons::QUALS_ELIMS:
        quals_elims = !quals_elims;
        break;    
    case autons::OFF_SAWP:
        off_sawp = !off_sawp;
        break;
    }

    if (off_sawp && quals_elims) {
        for (const auto& component : UI_auton_scr->get_UI_components()) {
            if (off_sawp_ID == component->get_ID()) {
                auto* toggle_component = static_cast<toggle*>(component.get());
                toggle_component->unpress();
            }
        }
        off_sawp = false;
    }
    set_description();
}

void UI_auton_screen::set_description() {    
    if (!red_blue && !rings_goal && !quals_elims && !off_sawp) { description_textbox->set_text("Blue Ringside Winpoint: 4+1"); return; }
    if (!red_blue && !rings_goal && !quals_elims &&  off_sawp) { description_textbox->set_text("Blue Ringside Sawp: (3,2)+1"); return; }
    if (!red_blue && !rings_goal &&  quals_elims && !off_sawp) { description_textbox->set_text("Blue Ring Rush: 6+1"); return; }
    
    if (!red_blue &&  rings_goal && !quals_elims && !off_sawp) { description_textbox->set_text("Blue Goalside Winpoint: 5"); return; }
    if (!red_blue &&  rings_goal && !quals_elims &&  off_sawp) { description_textbox->set_text("Blue Goalside Sawp (2,1)+1"); return; }
    if (!red_blue &&  rings_goal &&  quals_elims && !off_sawp) { description_textbox->set_text("Blue Driver Goalrush: 6"); return; }
    
    if ( red_blue && !rings_goal && !quals_elims && !off_sawp) { description_textbox->set_text("Red Ringside Winpoint: 4+1"); return; }
    if ( red_blue && !rings_goal && !quals_elims &&  off_sawp) { description_textbox->set_text("Red Ringside Sawp: (3,2)+1"); return; }
    if ( red_blue && !rings_goal &&  quals_elims && !off_sawp) { description_textbox->set_text("Red Ring Rush: 6+1"); return; }
    
    if ( red_blue &&  rings_goal && !quals_elims && !off_sawp) { description_textbox->set_text("Red Goalside Winpoint: 5"); return; }
    if ( red_blue &&  rings_goal && !quals_elims &&  off_sawp) { description_textbox->set_text("Red Goalside Sawp: (2,1)+1"); return; }
    if ( red_blue &&  rings_goal &&  quals_elims && !off_sawp) { description_textbox->set_text("Red Driver Goalrush: 6"); return; }    
}

void UI_auton_screen::queue_autons(bool calibrating) {    
    if (!red_blue && !rings_goal && !quals_elims && !off_sawp) { skills(calibrating); return; }
    if (!red_blue && !rings_goal && !quals_elims &&  off_sawp) { blue_ringside_sawp(calibrating); return; }
    if (!red_blue && !rings_goal &&  quals_elims && !off_sawp) { blue_ringside_elim(calibrating); return; }

    if (!red_blue &&  rings_goal && !quals_elims && !off_sawp) { blue_goalside_winpoint(calibrating); return; }
    if (!red_blue &&  rings_goal && !quals_elims &&  off_sawp) { blue_goalside_sawp(calibrating); return; }
    if (!red_blue &&  rings_goal &&  quals_elims && !off_sawp) { blue_goalside_elim(calibrating); return; }

    if ( red_blue && !rings_goal && !quals_elims && !off_sawp) { red_ringside_winpoint(calibrating); return; }
    if ( red_blue && !rings_goal && !quals_elims &&  off_sawp) { red_ringside_sawp(calibrating); return; }
    if ( red_blue && !rings_goal &&  quals_elims && !off_sawp) { red_ringside_elim(calibrating); return; }

    if ( red_blue &&  rings_goal && !quals_elims && !off_sawp) { red_goalside_winpoint(calibrating); return; }
    if ( red_blue &&  rings_goal && !quals_elims &&  off_sawp) { red_goalside_sawp(calibrating); return; }
    if ( red_blue &&  rings_goal &&  quals_elims && !off_sawp) { red_goalside_elim(calibrating); return; }
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

    if (!red_blue && !rings_goal && !quals_elims && !off_sawp) { return; }
    if (!red_blue && !rings_goal && !quals_elims &&  off_sawp) { return; }
    if (!red_blue && !rings_goal &&  quals_elims && !off_sawp) { return; }
    
    if (!red_blue &&  rings_goal && !quals_elims && !off_sawp) { return; }
    if (!red_blue &&  rings_goal && !quals_elims &&  off_sawp) { return; }
    if (!red_blue &&  rings_goal &&  quals_elims && !off_sawp) { return; }
    
    if ( red_blue && !rings_goal && !quals_elims && !off_sawp) { return; }
    if ( red_blue && !rings_goal && !quals_elims &&  off_sawp) { return; }
    if ( red_blue && !rings_goal &&  quals_elims && !off_sawp) { return; }
    
    if ( red_blue &&  rings_goal && !quals_elims && !off_sawp) { return; }
    if ( red_blue &&  rings_goal && !quals_elims &&  off_sawp) { return; }
    if ( red_blue &&  rings_goal &&  quals_elims && !off_sawp) { auton_img->modify_graphic(UI_crt_img("red_goalside_elim_auto.png", 15, 40, 188, 173, UI_distance_units::pixels)); return; }    
}
