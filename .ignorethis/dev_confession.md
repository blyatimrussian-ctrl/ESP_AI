# 🛠️ Nightmares

This file exists because the Serial Monitor is the only thing that listens to me anymore.

---

## My confession

- I once spent 4 hours troubleshooting a WiFi connection only to realize I needed to fix the endpoint, then I turned my laptop into a 360 flip phone and twisted it a thousand times, no anesthesia.

- I know there's a memory leak in the JSON parser (i guess maybe there is). I’ve named it **Fucker**. Fucker and I have a tentative peace treaty where he only crashes the board after I've finished my sleep.

- This board is being normal now, which either means he's really normal or it’s plotting its revenge for when I’m finally emotionally attached to the uptime.

- I wrote this STUPID ASS code at 3:00AM. If you find any problem please fix it yourself :), please.

- The ESP32 rebooted so many times Windows now recognizes the disconnect sound as part of the project soundtrack.

- Sometimes the code works first try and that genuinely scares me more than the bugs.

- Every `HTTP 400` feels personal.

- I added more debug prints to fix the issue.  
  The issue is now hidden under 700 lines of `"Connecting..."`.

- The PSRAM has 8MB.  
And umm idk im tired

I have achieved enlightenment:

WiFi.status() != WL_CONNECTED
The board crashes less when I threaten it verbally.

There are two types of embedded developers:

liars
people using delay() in production

I am both.

The setInsecure() call is not laziness.
It is survival instinct.
I don't test edge cases.
I create them accidentally. by a viewer request
One day this project will become stable.
Today is not that day.
Removing one Serial.println() somehow changes the timing enough to break HTTPS.
I am no longer programming... or am i
I am performing dark rituals.

My ESP32 has:

dual core CPU
WiFi
Bluetooth
AI API access
8MB PSRAM

and still somehow loses arguments against a missing comma.

I opened the Serial Monitor for one quick test.
That was 6 hours ago.
The code compiles successfully which usually means the runtime failure will now be significantly more creative.

Brownout detector:
triggered

Me:
same

I said:
"I'll clean the code later"

The git history has determined that was a lie.

The ESP32 runs hotter during TLS handshakes than my old laptop running 17 Chrome tabs and Minecraft (dw i have a new laptop lolol) 

If the board works after the first flash:

don't touch it
don't look at it
don't even breathe near it

I fear no man.
But this line:

deserializeJson(resDoc, response);

It scares me.

I once fixed a bug by changing absolutely nothing and recompiling.
Embedded development is quantum mechanics with extra suffering.
The watchdog timer is not a safety feature anymore.
It's an execution method.
Every successful upload gives me false hope.
Every failed upload builds character.
Current Mental State
[||||||||--] 80% Fucked

System Status:

Component	State
WiFi	emotionally unstable
JSON Parser	leaking probably
Telegram Bot	typing... forever
HTTPS	held together with hope
PSRAM	screaming
Sleep Schedule	404 Not Found
Sanity	stack overflow
Laptop Fan	takeoff mode
ESP32	plotting
Serial Monitor	therapist
Brownout Detector	my biggest opp
Arduino IDE	hostage situation
USB Port	fighting for its life



"Embedded systems is just arguing with sand that learned electricity."

"99% of embedded developers quit right before the random bug fixes itself."

TODO
 Fix memory leak (i think there is)
 Fix WiFi reconnect logic
 Fix sleep schedule
 Stop hardcoding everything
 Figure out why removing one Serial.println() breaks TLS
 Touch grass
 Actually document the code instead of emotionally reacting to it
 Stop debugging at 3AM
 Find who invented JSON
 Ask the ESP32 nicely to cooperate

 If you think thisis corny then youve touched too much grass... BECAUSE THATS NOT WHAT EMBED DEVS DO.
