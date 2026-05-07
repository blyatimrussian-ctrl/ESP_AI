<!-- 
  DEV NOTE: 
  If I see one more 'error code:400' i will skin this stupid ESP32 S3
  N16R8 first by the pcb then split this in half. 
  The N16R8 has 8MB of PSRAM and yet my brain still runs out of memory 
  trying to remember why I Always put A false Endpoint or Non existing AI models. 
  God Help Me i am suffering.
-->

ESP_AI 🚀
This repository provides a streamlined implementation for running Large Language Models (LLMs) directly on the ESP32-S3 (N16R8). By leveraging the internal 16MB Flash and 8MB PSRAM, this setup handles API requests and JSON parsing efficiently, turning your microcontroller into an AI-powered edge device.

🛠️ Features
Hardware Optimized: Specifically configured for the ESP32-S3 N16R8 to utilize extended PSRAM for handling large buffers.

API Integration: Pre-configured for seamless communication with LLM providers (e.g., Gemini, Groq, or OpenAI).

Edge-to-Cloud: Connects via WiFi to process complex queries that are normally impossible for standalone microcontrollers.

Lightweight: Minimal overhead, focusing on raw performance and fast response times.

📋 Hardware Requirements
Microcontroller: ESP32-S3 (N16R8 recommended or ummm N8R16 for more.. dwedicated wwam)

Connectivity: 2.4GHz WiFi

Development Environment: Arduino IDE or PlatformIO

🚀 Getting Started
1. Installation
Clone this repository to your local machine:

2. Configuration
Open the main project file and update your credentials
Ensure your board settings are correct in your IDE:

Board: ESP32S3 Dev Module

Flash Mode: QIO 80MHz

Flash Size: 16MB

Flash Config: 16MB flash (3mb Flash / 9.9 FatFS)

PSRAM: OPI PSRAM (Required for N16R8)

Then flash it.

🖥️ How It Works
The ESP32-S3 acts as a bridge. It captures user input (via Serial, sensors, or a web interface), packages it into a structured JSON payload, and sends an HTTPS POST request to the AI API. The response is then parsed using ArduinoJson and can be displayed on an OLED or used to trigger hardware actions.

🛠️ Planned Improvements
[ ] Integration with local voice-to-text (STT).

[ ] Support for streaming responses to reduce latency.

[ ] UI support for small TFT/OLED displays.

📄 License
Distributed under the GPL v3 License. See LICENSE for more information.

Note: This project is built for high-performance hardware hacking. Ensure your power supply can handle the WiFi bursts during API calls!
