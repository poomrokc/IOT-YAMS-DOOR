#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#define WIFI_SSID "iPhone"
#define WIFI_PASSWORD "aaaaaaaa"
int incomingByte;
int lock=0;
char JSONmessageBuffer[300];
String id="Vsbk0BISDU3JQE4lrHNq";
void setup()
{
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(D5, INPUT);
  pinMode(D6, INPUT);
  pinMode(D7, INPUT);
  digitalWrite(LED_BUILTIN, LOW);
  delay(2000);
  wifiConnect();
}

void loop()
{  
  if(digitalRead(D5)==1)
    id="Vsbk0BISDU3JQE4lrHNq";
  if(digitalRead(D6)==1)
    id="IsvvrImUQQ7aOTYvdin4";
  if(digitalRead(D7)==1)
    id="QRwF25FKZKCEuP2cx06k";
  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();

    if((char)incomingByte=='0') {
      String g =setZero();
      lock=0;
    }
    if((char)incomingByte=='3')
      String g =shock();
  }
  if(lock==0&&getStat()=="false") {
    Serial.print("1");
    lock=1;
  }
  delay(10);
  
  if(WiFi.status() != WL_CONNECTED)
  {
    wifiConnect();
  }
  delay(10);
}

String getStat()
{
  StaticJsonBuffer<300> JSONbuffer;
  JsonObject& JSONencoder = JSONbuffer.createObject();
  JSONencoder["deviceID"] = id;
  JSONencoder.prettyPrintTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
  HTTPClient http; //Declare object of class HTTPClient
  http.begin("http://54.255.244.191/embed/getLock"); //Specify request destination
  http.addHeader("Content-Type", "application/json"); //Specify content-type header
  int httpCode = http.POST(JSONmessageBuffer); //Send the request
  String payload = http.getString(); //Get the response payload
  http.end(); //Close connection
  return payload;
}

String setZero()
{
  StaticJsonBuffer<300> JSONbuffer;
  JsonObject& JSONencoder = JSONbuffer.createObject();
  JSONencoder["deviceID"] = id;
  JSONencoder.prettyPrintTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
  HTTPClient http; //Declare object of class HTTPClient
  http.begin("http://54.255.244.191/embed/setZero"); //Specify request destination
  http.addHeader("Content-Type", "application/json"); //Specify content-type header
  int httpCode = http.POST(JSONmessageBuffer); //Send the request
  String payload = http.getString(); //Get the response payload
  http.end(); //Close connection
  return payload;
}

String shock()
{
  StaticJsonBuffer<300> JSONbuffer;
  JsonObject& JSONencoder = JSONbuffer.createObject();
  JSONencoder["deviceID"] = id;
  JSONencoder.prettyPrintTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
  HTTPClient http; //Declare object of class HTTPClient
  http.begin("http://54.255.244.191/embed/shock"); //Specify request destination
  http.addHeader("Content-Type", "application/json"); //Specify content-type header
  int httpCode = http.POST(JSONmessageBuffer); //Send the request
  String payload = http.getString(); //Get the response payload
  http.end(); //Close connection
  return payload;
}

void wifiConnect()
{
  digitalWrite(LED_BUILTIN, HIGH);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);             // Connect to the network
  int teller = 0;
  while (WiFi.status() != WL_CONNECTED)
  {                                       // Wait for the Wi-Fi to connect
    delay(1000);
  }
  digitalWrite(LED_BUILTIN, LOW);
}
