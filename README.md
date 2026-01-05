# IoT Servo-Based Parking / Gate Control System

This repository contains a **completed IoT group assignment** demonstrating a modular **servo-controlled parking/gate system** built with Arduino and an **edge computing layer** (Raspberry Pi / VirtualBox), with optional web-based control.

The project is designed so that **each component can run independently**, while still supporting full system integration.

---

## System Architecture

[ Ultrasonic Sensor ]

|

Arduino (.ino)
(Real-time control)

|

USB Serial

|

Edge Device (Python)

(Flask / PubSub Logic)

|

HTTP / Messaging

|

Web Interface
(HTML / CSS UI)

**Design intent**
- Arduino handles **real-time sensing and actuation**
- Edge device handles **communication, control, and UI integration**
- Web interface provides **human interaction**

---

## Arduino Firmware (`.ino`)

These files are flashed directly to the Arduino using the Arduino IDE.

### `servo/servo.ino` — Ultrasonic Servo Gate Controller
- Uses an ultrasonic sensor (TRIG `6`, ECHO `7`) to measure distance
- Automatically opens a servo motor (pin `9`) when an object is detected between **5–10 cm**
- Closes the servo when the object leaves and logs detection duration
- Supports **remote control via Serial commands**:
  - `9` → Open gate  
  - `19` → Close gate  

This sketch represents the **main integrated device logic**.

---

### `led/led.ino` — IR Sensor Reader (Standalone)
- Reads a digital IR sensor (XC4524) on pin `13`
- Outputs `0` / `1` via Serial (9600 baud)
- Used for sensor validation and input testing

---

### `led_sensor/led_sensor.ino` — Serial-Controlled LED (Standalone)
- Controls an LED on pin `3`
- Listens for Serial input:
  - `'1'` → LED ON  
  - `'0'` → LED OFF  

Demonstrates actuator control via serial communication.

---

## Edge / Raspberry Pi Code (`.txt`)

Some source files are stored as `.txt` due to **academic submission requirements**. These files were executed on a **Raspberry Pi (VirtualBox)** and form the edge layer.

### Python / Edge Scripts
- `flaskforservo.txt`  
  Python Flask application that sends serial commands to the Arduino (e.g. `9`, `19`) and enables control via a web interface.

- `phytoncodeforedgesubscribe.txt`  
- `phytoncodeforservoedge.txt`  
  Python edge scripts that subscribe to messages (pub/sub style) and translate them into Arduino serial commands.

---

## Web Interface (`.txt`)
- `website.txt` — HTML frontend  
- `websitecss.txt` — CSS styling  

Provides a simple UI that communicates with the Flask backend to control the servo system.

---

## Key Concepts Demonstrated
- Modular IoT design (sensor-only, actuator-only, integrated device)
- Serial communication between microcontroller and edge device
- Edge computing using Python and Flask
- Separation of real-time hardware logic and network logic
- Simple command protocol for remote device control

---

## Notes
- Each module can be executed **independently** for testing and demonstration
- File naming reflects **submission constraints**, not production structure
- This repository is intended as a **learning and demonstration project**

---
