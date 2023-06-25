# Smart IoT Fire Detector
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

 This is a smart Fire Detector Project


[def]: https://github.com/AronAyub/Smart-IoT-Fire-Detector/blob/main/Adafruit_IO_Arduino-master.zip
[def2]: https://github.com/arduino-libraries/ArduinoHttpClient
