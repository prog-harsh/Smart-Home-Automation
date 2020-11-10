#include<FirebaseESP8266.h>
#include<ESP8266WiFi.h>
#include<DHT.h>
FirebaseData firebaseData;

#define FIREBASE_HOST "smart-home-automation-1883d.firebaseio.com"
#define FIREBASE_AUTH "W2rjGNgst5sBwY6cJlRu4s0YPYQ4So10hkKxiyBW"
#define WIFI_SSID "Quarantine"
#define WIFI_PASS "Covid-19"

#define DHT_PIN D1
#define LDR_A_PIN A0
#define DHT_TYPE DHT11

DHT DHT11_INTERFACE(DHT_PIN, DHT_TYPE);
float Temp = 0;
float Hum = 0 ;
float PrevTemp = 0;
float PrevHum = 0;

int PrevLDR = 0;
int LDR_A = 0;
void setup()
{
  DHT11_INTERFACE.begin();

  pinMode(LDR_A_PIN, INPUT);
  Serial.begin(9600);
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
  Firebase.setFloat(firebaseData, "/Humidity", 0);
  Firebase.setFloat(firebaseData, "/Temperature", 0);
  Firebase.setFloat(firebaseData, "/LightIntensity", 0);
  delay(1000);
}

void loop()
{
  Firebase.reconnectWiFi(true);
  Temp = DHT11_INTERFACE.readTemperature();
  Hum = DHT11_INTERFACE.readHumidity();
  
  LDR_A = analogRead(LDR_A_PIN); //0-1023 = 1024   
  LDR_A = map(LDR_A,0,1023,0,100); //0-100

  Serial.print("\nLDR = ");
  Serial.print(LDR_A);
  Serial.print("\nTemperature = ");
  Serial.print(Temp);
  Serial.print("\t\tHumidity = ");
  Serial.print(Hum);
  
  if (PrevTemp != Temp || PrevHum != Hum || PrevLDR != LDR_A)
  {
     Firebase.setFloat(firebaseData, "/Temperature", Temp);
  Firebase.setFloat(firebaseData, "/Humidity", Hum);
  Firebase.setInt(firebaseData, "/LightIntensity", LDR_A);
  } 

  PrevTemp = Temp;
  PrevHum = Hum;
  PrevLDR = LDR_A;
  
  delay(1000);
}
