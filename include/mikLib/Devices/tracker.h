#pragma once

#include <vector>
#include "v5.h"
#include "v5_vcs.h"

namespace mik {

class tracker {

public:
    /**
     * @brief Creates a new piston object on the port specified in the parameter.
     * @param port Port in "PORT_A" or "PORT1".
     */
    tracker(int port);

    /**
     * @brief Creates a new piston object on a triport expander.
     * @param expander_port Port in "PORT1" format.
     * @param port Triport in "PORT_A" format.
    */
    tracker(int expander_port, int port);

    /** @returns True if the tracker is plugged in and working */
    bool installed();

    /** @returns The index of the tracker, 0 -> 21 for smart ports
     * and -1 -> -8 for triports
    */
    int index();

    /** 
     * @brief Resets the position of the tracker to the value of zero. 
    */   
    void resetPosition();

    /**
     * @brief Gets the angle of the tracker.
     * @return Returns a float that represents the unit value specified by the parameter of the encoder sensor.
     * @param units The measurement unit for the encoder device.
    */    
    float angle(vex::rotationUnits units = vex::rotationUnits::deg);

    /** 
     * @brief Sets the value of the tracker to the value specified in the parameter.
     * @param value Sets the current position of the tracker.
     * @param units The measurement unit for the position value.
    */
    void setPosition(float value, vex::rotationUnits units);

    /** 
     * @brief Gets the current position of the tracker.
     * @returns Returns a float that represents the current position of the encoder in the units defined in the parameter.
     * @param units The measurement unit for the position.
    */    
    float position(vex::rotationUnits units);

    // For VEXU
    bool is_rev_encoder = true;

private:
    bool is_three_wire;
    int port;

    vex::triport expander;
    vex::rotation rotation_tracker;
    vex::encoder encoder_tracker;
};

}
