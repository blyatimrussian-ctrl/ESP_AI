<!-- 
  DEV NOTE: 
  If I see one more 'error code:400' i will skin this stupid ESP32 S3
  N16R8 first by the pcb then split this in half. 
  The N16R8 has 8MB of PSRAM and yet my brain still runs out of memory 
  trying to remember why I Always put A false Endpoint or Non existing AI models. 
  God Help Me i am suffering.

  UPDATE:
  Turns out the endpoint was correct.
  The JSON wasn't.
  I spent 4 hours debugging a missing comma.
  Embedded development is just advanced self-harm with extra steps.
-->

# ESP_AI 🚀
This repository provides a streamlined implementation for running Large Language Models (LLMs) directly on the ESP32-S3 (N16R8). By leveraging the internal 16MB Flash and 8MB PSRAM, this setup handles API requests and JSON parsing efficiently, turning your microcontroller into an AI-powered edge device.

> "Why run AI on a microcontroller?"
>
> Because running a 70B model request from a chip smaller than your fingernail is objectively funny.

---

## 🛠️ Features

- **Hardware Optimized**  
  Specifically configured for the ESP32-S3 N16R8 to utilize extended PSRAM for handling large buffers.

- **API Integration**  
  Pre-configured for seamless communication with LLM providers (e.g., Gemini, Groq, or OpenAI).

- **Edge-to-Cloud**  
  Connects via WiFi to process complex queries that are normally impossible for standalone microcontrollers.

- **Lightweight**  
  Minimal overhead, focusing on raw performance and fast response times.

- **Mentally Unstable Debugging Included**  
  Experience the authentic embedded developer workflow:
  - Fix bug
  - Create 3 new bugs
  - Restart IDE
  - Cry
  - Works somehow

---

## 📋 Hardware Requirements

- **Microcontroller:** ESP32-S3 (N16R8 recommended or ummm N8R16 for more.. dwedicated wwam)

- **Connectivity:** 2.4GHz WiFi

- **Development Environment:** Arduino IDE or PlatformIO

- **Sanity:** Optional but strongly recommended

---

## 🚀 Getting Started

### 1. Installation

2. Configuration

Open the main project file and update your credentials.

#define BOTtoken "YOUR_BOT_TOKEN"
#define GROQ_API_KEY "YOUR_GROQ_API_KEY"

Also configure your WiFi:

wifiMulti.addAP("YOUR_WIFI_SSID", "YOUR_WIFI_PASSWORD");
⚙️ Recommended Board Settings

Ensure your board settings are correct in your IDE:

Board: ESP32S3 Dev Module
Flash Mode: QIO 80MHz (just use QIO 120MHz if you dont run a display)
Flash Size: 16MB
Flash Config: 16MB flash (3mb Flash / 9.9 FatFS)
PSRAM: OPI PSRAM (Required for N16R8)

Then flash it.

If uploading fails:

unplug
replug
hold BOOT
pray to the silicon gods
try again


## 🖥️ How It Works

The ESP32-S3 acts as a bridge. It captures user input (via Serial, sensors, or a web interface), packages it into a structured JSON payload, and sends an HTTPS POST request to the AI API.

The response is then parsed using ArduinoJson and can be:

displayed on an OLED
sent to Telegram
used to trigger hardware actions
or ignored entirely because the ESP rebooted from brownout again

## 💀 Current Code Behavior

What this thing currently does:
Connects to WiFi
Syncs time using NTP
Connects securely to Groq API
Sends prompts to llama-3.3-70b-versatile
Reads Telegram messages
Replies with AI-generated responses
What it sometimes also does:
Random TLS anger
HTTP 400 emotional damage
JSON parsing explosions
Infinite reconnect rituals
Guru Meditation moments straight from 1987

## 🛠️ Planned Improvements

 Integration with local voice-to-text (STT)
 Support for streaming responses to reduce latency
 UI support for small TFT/OLED displays
 Stop writing cursed networking code at 3AM
 Maybe make the ESP32 stop sounding like a jet engine internally
 
## ⚠️ Important Notes

setInsecure() is currently used for HTTPS because certificates are pain and suffering on embedded systems.
Large responses may consume significant PSRAM.
The ESP32-S3 is powerful...
but not "run ChatGPT locally" powerful.
If your board suddenly disappears from COM ports:
congratulations, you discovered USB driver roulette.

## 📄 License

Distributed under the GPL v3 License. See LICENSE for more information.

Final Words

This project exists because:

cloud AI is cool
embedded systems are cool
combining both is either genius or a cry for help

Probably both...
