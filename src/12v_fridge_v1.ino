
#include <Adafruit_SSD1306.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define x 8
#define OLED_RESET     5 // Reset pin # (or -1 if sharing Arduino reset pin)
#define GREEN_LED      13 // pin for green led
#define RELAY_FAN          6 // 
#define RELAY_FRIDGE        7 
#define BUTTONS         A0
#define TEMP_SENSOR   4


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

#define DISPLAY_MODE_SCREENSAVER  0
#define DISPLAY_MODE_STATUS  1
#define DISPLAY_MODE_SETTEMP  2

#define BUTTON_UP     1
#define BUTTON_DOWN   2
#define BUTTON_ECO    3
#define BUTTON_ONOFF  4

#define TEMP_DIFF     2      // this number(in degrees) is added to the target temperature ensuring cyles arent too frequent

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Data wire is conntec to the Arduino digital pin 4
const int oneWireBus = TEMP_SENSOR;          
// Setup a oneWire instace to communicate with any OneWire devices
OneWire oneWire(oneWireBus);
// Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature sensors(&oneWire);


unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers
int buttonState;            // the current reading from the input pin
int lastButtonState = 0;  // the previous reading from the input pin

int tempReadDelay = 100;
int tempReadDelayCount;
int screensaverCount;
int screensaverTimeout= 200;
int backToStatusCounter;
int backToStatusTimeout=100;

int DisplayMode = DISPLAY_MODE_STATUS;




int current_temp=100;
int target_temp=20;


void setup() {

  pinMode(4, INPUT_PULLUP);
  Serial.begin(9600);
  sensors.begin();
  Serial.println("sensor count:");
  Serial.println(sensors.getDeviceCount());
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RELAY_FRIDGE, OUTPUT);
  pinMode(RELAY_FAN, OUTPUT);
  

  digitalWrite(GREEN_LED, HIGH); 
  //digitalWrite(RELAY, LOW); 

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }


  display.display();
}

void loop() {
  // read the input on analog:
  //int sensorValue = analogRead(TEMP_SENSOR);
  CheckButtons();

  UpdateScreen(0);


  // temp read cycle. We dont need to read the temp every loop
  if(tempReadDelayCount > tempReadDelay) {
    current_temp = sensors.getTempCByIndex(0);
    sensors.requestTemperatures();
    Serial.println(current_temp);
    tempReadDelayCount=0;
  }

  // do we need to turn on/off the fridge?
  if(current_temp + TEMP_DIFF > target_temp) {
    digitalWrite(RELAY_FRIDGE, LOW); //turn on fridge
    digitalWrite(RELAY_FAN, LOW);
  }
  else {
    digitalWrite(RELAY_FRIDGE, HIGH); //turn off fridge
    digitalWrite(RELAY_FAN, HIGH); 
  }

  //temperature set timeout check
  if(backToStatusCounter>backToStatusTimeout) {
    DisplayMode = DISPLAY_MODE_STATUS;
    backToStatusCounter=0;
  }

  // screensaver check
  if(screensaverCount > screensaverTimeout) {
    DisplayMode = DISPLAY_MODE_SCREENSAVER;
  }

  tempReadDelayCount++;
  screensaverCount++;

}



void CheckButtons()
{
  static int old_press;

  int sensorValue = analogRead(BUTTONS);
  int reading=0;
  
  //Serial.println(sensorValue);
  // check button ladder logic
  if(sensorValue > 200 && sensorValue < 240) {reading=1;}
  if(sensorValue > 240 && sensorValue < 280) {reading=2;};
  if(sensorValue > 300 && sensorValue < 400) {reading=3;};
  if(sensorValue > 500 && sensorValue < 600) {reading=4;};
  if(sensorValue > 1000) {reading=0;};
  
  if(reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:
    
    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;
      buttonPress(buttonState);
    }
  }

  lastButtonState = reading;
  return;
}

void buttonPress(int button)
{
  //char buffer[40];
  //sprintf(buffer, "Button %d pressed", button);
  Serial.println("buttonPress");


  if(DisplayMode == DISPLAY_MODE_SETTEMP) {
    backToStatusCounter=0;
  }

  if(DisplayMode == DISPLAY_MODE_SCREENSAVER) {
    DisplayMode = DISPLAY_MODE_STATUS;
    //reset screensaver count
    screensaverCount=0;
    return;
  }
  if (button == BUTTON_UP || button == BUTTON_DOWN && DisplayMode == DISPLAY_MODE_STATUS) {
    // switch to set temp mode
    DisplayMode = DISPLAY_MODE_SETTEMP;
  }

  if (button == BUTTON_UP) {
    target_temp++;
  }
  if (button == BUTTON_DOWN) {
    target_temp--;
  }
  if (button == BUTTON_ECO) {
  }
  if (button == BUTTON_ONOFF) {
  }
  
  screensaverCount=0;
  

}

void UpdateScreen(int v) {


  display.clearDisplay();
  

  if(DisplayMode == DISPLAY_MODE_STATUS) {
    display.setCursor(0, 0);            // Start at top-left corner
    display.setTextSize(4);
    display.setTextColor(WHITE);

    display.println(int(current_temp));
    
  }

  if(DisplayMode == DISPLAY_MODE_SETTEMP) {
    display.setCursor(0, 0);            // Start at top-left corner

    display.setTextSize(4);
    display.setTextColor(WHITE);
    display.print(">");
    display.print(int(target_temp));
    
    backToStatusCounter++;
  }

  display.display();
}
