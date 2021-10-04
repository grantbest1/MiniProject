// Rotary Encoder Inputs
#define CLK_ONE 2
#define DT_ONE 3
#define CLK_TWO 4
#define DT_TWO 5
#define fullRotation 20 

int counter_ONE = 0;
int currentStateCLK_ONE;
int lastStateCLK_ONE;
String currentDir_ONE ="";

int counter_TWO = 0;
int currentStateCLK_TWO;
int lastStateCLK_TWO;
String currentDir_TWO ="";
int positionONE;
int positionTWO;


void setup() {
  pinMode(CLK_ONE,INPUT);
  pinMode(DT_ONE,INPUT);
  
  pinMode(CLK_TWO,INPUT);
  pinMode(DT_TWO,INPUT);
  
  Serial.begin(9600);
  lastStateCLK_ONE = digitalRead(CLK_ONE);
  lastStateCLK_TWO = digitalRead(CLK_TWO);
}

void loop() {
  currentStateCLK_ONE = digitalRead(CLK_ONE);
  if (currentStateCLK_ONE != lastStateCLK_ONE  && currentStateCLK_ONE == 1){
    if (digitalRead(DT_ONE) != currentStateCLK_ONE) {
      counter_ONE ++;
      currentDir_ONE ="CW";
    } else {
      counter_ONE --;
      currentDir_ONE ="CCW";
    }
    Serial.print("Direction ONE: ");
    Serial.print(currentDir_ONE);
    Serial.print(" | Counter ONE: ");
    Serial.println(counter_ONE);
  }
  lastStateCLK_ONE = currentStateCLK_ONE;

  currentStateCLK_TWO = digitalRead(CLK_TWO);
  if (currentStateCLK_TWO != lastStateCLK_TWO  && currentStateCLK_TWO == 1){
    if (digitalRead(DT_TWO) != currentStateCLK_TWO) {
      counter_TWO ++;
      currentDir_TWO ="CW";
    } else {
      counter_TWO --;
      currentDir_TWO ="CCW";
    }
    Serial.print("Direction TWO: ");
    Serial.print(currentDir_TWO);
    Serial.print(" | Counter TWO: ");
    Serial.println(counter_TWO);
  }
  lastStateCLK_TWO = currentStateCLK_TWO;
  delay(1);
  }
  
