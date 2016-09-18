# esp8266-serial-receive-and-send
receive data from serial and send

One sketch for the Arduino uController that collects accelerometer data and sends it to the esp8266 uController.
Second sketch is the esp8266 uController receiving the data over serial and sending it to data.Sparkfun.com

Arduino sketch reads a 200G accerlometer with any arduino running 3.3V and sends the total accerlation (hit) to an ESP8266 over Serial.  
In this case I used a second serial hardware Serial1 as available in a Mega, teensy, leonardo uControllers. Could also use TX, pin 1 in an UNO.
 
 
ESP8266 sketch runs on an nodeMcu or any ESP8266 uController.  The ESP8266 receives a serial value from an Arduino and sends data via HTTP GET requests to data.sparkfun.com service.

Connect your arduino TX pin the the ESP8266 RX pin as well as connect the ground pin. Both uController's need to be 3.3volt or a level shifter is required.
 
The first character received is a ~ (ASCII 126) and then the data (inputString) followed by an Arduino pirnt return (println) sends the final character (ASCII 13)
 
You need to get streamId and privateKey at data.sparkfun.com and paste them below. Or just customize this script to talk to other HTTP servers.
