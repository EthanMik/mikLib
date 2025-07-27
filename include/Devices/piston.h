#pragma once

#include "vex.h"

namespace mik {

class piston {

public:
    /**
    * @brief Creates a new pneumatics object on the port specified in the parameter.
    * @param port A reference to a three wire port.
    */
    piston(int triport);

    /** @returns The state of the solenoid. True is open, false is closed. */
    bool state() const;

    /** @brief Opens the solenoid. */
    void open();
    
    /** @brief Closes the solenoid. */
    void close();

    /** @brief Flip the solenoid state: open → close or close → open. */
    void toggle();

    /** 
     * @brief Changes solenoid state.
     * @param state True → open, false → close.
     */
    void set(bool state);

private:
    vex::digital_out solenoid;
    bool state_;
};
} 