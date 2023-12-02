// Arduino Program for testing seven segment display (with button)
// Press button to get all displays in one second intervals.

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

// Button
const int button_pin = 2;
int button_state = 0;

void setup() 
{
  // 7 Segment Display
  clear_display();

  // Button
  pinMode(button_pin, INPUT);
}

void loop() 
{
  button_state = digitalRead(button_pin);

  if (button_state == HIGH) {
    display_zero();
    delay(1000);
    display_one();
    delay(1000);
    display_two();
    delay(1000);
    display_three();
    delay(1000);
    display_four();
    delay(1000);
    display_five();
    delay(1000);
    display_six();
    delay(1000);
    display_seven();
    delay(1000);
    display_eight();
    delay(1000);
    display_nine();
    delay(1000);
    display_h();
    delay(1000);
  } else {
    clear_display();
    delay(1000);
  }
}
