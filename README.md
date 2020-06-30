# home_automation
Prototype platform for home automation system

The goal of the project is to build a prototype platform for home automation which can be further improved in the future. Finished project will include features to monitor status and control some sort of devices but it is not expected to have a real-life application already.

System features:

- WiFi connection based on ESP8266 module (nodeMCU) to allow remote control (module can communicate with CPU (Nucleo F103RB) through UART, I2C or SPI)

- Simple web application with user interface

- Temperature monitoring with usage of DS18B20 digital thermometer (1-Wire)

- Controlling window shutter - it will be simulated by controlling small DC motor and monitoring status of distance sensor (e.g. HC-SR04)

Video presentation:
https://drive.google.com/file/d/1yC2IrriCyoDI8Foaz_9RnJ5CDaKP3N4N/view?usp=sharing
