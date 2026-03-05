---
sidebar_position: 2
---

# Chassis Setup

How to configure the mikLib chassis in robot-config.cpp

## Drivetrain 

The first step is to configure your drivetrain motors, each motor takes in 4 values, the port, whether or not the motor is reversed, 
its cartridge, and name.

```cpp
// Motor on port 1 with a blue cartridge that is not reversed
mik::motor(PORT1, false, blue_6_1, "my motor")
```


:::important

Right and left are from facing behind the front of the robot,
or the robots point of view.

:::

To determine the port of your motor you can open the device menu on the brain
and unplug the motor and see which port disappears. Do this for 
the left and right side of the drivetrain.

```cpp
// Left drivetrain motors (left/right is looking from behind the robot)
mik::motor_group({
    mik::motor(PORT1, false, blue_6_1, "left_front_motor"),
    mik::motor(PORT2, false, blue_6_1, "left_middle_motor"),
    mik::motor(PORT3, false, blue_6_1, "left_back_motor")
}),
// Right drivetrain motors
mik::motor_group({
    mik::motor(PORT4, false, blue_6_1, "right_front_motor"),
    mik::motor(PORT5, false, blue_6_1, "right_middle_motor"),
    mik::motor(PORT6, false, blue_6_1, "right_back_motor")
}),
```

When applying a positive voltage, all the drivetrain motors need to spin 
forward, to find which motors are reversed you can run the program, press
the **Config** tab at the top left, then press
**Spin Motors** at the bottom left. You should see each motor spin individually. Set reversed to 
**true** if motor does not spin forward.

// attach image

## Odometry

### Inertial Sensor

mikLib requires an [inertial sensor](https://www.vexrobotics.com/276-4855.html). Make sure your inertial sensor is lying down flat. To reduce vibrations
that cause the sensor to drift it is recommended to mount it on foam or rubber
links. 

// add image of that here

Place the port of your inertial sensor in the chassis.

```cpp
PORT10, // Inertial sensor port
```


### Inertial Scale

Sometimes what can happen is your inertial sensor will 
not read a full 360° after a full rotation. To fix this
you can apply a scale factor to your heading. To find this value run the program,
press **Config** then **Odom Data**. You should see **Rotation: 0.00000** with 
the small decimal places flickering. Turn your robot clockwise in a full 360 until it ends up
in the exact same spot it started. Use the value from **Rotation: 360.15**.

:::note
This is for extra precision, in most cases 360 will be fine to use
for inertial scale
:::

:::important
If the robot is not spun clockwise to find inertial scale, heading will be incorrect
:::

```cpp
360.15, // Inertial scale (reading after a full 360° turn)
```

### Force Calibrate Inertial

When set to true it will recalibrate the inertial sensor
automatically if after 1 second it drifts 0.05 degrees. 
This is to correct for when the robot is bumped during calibration leading 
the robot to think its spinning in circles. Set to false by default due to
calibration taking longer than expected.

```cpp
false,  // Forces inertial sensor to recalibrate
```

### Tracking Wheels

Tracking wheels are non motorized wheels with encoders attached to them.

:::note
Both a forward and sideways tracker near the robots center of rotation is optimal
:::

// attach image here

:::important
The forward tracking wheel is parallel to the wheels on the drivetrain, with 
sideways tracking wheel being perpendicular
:::

### Forward Tracker

import Tabs from '@theme/Tabs';
import TabItem from '@theme/TabItem';

The forward tracker measures the lateral distance of the robot. You can use
either a dedicated forward tracking wheel or your drivetrain motor encoders.

<Tabs>
  <TabItem value="motor-encoder" label="Motor Encoders" default>

If you don't have a dedicated forward tracking wheel, you can use the built-in
motor encoders from your drivetrain.

```cpp
motor_encoder, // Use "motor_encoder" if no forward tracker
```

To be able to use inches as distance measurement you need to plug in your drivetrain
wheel diameter in inches and gear ratio. If you have a 36 tooth gear attached to the motor with a 48
tooth gear attached to the wheel use 36/48 -> 0.75.

```cpp
2.75,   // Drivetrain wheel diameter (in). Negative flips direction.
0.75,   // Drivetrain gear ratio (e.g. 36T:48T = 0.75).
```

:::important
Run the program click on **Odom Data** on the **Config Tab**.
Take out a tape measure and move the robot 24 forward inches next to it. 
**If `Y: position` is not positive use a negative wheel diameter. If it is not reading 24
double check your wheel diameter is accurate.** 
:::

If you are using motor encoders for odometry you need an offset from the center of rotation. To get
this value you need to measure from the center of the wheel of the right and left drivetrain then divide
it by two. 

// Attach image here

```cpp
6,      // Drivetrain center distance (in), Half the track width
```


  </TabItem>
  <TabItem value="tracking-wheel" label="Forward Tracking Wheel">

If you have a dedicated forward tracking wheel, plug in the port and wheel
diameter.

```cpp
// Forward tracker on port 'A' with a 2.75" wheel
mik::tracker(PORT_A, 2.75, "forward_tracker"),
```



  </TabItem>
</Tabs>

### Sideways Tracker

The sideways tracker measures the horizontal distance of the robot

:::note
The sideways tracker is optional, however it is strongly
recommended for drivetrain's using only omni wheels.
:::

Plug in the port for the sideways tracker, you can use `PORT0` if you are 
not using one

```cpp
PORT0, // Sideways tracker port.
```

## Finished Chassis Setup

```cpp
// Left drivetrain motors (left/right is looking from behind the robot)
Chassis chassis(
  mik::motor_group({
    mik::motor(PORT1, false, blue_6_1, "left_front_motor"),
    mik::motor(PORT2, false, blue_6_1, "left_middle_motor"),
    mik::motor(PORT3, false, blue_6_1, "left_back_motor")
  }),
  // Right drivetrain motors
  mik::motor_group({
    mik::motor(PORT4, false, blue_6_1, "right_front_motor"),
    mik::motor(PORT5, false, blue_6_1, "right_middle_motor"),
    mik::motor(PORT6, false, blue_6_1, "right_back_motor")
  }),

  PORT9,  // Inertial sensor port
  360,    // Inertial scale (reading after a full 360° turn)
  false,  // Forces inertial sensor to recalibrate.

  forward_tracker, // Replace with "motor_encoder" if no forward tracker
  2.75,   // Drivetrain wheel diameter (in). Negative flips direction. 
  0.75,   // Drivetrain gear ratio (e.g. 36T:48T = 0.75). 
  6,      // Drivetrain center distance (in), Half the track width.

  PORT7,  // Forward tracker port. PORT0 if unused
  -2,     // Forward tracker wheel diameter (in). Negative flips direction.
  0,      // Forward tracker center distance (in). Positive = right of center, negative = left

  PORT8,  // Sideways tracker port. PORT0 if unused.
  2,      // Sideways tracker wheel diameter (in). Negative flips direction.
  0.3,    // Sideways tracker center distance (in). Positive = behind center, negative = in front

  // Distance sensors mounted on a face of the robot
  mik::distance_reset({
      mik::distance(
          PORT12,       // Distance sensor port
          front_sensor, // "front_sensor", "rear_sensor", "left_sensor", "right_sensor"
          5,            // X offset from tracking center (in).
          3.5           // Y offset from tracking center (in). 
      ),
      mik::distance(PORT13, left_sensor, -2, -4)
  })
);
```