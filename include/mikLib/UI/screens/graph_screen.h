#pragma once

#include "vex.h"

namespace mik {

class UI_graph_screen {
public:
    UI_graph_screen();
    std::shared_ptr<screen> get_graph_screen();

    void graph();
    void reset_graph();

    void set_plot_bounds(float y_min_bound, float y_max_bound, float x_min_bound, float x_max_bound, float x_step, float tick_rate_ms, int graphic_buffer = 100);
    void set_plot(const std::vector<std::function<float(float)>>& plots, const std::vector<std::pair<std::string, uint32_t>>& labels);
    
private:
    void UI_crt_graph_scr();

    std::pair<float, float> transform_plot(float x, float y);
    void enable_realtime_labels();

    float y_max_bound = 360;
    float y_min_bound = 0;
    float x_min_bound = 0;
    float x_max_bound = 30;
    float x_step = .02;
    float tick_rate_ms = 1;
    int graphic_buffer = 100;

    int graph_left = 10; 
    int graph_top = 74; 
    int graph_height = 160;
    int graph_width = 337;

    const int y_pos_label_rec = 63;
    const int y_pos_label_txt = 78;
    int next_label_y_pos = 22;

    bool undefined = false;

    std::vector<std::function<float(float)>> plots{};
    std::vector<std::pair<std::string, uint32_t>> labels{};
    
    vex::task graph_task;
    graphic* graph_lines; 
    graphic* legend_labels;
    graphic* legend_text;
    graphic* y_axis;

    std::shared_ptr<screen> UI_graph_scr = nullptr;
};
}