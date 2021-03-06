#include "Storage.h"

void Storage::init() {
    if (!SD.begin()) {
        Serial.println(F("Card mount failed"));
        for (;;);
    }

    uint8_t cardType = SD.cardType();
    if (cardType == CARD_NONE) {
        Serial.println(F("No SD card attached"));
        for (;;);
    }

    Instance().loadConfig();
}

void Storage::loadConfig() {
    Serial.print(F("Reading file: "));
    Serial.println(F(CONFIGURATION_PATH));

    File file = SD.open(CONFIGURATION_PATH);
    if (!file) {
        Serial.println(F("Failed to open config file for reading"));
        return;
    }

    /*
     * Config file format:
     *  1st line: wifi_ssid
     *  2nd line: wifi_password
     * */
    _wifi_ssid[0] = _wifi_password[0] = 0;;
    _wifi_ssid_length = _wifi_password_length = 0;

    if (file.available())
        _wifi_ssid_length = file.readBytesUntil('\t', _wifi_ssid, MAX_CHARACTERS_CONF_LINE);

    if (file.available())
        _wifi_password_length = file.readBytesUntil('\t', _wifi_password, MAX_CHARACTERS_CONF_LINE);

    _isWifiSet = _wifi_ssid_length && _wifi_password_length;
    printCurrentCredentials();

    file.close();
}

boolean Storage::containsCredentials() {
    return _isWifiSet;
}

void Storage::setNewCredentials(const char *ssid, const char *password) {
    strncpy(_wifi_ssid, ssid, MAX_CHARACTERS_CONF_LINE);
    strncpy(_wifi_password, password, MAX_CHARACTERS_CONF_LINE);

    _wifi_ssid_length = strlen(_wifi_ssid);
    _wifi_password_length = strlen(_wifi_password);
}

void Storage::printCurrentCredentials() {
    Serial.println(F("Current wifi credentials set:"));
    Serial.println(F(_wifi_ssid));
    Serial.println(F(_wifi_password));
}

void Storage::saveWifiCredentials() {
    Serial.print(F("Saving wifi credentials to file: "));
    Serial.println(F(CONFIGURATION_PATH));

    // Delete file if exists
    if (SD.exists(CONFIGURATION_PATH))
        SD.remove(CONFIGURATION_PATH);

    File file = SD.open(CONFIGURATION_PATH, FILE_APPEND);
    if (!file) {
        Serial.println("Failed to open file for writing");
        return;
    }

    Display::Instance().printScene("Saving wifi", 10);

    file.print(F(_wifi_ssid));
    file.print('\t');

    file.print(F(_wifi_password));
    file.println('\t');

    file.close();

    delay(1000);
}