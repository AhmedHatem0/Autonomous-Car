int VRx = A0;
int VRy = A1;
int light = A2;
// int SW = 2;

int xPosition = 0;
int yPosition = 0;
int intensity = 0;
// int SW_state = 0;
int mapX = 0;
int mapY = 0;
int led = 0;
void setup() {
  Serial.begin(9600); 
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(6,OUTPUT);  
  pinMode(VRx, INPUT);
  pinMode(VRy, INPUT);
  // pinMode(SW, INPUT_PULLUP); 
  
}

void loop() {
  xPosition = analogRead(VRx);
  yPosition = analogRead(VRy);
  intensity = analogRead(light);
  // SW_state = digitalRead(SW);
  mapX = map(xPosition, 0, 1023, -512, 512);
  mapY = map(yPosition, 0, 1023, -512, 512);
  led = map(intensity,50,1023,0,255);
  Serial.print("X: ");
  Serial.print(mapX);
  Serial.print(" | Y: ");
  Serial.println(mapY);
  // Serial.print(" | intensity: ");
  // Serial.print(intensity);
  // Serial.print(" | LED: ");
  // Serial.println(max(0,led));

  analogWrite(6,max(0,led));
  if(mapX<-400){
  digitalWrite(2,LOW);
  digitalWrite(3,LOW);
  }
  if(mapX>400){
  digitalWrite(2,HIGH);
  digitalWrite(3,LOW);
  }if(mapY<-400){
  digitalWrite(2,LOW);
  digitalWrite(3,HIGH);
  }if(mapY>400){
  digitalWrite(2,HIGH);
  digitalWrite(3,HIGH);
  }
  // Serial.print(" | Button: ");
  // Serial.println(SW_state);

  delay(100);
  
}