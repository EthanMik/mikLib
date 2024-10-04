#include "654-Template/motor_chain.h"
#include "654-Template/manual_drive.h"
#include "654-Template/auton_drive.h"
#include "util.h"
#include "vex.h"

#include <vector>
#include <cmath>
#include <algorithm>

using namespace vex;

int get_sign(int num) {
  if (num == 0) { 
    return 1;
  }

  return num/abs(num);
}

void turnAlongCircleLeft(float radius, float arcLength){ //RADIUS IN INCHES
    const int ADJUSTMENT_SHARPNESS = 10; //How much the code will change velocity when veering off course

    float dotProduct;
    float lengthOfVector;
    float maxSpeedOfWheel = rightDrive.get_set_speed(velocity_units::normalized);
    float turnSpeed = maxSpeedOfWheel;
    float offset = chassis.get_absolute_heading();
    //Creates a normal vector pointing straight up
    std::vector<float> currentDirection(to_normalized_vector(chassis.get_absolute_heading()));
    std::vector<float> newDirection(currentDirection); // Normal Vector representing current orientation NEEDS REAL CODE
    std::vector<float> centerOfCircle(chassis.get_X_position() - newDirection[1]*radius , chassis.get_Y_position() + newDirection[0]*radius);
    std::vector<float> targetDestination(centerOfCircle[0] + radius * cos(to_rad(arcLength + offset)), centerOfCircle[1] + radius * sin(to_rad(arcLength + offset))); //Gives Euclidian coordinates of ending location
   
    //Declaration of variables used below \/
    float xPos;
    float yPos;
    float distToPath; //Distance from robot to the circular path (0 -> on path)


    while(false || get_vector_distance(chassis.get_position_vector(), targetDestination) > 1){
        xPos = chassis.get_X_position() - centerOfCircle[0];
        yPos = chassis.get_Y_position() - centerOfCircle[1];
        float distToPath = clamp(std::abs(get_vector_distance({0.0f, 0.0f}, {xPos, yPos}) - radius) / radius,1,200);

        newDirection[0] = (-yPos + xPos * (radius - sqrt(xPos*xPos + yPos*yPos)) * ADJUSTMENT_SHARPNESS);
        newDirection[1] = (xPos + yPos * (radius - sqrt(xPos*xPos + yPos*yPos)) * ADJUSTMENT_SHARPNESS);
        float lengthOfVector = get_vector_distance({0.0f, 0.0f}, newDirection);
        newDirection[0] /= lengthOfVector;
        newDirection[1] /= lengthOfVector;
        dotProduct = newDirection[0] * currentDirection[0] + newDirection[1] * currentDirection[1]; //Gives relative closeness to direction (1:same, -1:complete opposites)
       
        turnSpeed = clamp(get_vector_distance(chassis.get_position_vector(), targetDestination) / 12.0f, 0.1f, maxSpeedOfWheel);

        if(arcLength > 0){
            if((currentDirection[1]/currentDirection[0] * newDirection[0] - newDirection[1]) * get_sign(newDirection[0]) > 0  ){ //Adjust to Right
                rightDrive.spin(fwd, turnSpeed * dotProduct, velocity_units::normalized);
                leftDrive.spin(fwd, turnSpeed * (1 - 1/radius*distToPath), velocity_units::normalized);
            }else{ //Adjust to Left
                leftDrive.spin(fwd, turnSpeed, velocity_units::normalized);
                rightDrive.spin(fwd, turnSpeed * (1 - 1/radius*distToPath) * dotProduct, velocity_units::normalized);
            }
        }else{
            if((currentDirection[1]/currentDirection[0] * newDirection[0] - newDirection[1]) * get_sign(newDirection[0]) > 0  ){ //Adjust to Right
                rightDrive.spin(fwd, -1 * turnSpeed * dotProduct, velocity_units::normalized);
                leftDrive.spin(fwd, -1 * turnSpeed * (1 - 1/radius*distToPath), velocity_units::normalized);
            }else{ //Adjust to Left
                leftDrive.spin(fwd, -1 * turnSpeed, velocity_units::normalized);
                rightDrive.spin(fwd, -1 * turnSpeed * (1 - 1/radius*distToPath), velocity_units::normalized);
            }
        }
       
    }
}














