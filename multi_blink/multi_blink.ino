void setup() {
  // put your setup code here, to run once:
  for (int i=2; i<=11;i++)
  {
    pinMode(i,OUTPUT);
  }

}

void loop() {
  // put your main code here, to run repeatedly:
 for (int i=2; i<=11;i++)
  {
    blynk(i);
  }
}

void blynk(int i)
{
  digitalWrite(i,HIGH);
  delay(i*1);
  digitalWrite(i,LOW);
  delay(i*1);
}
