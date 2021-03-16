#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>

#define WIFI_SSID ""
#define WIFI_PASSWORD ""

#define FIREBASE_HOST ""
#define FIREBASE_AUTH ""

FirebaseData fbdo;
String path = "/forward";



void printResult(FirebaseData &data);

void setup()
{

  Serial.begin(115200);

  pinMode(14, OUTPUT);
  pinMode(12, OUTPUT);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

  Firebase.beginStream(fbdo, path);

  if (!Firebase.beginStream(fbdo, path))
  {
    Serial.println("error beginning stream");
    Serial.println("reason " + fbdo.errorReason());
  }
}

void loop()
{

  Firebase.readStream(fbdo);

  if (!Firebase.readStream(fbdo))
  {
    Serial.println("error reading stream");
    Serial.println("reason " + fbdo.errorReason());
  }

  if (fbdo.streamAvailable())
  {
    //Serial.print("Value = ");
    
     if(fbdo.intData() == 1)//forward
  {
    Serial.print("Forward executing ");
    printResult(fbdo);
    digitalWrite (12, HIGH);
    digitalWrite (14, HIGH);
    digitalWrite(5,LOW);
    digitalWrite(6,LOW);
    
  }

  else if(fbdo.intData() == 0)//forward not
  {
    Serial.print("Forward not executing ");
    printResult(fbdo); 
  }
 

  else if(fbdo.intData() == 1)//backward
  {
    
  }

  else if (fbdo.intData()== 1) //right
  {
    
  }

 else if (fbdo.intData() == 1)//left
 {
   
 }

 else if (fbdo.intData() == 1) //stop
 {
   
 }
  }
}

void printResult(FirebaseData &data)
{

  if (data.dataType() == "int")
    Serial.println(data.intData());
}