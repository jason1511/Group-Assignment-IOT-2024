# IoT Mini Parking & Servo Control (Group Assignment)

This repository contains a **completed group IoT assignment** demonstrating Arduino-based hardware control integrated with an **edge computing layer (Raspberry Pi / VirtualBox)** and a **simple web interface**.

The project is intentionally modular: each Arduino sketch and edge script can be executed **independently**, or combined into a full system.

---

## High-Level Architecture

Sensors / Actuators

|

(Serial)

|

Arduino (.ino)

|

USB Serial

|

Edge Device (Python / Flask / PubSub)

|

HTTP / Messaging

|

Web Interface


- **Arduino** handles real-time sensing and actuation  
- **Edge device** handles control logic and communication  
- **Web UI** provides human interaction

---

## Arduino Firmware (`.ino`)

These files are flashed directly to the Arduino using the Arduino IDE.

### `led/led.ino` — IR Sensor Reader
- Reads a digital IR sensor (XC4524) on pin `13`
- Outputs `0` / `1` via Serial (9600 baud)
- Used for validating sensor detection and wiring

---

### `led_sensor/led_sensor.ino` — Serial-Controlled LED
- Controls an LED on pin `3`
- Listens for Serial commands:
  - `'1'` → LED ON  
  - `'0'` → LED OFF

This sketch demonstrates actuator control via serial communication.

---

### `servo/servo.ino` — Ultrasonic Servo Gate Controller
- Uses an ultrasonic sensor (TRIG `6`, ECHO `7`) for distance measurement
- Automatically opens a servo motor (pin `9`) when an object is detected between **5–10 cm**
- Closes the servo when the object leaves and logs detection duration
- Supports **remote control via Serial**:
  - `9` → Open gate  
  - `19` → Close gate  

This sketch represents the integrated IoT device logic.

---

## Edge / Raspberry Pi Code (`.txt`)

Some source files are stored as `.txt` due to **academic submission requirements**. These files were executed on a **Raspberry Pi (VirtualBox)** and act as the edge layer.

### Arduino Code Copies
- Some `.txt` files are direct copies of Arduino `.ino` sketches submitted in text format
- These files are **not flashed to the Arduino**, but kept for assessment completeness

---

### Python / Edge Scripts
- `flaskforservo.txt`  
  Python Flask application that sends serial commands to the Arduino (e.g. `9`, `19`) and enables control via a web interface

- `phytoncodeforedgesubscribe.txt`  
- `phytoncodeforservoedge.txt`  
  Python edge scripts that subscribe to messages (pub/sub style) and translate them into Arduino serial commands

---

## Web Interface (`.txt`)
- `website.txt` — HTML frontend
- `websitecss.txt` — CSS styling

These files provide a simple UI that communicates with the Flask backend to control the Arduino system.

---

## Notes
- Each module can be run **independently** for testing and demonstration
- File naming and duplication reflect **submission constraints**, not production structure
- This repository is intended as a **learning and demonstration project**

---

