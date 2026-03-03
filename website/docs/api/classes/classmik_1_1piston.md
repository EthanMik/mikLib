---
title: mik::piston

---

# mik::piston






`#include <piston.h>`

## Public Functions

|                | Name           |
| -------------- | -------------- |
| void | **[close](/api/classes/classmik_1_1piston#function-close)**()<br>Closes the solenoid.  |
| int | **[expander_port](/api/classes/classmik_1_1piston#function-expander-port)**() const |
| void | **[open](/api/classes/classmik_1_1piston#function-open)**()<br>Opens the solenoid.  |
| | **[piston](/api/classes/classmik_1_1piston#function-piston)**(int triport)<br>Creates a new piston object on the port specified in the parameter.  |
| | **[piston](/api/classes/classmik_1_1piston#function-piston)**(int triport, bool state)<br>Creates a new piston object on the port specified in the parameter.  |
| | **[piston](/api/classes/classmik_1_1piston#function-piston)**(int expander_port, int solenoid_port, bool state)<br>Creates a new piston object on a triport expander.  |
| void | **[set](/api/classes/classmik_1_1piston#function-set)**(bool state)<br>Changes solenoid state.  |
| bool | **[state](/api/classes/classmik_1_1piston#function-state)**() const |
| void | **[toggle](/api/classes/classmik_1_1piston#function-toggle)**()<br>Flip the solenoid state: open → close or close → open.  |
| int | **[triport_port](/api/classes/classmik_1_1piston#function-triport-port)**() const |

## Public Functions Documentation

### function close

```cpp
void close()
```

Closes the solenoid. 

### function expander_port

```cpp
int expander_port() const
```


**Return**: The expander port (PORT1 format), or 0 if using the brain's built-in triport 

### function open

```cpp
void open()
```

Opens the solenoid. 

### function piston

```cpp
piston(
    int triport
)
```

Creates a new piston object on the port specified in the parameter. 

**Parameters**: 

  * **triport** Triport in "PORT_A" format. 


### function piston

```cpp
piston(
    int triport,
    bool state
)
```

Creates a new piston object on the port specified in the parameter. 

**Parameters**: 

  * **triport** Triport in "PORT_A" format. 
  * **[state](/api/classes/classmik_1_1piston#function-state)** The state to start the piston at True → open, false → close. 


### function piston

```cpp
piston(
    int expander_port,
    int solenoid_port,
    bool state
)
```

Creates a new piston object on a triport expander. 

**Parameters**: 

  * **[expander_port](/api/classes/classmik_1_1piston#function-expander-port)** Port in "PORT1" format. 
  * **solenoid_port** Triport in "PORT_A" format. 
  * **[state](/api/classes/classmik_1_1piston#function-state)** The state to start the piston at True → open, false → close. 


### function set

```cpp
void set(
    bool state
)
```

Changes solenoid state. 

**Parameters**: 

  * **[state](/api/classes/classmik_1_1piston#function-state)** True → open, false → close. 


### function state

```cpp
bool state() const
```


**Return**: The state of the solenoid. True is open, false is closed. 

### function toggle

```cpp
void toggle()
```

Flip the solenoid state: open → close or close → open. 

### function triport_port

```cpp
int triport_port() const
```


**Return**: The triport index (PORT_A format) of the solenoid 

-------------------------------

Updated on 2026-03-02 at 17:21:01 -0600