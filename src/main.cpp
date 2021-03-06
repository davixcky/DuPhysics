#include <Arduino.h>
#include <ServerManager/ServerManager.h>

#include "globals.h"
#include "Storage/Storage.h"
#include "Display/Display.h"
#include "ServerManager/DataController.h"

void setup() {
    Serial.begin(115200);

    Display::Instance().begin();

    Storage::init();

    delay(1000);

    Display::Instance().clearPixels(0, SCREEN_HEIGHT);
    Display::Instance().printBasicInfo("Connecting", 80);
    Display::Instance().printScene("hello", 5);

    if (Storage::Instance().containsCredentials()) {
        ServerManager::Instance().setWifiCredentials(Storage::Instance().getSSID(), Storage::Instance().getPassword());
        ServerManager::Instance().connectToWifi();
    }

    if (!ServerManager::Instance().isConnected()) { // Only execute captive when is not connected
        ServerManager::Instance().launchCaptivePortal();
    }
}

void loop() {
    // Load storage
    // If password set -> launch st mode -> if fails -> launch ap mode
    // If no password set -> launch ap mode -> receives -> try connect ->
    //                                                                      password works -> saved
    //                                                                      password doesn't works -> try again

    if (!ServerManager::Instance().isConnected()) { // Only execute tick when is not connected
        ServerManager::Instance().tick();
    } else {
        Display::Instance().printScene(
                DataController::Instance().getStatus() == DataController::RUNNING
                ? RUNNING_TEXT
                : END_TEXT, 7);
    }

    Display::Instance().printBasicInfo(ServerManager::Instance().getCurrentIP(), 80);
}