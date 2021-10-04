/* This code reads from two encoders using 2 different ISRs that are meant to track encoder clicks and calculate both velocity, distance, and direction over time. 
 *  The declarations below in the #define section show which pin of the encoder needs to be connected to which pin on the UNO. The left wheel encoder should have
 *  CLK connected to Digital pin 2 and right wheel encoder should be connected to digital pin 3. The rest of the pin connections should be fairly self explanatory.
 *  Once connected, turning the encoder wheels will update the direction and distance on the serial monitor in real time.
 *   
 */



#define CLK_LEFT 2
#define CLK_RIGHT 3
#define DT_LEFT 4
#define DT_RIGHT 5
#define fullRotation 20 //number of clicks for a full rotations

float r = .05; // radius of the wheel
float b =  .1; // distance between wheels


int counter_LEFT = 0; // accumulates the number of clicks in either direction of the left encoder
int counter_RIGHT = 0; // same as above but for right encoder
int currentStateCLK_LEFT; // either high or low for leading contact
int currentStateCLK_RIGHT; // either high or low for leading contact
int lastStateCLK_LEFT; // either high or low for following contact
int lastStateCLK_RIGHT; // either high or low for following contact
String currentDir_LEFT =""; // string to show either clockwise or counter clockwise
String currentDir_RIGHT =""; // shows either CW or CCW
float thetaDot_LEFT; // angular velocity declaration
float thetaDot_RIGHT; // angular velocity declaration

float v_LEFT = 0; // velocity of left encoder
float v_RIGHT = 0; // velocity of right encoder
float deltaDistance_LEFT = 0; // change in left distance
float deltaDistance_RIGHT = 0; // change in right distance

float x_DISTANCE = .001; //total x distance 
float y_DISTANCE = .001; // total y distance 
float phi = .001; // current angle from straight


int tOld_LEFT; // Time old
int tOld_RIGHT; // Time old
int tNew_LEFT; // Time new
int tNew_RIGHT; // Time new
int delta_LEFT = 0; // change in time between left clicks
int delta_RIGHT = 0; // change in time between right clicks


int gatekeeperOld_LEFT = 0; // variable to allow first time to be captured
int gatekeeperOld_RIGHT = 0; 
int gatekeeperNew_LEFT = 1; // variable to allow second time to be captured
int gatekeeperNew_RIGHT = 1;

void setup() {
  // setting pins and initial conditions
  pinMode(CLK_LEFT,INPUT); 
  pinMode(DT_LEFT,INPUT);
  pinMode(CLK_RIGHT,INPUT);
  pinMode(DT_RIGHT,INPUT);
  Serial.begin(9600);
  lastStateCLK_LEFT = digitalRead(CLK_LEFT);
  lastStateCLK_RIGHT = digitalRead(CLK_RIGHT);
  attachInterrupt(digitalPinToInterrupt(2), updateEncoder_LEFT, CHANGE); // initializes the pins for interrupt
  attachInterrupt(digitalPinToInterrupt(3), updateEncoder_RIGHT, CHANGE);
  Serial.println("x   y"); // labels the columns for x and y distance



  
}
void loop() {} // do nothing lol



void updateEncoder_LEFT(){
  currentStateCLK_LEFT = digitalRead(CLK_LEFT); // captures first encoder state



  
  if (currentStateCLK_LEFT != lastStateCLK_LEFT  && currentStateCLK_LEFT == 1){ // conditional to check if the encoder is ready to be read
    if(gatekeeperOld_LEFT == 0){ // conditional to run once per every two loops
      tNew_LEFT = millis(); // captures the time 
      gatekeeperNew_LEFT = 0; // flips the bottom gate to open 
      gatekeeperOld_LEFT = 1; // flips the top gate to closed the purpose of this line and the one above it is to make sure only one if statement is evaluated per loop
      //Serial.print("Time new: ");
      //Serial.println(tNew_LEFT);
      delta_LEFT = tNew_LEFT - tOld_LEFT; // calculate this difference in time
      //Serial.print("Delta_LEFT is: ");
      //Serial.println(delta_LEFT);
      thetaDot_LEFT = (4*3.14)/(20*delta_LEFT); // angular velocity is calculated
      //Serial.print("Angular Velocity LEFT is: ");
      //Serial.println(thetaDot_LEFT);
      v_LEFT = thetaDot_LEFT * r; // actual velocity of the left wheel is calculated
      deltaDistance_LEFT = v_LEFT * delta_LEFT; // the distance the left wheel travels per clicks
      x_DISTANCE += (cos(phi)*(deltaDistance_LEFT + deltaDistance_RIGHT))/2; // the full x distance the wheel travels
      y_DISTANCE += (sin(phi)*(deltaDistance_LEFT + deltaDistance_RIGHT))/2; // full y distance the wheel
      phi += (r/b)*(deltaDistance_LEFT - deltaDistance_RIGHT); // calculates the new angle from perfectly straight
      //Serial.print("x Distance is: ");
      Serial.print(x_DISTANCE); //displays x the distance  
      Serial.print("    ");
      Serial.println(y_DISTANCE); // displays the y distance
    }


    
    if (digitalRead(DT_LEFT) != currentStateCLK_LEFT) {
      counter_LEFT ++; // increments the counter
      currentDir_LEFT ="CW"; // sets the direction to CW
    } else {
      counter_LEFT --; // Decrements the counter 
      currentDir_LEFT ="CCW";
    }
    //Serial.print("Direction_LEFT: ");
    //Serial.print(currentDir_LEFT);
    //Serial.print(" | Counter_LEFT: ");
    //Serial.println(counter_LEFT);
  }
  lastStateCLK_LEFT = currentStateCLK_LEFT; // sets the last state to the current state
  
  if(gatekeeperNew_LEFT == 0){
  tOld_LEFT = millis(); // captures the old time
  gatekeeperOld_LEFT = 0;
  gatekeeperNew_LEFT =1;
  //Serial.print("Time old: ");
  //Serial.println(tOld_LEFT);
  }
}


void updateEncoder_RIGHT(){
  currentStateCLK_RIGHT = digitalRead(CLK_RIGHT);



  
  if (currentStateCLK_RIGHT != lastStateCLK_RIGHT  && currentStateCLK_RIGHT == 1){
      
      if(gatekeeperOld_RIGHT == 0){ // this if statement is the same as the one above in the first ISR
      tNew_RIGHT = millis();
      gatekeeperNew_RIGHT = 0;
      gatekeeperOld_RIGHT = 1;
      //Serial.print("Time new: ");
      //Serial.println(tNew_RIGHT);
      delta_RIGHT = tNew_RIGHT - tOld_RIGHT;
      //Serial.print("Delta_RIGHT is: ");
      //Serial.println(delta_RIGHT);
      thetaDot_RIGHT = (4*3.14)/(20*delta_RIGHT);
      //Serial.print("Angular Velocity RIGHT is: ");
      //Serial.println(thetaDot_RIGHT);
      v_RIGHT = thetaDot_RIGHT * r;
      deltaDistance_RIGHT = v_RIGHT * delta_RIGHT;
      x_DISTANCE += (cos(phi)*(deltaDistance_LEFT + deltaDistance_RIGHT))/2;
      y_DISTANCE += (sin(phi)*(deltaDistance_LEFT + deltaDistance_RIGHT))/2;
      phi += (r/b)*(deltaDistance_LEFT - deltaDistance_RIGHT);
      
      Serial.print(x_DISTANCE);
      Serial.print("    ");
      Serial.println(y_DISTANCE);
      
    }

    
    if (digitalRead(DT_RIGHT) != currentStateCLK_RIGHT) {
      counter_RIGHT ++;
      currentDir_RIGHT ="CW";
    } else {
      // Encoder is rotating CW so increment
      counter_RIGHT --;
      currentDir_RIGHT ="CCW";
    }
    //Serial.print("Direction_RIGHT: ");
    //Serial.print(currentDir_RIGHT);
    //Serial.print(" | Counter_RIGHT: ");
    //Serial.println(counter_RIGHT);
  }
  lastStateCLK_RIGHT = currentStateCLK_RIGHT;



  if(gatekeeperNew_RIGHT == 0){ // same as the if statement in the first ISR
  tOld_RIGHT = millis();
  gatekeeperOld_RIGHT = 0;
  gatekeeperNew_RIGHT =1;
  //Serial.print("Time old RIGHT: ");
  //Serial.println(tOld_RIGHT);
  }
}
