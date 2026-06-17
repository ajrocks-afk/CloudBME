# 🌍 CloudBME

A low-power environmental monitoring station designed to collect real-time atmospheric data such as temperature , pressure & humidity , and securely transmit it to the cloud for remote monitoring and analysis.

---

## 🚀 Overview

CloudBME is an end-to-end IoT solution that measures **temperature**, **humidity**, and **barometric pressure** using a BME280 sensor. The system combines embedded hardware, wireless connectivity, and cloud services to enable reliable environmental monitoring from anywhere.

The project demonstrates the integration of custom hardware, embedded firmware, secure MQTT communication, and AWS cloud infrastructure in a complete IoT workflow.

---

## 🛠️ Tech Stack

### Hardware

* BME280 Environmental Sensor
* ATmega328P Microcontroller
* ESP32 Wi-Fi Module

### Firmware

* Embedded C++
* Arduino IDE

### Hardware Design

* Custom PCB designed using EasyEDA

### Cloud & Backend

* AWS IoT Core
* MQTT Protocol
* X.509 Certificate-Based Authentication

---

## 📋 System Architecture

```text
BME280 Sensor
      │
      ▼
ATmega328P Microcontroller
      │
      ▼
ESP32 Wi-Fi Module
      │
      ▼
AWS IoT Core
      │
      ▼
Cloud Dashboard / Data Visualization
```

Environmental data is collected by the BME280 sensor, processed by the ATmega328P microcontroller, transmitted through the ESP32 via Wi-Fi, and securely published to AWS IoT Core using MQTT.

---

## ✨ Key Features

* 📡 **Real-Time Monitoring** – Streams environmental data to the cloud for remote access.
* 🔒 **Secure Communication** – Uses X.509 certificates for device authentication and encrypted communication.
* ⚡ **Low-Power Operation** – Designed for efficient and reliable long-term deployment.
* 🧩 **Modular Architecture** – Separates hardware, firmware, and cloud components for easier maintenance and scalability.
* 🖥️ **Custom PCB Design** – Enhances system reliability and simplifies deployment.

---

## 📂 Project Structure

```text
CloudBME/
│
├── hardware/
│   ├── PCB_SCHEMATICS_DIAGRAM/
│   └── PCB_BOARD_IMAGE/
│
├── firmware/
│   ├── src/
│   └── secrets.h      (not tracked)
│
├── docs/
│
└── README.md
```
---

## ⚙️ Configuration

To protect sensitive information, Wi-Fi credentials and AWS certificates are stored in a separate `secrets.h` file that is excluded from version control.

### 1. Create `secrets.h`

Create a file named:

```text
firmware/secrets.h
```

### 2. Add Your Credentials

```cpp
#ifndef SECRETS_H
#define SECRETS_H

#define WIFI_SSID "YOUR_WIFI_NAME"
#define WIFI_PASSWORD "YOUR_WIFI_PASSWORD"

#define AWS_IOT_ENDPOINT "YOUR_AWS_IOT_ENDPOINT"

const char AWS_ROOT_CA[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
YOUR_ROOT_CA_CERTIFICATE
-----END CERTIFICATE-----
)EOF";

#endif
```

### 3. Build and Upload

1. Open the project in Arduino IDE.
2. Select the correct board and COM port.
3. Build the firmware.
4. Upload it to the device.

---

## 📄 Documentation

### Hardware

PCB schematics and design files are located in:

```text
/hardware
```

### Firmware

Source code and configuration files are located in:

```text
/firmware
```

---

## 🎯 Skills Demonstrated

This project showcases practical experience in:

* Embedded Systems Development
* Internet of Things (IoT)
* PCB Design and Hardware Integration
* Sensor Interfacing
* MQTT Communication
* AWS IoT Core
* Secure Device Authentication
* Cloud-Based Data Collection and Monitoring

---

## 🔮 Future Enhancements

* Web-based dashboard for live monitoring
* Historical data storage and analytics
* Over-the-Air (OTA) firmware updates
* Battery-powered deployment mode
* Mobile application integration
* Automated alert and notification system

---

## ⚖️ License

This project is licensed under the MIT License. See the `LICENSE` file for more information.

---

## 👨‍💻 Author

CloudBME was developed as an IoT environmental monitoring project to demonstrate embedded systems design, secure cloud connectivity, and real-time data acquisition.
