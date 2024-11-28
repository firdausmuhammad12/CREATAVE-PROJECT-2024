// Kontrol jarak jauh berbasis Telegram
// By.MUHAMMAD FIRDAUS
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

// KREDENSIAL STASIUN JARINGAN WIFI
#define WIFI_SSID "P"
#define WIFI_PASSWORD "1122334455"
// Token BOT telegram (dapat dari BOTfather)
#define CHAT_ID "6638014975"
#define BOT_TOKEN "7131142949:AAG23rYMMRSPeHGLujcEkovTtPFW5weewm0"

const unsigned long BOT_MTBS = 1000; //waktu rata-rata pemindaian pesan

WiFiClientSecure secured_client;
UniversalTelegramBot bot(BOT_TOKEN, secured_client);
unsigned long bot_lasttime; // terakhir kali pemindaian pesan dilakukan
String chat_id = "6638014975";
const int ledPin = 27;
int ledStatus = 0;

void handleNewMessages(int numNewMessages)
{
  Serial.print("handleNewMessages ");
  Serial.println(numNewMessages);

  for (int i = 0; i < numNewMessages; i++)
  {
    String chat_id =  String(bot.messages[i].chat_id);
   
     if (chat_id != CHAT_ID)
    {
      bot.sendMessage(chat_id, "ANDA TIDAK MEMILIKI AKSES KE BOT INI!!!", "");
      continue;
    }
       String text = bot.messages[i].text;
    Serial.println(text);

    String from_name = bot.messages[i].from_name;
   
    if (text == "/Lamp.on")
    {
      digitalWrite(ledPin, LOW); // menyalaKan lampu(aktif LOW)
      ledStatus = 1;
      bot.sendMessage(chat_id, "Led is ON", "");
    }

    if (text == "/Lamp.off")
    {
      ledStatus = 0;
      digitalWrite(ledPin, HIGH); //MEMATIKAN LAMPU (AKTIF LOW)
      bot.sendMessage(chat_id, "Led is OFF", "");
    }

    if (text == "/Lamp.status")
    {
      if (ledStatus)
      {
        bot.sendMessage(chat_id, "Led is ON", "");
      }
      else
      {
        bot.sendMessage(chat_id, "Led is OFF", "");
      }
    }

    if (text == "/start")
    {
      String welcome = "SELAMAT DATANG, " + from_name + ".\n";
      welcome += "DI KONTROL JARAK JAUH BERBASIS TELERAM\n\n";
      welcome += "/Lamp.on : UNTUK MENYALAKAN LAMPU\n";
      welcome += "/Lamp.off : UNTUK MEMATIKAN LAMPU\n";
      welcome += "/Lamp.status : UNTUK MENGETAHUI KEADAAN LAMPU\n";
      bot.sendMessage(chat_id, welcome, "Markdown");
    }
  }
}


void setup()
{
  Serial.begin(115200);
  Serial.println();

  pinMode(ledPin, OUTPUT); // INISIALISASI BAHWA ledPin adala OUTPUT
  delay(10);
  digitalWrite(ledPin, HIGH); // MEMBERIKAN LOGIKA RENDAH PADA ledPin (Aktif LOW)
  //Mencoba terkoneksi pada jaringan WiFi:
  Serial.print("Connecting to Wifi SSID ");
  Serial.print(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  secured_client.setCACert(TELEGRAM_CERTIFICATE_ROOT); // Menambahkan sertifikat root untuk api.telegram.org
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.print("\nWiFi connected. IP address: ");
  Serial.println(WiFi.localIP());

  Serial.print("Retrieving time: ");
  configTime(0, 0, "pool.ntp.org"); // Mendapatkan waktu UTP melalui NTP
  time_t now = time(nullptr);
  while (now < 24 * 3600)
  {
    Serial.print(".");
    delay(100);
    now = time(nullptr);
  }
  Serial.println(now);
}

void loop()
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
