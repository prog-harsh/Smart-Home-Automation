#include <FirebaseESP8266.h>
#include<ESP8266WiFi.h>
#include<EEPROM.h>
FirebaseData firebaseData;


#define FIREBASE_HOST "smart-home-automation-1883d.firebaseio.com"
#define FIREBASE_AUTH "W2rjGNgst5sBwY6cJlRu4s0YPYQ4So10hkKxiyBW"
#define WIFI_SSID "Quarantine 5G"
#define WIFI_PASSWORD "Covid-19"
String VAL1, VAL2, VAL3, VAL4;

void setup()
{
 EEPROM.begin(512);
 pinMode(D0,OUTPUT);
 pinMode(D1,OUTPUT);
 pinMode(D2,OUTPUT);
 pinMode(D3,OUTPUT);
 digitalWrite(D0,HIGH);
 digitalWrite(D1,HIGH);
 digitalWrite(D2,HIGH);
 digitalWrite(D3,HIGH);
 
 Serial.begin(9600);
 WiFi.begin(WIFI_SSID,WIFI_PASSWORD);
 Serial.print("connecting");
 while (WiFi.status()!=WL_CONNECTED)
 {
  Serial.print(".");
  delay(500);
 }
 Serial.print("connected:");
 Serial.println(WiFi.localIP());

 VAL1 = char(EEPROM.read(0x0F));
 VAL2 = char(EEPROM.read(0x11));
 VAL3 = char(EEPROM.read(0x13));
 VAL4 = char(EEPROM.read(0x15));
 
 Serial.println(VAL1);
 Serial.println(VAL2);
 Serial.println(VAL3);
 Serial.println(VAL4);
 
 Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);
 Firebase.setString(firebaseData,"/DEVICE1",VAL1);
 Firebase.setString(firebaseData,"/DEVICE2",VAL2);
 Firebase.setString(firebaseData,"/DEVICE3",VAL3);
 Firebase.setString(firebaseData,"/DEVICE4",VAL4);

}

void writeString(int add,String data)
{

  for(int i=0;i<data.length();i++)
  {
    EEPROM.write(add+i,data[i]);
  }
  EEPROM.commit();
}


void loop()
{
  Firebase.reconnectWiFi(true);   
  Firebase.getString(firebaseData,"/DEVICE1");  
  VAL1= firebaseData.stringData();
  if(VAL1=="1")
  {
    digitalWrite(D0,HIGH);
    Serial.println("Device 1 OFF");
  }
  else if (VAL1=="0")
  {
    digitalWrite(D0,LOW);
    Serial.println("Device 1 ON");
  }

  Firebase.getString(firebaseData,"/DEVICE2");  
  VAL2= firebaseData.stringData();
  if(VAL2=="1")
  {
    digitalWrite(D1,HIGH);
    Serial.println("Device 2 OFF");
  }
  else if (VAL2=="0")
  {
    digitalWrite(D1,LOW);
    Serial.println("Device 2 ON");
  }

  Firebase.getString(firebaseData,"/DEVICE3");  
  VAL3= firebaseData.stringData();
  if(VAL3=="1")
  {
    digitalWrite(D2,HIGH);
    Serial.println("Device 3 OFF");
  }
  else if (VAL3=="0")
  {
    digitalWrite(D2,LOW);
    Serial.println("Device 3 ON");
  }

  Firebase.getString(firebaseData,"/DEVICE4");  
  VAL4= firebaseData.stringData();
  if(VAL4=="1")
  {
    digitalWrite(D3,HIGH);
    Serial.println("Device 4 OFF");
  }
  else if (VAL4=="0")
  {
    digitalWrite(D3,LOW);
    Serial.println("Device 4 ON");
  }
  
  writeString(0x0F,VAL1); 
  writeString(0x11,VAL2); 
  writeString(0x13,VAL3); 
  writeString(0x15,VAL4); 
}
