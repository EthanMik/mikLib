#pragma once

#include "vex.h"

extern std::vector<std::pair<float, float>> curveNumeroUno; 
extern std::vector<std::pair<float, float>> curveNumeroDos; 
extern float curve_time;
extern float current_scalar;
extern float lead_scalar;
// Movement scheme developed my Thomas Grisamore
void turn_left_arc(float radius, float arcLength, float speed, bool precisionStop);
void turn_right_arc(float radius, float arcLength, float speed, bool precisionStop);
void go_smart_straight(float distance, float speed, bool precisionStop);
void standardized_vector_movement(float speed, const std::vector<std::pair<float, float>> &curvePattern);
void bezier(std::vector<float>& newDirection, const std::vector<std::pair<float, float>> &points);