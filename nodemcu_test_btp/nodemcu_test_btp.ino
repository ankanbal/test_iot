#include <Adafruit_ADS1015.h>
#include <DHT.h>
#include <ESP8266WiFi.h>
#include <Wire.h>

#define NUM_SAMPLES 10

Adafruit_ADS1115 ads(0x48);

#define S0 D4
#define S1 D5
#define S2 D6
#define S3 D7
#define sensorOut D8

#define DHTPIN D3
#define DHTTYPE DHT11

int blueFrequency = 0;
int blueColor = 0;

int sum = 0;
unsigned char sample_count = 0;
float voltage = 0.0;

DHT dht(DHTPIN, DHTTYPE);

const char* ssid = "karlo connect";
const char* password = "ankan1234";

WiFiServer server(80);

void setup() {
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  
  dht.begin();
  
  Serial.begin(115200);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.println(WiFi.localIP());
  ads.begin();

}

void loop() {
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  blueFrequency = pulseIn(sensorOut, LOW);
  blueColor = map(blueFrequency, -400, 232, 255, 0);
  float t = dht.readTemperature();
  int16_t adc0 = ads.readADC_SingleEnded(0);
  if (isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  float volt = (adc0/1024)*2.88;
  
  String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n <!DOCTYPE html> <html> <head> <title>IIT Ropar Smart Transformer Diagnosis</title> <style>";
  s += "a:link {background-color: YELLOW;text-decoration: none;}";
  s += "table, th, td {border: 1px solid black;} </style> </head> <body> <h1  style=";
  s += "font-size:300%;";
  s += " ALIGN=CENTER> IIT Ropar Smart Transformer Diagnosis</h1>";
  s += "<h2 ALIGN=CENTER>The following data shown here is read live yet dummy data, coz it is not coming from a transformer.</h2>";
  s += "<p ALIGN=CENTER style=""font-size:150%;""";
  s += "> <b>Transformer Details</b></p> <table ALIGN=CENTER style=";
  s += "width:50%";
  s += "> <tr> <th>Breather intensity</th>";
  s += "<td ALIGN=CENTER >";
  s += blueColor;
  s += "</td> </tr> <tr> <th>Temperature</th> <td ALIGN=CENTER >";
  s += t;
  s += "</td> </tr> <tr>  <th>Load</th> <td ALIGN=CENTER >";
  s += volt;
  s += "</td>  </tr> </table> ";
  WiFiClient client = server.available();
  if (!client)
  {
    return;
  }
  client.print(s);
  delay(1000);
}
