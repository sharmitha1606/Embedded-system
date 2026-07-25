#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <Adafruit_BMP085.h>

// Pin definitions matching the standard SPI setup
#define TFT_CS    15
#define TFT_DC     2
#define TFT_RST    4

// Initialize Display and Sensor
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);
Adafruit_BMP085 bmp;

void setup() {
  Serial.begin(115200);

  // Initialize ILI9341 Display
  tft.begin();
  tft.setRotation(1); // Landscape mode
  tft.fillScreen(ILI9341_BLACK);

  // Display Header
  tft.setTextColor(ILI9341_CYAN);
  tft.setTextSize(2);
  tft.setCursor(20, 20);
  tft.println("ESP32 Sensor Monitor");

  tft.drawFastHLine(0, 50, 320, ILI9341_WHITE);

  // Initialize BMP180 Sensor
  if (!bmp.begin()) {
    Serial.println("Could not find BMP180 sensor!");
    tft.setTextColor(ILI9341_RED);
    tft.setCursor(20, 80);
    tft.println("BMP180 Init Failed!");
    while (1); // Halt execution if sensor fails
  }
}

void loop() {
  float temp = bmp.readTemperature();
  float pressure = bmp.readPressure() / 100.0F; // Convert Pa to hPa

  // Clear previous sensor reading area (to prevent overlapping text)
  tft.fillRect(20, 80, 280, 100, ILI9341_BLACK);

  // Print Temperature
  tft.setTextColor(ILI9341_YELLOW);
  tft.setTextSize(2);
  tft.setCursor(20, 80);
  tft.print("Temp: ");
  tft.setTextColor(ILI9341_WHITE);
  tft.print(temp, 1);
  tft.println(" C");

  // Print Pressure
  tft.setTextColor(ILI9341_GREEN);
  tft.setCursor(20, 130);
  tft.print("Pressure: ");
  tft.setTextColor(ILI9341_WHITE);
  tft.print(pressure, 1);
  tft.println(" hPa");

  // Also output to Serial Monitor for debugging
  Serial.print("Temp: ");
  Serial.print(temp);
  Serial.print(" C | Pressure: ");
  Serial.print(pressure);
  Serial.println(" hPa");

  delay(2000); // Update every 2 seconds
}