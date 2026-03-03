---
title: mik::motor_group

---

# mik::motor_group






`#include <motors.h>`

## Public Functions

|                | Name           |
| -------------- | -------------- |
| float | **[averageCurrent](/api/classes/classmik_1_1motor__group#function-averagecurrent)**(vex::currentUnits units =vex::currentUnits::amp)<br>Gets the average electrical current for all motors in the group.  |
| float | **[averageEfficiency](/api/classes/classmik_1_1motor__group#function-averageefficiency)**(vex::percentUnits units =vex::percentUnits::pct)<br>Gets the average efficiency of the motors in the group.  |
| float | **[averagePower](/api/classes/classmik_1_1motor__group#function-averagepower)**(vex::powerUnits units =vex::powerUnits::watt)<br>Gets the average power of all motors in the group.  |
| float | **[averageTemperature](/api/classes/classmik_1_1motor__group#function-averagetemperature)**(vex::percentUnits units =vex::percentUnits::pct)<br>Gets the average temperature of the motors in the group.  |
| float | **[averageTemperature](/api/classes/classmik_1_1motor__group#function-averagetemperature)**(vex::temperatureUnits units)<br>Gets the average temperature of the motors in the group.  |
| float | **[averageTorque](/api/classes/classmik_1_1motor__group#function-averagetorque)**(vex::torqueUnits units =vex::torqueUnits::Nm)<br>Gets the average torque of the motors in the group.  |
| float | **[averageVoltage](/api/classes/classmik_1_1motor__group#function-averagevoltage)**(vex::voltageUnits units)<br>Gets the current average voltage of the motors in the group.  |
| int32_t | **[count](/api/classes/classmik_1_1motor__group#function-count)**(void )<br>return the number of motors in the motor group  |
| float | **[current](/api/classes/classmik_1_1motor__group#function-current)**(vex::currentUnits units =vex::currentUnits::amp)<br>Gets the sum electrical current for all motors in the group.  |
| float | **[current](/api/classes/classmik_1_1motor__group#function-current)**(vex::percentUnits units)<br>Gets the electrical current of the motors in percentage of maximum.  |
| float | **[efficiency](/api/classes/classmik_1_1motor__group#function-efficiency)**(vex::percentUnits units =vex::percentUnits::pct)<br>Gets the efficiency of the first motor in the group.  |
| std::vector< [mik::motor](/api/classes/classmik_1_1motor) > & | **[getMotors](/api/classes/classmik_1_1motor__group#function-getmotors)**() |
| bool | **[isDone](/api/classes/classmik_1_1motor__group#function-isdone)**(void )<br>Checks to see if all the motor are done rotating to a specific target.  |
| bool | **[isSpinning](/api/classes/classmik_1_1motor__group#function-isspinning)**(void )<br>Checks to see if any of the motors are rotating to a specific target.  |
| | **[motor_group](/api/classes/classmik_1_1motor__group#function-motor-group)**(const std::vector< [mik::motor](/api/classes/classmik_1_1motor) > & motors)<br>Constructs an array of mik motors that can be controlled at the same time.  |
| float | **[position](/api/classes/classmik_1_1motor__group#function-position)**(vex::rotationUnits units)<br>Gets the current position of the first motor in the group's encoder.  |
| float | **[power](/api/classes/classmik_1_1motor__group#function-power)**(vex::powerUnits units =vex::powerUnits::watt)<br>Gets the power of the first motor in the group.  |
| void | **[resetPosition](/api/classes/classmik_1_1motor__group#function-resetposition)**(void )<br>Resets the motor's encoder to the value of zero.  |
| void | **[setMaxTorque](/api/classes/classmik_1_1motor__group#function-setmaxtorque)**(float value, vex::percentUnits units)<br>Sets the max torque of the motors.  |
| void | **[setMaxTorque](/api/classes/classmik_1_1motor__group#function-setmaxtorque)**(float value, vex::torqueUnits units)<br>Sets the max torque of the motors.  |
| void | **[setMaxTorque](/api/classes/classmik_1_1motor__group#function-setmaxtorque)**(float value, vex::currentUnits units)<br>Sets the max torque of the motors.  |
| void | **[setPosition](/api/classes/classmik_1_1motor__group#function-setposition)**(float value, vex::rotationUnits units)<br>Sets the value of all motor encoders to the value specified in the parameter.  |
| void | **[setStopping](/api/classes/classmik_1_1motor__group#function-setstopping)**(vex::brakeType mode)<br>Sets the stopping mode of the motor group by passing a brake mode as a parameter.  |
| void | **[setTimeout](/api/classes/classmik_1_1motor__group#function-settimeout)**(int32_t time, vex::timeUnits units)<br>Sets the timeout for the motor group. If the motor group does not reach its' commanded position prior to the completion of the timeout, the motors will stop.  |
| void | **[setVoltage](/api/classes/classmik_1_1motor__group#function-setvoltage)**(float voltage, vex::voltageUnits units)<br>Sets the voltage of the motor group based on the parameters set in the command. This command will not run the motor. Any subsequent call that does not contain a specified motor voltage will use this value.  |
| void | **[spin](/api/classes/classmik_1_1motor__group#function-spin)**(vex::directionType dir)<br>Turns the motors on, and spins them in the specified direction.  |
| void | **[spin](/api/classes/classmik_1_1motor__group#function-spin)**(vex::directionType dir, float voltage, vex::voltageUnits units)<br>Turn on the motors and spins them in the specified direction and a specified voltage.  |
| bool | **[spinFor](/api/classes/classmik_1_1motor__group#function-spinfor)**(float rotation, vex::rotationUnits units, float voltage, vex::voltageUnits units_v, bool waitForCompletion =true)<br>Turn on the motors and spin them to a relative target rotation value at a specified velocity.  |
| bool | **[spinFor](/api/classes/classmik_1_1motor__group#function-spinfor)**(vex::directionType dir, float rotation, vex::rotationUnits units, float voltage, vex::voltageUnits units_v, bool waitForCompletion =true) |
| bool | **[spinFor](/api/classes/classmik_1_1motor__group#function-spinfor)**(float rotation, vex::rotationUnits units, bool waitForCompletion =true)<br>Turn on the motors and spin them to a relative target rotation value.  |
| bool | **[spinFor](/api/classes/classmik_1_1motor__group#function-spinfor)**(vex::directionType dir, float rotation, vex::rotationUnits units, bool waitForCompletion =true) |
| void | **[spinFor](/api/classes/classmik_1_1motor__group#function-spinfor)**(float time, vex::timeUnits units, float voltage, vex::voltageUnits units_v, bool waitForCompletion =true)<br>Turn on the motors and spin them to a relative target time value at a specified velocity.  |
| void | **[spinFor](/api/classes/classmik_1_1motor__group#function-spinfor)**(vex::directionType dir, float time, vex::timeUnits units, float voltage, vex::voltageUnits units_v, bool waitForCompletion =true) |
| void | **[stop](/api/classes/classmik_1_1motor__group#function-stop)**(void )<br>Stops all motors using the default brake mode.  |
| void | **[stop](/api/classes/classmik_1_1motor__group#function-stop)**(vex::brakeType mode)<br>Stops all motors using a specified brake mode.  |
| float | **[temperature](/api/classes/classmik_1_1motor__group#function-temperature)**(vex::percentUnits units =vex::percentUnits::pct)<br>Gets the temperature of the first motor in the group.  |
| float | **[temperature](/api/classes/classmik_1_1motor__group#function-temperature)**(vex::temperatureUnits units)<br>Gets the temperature of the first motor in the group.  |
| float | **[torque](/api/classes/classmik_1_1motor__group#function-torque)**(vex::torqueUnits units =vex::torqueUnits::Nm)<br>Gets the torque of the first motor in the group.  |
| float | **[voltage](/api/classes/classmik_1_1motor__group#function-voltage)**(vex::voltageUnits units =vex::voltageUnits::volt)<br>Gets the current voltage of the first motor in the group.  |

## Public Functions Documentation

### function averageCurrent

```cpp
float averageCurrent(
    vex::currentUnits units =vex::currentUnits::amp
)
```

Gets the average electrical current for all motors in the group. 

**Parameters**: 

  * **units** The measurement unit for the current. 


**Return**: Returns a float that represents the electrical current of the motors in the units defined in the parameter. 

### function averageEfficiency

```cpp
float averageEfficiency(
    vex::percentUnits units =vex::percentUnits::pct
)
```

Gets the average efficiency of the motors in the group. 

**Parameters**: 

  * **units** (Optional) The measurement unit for the efficiency. By default, this parameter is a percentage. 


**Return**: Returns the efficiency of the motor in the units defined in the parameter. 

### function averagePower

```cpp
float averagePower(
    vex::powerUnits units =vex::powerUnits::watt
)
```

Gets the average power of all motors in the group. 

**Parameters**: 

  * **units** The measurement unit for the power. 


**Return**: Returns a float that represents the power of the motor in the units defined in the parameter. 

### function averageTemperature

```cpp
float averageTemperature(
    vex::percentUnits units =vex::percentUnits::pct
)
```

Gets the average temperature of the motors in the group. 

**Parameters**: 

  * **units** The measurement unit for the temperature. 


**Return**: Returns the temperature of the motor in the units defined in the parameter. 

### function averageTemperature

```cpp
float averageTemperature(
    vex::temperatureUnits units
)
```

Gets the average temperature of the motors in the group. 

**Parameters**: 

  * **units** The measurement unit for the temperature. 


**Return**: Returns the temperature of the motor in the units defined in the parameter. 

### function averageTorque

```cpp
float averageTorque(
    vex::torqueUnits units =vex::torqueUnits::Nm
)
```

Gets the average torque of the motors in the group. 

**Parameters**: 

  * **units** The measurement unit for the torque. 


**Return**: Returns a float that represents the torque of the motor in the units defined in the parameter. 

### function averageVoltage

```cpp
float averageVoltage(
    vex::voltageUnits units
)
```

Gets the current average voltage of the motors in the group. 

**Parameters**: 

  * **units** The measurement unit for the voltage. 


**Return**: Returns a float that represents the current voltage of the motor in the units defined in the parameter. 

### function count

```cpp
int32_t count(
    void 
)
```

return the number of motors in the motor group 

**Return**: number of motors 

### function current

```cpp
float current(
    vex::currentUnits units =vex::currentUnits::amp
)
```

Gets the sum electrical current for all motors in the group. 

**Parameters**: 

  * **units** The measurement unit for the current. 


**Return**: Returns a float that represents the electrical current of the motors in the units defined in the parameter. 

### function current

```cpp
float current(
    vex::percentUnits units
)
```

Gets the electrical current of the motors in percentage of maximum. 

**Parameters**: 

  * **units** The measurement unit for the current. 


**Return**: Returns a float that represents the electrical current of the motors as percentage of max current. 

### function efficiency

```cpp
float efficiency(
    vex::percentUnits units =vex::percentUnits::pct
)
```

Gets the efficiency of the first motor in the group. 

**Parameters**: 

  * **units** (Optional) The measurement unit for the efficiency. By default, this parameter is a percentage. 


**Return**: Returns the efficiency of the motor in the units defined in the parameter. 

### function getMotors

```cpp
std::vector< mik::motor > & getMotors()
```


**Return**: The wrapped vex motors in a vector 

### function isDone

```cpp
bool isDone(
    void 
)
```

Checks to see if all the motor are done rotating to a specific target. 

**Return**: Returns a false Boolean if the motor is on and is rotating to a target. Returns a true Boolean if the motor is done rotating to a target. 

### function isSpinning

```cpp
bool isSpinning(
    void 
)
```

Checks to see if any of the motors are rotating to a specific target. 

**Return**: Returns a true Boolean if the motor is on and is rotating to a target. Returns a false Boolean if the motor is done rotating to a target. 

### function motor_group

```cpp
motor_group(
    const std::vector< mik::motor > & motors
)
```

Constructs an array of mik motors that can be controlled at the same time. 

### function position

```cpp
float position(
    vex::rotationUnits units
)
```

Gets the current position of the first motor in the group's encoder. 

**Parameters**: 

  * **units** The measurement unit for the position. 


**Return**: Returns a float that represents the current position of the motor in the units defined in the parameter. 

### function power

```cpp
float power(
    vex::powerUnits units =vex::powerUnits::watt
)
```

Gets the power of the first motor in the group. 

**Parameters**: 

  * **units** The measurement unit for the power. 


**Return**: Returns a float that represents the power of the motor in the units defined in the parameter. 

### function resetPosition

```cpp
void resetPosition(
    void 
)
```

Resets the motor's encoder to the value of zero. 

### function setMaxTorque

```cpp
void setMaxTorque(
    float value,
    vex::percentUnits units
)
```

Sets the max torque of the motors. 

**Parameters**: 

  * **value** Sets the amount of torque. 
  * **units** The measurement unit for the torque value. 


### function setMaxTorque

```cpp
void setMaxTorque(
    float value,
    vex::torqueUnits units
)
```

Sets the max torque of the motors. 

**Parameters**: 

  * **value** Sets the amount of torque. 
  * **units** The measurement unit for the torque value. 


### function setMaxTorque

```cpp
void setMaxTorque(
    float value,
    vex::currentUnits units
)
```

Sets the max torque of the motors. 

**Parameters**: 

  * **value** Sets the amount of torque. 
  * **units** The measurement unit for the torque value. 


### function setPosition

```cpp
void setPosition(
    float value,
    vex::rotationUnits units
)
```

Sets the value of all motor encoders to the value specified in the parameter. 

**Parameters**: 

  * **value** Sets the current position of the motor. 
  * **units** The measurement unit for the position value. 


### function setStopping

```cpp
void setStopping(
    vex::brakeType mode
)
```

Sets the stopping mode of the motor group by passing a brake mode as a parameter. 

**Parameters**: 

  * **mode** The stopping mode can be set to coast, brake, or hold. 


### function setTimeout

```cpp
void setTimeout(
    int32_t time,
    vex::timeUnits units
)
```

Sets the timeout for the motor group. If the motor group does not reach its' commanded position prior to the completion of the timeout, the motors will stop. 

**Parameters**: 

  * **time** Sets the amount of time. 
  * **units** The measurement unit for the time value. 


### function setVoltage

```cpp
void setVoltage(
    float voltage,
    vex::voltageUnits units
)
```

Sets the voltage of the motor group based on the parameters set in the command. This command will not run the motor. Any subsequent call that does not contain a specified motor voltage will use this value. 

**Parameters**: 

  * **[voltage](/api/classes/classmik_1_1motor__group#function-voltage)** Sets the amount of velocity. 
  * **units** The measurement unit for the voltage value. 


### function spin

```cpp
void spin(
    vex::directionType dir
)
```

Turns the motors on, and spins them in the specified direction. 

**Parameters**: 

  * **dir** The direction to spin the motors. 


### function spin

```cpp
void spin(
    vex::directionType dir,
    float voltage,
    vex::voltageUnits units
)
```

Turn on the motors and spins them in the specified direction and a specified voltage. 

**Parameters**: 

  * **dir** The direction to spin the motors. 
  * **[voltage](/api/classes/classmik_1_1motor__group#function-voltage)** Sets the amount of volts. 
  * **units** The measurement unit for the voltage value. 


### function spinFor

```cpp
bool spinFor(
    float rotation,
    vex::rotationUnits units,
    float voltage,
    vex::voltageUnits units_v,
    bool waitForCompletion =true
)
```

Turn on the motors and spin them to a relative target rotation value at a specified velocity. 

**Parameters**: 

  * **rotation** Sets the amount of rotation. 
  * **units** The measurement unit for the rotation value. 
  * **[voltage](/api/classes/classmik_1_1motor__group#function-voltage)** Sets the amount of velocity. 
  * **units_v** The measurement unit for the velocity value. 
  * **waitForCompletion** (Optional) If true, your program will wait until the motor reaches the target rotational value. If false, the program will continue after calling this function. By default, this parameter is true. 


**Return**: Returns a Boolean that signifies when the motor has reached the target rotation value. 

### function spinFor

```cpp
bool spinFor(
    vex::directionType dir,
    float rotation,
    vex::rotationUnits units,
    float voltage,
    vex::voltageUnits units_v,
    bool waitForCompletion =true
)
```


### function spinFor

```cpp
bool spinFor(
    float rotation,
    vex::rotationUnits units,
    bool waitForCompletion =true
)
```

Turn on the motors and spin them to a relative target rotation value. 

**Parameters**: 

  * **rotation** Sets the amount of rotation. 
  * **units** The measurement unit for the rotation value. 
  * **waitForCompletion** (Optional) If true, your program will wait until the motor reaches the target rotational value. If false, the program will continue after calling this function. By default, this parameter is true. 


**Return**: Returns a Boolean that signifies when the motor has reached the target rotation value. 

### function spinFor

```cpp
bool spinFor(
    vex::directionType dir,
    float rotation,
    vex::rotationUnits units,
    bool waitForCompletion =true
)
```


### function spinFor

```cpp
void spinFor(
    float time,
    vex::timeUnits units,
    float voltage,
    vex::voltageUnits units_v,
    bool waitForCompletion =true
)
```

Turn on the motors and spin them to a relative target time value at a specified velocity. 

**Parameters**: 

  * **time** Sets the amount of time. 
  * **units** The measurement unit for the time value. 
  * **velocity** Sets the amount of velocity. 
  * **units_v** The measurement unit for the velocity value. 


### function spinFor

```cpp
void spinFor(
    vex::directionType dir,
    float time,
    vex::timeUnits units,
    float voltage,
    vex::voltageUnits units_v,
    bool waitForCompletion =true
)
```


### function stop

```cpp
void stop(
    void 
)
```

Stops all motors using the default brake mode. 

### function stop

```cpp
void stop(
    vex::brakeType mode
)
```

Stops all motors using a specified brake mode. 

**Parameters**: 

  * **mode** The brake mode can be set to coast, brake, or hold. 


### function temperature

```cpp
float temperature(
    vex::percentUnits units =vex::percentUnits::pct
)
```

Gets the temperature of the first motor in the group. 

**Parameters**: 

  * **units** The measurement unit for the temperature. 


**Return**: Returns the temperature of the motor in the units defined in the parameter. 

### function temperature

```cpp
float temperature(
    vex::temperatureUnits units
)
```

Gets the temperature of the first motor in the group. 

**Parameters**: 

  * **units** The measurement unit for the temperature. 


**Return**: Returns the temperature of the motor in the units defined in the parameter. 

### function torque

```cpp
float torque(
    vex::torqueUnits units =vex::torqueUnits::Nm
)
```

Gets the torque of the first motor in the group. 

**Parameters**: 

  * **units** The measurement unit for the torque. 


**Return**: Returns a float that represents the torque of the motor in the units defined in the parameter. 

### function voltage

```cpp
float voltage(
    vex::voltageUnits units =vex::voltageUnits::volt
)
```

Gets the current voltage of the first motor in the group. 

**Parameters**: 

  * **units** The measurement unit for the voltage. 


**Return**: Returns a float that represents the current voltage of the motor in the units defined in the parameter. 

-------------------------------

Updated on 2026-03-02 at 17:21:01 -0600