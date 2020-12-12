#include <DHT.h>

#define NUM_SAMPLES 10

#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8

#define DHTPIN 2
#define DHTTYPE DHT11

int blueFrequency = 0;
int blueColor = 0;

int sum = 0;
unsigned char sample_count = 0;
float voltage = 0.0;

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  
  dht.begin();
  
  Serial.begin(9600);

}

void loop() {
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  blueFrequency = pulseIn(sensorOut, LOW);
  blueColor = map(blueFrequency, -400, 232, 255, 0);
  Serial.print("B = ");
  Serial.print(blueColor);
  Serial.print("\t");
  
  float t = dht.readTemperature();
  if (isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C\t ");
  
  while (sample_count < NUM_SAMPLES) {
        sum += analogRead(A2);
        sample_count++;
        delay(10);
    }
  voltage = ((float)sum / (float)NUM_SAMPLES * 5.015) / 1024.0;
  float ans = voltage * 11.132;
  Serial.print(ans);
  Serial.println (" V");
  sample_count = 0;
  sum = 0;
  
  if (blueColor <= 30)
  {
    Serial.println("Change breather of the transformer");
  }
  if (ans >= 10.000)
  {
    Serial.println("Voltage reaching danger signals");
  }
  if (t > 30.00)
  {
    Serial.println("Heat is increasing, might wanna cool it down.");
  }
  delay(2000);
}
