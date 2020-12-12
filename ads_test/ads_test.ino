#include <Adafruit_ADS1015.h>
#define voltOut A0
Adafruit_ADS1115 ads(0x48);
 
void setup(void)
{
Serial.begin(9600);
Serial.println("Hello!");
 
Serial.println("Getting single-ended readings from AIN0..3");
Serial.println("ADC Range: +/- 6.144V (1 bit = 3mV/ADS1015, 0.1875mV/ADS1115)");
 
ads.begin();
}
 
void loop(void)
{
int16_t adc1;
adc1 = ads.readADC_SingleEnded(1);
Serial.print("AIN1: ");
Serial.println((adc1/1024)*2.88);
float volt = (analogRead(voltOut)/1024)*2.88;
Serial.print("A0: ");
Serial.println(volt);
delay(1000);
}
