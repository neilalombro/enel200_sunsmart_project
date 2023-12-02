// Arduino Program for testing RGB LED

// RGB Led
// Note: Pin numbers are not set
const int red_pin = 11;
const int green_pin = 10;
const int blue_pin = 9;
int index;

void RGB_color(int red_value, int green_value, int blue_value)
{
  analogWrite(red_pin, red_value);
  analogWrite(green_pin, green_value);
  analogWrite(blue_pin, blue_value);
}

void setup()
{
  pinMode(red_pin, OUTPUT);
  pinMode(green_pin, OUTPUT);
  pinMode(blue_pin, OUTPUT);
}

void loop()
{
  index = 0;
  switch (index) {
    case 0:
      RGB_color(0, 255, 0); // Green
      delay(2000);
      index = 1;
    case 1:
      RGB_color(255, 210, 0); // Yellow
      delay(2000);
      index = 2;
    case 2:
      RGB_color(200, 19, 0); // Orange
      delay(2000);
      index = 3;
    case 3:
      RGB_color(255, 0, 1); // Red
      delay(2000);
    default:
      RGB_color(127, 0, 255); // Purple
      delay(2000);
      break;
  }
}
