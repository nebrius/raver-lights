/*
Copyright (c) 2017 Bryan Hughes <bryan@nebri.us>

This file is part of Raver Lights.

Raver Lights is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Raver Lights is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Raver Lights.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <Arduino.h>
#include "config.h"
#include "messaging.h"
#include "state.h"

WiFiUDP udp;

byte currentPreset = Codes::Preset::Unknown;
unsigned long commandStartTime = millis();

bool needsSync = false;

void sync();

void Messaging::init() {
  Serial.print("Setting soft-AP configuration...");
  if (WiFi.softAPConfig(SERVER_IP, GATEWAY, SUBNET)) {
    Serial.println("Ready");
  } else {
    Serial.println("Failed!");
    return;
  }

  Serial.print("Starting soft-AP ");
  Serial.print(WIFI_SSID);
  Serial.print("...");

  if (WiFi.softAP(WIFI_SSID, WIFI_PASSPHRASE, 8, false)) {
    Serial.println("Ready");
  } else {
    Serial.println("Failed!");
    return;
  }

  Serial.print("Soft-AP IP address = ");
  Serial.println(WiFi.softAPIP());

  Serial.println("Messaging initialized");
}

void sync() {
  Serial.println("Syncing");
  State::Settings* settings = State::getSettings();
  udp.beginPacket(GATEWAY, SERVER_PORT);
  uint32_t commandTime = (uint32_t)(millis() - commandStartTime);
  Serial.print(commandTime);
  udp.write((byte*)&commandTime, 4);
  Serial.print(',');
  Serial.print(settings->brightness);
  udp.write(settings->brightness);
  Serial.print(',');
  Serial.print(settings->preset);
  udp.write(settings->preset);
  for (int i = 0; i < NUM_PRESET_VALUES; i++) {
    Serial.print(',');
    Serial.print(settings->presetValues[settings->preset][i]);
    udp.write(settings->presetValues[settings->preset][i]);
  }
  Serial.println("");
  udp.endPacket();
}

int nextSyncTime = millis();
int numConnectedClients = 0;
void Messaging::loop() {
  if (millis() < nextSyncTime && !needsSync) {
    return;
  }
  needsSync = false;

  State::setClientsConnected(WiFi.softAPgetStationNum());
  nextSyncTime = millis() + CLIENT_SYNC_INTERVAL;
  sync();
}

void Messaging::update() {
  byte newPreset = State::getSettings()->preset;
  if (newPreset != currentPreset) {
    currentPreset = newPreset;
    commandStartTime = millis();
  }
  needsSync = true;
}
