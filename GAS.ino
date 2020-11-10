#include<FirebaseESP8266.h>
#include<ESP8266WiFi.h>
FirebaseData firebaseData;

#define FIREBASE_HOST "smart-home-automation-1883d.firebaseio.com"
#define FIREBASE_AUTH "W2rjGNgst5sBwY6cJlRu4s0YPYQ4So10hkKxiyBW"
#define WIFI_SSID "Quarantine"
#define WIFI_PASS "Covid-19"


#define GAS_A_PIN A0

int GAS_A =0;


void setup() 
{
  pinMode(GAS_A_PIN, INPUT);
  
  Serial.begin(9600);
  pinMode(LED_BUILTIN,OUTPUT);
  
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  Serial.print("Connecting to WIFI");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.print("\nWIFI Connected.");
  Serial.print("\nIP Address:");
  Serial.print(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.setInt(firebaseData, "/GAS_A", 0);
 
 
}
void loop() 
{
  Firebase.reconnectWiFi(true);
  GAS_A = analogRead(GAS_A_PIN);  //0-1023
  GAS_A = map(GAS_A,500,800,0,100); //0-100

  Firebase.setInt(firebaseData, "/GAS_A",GAS_A );


  Serial.print("\nGAS Analog =");
  Serial.print(GAS_A);
 
  delay(500);
}
