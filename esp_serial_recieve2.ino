/*
 *  This sketch runs on an ESP8266.  The ESP8266 receives a serial value from an Arduino and 
 *  sends data via HTTP GET requests to data.sparkfun.com service.
 *
 *  Connect your arduino TX pin the the ESP8266 RX pin as well as connect the ground pin.
 *  Both uController's need to be 3.3volt or a level shifter is required.
 *  
 *  The first character received is a ~ (ASCII 126) and then the data (inputString) followed by an Arduino pirnt return (println) sends the final character (ASCII 13)
 *  
 *  You need to get streamId and privateKey at data.sparkfun.com and paste them
 *  below. Or just customize this script to talk to other HTTP servers.
 *
 */

#include <ESP8266WiFi.h>

const char* ssid     = "xxxxx";
const char* password = "xxxx";

const char* host = "data.sparkfun.com";
const char* publicKey   = "XG3a7JLA2xCox1DajOr3";
const char* privateKey = "xxxxxxx";

boolean stringComplete;
String inputString;

int value = 0;
int sendGet = 0;

void setup() {
  Serial.begin(9600);
  delay(10);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {

  serialEvent();

  if (stringComplete) {
    Serial.print(inputString);
    value = inputString.toInt();
    inputString = "";
    stringComplete = false;
    sendGet = 1;
  }
    
  if(sendGet == 1){
    sendGet = 0;
  
    Serial.print("connecting to ");
    Serial.println(host);
  
    // Use WiFiClient class to create TCP connections
    WiFiClient client;
    const int httpPort = 80;
    if (!client.connect(host, httpPort)) {
      Serial.println("connection failed");
      return;
    }
  
    Serial.println(F("Connected"));

    // Post the data! Request should look a little something like:
    // GET /input/publicKey?private_key=privateKey&light=1024&switch=0&time=5201 HTTP/1.1\n
    // Host: data.sparkfun.com\n
    // Connection: close\n
    // \n
    client.print("GET /input/");
    client.print(publicKey);
    client.print("?private_key=");
    client.print(privateKey);
    client.print("&");
    client.print("gs");
    client.print("=");
    client.print(value);
    client.println(" HTTP/1.1");
    client.print("Host: ");
    client.println("data.sparkfun.com");
    client.println("Connection: close");
    client.println();

    unsigned long timeout = millis();
    while (client.available() == 0) {
      if (millis() - timeout > 5000) {
        Serial.println(">>> Client Timeout !");
        client.stop();
        return;
      }
    }
    
    // Read all the lines of the reply from server and print them to Serial
    while(client.available()){
      String line = client.readStringUntil('\r');
      Serial.print(line);
    }
    
    Serial.println();
    Serial.println("closing connection");
  }

}



//------------------------------------------- SERIAL EVENT


void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    //Serial.println(inChar);
    if(inChar == 126){  //~ erases string
      inputString = "";
    }
    if(inChar != 13 && inChar != 126){      // add it to the inputString:
      inputString += inChar;
    }
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == 13) { //13 is ASCI carriage return
      stringComplete = true;
    }
  }
}


