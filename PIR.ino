#include<FirebaseESP8266.h>
#include<ESP8266WiFi.h>
FirebaseData firebaseData;

#define FIREBASE_HOST "smart-home-automation-1883d.firebaseio.com"
#define FIREBASE_AUTH "W2rjGNgst5sBwY6cJlRu4s0YPYQ4So10hkKxiyBW"
#define WIFI_SSID "Quarantine"
#define WIFI_PASS "Covid-19"

int PIR = D1;
int warm_up =0;
int PIR_READ;

void setup() 
{
  pinMode(PIR, INPUT);
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
  Firebase.setInt(firebaseData, "/PIR", 0);

  delay(2000);
  
}
void loop() 
{
  Firebase.reconnectWiFi(true);
  PIR_READ = digitalRead(PIR);
  if( PIR_READ == 0 )
  {
    if( warm_up == 1 )
     {
      Serial.print("Warming Up\n");
      warm_up = 0;
      delay(2000);
    
      }
    Serial.print("No object detected\n");
    Firebase.setInt(firebaseData, "/PIR", 0);
    digitalWrite(LED_BUILTIN,1);
    delay(1000);
  }
  else
  {
    Serial.print("Object detected\n"); 
    Firebase.setInt(firebaseData, "/PIR", 1);
    digitalWrite(LED_BUILTIN,0);
    warm_up = 1;
    delay(1000);
  }  
}
