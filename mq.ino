//import lib
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
const char *ssid = ""; //  your wifi ssid{NAME} wpa2 key'
const char *pass = "";//  your wifi wpa2 key'
WiFiClient client;
const int mqpin = A0; //MQ analog Pin I/O
float h;
void setup()
{
  Serial.begin(115200);      //Baud rate
  delay(100);
  Serial.println("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED)
{
  delay(500);
  Serial.print(".");
}
  Serial.println("");
  Serial.println("WiFi connected");
}
void loop()
{
  unsigned long currentMillis = millis(); 
  h = analogRead(A0);
  if (isnan(h))
  {
    Serial.println("Failed to read from MQ-5 sensor!");
    return;
  }

  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
    HTTPClient http;                   //Declare an object of class HTTPClient
    String url = "//your website URL with string"
    Serial.println(url);
    http.begin(client, url);          //Specify request destination
    int httpCode = http.GET();        //Send the request
    if (httpCode > 0) 
    {                   //Check the returning code
      String payload = http.getString();  //Get the request response payload
      Serial.println(payload);            //Print the response payload (updated database results)
    }
    http.end();  //Close connection
  }
}
