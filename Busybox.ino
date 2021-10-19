#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>
#include <LiquidCrystal_I2C.h>
#include "config.h"

//const char fingerprint[] PROGMEM = "D7 FB 27 3B A9 97 C9 10 8F 58 95 30 DE B6 03 5B BD D3 66 1a";

#define ledRedPin D6
#define ledGreenPin D5

#define dip3 D8
#define dip2 D7
#define dip1 D4

LiquidCrystal_I2C lcd(0x27,16,2); 

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
}

void loop() {
  unsigned int UserID = 0;
  UserID = (digitalRead(dip3) << 2) + (digitalRead(dip2) << 1) + (digitalRead(dip1));

  lcd.setCursor(0,0);
  lcd.print("ID");

  if(UserID > 0) {
    lcd.setCursor(0,1);
    lcd.print("   ");
    lcd.setCursor(0,1);
    lcd.print(UserID);

    callhttps(UserID);
  } else {
    lcd.setCursor(0,1);
    lcd.print("Keine UserID");

    Serial.println("Keine UserID");
  }
  
  delay(2000);
}

void callhttps(int UserID){
  WiFiClientSecure httpsClient;
  httpsClient.setInsecure();

  if (!httpsClient.connect(host, httpsPort)) {
    Serial.println("Connection failed");    
    return;
  }

  Serial.println(String("UserID: ") + UserID);
  httpsClient.println(String("GET ") + url + UserID + " HTTP/1.0\r\n" + "Host: " + host + "\r\nConnection: close\r\n"); // HTTP 1.0 pour éviter les réponses découpées (chunked) / Use HTTP 1.0 to avoid chunked answers
  if (httpsClient.println() == 0) {
    Serial.println(F("ERROR : Failed to send request"));  
    return;
  }
  
  Serial.println(F("OK : Request sent"));
  int Retry = 0;
  while (httpsClient.connected() && Retry <= 15)  // Get header: "OK 200... " ==> need to add  header validity check (err 404, etc)
  {
    String line = httpsClient.readStringUntil('\n');
    if (line == "\r")
    {
      Serial.println("headers received");
      break;
    }
    Retry++;
  }

  String payload = "";
  Retry = 0;
  while (httpsClient.available() && Retry <= 1000)   // FOR NOW, JUST PRINT RECEIVED RAW JSON FILE, BUF FILE IS NOT COMPLETE !! (+/-1440 chars out of +/-54151 chars)
  {
    char c = httpsClient.read();
    payload.concat(c);
    Retry++;
  }

  // Disconnect
  httpsClient.stop();

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
    
  } else {
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
}
