
#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;
#include <TouchScreen.h>
#include <Arduino_FreeRTOS.h>

#define MINPRESSURE 200
#define MAXPRESSURE 1000

SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);

// ALL Touch panels and wiring is DIFFERENT
// copy-paste results from TouchScreen_Calibr_native.ino
const int XP = 8, XM = A2, YP = A3, YM = 9; //ID=0x9341
const int TS_LEFT = 145, TS_RT = 893, TS_TOP = 113, TS_BOT = 903;
int song=1;
char lable[] = "||";
bool abdo=true;
 bool playing=true;
 bool text =true;

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

Adafruit_GFX_Button on_btn, off_btn ,play ,up ,dow ;

int pixel_x, pixel_y;     //Touch_getXY() updates global vars
bool Touch_getXY(void)
{
    TSPoint p = ts.getPoint();
    pinMode(YP, OUTPUT);      //restore shared pins
    pinMode(XM, OUTPUT);
    digitalWrite(YP, HIGH);   //because TFT control pins
    digitalWrite(XM, HIGH);
    bool pressed = (p.z > MINPRESSURE && p.z < MAXPRESSURE);
    if (pressed) {
        pixel_x = map(p.x, TS_LEFT, TS_RT, 0, tft.width()); //.kbv makes sense to me
        pixel_y = map(p.y, TS_TOP, TS_BOT, 0, tft.height());
    }
    return pressed;
}

#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

void task1(void* parameters);
void setup(void)
{
  //////////////////////////////mp3/////////////////////////////////
  Serial.println("ana d5lt el task");
  mySoftwareSerial.begin(9600);
  Serial.begin(115200);
  
  Serial.println();
  Serial.println("DFRobot DFPlayer Mini Demo");
  Serial.println("Initializing DFPlayer ... (May take 3~5 seconds)");
  
  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true);
  }
  Serial.println(F("DFPlayer Mini online."));
  
  myDFPlayer.volume(30);  //Set volume value. From 0 to 30
  myDFPlayer.play(1);  //Play the first mp3

  uint16_t ID = tft.readID();
    Serial.print("TFT ID = 0x");
    Serial.println(ID, HEX);
    Serial.println("Calibrate for your Touch Panel");
    if (ID == 0xD3D3) ID = 0x9486; // write-only shield
    tft.begin(ID);
    tft.setRotation(0);            //PORTRAIT
    tft.fillScreen(BLACK);
    on_btn.initButton(&tft,  60, 200, 100, 40, WHITE, CYAN, BLACK, "<<", 2);
    off_btn.initButton(&tft, 180, 200, 100, 40, WHITE, CYAN, BLACK, ">>", 2);
    play.initButton(&tft, 120, 250, 100, 40, WHITE, CYAN, BLACK, "|> / ||", 2);
    up.initButton(&tft, 60, 300, 50, 20, WHITE, CYAN, BLACK, "+", 2);
    dow.initButton(&tft, 180, 300, 50, 20, WHITE, CYAN, BLACK, "-", 2);


    on_btn.drawButton(false);
    off_btn.drawButton(false);
     play.drawButton(false);
     up.drawButton(false);
     dow.drawButton(false);
     tft.setCursor(85,120);

    tft.fillRect(40, 80, 160, 80, RED);
 
  
  xTaskCreate(task1, "motor", 256, NULL,1, NULL);

  ///////////////////////////////////////////////////////////////////
   
    
}

/* two buttons are quite simple
 */
void loop(void)
{
}


void displaym(int s){
  tft.fillRect(40, 80, 160, 80, WHITE);
  tft.setCursor(85,120);
  tft.setTextColor(TFT_RED); // Set up text color
  

  if(s==1){
    tft.println("001.mp3");
  }
  if(s==2){
    tft.println("002.mp3");
  }
  if(s==3){
    tft.println("003.mp3");
  }
        
  
}
void printDetail(uint8_t type, int value){
  switch (type) {
    case TimeOut:
      Serial.println(F("Time Out!"));
      break;
    case WrongStack:
      Serial.println(F("Stack Wrong!"));
      break;
    case DFPlayerCardInserted:
      Serial.println(F("Card Inserted!"));
      break;
    case DFPlayerCardRemoved:
      Serial.println(F("Card Removed!"));
      break;
    case DFPlayerCardOnline:
      Serial.println(F("Card Online!"));
      break;
    case DFPlayerPlayFinished:
      Serial.print(F("Number:"));
      Serial.print(value);
      Serial.println(F(" Play Finished!"));
      break;
    case DFPlayerError:
      Serial.print(F("DFPlayerError:"));
      switch (value) {
        case Busy:
          Serial.println(F("Card not found"));
          break;
        case Sleeping:
          Serial.println(F("Sleeping"));
          break;
        case SerialWrongStack:
          Serial.println(F("Get Wrong Stack"));
          break;
        case CheckSumNotMatch:
          Serial.println(F("Check Sum Not Match"));
          break;
        case FileIndexOut:
          Serial.println(F("File Index Out of Bound"));
          break;
        case FileMismatch:
          Serial.println(F("Cannot Find File"));
          break;
        case Advertise:
          Serial.println(F("In Advertise"));
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }

}
void task1(void * parameters) {
  
  while (1) {
    
if(abdo == true){
tft.fillRect(40, 80, 160, 80, WHITE);  abdo=false;
 }
 
 if(text == true){
  displaym(1);
  text=false;
 }
    bool down = Touch_getXY();
    on_btn.press(down && on_btn.contains(pixel_x, pixel_y));
    off_btn.press(down && off_btn.contains(pixel_x, pixel_y));
   play.press(down && play.contains(pixel_x, pixel_y));
   up.press(down && up.contains(pixel_x, pixel_y));
   dow.press(down && dow.contains(pixel_x, pixel_y));
    if (on_btn.justReleased())
        on_btn.drawButton();
    if (up.justReleased())
        up.drawButton();
    if (dow.justReleased())
        dow.drawButton();    
    if (off_btn.justReleased())
        off_btn.drawButton();
        if (play.justReleased())
        play.drawButton();
    if (on_btn.justPressed()) {
        myDFPlayer.previous();
        on_btn.drawButton(true);
        if(song == 3){
          song=1;
        }else{
          song++;
        }
        Serial.print(song);
        displaym(song);
      //  tft.fillRect(40, 80, 160, 80, GREEN);
    }
    if (off_btn.justPressed()) {
         myDFPlayer.next();
        off_btn.drawButton(true);
        if(song == 1){
          song=3;
        }else{
          song--;
        }
        Serial.print(song);
        displaym(song);
      //  tft.fillRect(40, 80, 160, 80, RED);
    }
    if (up.justPressed()) {
        myDFPlayer.volumeUp();
        up.drawButton(true);
     //   tft.fillRect(40, 80, 160, 80, RED);
    }
    if (dow.justPressed()) {
         myDFPlayer.volumeDown();
        dow.drawButton(true);
       // tft.fillRect(40, 80, 160, 80, RED);
    }
     if (play.justPressed()) {
        if(playing ==  true){
//          lable[1]="a";
//          Serial.println(lable);
        //  tft.fillRect(40, 80, 160, 80, WHITE);
          myDFPlayer.pause();
          playing=false; 
               
        }else{
//          lable[1]="b";
//          Serial.println(lable);
       //   tft.fillRect(40, 80, 160, 80, BLUE);
          myDFPlayer.start();
          playing=true; 
        }
        play.drawButton(true);
    }
    if (myDFPlayer.available()) {
    printDetail(myDFPlayer.readType(), myDFPlayer.read()); //Print the detail message from DFPlayer to handle different errors and states.
  }
  vTaskDelay(50/portTICK_PERIOD_MS);
  }
}


