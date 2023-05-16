//BCD 1, these are the digital pins of the first CD4511 chip, the one placed on the right hand

int a1 = 8;
int a2 = 9;
int a3 = 10;
int a4 = 11;


int n=0; //Setting initial value of n to 0, n serves as a placeholder value of our button

void setup() //this will set all the pins to output, and the button pin (2) to input to receive
{

  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);

  pinMode(0,INPUT);
  pinMode(1,INPUT);
  pinMode(2,INPUT);
  pinMode(3,INPUT);
  pinMode(4,INPUT);
  pinMode(5,INPUT);
  pinMode(6,INPUT);
  Serial.begin(9600);
}

void loop(){
 if(n==10) 
   n=0;
disp1(n);
 delay(1000);//100 ms delay to debounce
 n++;
}

void disp1(int num){ //this method entails making 0-9 combinations using the BCD pins by sending different outputs to turn each segment on or off. 
  if(num == 0)//0000
  {
    digitalWrite(a1, LOW); 
    digitalWrite(a2, LOW);
    digitalWrite(a3, LOW);
    digitalWrite(a4, LOW);
  }
  if(num == 1)//0001
  {
    digitalWrite(a1, HIGH);
    digitalWrite(a2, LOW);
    digitalWrite(a3, LOW);
    digitalWrite(a4, LOW);
  }
  if(num == 2)//0010
  {
    digitalWrite(a1, LOW);//0
    digitalWrite(a2, HIGH);//1
    digitalWrite(a3, LOW);//0
    digitalWrite(a4, LOW);//0
  }
  if(num == 3)//0011
  {
    digitalWrite(a1, HIGH);//1
    digitalWrite(a2, HIGH);//1
    digitalWrite(a3, LOW);//0
    digitalWrite(a4, LOW);//0
  }
  if(num == 4)//0100
  {
    digitalWrite(a1, LOW);//0
    digitalWrite(a2, LOW);//0
    digitalWrite(a3, HIGH);//1
    digitalWrite(a4, LOW);//0
  }
  if(num == 5)//0101
  {
    digitalWrite(a1, HIGH);//1
    digitalWrite(a2, LOW);//0
    digitalWrite(a3, HIGH);//1
    digitalWrite(a4, LOW);//0
  }
  if(num == 6)//0110
  {
    digitalWrite(a1, LOW);//0
    digitalWrite(a2, HIGH);//1
    digitalWrite(a3, HIGH);//1
    digitalWrite(a4, LOW);//0
  }
  if(num == 7) //0111
  {
    digitalWrite(a1, HIGH);//1
    digitalWrite(a2, HIGH);//1
    digitalWrite(a3, HIGH);//1
    digitalWrite(a4, LOW);//0
  }
  if(num == 8) //1000
  {
    digitalWrite(a1, LOW);//0
    digitalWrite(a2, LOW);//0
    digitalWrite(a3, LOW);//0
    digitalWrite(a4, HIGH);//1
  }
  if(num == 9)//1001
  {
    digitalWrite(a1, HIGH);//1
    digitalWrite(a2, LOW);//0
    digitalWrite(a3, LOW);//0
    digitalWrite(a4, HIGH);//1
  }
  Serial.println(num);
  int o0 = digitalRead(0);
  int o1 = digitalRead(1);
  int o2 = digitalRead(2);
  int o3 = digitalRead(3);
  int o4 = digitalRead(4);
  int o5 = digitalRead(5);
  int o6 = digitalRead(6);
  Serial.print(o0);
  Serial.print(o1);
  Serial.print(o2);
  Serial.print(o3);
  Serial.print(o4);
  Serial.print(o5);
  Serial.println(o6);
}

//this is not meant to be copy pasted, I have included a downloadable version of the code if you wish to try it.
