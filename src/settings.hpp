// /*
// Copyright (c) 2017 Bryan Hughes <bryan@nebri.us>

// This file is part of Raver Lights.

// Raver Lights is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// Raver Lights is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with Raver Lights.  If not, see <http://www.gnu.org/licenses/>.
// */

#ifndef SETTINGS_H_
#define SETTINGS_H_

#include "./codes.hpp"
#include "./config.hpp"
#include <Arduino.h>
#include <rvl-wifi.hpp>

namespace Settings {

void init();

char* getWiFiSSID();
void setWiFiSSID(const char* ssid);

char* getWiFiPassphrase();
void setWiFiPassphrase(const char* passphrase);

uint16_t getPort();
void setPort(uint16_t newPort);

uint8_t getSetting(const char* key, uint8_t defaultValue);
void setSetting(const char* key, uint8_t value);

} // namespace Settings

#endif // SETTINGS_H_
