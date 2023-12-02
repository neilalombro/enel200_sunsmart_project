// Arduino Program for testing UV Sensor
#include "Adafruit_LTR390.h"

// UV Sensor
Adafruit_LTR390 ltr = Adafruit_LTR390();
uint32_t uv_data;
uint32_t uv_index;

unsigned long overall;
unsigned long minutes_elapsed;

void setup()
{
  // UV Sensor
  // NOTE: Confused about which mode, gain, and resolution needed
  Serial.begin(115200);
  ltr.begin();
  ltr.setMode(LTR390_MODE_UVS);
  ltr.setGain(LTR390_GAIN_3);
  ltr.setResolution(LTR390_RESOLUTION_16BIT);
  ltr.setThresholds(100, 1000);
  ltr.configInterrupt(true, LTR390_MODE_UVS);

  overall = 0;
  minutes_elapsed = 0;
}

void loop()
{
  overall = millis();
  if (overall >= (1000 * minutes_elapsed)) {
    minutes_elapsed += 1;
    if (ltr.newDataAvailable()) {      
      Serial.print("\nUV data: ");
      uv_data = ltr.readUVS();
      Serial.print(uv_data);
      Serial.print("\nUV Index: ");
      uv_index = uv_data / 25;
      Serial.print(uv_index);
      
    }
  }
}
