/*******************************************************************
    A telegram bot for your ESP32 that controls the 
    onboard LED. The LED in this example is active low.

    Parts:
    ESP32 D1 Mini stlye Dev board* - http://s.click.aliexpress.com/e/C6ds4my
    (or any ESP32 board)

      = Affilate

    If you find what I do useful and would like to support me,
    please consider becoming a sponsor on Github
    https://github.com/sponsors/witnessmenow/


    Written by Brian Lough
    YouTube: https://www.youtube.com/brianlough
    Tindie: https://www.tindie.com/stores/brianlough/
    Twitter: https://twitter.com/witnessmenow
 *******************************************************************/

#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#define TEMPO_ESPERA_SENSOR 100
// Wifi network station credentials
#define WIFI_SSID "P"
#define WIFI_PASSWORD "1122334455"

// Telegram BOT Token (Get from Botfather)
#define CHAT_ID "6638014975"
#define BOT_TOKEN "7131142949:AAG23rYMMRSPeHGLujcEkovTtPFW5weewm0"


const unsigned long BOT_MTBS = 1000; // mean time between scan messages

WiFiClientSecure secured_client;
UniversalTelegramBot bot(BOT_TOKEN, secured_client);
unsigned long bot_lasttime; // last time messages' scan has been done
#include "DHT.h"

// Deklarasi sensor DHT22
#define DHTPIN 12
#define DHTTYPE DHT11   // DHT 22  (AM2302), AM2321
DHT dht(DHTPIN, DHTTYPE);
float temperature = dht.readTemperature();
String chat_id = "6638014975";

// -----

String getReadings(){
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  String message = "Temperature: " + String(temperature) + " ºC \n";
  message += "Humidity: " + String (humidity) + " % \n";
  return message;
}
const int led_1 = 27;
const int led_2 = 26;
const int led_3 = 25;
const int led_4 = 33;
int ledStatus = 0;


void setup()
{
  Serial.begin(115200);
  Serial.println();
 dht.begin();
  pinMode(led_1, OUTPUT);
   pinMode(led_2, OUTPUT);
    pinMode(led_3, OUTPUT);
     pinMode(led_4, OUTPUT);// initialize digital ledPin as an output.
  delay(10);
  digitalWrite(led_1, HIGH);
  digitalWrite(led_2, HIGH);
  digitalWrite(led_3, HIGH);
  digitalWrite(led_4, HIGH);
  // initialize pin as off (active LOW)

  // attempt to connect to Wifi network:
  Serial.print("Connecting to Wifi SSID ");
  Serial.print(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  secured_client.setCACert(TELEGRAM_CERTIFICATE_ROOT); // Add root certificate for api.telegram.org
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.print("\nWiFi connected. IP address: ");
  Serial.println(WiFi.localIP());

  Serial.print("Retrieving time: ");
  configTime(0, 0, "pool.ntp.org"); // get UTC time via NTP
  time_t now = time(nullptr);
  while (now < 24 * 3600)
  {
    Serial.print(".");
    delay(100);
    now = time(nullptr);
  }
  Serial.println(now);
}
void handleNewMessages(int numNewMessages)
{
  Serial.print("handleNewMessages ");
  Serial.println(numNewMessages);

  for (int i = 0; i < numNewMessages; i++)
  {
     String chat_id = String(bot.messages[i].chat_id);
    if (chat_id != CHAT_ID)
    {
      bot.sendMessage(chat_id, "Unauthorized user", "");
      continue;
    }
    
    // Print the received message
    String text = bot.messages[i].text;
    Serial.println(text);

    String from_name = bot.messages[i].from_name;


 if (text == "/temp&humid") 
    {
      String readings = getReadings();
      bot.sendMessage(chat_id, readings, "");
    }  
    if (text == "/led1on")
    {
      digitalWrite(led_1, LOW); // turn the LED on (HIGH is the voltage level)
      ledStatus = 1;
      bot.sendMessage(chat_id, "Led1 is ON", "");
    }

    if (text == "/led1off")
    {
      ledStatus = 0;
      digitalWrite(led_1, HIGH); // turn the LED off (LOW is the voltage level)
      bot.sendMessage(chat_id, "Led1 is OFF", "");
    }

    if (text == "/status1")
    {
      if (ledStatus)
      {
        bot.sendMessage(chat_id, "Led1 is ON", "");
      }
      else
      {
        bot.sendMessage(chat_id, "Led1 is OFF", "");
      }
    }
     if (text == "/led2on")
    {
      digitalWrite(led_2, LOW); // turn the LED on (HIGH is the voltage level)
      ledStatus = 1;
      bot.sendMessage(chat_id, "Led2 is ON", "");
    }

    if (text == "/led2off")
    {
      ledStatus = 0;
      digitalWrite(led_2, HIGH); // turn the LED off (LOW is the voltage level)
      bot.sendMessage(chat_id, "Led2 is OFF", "");
    }

    if (text == "/status2")
    {
      if (ledStatus)
      {
        bot.sendMessage(chat_id, "Led2 is ON", "");
      }
      else
      {
        bot.sendMessage(chat_id, "Led2 is OFF", "");
      }
    }

 if (text == "/led3on")
    {
      digitalWrite(led_3, LOW); // turn the LED on (HIGH is the voltage level)
      ledStatus = 1;
      bot.sendMessage(chat_id, "Led3 is ON", "");
    }

    if (text == "/led3off")
    {
      ledStatus = 0;
      digitalWrite(led_3, HIGH); // turn the LED off (LOW is the voltage level)
      bot.sendMessage(chat_id, "Led3 is OFF", "");
    }

    if (text == "/status3")
    {
      if (ledStatus)
      {
        bot.sendMessage(chat_id, "Led3 is ON", "");
      }
      else
      {
        bot.sendMessage(chat_id, "Led3 is OFF", "");
      }
    }

 if (text == "/led4on")
    {
      digitalWrite(led_4, LOW); // turn the LED on (HIGH is the voltage level)
      ledStatus = 1;
      bot.sendMessage(chat_id, "Led4 is ON", "");
    }

    if (text == "/led4off")
    {
      ledStatus = 0;
      digitalWrite(led_4, HIGH); // turn the LED off (LOW is the voltage level)
      bot.sendMessage(chat_id, "Led4 is OFF", "");
    }

    if (text == "/status4")
    {
      if (ledStatus)
      {
        bot.sendMessage(chat_id, "Led4 is ON", "");
      }
      else
      {
        bot.sendMessage(chat_id, "Led4 is OFF", "");
      }
    }
     if (text == "/allon")
    {
      digitalWrite(led_1, LOW);
       digitalWrite(led_2, LOW);
        digitalWrite(led_3, LOW);
         digitalWrite(led_4, LOW);// turn the LED on (HIGH is the voltage level)
   
      bot.sendMessage(chat_id, "Led all is ON", "");
    }

    if (text == "/alloff")
    {
      digitalWrite(led_1, HIGH);
      digitalWrite(led_2, HIGH);
      digitalWrite(led_3, HIGH);
      digitalWrite(led_4, HIGH);// turn the LED off (LOW is the voltage level)
      bot.sendMessage(chat_id, "Led all is OFF", "");
    }

    if (text == "/status all")
    {
      if(ledStatus)
      {
        bot.sendMessage(chat_id, "Led1 is ON", "");
      }
      else
      {
        bot.sendMessage(chat_id, "Led all is OFF", "");
      }
    }
 
    if (text == "/start")
    {
      String welcome = "wilujeung sumping, " + from_name + ".\n";
      welcome += "smart home muhammad firdaus\n\n";
      welcome += "/led1on : to switch the Led1 ON\n";
      welcome += "/led1off : to switch the Led1 OFF\n";
       welcome += "/status1 : Returns current status of LED1\n";
        welcome += "/led2on : to switch the Led2 ON\n";
      welcome += "/led2off : to switch the Led2 OFF\n";
       welcome += "/status2 : Returns current status of LED2\n";
        welcome += "/led3on : to switch the Led3 ON\n";
      welcome += "/led3off : to switch the Led3 OFF\n";
       welcome += "/status3 : Returns current status of LED3\n";
        welcome += "/led4on : to switch the Led4 ON\n";
      welcome += "/led4off : to switch the Led4 OFF\n";
       welcome += "/status4 : Returns current status of LED4\n";
      welcome += "/allon : to switch all the Led ON\n";
      welcome += "/alloff : to switch all the Led OFF\n";
      welcome += "/status all : Returns current status of all LED\n";
      welcome += "/temp&humid : for read the temperature and humidity\n";
      bot.sendMessage(chat_id, welcome, "Markdown");
    }
    }
  }
void loop(){
{
  if (millis() - bot_lasttime > BOT_MTBS)
  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while (numNewMessages)
    {
      Serial.println("got response");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }

    bot_lasttime = millis();
  }
}
float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Check if any reads failed and exit early (to try again).
  if (isnan(temperature) || isnan(humidity)) 
  { 
    //isnan = is NOT A NUMBER which return true when it is not a number
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  Serial.print(F("Humidity: "));
  Serial.print(humidity);
  Serial.print(F("%  Temperature: "));
  Serial.print(temperature);
  Serial.println(F("°C "));

  if (dht.readTemperature() >= 60)
  {
    String potensiKebakar = "Suhu diatas 60";
    bot.sendMessage(chat_id, potensiKebakar, "");
  }
  delay(1000);
  //akhir dari membaca sensor DHT22

  if (millis() - bot_lasttime > BOT_MTBS)
  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while (numNewMessages)
    {
      Serial.println("got response");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }

    bot_lasttime = millis();
  }
}
