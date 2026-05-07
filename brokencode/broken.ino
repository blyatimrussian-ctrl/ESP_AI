/*THIS STUPID CODE IS FUCKING BROKEN THE
AI BROKE ALSO I AMIQWYFUWGEUFGWUGFUW
I HONESTLY DONT KNOW WHERE IS THE BROKEN PART
IF YALL NOTICE IT PLEASE REPORT IT TO ME.
IMMEDIETLY OKAY PLEASEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE*/

#include <WiFi.h>
#include <WiFiMulti.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>

// API and uhh stuff
WiFiMulti wifiMulti;

#define BOTtoken "your stupid telegram bot key"
#define GROQ_API_KEY "your stupid bot api key"

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

unsigned long lastTimeBotRan;
const unsigned long botMTBS = 1000;

// anti spam cooldown shi
unsigned long lastAiRequest = 0;
const unsigned long aiCooldown = 3000;

// max chars before esp32 cries
const int MAX_QUERY_LENGTH = 500;

// le ai function
String getGroqResponse(String query) {

  if (WiFi.status() != WL_CONNECTED) {
    return "WiFi Disconnected";
  }

  if (query.length() > MAX_QUERY_LENGTH) {
    return "Bro calm down thats too much text 💀";
  }

  WiFiClientSecure groqClient;
  groqClient.setInsecure();

  HTTPClient http;

  // esp32 tls demons prevention
  http.setReuse(false);
  http.setTimeout(15000);

  String url = "https://api.groq.com/openai/v1/chat/completions";

  if (!http.begin(groqClient, url)) {
    return "Connection Failed";
  }

  http.addHeader("Content-Type", "application/json");
  http.addHeader("Authorization", "Bearer " + String(GROQ_API_KEY));

  // fixed json sizing before heap goblin appears
  StaticJsonDocument<2048> doc;

  doc["model"] = "llama-3.3-70b-versatile";
  doc["temperature"] = 0.7;
  doc["max_tokens"] = 300;

  JsonArray messages = doc["messages"].to<JsonArray>();

  JsonObject msg1 = messages.add<JsonObject>();
  msg1["role"] = "user";
  msg1["content"] = query;

  String requestBody;
  requestBody.reserve(2048);

  serializeJson(doc, requestBody);

  Serial.println("\n========== REQUEST ==========");
  Serial.println(requestBody);
  Serial.println("=============================");

  int httpResponseCode = http.POST(requestBody);

  String result = "AI Error";

  Serial.print("HTTP CODE: ");
  Serial.println(httpResponseCode);

  if (httpResponseCode == HTTP_CODE_OK) {

    String response = http.getString();

    Serial.println("\n========== RESPONSE ==========");
    Serial.println(response);
    Serial.println("==============================");

    // larger buffer for ai response
    StaticJsonDocument<8192> resDoc;

    DeserializationError error = deserializeJson(resDoc, response);

    if (!error) {

      const char* content =
        resDoc["choices"][0]["message"]["content"];

      if (content) {

        result = String(content);

        // telegram hates ultra massive messages
        if (result.length() > 3500) {
          result = result.substring(0, 3500);
          result += "\n\n[Response trimmed because ESP32 got scared]";
        }

      } else {

        result = "Groq returned empty content.";

      }

    } else {

      result = "JSON Parsing Error: ";
      result += error.c_str();

      Serial.println("DESERIALIZE FAILED");
      Serial.println(error.c_str());
    }

  } else {

    result = "Groq Error: ";
    result += String(httpResponseCode);
    result += "\n";
    result += http.getString();
  }

  http.end();

  Serial.print("Free Heap: ");
  Serial.println(ESP.getFreeHeap());

  return result;
}



/*telegram stuff (please dont change any of this shi
you change it you fix it, YOURSELF)*/
void handleNewMessages(int numNewMessages) {

  for (int i = 0; i < numNewMessages; i++) {

    String chat_id = String(bot.messages[i].chat_id);
    String text = bot.messages[i].text;

    text.trim();

    Serial.println("\nNew Message: " + text);

    // local commands because yes
    if (text == "/start") {

      String welcome =
        "THIS THING IS ONLINE \n"
        "Model: llama-3.3-70b-versatile\n"
        "Heap: " + String(ESP.getFreeHeap()) + "\n"
        "PSRAM: " + String(ESP.getFreePsram());

      bot.sendMessage(chat_id, welcome, "");
      continue;
    }

    if (text == "/heap") {

      String heapInfo =
        "Free Heap: " + String(ESP.getFreeHeap()) +
        "\nFree PSRAM: " + String(ESP.getFreePsram());

      bot.sendMessage(chat_id, heapInfo, "");
      continue;
    }

    if (text == "/ping") {
      bot.sendMessage(chat_id, "pong 🗿", "");
      continue;
    }

    // anti spam
    if (millis() - lastAiRequest < aiCooldown) {
      bot.sendMessage(chat_id,
        "lemme thinkg",
        "");
      continue;
    }

    lastAiRequest = millis();

    bot.sendChatAction(chat_id, "typing");

    String aiReply = getGroqResponse(text);

    bot.sendMessage(chat_id, aiReply, "");
  }
}


/*very simple setup*/
void setup() {

  Serial.begin(115200);

  delay(1000);

  Serial.println("\nstarting this shi...");

  //3 wifi lmaoo just in case
  wifiMulti.addAP("YOUR_WIFI_SSID", "YOUR_WIFI_PASSWORD");
  wifiMulti.addAP("YOUR_WIFI_SSID", "YOUR_WIFI_PASSWORD");
  wifiMulti.addAP("YOUR_WIFI_SSID", "YOUR_WIFI_PASSWORD");

  Serial.print("Connecting WiFi");

  while (wifiMulti.run() != WL_CONNECTED) {

    delay(500);
    Serial.print(".");

  }

  Serial.println("\nWiFi Connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  configTime(0, 0, "pool.ntp.org", "time.nist.gov");

  Serial.print("Syncing Time");

  while (time(nullptr) < 1000000000) {

    delay(500);
    Serial.print(".");

  }

  Serial.println("\nTime Synced!");

  client.setInsecure();

  Serial.println("\n===== SYSTEM INFO =====");
  Serial.print("Free Heap: ");
  Serial.println(ESP.getFreeHeap());

  Serial.print("Free PSRAM: ");
  Serial.println(ESP.getFreePsram());

  Serial.print("CPU Freq: ");
  Serial.println(ESP.getCpuFreqMHz());

  Serial.println("=======================");

  Serial.println("Ready!");
}


/*Le loop (keep it untouched because idk)*/
void loop() {

  // wifi auto recovery because wifi likes dying
  if (WiFi.status() != WL_CONNECTED) {

    Serial.println("WiFi Lost Reconnecting...");

    while (wifiMulti.run() != WL_CONNECTED) {

      delay(500);
      Serial.print(".");

    }

    Serial.println("\nWiFi Reconnected!");
  }

  if (millis() > lastTimeBotRan + botMTBS) {

    int numNewMessages =
      bot.getUpdates(bot.last_message_received + 1);

  if (numNewMessages) {

  handleNewMessages(numNewMessages);

}

    lastTimeBotRan = millis();
  }
}
