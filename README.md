# 🌱 IoT-Based Smart Watering and NPK Fertilizer System

### Smart Agriculture | Internet of Things | Embedded Systems

## 📌 Project Overview

The **IoT-Based Smart Watering and NPK Fertilizer System** is a smart agriculture solution designed to improve irrigation management and fertilizer distribution through automation and Internet of Things (IoT) technology.

Traditional agricultural practices often involve manual irrigation and fertilizer application, which can lead to inefficient water consumption, inconsistent fertilizer distribution, and unnecessary human intervention.

This project aims to address these challenges by integrating soil moisture monitoring, automated water pump control, and remotely operated Nitrogen (N), Phosphorus (P), and Potassium (K) fertilizer valves into a unified smart farming system.

Using an Arduino UNO for sensor monitoring and an ESP8266 Wi-Fi module for connectivity, the system communicates with a Blynk IoT dashboard, allowing users to monitor soil conditions and control connected devices remotely.

## 🎯 Project Objectives

* Monitor soil moisture conditions in real time.
* Automate irrigation based on soil moisture readings.
* Enable controlled distribution of NPK fertilizers.
* Provide remote monitoring and control through a mobile dashboard.
* Reduce unnecessary water consumption and manual intervention.
* Explore IoT-based solutions for precision agriculture.

## ⚙️ Key Features

* **Soil Moisture Monitoring:** Continuously reads soil moisture sensor values.
* **Smart Irrigation:** Controls the water pump based on soil moisture conditions.
* **NPK Fertilizer Management:** Provides individual control over Nitrogen, Phosphorus, and Potassium solenoid valves.
* **Remote Monitoring:** Displays sensor readings and system status through Blynk IoT.
* **Manual Control:** Allows users to operate the pump and fertilizer valves remotely.
* **Automatic Mode:** Supports automated irrigation based on predefined moisture thresholds.
* **Status Indicators:** Uses LEDs and a buzzer to indicate system conditions.

## 🛠️ Technologies & Components

### Hardware Components

* Arduino UNO
* ESP8266 NodeMCU
* Soil Moisture Sensor
* Relay Modules
* Solenoid Valves (NPK)
* DC Water Pump
* Red LED and Green LED
* Buzzer
* External Power Supply

### Software & Technologies

* Embedded C/C++
* Arduino IDE
* Blynk IoT Platform
* Wi-Fi Communication
* Serial Communication (UART)

## 🏗️ System Architecture

The system consists of two primary controllers:

**1. Arduino UNO – Sensor and Local Control**

* Reads soil moisture sensor values.
* Processes the sensor readings.
* Controls LED and buzzer indicators.
* Transmits sensor data to ESP8266 through serial communication.

**2. ESP8266 – IoT Communication and Automation**

* Connects the system to Wi-Fi.
* Communicates with the Blynk IoT platform.
* Receives remote commands from the dashboard.
* Controls the water pump and NPK solenoid valves through relay modules.

## 📷 Project Demonstration

## 📱 Blynk Dashboard

The Blynk dashboard provides a remote interface for monitoring and controlling the system.

The dashboard includes:

* Soil moisture readings.
* Water pump ON/OFF control.
* Automatic irrigation mode.
* Individual Nitrogen, Phosphorus, and Potassium valve controls.
* LED and buzzer status monitoring.

## 🔄 Working Principle

1. The soil moisture sensor measures the moisture level in the soil.
2. Arduino UNO reads and processes the sensor values.
3. The processed data is transmitted to ESP8266 through serial communication.
4. ESP8266 sends the information to the Blynk IoT dashboard using Wi-Fi.
5. Based on the selected operating mode, the water pump can be controlled automatically or manually.
6. Users can independently operate the NPK solenoid valves through the mobile dashboard.
7. LEDs and the buzzer provide local system status indications.

## 🚀 Future Enhancements

* Integration of an NPK sensor for real-time soil nutrient analysis.
* AI/ML-based fertilizer recommendation system.
* Weather-based intelligent irrigation.
* Cloud-based historical data analysis.
* Crop-specific fertilizer scheduling.
* Advanced water consumption monitoring.

## 🎓 Project Domain

* Internet of Things (IoT)
* Smart Agriculture
* Embedded Systems
* Automation
* Precision Farming

## 👨‍💻 Developed By

**Sneha Sharma**

B.Tech – Computer Science and Engineering
Specialization: Artificial Intelligence and Data Science
