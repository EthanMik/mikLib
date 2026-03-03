---
title: Chassis

---

# Chassis






`#include <chassis.h>`

## Public Functions

|                | Name           |
| -------------- | -------------- |
| | **[Chassis](/api/classes/class_chassis#function-chassis)**([mik::motor_group](/api/classes/classmik_1_1motor__group) left_drive, [mik::motor_group](/api/classes/classmik_1_1motor__group) right_drive, int inertial_port, float inertial_scale, bool force_calibrate_inertial, [mik::tracker_mode](/api/namespaces/namespacemik#enum-tracker-mode) tracker_mode, float wheel_diameter, float wheel_ratio, float wheel_center_distance, int forward_tracker_port, float forward_tracker_diameter, float forward_tracker_center_distance, int sideways_tracker_port, float sideways_tracker_diameter, float sideways_tracker_center_distance, [mik::distance_reset](/api/classes/classmik_1_1distance__reset) reset_sensors) |
| bool | **[angles_mirrored](/api/classes/class_chassis#function-angles-mirrored)**() |
| void | **[calibrate_inertial](/api/classes/class_chassis#function-calibrate-inertial)**()<br>Calibrates the inertial sensor, if force calibrate is true it will continue to calibrate until it is within threshold for 1 second.  |
| void | **[cancel_motion](/api/classes/class_chassis#function-cancel-motion)**()<br>Cancels the current motion the robot is in. Useful for chaining movements faster.  |
| void | **[control](/api/classes/class_chassis#function-control)**([mik::drive_mode](/api/namespaces/namespacemik#enum-drive-mode) dm)<br>Dispatch joystick input based on the selected drive mode.  |
| void | **[disable_control](/api/classes/class_chassis#function-disable-control)**()<br>disables joystick control of the drivetrain  |
| void | **[disable_mirroring](/api/classes/class_chassis#function-disable-mirroring)**()<br>Disables mirroring for x_pos, y_pos and angles.  |
| void | **[drive_distance](/api/classes/class_chassis#function-drive-distance)**(float distance, const [drive_distance_params](/api/classes/structdrive__distance__params) & p)<br>Drives the robot a given distance with a given heading. Drive distance does not optimize for direction, so it won't try to drive at the opposite heading from the one given to get there faster. You can control the heading, but if you choose not to, it will drive with the heading it's currently facing. It uses forward tracker to find distance traveled. Use negative distance to go backwards.  |
| void | **[drive_to_point](/api/classes/class_chassis#function-drive-to-point)**(float X_position, float Y_position, const [drive_to_point_params](/api/classes/structdrive__to__point__params) & p)<br>Drives to a specified point on the field. Uses the double-PID method, with one for driving and one for heading correction. The drive error is the euclidean distance to the desired point, and the heading error is the turn correction from the current heading to the desired point. Uses optimizations like driving backwards whenever possible and scaling the drive output with the cosine of the angle to the point.  |
| void | **[drive_to_pose](/api/classes/class_chassis#function-drive-to-pose)**(float X_position, float Y_position, float angle, const [drive_to_pose_params](/api/classes/structdrive__to__pose__params) & p)<br>Drives to a specified point and orientation on the field. Uses a boomerang controller. The carrot point is back from the target by the same distance as the robot's distance to the target, times the lead. The robot always tries to go to the carrot, which is constantly moving, and the robot eventually gets into position. The heading correction is optimized to only try to reach the correct angle when drive error is low, and the robot will drive backwards to reach a pose if it's faster. .5 is a reasonable value for the lead. The setback parameter is used to glide into position more effectively. It is the distance back from the target that the robot tries to drive to first. Try it out in a desmos simulation [https://www.desmos.com/calculator/sptjw5szex](https://www.desmos.com/calculator/sptjw5szex).  |
| void | **[drive_with_voltage](/api/classes/class_chassis#function-drive-with-voltage)**(float left_voltage, float right_voltage)<br>Drives each side of the chassis at the specified voltage.  |
| void | **[enable_control](/api/classes/class_chassis#function-enable-control)**()<br>enables joystick control of the drivetrain  |
| void | **[follow_path](/api/classes/class_chassis#function-follow-path)**(std::vector< [point](/api/classes/structpoint) > path, const [follow_path_params](/api/classes/structfollow__path__params) & p)<br>Drives the robot along defined waypoints. Waypoints can be obtained from [https://path.jerryio.com/](https://path.jerryio.com/).  |
| float | **[get_X_position](/api/classes/class_chassis#function-get-x-position)**() |
| float | **[get_Y_position](/api/classes/class_chassis#function-get-y-position)**() |
| float | **[get_absolute_heading](/api/classes/class_chassis#function-get-absolute-heading)**() |
| float | **[get_forward_tracker_position](/api/classes/class_chassis#function-get-forward-tracker-position)**() |
| float | **[get_motor_encoder_position](/api/classes/class_chassis#function-get-motor-encoder-position)**() |
| float | **[get_sideways_tracker_position](/api/classes/class_chassis#function-get-sideways-tracker-position)**() |
| bool | **[is_in_motion](/api/classes/class_chassis#function-is-in-motion)**() |
| void | **[left_swing_to_angle](/api/classes/class_chassis#function-left-swing-to-angle)**(float angle, const [swing_to_angle_params](/api/classes/structswing__to__angle__params) & p) |
| void | **[left_swing_to_point](/api/classes/class_chassis#function-left-swing-to-point)**(float X_position, float Y_position, const [swing_to_point_params](/api/classes/structswing__to__point__params) & p)<br>Turns to a specified point on the field with the left side of the drivetrain. Functions similarly to [left_swing_to_angle()](/api/classes/class_chassis#function-left-swing-to-angle) except with a point. The angle_offset parameter turns the robot extra relative to the desired target. For example, if you want the back of your robot to point at (36, 42), you would run left_swing_to_point(36, 42, {.angle_offset = 180}).  |
| void | **[mirror_all_auton_angles](/api/classes/class_chassis#function-mirror-all-auton-angles)**()<br>Mirror all subsequent turn angles, affecting [turn_to_angle()](), [drive_to_pose()](/api/classes/class_chassis#function-drive-to-pose), and [set_coordinates()](). Useful on opposite field sides. Also changes turn directions to their inverse, cw->ccw, ccw->cw.  |
| void | **[mirror_all_auton_x_pos](/api/classes/class_chassis#function-mirror-all-auton-x-pos)**()<br>Mirror all subsequent x-coordinates, affecting [drive_to_point()](/api/classes/class_chassis#function-drive-to-point), [turn_to_point()](), [drive_to_pose()](/api/classes/class_chassis#function-drive-to-pose), and [set_coordinates()](). Useful on opposite field sides.  |
| void | **[mirror_all_auton_y_pos](/api/classes/class_chassis#function-mirror-all-auton-y-pos)**()<br>Mirror all subsequent y-coordinates, affecting [drive_to_point()](/api/classes/class_chassis#function-drive-to-point), [turn_to_point()](), [drive_to_pose()](/api/classes/class_chassis#function-drive-to-pose), and [set_coordinates()](). Useful on opposite field sides.  |
| void | **[position_track](/api/classes/class_chassis#function-position-track)**()<br>Background task for updating the odometry.  |
| int | **[position_track_task](/api/classes/class_chassis#function-position-track-task)**()<br>Background task for updating the odometry.  |
| bool | **[reset_axis](/api/classes/class_chassis#function-reset-axis)**([mik::distance_position](/api/namespaces/namespacemik#enum-distance-position) sensor_pos, float max_reset_distance)<br>Resets an X or Y position of the robot based on the heading and distance from a wall. The distance sensor must be facing the desired wall with no obstruction in order to work. Choosing to reset off a top or bottom wall will reset the robots y positon, and a left or right wall resetting the robots x position. The wall the robot is facing is automatically found by using its absolute X, Y, and heading. Wall facing can be specified.  |
| bool | **[reset_axis](/api/classes/class_chassis#function-reset-axis)**([mik::distance_position](/api/namespaces/namespacemik#enum-distance-position) sensor_pos, [mik::wall_position](/api/namespaces/namespacemik#enum-wall-position) wall_pos, float max_reset_distance) |
| void | **[right_swing_to_angle](/api/classes/class_chassis#function-right-swing-to-angle)**(float angle, const [swing_to_angle_params](/api/classes/structswing__to__angle__params) & p) |
| void | **[right_swing_to_point](/api/classes/class_chassis#function-right-swing-to-point)**(float X_position, float Y_position, const [swing_to_point_params](/api/classes/structswing__to__point__params) & p)<br>Turns to a specified point on the field with the right side of the drivetrain. Functions similarly to [right_swing_to_angle()](/api/classes/class_chassis#function-right-swing-to-angle) except with a point. The angle_offset parameter turns the robot extra relative to the desired target. For example, if you want the back of your robot to point at (36, 42), you would run right_swing_to_point(36, 42, {.angle_offset = 180}).  |
| void | **[set_brake_type](/api/classes/class_chassis#function-set-brake-type)**(vex::brakeType brake)<br>Globally sets the brake mode for both drive motor groups.  |
| void | **[set_control_constants](/api/classes/class_chassis#function-set-control-constants)**(float control_throttle_deadband, float control_throttle_min_output, float control_throttle_curve_gain, float control_turn_deadband, float control_turn_min_output, float control_turn_curve_gain)<br>Reset default joystick control constants for throttle and turn. Try it out in desmos [https://www.desmos.com/calculator/umicbymbnl](https://www.desmos.com/calculator/umicbymbnl).  |
| void | **[set_coordinates](/api/classes/class_chassis#function-set-coordinates)**(float X_position, float Y_position, float orientation_deg)<br>Resets the robot's coordinates and heading. This is for odom-using robots to specify where the bot is at the beginning of the match.  |
| void | **[set_drive_constants](/api/classes/class_chassis#function-set-drive-constants)**(float drive_max_voltage, float drive_kp, float drive_ki, float drive_kd, float drive_starti, float drive_slew)<br>Resets default drive constants. Driving includes [drive_distance()](/api/classes/class_chassis#function-drive-distance), [drive_to_point()](/api/classes/class_chassis#function-drive-to-point), [drive_to_pose()](/api/classes/class_chassis#function-drive-to-pose), and [follow_path()](/api/classes/class_chassis#function-follow-path).  |
| void | **[set_drive_exit_conditions](/api/classes/class_chassis#function-set-drive-exit-conditions)**(float drive_settle_error, float drive_settle_time, float drive_timeout)<br>Resets default drive exit conditions. The robot exits when error is less than settle_error for a duration of settle_time, or if the function has gone on for longer than timeout.  |
| void | **[set_heading](/api/classes/class_chassis#function-set-heading)**(float orientation_deg)<br>Resets the robot's heading. For example, at the beginning of auton, if your robot starts at 45 degrees, so set_heading(45) and the robot will know which way it's facing.  |
| void | **[set_heading_constants](/api/classes/class_chassis#function-set-heading-constants)**(float heading_max_voltage, float heading_kp, float heading_ki, float heading_kd, float heading_starti, float heading_slew)<br>Resets default heading constants. Heading control keeps the robot facing the right direction and is part of [drive_distance()](/api/classes/class_chassis#function-drive-distance), [drive_to_point()](/api/classes/class_chassis#function-drive-to-point), [drive_to_pose()](/api/classes/class_chassis#function-drive-to-pose), and [follow_path()](/api/classes/class_chassis#function-follow-path).  |
| void | **[set_swing_constants](/api/classes/class_chassis#function-set-swing-constants)**(float swing_max_voltage, float swing_kp, float swing_ki, float swing_kd, float swing_starti, float swing_slew)<br>Resets default swing constants. Swing control holds one side of the drive still and turns with the other. Used in [left_swing_to_angle()](/api/classes/class_chassis#function-left-swing-to-angle), [right_swing_to_angle()](/api/classes/class_chassis#function-right-swing-to-angle), [right_swing_to_point()](/api/classes/class_chassis#function-right-swing-to-point) and left_swing_to_point.  |
| void | **[set_swing_exit_conditions](/api/classes/class_chassis#function-set-swing-exit-conditions)**(float swing_settle_error, float swing_settle_time, float swing_timeout)<br>Resets default swing exit conditions. The robot exits when error is less than settle_error for a duration of settle_time, or if the function has gone on for longer than timeout.  |
| void | **[set_tracking_offsets](/api/classes/class_chassis#function-set-tracking-offsets)**(float forward_tracker_center_distance, float sideways_tracker_center_distance)<br>Resets the tracking offsets. Used for when robots center of rotation changes, ex: clamping onto a large game object.  |
| void | **[set_turn_constants](/api/classes/class_chassis#function-set-turn-constants)**(float turn_max_voltage, float turn_kp, float turn_ki, float turn_kd, float turn_starti, float turn_slew)<br>Resets default turn constants. Turning includes [turn_to_angle()]() and [turn_to_point()]().  |
| void | **[set_turn_exit_conditions](/api/classes/class_chassis#function-set-turn-exit-conditions)**(float turn_settle_error, float turn_settle_time, float turn_timeout)<br>Resets default turn exit conditions. The robot exits when error is less than settle_error for a duration of settle_time, or if the function has gone on for longer than timeout.  |
| void | **[split_arcade](/api/classes/class_chassis#function-split-arcade)**() |
| void | **[split_arcade_curved](/api/classes/class_chassis#function-split-arcade-curved)**() |
| void | **[stop_drive](/api/classes/class_chassis#function-stop-drive)**(vex::brakeType brake)<br>Stops both sides of the drivetrain.  |
| void | **[tank](/api/classes/class_chassis#function-tank)**() |
| void | **[tank_curved](/api/classes/class_chassis#function-tank-curved)**() |
| void | **[turn_to_angle](/api/classes/class_chassis#function-turn-to-angle)**(float angle, const [turn_to_angle_params](/api/classes/structturn__to__angle__params) & p)<br>Turns the robot to a field-centric angle. Optimizes direction, so it turns whichever way is closer to the current heading of the robot, unless a turn direction is specified.  |
| void | **[turn_to_point](/api/classes/class_chassis#function-turn-to-point)**(float X_position, float Y_position, const [turn_to_point_params](/api/classes/structturn__to__point__params) & p)<br>Turns to a specified point on the field. Functions similarly to [turn_to_angle()](/api/classes/class_chassis#function-turn-to-angle) except with a point. The angle_offset parameter turns the robot extra relative to the desired target. For example, if you want the back of your robot to point at (36, 42), you would run turn_to_point(36, 42, {.angle_offset = 180}).  |
| void | **[update_drive_max_voltage](/api/classes/class_chassis#function-update-drive-max-voltage)**(float drive_max_voltage)<br>Changes the drive max voltage that is currently being used for a drive motion.  |
| void | **[update_heading_max_voltage](/api/classes/class_chassis#function-update-heading-max-voltage)**(float heading_max_voltage)<br>Changes the heading max voltage that is currently being used for a drive motion.  |
| void | **[update_swing_max_voltage](/api/classes/class_chassis#function-update-swing-max-voltage)**(float swing_max_voltage)<br>Changes the swing max voltage that is currently being used for a drive motion.  |
| void | **[update_turn_max_voltage](/api/classes/class_chassis#function-update-turn-max-voltage)**(float turn_max_voltage)<br>Changes the turn max voltage that is currently being used for a drive motion.  |
| void | **[wait](/api/classes/class_chassis#function-wait)**()<br>Yield to the scheduler until motion is finished.  |
| void | **[wait_until](/api/classes/class_chassis#function-wait-until)**(float units)<br>Yield to the scheduler until the current motion the robots in has traveled specifed units. Drive motions use inches, turn motions use degrees.  |
| bool | **[x_pos_mirrored](/api/classes/class_chassis#function-x-pos-mirrored)**() |
| bool | **[y_pos_mirrored](/api/classes/class_chassis#function-y-pos-mirrored)**() |

## Public Attributes

|                | Name           |
| -------------- | -------------- |
| float | **[active_min_voltage](/api/classes/class_chassis#variable-active-min-voltage)**  |
| float | **[boomerang_drift](/api/classes/class_chassis#variable-boomerang-drift)**  |
| float | **[boomerang_lead](/api/classes/class_chassis#variable-boomerang-lead)**  |
| float | **[boomerang_setback](/api/classes/class_chassis#variable-boomerang-setback)**  |
| bool | **[calibrating](/api/classes/class_chassis#variable-calibrating)**  |
| bool | **[control_disabled](/api/classes/class_chassis#variable-control-disabled)**  |
| float | **[control_throttle_curve_gain](/api/classes/class_chassis#variable-control-throttle-curve-gain)**  |
| float | **[control_throttle_deadband](/api/classes/class_chassis#variable-control-throttle-deadband)**  |
| float | **[control_throttle_min_output](/api/classes/class_chassis#variable-control-throttle-min-output)**  |
| float | **[control_turn_curve_gain](/api/classes/class_chassis#variable-control-turn-curve-gain)**  |
| float | **[control_turn_deadband](/api/classes/class_chassis#variable-control-turn-deadband)**  |
| float | **[control_turn_min_output](/api/classes/class_chassis#variable-control-turn-min-output)**  |
| float | **[desired_X_position](/api/classes/class_chassis#variable-desired-x-position)**  |
| float | **[desired_Y_position](/api/classes/class_chassis#variable-desired-y-position)**  |
| float | **[desired_angle](/api/classes/class_chassis#variable-desired-angle)**  |
| float | **[desired_angle_offset](/api/classes/class_chassis#variable-desired-angle-offset)**  |
| float | **[desired_distance](/api/classes/class_chassis#variable-desired-distance)**  |
| float | **[desired_heading](/api/classes/class_chassis#variable-desired-heading)**  |
| std::vector< [point](/api/classes/structpoint) > | **[desired_path](/api/classes/class_chassis#variable-desired-path)**  |
| float | **[distance_traveled](/api/classes/class_chassis#variable-distance-traveled)**  |
| float | **[drive_kd](/api/classes/class_chassis#variable-drive-kd)**  |
| float | **[drive_ki](/api/classes/class_chassis#variable-drive-ki)**  |
| float | **[drive_kp](/api/classes/class_chassis#variable-drive-kp)**  |
| float | **[drive_max_voltage](/api/classes/class_chassis#variable-drive-max-voltage)**  |
| float | **[drive_min_voltage](/api/classes/class_chassis#variable-drive-min-voltage)**  |
| float | **[drive_settle_error](/api/classes/class_chassis#variable-drive-settle-error)**  |
| float | **[drive_settle_time](/api/classes/class_chassis#variable-drive-settle-time)**  |
| float | **[drive_slew](/api/classes/class_chassis#variable-drive-slew)**  |
| float | **[drive_starti](/api/classes/class_chassis#variable-drive-starti)**  |
| float | **[drive_timeout](/api/classes/class_chassis#variable-drive-timeout)**  |
| [mik::tracker](/api/classes/classmik_1_1tracker) | **[forward_tracker](/api/classes/class_chassis#variable-forward-tracker)**  |
| float | **[heading_kd](/api/classes/class_chassis#variable-heading-kd)**  |
| float | **[heading_ki](/api/classes/class_chassis#variable-heading-ki)**  |
| float | **[heading_kp](/api/classes/class_chassis#variable-heading-kp)**  |
| float | **[heading_max_voltage](/api/classes/class_chassis#variable-heading-max-voltage)**  |
| float | **[heading_slew](/api/classes/class_chassis#variable-heading-slew)**  |
| float | **[heading_starti](/api/classes/class_chassis#variable-heading-starti)**  |
| vex::inertial | **[inertial](/api/classes/class_chassis#variable-inertial)**  |
| [mik::motor_group](/api/classes/classmik_1_1motor__group) | **[left_drive](/api/classes/class_chassis#variable-left-drive)**  |
| bool | **[motion_running](/api/classes/class_chassis#variable-motion-running)**  |
| bool | **[position_tracking](/api/classes/class_chassis#variable-position-tracking)**  |
| float | **[pursuit_lookahead_distance](/api/classes/class_chassis#variable-pursuit-lookahead-distance)**  |
| [mik::distance_reset](/api/classes/classmik_1_1distance__reset) | **[reset_sensors](/api/classes/class_chassis#variable-reset-sensors)**  |
| [mik::motor_group](/api/classes/classmik_1_1motor__group) | **[right_drive](/api/classes/class_chassis#variable-right-drive)**  |
| [mik::drive_mode](/api/namespaces/namespacemik#enum-drive-mode) | **[selected_drive_mode](/api/classes/class_chassis#variable-selected-drive-mode)**  |
| [mik::tracker](/api/classes/classmik_1_1tracker) | **[sideways_tracker](/api/classes/class_chassis#variable-sideways-tracker)**  |
| bool | **[sideways_tracker_used](/api/classes/class_chassis#variable-sideways-tracker-used)**  |
| float | **[stop_apply_drive_slew](/api/classes/class_chassis#variable-stop-apply-drive-slew)**  |
| float | **[stop_apply_swing_slew](/api/classes/class_chassis#variable-stop-apply-swing-slew)**  |
| float | **[stop_apply_turn_slew](/api/classes/class_chassis#variable-stop-apply-turn-slew)**  |
| float | **[swing_kd](/api/classes/class_chassis#variable-swing-kd)**  |
| float | **[swing_ki](/api/classes/class_chassis#variable-swing-ki)**  |
| float | **[swing_kp](/api/classes/class_chassis#variable-swing-kp)**  |
| float | **[swing_max_voltage](/api/classes/class_chassis#variable-swing-max-voltage)**  |
| float | **[swing_min_voltage](/api/classes/class_chassis#variable-swing-min-voltage)**  |
| float | **[swing_opposite_voltage](/api/classes/class_chassis#variable-swing-opposite-voltage)**  |
| float | **[swing_settle_error](/api/classes/class_chassis#variable-swing-settle-error)**  |
| float | **[swing_settle_time](/api/classes/class_chassis#variable-swing-settle-time)**  |
| float | **[swing_slew](/api/classes/class_chassis#variable-swing-slew)**  |
| float | **[swing_starti](/api/classes/class_chassis#variable-swing-starti)**  |
| float | **[swing_timeout](/api/classes/class_chassis#variable-swing-timeout)**  |
| [mik::tracker_mode](/api/namespaces/namespacemik#enum-tracker-mode) | **[tracker_mode](/api/classes/class_chassis#variable-tracker-mode)**  |
| float | **[turn_kd](/api/classes/class_chassis#variable-turn-kd)**  |
| float | **[turn_ki](/api/classes/class_chassis#variable-turn-ki)**  |
| float | **[turn_kp](/api/classes/class_chassis#variable-turn-kp)**  |
| float | **[turn_max_voltage](/api/classes/class_chassis#variable-turn-max-voltage)**  |
| float | **[turn_min_voltage](/api/classes/class_chassis#variable-turn-min-voltage)**  |
| float | **[turn_settle_error](/api/classes/class_chassis#variable-turn-settle-error)**  |
| float | **[turn_settle_time](/api/classes/class_chassis#variable-turn-settle-time)**  |
| float | **[turn_slew](/api/classes/class_chassis#variable-turn-slew)**  |
| float | **[turn_starti](/api/classes/class_chassis#variable-turn-starti)**  |
| float | **[turn_timeout](/api/classes/class_chassis#variable-turn-timeout)**  |

## Public Functions Documentation

### function Chassis

```cpp
Chassis(
    mik::motor_group left_drive,
    mik::motor_group right_drive,
    int inertial_port,
    float inertial_scale,
    bool force_calibrate_inertial,
    mik::tracker_mode tracker_mode,
    float wheel_diameter,
    float wheel_ratio,
    float wheel_center_distance,
    int forward_tracker_port,
    float forward_tracker_diameter,
    float forward_tracker_center_distance,
    int sideways_tracker_port,
    float sideways_tracker_diameter,
    float sideways_tracker_center_distance,
    mik::distance_reset reset_sensors
)
```


**Parameters**: 

  * **[left_drive](/api/classes/class_chassis#variable-left-drive)** Motor group on the robot's left side. 
  * **[right_drive](/api/classes/class_chassis#variable-right-drive)** Motor group on the robot's right side. 
  * **inertial_port** Inertial sensor port (1-21). 
  * **inertial_scale** Scale factor applied to raw gyro angles to correct drift. 
  * **forward_tracker_port** Forward tracker rotation sensor port (1-21). 
  * **forward_tracker_diameter** Forward tracking‑wheel diameter (in inches). 
  * **forward_tracker_center_distance** Distance from the chassis centre to the forward tracker (in). 
  * **sideways_tracker_port** Sideways tracker rotation sensor port (1-21). 
  * **sideways_tracker_diameter** Sideways tracking‑wheel diameter (in inches). 
  * **sideways_tracker_center_distance** Distance from the chassis centre to the sideways tracker (in). 
  * **[reset_sensors](/api/classes/class_chassis#variable-reset-sensors)** Distance sensors parallel to a robot face that can reset odometry axes. 


### function angles_mirrored

```cpp
bool angles_mirrored()
```


**Return**: True if angles have been mirrored 

### function calibrate_inertial

```cpp
void calibrate_inertial()
```

Calibrates the inertial sensor, if force calibrate is true it will continue to calibrate until it is within threshold for 1 second. 

### function cancel_motion

```cpp
void cancel_motion()
```

Cancels the current motion the robot is in. Useful for chaining movements faster. 

### function control

```cpp
void control(
    mik::drive_mode dm
)
```

Dispatch joystick input based on the selected drive mode. 

**Parameters**: 

  * **dm** Drive mode enumeration. 


### function disable_control

```cpp
void disable_control()
```

disables joystick control of the drivetrain 

### function disable_mirroring

```cpp
void disable_mirroring()
```

Disables mirroring for x_pos, y_pos and angles. 

### function drive_distance

```cpp
inline void drive_distance(
    float distance,
    const drive_distance_params & p
)
```

Drives the robot a given distance with a given heading. Drive distance does not optimize for direction, so it won't try to drive at the opposite heading from the one given to get there faster. You can control the heading, but if you choose not to, it will drive with the heading it's currently facing. It uses forward tracker to find distance traveled. Use negative distance to go backwards. 

**Parameters**: 

  * **distance** Desired distance in inches. 
  * **heading** Desired heading in degrees. 
  * **min_voltage** Minimum voltage on the drive, used for chaining movements. 
  * **max_voltage** Max voltage on the drive out of 12. 
  * **[heading_max_voltage](/api/classes/class_chassis#variable-heading-max-voltage)** Max voltage for getting to heading out of 12. 
  * **settle_error** Error to be considered settled in inches. 
  * **settle_time** Time to be considered settled in milliseconds. 
  * **timeout** Time before quitting and move on in milliseconds. 
  * **drive_k** Drive [PID](/api/classes/class_p_i_d) and starti constants. Do drive_k. to access constants. 
  * **heading_k** Heading [PID](/api/classes/class_p_i_d) and starti constants. Do heading_k. to access constants. 
  * **[wait](/api/classes/class_chassis#function-wait)** Yields program until motion has finished, true by default. 


### function drive_to_point

```cpp
inline void drive_to_point(
    float X_position,
    float Y_position,
    const drive_to_point_params & p
)
```

Drives to a specified point on the field. Uses the double-PID method, with one for driving and one for heading correction. The drive error is the euclidean distance to the desired point, and the heading error is the turn correction from the current heading to the desired point. Uses optimizations like driving backwards whenever possible and scaling the drive output with the cosine of the angle to the point. 

**Parameters**: 

  * **X_position** Desired x position in inches. 
  * **Y_position** Desired y position in inches. 
  * **min_voltage** Minimum voltage on the drive, used for chaining movements. 
  * **max_voltage** Max voltage on the drive out of 12. 
  * **[heading_max_voltage](/api/classes/class_chassis#variable-heading-max-voltage)** Max voltage for getting to heading out of 12. 
  * **settle_error** Error to be considered settled in inches. 
  * **settle_time** Time to be considered settled in milliseconds. 
  * **timeout** Time before quitting and move on in milliseconds. 
  * **drive_k** Drive [PID](/api/classes/class_p_i_d) and starti constants. Do drive_k. to access constants. 
  * **heading_k** Heading [PID](/api/classes/class_p_i_d) and starti constants. Do heading_k. to access constants. 
  * **[wait](/api/classes/class_chassis#function-wait)** Yields program until motion has finished, true by default. 


### function drive_to_pose

```cpp
inline void drive_to_pose(
    float X_position,
    float Y_position,
    float angle,
    const drive_to_pose_params & p
)
```

Drives to a specified point and orientation on the field. Uses a boomerang controller. The carrot point is back from the target by the same distance as the robot's distance to the target, times the lead. The robot always tries to go to the carrot, which is constantly moving, and the robot eventually gets into position. The heading correction is optimized to only try to reach the correct angle when drive error is low, and the robot will drive backwards to reach a pose if it's faster. .5 is a reasonable value for the lead. The setback parameter is used to glide into position more effectively. It is the distance back from the target that the robot tries to drive to first. Try it out in a desmos simulation [https://www.desmos.com/calculator/sptjw5szex](https://www.desmos.com/calculator/sptjw5szex). 

**Parameters**: 

  * **X_position** Desired x position in inches. 
  * **Y_position** Desired y position in inches. 
  * **angle** Desired orientation in degrees. 
  * **lead** Constant scale factor that determines how far away the carrot point is. 
  * **setback** Distance in inches from target by which the carrot is always pushed back. 
  * **min_voltage** Minimum voltage on the drive, used for chaining movements. 
  * **max_voltage** Max voltage on the drive out of 12. 
  * **[heading_max_voltage](/api/classes/class_chassis#variable-heading-max-voltage)** Max voltage for getting to heading out of 12. 
  * **settle_error** Error to be considered settled in inches. 
  * **settle_time** Time to be considered settled in milliseconds. 
  * **timeout** Time before quitting and move on in milliseconds. 
  * **drive_k** Drive [PID](/api/classes/class_p_i_d) and starti constants. Do drive_k. to access constants. 
  * **heading_k** Heading [PID](/api/classes/class_p_i_d) and starti constants. Do heading_k. to access constants. 
  * **[wait](/api/classes/class_chassis#function-wait)** Yields program until motion has finished, true by default. 


### function drive_with_voltage

```cpp
void drive_with_voltage(
    float left_voltage,
    float right_voltage
)
```

Drives each side of the chassis at the specified voltage. 

**Parameters**: 

  * **left_voltage** Voltage (0-12). 
  * **right_voltage** Voltage (0-12). 


### function enable_control

```cpp
void enable_control()
```

enables joystick control of the drivetrain 

### function follow_path

```cpp
inline void follow_path(
    std::vector< point > path,
    const follow_path_params & p
)
```

Drives the robot along defined waypoints. Waypoints can be obtained from [https://path.jerryio.com/](https://path.jerryio.com/). 

**Parameters**: 

  * **[path](/api/files/test_8cpp#variable-path)** The vector of points that the robot will follow. 
  * **lookahead_distance** Radius of the look-ahead circle, in inches. 
  * **min_voltage** Minimum voltage on the drive, used for chaining movements. 
  * **max_voltage** Max voltage on the drive out of 12. 
  * **[heading_max_voltage](/api/classes/class_chassis#variable-heading-max-voltage)** Max voltage for getting to heading out of 12. 
  * **settle_error** Error to be considered settled in inches. 
  * **settle_time** Time to be considered settled in milliseconds. 
  * **timeout** Time before quitting and move on in milliseconds. 
  * **drive_k** Drive [PID](/api/classes/class_p_i_d) and starti constants. Do drive_k. to access constants. 
  * **heading_k** Heading [PID](/api/classes/class_p_i_d) and starti constants. Do heading_k. to access constants. 
  * **[wait](/api/classes/class_chassis#function-wait)** Yields program until motion has finished, true by default. 


Algorithm is from Taolib and is very similar to a pure pursuit controler. It continously finds the best intersection between a look-ahead circle (whose radius is `lookahead_distance`) and the current path segment, then goes to that point with pair of PIDs, one regulating forward motion and the other correcting heading. The larger the lookahead the faster but less accurate the robot will follow the path.


### function get_X_position

```cpp
float get_X_position()
```


**Return**: The robot's x position in inches 

### function get_Y_position

```cpp
float get_Y_position()
```


**Return**: The robot's y position in inches 

### function get_absolute_heading

```cpp
float get_absolute_heading()
```


**Return**: Field‑relative inertial heading (deg, 0‑360). 

### function get_forward_tracker_position

```cpp
float get_forward_tracker_position()
```


**Return**: Position of the forward tracker in inches 

### function get_motor_encoder_position

```cpp
float get_motor_encoder_position()
```


**Return**: Position of the right drivetrain in inches 

### function get_sideways_tracker_position

```cpp
float get_sideways_tracker_position()
```


**Return**: Position of the sideways tracker in inches 

### function is_in_motion

```cpp
bool is_in_motion()
```


**Return**: True if the robot is in motion. 

### function left_swing_to_angle

```cpp
inline void left_swing_to_angle(
    float angle,
    const swing_to_angle_params & p
)
```


**Parameters**: 

  * **angle** Desired angle in degrees. 
  * **turn_direction** The way the robot should turn, (ccw, cw, or shortest path) 
  * **min_voltage** Minimum voltage on the drive, used for chaining movements. 
  * **max_voltage** Max voltage on the drive out of 12. 
  * **settle_error** Error to be considered settled in degrees. 
  * **settle_time** Time to be considered settled in milliseconds. 
  * **timeout** Time before quitting and move on in milliseconds. 
  * **k** [PID](/api/classes/class_p_i_d) and starti constants. Do k. to access constants. 
  * **[wait](/api/classes/class_chassis#function-wait)** Yields program until motion has finished, true by default. 


Turns to a given angle with the left side of the drivetrain. Like [turn_to_angle()](/api/classes/class_chassis#function-turn-to-angle), is optimized for turning the shorter direction, unless a turn direction is specified


### function left_swing_to_point

```cpp
inline void left_swing_to_point(
    float X_position,
    float Y_position,
    const swing_to_point_params & p
)
```

Turns to a specified point on the field with the left side of the drivetrain. Functions similarly to [left_swing_to_angle()](/api/classes/class_chassis#function-left-swing-to-angle) except with a point. The angle_offset parameter turns the robot extra relative to the desired target. For example, if you want the back of your robot to point at (36, 42), you would run left_swing_to_point(36, 42, {.angle_offset = 180}). 

**Parameters**: 

  * **X_position** Desired x position in inches. 
  * **Y_position** Desired y position in inches. 
  * **angle_offset** Angle turned past the desired heading in degrees. 
  * **turn_direction** The way the robot should turn, (ccw, cw, or shortest path) 
  * **min_voltage** Minimum voltage on the drive, used for chaining movements. 
  * **max_voltage** Max voltage on the drive out of 12. 
  * **settle_error** Error to be considered settled in degrees. 
  * **settle_time** Time to be considered settled in milliseconds. 
  * **timeout** Time before quitting and move on in milliseconds. 
  * **k** [PID](/api/classes/class_p_i_d) and starti constants. Do k. to access constants. 
  * **[wait](/api/classes/class_chassis#function-wait)** Yields program until motion has finished, true by default. 


### function mirror_all_auton_angles

```cpp
void mirror_all_auton_angles()
```

Mirror all subsequent turn angles, affecting [turn_to_angle()](), [drive_to_pose()](/api/classes/class_chassis#function-drive-to-pose), and [set_coordinates()](). Useful on opposite field sides. Also changes turn directions to their inverse, cw->ccw, ccw->cw. 

### function mirror_all_auton_x_pos

```cpp
void mirror_all_auton_x_pos()
```

Mirror all subsequent x-coordinates, affecting [drive_to_point()](/api/classes/class_chassis#function-drive-to-point), [turn_to_point()](), [drive_to_pose()](/api/classes/class_chassis#function-drive-to-pose), and [set_coordinates()](). Useful on opposite field sides. 

### function mirror_all_auton_y_pos

```cpp
void mirror_all_auton_y_pos()
```

Mirror all subsequent y-coordinates, affecting [drive_to_point()](/api/classes/class_chassis#function-drive-to-point), [turn_to_point()](), [drive_to_pose()](/api/classes/class_chassis#function-drive-to-pose), and [set_coordinates()](). Useful on opposite field sides. 

### function position_track

```cpp
void position_track()
```

Background task for updating the odometry. 

### function position_track_task

```cpp
static int position_track_task()
```

Background task for updating the odometry. 

### function reset_axis

```cpp
bool reset_axis(
    mik::distance_position sensor_pos,
    float max_reset_distance
)
```

Resets an X or Y position of the robot based on the heading and distance from a wall. The distance sensor must be facing the desired wall with no obstruction in order to work. Choosing to reset off a top or bottom wall will reset the robots y positon, and a left or right wall resetting the robots x position. The wall the robot is facing is automatically found by using its absolute X, Y, and heading. Wall facing can be specified. 

**Parameters**: 

  * **sensor_pos** The side of the robot that the distance sensor is mounted. 
  * **max_reset_distance** The maxiumum allowed of distance in inches that an odom axis can be changed.


**Return**: True if the desired axis was reset successfully. 

### function reset_axis

```cpp
bool reset_axis(
    mik::distance_position sensor_pos,
    mik::wall_position wall_pos,
    float max_reset_distance
)
```


### function right_swing_to_angle

```cpp
inline void right_swing_to_angle(
    float angle,
    const swing_to_angle_params & p
)
```


**Parameters**: 

  * **angle** Desired angle in degrees. 
  * **turn_direction** The way the robot should turn, (ccw, cw, or shortest path) 
  * **min_voltage** Minimum voltage on the drive, used for chaining movements. 
  * **max_voltage** Max voltage on the drive out of 12. 
  * **settle_error** Error to be considered settled in degrees. 
  * **settle_time** Time to be considered settled in milliseconds. 
  * **timeout** Time before quitting and move on in milliseconds. 
  * **k** [PID](/api/classes/class_p_i_d) and starti constants. Do k. to access constants. 
  * **[wait](/api/classes/class_chassis#function-wait)** Yields program until motion has finished, true by default. 


Turns to a given angle with the right side of the drivetrain. Like [turn_to_angle()](/api/classes/class_chassis#function-turn-to-angle), is optimized for turning the shorter direction, unless a turn direction is specified


### function right_swing_to_point

```cpp
inline void right_swing_to_point(
    float X_position,
    float Y_position,
    const swing_to_point_params & p
)
```

Turns to a specified point on the field with the right side of the drivetrain. Functions similarly to [right_swing_to_angle()](/api/classes/class_chassis#function-right-swing-to-angle) except with a point. The angle_offset parameter turns the robot extra relative to the desired target. For example, if you want the back of your robot to point at (36, 42), you would run right_swing_to_point(36, 42, {.angle_offset = 180}). 

**Parameters**: 

  * **X_position** Desired x position in inches. 
  * **Y_position** Desired y position in inches. 
  * **angle_offset** Angle turned past the desired heading in degrees. 
  * **turn_direction** The way the robot should turn, (ccw, cw, or shortest path) 
  * **min_voltage** Minimum voltage on the drive, used for chaining movements. 
  * **max_voltage** Max voltage on the drive out of 12. 
  * **settle_error** Error to be considered settled in degrees. 
  * **settle_time** Time to be considered settled in milliseconds. 
  * **timeout** Time before quitting and move on in milliseconds. 
  * **k** [PID](/api/classes/class_p_i_d) and starti constants. Do k. to access constants. 
  * **[wait](/api/classes/class_chassis#function-wait)** Yields program until motion has finished, true by default. 


### function set_brake_type

```cpp
void set_brake_type(
    vex::brakeType brake
)
```

Globally sets the brake mode for both drive motor groups. 

**Parameters**: 

  * **mode** coast, brake, hold 


### function set_control_constants

```cpp
void set_control_constants(
    float control_throttle_deadband,
    float control_throttle_min_output,
    float control_throttle_curve_gain,
    float control_turn_deadband,
    float control_turn_min_output,
    float control_turn_curve_gain
)
```

Reset default joystick control constants for throttle and turn. Try it out in desmos [https://www.desmos.com/calculator/umicbymbnl](https://www.desmos.com/calculator/umicbymbnl). 

**Parameters**: 

  * **[control_throttle_deadband](/api/classes/class_chassis#variable-control-throttle-deadband)** Deadband percent for the throttle axis. 
  * **[control_throttle_min_output](/api/classes/class_chassis#variable-control-throttle-min-output)** Minimum throttle output percent after deadband. 
  * **[control_throttle_curve_gain](/api/classes/class_chassis#variable-control-throttle-curve-gain)** Expo gain for throttle axis (1 linear, 1.06 very curvy). 
  * **[control_turn_deadband](/api/classes/class_chassis#variable-control-turn-deadband)** Deadband percent for the turn axis. 
  * **[control_turn_min_output](/api/classes/class_chassis#variable-control-turn-min-output)** Minimum turn output percent after deadband. 
  * **[control_turn_curve_gain](/api/classes/class_chassis#variable-control-turn-curve-gain)** Expo gain for turn axis. 


### function set_coordinates

```cpp
void set_coordinates(
    float X_position,
    float Y_position,
    float orientation_deg
)
```

Resets the robot's coordinates and heading. This is for odom-using robots to specify where the bot is at the beginning of the match. 

**Parameters**: 

  * **X_position** Robot's x in inches. 
  * **Y_position** Robot's y in inches. 
  * **orientation_deg** Desired heading in degrees. 


### function set_drive_constants

```cpp
void set_drive_constants(
    float drive_max_voltage,
    float drive_kp,
    float drive_ki,
    float drive_kd,
    float drive_starti,
    float drive_slew
)
```

Resets default drive constants. Driving includes [drive_distance()](/api/classes/class_chassis#function-drive-distance), [drive_to_point()](/api/classes/class_chassis#function-drive-to-point), [drive_to_pose()](/api/classes/class_chassis#function-drive-to-pose), and [follow_path()](/api/classes/class_chassis#function-follow-path). 

**Parameters**: 

  * **[drive_max_voltage](/api/classes/class_chassis#variable-drive-max-voltage)** Max voltage out of 12. 
  * **[drive_kp](/api/classes/class_chassis#variable-drive-kp)** Proportional constant. 
  * **[drive_ki](/api/classes/class_chassis#variable-drive-ki)** Integral constant. 
  * **[drive_kd](/api/classes/class_chassis#variable-drive-kd)** Derivative constant. 
  * **[drive_starti](/api/classes/class_chassis#variable-drive-starti)** Minimum distance in inches for integral to begin. 
  * **[drive_slew](/api/classes/class_chassis#variable-drive-slew)** Slew rate in volt per 10 ms. 


### function set_drive_exit_conditions

```cpp
void set_drive_exit_conditions(
    float drive_settle_error,
    float drive_settle_time,
    float drive_timeout
)
```

Resets default drive exit conditions. The robot exits when error is less than settle_error for a duration of settle_time, or if the function has gone on for longer than timeout. 

**Parameters**: 

  * **[drive_settle_error](/api/classes/class_chassis#variable-drive-settle-error)** Error to be considered settled in inches. 
  * **[drive_settle_time](/api/classes/class_chassis#variable-drive-settle-time)** Time to be considered settled in milliseconds. 
  * **[drive_timeout](/api/classes/class_chassis#variable-drive-timeout)** Time before quitting and move on in milliseconds. 


### function set_heading

```cpp
void set_heading(
    float orientation_deg
)
```

Resets the robot's heading. For example, at the beginning of auton, if your robot starts at 45 degrees, so set_heading(45) and the robot will know which way it's facing. 

**Parameters**: 

  * **orientation_deg** Desired heading in degrees. 


### function set_heading_constants

```cpp
void set_heading_constants(
    float heading_max_voltage,
    float heading_kp,
    float heading_ki,
    float heading_kd,
    float heading_starti,
    float heading_slew
)
```

Resets default heading constants. Heading control keeps the robot facing the right direction and is part of [drive_distance()](/api/classes/class_chassis#function-drive-distance), [drive_to_point()](/api/classes/class_chassis#function-drive-to-point), [drive_to_pose()](/api/classes/class_chassis#function-drive-to-pose), and [follow_path()](/api/classes/class_chassis#function-follow-path). 

**Parameters**: 

  * **[heading_max_voltage](/api/classes/class_chassis#variable-heading-max-voltage)** Max voltage out of 12. 
  * **[heading_kp](/api/classes/class_chassis#variable-heading-kp)** Proportional constant. 
  * **[heading_ki](/api/classes/class_chassis#variable-heading-ki)** Integral constant. 
  * **[heading_kd](/api/classes/class_chassis#variable-heading-kd)** Derivative constant. 
  * **[heading_starti](/api/classes/class_chassis#variable-heading-starti)** Minimum angle in degrees for integral to begin. 
  * **[heading_slew](/api/classes/class_chassis#variable-heading-slew)** Slew rate in volt per 10 ms. 


### function set_swing_constants

```cpp
void set_swing_constants(
    float swing_max_voltage,
    float swing_kp,
    float swing_ki,
    float swing_kd,
    float swing_starti,
    float swing_slew
)
```

Resets default swing constants. Swing control holds one side of the drive still and turns with the other. Used in [left_swing_to_angle()](/api/classes/class_chassis#function-left-swing-to-angle), [right_swing_to_angle()](/api/classes/class_chassis#function-right-swing-to-angle), [right_swing_to_point()](/api/classes/class_chassis#function-right-swing-to-point) and left_swing_to_point. 

**Parameters**: 

  * **[swing_max_voltage](/api/classes/class_chassis#variable-swing-max-voltage)** Max voltage out of 12. 
  * **[swing_kp](/api/classes/class_chassis#variable-swing-kp)** Proportional constant. 
  * **[swing_ki](/api/classes/class_chassis#variable-swing-ki)** Integral constant. 
  * **[swing_kd](/api/classes/class_chassis#variable-swing-kd)** Derivative constant. 
  * **[swing_starti](/api/classes/class_chassis#variable-swing-starti)** Minimum angle in degrees for integral to begin. 
  * **[swing_slew](/api/classes/class_chassis#variable-swing-slew)** Slew rate in volt per 10 ms. 


### function set_swing_exit_conditions

```cpp
void set_swing_exit_conditions(
    float swing_settle_error,
    float swing_settle_time,
    float swing_timeout
)
```

Resets default swing exit conditions. The robot exits when error is less than settle_error for a duration of settle_time, or if the function has gone on for longer than timeout. 

**Parameters**: 

  * **[swing_settle_error](/api/classes/class_chassis#variable-swing-settle-error)** Error to be considered settled in degrees. 
  * **[swing_settle_time](/api/classes/class_chassis#variable-swing-settle-time)** Time to be considered settled in milliseconds. 
  * **[swing_timeout](/api/classes/class_chassis#variable-swing-timeout)** Time before quitting and move on in milliseconds. 


### function set_tracking_offsets

```cpp
void set_tracking_offsets(
    float forward_tracker_center_distance,
    float sideways_tracker_center_distance
)
```

Resets the tracking offsets. Used for when robots center of rotation changes, ex: clamping onto a large game object. 

**Parameters**: 

  * **forward_tracker_center_distance** Distance from the chassis centre to the forward tracker (in). 
  * **sideways_tracker_center_distance** Distance from the chassis centre to the sideways tracker (in). 


### function set_turn_constants

```cpp
void set_turn_constants(
    float turn_max_voltage,
    float turn_kp,
    float turn_ki,
    float turn_kd,
    float turn_starti,
    float turn_slew
)
```

Resets default turn constants. Turning includes [turn_to_angle()]() and [turn_to_point()](). 

**Parameters**: 

  * **[turn_max_voltage](/api/classes/class_chassis#variable-turn-max-voltage)** Max voltage out of 12. 
  * **[turn_kp](/api/classes/class_chassis#variable-turn-kp)** Proportional constant. 
  * **[turn_ki](/api/classes/class_chassis#variable-turn-ki)** Integral constant. 
  * **[turn_kd](/api/classes/class_chassis#variable-turn-kd)** Derivative constant. 
  * **[turn_starti](/api/classes/class_chassis#variable-turn-starti)** Minimum angle in degrees for integral to begin. 
  * **[turn_slew](/api/classes/class_chassis#variable-turn-slew)** Slew rate in volt per 10 ms. 


### function set_turn_exit_conditions

```cpp
void set_turn_exit_conditions(
    float turn_settle_error,
    float turn_settle_time,
    float turn_timeout
)
```

Resets default turn exit conditions. The robot exits when error is less than settle_error for a duration of settle_time, or if the function has gone on for longer than timeout. 

**Parameters**: 

  * **[turn_settle_error](/api/classes/class_chassis#variable-turn-settle-error)** Error to be considered settled in degrees. 
  * **[turn_settle_time](/api/classes/class_chassis#variable-turn-settle-time)** Time to be considered settled in milliseconds. 
  * **[turn_timeout](/api/classes/class_chassis#variable-turn-timeout)** Time before quitting and move on in milliseconds. 


### function split_arcade

```cpp
void split_arcade()
```


### function split_arcade_curved

```cpp
void split_arcade_curved()
```


### function stop_drive

```cpp
void stop_drive(
    vex::brakeType brake
)
```

Stops both sides of the drivetrain. 

**Parameters**: 

  * **mode** coast, brake, hold 


### function tank

```cpp
void tank()
```


### function tank_curved

```cpp
void tank_curved()
```


### function turn_to_angle

```cpp
inline void turn_to_angle(
    float angle,
    const turn_to_angle_params & p
)
```

Turns the robot to a field-centric angle. Optimizes direction, so it turns whichever way is closer to the current heading of the robot, unless a turn direction is specified. 

**Parameters**: 

  * **angle** Desired angle in degrees. 
  * **turn_direction** The way the robot should turn, (ccw, cw, or shortest path) 
  * **min_voltage** Minimum voltage on the drive, used for chaining movements. 
  * **max_voltage** Max voltage on the drive out of 12. 
  * **settle_error** Error to be considered settled in degrees. 
  * **settle_time** Time to be considered settled in milliseconds. 
  * **timeout** Time before quitting and move on in milliseconds. 
  * **k** [PID](/api/classes/class_p_i_d) and starti constants. Do k. to access constants. 
  * **[wait](/api/classes/class_chassis#function-wait)** Yields program until motion has finished, true by default. 


### function turn_to_point

```cpp
inline void turn_to_point(
    float X_position,
    float Y_position,
    const turn_to_point_params & p
)
```

Turns to a specified point on the field. Functions similarly to [turn_to_angle()](/api/classes/class_chassis#function-turn-to-angle) except with a point. The angle_offset parameter turns the robot extra relative to the desired target. For example, if you want the back of your robot to point at (36, 42), you would run turn_to_point(36, 42, {.angle_offset = 180}). 

**Parameters**: 

  * **X_position** Desired x position in inches. 
  * **Y_position** Desired y position in inches. 
  * **angle_offset** Angle turned past the desired heading in degrees. 
  * **turn_direction** The way the robot should turn, (ccw, cw, or shortest path) 
  * **min_voltage** Minimum voltage on the drive, used for chaining movements. 
  * **max_voltage** Max voltage on the drive out of 12. 
  * **settle_error** Error to be considered settled in degrees. 
  * **settle_time** Time to be considered settled in milliseconds. 
  * **timeout** Time before quitting and move on in milliseconds. 
  * **k** [PID](/api/classes/class_p_i_d) and starti constants. Do k. to access constants. 
  * **[wait](/api/classes/class_chassis#function-wait)** Yields program until motion has finished, true by default. 


### function update_drive_max_voltage

```cpp
void update_drive_max_voltage(
    float drive_max_voltage
)
```

Changes the drive max voltage that is currently being used for a drive motion. 

**Parameters**: 

  * **[drive_max_voltage](/api/classes/class_chassis#variable-drive-max-voltage)** voltage of the drive, 0-12. 


Example: chassis.drive_distance(12, {.drive_max_voltage = 12, .wait = false}); // Drives robot at 12 volts chassis.wait_until(6); // Waits until robot has driven 6 inches at 12 volts update_drive_max_voltage(6); // Sets max speed to 6 volts chassis.wait(); // Finishes drive distance at 6 volts


### function update_heading_max_voltage

```cpp
void update_heading_max_voltage(
    float heading_max_voltage
)
```

Changes the heading max voltage that is currently being used for a drive motion. 

**Parameters**: 

  * **[heading_max_voltage](/api/classes/class_chassis#variable-heading-max-voltage)** voltage of the heading, 0-12. 


### function update_swing_max_voltage

```cpp
void update_swing_max_voltage(
    float swing_max_voltage
)
```

Changes the swing max voltage that is currently being used for a drive motion. 

**Parameters**: 

  * **[swing_max_voltage](/api/classes/class_chassis#variable-swing-max-voltage)** voltage of swinging, 0-12. 


### function update_turn_max_voltage

```cpp
void update_turn_max_voltage(
    float turn_max_voltage
)
```

Changes the turn max voltage that is currently being used for a drive motion. 

**Parameters**: 

  * **[turn_max_voltage](/api/classes/class_chassis#variable-turn-max-voltage)** voltage of turning, 0-12. 


### function wait

```cpp
void wait()
```

Yield to the scheduler until motion is finished. 

### function wait_until

```cpp
void wait_until(
    float units
)
```

Yield to the scheduler until the current motion the robots in has traveled specifed units. Drive motions use inches, turn motions use degrees. 

**Parameters**: 

  * **units** units of motion (inches or degrees). 


### function x_pos_mirrored

```cpp
bool x_pos_mirrored()
```


**Return**: True if x coordinates have been mirrored 

### function y_pos_mirrored

```cpp
bool y_pos_mirrored()
```


**Return**: True if y coordinates have been mirrored 

## Public Attributes Documentation

### variable active_min_voltage

```cpp
float active_min_voltage = 0;
```


### variable boomerang_drift

```cpp
float boomerang_drift;
```


### variable boomerang_lead

```cpp
float boomerang_lead;
```


### variable boomerang_setback

```cpp
float boomerang_setback;
```


### variable calibrating

```cpp
bool calibrating = false;
```


### variable control_disabled

```cpp
bool control_disabled;
```


### variable control_throttle_curve_gain

```cpp
float control_throttle_curve_gain;
```


### variable control_throttle_deadband

```cpp
float control_throttle_deadband;
```


### variable control_throttle_min_output

```cpp
float control_throttle_min_output;
```


### variable control_turn_curve_gain

```cpp
float control_turn_curve_gain;
```


### variable control_turn_deadband

```cpp
float control_turn_deadband;
```


### variable control_turn_min_output

```cpp
float control_turn_min_output;
```


### variable desired_X_position

```cpp
float desired_X_position = 0;
```


### variable desired_Y_position

```cpp
float desired_Y_position = 0;
```


### variable desired_angle

```cpp
float desired_angle = 0;
```


SET POINTS. USED FOR GRAPHING AND ACCESSING CHASSIS DATA IN ANOTHER TASK 


### variable desired_angle_offset

```cpp
float desired_angle_offset = 0;
```


### variable desired_distance

```cpp
float desired_distance = 0;
```


### variable desired_heading

```cpp
float desired_heading = 0;
```


### variable desired_path

```cpp
std::vector< point > desired_path {};
```


### variable distance_traveled

```cpp
float distance_traveled;
```


### variable drive_kd

```cpp
float drive_kd;
```


### variable drive_ki

```cpp
float drive_ki;
```


### variable drive_kp

```cpp
float drive_kp;
```


### variable drive_max_voltage

```cpp
float drive_max_voltage;
```


### variable drive_min_voltage

```cpp
float drive_min_voltage = 0;
```


ALL CONSTANTS USED IN MOTIONS. 


### variable drive_settle_error

```cpp
float drive_settle_error;
```


### variable drive_settle_time

```cpp
float drive_settle_time;
```


### variable drive_slew

```cpp
float drive_slew;
```


### variable drive_starti

```cpp
float drive_starti;
```


### variable drive_timeout

```cpp
float drive_timeout;
```


### variable forward_tracker

```cpp
mik::tracker forward_tracker;
```


### variable heading_kd

```cpp
float heading_kd;
```


### variable heading_ki

```cpp
float heading_ki;
```


### variable heading_kp

```cpp
float heading_kp;
```


### variable heading_max_voltage

```cpp
float heading_max_voltage;
```


### variable heading_slew

```cpp
float heading_slew;
```


### variable heading_starti

```cpp
float heading_starti;
```


### variable inertial

```cpp
vex::inertial inertial;
```


### variable left_drive

```cpp
mik::motor_group left_drive;
```


### variable motion_running

```cpp
bool motion_running;
```


### variable position_tracking

```cpp
bool position_tracking;
```


### variable pursuit_lookahead_distance

```cpp
float pursuit_lookahead_distance;
```


### variable reset_sensors

```cpp
mik::distance_reset reset_sensors;
```


### variable right_drive

```cpp
mik::motor_group right_drive;
```


### variable selected_drive_mode

```cpp
mik::drive_mode selected_drive_mode = mik::drive_mode::SPLIT_ARCADE;
```


### variable sideways_tracker

```cpp
mik::tracker sideways_tracker;
```


### variable sideways_tracker_used

```cpp
bool sideways_tracker_used;
```


### variable stop_apply_drive_slew

```cpp
float stop_apply_drive_slew = 7.5;
```


### variable stop_apply_swing_slew

```cpp
float stop_apply_swing_slew = 20;
```


### variable stop_apply_turn_slew

```cpp
float stop_apply_turn_slew = 20;
```


### variable swing_kd

```cpp
float swing_kd;
```


### variable swing_ki

```cpp
float swing_ki;
```


### variable swing_kp

```cpp
float swing_kp;
```


### variable swing_max_voltage

```cpp
float swing_max_voltage;
```


### variable swing_min_voltage

```cpp
float swing_min_voltage = 0;
```


### variable swing_opposite_voltage

```cpp
float swing_opposite_voltage = 0;
```


### variable swing_settle_error

```cpp
float swing_settle_error;
```


### variable swing_settle_time

```cpp
float swing_settle_time;
```


### variable swing_slew

```cpp
float swing_slew;
```


### variable swing_starti

```cpp
float swing_starti;
```


### variable swing_timeout

```cpp
float swing_timeout;
```


### variable tracker_mode

```cpp
mik::tracker_mode tracker_mode;
```


### variable turn_kd

```cpp
float turn_kd;
```


### variable turn_ki

```cpp
float turn_ki;
```


### variable turn_kp

```cpp
float turn_kp;
```


### variable turn_max_voltage

```cpp
float turn_max_voltage;
```


### variable turn_min_voltage

```cpp
float turn_min_voltage = 0;
```


### variable turn_settle_error

```cpp
float turn_settle_error;
```


### variable turn_settle_time

```cpp
float turn_settle_time;
```


### variable turn_slew

```cpp
float turn_slew;
```


### variable turn_starti

```cpp
float turn_starti;
```


### variable turn_timeout

```cpp
float turn_timeout;
```


-------------------------------

Updated on 2026-03-02 at 17:21:00 -0600