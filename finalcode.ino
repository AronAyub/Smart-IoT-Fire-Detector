#include <ESP8266WiFi.h>
#include "AdafruitIO_WiFi.h"

#define WIFI_SSID       "WhatsApp for net 0765909567"
#define WIFI_PASS       "magic123."

#define IO_USERNAME    "AA001"
#define IO_KEY         "aio_APMG20ILzp2Osj44e8fsjDzZdOLN"

// Connect to Wi-Fi and Adafruit IO handel
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);

// Create a feed object that allows us to send data to
AdafruitIO_Feed * firedetector = io.feed("firedetector");
AdafruitIO_Feed * smoke = io.feed("smoke");

const int sensor_pin = A0;
const int buzzer = 14;
const int led = 15;
int smokeA0 = 12;

// Input value range
int sensorValueMin = 0;   // Minimum sensor value
int sensorValueMax = 1023;  // Maximum sensor value

// Output range (percentage)
int outputMin = 0;    // Minimum output value (0%)
int outputMax = 100;  // Maximum output value (100%)
int smokie;
int percentage;
//delay func
unsigned long previousTime = 0;
unsigned long delayTime = 5000;


void setup()
{
  // Enable the serial port so we can see updates
  Serial.begin(115200);
  pinMode(sensor_pin, INPUT_PULLUP);
  pinMode(buzzer, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(smokeA0, INPUT);

  //buzzer == LOW;
  //led == LOW;

  // Connect to Adafruit IO
  io.connect();

  // wait for a connection
  while (io.status() < AIO_CONNECTED)
  {
    Serial.println("*************");
    Serial.println("Connecting to Wi-Fi");
    delay(500);
  }
}

void loop()
{
  sensor();

}

void sensor() {
  // Always keep this at the top of your main loop
  // While not confirmed, this implies that the Adafruit IO library is not event-driven
  // This means you should refrain from using infinite loops
  io.run();
  int sensorValue = analogRead(sensor_pin);
  int smokie = digitalRead(smokeA0);

  // Map the sensor value to the percentage range
  int percentage = map(sensorValue, sensorValueMin, sensorValueMax, outputMin, outputMax);


  // Checks if it has reached the threshold value
  if (smokie == 1)
  {
    Serial.println("Printing Smoke State................");
    Serial.println("*********SMOKE DETECTED*********** ");
    digitalWrite(led, HIGH);
    delay(100);
  }

  if (smokie == 0)
  {
    Serial.println("No Smoke ******");
    delay(100);
  }
  if (percentage < 70)
  {
    Serial.println("Printing Flames State................");
    Serial.println("*********FLAME DETECTED********** ");
    digitalWrite(led, HIGH);
    
    delay(100);
  }
  if (percentage > 70)
  {
    Serial.println("Printing Flames State................");
    Serial.println("No Flames detected*********** ");
    delay(100);
  }
  if (smokie == 1 && percentage < 70)
  {
    Serial.println("Smoke and Flames Detected, critical!");
    delay(100);
    digitalWrite(led, HIGH);
    digitalWrite(buzzer, HIGH);
  }

  if (smokie == 0 && percentage > 76)

  {
    Serial.println("No Smoke & No Flames, ******* ");
    Serial.println("YOU ARE SAFE**");
    delay(100);
    digitalWrite(led, LOW);
    digitalWrite(buzzer, LOW);
  }


  // Print the percentage value

  if (millis() - previousTime >= delayTime) {

    firedetector->save(percentage);
    delay(100);
    smoke->save(smokie);

    Serial.print("Percentage: ");
    Serial.println(percentage);

    Serial.print("State Sent is***: ");
    Serial.println(smokie);
    //Serial.println(smokie);
    previousTime = millis();
  }
}

void buzz()
{
  // Checks if it has reached the threshold value
  if (smokie == 1) //|| percentage < 70)
  {
    digitalWrite(led, HIGH);
    digitalWrite(buzzer, HIGH);

    // tone(buzzer, 1000, 200);
  }
  if (smokie == 0) //|| percentage > 76)
  {
    digitalWrite(led, LOW);
    digitalWrite(buzzer, LOW);

    ///noTone(buzzer);
  }
  else
  {
    Serial.print("Check the Sensor");
  }
  delay(1000);
}
