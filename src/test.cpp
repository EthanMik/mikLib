#include "vex.h"

void test_constants() {
  	default_constants();
}

void test_drive() {
	chassis.drive_distance(6);
	chassis.drive_distance(12);
	chassis.drive_distance(18);
	chassis.drive_distance(-36);
}

void test_heading() {
	chassis.drive_distance(10, { .heading = 15 });
	chassis.drive_distance(20, { .heading = 45 });
	chassis.drive_distance(-30, { .heading = 0 });
}

void test_turn() {
	chassis.turn_to_angle(5);
	chassis.turn_to_angle(30);
	chassis.turn_to_angle(90);
	chassis.turn_to_angle(225);
	chassis.turn_to_angle(180, { .turn_direction = ccw });
	chassis.turn_to_angle(359, { .turn_direction = cw });
}

void test_swing() {
	chassis.left_swing_to_angle(110);
	chassis.right_swing_to_angle(0);
}

void test_full() {
	chassis.set_heading(0);

	chassis.drive_distance(24);
	chassis.turn_to_angle(-45);
	chassis.drive_distance(-36);
	chassis.right_swing_to_angle(-90);
	chassis.drive_distance(24);
	chassis.turn_to_angle(0);
}

void test_odom_drive() {
	chassis.drive_to_point(0, 6);
	chassis.drive_to_point(0, 18);
	chassis.drive_to_point(0, 36);
	chassis.drive_to_point(0, 0);
}

void test_odom_heading() {
	chassis.drive_to_point(5, 18);
	chassis.drive_to_point(20, 35);
	chassis.drive_to_point(0, 0);
	chassis.turn_to_angle(0);
}

void test_odom_turn() {
	chassis.turn_to_point(0.437,  5);
	chassis.turn_to_point(2.887,  5);
	chassis.turn_to_point(5, 0);
	chassis.turn_to_point(-5, -5);
	chassis.turn_to_point(0,  -5, {.turn_direction = ccw});
	chassis.turn_to_point(0,  5, {.turn_direction = cw});
}

void test_odom_swing() {	
	chassis.left_swing_to_point(24, 12);
	chassis.right_swing_to_point(12, 24);
}

void test_odom_full() {
	chassis.set_coordinates(0, 0, 0);

	Brain.resetTimer();
	chassis.drive_to_point(0, 24);
	print(Brain.Timer.time(msec) / 1000);

	Brain.resetTimer();
	chassis.turn_to_point(24, 0, { .angle_offset = 180 });
	print(Brain.Timer.time(msec) / 1000);

	Brain.resetTimer();
	chassis.drive_to_point(24, 0);
	print(Brain.Timer.time(msec) / 1000);

	Brain.resetTimer();
	chassis.right_swing_to_point(0, 0);
	print(Brain.Timer.time(msec) / 1000);

	Brain.resetTimer();
	chassis.drive_to_point(0, 0);
	print(Brain.Timer.time(msec) / 1000);

	Brain.resetTimer();
	chassis.turn_to_angle(0);
	print(Brain.Timer.time(msec) / 1000);
	
}

void test_boomerang() {
	chassis.set_coordinates(0, 0, 0);

    chassis.drive_to_pose(24, 24, 90);
    chassis.drive_to_pose(24, 0, 90);
    chassis.drive_to_pose(0, 24, 270);
    chassis.drive_to_pose(0, 0, 180);
    chassis.turn_to_angle(0);
}

pid_data data;
std::vector<std::string> error_data;
static vex::task user_control_task;
static vex::task update_controller_scr;
static vex::task pid_tuner_task;
static vex::task test_movements_task;
static float predicted_distance = 0;
static float prev_desired_distance = 0;
static std::function<void()> test_movements_func;
static bool testing_odom = false;


bool config_swap_test_mode() {
	testing_odom = !testing_odom;
	test_constants();
	return testing_odom;
}

bool config_is_testing_odom() {
  return testing_odom;
}

void config_tune_drive() {
	data.variables = { 
		{"drive_kp: ", chassis.drive_kp}, 
		{"drive_ki: ", chassis.drive_ki}, 
		{"drive_kd: ", chassis.drive_kd}, 
		{"drive_starti: ", chassis.drive_starti}, 
		{"drive_max_volt: ", chassis.drive_max_voltage}, 
		{"drive_stl_err: ", chassis.drive_settle_error}, 
		{"drive_stl_tm: ", chassis.drive_settle_time}, 
		{"drive_tmout: ", chassis.drive_timeout}, 
		{"drive_slew ", chassis.drive_slew},
		{"drive_ext_err: ", chassis.drive_exit_error}
		

		// You can add more parameters to tune

		// {"heading_kp: ", chassis.heading_kp}, 
		// {"heading_ki: ", chassis.heading_ki}, 
		// {"heading_kd: ", chassis.heading_kd}, 
		// {"heading_starti: ", chassis.heading_starti}, 
		// {"max_volt: ", chassis.heading_max_voltage},
		// {"heading_slew ", chassis.heading_slew}
	};

	std::function<float(double)> actual_plot = [](double x){ return chassis.get_forward_tracker_position(); };

	std::function<float(double)> set_point_plot = [](double x){ 
		if (chassis.desired_distance != prev_desired_distance) {
			predicted_distance += chassis.desired_distance;
			prev_desired_distance = chassis.desired_distance; 
		}
		return predicted_distance; 
	};

	if (testing_odom) {
		actual_plot = [](double x){ return hypot(chassis.get_X_position(), chassis.get_Y_position()); };
		set_point_plot = [](double x){ return hypot(chassis.desired_X_position, chassis.desired_Y_position); };
	}

	int y_min = -30;
	int y_max = 50;
	int time_spent_graphing_ms = 6000; 

	graph_scr->set_plot_bounds(y_min, y_max, 0, time_spent_graphing_ms, 1, 1);
	graph_scr->set_plot({actual_plot, set_point_plot}, {{"Actual", 0x002E8B59}, {"SetPoint", 0x00FA8072}});

	UI_select_scr(graph_scr->get_graph_screen()); 

	test_movements_func = [](){
	chassis.forward_tracker.resetPosition();
	chassis.set_coordinates(0, 0, 0);
	predicted_distance = 0;
	prev_desired_distance = 0;
	graph_scr->reset_graph();
	graph_scr->graph();

	if (testing_odom) {
		test_odom_drive();
	} else {
		test_drive();
	}
	};

	PID_tuner();
}

void config_tune_heading() {
	data.variables = { 
		{"heading_kp: ", chassis.heading_kp}, 
		{"heading_ki: ", chassis.heading_ki}, 
		{"heading_kd: ", chassis.heading_kd}, 
		{"heading_starti: ", chassis.heading_starti}, 
		{"max_volt: ", chassis.heading_max_voltage},
		{"heading_slew: ", chassis.heading_slew}
	};

	int y_min = -30;
	int y_max = 60;
	int time_spent_graphing_ms = 5000; 

	graph_scr->set_plot_bounds(y_min, y_max, 0, time_spent_graphing_ms, 1, 1);
	graph_scr->set_plot({
	[](double x) { return chassis.inertial.rotation(); }, 
	[](double x) {
		float heading = chassis.desired_heading;
		if (heading < 0) {
			// Accounting for when drive_to_point() drives backwards
			return heading + 180;
		}
		return heading;
	}},
	{{"Actual", 0x002E8B59}, 
	{"SetPoint", 0x00FA8072}}
	);

	UI_select_scr(graph_scr->get_graph_screen()); 

	test_movements_func = [](){
	chassis.set_coordinates(0, 0, 0);
	graph_scr->reset_graph();
	graph_scr->graph();

	if (testing_odom) {
		test_odom_heading();
	} else {
		test_heading();
	}
	};

	PID_tuner();
}


void config_tune_turn() {  
	data.variables = { 
		{"turn_kp: ", chassis.turn_kp}, 
		{"turn_ki: ", chassis.turn_ki},
		{"turn_kd: ", chassis.turn_kd}, 
		{"turn_starti: ", chassis.turn_starti}, 
		{"turn_max_volt: ", chassis.turn_max_voltage}, 
		{"turn_stl_err: ", chassis.turn_settle_error}, 
		{"turn_stl_tm: ", chassis.turn_settle_time}, 
		{"turn_tmout: ", chassis.turn_timeout},
		{"Turn_slew: ", chassis.turn_slew},
		{"Turn_exit_err: ", chassis.turn_exit_error}
	};

  int y_min = -10;
  int y_max = 370;
  int time_spent_graphing_ms = 10000; 

	graph_scr->set_plot_bounds(y_min, y_max, 0, time_spent_graphing_ms, 1, 1);
	graph_scr->set_plot({
		[](double x){ return chassis.get_absolute_heading(); }, 
		[](double x){ return reduce_0_to_360(chassis.desired_angle); }},
		{{"Actual", 0x002E8B59}, 
		{"SetPoint", 0x00FA8072}}
	);
	UI_select_scr(graph_scr->get_graph_screen()); 

	test_movements_func = [](){
		chassis.set_coordinates(0, 0, 0);
		graph_scr->reset_graph();
		graph_scr->graph();

		if (testing_odom) {
			test_odom_turn();
		} else {
			test_turn();
		}
	};

	PID_tuner();
}

void config_tune_swing() {
	data.variables = { 
		{"swing_kp: ", chassis.swing_kp }, 
		{"swing_ki: ", chassis.swing_ki }, 
		{"swing_kd: ", chassis.swing_kd}, 
		{"swing_starti: ", chassis.swing_starti}, 
		{"swing_max_volt: ", chassis.swing_max_voltage}, 
		{"swing_opp_volt: ", chassis.swing_opposite_voltage}, 
		{"swing_stl_err: ", chassis.swing_settle_error}, 
		{"swing_stl_tm: ", chassis.swing_settle_time}, 
		{"swing_tmout: ", chassis.swing_timeout},
		{"swing_slew: ", chassis.swing_slew},
		{"swing_ext_err: ", chassis.swing_exit_error}
	};

	int y_min = -20;
	int y_max = 370;
	int time_spent_graphing_ms = 5000; 

	graph_scr->set_plot_bounds(y_min, y_max, 0, time_spent_graphing_ms, 1, 1);
	graph_scr->set_plot({
		[](double x){ return chassis.get_absolute_heading(); }, 
		[](double x){ return chassis.desired_angle; }},
		{{"Actual", 0x002E8B59}, 
		{"SetPoint", 0x00FA8072}}
	);

	UI_select_scr(graph_scr->get_graph_screen()); 

	test_movements_func = [](){
	chassis.set_coordinates(0, 0, 0);
	graph_scr->reset_graph();
	graph_scr->graph();

	if (testing_odom) {
		test_odom_swing();
	} else {
		test_swing();
	}
	};

	PID_tuner();
}

static int get_flicker_index(const std::string& value_str, float place) {
  int dot_pos = value_str.find('.');
  if (dot_pos == (int)std::string::npos) {
		int idx = value_str.size() - 1 - place; 
		return idx;
  } else {
	int idx;
	if (place > 0) {
		idx = dot_pos + place; 
	} else {
		idx = dot_pos - 1 + place;
	}
	return idx;
  }
}

static int get_power(float n) {
	if (n <= 0) { return 1; }
	int power = 1;
	while (n >= 10) {
		n /= 10;
		power *= 10;
	}
	return power;
}

void PID_tuner() {
  auton_scr->disable_controller_overlay();
  disable_user_control(true);
  vex::task test;

  user_control_task = vex::task([](){
	while(1) {
	  	chassis.control(chassis.selected_drive_mode);
	  	vex::this_thread::sleep_for(5);
	}
	return 0;
  });

  pid_tuner_task = vex::task([](){
	static int flicker = 0;
	while(1) {
	data.max = std::max(3, data.index+1);
	data.min = data.max - 3;

	int j = 0;
	for(int i = data.min; i < data.max; ++i) {
	  Controller.Screen.setCursor(j+1, 1);
	  j++;
	  std::string var = to_string_float(data.variables[i].second, 3, false);

	  if (data.index == i) {
		flicker++;
		if(flicker % 2 == 0) {
		  int idx = get_flicker_index(var, -std::log10(1.0 / data.modifer_scale));
		  if(idx >= 0 && idx < (int)var.size()) {
			if(std::isdigit(var[idx])) {
			  if(var[idx] == '1') {
				var[idx] = '-';
			  } else {
				var[idx] = '_';
			  }
			}
		  }
		}
		else{}
	  }

	  Controller.Screen.print((data.variables[i].first + var).c_str());
	  
	  if (data.index == i) { 
		data.var_upper_size = get_power(data.variables[i].second);

		if (data.needs_update) {
			remove_duplicates_SD_file("pid_data.txt", data.variables[i].first);
			data.variables[i].second += data.modifier;
			write_to_SD_file("pid_data.txt", (data.variables[i].first + to_string(data.variables[i].second)));
			data.needs_update = false;
		}
		Controller.Screen.print("<            "); 
	  } else { 
		Controller.Screen.print("             "); 
	  }
	}

	this_thread::sleep_for(20);
	}
	return 0;
  });
  update_controller_scr = vex::task([](){
	while(1) {
		if (btnUp_new_press(Controller.ButtonUp.pressing())) {
			if (data.index > 0) { data.index--; }
				data.modifer_scale = 1;
		}
		if (btnDown_new_press(Controller.ButtonDown.pressing())) {
			if (data.index < data.variables.size() - 1) { data.index++; }
			data.modifer_scale = 1;
		}
		if (btnRight_new_press(Controller.ButtonRight.pressing())) {
			data.modifer_scale *= 10;
			if (data.modifer_scale > 1000) {
				data.modifer_scale = 1000;
			}
		}
		if (btnLeft_new_press(Controller.ButtonLeft.pressing())) {
			data.modifer_scale /= 10;
			if (data.modifer_scale < (1 / data.var_upper_size)) {
				data.modifer_scale = (1 / data.var_upper_size);
			}
		}
		if (btnY_new_press(Controller.ButtonY.pressing())) {
			data.modifier = -1 / data.modifer_scale;
			data.needs_update = true;
		}
		if (btnA_new_press(Controller.ButtonA.pressing())) {
			data.modifier = 1 / data.modifer_scale;
			data.needs_update = true;
		}
		if (btnX_new_press(Controller.ButtonX.pressing())) {
			user_control_task.suspend();
			test_movements_task = vex::task([](){
				test_movements_func();
				return 0;
			});
		}
		if (btnB_new_press(Controller.ButtonB.pressing())) {
			static uint32_t last_b_press = 0;
			uint32_t now = vex::timer::system();
			if (now - last_b_press < 200) {
				pid_tuner_task.stop();
				user_control_task.stop();
				test_movements_task.stop();
				chassis.stop_drive(vex::coast);
				auton_scr->enable_controller_overlay();
				disable_user_control();
				return 0;
			}
			last_b_press = now;
			user_control_task.resume();
			test_movements_task.stop();
			chassis.stop_drive(vex::coast);
		}
		task::sleep(20);
	}
	return 0;
  });
}

std::vector<mik::motor*> config_get_motors() {
	return mik::motor_registry();
}


void stop_all_motors(vex::brakeType mode) {
	for (auto motor : config_get_motors()) {
		motor->stop(mode);
	}
}

void set_brake_all_motors(vex::brakeType mode) {  
	for (auto motor : config_get_motors()) {
		motor->setBrake(mode);
	}
}

int run_diagnostic() {
	error_data.clear();
	int errors = 0;
	if (!Brain.SDcard.isInserted()) {
		error_data.push_back("SD is not inserted");
		errors++;
	}
	if (!chassis.inertial.installed()) {
		std::string port = port_to_string(chassis.inertial.index());
		error_data.push_back("Inertial [" + port + "] is disconnected");
		errors++;
	}
	if (!chassis.forward_tracker.installed() && chassis.tracker_mode == mik::tracker_mode::FORWARD_TRACKER) {
		std::string port = port_to_string(chassis.forward_tracker.index());

		error_data.push_back("Forward Tracker [" + port + "] is disconnected");
		errors++;
	}
	if (!chassis.sideways_tracker.installed() && chassis.sideways_tracker_used) {
		std::string port = port_to_string(chassis.sideways_tracker.index());
		error_data.push_back("Sideways Tracker [" + port + "] is disconnected");
		errors++;
	}
	for (auto motor : config_get_motors()) {
		if (!motor->installed()) {
			std::string port = port_to_string(motor->index());
			error_data.push_back(motor->name() + " [" + port +  "] is disconnected");
			errors++;
		}   
	}
	for (auto& distance : chassis.reset_sensors.get_distance_sensors()) {
		if (!distance.installed()) {
			std::string port = port_to_string(distance.index());
			error_data.push_back(distance.name() + " [" + port +  "] is disconnected");
			errors++;
		}
	}
	if (errors <= 0) {
		error_data.push_back("No issues found");
	}

	return errors;
}

void config_add_pid_output_SD_console() {
	if (!Brain.SDcard.isInserted()) { return; }
	UI_select_scr(console_scr->get_console_screen());
	console_scr->reset();
	vex::task e([](){
		std::vector<std::string> data_arr = get_SD_file_txt("pid_data.txt");
		for (const auto& line : data_arr) {
			console_scr->add(line, false);
		}
		return 0;
	});
}

void config_spin_all_motors() {
	UI_select_scr(console_scr->get_console_screen()); 
	console_scr->reset();
	disable_user_control(true);
	vex::task spin_mtrs([](){
		for (auto motor : config_get_motors()) { 
			std::string data = (motor->name() + ": " + port_to_string(motor->index()) + ", fwd, 6 volt");
			console_scr->add(std::string(data), [](){ return ""; });
			motor->spin(fwd, 6, volt);
			vex::task::sleep(1000);
			motor->stop();
			vex::task::sleep(1000);
		}
		enable_user_control();
	return 0;
  });
}

void config_motor_wattage() {
	console_scr->reset();
	UI_select_scr(console_scr->get_console_screen()); 

	vex::task watt([](){
		console_scr->add("right_drive: ", []() { return to_string_float(chassis.right_drive.averagePower(), 5, false) + " Watts    "; });
		console_scr->add("left_drive: ", []() { return to_string_float(chassis.left_drive.averagePower(), 5, false) + " Watts    "; });

		for (auto motor : config_get_motors()) {
			console_scr->add(motor->name() + ": ", [motor]() { return to_string_float(motor->power(), 5, false) + " Watts    "; });
		}
		return 0;
	});
}

void config_motor_temp() {
	console_scr->reset();
	UI_select_scr(console_scr->get_console_screen()); 
  
  	vex::task temp([](){
		console_scr->add("right_drive: ", []() { return to_string_float(chassis.right_drive.averageTemperature(), 0, true) + "%% overheated    "; });
		console_scr->add("left_drive: ", []() { return to_string_float(chassis.left_drive.averageTemperature(), 0, true) + "%% overheated    "; });
		for (auto motor : config_get_motors()) {
			console_scr->add(motor->name() + ": ", [motor]() { return to_string_float(motor->temperature(), 0, true) + "%% overheated    "; });
		}
		return 0;
  });

}

void config_motor_torque() {
	console_scr->reset();
	UI_select_scr(console_scr->get_console_screen()); 
	
	vex::task temp([](){		
		console_scr->add("right_drive: ", []() { return to_string_float(chassis.right_drive.averageTorque(), 5, false) + " Nm    "; });
		console_scr->add("left_drive: ", []() { return to_string_float(chassis.left_drive.averageTorque(), 5, false) + " Nm    "; });
		for (auto motor : config_get_motors()) {
			console_scr->add(motor->name() + ": ", [motor]() { return to_string_float(motor->torque(), 5, false) + " Nm    "; });
		}
		return 0;
	});

}

void config_motor_efficiency() {
	console_scr->reset();
	UI_select_scr(console_scr->get_console_screen()); 

	vex::task temp([](){
		console_scr->add("right_drive: ", []() { return to_string_float(chassis.right_drive.averageEfficiency(), 5, false) + "%% Eff    "; });
		console_scr->add("left_drive: ", []() { return to_string_float(chassis.left_drive.averageEfficiency(), 5, false) + "%% Eff     "; });
		for (auto motor : config_get_motors()) {
			console_scr->add(motor->name() + ": ", [motor]() { return to_string_float(motor->efficiency(), 5, false) + "%% Eff    "; });
		}
		return 0;
	});

}

void config_motor_current() {
	console_scr->reset();
	UI_select_scr(console_scr->get_console_screen()); 

	vex::task temp([](){
		console_scr->add("right_drive: ", []() { return to_string_float(chassis.right_drive.averageCurrent(), 5, false) + " Amps    "; });
		console_scr->add("left_drive: ", []() { return to_string_float(chassis.left_drive.averageCurrent(), 5, false) + " Amps    "; });
		for (auto motor : config_get_motors()) {
			console_scr->add(motor->name() + ": ", [motor]() { return to_string_float(motor->current(), 5, false) + " Amps    "; });
		}
		return 0;
	});
}

void config_odom_data() {
	console_scr->reset();
	UI_select_scr(console_scr->get_console_screen()); 

	vex::task temp([](){
		if (!chassis.position_tracking) {
			chassis.set_coordinates(0, 0, 0);
		}
	
		console_scr->add("X: ", [](){ return chassis.get_X_position(); });
		console_scr->add("Y: ", [](){ return chassis.get_Y_position(); });
		console_scr->add("Heading: ", [](){ return chassis.get_absolute_heading(); });
		console_scr->add("Rotation: ", [](){ return chassis.inertial.rotation(); });
		console_scr->add("Forward Tracker: ", [](){ return chassis.get_forward_tracker_position(); });
		console_scr->add("Sideways Tracker: ", [](){ return chassis.get_sideways_tracker_position(); });

		console_scr->add("Right Drive: ", [](){ return chassis.get_right_drive_position(); });
		console_scr->add("Left Drive: ", [](){ return chassis.get_left_drive_position(); });

		for (size_t i = 0; i < chassis.right_drive.getMotors().size(); ++i) {
			auto motor = chassis.right_drive.getMotors()[i];
			console_scr->add(motor.name() + ": ", [i]() { return to_string_float(chassis.get_right_drive_position(i), 5, false) + ""; });
		}
		for (size_t i = 0; i < chassis.right_drive.getMotors().size(); ++i) {
			auto motor = chassis.left_drive.getMotors()[i];
			console_scr->add(motor.name() + ": ", [i]() { return to_string_float(chassis.get_left_drive_position(i), 5, false) + ""; });
		}
		return 0;
	});

}

void config_reset_data() {
	console_scr->reset();
	UI_select_scr(console_scr->get_console_screen()); 

	vex::task temp([](){
		if (!chassis.position_tracking) {
			console_scr->add("The robot does not know where it is, place", [](){ return ""; });	
			console_scr->add("`chassis.set_coordinates(x, y, heading);`", [](){ return ""; });	
			console_scr->add("during pre_auton() or calibrate an auton", [](){ return ""; });	
			return 0;
		}

		console_scr->add("Odom X: ", [](){ return chassis.get_X_position(); });
		console_scr->add("Odom Y: ", [](){ return chassis.get_Y_position(); });
		console_scr->add("Heading: ", [](){ return chassis.get_absolute_heading(); });

		for (auto& sensor : chassis.reset_sensors.get_distance_sensors()) {
			auto sensor_pos = sensor.position();

			console_scr->add(sensor.name() + ": ", [sensor_pos, &sensor](){
				auto wall = chassis.reset_sensors.get_wall_facing(sensor_pos, chassis.get_X_position(), chassis.get_Y_position(), chassis.get_absolute_heading());
				std::string axis = (wall == "Bottom Wall" || wall == "Top Wall") ? "Y" : "X";
				return wall + " " + axis + ": " + to_string_float(chassis.reset_sensors.get_reset_axis_pos(sensor_pos, auto_detect_wall, chassis.get_X_position(), chassis.get_Y_position(), chassis.get_absolute_heading()), 3, false) + " D: " + to_string_float(sensor.objectDistance(distanceUnits::in), 3, false);
			});
		}

		return 0;
	});	
}

void config_error_data() {
	console_scr->reset();
	UI_select_scr(console_scr->get_console_screen()); 

	vex::task add_errors([](){
		for (const auto& error : error_data) {
			console_scr->add(error);  
		}
		return 0;
	});
}

void config_measure_velocity_accel() {
    console_scr->reset();
    UI_select_scr(console_scr->get_console_screen());

	disable_user_control();

    vex::task temp([](){
		
		std::vector<std::pair<float, float>> angle_time{};

		// Spin in place at full voltage for 1.5 seconds
		
		Brain.Timer.reset();
		chassis.inertial.resetRotation();
		
		chassis.drive_with_voltage(12, -12);
		
		while (Brain.Timer.time(msec) < 1500) {
			float angle = chassis.inertial.rotation(degrees);
			float t = Brain.Timer.time(sec); 
			angle_time.push_back({angle, t});
			task::sleep(10);
		}
		chassis.turn_to_angle(0);
		chassis.stop_drive(coast);

        std::vector<std::pair<float, float>> pos_time{};

		// Drive full speed for 1.5 seconds
		chassis.drive_distance(72, {.max_voltage = 12, .heading_max_voltage = 12, .timeout = 1500, .wait = false});

		Brain.resetTimer();
		chassis.right_drive.resetPosition();
		chassis.left_drive.resetPosition();
		chassis.forward_tracker.resetPosition();

        while (chassis.motion_running) {
            float pos = chassis.get_forward_tracker_position() / 12.0;
			float t = Brain.Timer.time(sec);
            pos_time.push_back({pos, t});
            task::sleep(10);
        }
		chassis.stop_drive(coast);

		auto position_to_velocity = [](const std::vector<std::pair<float, float>>& unit_time){
			std::vector<std::pair<float, float>> velocities;
			for (size_t i = 1; i < unit_time.size(); ++i) {
				float v = ((unit_time[i].first - unit_time[i - 1].first) / (unit_time[i].second - unit_time[i - 1].second));
				velocities.push_back({v, unit_time[i].second});
			}
			return velocities;
		};

		// 5-point centered median filter — eliminates encoder-tick spikes with only ~20ms lag
		auto smooth_velocity_median = [](const std::vector<std::pair<float, float>>& velocity){
			std::vector<std::pair<float, float>> smoothed;
			const int half = 2;
			for (size_t i = 0; i < velocity.size(); ++i) {
				int start = std::max(0, (int)i - half);
				int end   = std::min((int)velocity.size() - 1, (int)i + half);
				std::vector<float> vals;
				for (int j = start; j <= end; ++j) {
					vals.push_back(velocity[j].first);
				}
				std::nth_element(vals.begin(), vals.begin() + vals.size() / 2, vals.end());
				smoothed.push_back({vals[vals.size() / 2], velocity[i].second});
			}
			return smoothed;
		};

		auto max_velo_idx = [](float& max_velocity, size_t& index, const std::vector<std::pair<float, float>>& smoothed_velo){
			max_velocity = -1;
			index = 0;

			for (size_t i = 0; i < smoothed_velo.size(); ++i) {
				if (smoothed_velo[i].first > max_velocity) {
					max_velocity = smoothed_velo[i].first;
					index = i;
				}
			}		
		};

		// Time constant = time from first motion to reaching 63.2% of max velocity
		auto time_constant = [](const std::vector<std::pair<float, float>>& smoothed_velo, float max_vel){
			float t_start = -1.0f;
			for (size_t i = 0; i < smoothed_velo.size(); ++i) {
				if (smoothed_velo[i].first > 0.0f) {
					t_start = smoothed_velo[i].second;
					break;
				}
			}
			if (t_start < 0.0f) return -1.0f;

			const float threshold = max_vel * 0.632f;
			for (size_t i = 0; i < smoothed_velo.size(); ++i) {
				if (smoothed_velo[i].second >= t_start && smoothed_velo[i].first >= threshold) {
					return smoothed_velo[i].second - t_start;
				}
			}
			return -1.0f;
		};

		auto turn_velocities = position_to_velocity(angle_time);
		auto drive_velocities = position_to_velocity(pos_time);

		auto smoothed_turn_velo = smooth_velocity_median(turn_velocities);
		auto smoothed_drive_velo = smooth_velocity_median(drive_velocities);

		float max_drive_vel, max_turn_vel = -1.0;
		size_t max_drive_index, max_turn_index = 0;
		
		max_velo_idx(max_drive_vel, max_drive_index, smoothed_drive_velo);
		max_velo_idx(max_turn_vel, max_turn_index, smoothed_turn_velo);

		float drive_time_constant = time_constant(smoothed_drive_velo, max_drive_vel);
		float turn_time_constant = time_constant(smoothed_turn_velo, max_turn_vel);

        console_scr->add("Max Drive Velocity: ", [max_drive_vel](){ return to_string_float(max_drive_vel, 3, false) + " ft/s"; });
        console_scr->add("Drive Time Constant: ", [drive_time_constant](){ return to_string_float(drive_time_constant, 4, false) + " s"; });
		
        console_scr->add("Turn Time Constant: ", [turn_time_constant](){ return to_string_float(turn_time_constant, 4, false) + " s"; });

		auto print_unit_time = [](const std::vector<std::pair<float, float>> unit_time){
			for (const auto& p : unit_time) {
				print(to_string_float(p.second, 3, false) + ", " + to_string_float(p.first, 3, false));
				task::sleep(20);
			}
			print("End Data\n");
		};

		print("Start Data, Position (second, ft)");
		print_unit_time(pos_time);

		print("Start Data, Angle (degrees, ft)");
		print_unit_time(angle_time);

		print("Start Data, Smoothed Drive Velocity (second, ft/s)");
		print_unit_time(smoothed_drive_velo);

		print("Start Data, Smoothed Turn Velocity (second, ft/s)");
		print_unit_time(smoothed_turn_velo);

		enable_user_control();
        return 0;
    });
}

void config_measure_distance_reset_offsets() {
	console_scr->reset();
	UI_select_scr(console_scr->get_console_screen());

	vex::task temp([](){
		struct sensor_data {
			mik::distance sensor;
			float x_offset;
			float y_offset;
		};

		std::vector<sensor_data> sensor_order{
			{ chassis.reset_sensors.get_distance_sensor(front_sensor), 0, 0 },
			{ chassis.reset_sensors.get_distance_sensor(left_sensor),  0, 0 },
			{ chassis.reset_sensors.get_distance_sensor(rear_sensor),  0, 0 },
			{ chassis.reset_sensors.get_distance_sensor(right_sensor), 0, 0 },
		};

		const float iterations = 10.0;
		const float bracket = 15.0;
		const float cardinals[] = { 0.0, 90.0, 180.0, 270.0 };
		const float facing_offsets[] = { 0.0, 270.0, 180.0, 90.0 };

		chassis.set_coordinates(47.125, 47.125, 0);

		for (size_t i = 0; i < sensor_order.size(); ++i) {
			float cardinal = cardinals[i];
			float angle1, angle2, robot_y1, robot_y2;
			float dist1 = 0, dist2 = 0;

			chassis.turn_to_angle(cardinal - bracket, { .max_voltage = 6, .settle_error = 1, .settle_time = 300 });
			task::sleep(250);
			angle1 = chassis.get_absolute_heading();
			robot_y1 = chassis.get_Y_position();
			for (int j = 0; j < iterations; ++j) {
				dist1 += sensor_order[i].sensor.objectDistance(inches);
				task::sleep(50);
			}
			dist1 /= iterations;

			chassis.turn_to_angle(cardinal + bracket, { .max_voltage = 6, .settle_error = 1, .settle_time = 300 });
			task::sleep(250);
			angle2 = chassis.get_absolute_heading();
			robot_y2 = chassis.get_Y_position();
			for (int j = 0; j < iterations; ++j) {
				dist2 += sensor_order[i].sensor.objectDistance(inches);
				task::sleep(50);
			}
			dist2 /= iterations;

			if (dist1 > 100 || dist1 < 1 || dist2 > 100 || dist2 < 1) {
				sensor_order[i].x_offset = -9999;
				sensor_order[i].y_offset = -9999;
				continue;
			}

			float eq1 = 70.25f - dist1 * cos(to_rad(angle1 + facing_offsets[i])) - robot_y1;
			float eq2 = 70.25f - dist2 * cos(to_rad(angle2 + facing_offsets[i])) - robot_y2;
			float det = sin(to_rad(angle2 - angle1));
			if (fabs(det) < 0.01f) continue;

			sensor_order[i].x_offset = (eq1 * cos(to_rad(angle2)) - eq2 * cos(to_rad(angle1))) / det;
			sensor_order[i].y_offset = (eq1 * sin(to_rad(angle2)) - eq2 * sin(to_rad(angle1))) / det;
		}

		for (auto& data : sensor_order) {
			if (fabs(data.x_offset) > 999 || fabs(data.y_offset) > 999) {
				console_scr->add(data.sensor.name() + " Sensor is unplugged or missing", [](){ return ""; });
				continue;
			}
			console_scr->add(data.sensor.name() + " Sensor Offsets, ", [x = data.x_offset, y = data.y_offset](){
				return "X: " + to_string_float(x, 3, false) + " Y: " + to_string_float(y, 3, false);
			});
		}

		chassis.set_brake_type(vex::brakeType::coast);
		chassis.stop_drive(vex::brakeType::coast);

		return 0;
	});
}

void config_measure_odometry_offsets() {
    console_scr->reset();
    UI_select_scr(console_scr->get_console_screen());
	
    vex::task temp([](){
		const auto saved_mode = chassis.tracker_mode; 
		chassis.tracker_mode = mik::tracker_mode::FORWARD_TRACKER;

		int iterations = 10;
	
		float f_offset = 0.0, s_offset = 0.0, d_offset = 0.0;
	
		chassis.forward_tracker.resetPosition();
		chassis.sideways_tracker.resetPosition();
		chassis.right_drive.resetPosition();
	
		for (int i = 0; i < iterations; i++) {
			chassis.set_heading(0);
			chassis.forward_tracker.resetPosition();
			chassis.sideways_tracker.resetPosition();
			chassis.right_drive.resetPosition();
	
			float start_heading = chassis.inertial.rotation();
			float target = i % 2 == 0 ? 90 : 270;
	
			chassis.turn_to_angle(target, { .max_voltage = 6, .settle_error = 1, .settle_time = 300 });
			task::sleep(250);
	
			float t_delta = to_rad(reduce_negative_180_to_180(chassis.inertial.rotation() - start_heading));
	
	
			float f_delta = chassis.get_forward_tracker_position();
			float s_delta = chassis.get_sideways_tracker_position();
	
			f_offset += f_delta / t_delta;
			s_offset += s_delta / t_delta;
		}
	
		f_offset /= iterations;
		s_offset /= iterations;
		d_offset /= iterations;

		console_scr->add("Forward Tracker Center Distance: ", [f_offset](){ return to_string_float(-f_offset, 3, false) + " in"; });
		console_scr->add("Sideways Tracker Center Distance: ", [s_offset](){ return to_string_float(-s_offset, 3, false) + " in"; });

		chassis.set_brake_type(vex::brakeType::coast);
		chassis.stop_drive(vex::brakeType::coast);

		chassis.tracker_mode = saved_mode;

		return 0;
	});

}

void config_skills_driver_run() {
	auton_scr->disable_controller_overlay();
	vex::task timer([](){
		Controller.Screen.setCursor(1, 1);
		Controller.Screen.print("SKILLS DRIVER RUN               ");
		task::sleep(1000);
		Controller.Screen.setCursor(1, 1);
		Controller.Screen.print("             3                 ");
		Controller.rumble(".");
		task::sleep(1000);
		Controller.Screen.setCursor(1, 1);
		Controller.Screen.print("             2                 ");
		Controller.rumble(".");
		task::sleep(1000);
		Controller.Screen.setCursor(1, 1);
		Controller.Screen.print("             1                 ");
		Controller.rumble(".");
		task::sleep(1000);
		Controller.Screen.setCursor(1, 1);
		Controller.Screen.print("            GO                 ");
		Controller.rumble("-");
		Controller.Screen.setCursor(1, 1);
		Controller.Screen.print("                               ");

		float start_time = Brain.Timer.time(vex::timeUnits::sec);
		float current_time = start_time;
		float max_time = 60;
		float elapsed_time = 0;
		int time_remaining = 0;
		while(1) {
			current_time = Brain.Timer.time(vex::timeUnits::sec);
			elapsed_time = current_time - start_time;
			time_remaining = max_time - elapsed_time;

			switch (time_remaining)
			{
			case 30:
				Controller.rumble((".-"));
				break;
			case 15:
				Controller.rumble(("."));
				break;
			case 5:
				Controller.rumble((".-"));
				break;
			case 0:
				Controller.rumble(("."));
				chassis.stop_drive(vex::coast);
				disable_user_control(true);
				std::abort();
				break;
			default:
				break;
			}
			
			Controller.Screen.setCursor(1, 1);
			Controller.Screen.print("           ");
			Controller.Screen.print(time_remaining);
			Controller.Screen.print("  ");
		}
		return 0;
	});
}

void config_test_three_wire_port(int port) {
	vex::digital_out dig_out = to_triport(port);
	dig_out.set(!dig_out.value());
}

void config_test_three_wire_port(int expander_port, int port) {
	vex::triport expander(expander_port);
	vex::digital_out dig_out = to_triport(expander, port);
	dig_out.set(!dig_out.value());
}
