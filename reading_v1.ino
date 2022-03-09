/* This arduino code is sending data to mysql server */

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h> //multicast domain name server
#include <SPI.h> //Serial Peripheral Interface (SPI)

// defined pins
#define acs712 A0

long lastSample = 0;
long sampleSum =  0;
int sampleCount = 0;
float vpc = 4.8828125 ; //volt per count "convert count cycle into votages"
float readingData = 0;
float meterNumber = 1001;
float final_amperage = 0;


//wifi connection
const char* ssid = "UB";
const char* password = "12345678";

//WiFiClient client;
char server[] = "192.168.43.151";   //eg: 192.168.0.222
WiFiClient client;

void setup()
{
  Serial.begin(115200);
  delay(10);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin("UB", "12345678");

  while (WiFi.status() != WL_CONNECTED) { // IF wifi is connecting
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");

  // Start the server
  //  server.begin();
  Serial.println("Server started");
  Serial.print(WiFi.localIP());
  delay(1000);
  Serial.println("connecting...");

}   //Setup END



void loop()
{
  //RMS method 1
  //S means square M means Mean +=  R means root



  if (millis() > lastSample + 1) {
    //taking sample
    sampleSum +=  sq(analogRead(acs712) - 830);
    sampleCount++;
    lastSample = millis();

  }

  if (sampleCount == 1000 )
  {
    // Averaging stuff

    float mean = sampleSum / sampleCount ;
    float final_value = sqrt(mean);


    float miliVolt = final_value * vpc;
    float amperage = miliVolt / 186;
    final_amperage = amperage * 210;
    //Serial.println("The final RMS AMPERAGE is:" +  String(amperage) + "Approx WATTAGES is:" + String (final_amperage) + "." );


    sampleSum = 0;
    sampleCount = 0;

    readingData = final_amperage;// for correcting error
    Sending_To_phpmyadmindatabase();
    delay(30000); // interval

  }




}


void Sending_To_phpmyadmindatabase()   //CONNECTING WITH MYSQL
{

  if (client.connect(server, 80)) {
    Serial.println("connected");
    // Make a HTTP request:
    Serial.print("Your meterNumber is =");
    client.print("GET /reading_v1/reading_v1.php?meterNumber=");     //YOUR URL
    Serial.print(meterNumber);
    client.print(meterNumber);

    Serial.println(" ");

    client.print("&readingData=");
    Serial.print("Current load=");
    client.print(readingData);
    Serial.print(readingData);
    Serial.println(" ");
    Serial.println("--------------------------------------------------------------------");

    client.print(" ");      //SPACE BEFORE HTTP/1.1
    client.print("HTTP/1.1");
    client.println();
    client.println("Host: 192.168.43.151");
    client.println("Connection: close");
    client.println();
  } else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }


}
