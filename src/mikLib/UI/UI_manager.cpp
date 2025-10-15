#include "vex.h"

using namespace mik;

std::vector<std::shared_ptr<mik::screen>> UI_render_queue = {};
static std::vector<std::shared_ptr<mik::screen>> UI_render_buffer;

std::shared_ptr<mik::UI_console_screen> console_scr = std::make_shared<mik::UI_console_screen>();
std::shared_ptr<mik::UI_auton_screen> auton_scr = std::make_shared<mik::UI_auton_screen>();
std::shared_ptr<mik::UI_graph_screen> graph_scr = std::make_shared<mik::UI_graph_screen>();
std::shared_ptr<mik::UI_config_screen> config_scr = std::make_shared<mik::UI_config_screen>();
static std::shared_ptr<mik::UI_component> console_tgl;
static std::shared_ptr<mik::UI_component> auton_tgl;
static std::shared_ptr<mik::UI_component> graph_tgl;
static std::shared_ptr<mik::UI_component> config_tgl;

static bool is_screen_swapping = false;

static bool local_needs_render_update = false;
static bool full_refresh = false;
static std::vector<std::shared_ptr<mik::screen>> temp;

static std::shared_ptr<mik::screen> selector_panel_scr;

static void create_UI_files() {
    if (!Brain.SDcard.isInserted()) {
        return;
    }
    if (!Brain.SDcard.exists("pid_data.txt")) {
        Brain.SDcard.savefile("pid_data.txt", nullptr, 0);
    }
    if (!Brain.SDcard.exists("auton.txt")) {
        Brain.SDcard.savefile("auton.txt", nullptr, 0);
    }

}

void UI_init() {
    create_UI_files();
    // auto main_bg = UI_crt_gfx(UI_crt_img("background_main.png", 0, 0, 0, 0, mik::UI_distance_units::pixels));

    std::shared_ptr<mik::drawable> main_bg_img = std::make_shared<mik::image>(mikLib_logo, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, mik::UI_distance_units::pixels);
    std::shared_ptr<mik::UI_component> main_bg = std::make_shared<mik::graphic>(main_bg_img);
    
    auto main_bg_scr = UI_crt_scr(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    main_bg_scr->add_UI_component(main_bg);

    // Initialize selector panel
    selector_panel_scr = UI_crt_scr(0, 0, SCREEN_WIDTH + 160, 45);
    selector_panel_scr->add_scroll_bar(UI_crt_rec(0, 0, 40, 3, selector_scroll_bar_color, mik::UI_distance_units::pixels), mik::screen::alignment::BOTTOM);

    // Init config selector toggle
    config_tgl = UI_crt_tgl(UI_crt_grp({
        UI_crt_rec(0, 0, 160, 45, selector_bg_color, mik::UI_distance_units::pixels),
        UI_crt_rec(0, 0, 1, 35, selector_outline_color, mik::UI_distance_units::pixels), 
        UI_crt_rec(159, 0, 1, 35, selector_outline_color, mik::UI_distance_units::pixels), 
        UI_crt_rec(0, 35, 160, 5, selector_bg_pressed_color, mik::UI_distance_units::pixels),
        UI_crt_txt("Config", 48, 23, selector_text_color, selector_bg_color, mik::UI_distance_units::pixels)}),
        nullptr, 1
    );
    config_tgl->set_states(UI_crt_grp({
        UI_crt_rec(0, 0, 160, 45, selector_bg_pressing_color, mik::UI_distance_units::pixels),
        UI_crt_rec(0, 40, 160, 5, selector_bg_color, mik::UI_distance_units::pixels),
        UI_crt_rec(0, 35, 160, 5, selector_outline_pressing_color, mik::UI_distance_units::pixels),
        UI_crt_txt("Config", 48, 23, selector_text_color, selector_bg_pressing_color, mik::UI_distance_units::pixels)}),
        
        UI_crt_grp({
        UI_crt_rec(0, 0, 160, 45, selector_bg_pressed_color, mik::UI_distance_units::pixels),
        UI_crt_rec(0, 40, 160, 5, selector_bg_color, mik::UI_distance_units::pixels),
        UI_crt_rec(0, 35, 160, 5, selector_outline_pressed_color, mik::UI_distance_units::pixels),
        UI_crt_txt("Config", 48, 23, selector_text_color, selector_bg_pressed_color, mik::UI_distance_units::pixels)}));
    config_tgl->set_callback([=](){ 
        UI_select_scr(config_scr->get_config_screen());
    } 
    );

    // Init auton selector toggle
    auton_tgl = UI_crt_tgl(UI_crt_grp({
        UI_crt_rec(160, 0, 160, 45, selector_bg_color, mik::UI_distance_units::pixels),
        UI_crt_rec(160, 0, 1, 35, selector_outline_color, mik::UI_distance_units::pixels), 
        UI_crt_rec(159+160, 0, 1, 35, selector_outline_color, mik::UI_distance_units::pixels), 
        UI_crt_rec(160, 35, 160, 5, selector_bg_pressed_color, mik::UI_distance_units::pixels),
        UI_crt_txt("Autons", 48+160, 23, selector_text_color, selector_bg_color, mik::UI_distance_units::pixels)}),
        nullptr, 1
    );
    auton_tgl->set_states(UI_crt_grp({
        UI_crt_rec(160, 0, 160, 45, selector_bg_pressing_color, mik::UI_distance_units::pixels),
        UI_crt_rec(160, 40, 160, 5, selector_bg_color, mik::UI_distance_units::pixels),
        UI_crt_rec(160, 35, 160, 5, selector_outline_pressing_color, mik::UI_distance_units::pixels),
        UI_crt_txt("Autons", 48+160, 23, selector_text_color, selector_bg_pressing_color, mik::UI_distance_units::pixels)}),
        
        UI_crt_grp({
        UI_crt_rec(160, 0, 160, 45, selector_bg_pressed_color, mik::UI_distance_units::pixels),
        UI_crt_rec(160, 40, 160, 5, selector_bg_color, mik::UI_distance_units::pixels),
        UI_crt_rec(160, 35, 160, 5, selector_outline_pressed_color, mik::UI_distance_units::pixels),
        UI_crt_txt("Autons", 48+160, 23, selector_text_color, selector_bg_pressed_color, mik::UI_distance_units::pixels)}));
    auton_tgl->set_callback([=](){ 
        UI_select_scr(auton_scr->get_auton_screen());
    } 
    );

    // Init graph selector toggle
    graph_tgl = UI_crt_tgl(UI_crt_grp({
        UI_crt_rec(320, 0, 160, 45, selector_bg_color, mik::UI_distance_units::pixels),
        UI_crt_rec(320, 0, 1, 35, selector_outline_color, mik::UI_distance_units::pixels), 
        UI_crt_rec(159+160+160, 0, 1, 35, selector_outline_color, mik::UI_distance_units::pixels), 
        UI_crt_rec(320, 35, 160, 5, selector_bg_pressed_color, mik::UI_distance_units::pixels),
        UI_crt_txt("Graph", 56+160+160, 23, selector_text_color, selector_bg_color, mik::UI_distance_units::pixels)}),
        nullptr, 1
    );
    graph_tgl->set_states(UI_crt_grp({
        UI_crt_rec(320, 0, 160, 45, selector_bg_pressing_color, mik::UI_distance_units::pixels),
        UI_crt_rec(320, 40, 160, 5, selector_bg_color, mik::UI_distance_units::pixels),
        UI_crt_rec(320, 35, 160, 5, selector_outline_pressing_color, mik::UI_distance_units::pixels),
        UI_crt_txt("Graph", 56+160+160, 23, selector_text_color, selector_bg_pressing_color, mik::UI_distance_units::pixels)}),
        
        UI_crt_grp({
        UI_crt_rec(320, 0, 160, 45, selector_bg_pressed_color, mik::UI_distance_units::pixels),
        UI_crt_rec(320, 40, 160, 5, selector_bg_color, mik::UI_distance_units::pixels),
        UI_crt_rec(320, 35, 160, 5, selector_outline_pressed_color, mik::UI_distance_units::pixels),
        UI_crt_txt("Graph", 56+160+160, 23, selector_text_color, selector_bg_pressed_color, mik::UI_distance_units::pixels)}));
    graph_tgl->set_callback([=](){ 
        UI_select_scr(graph_scr->get_graph_screen());
    } 
    );

    // Init console selector toggle
    console_tgl = UI_crt_tgl(UI_crt_grp({
        UI_crt_rec(480, 0, 160, 45, selector_bg_color, mik::UI_distance_units::pixels),
        UI_crt_rec(480, 0, 1, 35, selector_outline_color, mik::UI_distance_units::pixels), 
        UI_crt_rec(159+160+160+160, 0, 1, 35, selector_outline_color, mik::UI_distance_units::pixels), 
        UI_crt_rec(480, 35, 160, 5, selector_bg_pressed_color, mik::UI_distance_units::pixels),
        UI_crt_txt("Console", 48+160+160+160, 23, selector_text_color, selector_bg_color, mik::UI_distance_units::pixels)}),
        nullptr, 1
    );
    console_tgl->set_states(UI_crt_grp({
        UI_crt_rec(480, 0, 160, 45, selector_bg_pressing_color, mik::UI_distance_units::pixels),
        UI_crt_rec(480, 40, 160, 5, selector_bg_color, mik::UI_distance_units::pixels),
        UI_crt_rec(480, 35, 160, 5, selector_outline_pressing_color, mik::UI_distance_units::pixels),
        UI_crt_txt("Console", 48+160+160+160, 23, selector_text_color, selector_bg_pressing_color, mik::UI_distance_units::pixels)}),
        
        UI_crt_grp({
        UI_crt_rec(480, 0, 160, 45, selector_bg_pressed_color, mik::UI_distance_units::pixels),
        UI_crt_rec(480, 40, 160, 5, selector_bg_color, mik::UI_distance_units::pixels),
        UI_crt_rec(480, 35, 160, 5, selector_outline_pressed_color, mik::UI_distance_units::pixels),
        UI_crt_txt("Console", 48+160+160+160, 23, selector_text_color, selector_bg_pressed_color, mik::UI_distance_units::pixels)}));
    console_tgl->set_callback([=](){ 
        UI_select_scr(console_scr->get_console_screen());
    } 
    );

    selector_panel_scr->add_UI_components({console_tgl, auton_tgl, graph_tgl, config_tgl});

    // init rendering
    UI_render_queue = {main_bg_scr, selector_panel_scr};
    for (const auto& scr : UI_render_queue) {
        scr->refresh();
    }
}

void UI_controller_auton_selector() {
    auton_scr->enable_controller_overlay();
}

void UI_select_scr(std::shared_ptr<mik::screen> scr) {
    if (scr == console_scr->get_console_screen()) {
        auto* tgl = static_cast<mik::toggle*>(console_tgl.get());
        tgl->press();
        UI_execute_selector_toggles(console_tgl, selector_panel_scr, true);
        UI_swap_screens({console_scr->get_console_screen(), selector_panel_scr});
    } else if (scr == config_scr->get_config_screen()) {
        auto* tgl = static_cast<mik::toggle*>(config_tgl.get());
        tgl->press(); 
        UI_execute_selector_toggles(config_tgl, selector_panel_scr, true);
        UI_swap_screens({config_scr->get_config_screen(), selector_panel_scr});
    } else if (scr == auton_scr->get_auton_screen()) {
        auto* tgl = static_cast<mik::toggle*>(auton_tgl.get());
        tgl->press();
        UI_execute_selector_toggles(auton_tgl, selector_panel_scr, true);
        UI_swap_screens({auton_scr->get_auton_screen(), selector_panel_scr}); 
    } else if (scr == graph_scr->get_graph_screen()) {
        auto* tgl = static_cast<mik::toggle*>(graph_tgl.get());
        tgl->press();
        UI_execute_selector_toggles(graph_tgl, selector_panel_scr, true);
        UI_swap_screens({graph_scr->get_graph_screen(), selector_panel_scr}); 
    }
}

void UI_swap_screens(const std::vector<std::shared_ptr<mik::screen>>& scr) {
    UI_render_buffer = scr;
    is_screen_swapping = true;
}

void UI_render() {
    while(1) {
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
                }
                if (screen->needs_full_refresh()) {
                    temp = UI_render_queue;
                    break;
                }
            }
        }

        while (local_needs_render_update || full_refresh) {
            for (const auto& screen : temp) {
                screen->render(full_refresh);
            }
            if (Brain.Screen.render(true, true)) {  
                local_needs_render_update = false;
                full_refresh = false;
            }
            vex::this_thread::sleep_for(20);
        }
        temp.clear();

        vex::this_thread::sleep_for(20);
    }
}

void UI_execute_selector_toggles(std::shared_ptr<mik::UI_component> tgl, std::shared_ptr<mik::screen> scr, bool lock_toggles) {
    int tgl_id = UI_decode_toggle_group(tgl->get_ID());
    int tgl_unique_id = tgl->get_ID();

    if (tgl_id <= 0) { return; }

    auto* toggle_component = static_cast<mik::toggle*>(tgl.get());

    if (toggle_component->get_toggle_state() == true && lock_toggles) {
        toggle_component->lock_toggle();
    }

    for (const auto& component : scr->get_UI_components()) {
        if (component->get_ID() == tgl_unique_id) {
            continue;
        }
        if (tgl_id == UI_decode_toggle_group(component->get_ID())) {
            auto* toggle_component = static_cast<mik::toggle*>(component.get());
            toggle_component->unpress();
        }
    }
}
