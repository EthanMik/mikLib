#include "mikLib/ui.h"
#include "test.h"

using namespace mik;

UI_pneumatic_screen::UI_pneumatic_screen() {
    UI_crt_pneumatic_scr();
}

std::shared_ptr<screen> UI_pneumatic_screen::get_pneumatic_screen() {
    return UI_pneumatic_scr;
}

void UI_pneumatic_screen::UI_crt_pneumatic_scr() {
    UI_pneumatic_scr = UI_crt_scr(0, 45, SCREEN_WIDTH, SCREEN_HEIGHT - 45);
    auto bg = UI_crt_bg(UI_crt_rec(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, pnematic_bg_color, UI_distance_units::pixels));

    const float txt_x = 27;
    const float txt_y = 37;

    auto expander_port_idx = std::make_shared<int>(0);

    struct port_entry {
        const char* label;
        const std::string* bg_color;
        float x, y;
        int port_id;
    };
    const port_entry ports[8] = {
        { "A", &pnematic_A_btn_bg_color, 48,  52-45,  PORT_A },
        { "B", &pnematic_B_btn_bg_color, 155, 52-45,  PORT_B },
        { "C", &pnematic_C_btn_bg_color, 264, 52-45,  PORT_C },
        { "D", &pnematic_D_btn_bg_color, 372, 52-45,  PORT_D },
        { "E", &pnematic_E_btn_bg_color, 48,  127-45, PORT_E },
        { "F", &pnematic_F_btn_bg_color, 155, 127-45, PORT_F },
        { "G", &pnematic_G_btn_bg_color, 264, 127-45, PORT_G },
        { "H", &pnematic_H_btn_bg_color, 372, 127-45, PORT_H },
    };
    std::vector<std::shared_ptr<UI_component>> port_btns, port_toggles;
    port_btns.reserve(8);
    port_toggles.reserve(8);
    for (int i = 0; i < 8; ++i) {
        const auto& p = ports[i];
        float x = p.x, y = p.y;
        int pid = p.port_id;
        const std::string& bg = *p.bg_color;
        auto btn = UI_crt_btn(UI_crt_img("", x, y, 60, 60, UI_distance_units::pixels),
            [expander_port_idx, pid](){ *expander_port_idx == 0 ? config_test_three_wire_port(pid) : config_test_three_wire_port(*expander_port_idx - 1, pid); });
        auto tgl = UI_crt_tgl(
            UI_crt_grp({ UI_crt_rec(x, y, 60, 60, bg, pnematic_port_btn_outline_color, 3, UI_distance_units::pixels), UI_crt_txt(p.label, x+txt_x, y+txt_y, pnematic_text_color, bg, UI_distance_units::pixels)}),
            [](){});
        tgl->set_states(
            UI_crt_grp({ UI_crt_rec(x, y, 60, 60, bg, pnematic_port_btn_outline_pressing_color, 3, UI_distance_units::pixels), UI_crt_txt(p.label, x+txt_x, y+txt_y, pnematic_text_color, bg, UI_distance_units::pixels)}),
            UI_crt_grp({ UI_crt_rec(x, y, 60, 60, bg, pnematic_port_btn_outline_pressed_color, 3, UI_distance_units::pixels), UI_crt_txt(p.label, x+txt_x, y+txt_y, pnematic_text_color, bg, UI_distance_units::pixels)})
        );
        port_btns.push_back(btn);
        port_toggles.push_back(tgl);
    }
    auto reset_port_btns = [port_toggles]() {
        for (auto& t : port_toggles)
            static_cast<toggle*>(t.get())->unpress();
    };

    int btn_height = 161;
    int btn_w = 30;
    int btn_h = 30;
    int txt_height = btn_height + 20;

    int seven_left_x = 162;
    int triport_x = seven_left_x - 155;
    int one_left_x = seven_left_x + 38;
    int port_text_x = seven_left_x + 71;
    int one_right = seven_left_x + 160;
    int seven_right = seven_left_x + 198;

    auto update_expander_txt = [](std::shared_ptr<UI_component> expander_txt, int idx) {
        auto* txt = static_cast<textbox*>(expander_txt.get());
        txt->set_text(idx == 0 ? "Brain" : "PORT" + to_string(idx));
    };

    auto title_txt = UI_crt_txtbox(
        "Triport: ",
        pnematic_text_color, pnematic_bg_color, text_align::CENTER,
        UI_crt_rec(triport_x, btn_height, 200, 30, pnematic_bg_color, UI_distance_units::pixels)
    );

    auto expander_txt = UI_crt_txtbox(
        "Brain",
        pnematic_text_color, pnematic_bg_color, text_align::CENTER,
        UI_crt_rec(port_text_x, btn_height, 90, 30, pnematic_bg_color, UI_distance_units::pixels)
    );

    auto expander_minus7_btn = UI_crt_btn(
        UI_crt_rec(seven_left_x, btn_height, btn_w, btn_h, pnematic_bg_color, pnematic_close_btn_outline_color, 2, UI_distance_units::pixels),
        [expander_port_idx, expander_txt, update_expander_txt, reset_port_btns](){
            *expander_port_idx = (*expander_port_idx - 7 + 22) % 22;
            update_expander_txt(expander_txt, *expander_port_idx);
            reset_port_btns();
        }
    );
    expander_minus7_btn->set_states(
        UI_crt_rec(seven_left_x, btn_height, btn_w, btn_h, pnematic_bg_color, pnematic_close_btn_pressing_color, 2, UI_distance_units::pixels),
        UI_crt_rec(seven_left_x, btn_height, btn_w, btn_h, pnematic_bg_color, pnematic_close_btn_pressed_color, 2, UI_distance_units::pixels)
    );
    auto expander_minus7_lbl = UI_crt_gfx(UI_crt_txt("-7", seven_left_x + 5, txt_height, pnematic_text_color, pnematic_bg_color, UI_distance_units::pixels));

    auto expander_minus1_btn = UI_crt_btn(
        UI_crt_rec(one_left_x, btn_height, btn_w, btn_h, pnematic_bg_color, pnematic_close_btn_outline_color, 2, UI_distance_units::pixels),
        [expander_port_idx, expander_txt, update_expander_txt, reset_port_btns](){
            *expander_port_idx = (*expander_port_idx - 1 + 22) % 22;
            update_expander_txt(expander_txt, *expander_port_idx);
            reset_port_btns();
        }
    );
    expander_minus1_btn->set_states(
        UI_crt_rec(one_left_x, btn_height, btn_w, btn_h, pnematic_bg_color, pnematic_close_btn_pressing_color, 2, UI_distance_units::pixels),
        UI_crt_rec(one_left_x, btn_height, btn_w, btn_h, pnematic_bg_color, pnematic_close_btn_pressed_color, 2, UI_distance_units::pixels)
    );
    auto expander_minus1_lbl = UI_crt_gfx(UI_crt_txt("-1", one_left_x + 5, txt_height, pnematic_text_color, pnematic_bg_color, UI_distance_units::pixels));

    auto expander_plus1_btn = UI_crt_btn(
        UI_crt_rec(one_right, btn_height, btn_w, btn_h, pnematic_bg_color, pnematic_close_btn_outline_color, 2, UI_distance_units::pixels),
        [expander_port_idx, expander_txt, update_expander_txt, reset_port_btns](){
            *expander_port_idx = (*expander_port_idx + 1) % 22;
            update_expander_txt(expander_txt, *expander_port_idx);
            reset_port_btns();
        }
    );
    expander_plus1_btn->set_states(
        UI_crt_rec(one_right, btn_height, btn_w, btn_h, pnematic_bg_color, pnematic_close_btn_pressing_color, 2, UI_distance_units::pixels),
        UI_crt_rec(one_right, btn_height, btn_w, btn_h, pnematic_bg_color, pnematic_close_btn_pressed_color, 2, UI_distance_units::pixels)
    );
    auto expander_plus1_lbl = UI_crt_gfx(UI_crt_txt("+1", one_right + 5, txt_height, pnematic_text_color, pnematic_bg_color, UI_distance_units::pixels));

    auto expander_plus7_btn = UI_crt_btn(
        UI_crt_rec(seven_right, btn_height, btn_w, btn_h, pnematic_bg_color, pnematic_close_btn_outline_color, 2, UI_distance_units::pixels),
        [expander_port_idx, expander_txt, update_expander_txt, reset_port_btns](){
            *expander_port_idx = (*expander_port_idx + 7) % 22;
            update_expander_txt(expander_txt, *expander_port_idx);
            reset_port_btns();
        }
    );
    expander_plus7_btn->set_states(
        UI_crt_rec(seven_right, btn_height, btn_w, btn_h, pnematic_bg_color, pnematic_close_btn_pressing_color, 2, UI_distance_units::pixels),
        UI_crt_rec(seven_right, btn_height, btn_w, btn_h, pnematic_bg_color, pnematic_close_btn_pressed_color, 2, UI_distance_units::pixels)
    );
    auto expander_plus7_lbl = UI_crt_gfx(UI_crt_txt("+7", seven_right + 5, txt_height, pnematic_text_color, pnematic_bg_color, UI_distance_units::pixels));

    std::vector<std::shared_ptr<UI_component>> all_comps = {bg, title_txt, expander_txt, expander_minus7_btn, expander_minus7_lbl, expander_minus1_btn, expander_minus1_lbl, expander_plus1_btn, expander_plus1_lbl, expander_plus7_btn, expander_plus7_lbl};
    for (int i = 0; i < 8; ++i) { all_comps.push_back(port_btns[i]); all_comps.push_back(port_toggles[i]); }
    UI_pneumatic_scr->add_UI_components(all_comps);
}
