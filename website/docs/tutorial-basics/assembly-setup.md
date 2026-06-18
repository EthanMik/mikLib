---
sidebar_position: 3
---

# User Control Setup

How to configure user control in assembly.cpp and main.cpp

## Assembly Setup

:::note
Using the assembly class is completely optional, there are many other ways to structure user control. In this example the robot has 1 intake motor and 1 piston.
:::

### Creating Devices

Navigate to `include/assembly.h`. This is what holds non drivetrain related devices.
To add a devices declare it as

```cpp
static vex::device_name name;
```

The vex devices commonly used are 
```cpp
vex::rotation
vex::optical
vex::distance
vex::limit
```

With mikLib specific devices being

```cpp
mik::piston
mik::motor
mik::motor_group
```

For a full list of all VEX devices check out their [api reference](https://api.vex.com/v5/home/cpp/index.html)

For our robot we will create a piston and intake device.

```cpp
static mik::motor intake_motor;
static mik::piston wing_piston;
```

Once you have your devices inside assembly.h, add functionally in robot-config.cpp by doing

```cpp
vex::device_name Assembly::name(PORT12)
```

:::important
For non vex:: triport devices make sure you convert the port letter to an actual triport object using `to_triport()`.
For `mik::piston` this is done automatically.
:::

```cpp
vex::limit Assembly::limit_switch(to_triport(PORT_A));
mik::piston Assembly::piston_toggle(to_triport(PORT_B));
```

For our example

```cpp
mik::motor Assembly::intake_motor(PORT16, false, blue_6_1, "intake");
mik::piston Assembly::wing_piston(PORT_B);
```

### User Control

Now you need a way of controlling these devices. First define functions used to control devices in assembly.h

```cpp
void intake_control();
void wing_piston_control(); 
```

Then in assembly.cpp add functionally to the functions.

:::note
`btnA_new_press` fires only on the initial press, and only reactivates on release. Use this instead of ```.pressing()``` for toggles.
:::

```cpp
// Extends or retracts piston when button A is pressed, 
// can only extend or retract again until button A is released and pressed again
void Assembly::wing_piston_control() {
    if (btnA_new_press(Controller.ButtonA.pressing())) {
        wing_piston.toggle();
    }
}

// Spins intake forward if L1 is being held, reverse if L2 is being held; stops otherwise
void Assembly::intake_control() {
    if (Controller.ButtonL1.pressing()) {
        intake_motor.spin(fwd, 12, volt);
    } else if (Controller.ButtonL2.pressing()) {
        intake_motor.spin(fwd, -12, volt);
    } else {
        intake_motor.stop();
    }
}
```

Then add your functions inside of control

```cpp
void Assembly::control() {
    static bool initialized = false;

    if (!initialized) {
        init();
        initialized = true;
    }

    intake_control();
    wing_piston_control();
}
```

### Completed Assembly Setup

```cpp
// assembly.h
class Assembly {
public:
  static mik::motor intake_motor;
  static mik::piston wing_piston;
  
  void init();
  void control();

  void intake_control();
  void wing_piston_control(); 
};
```

```cpp
// robot-config.cpp
mik::motor Assembly::intake_motor(PORT16, false, blue_6_1, "intake");
mik::piston Assembly::wing_piston(PORT_B);
```

```cpp
// assembly.cpp
void Assembly::control() {
    static bool initialized = false;

    if (!initialized) {
        init();
        initialized = true;
    }

    intake_control();
    wing_piston_control();
}

void Assembly::wing_piston_control() {
    if (btnA_new_press(Controller.ButtonA.pressing())) {
        wing_piston.toggle();
    }
}

void Assembly::intake_control() {
    if (Controller.ButtonL1.pressing()) {
        intake_motor.spin(fwd, 12, volt);
    } else if (Controller.ButtonL2.pressing()) {
        intake_motor.spin(fwd, -12, volt);
    } else {
        intake_motor.stop();
    }
}
```

## Chassis Control

Navigate to main.cpp to change the control mode. The most common one is split arcade,
where the left stick is the throttle, and right stick turns.

To use split arcade do
```cpp
chassis.control(drive_mode::SPLIT_ARCADE);
```

For finer control, you can also use tank drive, with the left stick controlling
the left side of the drivetrain, and right stick controlling right side.

```cpp
chassis.control(drive_mode::TANK);
```

### Control Curved

Both split arcade and tank support curved versions.

```cpp
chassis.control(drive_mode::SPLIT_ARCADE_CURVED);
chassis.control(drive_mode::TANK_CURVED);
```

Using curved drive provides finer control and will arc while turning and driving.

### Holonomic

Holonomic drivetrains can use 

```cpp
chassis.control(drive_mode::SPLIT_ARCADE_HOLONOMIC);
chassis.control(drive_mode::FIELD_CENTRIC_HOLONOMIC);
```

Field centric uses the inertial sensor to determine which direction it should go, meaning wherever you point the left stick no matter the orientation, the robot will drive in that direction.

### Constants

The constants for drive modes are ```deadband```, ```min_output```, ```curve_gain```,
and ```desaturate_bias```. With the scale being 0-100. Deadband applies to all drive
modes, while the others only apply to curve modes.

```cpp
// Each controller constant in the form of throttle, 
// turn (deadband, min_output, curve_gain), desaturate_bias.
chassis.set_control_constants(5, 10, 1.019, 5, 10, 1.019, 0.5);
```

With these constants, the left stick and right stick have a deadband of 5, meaning any inputs under 5 percent are 0. 

Then for drive curve modes for both sticks, any output past deadband, will be at a minimum 10%, with the output following an [exponential function using constant 1.019](https://www.desmos.com/calculator/umicbymbnl). The desaturate bias of 0.5, means that the throttle and turning have equal priority, will not exceed max speed of 100.

### Completed User Control Loop

```cpp
void user_control(void) {
  while (chassis.calibrating) { task::sleep(50); }

  enable_user_control();

  chassis.set_brake_type(brakeType::coast);

  while (true) {
    if (!control_disabled()) {      
        chassis.control(drive_mode::SPLIT_ARCADE);
        assembly.control();
    }
    task::sleep(5);
  }
}
```
