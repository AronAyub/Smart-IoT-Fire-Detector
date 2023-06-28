# Smart IoT Fire Detector and Monitoring Solution

<img width="1362" alt="fire" src="https://github.com/AronAyub/Smart-IoT-Fire-Detector/assets/55284959/6a75ac05-58e5-4e73-af43-739343d4e70e">

## Get the right libraries 
- [Adafruit-Io master][def]
- [ArduinoHtttpsClient][def2]

### Test your Flame sensor using a simple arduino Sketch.

```
const int sensor_pin = 4;
const int buzzer = 14;

void setup() {
  pinMode(sensor_pin,INPUT_PULLUP);
  pinMode(buzzer,OUTPUT);
}

void loop() {
  if(digitalRead(sensor_pin) == LOW){
    digitalWrite(buzzer,HIGH);
  }else{
    digitalWrite(buzzer,LOW);
  }
}
```
##### **Test the Ardafruit Io by sending random values**

```
#include <ESP8266WiFi.h>
#include "AdafruitIO_WiFi.h"
 
#define WIFI_SSID       "xxxxx"
#define WIFI_PASS       "xxxxxx"
 
#define IO_USERNAME    "xxxxxxx"
#define IO_KEY         "xxxxxxxxxxxxxxx"
 
// Connect to Wi-Fi and Adafruit IO handel 
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);
 
// Create a feed object that allows us to send data to
AdafruitIO_Feed * firedetector = io.feed("xxxxx");
 

void setup() 
{
  // Enable the serial port so we can see updates 
  Serial.begin(115200);
 
  // Connect to Adafruit IO
  io.connect();
 
  // wait for a connection
  while(io.status() < AIO_CONNECTED) 
  {
    Serial.print(".");
    delay(500);
  }
}
 
void loop() 
{

  int randomValue = random(0, 100); 
  // Always keep this at the top of your main loop
  // While not confirmed, this implies that the Adafruit IO library is not event-driven
  // This means you should refrain from using infinite loops
  io.run();
 
  // Send 10 to our Workshop Temperature Feed
  firedetector->save(randomValue);
 
  // This is so we can see some response on the computer
  Serial.println("Data sent");
 
  // DONT SEND A BILLION DATA POINTS! This slows down the program so that it sends readings once every 5 seconds
  delay(5000);
}
```
#### Test the smoke sensor

```
//******

// All the resources for this project:
// https://www.electromaniaweb.wordpress.com 
//https://www.arduino.cc
//*******/

int LED1 = 12;
int LED2 = 11;
int buzzer = 10;
int smokeA0 = A2;
int sensorThreshold = 400;

void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(smokeA0, INPUT);
  Serial.begin(9600);
}

void loop() {
  int analogSensor = analogRead(smokeA0);

  Serial.print("Pin A0: ");
  Serial.println(analogSensor);
  // Checks if it has reached the threshold value
  if (analogSensor > sensorThreshold)
  {
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, LOW);
    tone(buzzer, 1000, 200);
  }
  else
  {
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, HIGH);
    noTone(buzzer);
  }
  delay(100);
}
````
 This is a smart Fire Detector Project


[def]: https://github.com/AronAyub/Smart-IoT-Fire-Detector/blob/main/Adafruit_IO_Arduino-master.zip
[def2]: https://github.com/arduino-libraries/ArduinoHttpClient
