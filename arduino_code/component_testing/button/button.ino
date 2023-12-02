// Arduino Program for testing button (with LED)

// RGB Led
// Note: Pin numbers are not set
const int red_pin = 11;
const int green_pin = 10;
const int blue_pin = 9;

void RGB_color(int red_value, int green_value, int blue_value) 
{
  analogWrite(red_pin, red_value);
  analogWrite(green_pin, green_value);
  analogWrite(blue_pin, blue_value);
}

// Button
const int button_pin = 2;
int button_state = 0;

void setup() 
{
  // RGB Led
  pinMode(red_pin, OUTPUT);
  pinMode(green_pin, OUTPUT);
  pinMode(blue_pin, OUTPUT);

  // Button
  pinMode(button_pin, INPUT);
}

void loop() 
{
  button_state = digitalRead(button_pin);
  
  if (button_state == HIGH) {
    // HIGH when pressed
    RGB_color(0, 255, 0); // Green
    delay(1000);
  } else {
    RGB_color(255, 0, 0); // Red
    delay(1000);
  }
}
