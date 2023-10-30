#include <Adafruit_LiquidCrystal.h>
#include <Servo.h>
Adafruit_LiquidCrystal lcd_1(0);

//-------------------pot-----------------------
int potValue = 0;
//-------------------button---------------
int button = 0;
const int buttonPin = 2;

//-------------------custom variables-----------------
int mode_1 = 0;
int cup_1 = 0;
int pos = 0;

//-------------------servo-----------------
Servo servo_9;

//---------------------------------------------------

void setup()
{
    lcd_1.begin(16, 2);
    lcd_1.setBacklight(1);

    lcd_1.setCursor(0, 0);
    lcd_1.print("smart cooker");

    delay(2000);

    lcd_1.clear();

    // lcd_1.setCursor(0, 1);
    // lcd_1.print("min:");

    // lcd_1.setCursor(4, 1);
    // lcd_1.print(0);

    pinMode(buttonPin, INPUT);

    pinMode(A0, INPUT);
    pinMode(LED_BUILTIN, OUTPUT);

    servo_9.attach(9, 500, 2500);

    Serial.begin(9600);
}
//-------------------------------------------
void loop()
{
    button = digitalRead(buttonPin);

    potValue = analogRead(A0);
    Serial.println(potValue);

    if (potValue <= 68)
    {
        lcd_1.setCursor(0, 1);
        lcd_1.clear();
        lcd_1.print("White Rice");

        delay(2000);

        lcd_1.clear();
        Serial.println("Pushbutton state: ");

        if (digitalRead(buttonPin) == HIGH || mode_1 == 1)
        {
            mode_1 = 1;

            if (potValue <= 256)
            {
                lcd_1.clear();
                lcd_1.print("1 Cup Rice");
                delay(3000);
                lcd_1.clear();

                if (digitalRead(buttonPin) == HIGH || cup_1 == 1)
                {
                    cup_1 = 1;

                    // Jump to start cooking function
                    clock(1);
                    drain_servo(15000);
                    int mode_1 = 0;
                    int cup_1 = 0;
                    int pos = 0;
                }
            }
        }
    }
}
void clock(int selecttime)
{
    int seconds = 0;
    int min = 0;
    bool whiteRiceSelected = false;
    bool oneCupRiceSelected = false;

    while (min < selecttime)
    {
        if (seconds < 60)
        {
            seconds += 1;

            lcd_1.setCursor(0, 0);
            lcd_1.print("sec:");
            lcd_1.print(seconds);

            lcd_1.setCursor(0, 1);
            lcd_1.print("min:");
            lcd_1.print(min);

            delay(1000);
        }

        if (seconds == 60)
        {
            lcd_1.clear();
            seconds = 0;
            min += 1;

            lcd_1.setCursor(0, 0);
            lcd_1.print("sec:");
            lcd_1.print(seconds);

            lcd_1.setCursor(0, 1);
            lcd_1.print("min:");
            lcd_1.print(min);
        }
    }
}
void drain_servo(int drain_time)
{
    for (pos = 0; pos <= 180; pos += 1)
    {

        servo_9.write(pos);

        delay(15);
    }
    delay(drain_time);
    for (pos = 180; pos >= 0; pos -= 1)
    {

        servo_9.write(pos);

        delay(15);
    }
}