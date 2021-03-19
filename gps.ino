#include <TinyGPS++.h> 
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>

TinyGPSPlus gps; 
int RX = 4;
int TX = 5;
SoftwareSerial ss(RX, TX); 
const char* ssid = "Haunted House"; 
const char* password = "kotha103"; 
const char* firebase_host = "";
const char* firebase_auth = "";
float latitude, longitude, alt;

FirebaseData fbdo;
String path = "/forward";

void setup() {
  Serial.begin(115200);
  ss.begin(9600);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password); 
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  
  Firebase.begin(firebase_host, firebase_auth);
  Firebase.reconnectWiFi(true);

  Firebase.beginStream(fbdo, path);

  if (!Firebase.beginStream(fbdo, path))
  {
    Serial.println("error beginning stream");
    Serial.println("reason " + fbdo.errorReason());
  }
}

void loop() {
  while (ss.available() > 0) {
    if (gps.encode(ss.read())) 
    {
      if (gps.location.isValid()) 
      {
        latitude = (gps.location.lat(),6);
        longitude = (gps.location.lng(),6);
        alt = (gps.altitude.meters(),6);
        Serial.print("latitude : ");
        Serial.println(latitude);
        Serial.print("longitude : ");
        Serial.println(longitude);
        Serial.print("altitude : ");
        Serial.println(alt);
        Firebase.setFloat("latitude : ",latitude);
      }
    }
  }
}
