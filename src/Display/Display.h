#ifndef DISPLAY__H
#define DISPLAY__H

#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)

// Images
#define MAIN_LOGO_WIDTH 127
#define MAIN_LOGO_HEIGHT 30
const unsigned char MAIN_LOGO[] PROGMEM = {
        B00000000, B00000110, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
        B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
        B00000000, B00001110, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
        B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
        B00000000, B00001110, B00000000, B00000000, B11000011, B00011000, B01100110, B11000001, B10111111, B10001111,
        B10000001, B11100001, B10011111, B00000000, B11000001, B11111000,
        B00000000, B00001111, B00000000, B00000000, B11100011, B10111000, B01101110, B11100011, B10111111, B11011111,
        B11100011, B11111001, B10011111, B11000000, B11100001, B11111110,
        B00000000, B00011111, B00000000, B00000000, B11100011, B10111100, B01101110, B11100011, B00111111, B11011111,
        B11110111, B00111001, B10011111, B11100001, B11100001, B11111110,
        B00000000, B00011111, B10000000, B00000000, B11100011, B10111110, B01101110, B01100011, B00110000, B00011100,
        B01110111, B00011001, B10011000, B01110001, B11110001, B11000110,
        B00000000, B00111111, B10000000, B00000000, B11100011, B10111110, B01101110, B01110111, B00111111, B10011100,
        B01110111, B11000001, B10011000, B01110011, B11110001, B11000110,
        B00000000, B00111111, B10000000, B00000000, B11100011, B10111111, B01101110, B01110110, B00111111, B10011111,
        B11100011, B11111001, B10011000, B01110011, B10110001, B11000010,
        B11111111, B11111111, B11111111, B11100000, B11100011, B10111011, B11101110, B00110110, B00111111, B10011111,
        B11100000, B11111001, B10011000, B01110011, B00111001, B11000110,
        B11111111, B11111111, B11111111, B11100000, B11100011, B10111011, B11101110, B00111110, B00110000, B00011100,
        B01110110, B00011101, B10011000, B01110111, B11111001, B11000110,
        B10000111, B10000110, B00001110, B00100000, B11100011, B10111001, B11101110, B00111100, B00110000, B00011100,
        B01110111, B00011101, B10011000, B11100111, B11111101, B11001110,
        B10000111, B10000110, B00001110, B00100000, B01111111, B00111000, B11101110, B00011100, B00111111, B11011100,
        B01110111, B11111001, B10011111, B11100110, B00011101, B11111110,
        B10000111, B10000110, B00000110, B00100000, B00111110, B00111000, B11101110, B00011100, B00111111, B11011100,
        B01110011, B11110001, B10011111, B10001110, B00011101, B11111100,
        B10000111, B10000110, B00000110, B00100000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
        B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
        B10000111, B10000110, B00000110, B00100000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
        B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
        B10000111, B10000110, B00000010, B00100000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
        B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
        B10000111, B10000110, B00100010, B00100000, B11111100, B00011111, B11001100, B00000000, B00000000, B00000000,
        B11000011, B00001111, B10000111, B11110011, B11111110, B11111110,
        B10000111, B10000110, B00100010, B00100000, B11111111, B00111111, B11001100, B00000000, B00000000, B00000000,
        B11100011, B00011111, B11000111, B11111011, B11111110, B11111110,
        B10000111, B10000110, B00100000, B00100000, B11101111, B10111111, B11001100, B00000000, B00000000, B00000000,
        B11110011, B00111000, B11100111, B00111001, B11111100, B11111110,
        B10000111, B10000110, B00110000, B00100000, B11100011, B10111000, B00001100, B00000000, B00000000, B00000000,
        B11110011, B00111000, B01100110, B00011100, B01110000, B11000000,
        B10000111, B10001110, B00110000, B00100000, B11100011, B10111111, B11001100, B00000000, B00000000, B00000000,
        B11111011, B00110000, B01110110, B00011000, B01110000, B11111110,
        B10000111, B00001110, B00110000, B00100000, B11100001, B10111111, B11001100, B00000000, B00000000, B00000000,
        B11011011, B01110000, B01110111, B11111000, B01110000, B11111110,
        B11000000, B00001110, B00111000, B00100000, B11100011, B10111000, B00001100, B00000000, B00000000, B00000000,
        B11011111, B00110000, B01110111, B11111000, B01110000, B11000000,
        B11100000, B00011110, B00111000, B00100000, B11100011, B10111000, B00001100, B00000000, B00000000, B00000000,
        B11001111, B00110000, B01100110, B00011000, B01110000, B11000000,
        B11111000, B01111110, B01111100, B00100000, B11100111, B00111000, B00001110, B00000000, B00000000, B00000000,
        B11000111, B00111000, B11100110, B00011000, B01110000, B11000000,
        B11111111, B11111111, B11111111, B11100000, B11111111, B00111111, B11101111, B11100000, B00000000, B00000000,
        B11000111, B00011111, B11000110, B00011000, B01110000, B11111110,
        B00011111, B11111111, B11111111, B00000000, B11111100, B00011111, B11001111, B11100000, B00000000, B00000000,
        B11000011, B00001111, B10000110, B00011100, B01110000, B11111110,
        B00111111, B11111111, B11111111, B10000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
        B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
        B00111111, B11000000, B01111111, B10000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
        B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
        B00111100, B00000000, B00000111, B10000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
        B00000000, B00000000, B00000000, B00000000, B00000000, B00000000
};

#define EXPOFISICA_LOGO_WIDTH 128
#define EXPOFISICA_LOGO_HEIGHT 32
const unsigned char EXPOFISICA_LOGO[] PROGMEM = {
        B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111,
        B11111111, B11111111, B11111111, B11111111, B11111111, B11111111,
        B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111,
        B11111111, B11111111, B11111111, B11111111, B11111111, B11111111,
        B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111,
        B11111111, B11111111, B11111111, B11111111, B11111111, B11111111,
        B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111,
        B11111111, B11111111, B11111111, B11111111, B11111111, B11111111,
        B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111,
        B11111111, B11111111, B11111111, B11111111, B11111111, B11111111,
        B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111,
        B11111111, B11111111, B11111111, B11111111, B11111111, B11111111,
        B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111000, B11111111, B11111111, B10011111,
        B11111101, B11111111, B11111111, B11111111, B11111111, B11111111,
        B11111111, B11111111, B11111111, B11000000, B01001100, B01000000, B11100000, B01110000, B00000010, B00000110,
        B01110000, B01111100, B01111111, B11111111, B11111111, B11111111,
        B11111111, B11111111, B11111111, B11000000, B11000100, B11000000, B01100010, B00110000, B00100010, B01100010,
        B01100000, B00111000, B01111111, B11111111, B11111111, B11111111,
        B11111111, B11111111, B11111111, B11001111, B11100001, B11001110, B01000111, B00010011, B11100010, B01110010,
        B01000111, B00111000, B01111111, B11111111, B11111111, B11111111,
        B11111111, B11111111, B11111111, B11000000, B11100001, B11001110, B01001111, B00010000, B00100010, B00001110,
        B01000111, B11111000, B00111111, B11111111, B11111111, B11111111,
        B11111111, B11111111, B11111111, B11000000, B11110001, B11000000, B01001111, B10010000, B00100011, B00000010,
        B01000111, B11110001, B00111111, B11111111, B11111111, B11111111,
        B11111111, B11111111, B11111111, B11001111, B11100001, B11000001, B11001111, B00010011, B11100011, B11100010,
        B01000111, B10110000, B00011111, B11111111, B11111111, B11111111,
        B11111111, B11111111, B11111111, B11001111, B11000000, B11001111, B11000111, B00110011, B11100000, B01110010,
        B01000111, B00110000, B00011111, B11111111, B11111111, B11111111,
        B11111111, B11111111, B11111111, B11000000, B01001100, B01001111, B11100000, B00110011, B11100010, B00000010,
        B01100000, B00100011, B10011111, B11111111, B11111111, B11111111,
        B11111111, B11111111, B11111111, B11000000, B00001110, B01001111, B11110000, B01110011, B11100111, B00000110,
        B01110000, B01100111, B10011111, B11111111, B11111111, B11111111,
        B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111,
        B11111111, B11111111, B11111111, B11111111, B11111111, B11111111,
        B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111,
        B11111111, B11111111, B11111111, B11111111, B11111111, B11111111,
        B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111,
        B11111111, B11111111, B11111111, B11111111, B11111111, B11111111,
        B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11100001, B11100001, B11000011, B10001111,
        B11111111, B11111111, B11111111, B11111111, B11111111, B11111111,
        B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11100000, B11000000, B11000001, B00001111,
        B11111111, B11111111, B11111111, B11111111, B11111111, B11111111,
        B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111100, B10011100, B11111001, B10011111,
        B11111111, B11111111, B11111111, B11111111, B11111111, B11111111,
        B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111100, B10011100, B11111001, B10011111,
        B11111111, B11111111, B11111111, B11111111, B11111111, B11111111,
        B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111001, B10011100, B11110011, B10011111,
        B11111111, B11111111, B11111111, B11111111, B11111111, B11111111,
        B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11110011, B00011000, B11100111, B10011111,
        B11111111, B11111111, B11111111, B11111111, B11111111, B11111111,
        B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11100111, B00111001, B11001111, B00111111,
        B11111111, B11111111, B11111111, B11111111, B11111111, B11111111,
        B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11000011, B10010001, B10000111, B00111111,
        B11111111, B11111111, B11111111, B11111111, B11111111, B11111111,
        B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B10000001, B10000011, B00000011, B00111111,
        B11111111, B11111111, B11111111, B11111111, B11111111, B11111111,
        B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111,
        B11111111, B11111111, B11111111, B11111111, B11111111, B11111111,
        B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111,
        B11111111, B11111111, B11111111, B11111111, B11111111, B11111111,
        B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111,
        B11111111, B11111111, B11111111, B11111111, B11111111, B11111111,
        B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111,
        B11111111, B11111111, B11111111, B11111111, B11111111, B11111111
};


class Display {
public:
    Display();

    void begin();

    void printImage(const uint8_t bitmap[], const short width, const short height);

    void setNumberScenes(int totalScenes);

    void setScenesTitles(String titles[]);

    void setScenesSuffix(String suffix[]);

    void printCurrentScene(String scenesValues[], bool showTitle);
    void printBasicInfo(bool isWifiConnected, short batteryLevelPercent);

    void clearPixels(uint16_t startY, uint16_t stopY = SCREEN_WIDTH);

private:

    Adafruit_SSD1306 *display = nullptr;
    int maxScenes;
    int currentIndexScene;
    String *titlesScenes = nullptr;
    String *suffixesScenes = nullptr;

    void drawBatteryIndicator(short percent);

};

#endif // DISPLAY__H