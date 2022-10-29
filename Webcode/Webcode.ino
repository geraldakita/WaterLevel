#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include "html.h"

#include <WiFi.h>
#include <WiFiMulti.h>

#include <HTTPClient.h>

#define USE_SERIAL Serial

//define sound speed in cm/uS
#define SOUND_SPEED 0.034
#include <LiquidCrystal_I2C.h>
#define uS_TO_S_FACTOR 1000000ULL  /* Conversion factor for micro seconds to seconds */

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

WiFiMulti wifiMulti;

long duration;
float distanceCm;
const int trigPin = 5;
const int echoPin = 18;
int led = 4; // set the "led" variable as 13
int relay = 23;



const char* ssid = "DUFIE-HOSTEL";
const char* password = "Duf1e@9723";

WebServer server(80);

int state;

void handleRoot() {
//  digitalWrite(led, 1);
  server.send(200, "text/html", page);
//  digitalWrite(led, 0);
}

void handleNotFound() {
  digitalWrite(led, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  digitalWrite(led, 0);
}

void autoOP(){
  state = 0;
}

void manStartOP(){
  state = 1;
}

void manStopOP(){
  state = 2;
}

void operation(){

    lcd.setCursor(0,0);   //Set cursor to character 2 on line 0
    lcd.print("Water Level(cm)");
    lcd.setCursor(6,1);   //Move cursor to character 2 on line 1
    lcd.print(distanceCm);
     // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);


   duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance
  distanceCm = duration * SOUND_SPEED/2;
    delay(1000);
    lcd.clear();
    Serial.println(distanceCm);
  
  if (state == 0){
    if(distanceCm < 10){
      digitalWrite(led, HIGH);
      digitalWrite(relay, LOW);
    }
    if(distanceCm >= 50){
      digitalWrite(led, LOW);
      digitalWrite(relay, HIGH);
    }
  }
  else if (state == 1){
    digitalWrite(led, HIGH);
    digitalWrite(relay, LOW);
  }
  else if (state == 2){
    digitalWrite(led, LOW);
    digitalWrite(relay, HIGH);
  }
}

void setup(void) {
  wifiMulti.addAP("DUFIE-HOSTEL", "Duf1e@9723");
  lcd.init();
  lcd.clear();         
  lcd.backlight();      // Make sure backlight is on

  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
    
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
    
  pinMode(led, OUTPUT);   // designate port 13 as output  

  pinMode(relay, OUTPUT);

  
  digitalWrite(led, 0);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp32")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);
  server.on("/AutoStart", autoOP);
  server.on("/ManualStart", manStartOP);
  server.on("/ManualStop", manStopOP);

  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");
  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();
  delay(2);//allow the cpu to switch to other tasks
  operation();


  if((wifiMulti.run() == WL_CONNECTED)) {

        HTTPClient http;

                
        sendinformation();
        sendData();
        
        USE_SERIAL.print("[HTTP] begin...\n");
        // configure traged server and url
        //http.begin("https://www.howsmyssl.com/a/check", ca); //HTTPS

        
        USE_SERIAL.print("[HTTP] GET...\n");
        // start connection and send HTTP header
        int httpCode = http.GET();

        // httpCode will be negative on error
        if(httpCode > 0) {
            // HTTP header has been send and Server response header has been handled
            USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode);

            // file found at server
            if(httpCode == HTTP_CODE_OK) {
                String payload = http.getString();
                USE_SERIAL.println(payload);
            }
        } else {
            USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }

        http.end();
    }
}

void sendData(){
  HTTPClient http;
  Serial.println(" ");
  Serial.println("Sending Reading Request");
  http.begin("http://192.168.103.48/waterlevel/waterTB.php?ownerID=1&location=Eastlegon&water_level=" + String(distanceCm));
  int httpCode = http.GET();
  String result = http.getString();
//  Serial.println(result);
}

void sendinformation() {
  HTTPClient http;
  Serial.println(" ");
  Serial.println("Sending Tank Information Request");

  http.begin("http://192.168.103.48/waterlevel/ownerTB.php?ownerID=1&first_name=Eben&last_name=Akolly");
  int httpCode = http.GET();
  String result = http.getString();
//  Serial.println(result);
}
