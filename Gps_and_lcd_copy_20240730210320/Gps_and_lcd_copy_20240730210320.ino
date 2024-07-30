#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(9600);

  // Initialize OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print(F("GPS Receiver Initialized"));
  display.display();
  delay(2000);
}

void parseGPSData(const String& gpsData) {
  // Simple NMEA $GPGGA sentence parsing
  int index1 = gpsData.indexOf(',');
  int index2 = gpsData.indexOf(',', index1 + 1);
  int index3 = gpsData.indexOf(',', index2 + 1);
  int index4 = gpsData.indexOf(',', index3 + 1);
  int index5 = gpsData.indexOf(',', index4 + 1);
  int index6 = gpsData.indexOf(',', index5 + 1);
  int index7 = gpsData.indexOf(',', index6 + 1);
  int index8 = gpsData.indexOf(',', index7 + 1);
  int index9 = gpsData.indexOf(',', index8 + 1);

  String latitude = gpsData.substring(index2 + 1, index3);
  String latDir = gpsData.substring(index3 + 1, index4);
  String longitude = gpsData.substring(index4 + 1, index5);
  String lonDir = gpsData.substring(index5 + 1, index6);

  Serial.print("Latitude: ");
  Serial.print(latitude);
  Serial.print(" ");
  Serial.println(latDir);
  Serial.print("Longitude: ");
  Serial.print(longitude);
  Serial.print(" ");
  Serial.println(lonDir);

  // Update OLED display
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Lat: ");
  display.print(latitude);
  display.print(" ");
  display.print(latDir);
  display.setCursor(0, 20);
  display.print("Lon: ");
  display.print(longitude);
  display.print(" ");
  display.print(lonDir);
  display.display();
}

void loop() {
  if (Serial.available() > 0) {
    String gpsData = Serial.readStringUntil('\n');
    Serial.print("Received: ");
    Serial.println(gpsData);

    if (gpsData.startsWith("$GPGGA")) {
      parseGPSData(gpsData);
      display.clearDisplay();
      display.println(gpsData);
    }
  }
}
