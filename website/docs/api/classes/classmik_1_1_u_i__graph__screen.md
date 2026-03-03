---
title: mik::UI_graph_screen

---

# mik::UI_graph_screen






`#include <graph_screen.h>`

## Public Functions

|                | Name           |
| -------------- | -------------- |
| | **[UI_graph_screen](/api/classes/classmik_1_1_u_i__graph__screen#function-ui-graph-screen)**() |
| std::shared_ptr< [screen](/api/classes/classmik_1_1screen) > | **[get_graph_screen](/api/classes/classmik_1_1_u_i__graph__screen#function-get-graph-screen)**() |
| void | **[graph](/api/classes/classmik_1_1_u_i__graph__screen#function-graph)**() |
| void | **[reset_graph](/api/classes/classmik_1_1_u_i__graph__screen#function-reset-graph)**() |
| void | **[set_plot](/api/classes/classmik_1_1_u_i__graph__screen#function-set-plot)**(const std::vector< std::function< float(float)> > & plots, const std::vector< std::pair< std::string, uint32_t > > & labels) |
| void | **[set_plot_bounds](/api/classes/classmik_1_1_u_i__graph__screen#function-set-plot-bounds)**(float y_min_bound, float y_max_bound, float x_min_bound, float x_max_bound, float x_step, float tick_rate_ms, int graphic_buffer =100) |

## Public Functions Documentation

### function UI_graph_screen

```cpp
UI_graph_screen()
```


### function get_graph_screen

```cpp
std::shared_ptr< screen > get_graph_screen()
```


### function graph

```cpp
void graph()
```


### function reset_graph

```cpp
void reset_graph()
```


### function set_plot

```cpp
void set_plot(
    const std::vector< std::function< float(float)> > & plots,
    const std::vector< std::pair< std::string, uint32_t > > & labels
)
```


### function set_plot_bounds

```cpp
void set_plot_bounds(
    float y_min_bound,
    float y_max_bound,
    float x_min_bound,
    float x_max_bound,
    float x_step,
    float tick_rate_ms,
    int graphic_buffer =100
)
```


-------------------------------

Updated on 2026-03-02 at 17:21:01 -0600