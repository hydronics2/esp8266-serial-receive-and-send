# esp8266-serial-receive-and-send
One Arduino records data and sends it over serial to a NodeMcu that sends it to data.sparkfun.com.

The 'record' sketch is for a uController that collects accelerometer data and sends it to the esp8266 uController.
The 'esp8266' sketch receives the data over serial and sends it over wifi to data.Sparkfun.com

I used a teensy 3.2 uController [teensy 3.2](https://www.pjrc.com/store/teensy32.html) to read a 200G accelerometer, [Adafruit ADXL377](https://www.adafruit.com/product/1413).
I used a NodeMcu for my esp8266.

The 'record' sketch reads a 200G accerlometer with any 3.3V arduino and sends the total accerlation (hit) to an ESP8266 over Serial. In this case I used a second serial hardware Serial1 as available in a Mega, teensy, leonardo uControllers. Could also use TX, pin 1 in an UNO with an appropriate level shifter.
 
ESP8266 sketch runs on an nodeMcu or any ESP8266 uController.  The ESP8266 receives a serial value from an Arduino and sends data via HTTP GET requests to data.sparkfun.com service.

Connect your arduino TX pin the the ESP8266 RX pin as well as connect the ground pin. Both uController's need to be 3.3volt or a level shifter is required.
 
The first character received is a ~ (ASCII 126) and then the data (inputString) followed by an Arduino pirnt return (println) sends the final character (ASCII 13)
 
You need to get streamId and privateKey at data.sparkfun.com and paste them below. Or just customize this script to talk to other HTTP servers.


