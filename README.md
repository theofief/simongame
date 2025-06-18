# 🎮 Simon Game – ESP32 + Web Companion

A modern remake of the classic **Simon memory game**, combining:

- 🧠 A fully **autonomous ESP32-based physical game**
- 🌐 An optional **online web interface** for remote interaction
- 🧰 Custom 3D-printed case and fully open-source firmware

---

## 🧩 Project Overview

This project is a hybrid physical/digital experience:

### 🕹️ Physical Game (ESP32)
- Runs **standalone** with no computer required
- Features 4 buttons, 4 LEDs, a buzzer and game logic directly on the ESP32
- Fully interactive and playable in real life!

### 🌐 Web Interface (Companion)
- Accessible from any browser (desktop or mobile)
- Lets you control difficulty, check scores, and reset the game
- Multilingual (🇫🇷 French, 🇬🇧 English, 🇪🇸 Spanish)
- Connects to the ESP32 over local Wi-Fi (via HTTP/WebSocket)

---

## ⚙️ Features

✅ Classic Simon game logic  
✅ Standalone ESP32 gameplay  
✅ Optional remote control via browser  
✅ Sound feedback with buzzer  
✅ Multilingual UI (EN, FR, ES)  
✅ Multiple difficulty levels  
✅ Score tracking & error display  
✅ 3D printable case included

---

## 📁 Project Structure

```bash
📦 simon-game/
├── 🧠 hardware/
│   ├── simon.ino           # ESP32 firmware (Arduino IDE)
│   └── box-design.stl      # 3D printed enclosure
├── 🌐 web-interface/
│   ├── index.html          # Web companion UI
│   ├── style.css           # Web styling
│   └── script.js           # Web control logic
├── 📄 LICENSE              # MIT License
└── 📘 README.md            # Project description
```
## 🚀 How to Use

```🔌 Physical Game
	1.	Flash simon.ino to your ESP32 using Arduino IDE
	2.	Connect:
	•	4x LEDs to GPIOs
	•	4x Buttons
	•	1x Buzzer for feedback
	3.	Power the ESP32 and play directly!
```

```🌍 Web Interface
	1.	Open web-interface/index.html in a browser
	2.	Make sure your computer/phone is on the same network as the ESP32
	3.	Configure the ESP32’s IP in script.js
	4.	Use the UI to control and monitor the game remotely
```

## 📜 License

This project is under the MIT License.
Feel free to modify, share, and build on it!


Made with ❤️ by high school students passionate about tech
🎓 2025 Bachelor 1 Final Project
