#include "vex.h"

using namespace mik;

UI_graph_screen::UI_graph_screen() {
    UI_crt_graph_scr();
}

std::shared_ptr<screen> UI_graph_screen::get_graph_screen() {
    return(UI_graph_scr);
}

void UI_graph_screen::UI_crt_graph_scr() {
    UI_graph_scr = UI_crt_scr(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT - 45);
    auto bg = UI_crt_bg(UI_crt_rec(0, 45, SCREEN_WIDTH, SCREEN_HEIGHT - 45, graph_bg_color, UI_distance_units::pixels));
    
    auto legend_box = UI_crt_gfx(UI_crt_rec(3.72, .56, 1.19, 1.88, graph_legend_bg_color, graph_legend_outline_color, 2, UI_distance_units::inches));

    auto graph_table = UI_crt_gfx({UI_crt_rec(0.05, .73, 3.58, 1.71, graph_chart_bg_color, graph_chart_outline_color, 1, UI_distance_units::inches),
        UI_crt_ln(0.05, 1.13, 3.6, 1.13, graph_chart_outline_color, UI_distance_units::inches),
        UI_crt_ln(0.05, 1.59, 3.6, 1.59, graph_chart_outline_color, UI_distance_units::inches),
        UI_crt_ln(0.05, 2.04, 3.6, 2.04, graph_chart_outline_color, UI_distance_units::inches)
    });

    auto graph_name = UI_crt_gfx(UI_crt_txt("PID Output", 140, 62, graph_text_color, graph_bg_color, UI_distance_units::pixels));
    
    auto reset_btn = UI_crt_btn(UI_crt_grp({UI_crt_rec(366, 205, 98, 20, graph_reset_btn_bg_color, graph_reset_btn_outline_color, 2, UI_distance_units::pixels), UI_crt_txt("Reset", 392, 221, graph_text_color, graph_reset_btn_bg_color, UI_distance_units::pixels)}), 
        [this](){ reset_graph(); });
    reset_btn->set_states(
        UI_crt_grp({UI_crt_rec(366, 205, 98, 20, graph_reset_btn_bg_color, graph_reset_btn_pressing_color, 2, UI_distance_units::pixels), 
        UI_crt_txt("Reset", 392, 221, graph_text_color, graph_reset_btn_bg_color, UI_distance_units::pixels)}), 
        
        UI_crt_grp({UI_crt_rec(366, 205, 98, 20, graph_reset_btn_bg_color, graph_reset_btn_pressed_color, 2, UI_distance_units::pixels), 
        UI_crt_txt("Reset", 392, 221, graph_text_color, graph_reset_btn_bg_color, UI_distance_units::pixels)})
    );
    
    auto _y_axis = UI_crt_gfx(UI_crt_img("", 0, 0, 0, 0, UI_distance_units::pixels));
    y_axis = static_cast<graphic*>(_y_axis.get());

    auto _legend_labels = UI_crt_gfx({UI_crt_px(-1, -1, 0, UI_distance_units::pixels)});
    legend_labels = static_cast<graphic*>(_legend_labels.get());

    auto _graph_lines = UI_crt_gfx(UI_crt_px(-1, -1, 0, UI_distance_units::pixels));
    graph_lines = static_cast<graphic*>(_graph_lines.get());

    UI_graph_scr->add_UI_components({bg, legend_box, graph_table, graph_name, _y_axis, _legend_labels, reset_btn, _graph_lines});
}

void UI_graph_screen::reset_graph() {
    graph_lines->replace_graphic({UI_crt_px(-1, -1, 0, UI_distance_units::pixels)});
    legend_labels->replace_graphic({UI_crt_px(-1, -1, 0, UI_distance_units::pixels)});
    UI_graph_scr->refresh();
    graph();
}

void UI_graph_screen::set_plot_bounds(float y_min_bound, float y_max_bound, float x_min_bound, float x_max_bound, float x_step, float tick_rate_ms, int graphic_buffer) {
    this->y_max_bound = y_max_bound;
    this->y_min_bound = y_min_bound;
    this->x_min_bound = x_min_bound;
    this->x_max_bound = x_max_bound;
    this->x_step = x_step;
    this->tick_rate_ms = tick_rate_ms;
    this->graphic_buffer = graphic_buffer;

    float range = y_max_bound - y_min_bound;
    y_axis->replace_graphic({
        UI_crt_txt(to_string_float(y_max_bound, 3), 10, 90, graph_text_color, graph_bg_color, UI_distance_units::pixels),
        UI_crt_txt(to_string_float(y_min_bound + range * .75, 3), 10, 127, graph_text_color, graph_bg_color, UI_distance_units::pixels),
        UI_crt_txt(to_string_float(y_min_bound + range * .5, 3), 10, 172, graph_text_color, graph_bg_color, UI_distance_units::pixels),
        UI_crt_txt(to_string_float(y_min_bound + range * .25, 3), 10, 215, graph_text_color, graph_bg_color, UI_distance_units::pixels),
    });
}

void UI_graph_screen::set_plot(const std::vector<std::function<float(float)>>& plots, const std::vector<std::pair<std::string, uint32_t>>& labels) {
    this->plots = plots;
    this->labels = labels;
}

std::pair<float, float> UI_graph_screen::transform_plot(float x, float y) {
    const float x_norm = (x - x_min_bound) / (x_max_bound - x_min_bound);
    const float x_px = graph_left + (x_norm * graph_width);

    const float y_norm = (y - y_min_bound) / (y_max_bound - y_min_bound);
    const float y_px = graph_top + graph_height - (y_norm * graph_height);

    if (y_px > graph_height + graph_top || y_px < graph_top) {
        undefined = true;
    }
    
    return { x_px, y_px };
}


void UI_graph_screen::graph() {
    int txt_y = y_pos_label_txt;
    int rec_y = y_pos_label_rec;

    for (size_t i = 0; i < labels.size(); ++i) {
        legend_labels->add_graphic(UI_crt_rec(368, rec_y, 18, 18, labels[i].second, UI_distance_units::pixels));
        legend_labels->add_graphic(UI_crt_txt(labels[i].first, 389, txt_y, graph_text_color, graph_bg_color, UI_distance_units::pixels));
        rec_y += next_label_y_pos;
        txt_y += next_label_y_pos;
    }

    graph_task = vex::task([]() {
        float x = graph_scr->x_min_bound;

        std::vector<std::pair<int,int>> prev_pts;
        prev_pts.reserve(graph_scr->plots.size());

        for (auto& f : graph_scr->plots) {
            auto [px, py] = graph_scr->transform_plot(x, f(x));
            prev_pts.emplace_back(px, py);
        }

        while (x < graph_scr->x_max_bound) {
            while (Brain.Screen.pressing()) { vex::this_thread::sleep_for(100); }
            for (size_t i = 0; i < graph_scr->plots.size(); ++i) {
                graph_scr->undefined = false;
                auto [x_px, y_px] = graph_scr->transform_plot(x, graph_scr->plots[i](x));
                
                if (!graph_scr->undefined) {
                    uint32_t clr = (i < graph_scr->labels.size()) ? graph_scr->labels[i].second : 0x00FF3C00;
                    graph_scr->graph_lines->add_graphic(UI_crt_ln(prev_pts[i].first, prev_pts[i].second, x_px, y_px, clr, UI_distance_units::pixels));

                    if (graph_scr->graph_lines->get_size() >= graph_scr->graphic_buffer)
                    graph_scr->graph_lines->remove_first_graphic();
                }
                prev_pts[i] = {x_px, y_px};
            }

            x += graph_scr->x_step;
            vex::this_thread::sleep_for(graph_scr->tick_rate_ms);
        }
        return 0;
    });
}
