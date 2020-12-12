
#define BLYNK_PRINT Serial
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
char auth[] ="b2707fc31e034dc09c39a9b3147bba4b";
char ssid[] = "Realme 2 Pro";
char pass[] = " 12345678";
WidgetMap myMap(V0);
void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);

  // If you want to remove all points:
  //myMap.clear();
  Serial.print("There you go.....");
  int index = 1;
  float latt = 26.8687764;
  float lon = 75.7633267;
  Blynk.notify("Garbage bin full. Check out the location and if its nearby....head out to empty it.");
  myMap.location(index, latt, lon, "value");
}

void loop()
{
  Blynk.run();
}
