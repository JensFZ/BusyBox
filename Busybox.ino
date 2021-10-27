#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <HttpClient.h>
#include <ArduinoJson.h>
#include <LiquidCrystal_I2C.h>
#include "config.h"

//const char fingerprint[] PROGMEM = "D7 FB 27 3B A9 97 C9 10 8F 58 95 30 DE B6 03 5B BD D3 66 1a";

#define ledRedPin D6
#define ledGreenPin D5

#define dip3 D8
#define dip2 D7
#define dip1 D4

#define switchState D3

LiquidCrystal_I2C lcd(0x27,16,2); 
WiFiClient wifiClient;
void setup() {
  Serial.flush();

  lcd.init();
  lcd.backlight();
  
  lcd.setCursor(0,0);
  lcd.print("Init");
  
  // put your setup code here, to run once:

  pinMode(LED_BUILTIN, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
  digitalWrite(LED_BUILTIN, LOW);   // Turn the LED on (Note that LOW is the voltage level

  pinMode(ledRedPin, OUTPUT); //Declare Pin mode
  digitalWrite(ledRedPin, LOW); //Declare Pin mode
  
  pinMode(ledGreenPin, OUTPUT); //Declare Pin mode
  digitalWrite(ledGreenPin, LOW); //Declare Pin mode

  pinMode(dip3, INPUT);
  pinMode(dip2, INPUT);
  pinMode(dip1, INPUT);
  
  pinMode(switchState, INPUT);

  //attachInterrupt(digitalPinToInterrupt(switchState), callhttpSwitch, RISING);
  

//  client.setInsecure();
  Serial.begin(115200);
  Serial.println("Awake");

  Serial.print("Connecting to WiFi: ");
  Serial.println(ssid);

  lcd.setCursor(0,0);
  lcd.print("Connecting to:");
  lcd.setCursor(0,1);
  lcd.print(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("Connected!");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP()); 

  delay(500);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("IP:");
  lcd.setCursor(0,1);
  lcd.print(WiFi.localIP());
  delay(1500);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("ID");

}

bool buttonPressed = false;

bool aktiv = true;

int lastUserID = -1;
bool lastBacklight = true;

unsigned int UserID = 0;

 
void loop() {
  UserID = (digitalRead(dip3) << 2) + (digitalRead(dip2) << 1) + (digitalRead(dip1));

    if(UserID > 0) {
      if(lastUserID != UserID) {
        printUserID();
        lastUserID = UserID;
      }
      
      if(callAktiv()) {
        if(!lastBacklight) {
          lcd.backlight();
          lastBacklight = true;
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("ID");
          printUserID();

        }
        callBusy();
        delay(1000);
      } else {
        if(lastBacklight) {
          lcd.noBacklight();
          lcd.clear();
          lastBacklight = false;
        }
        digitalWrite(ledGreenPin, LOW);   //Turn the LED off
        digitalWrite(ledRedPin, LOW);   //Turn the LED off

        delay(30000);
      }
    } else {
      lcd.setCursor(0,1);
      lcd.print("Keine UserID");
      Serial.println("Keine UserID");
      
      delay(10000);
    }
}

void callhttpSwitch() {
  Serial.println("Button");
};

void printUserID() {
  lcd.setCursor(0,1);
  lcd.print("   ");
  lcd.setCursor(0,1);
  lcd.print(UserID);
}


bool callAktiv() {
  Serial.println("callAktiv");
  int err =0;
  HTTPClient http;
  
  String serverPath = serverNameAktiv + UserID;
  Serial.println(serverPath);
  
  http.begin(wifiClient, serverPath);
  int httpResponseCode = http.GET();
  if (httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    String payload = http.getString();
    Serial.println(payload);

    const size_t capacity = JSON_ARRAY_SIZE(5) + 5*JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(3) + 200;
    DynamicJsonDocument doc(capacity);
    deserializeJson(doc, payload);
    String Aktiv = doc["Aktiv"];
    Serial.println(Aktiv);
    return Aktiv == "true";
  }

  return false;
}

void callBusy(){
  int err =0;
  HTTPClient http;
  Serial.println(String("UserID: ") + UserID);
  String serverPath = serverNameBusy + UserID;

  Serial.println(serverPath);
  http.begin(wifiClient, serverPath);

  int httpResponseCode = http.GET();
  if (httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    String payload = http.getString();
    Serial.println(payload);

    const size_t capacity = JSON_ARRAY_SIZE(5) + 5*JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(3) + 200;
    DynamicJsonDocument doc(capacity);
    deserializeJson(doc, payload);

    String amTelefon = doc["amTelefon"];
    Serial.println("amTelefon: " + amTelefon);
    if(amTelefon == "false") {
      digitalWrite(ledGreenPin, HIGH);   //Turn the LED off
      digitalWrite(ledRedPin, LOW);   //Turn the LED off
  
      lcd.setCursor(3,0);
      lcd.print("      ");
      lcd.setCursor(3,1);
      lcd.print("            ");
      
    } else if(amTelefon == "true"){
      digitalWrite(ledGreenPin, LOW);   //Turn the LED off
      digitalWrite(ledRedPin, HIGH);   //Turn the LED off
  
      char Zeit[20];
      int Total = doc["seit"];
      int Tage = Total / 86400;
      Total = Total % 86400;
      int Stunden = Total / 3600;
      Total = Total % 3600;
      int Minuten = Total / 60;
      int Sekunden = Total % 60;
      
      Serial.println("Tage: " + String(Tage));
      Serial.println("Stunden: " + String(Stunden));
      Serial.println("Minuten: " + String(Minuten));
      Serial.println("Sekunden: " + String(Sekunden));
  
      if(Tage > 0) {
        sprintf(Zeit, "%01d:%02d:%02d:%02d", Tage, Stunden, Minuten, Sekunden);
      } else if(Stunden > 0) {
        sprintf(Zeit, "%02d:%02d:%02d", Stunden, Minuten, Sekunden);
      } else {
        sprintf(Zeit, "%02d:%02d", Minuten, Sekunden);
      }
  
      lcd.setCursor(3,0);
      lcd.print("| Zeit");
      lcd.setCursor(3,1);
      lcd.print("| " + String(Zeit));
    
    }
        
  } else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  http.end();
}
