/*
Copyright (c) 2018 Bryan Hughes <bryan@nebri.us>

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

#ifdef HAS_UI

#include <Arduino.h>
#include <rvl-wifi.h>
#include <vector>
#include "./settings.h"
#include "./ui/presets/solid.h"

namespace Solid {

uint8_t hue;
uint8_t saturation;
uint8_t value;

void updateWaveParameters() {
  RVLWaveSettings newSettings;

  // Wave wave
  newSettings.waves[0].h.b = hue;
  newSettings.waves[0].s.b = saturation;
  newSettings.waves[0].v.b = value;
  newSettings.waves[0].a.b = 255;

  rvl::setWaveSettings(&newSettings);
}

void updateHueValue(uint8_t newValue) {
  if (hue != newValue) {
    hue = newValue;
    Settings::setSetting("ui-s-hue", hue);
    updateWaveParameters();
  }
}

void updateSaturationValue(uint8_t newValue) {
  if (saturation != newValue) {
    saturation = newValue;
    Settings::setSetting("ui-s-sat", saturation);
    updateWaveParameters();
  }
}

void updateValueValue(uint8_t newValue) {
  if (value != newValue) {
    value = newValue;
    Settings::setSetting("ui-s-val", value);
    updateWaveParameters();
  }
}

Solid::Solid() {
  hue = Settings::getSetting("ui-s-hue", 170);
  saturation = Settings::getSetting("ui-s-sat", 255);
  value = Settings::getSetting("ui-s-val", 255);
  this->controls.push_back(new Control::RangeControl(
    "HUE",
    0,
    255,
    hue,
    updateHueValue,
    NULL));
  this->controls.push_back(new Control::RangeControl(
    "SAT",
    0,
    255,
    saturation,
    updateSaturationValue,
    NULL));
  this->controls.push_back(new Control::RangeControl(
    "VAL",
    0,
    255,
    value,
    updateValueValue,
    NULL));
}

void Solid::updateWave() {
  updateWaveParameters();
}

}  // namespace Solid

#endif  // HAS_UI
