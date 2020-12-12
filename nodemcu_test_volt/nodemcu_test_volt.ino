#define NUM_SAMPLES 10

int sum = 0;
unsigned char sample_count = 0;
float voltage = 0.0;

void setup()
{
    Serial.begin(115200);
}

void loop()
{
    // take a number of analog samples and add them up
    Serial.println(analogRead(A0/1024)*2.88);
    delay(100);
}
