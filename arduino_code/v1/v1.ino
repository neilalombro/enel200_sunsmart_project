// Arduino Program for Solar Powered UV Sensor
// Components include:
//    - UV Sensor
//    - Transducer
//    - RGB LED
//    - 7 Segment Display
//    - Button


// Things to do:
//    - Figure out how to turn reading into index
//        - Make sure index we set is an integer and is above zero
//    - Make sure we have the right mode, gain, and resolution.
//        - Is there added value to using the ALS mode as well?
//    - Include some time component and UV calculation for Piezo
//        - Should reset and look for button incorporation
//    - Figure out how to use Piezo with Analog Pins

#include <Adafruit_LTR390.h>
#include <Adafruit_BusIO_Register.h>
#include <Adafruit_I2CDevice.h>
#include <Adafruit_I2CRegister.h>
#include <Adafruit_SPIDevice.h>

// UV Sensor
Adafruit_LTR390 ltr = Adafruit_LTR390();
uint32_t uv_data;
uint32_t uv_index;

// Transducer
const int buzz_pin = 3;
bool buzz_on = false;

//Time
unsigned long overall;
unsigned long minutes_elapsed;

// RGB Led
// Note: Pin numbers are not set
const int red_pin = 10;
const int green_pin = 11;
const int blue_pin = 9;

void RGB_color(int red_value, int green_value, int blue_value)
{
  analogWrite(red_pin, red_value);
  analogWrite(green_pin, green_value);
  analogWrite(blue_pin, blue_value);
}

// 7 Segment Display
// Pins go clockwise from the top and end with the middle segment
const int a_pin = 5;
const int b_pin = 4;
const int c_pin = 13;
const int d_pin = 12;
const int e_pin = 8;
const int f_pin = 6;
const int g_pin = 7;

void clear_display(void)
{
  digitalWrite(a_pin, LOW);
  digitalWrite(b_pin, LOW);
  digitalWrite(c_pin, LOW);
  digitalWrite(d_pin, LOW);
  digitalWrite(e_pin, LOW);
  digitalWrite(f_pin, LOW);
  digitalWrite(g_pin, LOW);
}

void display_zero(void)
{
  clear_display();
  digitalWrite(a_pin, HIGH);
  digitalWrite(b_pin, HIGH);
  digitalWrite(c_pin, HIGH);
  digitalWrite(d_pin, HIGH);
  digitalWrite(e_pin, HIGH);
  digitalWrite(f_pin, HIGH);
}

void display_one(void)
{
  clear_display();
  digitalWrite(b_pin, HIGH);
  digitalWrite(c_pin, HIGH);
}

void display_two(void)
{
  clear_display();
  digitalWrite(a_pin, HIGH);
  digitalWrite(b_pin, HIGH);
  digitalWrite(g_pin, HIGH);
  digitalWrite(e_pin, HIGH);
  digitalWrite(d_pin, HIGH);
}

void display_three(void)
{
  clear_display();
  digitalWrite(a_pin, HIGH);
  digitalWrite(b_pin, HIGH);
  digitalWrite(c_pin, HIGH);
  digitalWrite(d_pin, HIGH);
  digitalWrite(g_pin, HIGH);
}

void display_four(void)
{
  clear_display();
  digitalWrite(f_pin, HIGH);
  digitalWrite(g_pin, HIGH);
  digitalWrite(b_pin, HIGH);
  digitalWrite(c_pin, HIGH);
}

void display_five(void)
{
  clear_display();
  digitalWrite(a_pin, HIGH);
  digitalWrite(f_pin, HIGH);
  digitalWrite(g_pin, HIGH);
  digitalWrite(c_pin, HIGH);
  digitalWrite(d_pin, HIGH);
}

void display_six(void)
{
  clear_display();
  digitalWrite(a_pin, HIGH);
  digitalWrite(f_pin, HIGH);
  digitalWrite(e_pin, HIGH);
  digitalWrite(d_pin, HIGH);
  digitalWrite(c_pin, HIGH);
  digitalWrite(g_pin, HIGH);
}

void display_seven(void)
{
  clear_display();
  digitalWrite(a_pin, HIGH);
  digitalWrite(b_pin, HIGH);
  digitalWrite(c_pin, HIGH);
}

void display_eight(void)
{
  clear_display();
  digitalWrite(a_pin, HIGH);
  digitalWrite(b_pin, HIGH);
  digitalWrite(c_pin, HIGH);
  digitalWrite(d_pin, HIGH);
  digitalWrite(e_pin, HIGH);
  digitalWrite(f_pin, HIGH);
  digitalWrite(g_pin, HIGH);
}

void display_nine(void)
{
  clear_display();
  digitalWrite(a_pin, HIGH);
  digitalWrite(f_pin, HIGH);
  digitalWrite(g_pin, HIGH);
  digitalWrite(b_pin, HIGH);
  digitalWrite(c_pin, HIGH);
}

void display_h(void)
{
  clear_display();
  digitalWrite(b_pin, HIGH);
  digitalWrite(c_pin, HIGH);
  digitalWrite(e_pin, HIGH);
  digitalWrite(f_pin, HIGH);
  digitalWrite(g_pin, HIGH);
}

// Button
const int button_pin = 2;
int button_state = 0;

void setup()
{
  // UV Sensor
  // NOTE: Confused about which mode, gain, and resolution needed
  Serial.begin(115200);
  ltr.setMode(LTR390_MODE_UVS);
  ltr.setGain(LTR390_GAIN_3);
  ltr.setResolution(LTR390_RESOLUTION_16BIT);
  ltr.setThresholds(100, 1000);
  ltr.configInterrupt(true, LTR390_MODE_UVS);

  // Transducer
  pinMode(buzz_pin, OUTPUT);

  // RGB Led
  pinMode(red_pin, OUTPUT);
  pinMode(green_pin, OUTPUT);
  pinMode(blue_pin, OUTPUT);

  // 7 Segment Display
  clear_display();

  // Button
  pinMode(button_pin, INPUT);
}

void loop()
{
  // UV Sensor Reading
  // Note: UV Sensor reading is NOT index
  // Work out how to get index from reading

  // Time
  overall = millis();
  if (overall > (60000 * minutes_elapsed)) {
    minutes_elapsed += 1;
    if (ltr.newDataAvailable()) {      
      uv_data = ltr.readUVS();
      uv_index = 0;
    } else {
      uv_data = 0;
      uv_index = 0;
    }
    
    // RBG Led and 7 Segment Display
    switch (uv_index) {
      case 0:
        display_zero();
        RGB_color(0, 255, 0); // Green
        break;
      case 1:
        display_one();
        RGB_color(0, 255, 0); // Green
        break;
      case 2:
        display_two();
        RGB_color(0, 255, 0); // Green
        break;
      case 3:
        display_three();
        RGB_color(255, 210, 0); // Yellow
        break;
      case 4:
        display_four();
        RGB_color(255, 210, 0); // Yellow
        break;
      case 5:
        display_five();
        RGB_color(255, 210, 0); // Yellow
        break;
      case 6:
        display_six();
        RGB_color(200, 19, 0); // Orange
        break;
      case 7:
        display_seven();
        RGB_color(200, 19, 0); // Orange
        break;
      case 8:
        display_eight();
        RGB_color(255, 0, 1); // Red
        break;
      case 9:
        display_nine();
        RGB_color(255, 0, 1); // Red
        break;
      case 10:
        display_h();
        RGB_color(255, 0, 1); // Red
        break;
      default:
        display_h();
        RGB_color(127, 0, 255); // Purple
        break;
    }
  }

  // Button
  button_state = digitalRead(button_pin);
  
  if (buzz_on) {
    if (button_state == HIGH) {
    // HIGH when pressed
    // Set time to reset and turn off transducer
  } else {
    
  }
  
  
  // Note: check button press AND transducer on. AND necessary since it also resets time
  
  }
}
