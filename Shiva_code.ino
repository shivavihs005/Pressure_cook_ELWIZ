#include <Adafruit_LiquidCrystal.h>

#include <Servo.h>
 //-----------Servo Moter--------------
Servo servoMotor;
const int servo_pin = 7;
//--------potentiometer--------------
const int potPin = A0;
int potValue = 0;
//--------Herater---------------
const int heaterpin = 8; // Pin connected to heater
//--------Button-------------------
const int buttonPin = 5;
//--------------buzzer-----------------------
int buzzerpin = 9;
int buzzer;
//------------------cuplock-------------------------
int cup_1 = 0;
int cup_3 = 0;
int cup_2 = 0;
int cup_4 = 0;
//-----------------Mode-Lock------------------------
int pot1lock = 0;
int mode_1 = 0;
Adafruit_LiquidCrystal lcd_1(0);

void setup() {
  lcd_1.begin(16, 2);
  lcd_1.print("Smart Cooker");
  delay(1000);
  lcd_1.clear();
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(potPin, INPUT_PULLUP);
  pinMode(buzzerpin, OUTPUT);
  pinMode(heaterpin, OUTPUT);
  Serial.begin(9600);
  servoMotor.attach(servo_pin); // Connect the servo signal wire to pin 9
  servoMotor.write(0); // Set initial position to 0 degrees
}
void valve(int dig) {
  servoMotor.write(dig);
  // unsigned long int duration = 12000; // 2 minutes
  unsigned long int duration = 1200; // tempervary
  // Wait for the specified duration
  delay(duration);

  // Move the servo back to 0 degrees
  servoMotor.write(0);
  //----------buzzer---------------
  digitalWrite(buzzerpin, HIGH);
  delay(6000);
  digitalWrite(buzzerpin, LOW);

}
//----------------cooking-timing-in minute--------------------
void cooking_time(int cup_time) {
  //unsigned long  duration_cup = 60000*cup_time; // 2 minutes
  unsigned long duration_cup = 7000 * cup_time; // tempervary
  //---------Heater ON ----------------
  digitalWrite(heaterpin, HIGH);
  delay(duration_cup);
  digitalWrite(heaterpin, LOW);
  //---------Heater OFF------------
  digitalWrite(buzzerpin, HIGH);
  delay(6000);
  digitalWrite(buzzerpin, LOW);
  valve(90); /// digree for valve

}

void loop() {
  // Read the potentiometer value
  potValue = analogRead(potPin);
  delay(100);

  // Divide the potentiometer value into 14 modes

  //------------------------- Mode 1-----------------------
  if (potValue < 73 || pot1lock == 1) {
    lcd_1.setCursor(0, 0);
    lcd_1.print("white rice");

    // mode_1 for hold in current state
    // Do something for mode 1

    if (digitalRead(buttonPin) == 1 || mode_1 == 1) {
      mode_1 = 1;
      pot1lock = 1;

      lcd_1.setCursor(0, 0);
      lcd_1.print("WHITE RICE");
      delay(1000);

      //potValue=cupvalue;
      // ---------------Cup 1----------------
      if ((potValue >= 0 && potValue <= 255) || cup_1 == 1) {
        // cup 1

        lcd_1.setCursor(0, 1);
        lcd_1.print("cup 1");
        if (digitalRead(buttonPin) == 1 || cup_1 == 1) {
          cup_1 = 1; //lock cup 1

          lcd_1.setCursor(0, 1);
          lcd_1.print("CUP 1");
          delay(1000);
          cooking_time(1); //cooking time for Rice

        }
      }
      // ---------------Cup 2----------------
      else if ((potValue >= 256 && potValue <= 511) || cup_2 == 1) {
        // cup 2

        lcd_1.setCursor(0, 1);
        lcd_1.print("cup 2");
        // Do something for cup 2
        if (digitalRead(buttonPin) == 1 || cup_2 == 1) {
          cup_2 = 1; //lock cup 2

          lcd_1.setCursor(0, 1);
          lcd_1.print("CUP 2");
          delay(1000);
          cooking_time(1); //cooking time for Rice
        }
      }
      // ---------------Cup 3----------------
      else if ((potValue >= 512 && potValue <= 767) || cup_3 == 1) {
        // cup 3
        lcd_1.setCursor(0, 1);
        lcd_1.print("cup 3");
        // Do something for mode 3
        if (digitalRead(buttonPin) == 1 || cup_3 == 1) {
          cup_3 = 1; //lock cup 3

          lcd_1.setCursor(0, 1);
          lcd_1.print("CUP 3");
          delay(1000);
          cooking_time(1); //cooking time for Rice
        }
      }
      // ---------------Cup 4----------------
      else if ((potValue >= 768 && potValue <= 1023) || cup_4 == 1) {
        // cup 4
        lcd_1.setCursor(0, 1);
        lcd_1.print("cup 4");
        // Do something for mode 4
        if (digitalRead(buttonPin) == 1 || cup_4 == 1) {
          cup_4 = 1; //lock cup 4

          lcd_1.setCursor(0, 1);
          lcd_1.print("CUP 4 ");
          delay(1000);
          cooking_time(1); //cooking time for Rice
        }
      }
    }
}
}
