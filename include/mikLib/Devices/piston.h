#pragma once

#include "vex.h"

namespace mik {

class piston {

public:
    /**
     * @brief Creates a new piston object on the port specified in the parameter.
     * @param triport Triport in "PORT_A" format.
     */
    piston(int triport);

    /**
     * @brief Creates a new piston object on the port specified in the parameter.
     * @param triport Triport in "PORT_A" format.
     * @param state The state to start the piston at True → open, false → close.
    */
    piston(int triport, bool state);
    
    /**
     * @brief Creates a new piston object on a triport expander.
     * @param expander_port Port in "PORT1" format.
     * @param solenoid_port Triport in "PORT_A" format.
     * @param state The state to start the piston at True → open, false → close.
    */
    piston(int expander_port, int solenoid_port, bool state);
    
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
    vex::triport triport_expander;
    bool state_;
};
} 