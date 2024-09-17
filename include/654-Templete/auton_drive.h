#include "vex.h"

class DriveSide{
 motor m1;
 motor m2;
 motor m3;
 const int NORMAL_MODE = 0, RPM_MODE = 1, DEGREE_MODE = 1, PERCENT_MODE = 2;
 const int MAX_RPM = 200; //FIND TRUE VALUE <---- <----- <-------


 float speed, setSpeed;
 bool direction = true;


    
///////////////////////////////////////////////////////////////////////////////////
///8/8/8/8/8/8/8/8/8/8/8/8/8/8/8/8/8/8/8/8/8/8/8/8/8/8/8/8/8/8/8/8/8/8/8/8/8/8/8/8/
 public:
     DriveSide(motor im1, motor im2, motor im3) : m1(im1), m2(im2), m3(im3){
       speed = 0.1;
       m1.setVelocity(speed * 100, percent);
       m2.setVelocity(speed * 100, percent);
       m3.setVelocity(speed * 100, percent);
   }
///////////////////////////////////////////////////////////////////////////////////
 void setVelocity(float speed, int type = 0){
   switch(type){
     case 0: //NORMAL_MODE (0  --> 1.0)
       speed *= 100;
       m1.setVelocity(speed, percent);
       m2.setVelocity(speed, percent);
       m3.setVelocity(speed, percent);
       break;


     case 1: //RPM_MODE (0 --> Max RPM of motors)
       m1.setVelocity(speed, rpm);
       m2.setVelocity(speed, rpm);
       m3.setVelocity(speed, rpm);
       break;


     default: //PERCENT_MODE (0 --> 100)
       m1.setVelocity(speed, percent);
       m2.setVelocity(speed, percent);
       m3.setVelocity(speed, percent);
       break;
   }
 }
///////////////////////////////////////////////////////////////////////////////////
 float getVelocity(int type = 1){
   switch(type){
     case 0: //NORMAL_MODE (0  --> 1.0)
       return m1.velocity(percent)/100.0;


     case 1: //RPM_MODE (0 --> Max RPM of motors)
       return m1.velocity(rpm);


     default: //PERCENT_MODE (0 --> 100)
       return m1.velocity(percent);
   }
 }
////////////////////////////////////////////////////////////////////////////////////
 void setPosition(float newPosition, int type = 0){
   switch(type){
     case 0: //NORMAL_MODE (1:1)
       m1.setPosition(newPosition, turns);
       m2.setPosition(newPosition, turns);
       m3.setPosition(newPosition, turns);
       break;
     case 1: //DEGREE_MODE (360:1)
       m1.setPosition(newPosition, degrees);
       m2.setPosition(newPosition, degrees);
       m3.setPosition(newPosition, degrees);
       break;
     default: //PERCENT_MODE (100:1)
       newPosition /= 100;
       m1.setPosition(newPosition, turns);
       m2.setPosition(newPosition, turns);
       m3.setPosition(newPosition, turns);
       break;
   }
 }
////////////////////////////////////////////////////////////////////////////////////
 float getPosition(int type = 0){
   switch(type){
     case 0:
       return m1.position(turns);
    
     case 1:
       return m1.position(degrees);


     default:
       return m1.position(turns)*100.0;
   }
 }
////////////////////////////////////////////////////////////////////////////////////
   void spinTo(float units, int type = 0){
     switch(type){


     }


   }
   float motorVelocity(bool condition = true){
     if(condition)
       return speed;
     return speed*200/60*360; // degrees per second
   }
   void spin(bool direction, float sec = 0){
     if(direction){
     m1.spin(forward);
     m2.spin(forward);
     m3.spin(forward);
     }else{
     m1.spin(reverse);
     m2.spin(reverse);
     m3.spin(reverse);
     }
     if(sec == 0)
       return;
     wait(sec, seconds);
     m1.stop();
     m2.stop();
     m3.stop();
   }
   void stop(){
     m1.stop();
     m2.stop();
     m3.stop();
   }
   void holding(bool condition = true){
     if(condition){
       m1.setStopping(hold);
       m1.setStopping(hold);
       m1.setStopping(hold);
     }else{
       m1.setStopping(coast);
       m1.setStopping(coast);
       m1.setStopping(coast);
     }
   }
};


};



