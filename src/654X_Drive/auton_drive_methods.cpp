#include "vex.h"

std::vector<std::pair<float, float>> curveNumeroUno = {
    {-21.79f, -51.93f}, // (-55.3,  -131.9)
    {-30.71f, -42.13f}, // (-78,    -107)
    {-38.98f, -33.86f}, // (-99,    -86)
    {-49.76f, -21.83f}, // (-126.35, -55.428)
    {-49.76f, -21.83f}, // (-126.35, -55.428)
    {-62.20f,  -8.27f}, // (-158,   -21)
    {-35.04f,   6.69f}, // (-89,    17)
    {-23.23f,  17.46f}, // (-59,    44.34)
    {-23.23f,  17.46f}, // (-59,    44.34)
    {-11.42f,  27.56f}, // (-29,    70)
    { 29.05f, -19.64f}, // (73.8,   -49.9)
    { 21.81f, -41.34f}, // (55.4,   -105)
    { 21.81f, -41.34f}, // (55.4,   -105)
    { 14.57f, -63.00f}, // (37,     -160)
    {-22.52f, -65.67f}, // (-57.2,  -166.8)
    {-21.79f, -51.93f}  // (-55.3,  -131.9)
};

// Movement scheme developed by Thomas Grisamore
float turningStength = 1000; // Used to control speed to prevent slippage


void standardized_vector_movement(float speed, const std::vector<std::pair<float, float>> &curvePattern){
    
    float dotProduct;
    float lengthOfVector;
    float offset = chassis.get_heading();
    chassis.set_coordinates(curvePattern[0].first, curvePattern[0].second, chassis.get_absolute_heading());
    std::vector<float> origin = {0,0};
   
    //Creates a normal vector pointing straight up
   
    std::vector<float> currentDirection;
    currentDirection = to_normalized_vector(chassis.get_heading()+90);



    std::vector<float> newDirection; // Normal Vector representing current orientation NEEDS REAL CODE
    newDirection = currentDirection;
   


   
    //Declaration of variables used below \/
   
    float xPos;
    float yPos;
    float leftSpeed;
    float rightSpeed;
    float COMSpeed; //Center of mass speed
    float curveSpeed;

    
    while(true){ // get_vector_distance(chassis.get_position_vector(), {chassis.ideal_x, chassis.ideal_y}) < 1
       
        //xPos = (chassis.get_X_position() - origin[0]) * cos(to_rad(chassis.get_heading() - offset)) - (chassis.get_Y_position() - origin[1]) * sin(to_rad(chassis.get_heading() - offset));
        //yPos = (chassis.get_Y_position() - origin[1]) * sin(to_rad(chassis.get_heading() - offset)) + (chassis.get_X_position() - origin[0]) * cos(to_rad(chassis.get_heading() - offset));
        currentDirection = to_normalized_vector(chassis.get_heading()+90);




        bezier(newDirection, curvePattern);
        lengthOfVector = get_vector_distance({0.0f, 0.0f}, newDirection);
        newDirection[0] /= lengthOfVector;
        newDirection[1] /= lengthOfVector;
        dotProduct = newDirection[0] * currentDirection[0] + newDirection[1] * currentDirection[1]; //Gives relative closeness to direction (1:same, -1:complete opposites)
       
        // These two lines of code determine which movement scheme to input to the robot
        //if(currentDirection[0] == 0) currentDirection[0] = 0.001;
        float crossProduct = currentDirection[0] * newDirection[1] - currentDirection[1] *  newDirection[0];
        if (crossProduct < 0) {  // Adjust to Right
            leftSpeed = speed;
            rightSpeed = speed  * dotProduct;
        } else {  // Adjust to Left
            leftSpeed = speed * dotProduct;
            rightSpeed = speed;
        }
        COMSpeed = (leftSpeed + rightSpeed) / 2;
        curveSpeed = sqrt(turningStength * (1/(1.001-dotProduct)));
        if(curveSpeed < COMSpeed){
            leftSpeed *=  curveSpeed / COMSpeed;
            rightSpeed *= curveSpeed / COMSpeed;
        }
        
        // this needs to be a function
        chassis.right_drive.spin(vex::fwd, rightSpeed, velocity_units::normalized);
        chassis.left_drive.spin(vex::fwd, leftSpeed, velocity_units::normalized);
        
   
    }
}




//3{(1−t)2(P1−P0)+2t(1−t)(P2−P1)+t2(P3−P2)}


void bezier(std::vector<float>& newDirection, const std::vector<std::pair<float, float>> &points){
    const float current_scalar = 1, lead_scalar = 1;
    const float header_dist = 5;
    const float header_stepper_size = 0.001;
    int num_of_curves = sizeof(points)/4;
    static float time = 0;
    float t = time;
    int index = t;
    float increment = 0.1;
    float pastDist = 10000; //Big number
    float dist = 0;
    float carrot_dist;
    float dx_dt;
    float dy_dt;
    float px, py, px2, py2;
    float vx, vy;
    std::vector<float> correction;
    std::vector<float> output;
    std::vector<float> lead;
    std::vector<float> current;

    for(int i = 0; i < 20 && increment >= 0.01; i++){
        index = t;
        t -= index;
        px = pow(1-t,3)*points[index*4].first + 3*pow(1-t,2)*t*points[index*4+1].first + 3*(1-t)*t*t*points[index*4+2].first + t*t*t*points[index*4+3].first;
        py = pow(1-t,3)*points[index*4].second + 3*pow(1-t,2)*t*points[index*4+1].second + 3*(1-t)*t*t*points[index*4+2].second + t*t*t*points[index*4+3].second;

        dist = pow(pow(px-chassis.get_X_position(),2) + pow(py-chassis.get_Y_position(),2),0.5);

        if(pastDist<=dist){
            t-=increment;
            increment/=10;
        }
        t+=increment;
        pastDist = dist;
    }
    t+=increment*9;
    time = t + index;


    


    //This part gets the vector pointing directly to the path
    vx =  px - chassis.get_X_position();
    vy =  py - chassis.get_Y_position();
    correction.push_back(vx);
    correction.push_back(vy);
    //This part gets the vector tangent to the path of where the robot should be
    dx_dt = 3*(pow(1-t,2)*(points[index*4 + 1].first - points[index*4].first)) + 2*t*(1-t)*(points[index*4+2].first-points[index*4 + 1].first) + t*t*(points[index*4+2].first-points[index*4 + 1].first);
    dy_dt = 3*(pow(1-t,2)*(points[index*4 + 1].second - points[index*4].second)) + 2*t*(1-t)*(points[index*4+2].second-points[index*4 + 1].second) + t*t*(points[index*4+2].second-points[index*4 + 1].second);
    current.push_back(dx_dt);
    current.push_back(dy_dt);
    //This part gets the vector tangent to the path of where the robot will later be (distance determined by header_dist)
    carrot_dist = sqrt(pow(vx,2)+pow(vy,2));
    for(int i = 0; i < 1/header_stepper_size; i++){ //   1/998001 ---> 1 is the total interval it will search through before quitting
        t += header_stepper_size;//How finely it steps through the function
        if(carrot_dist > header_dist || t > num_of_curves) break;  
        index = t;
        px2 = pow(1-t,3)*points[index*4].first + 3*pow(1-t,2)*t*points[index*4+1].first + 3*(1-t)*t*t*points[index*4+2].first + t*t*t*points[index*4+3].first;
        py2 = pow(1-t,3)*points[index*4].second + 3*pow(1-t,2)*t*points[index*4+1].second + 3*(1-t)*t*t*points[index*4+2].second + t*t*t*points[index*4+3].second;
        carrot_dist += sqrt(pow(px - px2, 2)+pow(py-py2, 2));
        px = px2;
        py = py2;
        
    }
    Controller.Screen.setCursor(1,1);
    Controller.Screen.print(index);
    dx_dt = 3*(pow(1-t,2)*(points[index*4 + 1].first - points[index*4].first)) + 2*t*(1-t)*(points[index*4+2].first-points[index*4 + 1].first) + t*t*(points[index*4+2].first-points[index*4 + 1].first);
    dy_dt = 3*(pow(1-t,2)*(points[index*4 + 1].second - points[index*4].second)) + 2*t*(1-t)*(points[index*4+2].second-points[index*4 + 1].second) + t*t*(points[index*4+2].second-points[index*4 + 1].second);
    lead.push_back(dx_dt);
    lead.push_back(dy_dt);

    
    //print_vector_to_serial("correction", correction);
    //print_vector_to_serial("current", current);
    //print_vector_to_serial("lead", lead);

    to_normalized_vector(current);
    to_normalized_vector(lead);


    output.push_back(correction[0] + current[0]*current_scalar + lead[0]*lead_scalar);
    output.push_back(correction[1] + current[1]*current_scalar + lead[1]*lead_scalar);
    to_normalized_vector(output);


    if(sqrt(pow(correction[0],2)+pow(correction[1],2)) > 3){ //When slips too much, make slip less (slower) | Increase increment to make it more sensitive
        turningStength -= 0.0002; /*NOTE: Adjust based on the frequency this program runs at */
    }else if(sqrt(pow(correction[0],2)+pow(correction[1],2)) < 1){ //When slips too little, make faster (more slippage) | Increase increment to make it more sensitive  
        turningStength += 0.0002;
    }

    
    newDirection = output;


    //Alright i need to draw a line from thje robot to the point it thinks it should be at then use that in conjunction with the tangent vector, using some scalar to determine the weight of each. After that, I need to make a tracer that goes ahead and also averages with the other vector


}


/*
set t to little less than last run through
iterate through t until distance function (derivative) between robot
position and curve goes from (-) -> (+)
once happens, decrease increment and run again (subtract value at the
start of loops so that t(used) is greater than t (actual))
repeat until increment is within WHAT I DEEM an acceptance margin of error
Store t as position along the curve
Find tangent vector at t
find the distance from the point to the tangent of the curve at that value
of t
--> std::abs(m * xp + -1 * yp + y - m *x) / std::sqrt(m * m + 1)
assign vector value
go up by some amount t and take the vector along the curve


Find the average of these two and return the value (use value to determine
weight of each component)










useless
dx_dt =
3(pow(1-t,2)*(points[index*4 + 1][0] - points[index*4][0]) +
2*t*(1-t)*(points[index*4+2][0]-points[index*4 + 1][0]) +
t*t*(points[index*4+2][0]-points[index*4 + 1][0];
dy_dt =
3(pow(1-t,2)*(points[index*4 + 1][1] - points[index*4][1]) +
2*t*(1-t)*(points[index*4+2][1]-points[index*4 + 1][1]) +
t*t*(points[index*4+2][1]-points[index*4 + 1][1];
float deriv_of_dist = 0.5*pow(pow(chassis.get_X_position() - px,2) + pow(chassis.get_Y_position() - py,2),- 0.5)
* (2*(chassis.get_X_position() - px)*-dx_dt+2*(chassis.get_Y_position() - py)*-dy_dt)
*/


