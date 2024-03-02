#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <Arduino_JSON.h>
#include <LiquidCrystal_I2C.h>

const char* ssid     = "SSID";          // The SSID (name) of the Wi-Fi network you want to connect to
const char* password = "PASSWORD";      // The password of the Wi-Fi network

const char* myLineCode    = "1";        // The Line Code of the A.T.M. bus
const char* myStopCode    = "11829";    // The Stop Code of the A.T.M. bus line you chose

LiquidCrystal_I2C lcd(0x3F, 16, 2);     // set up the LCD's number of columns and rows

unsigned long timerDelay = 5000;        // Set timer to 5 seconds (5000)
unsigned long lastTime = 0;             // Initialize lastTime with 0

String waitMessage = "";                // Global variable storing the waiting time of the bus
String refreshedWaitMessage = "";       // Global variable storing the new waiting time of the bus

const char* serverName = "https://giromilano.atm.it/proxy.tpportal/proxy.ashx";  // API server

void setup()
{
    Serial.begin(115200);
    Serial.println();

    WiFi.begin(ssid, password);

    Serial.print("Connecting");
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println();

    Serial.print("Connected, IP address: ");
    Serial.println(WiFi.localIP());

    lastTime = millis(); // Initialize lastTime with current time

    // The begin call takes the width and height. This
    // Should match the number provided to the constructor.
    lcd.begin(16,2);
    lcd.init();

    // Turn on the backlight.
    lcd.backlight();

    // Print the bus line code you chose to the screen.
    lcd.print(myLineCode + ":");

    // Move the cursor to the next line
    lcd.setCursor(5, 1);
}

void loop() {
    // Send an HTTP POST request depending on timerDelay
    if ((millis() - lastTime) > timerDelay) {

        // Check connection before proceeding
        if(WiFi.status() == WL_CONNECTED){

            // Refresh wait message
            refreshWaitMessage(myStopCode, myLineCode);

            // Display the new wait message if it changed
            if (refreshedWaitMessage != waitMessage) {
                waitMessage = refreshedWaitMessage;

                // Clear the display before printing new message
                lcd.clear();

                // Print the bus line code you chose to the screen.
                lcd.print(myLineCode + ":");

                // Move the cursor to the next line
                lcd.setCursor(5, 1);

                // Print the new wait message to the screen
                lcd.print(waitMessage);
            }

        }
        else {
            Serial.println("WiFi Disconnected");
        }

        lastTime = millis();
    }
}

void refreshWaitMessage(const char* stopCode, const char* lineCode) {
    WiFiClient client;
    HTTPClient http;

    // A.T.M.'s server
    http.begin(client, serverName);

    // Specify headers
    http.addHeader("User-Agent", "Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:122.0) Gecko/20100101 Firefox/122.0");
    http.addHeader("Content-Type", "application/x-www-form-urlencoded;charset=utf-8");
    http.addHeader("Accept-Language", "en-US,en;q=0.5");  // Include the Accept-Language header
    http.addHeader("Referer", "https://giromilano.atm.it/");
    http.addHeader("cookie", "TS01ac3475=0199b2c74a586b2cd3f979a7ee12300ddcc689b1fefbbbc91f6642ce9f2d4ff46133460b04f410c5a5d64ffea5e2b6581194aaeabc");


    // Prepare the payload for the POST request
    String httpRequestData = "url=tpPortal%2Fgeodata%2Fpois%2Fstops%2F" + String(stopCode);


    // Send HTTP POST request
    int httpResponseCode = http.POST(httpRequestData);

    // Refresh the wait message
    if (httpResponseCode > 0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String payload = http.getString();

        // Parse the response JSON
        JSONVar response = JSON.parse(payload);

        // Check if the response contains the "Lines" field
        if (response.hasOwnProperty("Lines")) {
            JSONVar lines = response["Lines"];

            // Look for the chosen bus line
            for (int i = 0; i < lines.length(); i++) {
                if (lines[i].hasOwnProperty("BookletUrl2") && String(lines[i]["BookletUrl2"]) == lineCode) {
                    if (lines[i].hasOwnProperty("WaitMessage")) {
                        String newWaitMessage = String(lines[i]["WaitMessage"]);
                        if (newWaitMessage != refreshedWaitMessage) {
                            refreshedWaitMessage = newWaitMessage;
                            Serial.println(refreshedWaitMessage);
                            http.end();
                            return;
                        }
                    }
                }
            }
        }
    }
    else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
    }

    // Free resources
    http.end();
}
