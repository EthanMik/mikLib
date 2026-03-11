#pragma once

constexpr float BARREL_ROTATION = 2365;

extern float barrel_target;
extern bool override_barrel;
extern float barrel_max_voltage;

void start_barrel_task();


void matchload(float volts = 12);

void intake(float volts = 12);

void intake_rear(float volts = 12);
void stop_intake_rear();

void lift_barrel();
void drop_barrel();

void stop_matchload();

void stop_intake();
void outtake_rear(float volts = 12);

void score(float volts = 12);