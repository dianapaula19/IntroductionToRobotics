#define red_light_pin  9
#define green_light_pin 10
#define blue_light_pin 11
#define pot_pin_red A2
#define pot_pin_green A1
#define pot_pin_blue A0
int pot_pin_red_value, pot_pin_green_value, pot_pin_blue_value; 
int pin_red_value, pin_green_value, pin_blue_value;
void setup() {
  // put your setup code here, to run once:
  pinMode(pot_pin_red, INPUT);
  pinMode(pot_pin_green, INPUT);
  pinMode(pot_pin_blue, INPUT);
  pinMode(red_light_pin, OUTPUT);
  pinMode(green_light_pin, OUTPUT);
  pinMode(blue_light_pin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  read_pot_values(pot_pin_red_value, pot_pin_green_value, pot_pin_blue_value); 
  pin_red_value = map(pot_pin_red_value, 0, 1023, 0, 255);
  pin_green_value = map(pot_pin_green_value, 0, 1023, 0, 255);
  pin_blue_value = map(pot_pin_blue_value, 0, 1023, 0, 255);
  set_colour(pin_red_value, pin_green_value, pin_blue_value);

}
void read_pot_values(int &red, int &green, int &blue) {

   red = analogRead(pot_pin_red);
   green = analogRead(pot_pin_green);
   blue = analogRead(pot_pin_blue);
}
void set_colour(int red, int green, int blue) {

    analogWrite(red_light_pin, pin_red_value);
    analogWrite(green_light_pin, pin_green_value);
    analogWrite(blue_light_pin, pin_blue_value);

}
