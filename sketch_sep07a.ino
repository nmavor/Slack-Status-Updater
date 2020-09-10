/*******************************************************************
    Sets a custom status on your slack account.
    
    By Becky Stern
    Based on Brian Lough's ArduinoSlackAPI library examples
    https://github.com/witnessmenow/arduino-slack-api

    You will need a Slack bearer token, see library readme for more details

    You will also need to be on version 2.5 or higher of the ESP8266 core

 *******************************************************************/
/////////////////////////////////////////////////////////////////
// ----------------------------
// Standard Libraries
// ----------------------------

#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include "ESPRotary.h";

// ----------------------------
// Additional Libraries - each one of these will need to be installed.
// ----------------------------

#include <ArduinoSlack.h>
// Library for connecting to the Slack API

// Install from Github
// https://github.com/witnessmenow/arduino-slack-api

#include <ArduinoJson.h>
// Library used for parsing Json from the API responses

// Search for "Arduino Json" in the Arduino Library manager
// https://github.com/bblanchon/ArduinoJson

/////////////////////////////////////////////////////////////////

#define ROTARY_PIN1  12
#define ROTARY_PIN2 13

#define CLICKS_PER_STEP   4   // this number depends on your rotary encoder 
#define MIN_POS   0
#define MAX_POS   20

int Status = 0;
String dir;

/////////////////////////////////////////////////////////////////

ESPRotary r = ESPRotary(ROTARY_PIN1, ROTARY_PIN2, CLICKS_PER_STEP);

/////////////////////////////////////////////////////////////////
//------- Replace the following! ------

char ssid[] = "AAAAAAAA";         // your network SSID (name)
char password[] = "BBBBBBBBBB"; // your network password

#define SLACK_ACCESS_TOKEN "CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC"

//------- ---------------------- ------

WiFiClientSecure client;
ArduinoSlack slack(client, SLACK_ACCESS_TOKEN);

//unsigned long delayBetweenRequests = 15000; // Time between requests
unsigned long delayBetweenRequests = 150; // Time between requests

unsigned long requestDueTime;               // time when request 


void setup() {
  Serial.begin(9600);
  delay(50);
  
  r.setLeftRotationHandler(Direction);
  r.setRightRotationHandler(Direction);

  // Set WiFi to station mode and disconnect from an AP if it was Previously
  // connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  // Attempt to connect to Wifi network:
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
      Serial.print(".");
      delay(500);
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  IPAddress ip = WiFi.localIP();
  Serial.println(ip);

  client.setFingerprint(SLACK_FINGERPRINT);

  // If you want to enable some extra debugging
  // uncomment the "#define SLACK_ENABLE_DEBUG" in ArduinoSlack.h

}

void displayProfile(SlackProfile profile)
{
    if (!profile.error)
    {
        Serial.println("--------- Profile ---------");

    
        Serial.print("Display Name: ");
        Serial.println(profile.displayName);

        Serial.print("Status Text: ");
        Serial.println(profile.statusText);

        Serial.print("Status Emoji: ");
        Serial.println(profile.statusEmoji);

        Serial.print("Status Expiration: ");
        Serial.println(profile.statusExpiration);

        Serial.println("------------------------");
    } else {
        Serial.println("error getting profile");
    }
}

void loop() {
  r.loop();
}

/////////////////////////////////////////////////////////////////

// on change
//void rotate(ESPRotary& r) {
////   Serial.println(r.getPosition());
//    Serial.println("asdasd");
//}

// on left or right rotation
void Direction(ESPRotary& r) {
  Serial.println(r.directionToString(r.getDirection()));
  if (Status == 19 &&  r.directionToString(r.getDirection()) == "RIGHT") {
    Status = 0;
  }else if (r.directionToString(r.getDirection()) == "RIGHT") {
    Status ++ ;
  }else if (Status == 0 &&  r.directionToString(r.getDirection()) == "LEFT") {
    Status = 19;
  }
  else if (r.directionToString(r.getDirection()) == "LEFT") {
    Status -- ;
  }
  Serial.println(Status);
  if (millis() > requestDueTime)
        {
          SlackProfile profile;
          switch (Status) {
            case 0:
             profile = slack.setCustomStatus("I am the 0 status", ":sparkling_heart:");
             break;
            case 1:
              profile = slack.setCustomStatus("I am the 1 status", ":v:");
              // There is an optional third parameter which takes a Unix timestamp for
              // when this custom status expires:
              // slack.setCustomStatus("I am the second status", ":v:", 1532627506);
              break;
            case 2:
              profile = slack.setCustomStatus("I am the 2 status", ":sunglasses:");
              break;
            case 3:
              profile = slack.setCustomStatus("I am the 3 status", ":dog2:");
              break;
            case 4:
              profile = slack.setCustomStatus("I am the 4 status", ":palm_tree:");
              break;
            case 5:
              profile = slack.setCustomStatus("I am the 5 status", ":soon:");
              break;
            case 6:
              profile = slack.setCustomStatus("I am the 6 status", ":v:");
              break;
            case 7:
              profile = slack.setCustomStatus("I am the 7 status", ":sunglasses:");
              break;
            case 8:
              profile = slack.setCustomStatus("I am the 8 status", ":dog2:");
              break;
            case 9:
              profile = slack.setCustomStatus("I am the 9 status", ":palm_tree:");
              break;
            case 10:
              profile = slack.setCustomStatus("I am the 10 status", ":soon:");
              break;
            case 11:
              profile = slack.setCustomStatus("I am the 11 status", ":v:");
              break;
            case 12:
              profile = slack.setCustomStatus("I am the 12 status", ":sunglasses:");
              break;
            case 13:
              profile = slack.setCustomStatus("I am the 13 status", ":dog2:");
              break;
            case 14:
              profile = slack.setCustomStatus("I am the 14 status", ":palm_tree:");
              break;
            case 15:
              profile = slack.setCustomStatus("I am the 15 status", ":soon:");
              break;
            case 16:
              profile = slack.setCustomStatus("I am the 16 status", ":sunglasses:");
              break;
            case 17:
              profile = slack.setCustomStatus("I am the 17 status", ":dog2:");
              break;
            case 18:
              profile = slack.setCustomStatus("I am the 18 status", ":palm_tree:");
              break;
            case 19:
              profile = slack.setCustomStatus("I am the 19 status", ":soon:");
              break;
          }
            displayProfile(profile);
            requestDueTime = millis() + delayBetweenRequests;
        }
}


/////////////////////////////////////////////////////////////////
