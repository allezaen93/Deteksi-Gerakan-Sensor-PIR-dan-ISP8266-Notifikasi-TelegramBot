/*******************************************************************
*  An example of bot that echos back any messages received         *
*                                                                  *
*  written by Giacarlo Bacchio (Gianbacchio on Github)             *
*  adapted by Brian Lough
*  Modification Source By Alle Zaen - teknologi.or.id              *
*******************************************************************/
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

// Initialize Wifi connection to the router
char ssid[] = "ESSID";     // your network SSID (name)
char password[] = "PASSWORD-WIFI"; // your network key

// Initialize Telegram BOT
#define BOTtoken "3766xxxxx:AAF7_g1ytgSkqfDcfoEAYf2Qxxxxxx"  // your Bot Token (Get from Botfather) 30215344 (My Chat ID)


WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

int Bot_mtbs = 1000; //mean time between scan messages
long Bot_lasttime;   //last time messages' scan has been done
int ledPin = D1;                // choose the pin for the LED
int inputPin = D4;               // choose the input pin (for PIR sensor)
int pirState = LOW;             // we start, assuming no motion detected
int val = 0;                    // variable for reading the pin status
//int pinSpeaker = 10;           //Set up a speaker on a PWM pin (digital 9, 10, or 11)


void setup() {
  Serial.begin(115200);

  // Set WiFi to station mode and disconnect from an AP if it was Previously
  // connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  // Attempt to connect to Wifi network:
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  for (int i=0; i++;) {
  String chat_id = String(bot.messages[i].chat_id);
  String text = bot.messages[i].text;
  val = digitalRead(inputPin);              // read input value
    if (val == HIGH) {                      // check if the input is HIGH
      digitalWrite(ledPin, HIGH);           // turn LED ON
      //playTone(300, 160);
      delay(150);
      if (pirState == LOW) {                // we have just turned on
        Serial.println("Motion detected!"); // We only want to print on the output change, not state
        pirState = HIGH;
        bot.sendMessage("Motion Detected..!", "");
      }
    } else {
        digitalWrite(ledPin, LOW);          // turn LED OFF
        delay(300);                         // playTone(0, 0);
        if (pirState == HIGH){              // we have just turned of
        Serial.println("Motion ended!");    // We only want to print on the output change, not state
        pirState = LOW;
      }
  }
  
  if (millis() > Bot_lasttime + Bot_mtbs)  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while(numNewMessages) {
      Serial.println("got response");
      for (int i=0; i<numNewMessages; i++) {
        bot.sendMessage(bot.messages[i].chat_id, bot.messages[i].text, "");
      }
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }

    Bot_lasttime = millis();
    }
  }
}
