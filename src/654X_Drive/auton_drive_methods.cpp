// #include "vex.h"


// // Movement scheme developed by Thomas Grisamore
// float turningStength = 1; // Used to control speed to prevent slippage


// void left_spiral(float radius, float arcLength, float speed){
//     for(int i = arcLength; i > 0; i--){
//         turn_left_arc(i/arcLength * radius, 1, speed, false);
//     }
// }






// void turn_left_arc(float radius, float arcLength, float speed, bool precisionStop){ //RADIUS IN INCHES
//     if(radius == 0) return;
//     const float ADJUSTMENT_SHARPNESS = 0.3; //How much the code will change velocity when veering off course
   
//     float dotProduct;
//     float lengthOfVector;
//     speed = clamp(speed, 0, (1.0/(1 + (6.0 / radius))));
//     float offset = chassis.get_absolute_heading();
//     //Creates a normal vector pointing straight up
   
//     std::vector<float> currentDirection;
//     currentDirection.push_back(to_normalized_vector(chassis.get_heading()+90)[0]);
//     currentDirection.push_back(to_normalized_vector(chassis.get_heading()+90)[1]);


//     std::vector<float> newDirection; // Normal Vector representing current orientation NEEDS REAL CODE
//     newDirection.push_back(currentDirection[0]);
//     newDirection.push_back(currentDirection[1]);


//     std::vector<float> centerOfCircle;
//     centerOfCircle.push_back(chassis.ideal_x - currentDirection[1]*radius);
//     centerOfCircle.push_back(chassis.ideal_y + currentDirection[0]*radius);
   




//     float targetX = centerOfCircle.at(0) + radius * cos(to_rad(arcLength + offset));
//     float targetY = centerOfCircle.at(1) + radius * sin(to_rad(arcLength + offset));
//     std::vector<float> targetDestination; //Gives Euclidian coordinates of ending location
//     targetDestination.push_back(targetX);
//     targetDestination.push_back(targetY);
//     chassis.ideal_x = targetX;
//     chassis.ideal_y = targetY;
//     targetX -= centerOfCircle.at(0);
//     targetY -= centerOfCircle.at(1);
   
//     //Declaration of variables used below \/
//     float xPos;
//     float yPos;
//     float distToPath; //Distance from robot to the circular path (0 -> on path)
     
//     do{
//         xPos = chassis.get_X_position() - centerOfCircle[0];
//         yPos = chassis.get_Y_position() - centerOfCircle[1];
//         distToPath = clamp(std::abs(get_vector_distance({0.0f, 0.0f}, {xPos, yPos}) - radius),0,100);
//         xPos /= radius;
//         yPos /= radius;
//         currentDirection[0] = to_normalized_vector(chassis.get_heading()+90)[0];
//         currentDirection[1] = to_normalized_vector(chassis.get_heading()+90)[1];


       
//         newDirection[0] = (-yPos + xPos * (1 - sqrt(xPos*xPos + yPos*yPos)) * ADJUSTMENT_SHARPNESS);
//         newDirection[1] = (xPos + yPos * (1 - sqrt(xPos*xPos + yPos*yPos)) *  ADJUSTMENT_SHARPNESS);
//         lengthOfVector = get_vector_distance({0.0f, 0.0f}, newDirection);
//         newDirection[0] /= lengthOfVector;
//         newDirection[1] /= lengthOfVector;
//         dotProduct = newDirection[0] * currentDirection[0] + newDirection[1] * currentDirection[1]; //Gives relative closeness to direction (1:same, -1:complete opposites)
       
//         float turnSpeed = speed;
//         if(precisionStop){
//             turnSpeed = clamp(get_vector_distance(chassis.get_position_vector(), targetDestination) / 30.0f, 0.1f, speed);
//         }


//         // These two lines of code determine which movement scheme to input to the robot
//         int direction = (arcLength > 0) ? 1 : -1;
//         if(currentDirection[0] == 0) currentDirection[0] = 0.001;
//         float crossProduct = currentDirection[0] * newDirection[1] - currentDirection[1] *  newDirection[0];
       
//         float outerRadius = 1.0f + (6.0f / radius)/(distToPath*ADJUSTMENT_SHARPNESS*0.1 + 1);
//         float innerRadius = 1.0f - (6.0f / radius)/(distToPath*ADJUSTMENT_SHARPNESS*0.1 + 1);
//         float adjustedTurnSpeed = direction * turnSpeed;


//         float leftSpeed = 0.0f;
//         float rightSpeed = 0.0f;
       
//         if (crossProduct < 0) {  // Adjust to Right
//             leftSpeed = adjustedTurnSpeed * innerRadius;
//             rightSpeed = adjustedTurnSpeed * outerRadius * dotProduct;
//         } else {  // Adjust to Left
//             leftSpeed = adjustedTurnSpeed * dotProduct * innerRadius;
//             rightSpeed = adjustedTurnSpeed * outerRadius;
//         }
//         Controller.Screen.setCursor(1,1);
//         Controller.Screen.print(currentDirection[0]);
//         // this needs to be a function
//         chassis.right_drive.spin(vex::fwd, rightSpeed, velocity_units::normalized);
//         chassis.left_drive.spin(vex::fwd, leftSpeed, velocity_units::normalized);
//         //Brain.Screen.printAt(0, 50, "%f", xPos);
//     }while (targetX*yPos - targetY*xPos > 0 || get_vector_distance(chassis.get_position_vector(), targetDestination) > 8);
// }




// void turn_right_arc(float radius, float arcLength, float speed, bool precisionStop){ //RADIUS IN INCHES
//     if(radius == 0) return;
//     const int ADJUSTMENT_SHARPNESS = 3; //How much the code will change velocity when veering off course
   
//     float dotProduct;
//     float lengthOfVector;
//     speed = clamp(speed, 0, (1.0/(1 + (6.0 / radius))));
//     float offset = chassis.get_absolute_heading();
//     //Creates a normal vector pointing straight up
   
//     std::vector<float> currentDirection;
//     currentDirection.push_back(to_normalized_vector(chassis.get_heading()+90)[0]);
//     currentDirection.push_back(to_normalized_vector(chassis.get_heading()+90)[1]);


//     std::vector<float> newDirection; // Normal Vector representing current orientation NEEDS REAL CODE
//     newDirection.push_back(currentDirection[0]);
//     newDirection.push_back(currentDirection[1]);


//     std::vector<float> centerOfCircle;
//     centerOfCircle.push_back(chassis.ideal_x - currentDirection[1]*radius);
//     centerOfCircle.push_back(chassis.ideal_y + currentDirection[0]*radius);
   




//     float targetX = centerOfCircle.at(0) - radius * cos(to_rad(arcLength + offset));
//     float targetY = centerOfCircle.at(1) - radius * sin(to_rad(arcLength + offset));
//     std::vector<float> targetDestination; //Gives Euclidian coordinates of ending location
//     targetDestination.push_back(targetX);
//     targetDestination.push_back(targetY);
//     chassis.ideal_x = targetX;
//     chassis.ideal_y = targetY;
//     targetX -= centerOfCircle.at(0);
//     targetY -= centerOfCircle.at(1);
   
//     //Declaration of variables used below \/
//     float xPos;
//     float yPos;
//     float distToPath; //Distance from robot to the circular path (0 -> on path)
     
//     do{
//         xPos = chassis.get_X_position() - centerOfCircle[0];
//         yPos = chassis.get_Y_position() - centerOfCircle[1];
//         distToPath = clamp(std::abs(get_vector_distance({0.0f, 0.0f}, {xPos, yPos}) - radius),0,100);
//         xPos /= radius;
//         yPos /= radius;
//         currentDirection[0] = to_normalized_vector(chassis.get_heading()+90)[0];
//         currentDirection[1] = to_normalized_vector(chassis.get_heading()+90)[1];


       
//         newDirection[0] = (yPos + xPos * (1 - sqrt(xPos*xPos + yPos*yPos)) * ADJUSTMENT_SHARPNESS);
//         newDirection[1] = (-xPos + yPos * (1 - sqrt(xPos*xPos + yPos*yPos)) *  ADJUSTMENT_SHARPNESS);
//         lengthOfVector = get_vector_distance({0.0f, 0.0f}, newDirection);
//         newDirection[0] /= lengthOfVector;
//         newDirection[1] /= lengthOfVector;
//         dotProduct = newDirection[0] * currentDirection[0] + newDirection[1] * currentDirection[1]; //Gives relative closeness to direction (1:same, -1:complete opposites)
       
//         float turnSpeed = speed;
//         if(precisionStop){
//             turnSpeed = clamp(get_vector_distance(chassis.get_position_vector(), targetDestination) / 30.0f, 0.1f, speed);
//         }


//         // These two lines of code determine which movement scheme to input to the robot
//         int direction = (arcLength > 0) ? 1 : -1;
//         if(currentDirection[0] == 0) currentDirection[0] = 0.001;
//         float crossProduct = currentDirection[0] * newDirection[1] - currentDirection[1] *  newDirection[0];
       
//         float outerRadius = 1.0f + (6.0f / radius)/(distToPath*ADJUSTMENT_SHARPNESS*0.1 + 1);
//         float innerRadius = 1.0f - (6.0f / radius)/(distToPath*ADJUSTMENT_SHARPNESS*0.1 + 1);
//         float adjustedTurnSpeed = direction * turnSpeed;


//         float leftSpeed = 0.0f;
//         float rightSpeed = 0.0f;
       
//         if (crossProduct < 0) {  // Adjust to Right
//             leftSpeed = adjustedTurnSpeed * outerRadius;
//             rightSpeed = adjustedTurnSpeed * innerRadius * dotProduct;
//         } else {  // Adjust to Left
//             leftSpeed = adjustedTurnSpeed * dotProduct * outerRadius;
//             rightSpeed = adjustedTurnSpeed * innerRadius;
//         }
//         Controller.Screen.setCursor(1,1);
//         Controller.Screen.print(currentDirection[0]);
//         // this needs to be a function
//         chassis.right_drive.spin(vex::fwd, rightSpeed, velocity_units::normalized);
//         chassis.left_drive.spin(vex::fwd, leftSpeed, velocity_units::normalized);
//         //Brain.Screen.printAt(0, 50, "%f", xPos);
//     }while (targetX*yPos - targetY*xPos < 0 || get_vector_distance(chassis.get_position_vector(), targetDestination) > 8);
// }




// void go_smart_straight(float distance, float speed, bool precisionStop){ //RADIUS IN INCHES
//     if(distance == 0) return;
//     const float ADJUSTMENT_SHARPNESS = 0.01; //How much the code will change velocity when veering off course
   
//     float dotProduct;
//     float lengthOfVector;
//     float offset = chassis.get_absolute_heading();
//     //Creates a normal vector pointing straight up
   
//     std::vector<float> currentDirection;
//     currentDirection.push_back(to_normalized_vector(chassis.get_heading()+90)[0]);
//     currentDirection.push_back(to_normalized_vector(chassis.get_heading()+90)[1]);


//     std::vector<float> newDirection; // Normal Vector representing current orientation NEEDS REAL CODE
//     newDirection.push_back(currentDirection[0]);
//     newDirection.push_back(currentDirection[1]);


//     float startX = chassis.ideal_x;
//     float startY = chassis.ideal_y;
   
//     float targetX = startX + currentDirection[0]*distance;
//     float targetY = startY + currentDirection[1]*distance;
//     std::vector<float> targetDestination; //Gives Euclidian coordinates of ending location
//     targetDestination.push_back(targetX);
//     targetDestination.push_back(targetY);
//     chassis.ideal_x = targetX;
//     chassis.ideal_y = targetY;
   
//     //Declaration of variables used below \/
//     float xPos = 0;
//     float yPos = 0;
//     float distToPath; //Distance from robot to the circular path (0 -> on path)
     
//     while (yPos < distance && get_vector_distance(chassis.get_position_vector(), targetDestination) > 2) {
//         xPos = (chassis.get_X_position() - startX) * cos(to_rad(chassis.get_heading() - offset)) - (chassis.get_Y_position() - startY) * sin(to_rad(chassis.get_heading() - offset));
//         yPos = (chassis.get_Y_position() - startY) * sin(to_rad(chassis.get_heading() - offset)) + (chassis.get_X_position() - startX) * cos(to_rad(chassis.get_heading() - offset));
//         distToPath = clamp(std::abs(get_vector_distance({0.0f, 0.0f}, {xPos, yPos}) - distance),0,100);
//         currentDirection[0] = to_normalized_vector(chassis.get_heading()+90)[0];
//         currentDirection[1] = to_normalized_vector(chassis.get_heading()+90)[1];


//         newDirection[0] = -std::abs(xPos)*xPos*ADJUSTMENT_SHARPNESS;
//         newDirection[1] = 1;
//         lengthOfVector = get_vector_distance({0.0f, 0.0f}, newDirection);
//         newDirection[0] /= lengthOfVector;
//         newDirection[1] /= lengthOfVector;
//         dotProduct = newDirection[0] * currentDirection[0] + newDirection[1] * currentDirection[1]; //Gives relative closeness to direction (1:same, -1:complete opposites)
       
//         float turnSpeed = speed;
//         if(precisionStop){
//             turnSpeed = clamp(get_vector_distance(chassis.get_position_vector(), targetDestination) / 10.0f, 0.1f, speed);
//         }


//         // These two lines of code determine which movement scheme to input to the robot
//         int direction = (distance > 0) ? 1 : -1;
//         if(currentDirection[0] == 0) currentDirection[0] = 0.001;
//         float crossProduct = currentDirection[0] * newDirection[1] - currentDirection[1] *  newDirection[0];
       
//         float adjustedTurnSpeed = direction * turnSpeed;


//         float leftSpeed = 0.0f;
//         float rightSpeed = 0.0f;
       
//         if (crossProduct < 0) {  // Adjust to Right
//             leftSpeed = adjustedTurnSpeed;
//             rightSpeed = adjustedTurnSpeed  * dotProduct;
//         } else {  // Adjust to Left
//             leftSpeed = adjustedTurnSpeed * dotProduct;
//             rightSpeed = adjustedTurnSpeed;
//         }
//         Controller.Screen.setCursor(1,1);
//         Controller.Screen.print(dotProduct);
//         // this needs to be a function
//         chassis.right_drive.spin(vex::fwd, rightSpeed, velocity_units::normalized);
//         chassis.left_drive.spin(vex::fwd, leftSpeed, velocity_units::normalized);
//         Brain.Screen.printAt(0, 50, "%f", newDirection[0]);
//     }
//     if(precisionStop){
//         chassis.right_drive.stop();
//         chassis.left_drive.stop();
//     }
// }


// void 

// void standardized_vector_movement(std::vector<float> origin, float speed, float adjustment_sharpness, float* curvePattern[]){
   
//     float dotProduct;
//     float lengthOfVector;
//     float offset = chassis.get_heading();
   
//     //Creates a normal vector pointing straight up
   
//     std::vector<float> currentDirection;
//     currentDirection.push_back(to_normalized_vector(chassis.get_heading()+90)[0]);
//     currentDirection.push_back(to_normalized_vector(chassis.get_heading()+90)[1]);


//     std::vector<float> newDirection; // Normal Vector representing current orientation NEEDS REAL CODE
//     newDirection.push_back(currentDirection[0]);
//     newDirection.push_back(currentDirection[1]);
   


   
//     //Declaration of variables used below \/
   
//     float xPos;
//     float yPos;
//     float leftSpeed;
//     float rightSpeed;
//     float COMSpeed; //Center of mass speed
//     float curveSpeed;


//     while(get_vector_distance(chassis.get_position_vector(), {chassis.ideal_x, chassis.ideal_y}) < 1) {
//         xPos = (chassis.get_X_position() - origin[0]) * cos(to_rad(chassis.get_heading() - offset)) - (chassis.get_Y_position() - origin[1]) * sin(to_rad(chassis.get_heading() - offset));
//         yPos = (chassis.get_Y_position() - origin[1]) * sin(to_rad(chassis.get_heading() - offset)) + (chassis.get_X_position() - origin[0]) * cos(to_rad(chassis.get_heading() - offset));
//         currentDirection[0] = to_normalized_vector(chassis.get_heading()+90)[0];
//         currentDirection[1] = to_normalized_vector(chassis.get_heading()+90)[1];




//         newDirection = bezier(curvePattern);
//         lengthOfVector = get_vector_distance({0.0f, 0.0f}, newDirection);
//         newDirection[0] /= lengthOfVector;
//         newDirection[1] /= lengthOfVector;
//         dotProduct = newDirection[0] * currentDirection[0] + newDirection[1] * currentDirection[1]; //Gives relative closeness to direction (1:same, -1:complete opposites)
       
//         // These two lines of code determine which movement scheme to input to the robot
//         //if(currentDirection[0] == 0) currentDirection[0] = 0.001;
//         float crossProduct = currentDirection[0] * newDirection[1] - currentDirection[1] *  newDirection[0];
//         if (crossProduct < 0) {  // Adjust to Right
//             leftSpeed = speed;
//             rightSpeed = speed  * dotProduct;
//         } else {  // Adjust to Left
//             leftSpeed = speed * dotProduct;
//             rightSpeed = speed;
//         }
//         COMSpeed = (leftSpeed + rightSpeed) / 2;
//         curveSpeed = sqrt(turningStength * (1/(1-dotProduct)));
//         if(curveSpeed < COMSpeed){
//             leftSpeed *=  curveSpeed / COMSpeed;
//             rightSpeed *= curveSpeed / COMSpeed;
//         }
//         Controller.Screen.setCursor(1,1);
//         Controller.Screen.print(xPos);
//         // this needs to be a function
//         chassis.right_drive.spin(vex::fwd, rightSpeed, velocity_units::normalized);
//         chassis.left_drive.spin(vex::fwd, leftSpeed, velocity_units::normalized);
   
//     }
// }


// void optimization(float dist, int mode){
//     switch(mode){
//         case 1:
//         case 2:
//         default:


//     }
// }


// std::vector<float> CCW(float x, float y, float adjShrp, float depth, float speed){ //Depth cannot exceed distance to the endpoint
//     float startX = x, startY = y;
//     std::vector<float> newDirection(2);
//     float const GRANULARITY = 2 / speed; //Amount of iterations per inch
//     for(int i = 0; i < depth * GRANULARITY; i++){
//         newDirection[0] = (-y + x * (1 - sqrt(x*x + y*y)) * adjShrp);
//         newDirection[1] = (x + y * (1 - sqrt(x*x + y*y)) *  adjShrp);
//         to_normalized_vector(newDirection);
//         x += newDirection[0] / GRANULARITY;
//         y += newDirection[1] / GRANULARITY;
//     }
//     newDirection[0] = x - startX;
//     newDirection[1] = y - startY;
//     to_normalized_vector(newDirection);
//     return newDirection;
// }


// void leftArc(float degrees, float radius, float speed, int mode = 0){
//     std::vector<float> centerOfCircle;
//     float offset = chassis.get_heading();
//     centerOfCircle.push_back(chassis.ideal_x - to_normalized_vector(chassis.get_heading()+90)[1]*radius);
//     centerOfCircle.push_back(chassis.ideal_y + to_normalized_vector(chassis.get_heading()+90)[0]*radius);
//     chassis.ideal_x = centerOfCircle.at(0) + radius * cos(to_rad(degrees + offset));
//     chassis.ideal_y = centerOfCircle.at(1) + radius * sin(to_rad(degrees + offset));
//     standardized_vector_movement(centerOfCircle, speed, CCW, 0, 10);
// }


// //3{(1−t)2(P1−P0)+2t(1−t)(P2−P1)+t2(P3−P2)}


// std::vector<float> bezier(float* points[]){
//     const float current_scalar = 1, lead_scalar = 1;
//     const float header_dist = 5;
//     const float header_stepper_size = 0.05;
//     int num_of_curves = sizeof(points)/4;
//     static float time = 0;
//     float t = time;
//     int index = t;
//     float increment = 0.1;
//     float pastDist = 10000; //Big number
//     float dist = 0;
//     float carrot_dist;
//     float dx_dt;
//     float dy_dt;
//     float px, py, px2, py2;
//     float vx, vy;
//     std::vector<float> correction, 
//     std::vector<float> current, lead, output;


//     for(int i = 0; i < 20 && increment >= 0.01; i++){
//         index = t;
//         t -= index;
//         px = pow(1-t,3)*points[index*4][0] + 3*pow(1-t,2)*t*points[index*4+1][0] + 3*(1-t)*t*t*points[index*4+2][0] + t*t*t*points[index*4+3][0];
//         py = pow(1-t,3)*points[index*4][1] + 3*pow(1-t,2)*t*points[index*4+1][1] + 3*(1-t)*t*t*points[index*4+2][1] + t*t*t*points[index*4+3][1];


//         dist = pow(pow(px-chassis.get_X_position(),2) + pow(py-chassis.get_Y_position(),2),0.5);


//         if(pastDist<=dist){
//             t-=increment;
//             increment/=10;
//         }
//         t+=increment;
//         pastDist = dist;
//     }
//     t+=increment*9;


   


//     //This part gets the vector pointing directly to the path
//     vx -=  px - chassis.get_X_position();
//     vy -=  py - chassis.get_Y_position();
//     correction.push(vx);
//     correction.push(vy);
//     //This part gets the vector tangent to the path of where the robot should be
//     dx_dt = 3*(pow(1-t,2)*(points[index*4 + 1][0] - points[index*4][0])) + 2*t*(1-t)*(points[index*4+2][0]-points[index*4 + 1][0]) + t*t*(points[index*4+2][0]-points[index*4 + 1][0]);
//     dy_dt = 3*(pow(1-t,2)*(points[index*4 + 1][1] - points[index*4][1])) + 2*t*(1-t)*(points[index*4+2][1]-points[index*4 + 1][1]) + t*t*(points[index*4+2][1]-points[index*4 + 1][1]);
//     current.push(dx_dt);
//     current.push(dy_dt);
//     //This part gets the vector tangent to the path of where the robot will later be (distance determined by header_dist)
//     carrot_dist = sqrt(pow(vx,2)+pow(vy,2));
//     for(int i = 0; i < 1/header_stepper_size; i++){ //   1/998001 ---> 1 is the total interval it will search through before quitting
//         t += header_stepper_size;//How finely it steps through the function
//         if(carrot_dist > header_dist || t > num_of_curves) break;  
//         index = t;
//         px2 = pow(1-t,3)*points[index*4][0] + 3*pow(1-t,2)*t*points[index*4+1][0] + 3*(1-t)*t*t*points[index*4+2][0] + t*t*t*points[index*4+3][0];
//         py2 = pow(1-t,3)*points[index*4][1] + 3*pow(1-t,2)*t*points[index*4+1][1] + 3*(1-t)*t*t*points[index*4+2][1] + t*t*t*points[index*4+3][1];
//         carrot_dist += sqrt(pow(px - px2, 2)+pow(py-py2, 2));
//         px = px2;
//         py = py2;
//     }
//     dx_dt = 3*(pow(1-t,2)*(points[index*4 + 1][0] - points[index*4][0])) + 2*t*(1-t)*(points[index*4+2][0]-points[index*4 + 1][0]) + t*t*(points[index*4+2][0]-points[index*4 + 1][0]);
//     dy_dt = 3*(pow(1-t,2)*(points[index*4 + 1][1] - points[index*4][1])) + 2*t*(1-t)*(points[index*4+2][1]-points[index*4 + 1][1]) + t*t*(points[index*4+2][1]-points[index*4 + 1][1]);
//     lead.push(dx_dt);
//     lead.push(dy_dt);


//     current = to_normalized_vector(current);
//     lead = to_normalized_vector(lead);


//     output.push(correction[0] + current[0]*current_scalar + lead[0]*lead_scalar);
//     output.push(correction[1] + current[1]*current_scalar + lead[1]*lead_scalar);
//     output = to_normalized_vector(output);


//     if(sqrt(pow(correction[0],2)+pow(correction[1],2)) > 3){ //When slips too much, make slip less (slower) | Increase increment to make it more sensitive
//         turningStength -= 0.0002; /*NOTE: Adjust based on the frequency this program runs at */
//     }else if(sqrt(pow(correction[0],2)+pow(correction[1],2)) < 1){ //When slips too little, make faster (more slippage) | Increase increment to make it more sensitive  
//         turningStength += 0.0002;
//     }


//     return output;


//     //Alright i need to draw a line from thje robot to the point it thinks it should be at then use that in conjunction with the tangent vector, using some scalar to determine the weight of each. After that, I need to make a tracer that goes ahead and also averages with the other vector


// }

// std::vector<float[]> curve

// /*
// set t to little less than last run through
// iterate through t until distance function (derivative) between robot
// position and curve goes from (-) -> (+)
// once happens, decrease increment and run again (subtract value at the
// start of loops so that t(used) is greater than t (actual))
// repeat until increment is within WHAT I DEEM an acceptance margin of error
// Store t as position along the curve
// Find tangent vector at t
// find the distance from the point to the tangent of the curve at that value
// of t
// --> std::abs(m * xp + -1 * yp + y - m *x) / std::sqrt(m * m + 1)
// assign vector value
// go up by some amount t and take the vector along the curve


// Find the average of these two and return the value (use value to determine
// weight of each component)










// useless
// dx_dt =
// 3(pow(1-t,2)*(points[index*4 + 1][0] - points[index*4][0]) +
// 2*t*(1-t)*(points[index*4+2][0]-points[index*4 + 1][0]) +
// t*t*(points[index*4+2][0]-points[index*4 + 1][0];
// dy_dt =
// 3(pow(1-t,2)*(points[index*4 + 1][1] - points[index*4][1]) +
// 2*t*(1-t)*(points[index*4+2][1]-points[index*4 + 1][1]) +
// t*t*(points[index*4+2][1]-points[index*4 + 1][1];
// float deriv_of_dist = 0.5*pow(pow(chassis.get_X_position() - px,2) + pow(chassis.get_Y_position() - py,2),- 0.5)
// * (2*(chassis.get_X_position() - px)*-dx_dt+2*(chassis.get_Y_position() - py)*-dy_dt)
// */


