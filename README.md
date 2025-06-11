# IoT People Counter with ESP8266, Firebase & React

This project counts people entering and exiting a location using PIR (motion) sensors connected to an ESP8266. The counts are synced in real-time to Firebase Realtime Database and displayed on a live web dashboard built with React.

---

## Project Overview

- **Hardware**: ESP8266 (NodeMCU), 2x PIR motion sensors
- **Backend**: Firebase Realtime Database
- **Frontend**: React (Vite), Tailwind CSS
- **Functionality**:
  - Detects "entry" and "exit" motion events
  - Updates the count in real-time
  - Displays counts on a web dashboard
  - Supports counter reset with a button

---

## Hardware Setup

### Components:
- ESP8266 NodeMCU
- 2x PIR motion sensors
- Breadboard and jumper wires

### Wiring:
| PIR Sensor | ESP8266 Pin |
|------------|-------------|
| VCC        | 3V3         |
| GND        | GND         |
| OUT (Entry) | D2 (GPIO4)  |
| OUT (Exit)  | D5 (GPIO14) |

---

## Firebase Setup

1. Go to [Firebase Console](https://console.firebase.google.com)
2. Create a new project
3. Enable **Realtime Database** (in test mode for simplicity)
4. Note down your config:
   ```js
   const firebaseConfig = {
     apiKey: "YOUR_API_KEY",
     authDomain: "YOUR_PROJECT.firebaseapp.com",
     databaseURL: "https://YOUR_PROJECT.firebaseio.com",
     ...
   };
