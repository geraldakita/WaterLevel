//define sound speed in cm/uS
#define SOUND_SPEED 0.034
#include <LiquidCrystal_I2C.h>

#define uS_TO_S_FACTOR 1000000ULL  /* Conversion factor for micro seconds to seconds */

#include <Arduino.h>

#include <WiFi.h>
#include <WiFiMulti.h>

#include <HTTPClient.h>

#define USE_SERIAL Serial

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

WiFiMulti wifiMulti;


long duration;
float distanceCm;
const int trigPin = 5;
const int echoPin = 18;
int led = 4; // set the "led" variable as 13


void setup() {
    lcd.init();
    lcd.clear();         
    lcd.backlight();      // Make sure backlight is on

    Serial.begin(115200); // Starts the serial communication
    pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
    
    pinMode(echoPin, INPUT); // Sets the echoPin as an Input
    
    pinMode(led, OUTPUT);   // designate port 13 as output  

    
    USE_SERIAL.begin(115200);

    USE_SERIAL.println();
    USE_SERIAL.println();
    USE_SERIAL.println();

    for(uint8_t t = 4; t > 0; t--) {
        USE_SERIAL.printf("[SETUP] WAIT %d...\n", t);
        USE_SERIAL.flush();
        delay(1000);
    }

    wifiMulti.addAP("Ben.Fra.Pri", "M633SFTK");

    

}

void loop() {

   // Print a message on both lines of the LCD.
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


  // turns on the led when the water level is below 5cm 
  if(distanceCm < 10){
    digitalWrite(led, HIGH);   // turn the led on

   }else {
    digitalWrite(led, LOW);    // turn the led off
   }
     
    // wait for WiFi connection
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

    delay(5000);
    lcd.clear();
}

void sendData(){
  HTTPClient http;
  Serial.println(" ");
  Serial.println("Sending Reading Request");
  http.begin("http://IP ADDRESS/Iot/waterTB.php?ownerID=1&location=Eastlegon&water_level=" + String(distanceCm));
  int httpCode = http.GET();
  String result = http.getString();
//  Serial.println(result);
}

void sendinformation() {
  HTTPClient http;
  Serial.println(" ");
  Serial.println("Sending Tank Information Request");

  http.begin("http://IP ADDRESS/Iot/ownerTB.php?ownerID=1&first_name=Eben&last_name=Akolly");
  int httpCode = http.GET();
  String result = http.getString();
//  Serial.println(result);
}
