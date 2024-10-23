#include "654-Template/motor_chain.h"
#include "654-Template/manual_drive.h"
#include "654-Template/auton_drive.h"
#include "util.h"
#include "vex.h"

#include <vector>
#include <cmath>
#include <algorithm>

using namespace vex;


//notes
// for readability please do more variable assigns
// the more you split the math into more lines/functions the better i can understand/test
// lines i put //fix i cant read



int get_sign(int num) {
    return (num == 0) ? 1 : num / abs(num);
}

void turnAlongCircleLeft(float radius, float arcLength, float speed){ //RADIUS IN INCHES
    if(radius == 0) return;
    const int ADJUSTMENT_SHARPNESS = 10; //How much the code will change velocity when veering off course
    
    float dotProduct;
    float lengthOfVector;
    speed = clamp(speed, 0, (1.0/(1 + (6.0 / radius))));
    float offset = chassis.get_absolute_heading();
    //Creates a normal vector pointing straight up
    
    std::vector<float> currentDirection;
    currentDirection.push_back(to_normalized_vector(chassis.get_heading()+90)[0]);
    currentDirection.push_back(to_normalized_vector(chassis.get_heading()+90)[1]);
    

    std::vector<float> newDirection; // Normal Vector representing current orientation NEEDS REAL CODE
    newDirection.push_back(currentDirection[0]);
    newDirection.push_back(currentDirection[1]);

    std::vector<float> centerOfCircle;
    centerOfCircle.push_back(chassis.get_X_position() - currentDirection[1]*radius);
    centerOfCircle.push_back(chassis.get_Y_position() + currentDirection[0]*radius);
   


    float targetX = centerOfCircle.at(0) + radius * cos(to_rad(arcLength + offset)); 
    float targetY = centerOfCircle.at(1) + radius * sin(to_rad(arcLength + offset));
    std::vector<float> targetDestination; //Gives Euclidian coordinates of ending location
    targetDestination.push_back(targetX);
    targetDestination.push_back(targetY);
    
    //Declaration of variables used below \/
    float xPos;
    float yPos;
    float distToPath; //Distance from robot to the circular path (0 -> on path)
    float distToEnd;
     
    while(false || get_vector_distance(chassis.get_position_vector(), targetDestination) > 2){
        xPos = chassis.get_X_position() - centerOfCircle[0];
        yPos = chassis.get_Y_position() - centerOfCircle[1]; 
        distToPath = clamp(std::abs(get_vector_distance({0.0f, 0.0f}, {xPos, yPos}) - radius),0,100);
        xPos /= radius;
        yPos /= radius;
        currentDirection[0] = to_normalized_vector(chassis.get_heading()+90)[0];
        currentDirection[1] = to_normalized_vector(chassis.get_heading()+90)[1];

        
        newDirection[0] = (-yPos + xPos * (1 - sqrt(xPos*xPos + yPos*yPos)) * ADJUSTMENT_SHARPNESS);
        newDirection[1] = (xPos + yPos * (1 - sqrt(xPos*xPos + yPos*yPos)) *  ADJUSTMENT_SHARPNESS);
        lengthOfVector = get_vector_distance({0.0f, 0.0f}, newDirection);
        newDirection[0] /= lengthOfVector;
        newDirection[1] /= lengthOfVector;
        dotProduct = newDirection[0] * currentDirection[0] + newDirection[1] * currentDirection[1]; //Gives relative closeness to direction (1:same, -1:complete opposites)
        
        float turnSpeed = clamp(get_vector_distance(chassis.get_position_vector(), targetDestination) / 36.0f, 0.1f, speed);

        // These two lines of code determine which movement scheme to input to the robot
        int direction = (arcLength > 0) ? 1 : -1;
        if(currentDirection[0] == 0) currentDirection[0] = 0.001;
        float crossProduct = currentDirection[0] * newDirection[1] - currentDirection[1] *  newDirection[0];
       
        float outerRadius = 1.0f + (6.0f / radius)/(distToPath*ADJUSTMENT_SHARPNESS*0.1 + 1);
        float innerRadius = 1.0f - (6.0f / radius)/(distToPath*ADJUSTMENT_SHARPNESS*0.1 + 1);
        float adjustedTurnSpeed = direction * turnSpeed;

        float leftSpeed = 0.0f;
        float rightSpeed = 0.0f;
        
        if (crossProduct < 0) {  // Adjust to Right
            leftSpeed = adjustedTurnSpeed * innerRadius;
            rightSpeed = adjustedTurnSpeed * outerRadius * dotProduct;
        } else {  // Adjust to Left
            leftSpeed = adjustedTurnSpeed * dotProduct * innerRadius;
            rightSpeed = adjustedTurnSpeed * outerRadius;
        }
        Controller.Screen.setCursor(1,1);
        Controller.Screen.print(currentDirection[0]);
        // this needs to be a function
        rightDrive.spin(fwd, rightSpeed, velocity_units::normalized);
        leftDrive.spin(fwd, leftSpeed, velocity_units::normalized);
        //Brain.Screen.printAt(0, 50, "%f", xPos);
    }
}













