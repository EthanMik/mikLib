#include "vex.h"

// Movement scheme developed by Thomas Grisamore

void turn_left_arc(float radius, float arcLength, float speed, bool precisionStop){ //RADIUS IN INCHES
    if(radius == 0) return;
    const float ADJUSTMENT_SHARPNESS = 0.3; //How much the code will change velocity when veering off course
   
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
    centerOfCircle.push_back(chassis.ideal_x - currentDirection[1]*radius);
    centerOfCircle.push_back(chassis.ideal_y + currentDirection[0]*radius);
   


    float targetX = centerOfCircle.at(0) + radius * cos(to_rad(arcLength + offset));
    float targetY = centerOfCircle.at(1) + radius * sin(to_rad(arcLength + offset));
    std::vector<float> targetDestination; //Gives Euclidian coordinates of ending location
    targetDestination.push_back(targetX);
    targetDestination.push_back(targetY);
    chassis.ideal_x = targetX;
    chassis.ideal_y = targetY;
    targetX -= centerOfCircle.at(0);
    targetY -= centerOfCircle.at(1);
   
    //Declaration of variables used below \/
    float xPos;
    float yPos;
    float distToPath; //Distance from robot to the circular path (0 -> on path)
     
    do{
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
       
        float turnSpeed = speed;
        if(precisionStop){
            turnSpeed = clamp(get_vector_distance(chassis.get_position_vector(), targetDestination) / 30.0f, 0.1f, speed);
        }

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
        chassis.right_drive.spin(vex::fwd, rightSpeed, velocity_units::normalized);
        chassis.left_drive.spin(vex::fwd, leftSpeed, velocity_units::normalized);
        //Brain.Screen.printAt(0, 50, "%f", xPos);
    }while (targetX*yPos - targetY*xPos > 0 || get_vector_distance(chassis.get_position_vector(), targetDestination) > 8);
}


void turn_right_arc(float radius, float arcLength, float speed, bool precisionStop){ //RADIUS IN INCHES
    if(radius == 0) return;
    const int ADJUSTMENT_SHARPNESS = 3; //How much the code will change velocity when veering off course
   
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
    centerOfCircle.push_back(chassis.ideal_x - currentDirection[1]*radius);
    centerOfCircle.push_back(chassis.ideal_y + currentDirection[0]*radius);
   


    float targetX = centerOfCircle.at(0) - radius * cos(to_rad(arcLength + offset));
    float targetY = centerOfCircle.at(1) - radius * sin(to_rad(arcLength + offset));
    std::vector<float> targetDestination; //Gives Euclidian coordinates of ending location
    targetDestination.push_back(targetX);
    targetDestination.push_back(targetY);
    chassis.ideal_x = targetX;
    chassis.ideal_y = targetY;
    targetX -= centerOfCircle.at(0);
    targetY -= centerOfCircle.at(1);
   
    //Declaration of variables used below \/
    float xPos;
    float yPos;
    float distToPath; //Distance from robot to the circular path (0 -> on path)
     
    do{
        xPos = chassis.get_X_position() - centerOfCircle[0];
        yPos = chassis.get_Y_position() - centerOfCircle[1];
        distToPath = clamp(std::abs(get_vector_distance({0.0f, 0.0f}, {xPos, yPos}) - radius),0,100);
        xPos /= radius;
        yPos /= radius;
        currentDirection[0] = to_normalized_vector(chassis.get_heading()+90)[0];
        currentDirection[1] = to_normalized_vector(chassis.get_heading()+90)[1];

       
        newDirection[0] = (yPos + xPos * (1 - sqrt(xPos*xPos + yPos*yPos)) * ADJUSTMENT_SHARPNESS);
        newDirection[1] = (-xPos + yPos * (1 - sqrt(xPos*xPos + yPos*yPos)) *  ADJUSTMENT_SHARPNESS);
        lengthOfVector = get_vector_distance({0.0f, 0.0f}, newDirection);
        newDirection[0] /= lengthOfVector;
        newDirection[1] /= lengthOfVector;
        dotProduct = newDirection[0] * currentDirection[0] + newDirection[1] * currentDirection[1]; //Gives relative closeness to direction (1:same, -1:complete opposites)
       
        float turnSpeed = speed;
        if(precisionStop){
            turnSpeed = clamp(get_vector_distance(chassis.get_position_vector(), targetDestination) / 30.0f, 0.1f, speed);
        }

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
            leftSpeed = adjustedTurnSpeed * outerRadius;
            rightSpeed = adjustedTurnSpeed * innerRadius * dotProduct;
        } else {  // Adjust to Left
            leftSpeed = adjustedTurnSpeed * dotProduct * outerRadius;
            rightSpeed = adjustedTurnSpeed * innerRadius;
        }
        Controller.Screen.setCursor(1,1);
        Controller.Screen.print(currentDirection[0]);
        // this needs to be a function
        chassis.right_drive.spin(vex::fwd, rightSpeed, velocity_units::normalized);
        chassis.left_drive.spin(vex::fwd, leftSpeed, velocity_units::normalized);
        //Brain.Screen.printAt(0, 50, "%f", xPos);
    }while (targetX*yPos - targetY*xPos < 0 || get_vector_distance(chassis.get_position_vector(), targetDestination) > 8);
}


void go_smart_straight(float distance, float speed, bool precisionStop){ //RADIUS IN INCHES
    if(distance == 0) return;
    const float ADJUSTMENT_SHARPNESS = 0.01; //How much the code will change velocity when veering off course
   
    float dotProduct;
    float lengthOfVector;
    float offset = chassis.get_absolute_heading();
    //Creates a normal vector pointing straight up
   
    std::vector<float> currentDirection;
    currentDirection.push_back(to_normalized_vector(chassis.get_heading()+90)[0]);
    currentDirection.push_back(to_normalized_vector(chassis.get_heading()+90)[1]);

    std::vector<float> newDirection; // Normal Vector representing current orientation NEEDS REAL CODE
    newDirection.push_back(currentDirection[0]);
    newDirection.push_back(currentDirection[1]);

    float startX = chassis.ideal_x;
    float startY = chassis.ideal_y;
   
    float targetX = startX + currentDirection[0]*distance;
    float targetY = startY + currentDirection[1]*distance;
    std::vector<float> targetDestination; //Gives Euclidian coordinates of ending location
    targetDestination.push_back(targetX);
    targetDestination.push_back(targetY);
    chassis.ideal_x = targetX;
    chassis.ideal_y = targetY;
   
    //Declaration of variables used below \/
    float xPos = 0;
    float yPos = 0;
    float distToPath; //Distance from robot to the circular path (0 -> on path)
     
    while (yPos < distance && get_vector_distance(chassis.get_position_vector(), targetDestination) > 2) {
        xPos = (chassis.get_X_position() - startX) * cos(to_rad(chassis.get_heading() - offset)) - (chassis.get_Y_position() - startY) * sin(to_rad(chassis.get_heading() - offset));
        yPos = (chassis.get_Y_position() - startY) * sin(to_rad(chassis.get_heading() - offset)) + (chassis.get_X_position() - startX) * cos(to_rad(chassis.get_heading() - offset));
        distToPath = clamp(std::abs(get_vector_distance({0.0f, 0.0f}, {xPos, yPos}) - distance),0,100);
        currentDirection[0] = to_normalized_vector(chassis.get_heading()+90)[0];
        currentDirection[1] = to_normalized_vector(chassis.get_heading()+90)[1];

        newDirection[0] = -std::abs(xPos)*xPos*ADJUSTMENT_SHARPNESS;
        newDirection[1] = 1;
        lengthOfVector = get_vector_distance({0.0f, 0.0f}, newDirection);
        newDirection[0] /= lengthOfVector;
        newDirection[1] /= lengthOfVector;
        dotProduct = newDirection[0] * currentDirection[0] + newDirection[1] * currentDirection[1]; //Gives relative closeness to direction (1:same, -1:complete opposites)
       
        float turnSpeed = speed;
        if(precisionStop){
            turnSpeed = clamp(get_vector_distance(chassis.get_position_vector(), targetDestination) / 10.0f, 0.1f, speed);
        } 

        // These two lines of code determine which movement scheme to input to the robot
        int direction = (distance > 0) ? 1 : -1;
        if(currentDirection[0] == 0) currentDirection[0] = 0.001;
        float crossProduct = currentDirection[0] * newDirection[1] - currentDirection[1] *  newDirection[0];
       
        float adjustedTurnSpeed = direction * turnSpeed;

        float leftSpeed = 0.0f;
        float rightSpeed = 0.0f;
       
        if (crossProduct < 0) {  // Adjust to Right
            leftSpeed = adjustedTurnSpeed;
            rightSpeed = adjustedTurnSpeed  * dotProduct;
        } else {  // Adjust to Left
            leftSpeed = adjustedTurnSpeed * dotProduct;
            rightSpeed = adjustedTurnSpeed;
        }
        Controller.Screen.setCursor(1,1);
        Controller.Screen.print(dotProduct);
        // this needs to be a function
        chassis.right_drive.spin(vex::fwd, rightSpeed, velocity_units::normalized);
        chassis.left_drive.spin(vex::fwd, leftSpeed, velocity_units::normalized);
        Brain.Screen.printAt(0, 50, "%f", newDirection[0]);
    }
    if(precisionStop){
        chassis.right_drive.stop();
        chassis.left_drive.stop();
    }
}
