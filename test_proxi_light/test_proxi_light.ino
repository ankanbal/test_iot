#include <APDS9930.h>

#include <Wire.h>
#define APDS9960_INT    2 // Needs to be an interrupt pin
APDS9960 apds = APDS9960();
int isr_flag = 0;

void setup() {
  pinMode(APDS9960_INT, INPUT);   // Set interrupt pin as input
  Serial.begin(9600); //Initialize Serial Port
  Serial.println();
  Serial.println("--------------------------------");
  Serial.println("14CORE | GESTURE TEST W/D APDS-9960");
  Serial.println("--------------------------------");
  
  attachInterrupt(0, interruptRoutine, FALLING);   // Initialize interrupt service routine
  if ( apds.init() ) { 
    Serial.println("APDS-9960 initialization complete"); // Initialize APDS-9960 (configure I2C and initial values)
  } else {
    Serial.println("Error APDS Initialization");
  }
  if ( apds.enableGestureSensor(true) ) {
    Serial.println("Gesture sensor is now running");
  } else {
    Serial.println("Error APDS Initialization");
  }
}

void loop() {
  if( isr_flag == 1 ) {
    detachInterrupt(0);
    handleGesture();
    isr_flag = 0;
    attachInterrupt(0, interruptRoutine, FALLING);
  }
}

void interruptRoutine() {
  isr_flag = 1;
}

void handleGesture() {
    if ( apds.isGestureAvailable() ) {
    switch ( apds.readGesture() ) {
      case DIR_UP:
        Serial.println("UP");
        break;
      case DIR_DOWN:
        Serial.println("DOWN");
        break;
      case DIR_LEFT:
        Serial.println("LEFT");
        break;
      case DIR_RIGHT:
        Serial.println("RIGHT");
        break;
      case DIR_NEAR:
        Serial.println("NEAR");
        break;
      case DIR_FAR:
        Serial.println("FAR");
        break;
      default:
        Serial.println("NONE");
    }
  }
}
