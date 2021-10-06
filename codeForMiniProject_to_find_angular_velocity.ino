#define clk 2
#define dt 3

int counter = 0;
int currentState;
int lastState;
String currentDir;
float thetaDot; // angular velocity

int tOld;
int tNew;
int deltaT = 0;

int gatekeeperOld = 0;
int gatekeeperNew = 1;

bool flag = false;


void setup() {
pinMode(clk, INPUT);
pinMode(dt, INPUT);
Serial.begin(250000);
lastState = digitalRead(clk);
attachInterrupt(digitalPinToInterrupt(2), updateEncoder, CHANGE);
}



void loop() {
  if(flag == true){
  Serial.print("angular velocity is: ");
  Serial.println(thetaDot);
  flag = false;
  }
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
      counter --;
      currentDir = "CCW";
    }
    else{
      counter ++;
      currentDir = "CW";
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
