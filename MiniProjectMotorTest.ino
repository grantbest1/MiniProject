#include "DualMC33926MotorShield.h"

DualMC33926MotorShield md;

#define clk 2
#define dt 3

//#define 

int counter = 0;
int currentState;
int lastState;
String currentDir;
double thetaDot; // angular velocity

int tOld;
int tNew;
int deltaT = 0;

int gatekeeperOld = 0;
int gatekeeperNew = 1;

bool flag = false;


void stopIfFault()
{
  if (md.getFault())
  {
    Serial.println("fault");
    while(1);
  }
}


void setup() {
  Serial.begin(250000);
  pinMode(clk, INPUT);
  pinMode(dt, INPUT);

  
  Serial.println("Dual MC33926 Motor Shield");
  md.init();
  
  lastState = digitalRead(clk);
  attachInterrupt(digitalPinToInterrupt(2), updateEncoder, CHANGE);
}



void loop() {
  // put your main code here, to run repeatedly:
  if(pos !=0){
    md.setM1Speed(100);
  }
  //md.setM1Speed(100);
//  if(flag == true){
//    Serial.println(thetaDot);
//    flag = false;
//  }
  
  
}

void updateEncoder(){
  currentState = digitalRead(clk);


  if(currentState != lastState && currentState == 1){
    if(gatekeeperOld == 0){
      tNew = millis();
      gatekeeperNew = 0;
      gatekeeperOld = 1;
      deltaT = tNew - tOld;
      thetaDot = (counter*2*3.14)/(800*deltaT);
    }

    if(digitalRead(dt) != currentState){
      counter ++;
      currentDir = "CW";
    }
    else{
      counter --;
      currentDir = "CCW";
    }
  }
  lastState = currentState;

  if(gatekeeperNew == 0){
    tOld = millis();
    gatekeeperOld = 0;
    gatekeeperNew = 1;
    flag = true;
  }
  
  
}
