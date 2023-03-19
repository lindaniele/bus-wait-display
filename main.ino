#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <Arduino_JSON.h>
#include <LiquidCrystal_I2C.h>

const char* ssid     = "SSID";          // The SSID (name) of the Wi-Fi network you want to connect to
const char* password = "PASSWORD";      // The password of the Wi-Fi network

String myLineCode    = "1";             // The Line Code of the A.T.M. bus
String myStopCode    = "11829";         // The Stop Code of the A.T.M. bus line you chose

LiquidCrystal_I2C lcd(0x3F, 16, 2);     // set up the LCD's number of columns and rows

unsigned long lastTime = 0;            // Global variable storing the last time you refreshed the waiting time of the bus
unsigned long timerDelay = 5000;        // Set timer to 5 seconds (5000)

String waitMessage = "";                // Global variable storing the waiting time of the bus
String refreshedWaitMessage = "";       // Global variable storing the new waiting time of the bus

const char* serverName = "https://giromilano.atm.it/proxy.ashx";

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
    http.addHeader("User-Agent", "Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:101.0) Gecko/20100101 Firefox/101.0");
    http.addHeader("Content-Type", "application/x-www-form-urlencoded;charset=utf-8");
    http.addHeader("Referer", "https://giromilano.atm.it/");

    // Data to send with HTTP POST
    String httpRequestData = "url=tpPortal%2Fgeodata%2Fpois%2Fstops%2F" + stopCode;

    // Send HTTP POST request
    int httpResponseCode = http.POST(httpRequestData);

    // Refresh the wait message
    if (httpResponseCode>0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String payload = http.getString();

        // List of bus lines that meet at the chosen bus stop
        JSONVar lines = JSON.parse(payload)["Lines"];

        // Look for the chosen bus line
        for (int i = 0; i < lines.length(); ++i) {
            if (lines[i]["BookletUrl2"] == lineCode) {
                refreshedWaitMessage = lines[i]["WaitMessage"];
                http.end();
                return;
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
