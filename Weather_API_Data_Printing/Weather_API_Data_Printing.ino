#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

const char* ssid = "PTCL-BB";
const char* password = "c7f74a18";

WiFiClient client;
HTTPClient http;

WiFiServer server(80);
String payload;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println();
  Serial.println("Connecting to Wifi");
  Serial.println(ssid);
  Serial.println();
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED){
    delay(1000);
    Serial.print("*");
  }
  Serial.println();
  Serial.println("Connected to Wifi");
  Serial.println(WiFi.localIP());

  server.begin();

  http.begin(client, "api.openweathermap.org",80,"/data/2.5/weather?q=Lahore&appid=157302c3fdf655fe54af952aa71e4c30");
  http.GET();

  payload = http.getString();
  Serial.println(payload);
  http.end();
}

void loop() {
  // put your main code here, to run repeatedly:
  WiFiClient client = server.available();
  if(!client){
    return;
  }

  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }

  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();

  client.println(payload);
  delay(1);
}
