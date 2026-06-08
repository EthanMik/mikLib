---
sidebar_position: 3
---

# Assembly Setup

How to configure user control in assembly.cpp

:::note
Using the assembly class is completely optional, there are many other ways to structure user control. In this example the robot has 1 intake motor and 1 piston.
:::

## Creating Devices

Navigate to include/assembly.h. This is what holds non drivetrain related devices.
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

Once you have your devices inside assembly.h, add functionally in robot_config.cpp by doing

```cpp
vex::device_name Assembly::name(PORT12)
```

For non vex:: triport devices make sure you convert the port letter to an actual triport object. 
For mik piston it will do it for you.

```cpp
vex::limit Assembly::limit_switch(to_triport(PORT_A));
mik::piston Assembly::piston_toggle(to_triport(PORT_B));
```

For our example

```cpp
mik::motor Assembly::intake_motor(PORT16, false, blue_6_1, "intake");
mik::piston Assembly::wing_piston(PORT_B);
```

## User Control

Now you need a way of controlling these devices. First define functions used to control devices in assembly.h

```cpp
void intake_control();
void wing_control(); 
```

Then in assembly.cpp add functionally to the functions.

```cpp
// Extends or retracts piston when button A is pressed, 
// can only extend or retract again until button A is released and pressed again
void Assembly::wing_piston_control() {
    if (btnA_new_press(Controller.ButtonA.pressing())) {
        scraper_piston.toggle();
    }
}

// Spins intake forward if L1 is being held, reverse if L2 is being held; stops otherwise
void Assembly::lower_intake_control() {
    if (Controller.ButtonL1.pressing()) {
        lower_intake_motors.spin(fwd, 12, volt);
    } else if (Controller.ButtonL2.pressing()) {
        lower_intake_motors.spin(fwd, -12, volt);
    } else {
        lower_intake_motors.stop();
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

## Completed Assembly Setup

```cpp
// assembly.h
class Assembly {
public:
  static mik::motor intake_motor;
  static mik::piston wing_piston;
  
  void init();
  void control();

  void intake_control();
  void wing_control(); 
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
        scraper_piston.toggle();
    }
}

void Assembly::intake_control() {
    if (Controller.ButtonL1.pressing()) {
        lower_intake_motors.spin(fwd, 12, volt);
    } else if (Controller.ButtonL2.pressing()) {
        lower_intake_motors.spin(fwd, -12, volt);
    } else {
        lower_intake_motors.stop();
    }
}
```

## Drivetrain Control