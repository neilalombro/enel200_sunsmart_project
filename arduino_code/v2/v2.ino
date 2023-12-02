// Arduino Program for Solar Powered UV Sensor
// Components include:
//    - UV Sensor
//    - Transducer
//    - RGB LED
//    - 7 Segment Display
//    - Button

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
unsigned long time_since_last_buzz;

// RGB Led
const int red_pin = 11;
const int green_pin = 10;
const int blue_pin = 9;

void RGB_color(int red_value, int green_value, int blue_value)
{
  analogWrite(red_pin, red_value);
  analogWrite(green_pin, green_value);
  analogWrite(blue_pin, blue_value);
}

// 7 Segment Display
// Pins go clockwise from the top and end with the middle segment
const int a_pin = 6;
const int b_pin = 7;
const int c_pin = 13;
const int d_pin = 12;
const int e_pin = 8;
const int f_pin = 5;
const int g_pin = 4;

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

void display_seg_and_rgb(uint32_t uv_index)
{
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
      RGB_color(255, 0, 0); // Yellow
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
const int button_pin = 2;
int button_state = 0;

void setup()
{
  // UV Sensor
  Serial.begin(115200);
  ltr.begin();
  ltr.setMode(LTR390_MODE_UVS);
  ltr.setGain(LTR390_GAIN_3);
  ltr.setResolution(LTR390_RESOLUTION_16BIT);
  ltr.setThresholds(100, 1000);
  ltr.configInterrupt(true, LTR390_MODE_UVS);

  // Transducer
  pinMode(buzz_pin, OUTPUT);

  //Time
  overall = 0;
  minutes_elapsed = 0;
  time_since_last_buzz = 0;

  // RGB Led
  pinMode(red_pin, OUTPUT);
  pinMode(green_pin, OUTPUT);
  pinMode(blue_pin, OUTPUT);

  // 7 Segment Display
  pinMode(a_pin, OUTPUT);
  pinMode(b_pin, OUTPUT);
  pinMode(c_pin, OUTPUT);
  pinMode(d_pin, OUTPUT);
  pinMode(e_pin, OUTPUT);
  pinMode(f_pin, OUTPUT);
  pinMode(g_pin, OUTPUT);
  clear_display();

  // Button
  pinMode(button_pin, INPUT);

  //Transducer
  analogWrite(buzz_pin, 127);
  delay(500);
  analogWrite(buzz_pin, 0);
}

void loop()
{
  // UV Sensor Reading
  // Note: UV Sensor reading is NOT index
  // Work out how to get index from reading

  // Time
  overall = millis();

  // Updates UV Index every minute
  if (overall >= (60000 * minutes_elapsed)) {
    minutes_elapsed += 1;
    if (ltr.newDataAvailable()) {      
      uv_data = ltr.readUVS();
      uv_index = uv_data / 25;  
    } else {
      uv_data = 0;
      uv_index = 0;
    }
    
    display_seg_and_rgb(uv_index);

    // Add on to sunblock indicator
    time_since_last_buzz += uv_index;
  }

  // Checks if 100 index points have been passed: buzzer turns on if so.
  // Based on research: https://pdskin.com/blogs/uv-index-the-sun-safety-scale
  if (time_since_last_buzz > 100) {
    buzz_on = true;
    analogWrite(buzz_pin, 127);
    RGB_color(255, 0, 1); // Red
    delay(100);
    RGB_color(0, 0, 0); // Blank
  }

  // Button
  button_state = digitalRead(button_pin);

  // If buzzing, button will act as a stopper for transducer.
  // Else, button will act as a 7 Segment indicator to show the exact UV Index
  if (buzz_on) {
    if (button_state == HIGH) {
      buzz_on = false;
      analogWrite(buzz_pin, 0);
      time_since_last_buzz = 0;
      display_seg_and_rgb(uv_index);
    }
  } else {
    if (button_state == HIGH) {
      display_seg_and_rgb(uv_index);
    } else {
      clear_display();
    }
  }
}
