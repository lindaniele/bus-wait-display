# Real-Time Bus Wait Time Display

The "Real-Time Bus Wait Time Display" project utilizes an ESP8266 microcontroller and an LCD display to show the real-time waiting time of buses from Azienda Trasporti Milanesi (ATM Milano), a public transport company in Milan. By setting the bus line and stop code, the device fetches the waiting time information from the ATM server (GiroMilano) and displays it on the LCD screen.

[Leggi questo in italiano](it/README.md)

## Table of Contents
- [Project Overview](#project-overview)
- [Hardware Requirements](#hardware-requirements)
- [Software Requirements](#software-requirements)
- [Installation and Setup](#installation-and-setup)
- [Usage](#usage)
- [Contributing](#contributing)
- [License](#license)

## Project Overview

The "Real-Time Bus Wait Time Display" project provides a convenient way to monitor the waiting time of a specific bus line at a particular stop in real-time. The ESP8266 microcontroller connects to the ATM server through Wi-Fi, retrieves the waiting time information, and displays it on the LCD screen. With this display, users can easily plan their bus trips more efficiently.

## Hardware Requirements

To set up the project, you will need the following hardware components:

- ESP8266 microcontroller
- LCD display (16x2 or similar, compatible with the LiquidCrystal_I2C library)
- Jumper wires
- Breadboard (optional, for prototyping)
- Power supply or battery pack (if not powered through USB)

## Software Requirements

The project relies on the following software:

- Arduino IDE (or any compatible IDE)
- ESP8266WiFi library
- ESP8266HTTPClient library
- WiFiClient library
- Arduino JSON library
- LiquidCrystal_I2C library

Make sure you have these libraries installed in your Arduino IDE before proceeding with the installation: Go to **Sketch > Include Library > Manage Libraries**.

## Installation and Setup

Follow these steps to install and set up the "Real-Time Bus Wait Time Display" project:

1. Clone or download the project repository to your local machine.

2. Open the Arduino IDE and navigate to **File > Open**. Select the main project file (the one with the `.ino` extension) from the downloaded repository.

3. Connect the ESP8266 microcontroller and LCD display to your computer using jumper wires and a breadboard if necessary.

4. In the Arduino IDE, make sure you have selected the appropriate board and port for the ESP8266:
   - Go to **Tools > Board** and select your ESP8266 board model.
   - Go to **Tools > Port** and select the COM port your ESP8266 is connected to.

5. Open the `main.ino` file and modify the following variables as per your requirements:
   - `ssid`: Set the SSID (name) of your Wi-Fi network.
   - `password`: Set the password of your Wi-Fi network.
   - `myLineCode`: Set the bus line code you are interested in.
   - `myStopCode`: Set the stop code corresponding to the bus stop you want to monitor.

6. Upload the sketch to the ESP8266 microcontroller by clicking on the "Upload" button in the Arduino IDE.

7. Once the upload is complete, open the Serial Monitor in the Arduino IDE to view the ESP8266's connection status and IP address.

8. Connect the LCD display to the ESP8266 microcontroller according to the wiring instructions provided in the project. Generally the connections are as follows:
   - **VCC** of LCD to **3.3V** on ESP8266.
     - Most I2C LCD displays are designed to work with 5V power supply. However, many can also work at 3.3V, which is the operating voltage of the ESP8266. Ensure that your specific LCD model can operate safely and reliably at 3.3V. If your LCD requires 5V, you may need to use a voltage regulator or level shifter to safely connect it to the ESP8266.
   - **GND** of LCD to **GND** on ESP8266.
   - **SDA** of LCD to **D2** (or the I2C SDA pin) on ESP8266.
   - **SCL** of LCD to **D1** (or the I2C SCL pin) on ESP8266.

9. Power on the ESP8266 microcontroller. The LCD display should show the bus line code and the waiting time information.

## Usage

After the installation and setup process, the "Real-Time Bus Wait Time Display" project will continuously fetch the waiting time information for the specified bus line and stop code from the ATM server. The LCD display will update with the latest waiting time information every few seconds.

Monitor the LCD display to stay updated with the real-time waiting time of the bus. Here are some usage considerations:

- Make sure the ESP8266 microcontroller is connected to a stable Wi-Fi network with internet access.
- Ensure that the bus line code and stop code you set correspond to valid values recognized by the ATM server.
- The LCD display will refresh the waiting time information at the specified interval (5 seconds by default). You can modify the `timerDelay` variable in the code to adjust the refresh rate according to your preference.
- If the waiting time information changes, the LCD display will update accordingly. The new waiting time will replace the previous one on the screen.
- If the Wi-Fi connection is lost, the LCD display will indicate that the connection is disconnected.
- If you want to monitor a different bus line or stop, modify the `myLineCode` and `myStopCode` variables in the code, upload the updated sketch to the ESP8266, and restart the device.

Please note that this project relies on the availability and accuracy of the waiting time information provided by the ATM server. Any changes or issues with the server's API or data may affect the reliability of the displayed information.

## Contributing

Contributions to the "Real-Time Bus Wait Time Display" project are welcome! If you have any ideas, improvements, or bug fixes, please feel free to open an issue or submit a pull request in the project repository.

## License

The "Real-Time Bus Wait Time Display" project by Daniele Lin [complies with ATM's Terms and Conditions](COMPLIANCE_ATM.md) and is licensed under a
[Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License][cc-by-nc-sa].

[![CC BY-NC-SA 4.0][cc-by-nc-sa-image]][cc-by-nc-sa]

[cc-by-nc-sa]: http://creativecommons.org/licenses/by-nc-sa/4.0/
[cc-by-nc-sa-image]: https://licensebuttons.net/l/by-nc-sa/4.0/88x31.png