# 🎮 Simon Game – ESP32 + Web Interface

A full-stack Simon Game project combining **a physical ESP32-based device**, a **3D-printed case**, and a **multilingual web interface**.  
Designed for fun and educational purposes, with score tracking, difficulty levels, and language support (French 🇫🇷, English 🇬🇧, Spanish 🇪🇸).

---

## 🧠 Project Overview

This Simon Game is a modern remake of the classic memory game, built with:

- 🧩 **Hardware**:  
  - ESP32 microcontroller  
  - 4 LEDs & 4 push buttons  
  - Buzzer for sound feedback  
  - 3D-printed case (STL included)  

- 🌐 **Web Interface** *(hosted or local)*:  
  - Built with HTML, CSS, JavaScript  
  - Controls difficulty & game mode  
  - Displays score and error messages  
  - Multilingual support: FR / EN / ES

- 📶 **Communication**:  
  - Wi-Fi connection between ESP32 and the web interface (via WebSocket or HTTP)  
  - Real-time synchronization

---

## 🔧 Features

- ✅ ESP32 logic for LED and button sequence
- ✅ Real-time gameplay with sound & light feedback
- ✅ Web interface to launch, stop or reset the game
- ✅ Language switcher (FR, EN, ES)
- ✅ Difficulty modes: Easy, Normal, Hard
- ✅ Score display and history
- ✅ Stylish, compact **3D-printed box design**

---

## 📦 Files & Structure

```bash
📁 simon-game/
├── 📁 hardware/
│   ├── simon.ino           # ESP32 firmware (Arduino IDE)
│   └── box-design.stl      # 3D printed case
├── 📁 web/
│   ├── index.html          # Main UI
│   ├── style.css           # Interface styling
│   └── script.js           # Game logic and communication
├── LICENSE                 # MIT License
└── README.md               # You're here!
