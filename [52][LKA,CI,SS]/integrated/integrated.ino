#include <Arduino_FreeRTOS.h>

// Black Line Follower 
const int IR1=8;      //Right sensor
const int IR2=9;    //left Sensor
// motor one
const int enA = 5;    //Right motor
const int MotorAip1=2;
const int MotorAip2=3;
// motor two
const int enB = 6;    //Left motor
const int MotorBip1=4;
const int MotorBip2=7;
//analog+7seg+light+led
const int VRx = A2;
const int VRy = A1;
const int light = A5;
int xPosition = 0;
int yPosition = 0;
int intensity = 0;
int mapX = 0;
int mapY = 0;
int led = 0;
const int segA = 10;
const int segB = 12;
const int ledPin=11;
const int buzzer=13;

void CG(void * parameters);
void LI(void * parameters);
void LKA(void * parameters);

void setup() 
{
  // put your setup code here, to run once:
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(IR1,INPUT);
  pinMode(IR2,INPUT);
  pinMode(MotorAip1,OUTPUT);
  pinMode(MotorAip2,OUTPUT);
  pinMode(MotorBip1,OUTPUT);
  pinMode(MotorBip2,OUTPUT);

//analog+7seg+light+led
  pinMode(segA,OUTPUT);
  pinMode(buzzer,OUTPUT);

  pinMode(segB,OUTPUT);
  pinMode(ledPin,OUTPUT);  
  pinMode(VRx, INPUT);
  pinMode(VRy, INPUT);
  Serial.begin(9600);

  xTaskCreate(
    LKA, // Function Name
    "Lane Keeping Assist", // Task Name
    100,       // Stack Size
    NULL,       // task parameters
    2,          // task priority
    NULL        // task handle
  );
  
  xTaskCreate(
    CG, // Function Name
    "Current Gear", // Task Name
    100,       // Stack Size
    NULL,       // task parameters
    1,          // task priority
    NULL
  );
  
  xTaskCreate(
    LI, // Function Name
    "Light Intensity", // Task Name
    100,       // Stack Size
    NULL,       // task parameters
    0,          // task priority
    NULL
  );
}
void loop() 
{
//analog+7seg+light+led
  
  //car code 
   

  // delay(100);  
  // Serial.print("ٌRight Sensor: ");
  // Serial.print(digitalRead(IR1));
  // Serial.print("ٌ Left Sensor: ");
  // Serial.print(digitalRead(IR2));
  // Serial.print("ٌ PWM Right: ");
  // Serial.print(analogRead(enA));
  // Serial.print("ٌ PWM Left: ");
  // Serial.println(analogRead(enB));


//     Serial.print("X: ");
//   Serial.print(mapX);
//   Serial.print(" | Y: ");
//   Serial.print(mapY);
//   Serial.print(" | seg: ");
// Serial.print(digitalRead(segA));
// Serial.print(digitalRead(segB));  
//   Serial.print(" | intensity: ");
//   Serial.print(intensity);
//   Serial.print(" | LED: ");
//   Serial.println(max(0,led));

}

void LKA(void * parameters) {
  // In this task we don't apply delay because the task itself has a delay
  while (1) {
   // Serial.println("Task 1");
    
if(digitalRead(IR1)==HIGH && digitalRead(IR2)==HIGH) //IR will not glow on black line
  {
    //Stop both Motors
    digitalWrite(MotorAip1,LOW);
    digitalWrite(MotorAip2,LOW);
    digitalWrite(MotorBip1,LOW);
    digitalWrite(MotorBip2,LOW);
    analogWrite (enA, 0);
    analogWrite (enB, 0);
    digitalWrite(buzzer,LOW);

  }

  else if(digitalRead(IR1)==LOW && digitalRead(IR2)==LOW)  //IR not on black line
  {
    //Move both the Motors
    digitalWrite(MotorAip1,HIGH);
    digitalWrite(MotorAip2,LOW);
    digitalWrite(MotorBip1,HIGH);
    digitalWrite(MotorBip2,LOW);
    analogWrite (enA, 60);
    analogWrite (enB, 60);
    digitalWrite(buzzer,LOW);

  }

  else if(digitalRead(IR1)==HIGH && digitalRead(IR2)==LOW)
  {
    //Tilt robot towards left B by stopping the left wheel and moving the right A one
    digitalWrite(MotorAip1,HIGH);     
    digitalWrite(MotorAip2,LOW);
    digitalWrite(MotorBip1,LOW);
    digitalWrite(MotorBip2,HIGH);
    analogWrite (enA, 160);
    analogWrite (enB, 160);
    digitalWrite(buzzer,HIGH);
  }

  else if(digitalRead(IR1)==LOW && digitalRead(IR2)==HIGH)
  {
    //Tilt robot towards right by stopping the right wheel and moving the left one
    digitalWrite(MotorAip1,LOW);     // If I want to turn right then the speed of the right wheel should be less than that of the left wheel, here, let a be the right wheel
    digitalWrite(MotorAip2,HIGH);
    digitalWrite(MotorBip1,HIGH);
    digitalWrite(MotorBip2,LOW);
    analogWrite (enA, 160);
    analogWrite (enB, 160);
    digitalWrite(buzzer,HIGH);

  }

  else
  {
    //Stop both the motors
    digitalWrite(MotorAip1,LOW);
    digitalWrite(MotorAip2,LOW);
    digitalWrite(MotorBip1,LOW);
    digitalWrite(MotorBip2,LOW);
    analogWrite (enA, 0);
    analogWrite (enB, 0);
    digitalWrite(buzzer,LOW);

  } 
  vTaskDelay(50/portTICK_PERIOD_MS);   
  }
}


//TAsk 2 (Light Intensity)
void LI(void * parameters) {
  TickType_t xLastWakeTime;
  const TickType_t xDelay250ms = pdMS_TO_TICKS(250);
  xLastWakeTime = xTaskGetTickCount();
  while (1) {
    intensity = analogRead(light);
    led = map(intensity,50,1023,0,255); 
  analogWrite(ledPin,max(0,led));
    // vTaskDelayUntil(&xLastWakeTime, xDelay250ms);
    vTaskDelay(50/portTICK_PERIOD_MS);
  }
}


// Task3 (Current Gear)
void CG(void * parameters) {
  TickType_t xLastWakeTime;
  const TickType_t xDelay250ms = pdMS_TO_TICKS(250);
  xLastWakeTime = xTaskGetTickCount();
  while (1) {
    //Serial.println("Task 3");
    xPosition = analogRead(VRx);
  yPosition = analogRead(VRy);
  
  mapX = map(xPosition, 0, 1023, -512, 512);
  mapY = map(yPosition, 0, 1023, -512, 512);
  
  if(mapX<-400){
  digitalWrite(segA,LOW);
  digitalWrite(segB,LOW);
  }
  if(mapX>400){
  digitalWrite(segA,HIGH);
  digitalWrite(segB,LOW);
  }if(mapY<-400){
  digitalWrite(segA,LOW);
  digitalWrite(segB,HIGH);
  }if(mapY>400){
  digitalWrite(segA,HIGH);
  digitalWrite(segB,HIGH);
  }
    vTaskDelay(50/portTICK_PERIOD_MS);
    // vTaskDelayUntil(&xLastWakeTime, xDelay250ms);
  }
}
