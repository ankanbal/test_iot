#define NUM_SAMPLES 10

int sum = 0;
unsigned char sample_count = 0;
float voltage = 0.0;

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    // take a number of analog samples and add them up
    while (sample_count < NUM_SAMPLES) {
        sum += analogRead(A2);
        sample_count++;
        delay(10);
    }
    voltage = ((float)sum / (float)NUM_SAMPLES * 5.015) / 1024.0;
    Serial.print(voltage * 11.132);
    Serial.println (" V");
    sample_count = 0;
    sum = 0;
}
