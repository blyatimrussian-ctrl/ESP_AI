#include <WiFi.h>
#include <WiFiMulti.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>

// API and uhh stuff
WiFiMulti wifiMulti;
#define BOTtoken "the telegram bot api key" 
#define GROQ_API_KEY "the umm ai api key" // Replace with your actual Groq Key

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

unsigned long lastTimeBotRan;
const unsigned long botMTBS = 1000; 

// le ai function
String getGroqResponse(String query) {
  if (WiFi.status() != WL_CONNECTED) return "WiFi Disconnected";

  WiFiClientSecure groqClient;
  groqClient.setInsecure(); 
  
  HTTPClient http;
  

  String url = "https://api.groq.com/openai/v1/chat/completions";
  
  if (!http.begin(groqClient, url)) return "Connection Failed";
  
  http.addHeader("Content-Type", "application/json");
  http.addHeader("Authorization", "Bearer " + String(GROQ_API_KEY));

  JsonDocument doc;
  doc["model"] = "llama-3.3-70b-versatile";

  JsonArray messages = doc["messages"].to<JsonArray>();
  JsonObject msg1 = messages.add<JsonObject>();
  msg1["role"] = "user";
  msg1["content"] = query; 

  String requestBody;
  serializeJson(doc, requestBody);

  
  Serial.println("Sending JSON: " + requestBody);

  int httpResponseCode = http.POST(requestBody);
  String result = "AI Error";

  if (httpResponseCode == 200) {
    String response = http.getString();
    
    JsonDocument resDoc;
    DeserializationError error = deserializeJson(resDoc, response);
    
    if (!error) {
      
      const char* content = resDoc["choices"][0]["message"]["content"];
      if (content) {
        result = String(content);
      } else {
        result = "Groq returned empty content.";
      }
    } else {
      result = "JSON Parsing Error: " + String(error.c_str());
    }
  } else {
  
    result = "Groq Error: " + String(httpResponseCode) + " - " + http.getString();
  }
  
  http.end();
  return result;
}




 /*telegram stuff (please dont change any of this shi
 you change it you fix it, YOURSELF)*/
void handleNewMessages(int numNewMessages) {
  for (int i = 0; i < numNewMessages; i++) {
    String chat_id = String(bot.messages[i].chat_id);
    String text = bot.messages[i].text;
    
    bot.sendChatAction(chat_id, "typing");


    String aiReply = getGroqResponse(text);
    bot.sendMessage(chat_id, aiReply, "");
  }
}

/*very simple setup*/
void setup() {
  Serial.begin(115200);

  //3 wifi lmaoo just in case
  wifiMulti.addAP("passssid", "passwifi"); 
  wifiMulti.addAP("passssid", "passwifi"); 
  wifiMulti.addAP("passssid", "passwifi"); 
  Serial.print("Connecting WiFi...");
  while (wifiMulti.run() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Connected!");

  configTime(0, 0, "pool.ntp.org", "time.nist.gov");
  while (time(nullptr) < 1000000000) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nTime Synced!");

  client.setInsecure(); 
  Serial.println("Ready!");
}

/*Le loop (keep it untouched because idk)*/
void loop() {
  if (millis() > lastTimeBotRan + botMTBS)  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    while(numNewMessages) {
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
    lastTimeBotRan = millis();
  }
}
