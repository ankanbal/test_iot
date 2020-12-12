int sensorPin = A0; // select the input pin for the potentiometer
int ledPin = A1; // select the pin for the LED
int sensorValue = 0; // variable to store the value coming from the sensor
float brightness = 0;
void setup () 
{
  pinMode (ledPin, OUTPUT);
  Serial.begin (9600);
}
 
void loop () 
{
  sensorValue = analogRead (sensorPin);
  brightness = float(sensorValue) * (255/1023);
  analogWrite(ledPin, brightness);
  Serial.println (st(sensorValue)+" , "+str(brightness));
}
 /* int SensorData=digitalRead(soundSensor); 
  if(SensorData==1){

    if(LEDStatus==false){
        LEDStatus=true;
        digitalWrite(LED,HIGH);
    }
    else{
        LEDStatus=false;
        digitalWrite(LED,LOW);
    }
  }*/
// } 
