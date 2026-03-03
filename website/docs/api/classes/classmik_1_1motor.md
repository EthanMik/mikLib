---
title: mik::motor

---

# mik::motor






`#include <motors.h>`

Inherits from vex::motor

## Public Functions

|                | Name           |
| -------------- | -------------- |
| vex::gearSetting | **[gear_cartridge](/api/classes/classmik_1_1motor#function-gear-cartridge)**() const |
| | **[motor](/api/classes/classmik_1_1motor#function-motor)**(int port, bool reversed, vex::gearSetting gear_cartridge, std::string name)<br>Creates a new motor object with a name on the port specified and sets the reversed flag.  |
| | **[motor](/api/classes/classmik_1_1motor#function-motor)**(int port, bool reversed, std::string name) |
| | **[motor](/api/classes/classmik_1_1motor#function-motor)**(const motor & other) |
| | **[motor](/api/classes/classmik_1_1motor#function-motor)**(motor && other) |
| std::string & | **[name](/api/classes/classmik_1_1motor#function-name)**() |
| const std::string | **[name](/api/classes/classmik_1_1motor#function-name)**() const |
| bool | **[reversed](/api/classes/classmik_1_1motor#function-reversed)**() const |
| | **[~motor](/api/classes/classmik_1_1motor#function-~motor)**() |

## Public Functions Documentation

### function gear_cartridge

```cpp
vex::gearSetting gear_cartridge() const
```


**Return**: The gear cartidge used in [mik::motor](/api/classes/classmik_1_1motor), default is 6 to 1 

### function motor

```cpp
motor(
    int port,
    bool reversed,
    vex::gearSetting gear_cartridge,
    std::string name
)
```

Creates a new motor object with a name on the port specified and sets the reversed flag. 

**Parameters**: 

  * **port** The port index for this motor. The index is zero-based. 
  * **reverse** Sets the reverse flag for the new motor object. 
  * **[name](/api/classes/classmik_1_1motor#function-name)** Sets the name for the motor 


### function motor

```cpp
motor(
    int port,
    bool reversed,
    std::string name
)
```


### function motor

```cpp
motor(
    const motor & other
)
```


### function motor

```cpp
motor(
    motor && other
)
```


### function name

```cpp
std::string & name()
```


**Return**: The name given to [mik::motor](/api/classes/classmik_1_1motor)

### function name

```cpp
const std::string name() const
```


**Return**: The name given to [mik::motor](/api/classes/classmik_1_1motor)

### function reversed

```cpp
bool reversed() const
```


**Return**: True is motor is reversed 

### function ~motor

```cpp
~motor()
```


-------------------------------

Updated on 2026-03-02 at 17:21:01 -0600