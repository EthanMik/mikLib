---
title: PID

---

# PID






`#include <PID.h>`

## Public Functions

|                | Name           |
| -------------- | -------------- |
| | **[PID](/api/classes/class_p_i_d#function-pid)**() |
| | **[PID](/api/classes/class_p_i_d#function-pid)**(float kp, float ki, float kd)<br>[PID](/api/classes/class_p_i_d) constructor with P, I, D.  |
| | **[PID](/api/classes/class_p_i_d#function-pid)**(float error, float kp, float ki, float kd, float starti)<br>[PID](/api/classes/class_p_i_d) constructor with P, I, D, and starti. Starti keeps the I term at 0 until error is less than starti.  |
| | **[PID](/api/classes/class_p_i_d#function-pid)**(float error, float kp, float ki, float kd, float starti, float settle_error, float settle_time, float timeout)<br>[PID](/api/classes/class_p_i_d) constructor with settling inputs. The settling system works like this: The robot is settled when error is less than settle_error for a duration of settle_time, or if the function has gone on for longer than timeout. Otherwise it is not settled. Starti keeps the I term at 0 until error is less than starti.  |
| float | **[compute](/api/classes/class_p_i_d#function-compute)**(float error)<br>Computes the output power based on the error. Typical [PID](/api/classes/class_p_i_d) calculation with some optimizations: When the robot crosses error=0, the i-term gets reset to 0. And, of course, the robot only accumulates i-term when error is less than starti.  |
| bool | **[is_settled](/api/classes/class_p_i_d#function-is-settled)**()<br>Computes whether or not the movement has settled. The robot is considered settled when error is less than settle_error for a duration of settle_time, or if the function has gone on for longer than timeout. Otherwise it is not settled.  |

## Public Attributes

|                | Name           |
| -------------- | -------------- |
| float | **[accumulated_error](/api/classes/class_p_i_d#variable-accumulated-error)**  |
| float | **[error](/api/classes/class_p_i_d#variable-error)**  |
| float | **[kd](/api/classes/class_p_i_d#variable-kd)**  |
| float | **[ki](/api/classes/class_p_i_d#variable-ki)**  |
| float | **[kp](/api/classes/class_p_i_d#variable-kp)**  |
| float | **[output](/api/classes/class_p_i_d#variable-output)**  |
| float | **[previous_error](/api/classes/class_p_i_d#variable-previous-error)**  |
| float | **[settle_error](/api/classes/class_p_i_d#variable-settle-error)**  |
| float | **[settle_time](/api/classes/class_p_i_d#variable-settle-time)**  |
| float | **[starti](/api/classes/class_p_i_d#variable-starti)**  |
| float | **[time_spent_running](/api/classes/class_p_i_d#variable-time-spent-running)**  |
| float | **[time_spent_settled](/api/classes/class_p_i_d#variable-time-spent-settled)**  |
| float | **[timeout](/api/classes/class_p_i_d#variable-timeout)**  |

## Public Functions Documentation

### function PID

```cpp
PID()
```


### function PID

```cpp
PID(
    float kp,
    float ki,
    float kd
)
```

[PID](/api/classes/class_p_i_d) constructor with P, I, D. 

**Parameters**: 

  * **[kp](/api/classes/class_p_i_d#variable-kp)** Proportional constant. 
  * **[ki](/api/classes/class_p_i_d#variable-ki)** Integral constant. 
  * **[kd](/api/classes/class_p_i_d#variable-kd)** Derivative constant. 


### function PID

```cpp
PID(
    float error,
    float kp,
    float ki,
    float kd,
    float starti
)
```

[PID](/api/classes/class_p_i_d) constructor with P, I, D, and starti. Starti keeps the I term at 0 until error is less than starti. 

**Parameters**: 

  * **[error](/api/classes/class_p_i_d#variable-error)** Difference in desired and current position. 
  * **[kp](/api/classes/class_p_i_d#variable-kp)** Proportional constant. 
  * **[ki](/api/classes/class_p_i_d#variable-ki)** Integral constant. 
  * **[kd](/api/classes/class_p_i_d#variable-kd)** Derivative constant. 
  * **[starti](/api/classes/class_p_i_d#variable-starti)** Maximum error to start integrating. 


### function PID

```cpp
PID(
    float error,
    float kp,
    float ki,
    float kd,
    float starti,
    float settle_error,
    float settle_time,
    float timeout
)
```

[PID](/api/classes/class_p_i_d) constructor with settling inputs. The settling system works like this: The robot is settled when error is less than settle_error for a duration of settle_time, or if the function has gone on for longer than timeout. Otherwise it is not settled. Starti keeps the I term at 0 until error is less than starti. 

**Parameters**: 

  * **[error](/api/classes/class_p_i_d#variable-error)** Difference in desired and current position. 
  * **[kp](/api/classes/class_p_i_d#variable-kp)** Proportional constant. 
  * **[ki](/api/classes/class_p_i_d#variable-ki)** Integral constant. 
  * **[kd](/api/classes/class_p_i_d#variable-kd)** Derivative constant. 
  * **[starti](/api/classes/class_p_i_d#variable-starti)** Maximum error to start integrating. 
  * **[settle_error](/api/classes/class_p_i_d#variable-settle-error)** Maximum error to be considered settled. 
  * **[settle_time](/api/classes/class_p_i_d#variable-settle-time)** Minimum time to be considered settled. 
  * **[timeout](/api/classes/class_p_i_d#variable-timeout)** Time after which to give up and move on. Using 0 will not time out movement. 


### function compute

```cpp
float compute(
    float error
)
```

Computes the output power based on the error. Typical [PID](/api/classes/class_p_i_d) calculation with some optimizations: When the robot crosses error=0, the i-term gets reset to 0. And, of course, the robot only accumulates i-term when error is less than starti. 

**Parameters**: 

  * **[error](/api/classes/class_p_i_d#variable-error)** Difference in desired and current position. 


**Return**: Output power. 

### function is_settled

```cpp
bool is_settled()
```

Computes whether or not the movement has settled. The robot is considered settled when error is less than settle_error for a duration of settle_time, or if the function has gone on for longer than timeout. Otherwise it is not settled. 

**Return**: Whether the movement is settled. 

## Public Attributes Documentation

### variable accumulated_error

```cpp
float accumulated_error = 0;
```


### variable error

```cpp
float error = 0;
```


### variable kd

```cpp
float kd = 0;
```


### variable ki

```cpp
float ki = 0;
```


### variable kp

```cpp
float kp = 0;
```


### variable output

```cpp
float output = 0;
```


### variable previous_error

```cpp
float previous_error = 0;
```


### variable settle_error

```cpp
float settle_error = 0;
```


### variable settle_time

```cpp
float settle_time = 0;
```


### variable starti

```cpp
float starti = 0;
```


### variable time_spent_running

```cpp
float time_spent_running = 0;
```


### variable time_spent_settled

```cpp
float time_spent_settled = 0;
```


### variable timeout

```cpp
float timeout = 0;
```


-------------------------------

Updated on 2026-03-02 at 17:21:00 -0600