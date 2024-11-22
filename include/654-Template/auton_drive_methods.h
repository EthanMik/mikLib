#pragma once

#include "vex.h"

// Movement scheme developed my Thomas Grisamore
void turn_left_arc(float radius, float arcLength, float speed, bool precisionStop);
void turn_right_arc(float radius, float arcLength, float speed, bool precisionStop);
void go_smart_straight(float distance, float speed, bool precisionStop);
