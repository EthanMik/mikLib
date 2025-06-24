// #include "vex.h"

// using namespace vex;

// std::vector<std::pair<float, float>> curveNumeroUno = {
//     {-21.79f, -51.93f}, // (-55.3,  -131.9)
//     {-30.71f, -42.13f}, // (-78,    -107)
//     {-38.98f, -33.86f}, // (-99,    -86)
//     {-49.76f, -21.83f}, // (-126.35, -55.428)
//     {-49.76f, -21.83f}, // (-126.35, -55.428)
//     {-62.20f,  -8.27f}, // (-158,   -21)
//     {-35.04f,   6.69f}, // (-89,    17)
//     {-23.23f,  17.46f}, // (-59,    44.34)
//     {-23.23f,  17.46f}, // (-59,    44.34)
//     {-11.42f,  27.56f}, // (-29,    70)
//     { 29.05f, -19.64f}, // (73.8,   -49.9)
//     { 21.81f, -41.34f}, // (55.4,   -105)
//     { 21.81f, -41.34f}, // (55.4,   -105)
//     { 14.57f, -63.00f}, // (37,     -160)
//     {-22.52f, -65.67f}, // (-57.2,  -166.8)
//     {-21.79f, -51.93f},  // (-55.3,  -131.9)
//     {-21.79f, -51.93f}, // (-55.3,  -131.9)
//     {-30.71f, -42.13f}, // (-78,    -107)
//     {-38.98f, -33.86f}, // (-99,    -86)
//     {-49.76f, -21.83f} // (-126.35, -55.428)
// };

// std::vector<std::pair<float, float>> curveNumeroDos = {
//    {-23.5,-23.5},
//    {-14,-36},
//    {-5,-44},
//    {24,-47}
   
// };

// float current_scalar = 3;
// float lead_scalar = 3;
// float curve_time = 0;

// // Movement scheme developed by Thomas Grisamore
// float turningStength = 1000; // Used to control speed to prevent slippage. Functions as a coefficient


// void standardized_vector_movement(float speed, const std::vector<std::pair<float, float>> &curvePattern){  //Moves a robot along a bezier curve with specific features to minimize slippage and maximize customizability
//     float dotProduct;
//     chassis.set_coordinates(curvePattern[0].first, curvePattern[0].second, chassis.get_absolute_heading());
//     //Line above MUST be removed and replaced with a better system - Ex. Position declared at the start of main
//     //Creates a normal vector pointing straight forward
   
//     std::vector<float> currentDirection = to_normalized_vector(chassis.get_heading()+90);// Normal Vector representing current orientation
//     std::vector<float> newDirection = currentDirection;//Normal Vector representing intended direction. Determined later with functions
   
//     chassis.ideal_x = curvePattern[curvePattern.size()-1].first; //Sets end x-coordinate for robot
//     chassis.ideal_y = curvePattern[curvePattern.size()-1].second; //Sets end y-coordinate for robot
      
//     //Declaration of variables used below \/
//     float leftSpeed; //Left drive chain speed
//     float rightSpeed; //Right drive chain speed
//     float COMSpeed; //Center of mass speed
//     float curveSpeed; //Max speed of robot when on some specified curve

    
//     while(curve_time < curvePattern.size()/4){ //While robot sufficiently far away from the end, keep running the function
//         currentDirection = to_normalized_vector(chassis.get_heading()+90); //Obtains degree heading of robot
        
//         bezier(newDirection, curvePattern); //Returns vector pointing robot in the direction it will turn
        
//         dotProduct = newDirection[0] * currentDirection[0] + newDirection[1] * currentDirection[1]; //Gives relative closeness of currentDirection to newDirection (1:same, -1:complete opposites)
//         float crossProduct = currentDirection[0] * newDirection[1] - currentDirection[1] *  newDirection[0]; //Cross product used to determine turning direction | (-) = Clockwise, (+) = Counterclockwise
//         Controller.Screen.setCursor(3,1);
//         Controller.Screen.print(dotProduct);
//         if (crossProduct < 0) {  // Adjust to Right
//             leftSpeed = speed;
//             rightSpeed = speed  * dotProduct; //Slows inner wheel down to cause turning
//         } else {  // Adjust to Left
//             leftSpeed = speed * dotProduct; //Slows inner wheel down to cause turning
//             rightSpeed = speed;
//         }
//         COMSpeed = (leftSpeed + rightSpeed) / 2 + 0.01; //Obtains the speed of the center of mass. Used to determine the velocity when calculating the max curve speed without slipping
//         curveSpeed = sqrt(turningStength * (1/(1.01-dotProduct))); //Determines max speed without slippage for a given turn. Equation derived from Kinetic Energy with turningStrength proportional to friction coefficient 
//         if(curveSpeed < COMSpeed){ //If robot too fast for curve, slow down robot
//             leftSpeed *=  curveSpeed / COMSpeed;
//             rightSpeed *= curveSpeed / COMSpeed;
//         }
        
//         // Sets robot's speed
//         chassis.right_drive.spin(vex::fwd, rightSpeed, velocity_units::normalized);
//         chassis.left_drive.spin(vex::fwd, leftSpeed, velocity_units::normalized);

   
//     }
//     Controller.Screen.setCursor(1,1);
//     //Controller.Screen.print("Code finished, hopefully it worked");
//     chassis.stop_drive(vex::brake);
//     return;
// }

// void bezier(std::vector<float>& newDirection, const std::vector<std::pair<float, float>> &points){
//     const float lead_scalar = 3; //Values used to determine which components of the final vector are most heavily weighed
//     const float header_dist = 15; //How many inches ahead the lead vector is taken from
//     const float header_stepper_size = 0.01; //Increment for t when used in finding the lead vector
//     float num_of_curves = sizeof(points)/4; //Where along the curve the robot is currently. Stored between runs of function. NOT ACTUALLY RELATED TO REAL-LIFE TIME, more like a third variable like "z" or "i" 
//     float t = std::max(0.0, curve_time - 0.3); //Form of "time" used in calculation. Often shortened to a float between 0-1 to get position along a bezier curve
//     int index = 0; //Marker of which bezier curve is being used 
//     float increment = 0.1; 
//     double pastDist = 10000; //Big number
//     double dist = 0;
//     float carrot_dist;
//     float dx_dt;
//     float dy_dt;
//     float px, py, px2, py2;
//     float vx, vy;
//     float storeVariable;
//     float radius;
//     float innerSpeed;
//     float angleShift;
//     std::vector<float> correction;
//     std::vector<float> output;
//     std::vector<float> lead;
//     std::vector<float> current;
//     std::vector<float> onPath;

//     for(int i = 0; i < 200 && increment >= 0.0001; i++){
//         t += index; //Fixes problem
//         index = std::min(t, (num_of_curves + 1)); //Gives integer of which curve to follow
//         t -= index;
//         px = pow(1-t,3)*points[index*4].first + 3*pow(1-t,2)*t*points[index*4+1].first + 3*(1-t)*t*t*points[index*4+2].first + t*t*t*points[index*4+3].first;
//         py = pow(1-t,3)*points[index*4].second + 3*pow(1-t,2)*t*points[index*4+1].second + 3*(1-t)*t*t*points[index*4+2].second + t*t*t*points[index*4+3].second;

//         dist = pow(pow(px-chassis.get_X_position(),2) + pow(py-chassis.get_Y_position(),2),0.5);

//         if(pastDist<=dist){
//             t-=increment;
//             increment/=10;
//             pastDist = 1000;
//         }
//         t+=increment;
//         pastDist = dist;
//     }
//     t+=increment*9;
//     curve_time = t + index;
//     storeVariable = index;

//     //This part gets the vector pointing directly to the path
//     vx =  px - chassis.get_X_position();
//     vy =  py - chassis.get_Y_position();
//     correction.push_back(vx);
//     correction.push_back(vy);
//     //This part gets the vector tangent to the path of where the robot should be
//     dx_dt = 3*(pow(1-t,2)*(points[index*4 + 1].first - points[index*4].first)) + 2*t*(1-t)*(points[index*4+2].first-points[index*4 + 1].first) + t*t*(points[index*4+2].first-points[index*4 + 1].first);
//     dy_dt = 3*(pow(1-t,2)*(points[index*4 + 1].second - points[index*4].second)) + 2*t*(1-t)*(points[index*4+2].second-points[index*4 + 1].second) + t*t*(points[index*4+2].second-points[index*4 + 1].second);
//     current.push_back(dx_dt);
//     current.push_back(dy_dt);
//     //This part gets the vector tangent to the path of where the robot will later be (distance determined by header_dist)
//     carrot_dist = sqrt(pow(vx,2)+pow(vy,2));
//     for(int i = 0; i < 1/header_stepper_size; i++){ //   1/998001 ---> 1 is the total interval it will search through before quitting
//         t += index + header_stepper_size; //How finely it steps through the function
//         index = t; //Gives integer of which curve to follow
//         t -= index;
//         if(carrot_dist > header_dist || t > num_of_curves) break;  
//         px2 = pow(1-t,3)*points[index*4].first + 3*pow(1-t,2)*t*points[index*4+1].first + 3*(1-t)*t*t*points[index*4+2].first + t*t*t*points[index*4+3].first;
//         py2 = pow(1-t,3)*points[index*4].second + 3*pow(1-t,2)*t*points[index*4+1].second + 3*(1-t)*t*t*points[index*4+2].second + t*t*t*points[index*4+3].second;
//         carrot_dist += sqrt(pow(px - px2, 2)+pow(py-py2, 2));
//         px = px2;
//         py = py2;
        
//     }
//     dx_dt = 3*(pow(1-t,2)*(points[index*4 + 1].first - points[index*4].first)) + 2*t*(1-t)*(points[index*4+2].first-points[index*4 + 1].first) + t*t*(points[index*4+2].first-points[index*4 + 1].first);
//     dy_dt = 3*(pow(1-t,2)*(points[index*4 + 1].second - points[index*4].second)) + 2*t*(1-t)*(points[index*4+2].second-points[index*4 + 1].second) + t*t*(points[index*4+2].second-points[index*4 + 1].second);
//     lead.push_back(dx_dt);
//     lead.push_back(dy_dt);

    
//     //print_vector_to_serial("correction", correction);
//     //print_vector_to_serial("current", current);
//     //print_vector_to_serial("lead", lead)

//     to_normalized_vector(current);
//     to_normalized_vector(lead);

//     radius = header_dist/(0.01+acos(current[0]*lead[0] + current[1]*lead[1]));
//     innerSpeed = (radius - 12.5/2) / (radius + 12.5/2);
//     angleShift = acos(innerSpeed);
//     if(current[0]*lead[1]-lead[0]*current[1] < 0) angleShift *= -1;
//     onPath.push_back(current[0]*cos(angleShift)-current[1]*sin(angleShift));
//     onPath.push_back(current[0]*sin(angleShift)+current[1]*cos(angleShift));

//     output.push_back(correction[0] + onPath[0]*lead_scalar);
//     output.push_back(correction[1] + onPath[1]*lead_scalar);
//     to_normalized_vector(output);


//     if(sqrt(pow(correction[0],2)+pow(correction[1],2)) > 3){ //When slips too much, make slip less (slower) | Increase increment to make it more sensitive
//         turningStength -= 0.0002; /*NOTE: Adjust based on the frequency this program runs at */
//     }else if(sqrt(pow(correction[0],2)+pow(correction[1],2)) < 1){ //When slips too little, make faster (more slippage) | Increase increment to make it more sensitive  
//         turningStength += 0.0002;
//     }
    
//     Controller.Screen.setCursor(1,1);
//     Controller.Screen.print(curve_time);
//     Controller.Screen.setCursor(2,1);
//     Controller.Screen.print(current[0]);
//     Controller.Screen.print(", ");
//     Controller.Screen.print(current[1]);
    
//     newDirection = output;

//     return;

//     //Alright I need to draw a line from the robot to the point it thinks it should be at then use that in conjunction with the tangent vector, using some scalar to determine the weight of each. After that, I need to make a tracer that goes ahead and also averages with the other vector


// }


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


