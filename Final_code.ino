// C++ code
//
#include <Adafruit_LiquidCrystal.h>
#include <Servo.h>

int seconds = 0;
int a = 0;
int b = 0;
int pos = 0;
int mode_select = 0;
int cup_select = 0;
char rice_type[] = " ";
char Veg_type[] = " ";
int cups_value = 0;
int cook_done = 0;

bool isStoring = 0;

const int pot = A0;
const int btn = 2;
const int heater = 5;
const int rst = 6;
Servo servo_3;

Adafruit_LiquidCrystal lcd_1(0);

void drain_servo(int drain_time)
{
    for (pos = 0; pos <= 180; pos += 1)
    {
        servo_3.write(pos);
        delay(15);
    }
    delay(drain_time);
    for (pos = 180; pos >= 0; pos -= 1)
    {
        servo_3.write(pos);
        delay(15);
    }
}

void cooking_done()
{
    lcd_1.clear();
    lcd_1.setCursor(0, 0);
    lcd_1.print("Cooking Done");
    mode_select = 0;
    cup_select = 0;
    a = 0;
    b = 0;
    analogWrite(heater, 11); // heater turned on at 45 degree celcius until push btn is pressed
    digitalWrite(4, HIGH);   // Buzzer and Led Indication
    // delay(5000);
    // digitalWrite(4, LOW);
    drain_servo(10000);
    int rst_btn = digitalRead(rst);
    if (rst_btn == 1)
    {
        // cook_done == 1;
        analogWrite(heater, 0);
    }
}

void rice_select(char rice_type[], int cups_value, int time)
{
    lcd_1.clear();
    lcd_1.setCursor(0, 0);
    lcd_1.print(rice_type);
    lcd_1.setCursor(0, 1);
    lcd_1.print("Cups : ");
    lcd_1.setCursor(7, 1);
    lcd_1.print(cups_value);
    analogWrite(heater, 255); // heater on
    delay(time);              // Timer for 35 mins
    cooking_done();
}

void vegetable_select(char veg_type[], int preheattime, int time)
{
    lcd_1.clear();
    lcd_1.setCursor(0, 0);
    lcd_1.print(veg_type);
    lcd_1.setCursor(0, 1);
    lcd_1.print("Preating 5-9 mins");
    analogWrite(heater, 255); // heater on
    delay(preheattime);       // Timer for 5-9 mins
    lcd_1.clear();
    lcd_1.setCursor(0, 0);
    lcd_1.print("Cooking");
    analogWrite(heater, 255); // Active cooking
    delay(time);              // Timer for 12 mins
    cooking_done();
}

void setup()
{
    lcd_1.begin(16, 2);
    lcd_1.print("Smart Cooker");
    delay(500);
    pinMode(btn, INPUT_PULLUP);
    servo_3.attach(3, 500, 2500);
    servo_3.write(0);
    Serial.begin(9600);
}

void loop()
{
    int rst_btn = digitalRead(rst);
    if (rst_btn == 1)
    {
        // cook_done == 1;
        analogWrite(heater, 0);
        mode_select = 0;
        cup_select = 0;
        a = 0;
        b = 0;
    }

    else
    {
        int buttonState = digitalRead(btn);

        if (buttonState == HIGH)
        {
            isStoring = !isStoring;
            delay(1000); // Debounce delay

            if (isStoring)
            {
                a = analogRead(pot);
            }

            else
            {
                b = analogRead(pot);
            }
        }

        mode_select = a;
        cup_select = b;

        Serial.print("Mode : ");
        Serial.println(mode_select);
        Serial.print("Cups : ");
        Serial.println(cup_select);

        delay(100);

        // ------------------------------Mode1--------------------------------

        // ---------------Cup1----------------
        if (mode_select > 0 && mode_select <= 73 && cup_select > 0 && cup_select <= 255)
        {
            rice_select("White Rice", 1, 3200); // time 32 min
        }
        // ---------------Cup2----------------
        else if (mode_select > 0 && mode_select <= 73 && cup_select >= 256 && cup_select <= 511)
        {
            rice_select("White Rice", 2, 3500); // time 35 min
        }
        // ---------------Cup3----------------
        else if (mode_select > 0 && mode_select <= 73 && cup_select >= 512 && cup_select <= 767)
        {
            rice_select("White Rice", 3, 3800); // time 38 min
        }
        // ---------------Cup4----------------
        else if (mode_select > 0 && mode_select <= 73 && cup_select >= 768 && cup_select <= 1023)
        {
            rice_select("White Rice", 4, 4200); // time 42 min
        }

        // ---------------------------------Mode2--------------------------------

        // ---------------Cup1----------------
        else if (mode_select >= 74 && mode_select <= 146 && cup_select > 0 && cup_select <= 255)
        {
            rice_select("Black Rice", 1, 5500); // time 55 min
        }
        // ---------------Cup2----------------
        else if (mode_select >= 74 && mode_select <= 146 && cup_select >= 256 && cup_select <= 511)
        {
            rice_select("Black Rice", 2, 5700); // time 57 min
        }
        // ---------------Cup3----------------
        else if (mode_select >= 74 && mode_select <= 146 && cup_select >= 512 && cup_select <= 767)
        {
            rice_select("Black Rice", 3, 6100); // time 61 min
        }
        // ---------------Cup4----------------
        else if (mode_select >= 74 && mode_select <= 146 && cup_select >= 768 && cup_select <= 1023)
        {
            rice_select("Black Rice", 4, 0); // time 0 min
            lcd_1.clear();
            lcd_1.print("Cannot cook");
        }

        // ---------------------------------Mode3--------------------------------

        // ---------------Cup1----------------
        else if (mode_select >= 147 && mode_select <= 219 && cup_select > 0 && cup_select <= 255)
        {
            rice_select("Brown Rice", 1, 5500); // time 55 min
        }
        // ---------------Cup2----------------
        else if (mode_select >= 147 && mode_select <= 219 && cup_select >= 256 && cup_select <= 511)
        {
            rice_select("Brown Rice", 2, 5700); // time 57 min
        }
        // ---------------Cup3----------------
        else if (mode_select >= 147 && mode_select <= 219 && cup_select >= 512 && cup_select <= 767)
        {
            rice_select("Brown Rice", 3, 6100); // time 61 min
        }
        // ---------------Cup4----------------
        else if (mode_select >= 147 && mode_select <= 219 && cup_select >= 768 && cup_select <= 1023)
        {
            rice_select("Brown Rice", 4, 0); // time 0 min
            lcd_1.clear();
            lcd_1.print("Cannot cook");
        }

        // ---------------------------------Mode4--------------------------------

        // ---------------Cup1----------------
        else if (mode_select >= 220 && mode_select <= 292 && cup_select > 0 && cup_select <= 255)
        {
            rice_select("Red Rice", 1, 5500); // time 55 min
        }
        // ---------------Cup2----------------
        else if (mode_select >= 220 && mode_select <= 292 && cup_select >= 256 && cup_select <= 511)
        {
            rice_select("Red Rice", 2, 5700); // time 57 min
        }
        // ---------------Cup3----------------
        else if (mode_select >= 220 && mode_select <= 292 && cup_select >= 512 && cup_select <= 767)
        {
            rice_select("Red Rice", 3, 6300); // time 63 min
        }
        // ---------------Cup4----------------
        else if (mode_select >= 220 && mode_select <= 292 && cup_select >= 768 && cup_select <= 1023)
        {
            rice_select("Red Rice", 4, 0); // time 0 min
            lcd_1.clear();
            lcd_1.print("Cannot cook");
        }

        // ---------------------------------Rice---------------------------------
        // ---------------------------------Mode5--------------------------------

        // ---------------Cup1----------------
        else if (mode_select >= 293 && mode_select <= 365 && cup_select > 0 && cup_select <= 255)
        {
            rice_select("Quinoa Rice", 1, 4200); // time 42 min
        }
        // ---------------Cup2----------------
        else if (mode_select >= 293 && mode_select <= 365 && cup_select >= 256 && cup_select <= 511)
        {
            rice_select("Quinoa Rice", 2, 4400); // time 44 min
        }
        // ---------------Cup3----------------
        else if (mode_select >= 293 && mode_select <= 365 && cup_select >= 512 && cup_select <= 767)
        {
            rice_select("Quinoa Rice", 3, 4400); // time 44 min
        }
        // ---------------Cup4----------------
        else if (mode_select >= 293 && mode_select <= 365 && cup_select >= 768 && cup_select <= 1023)
        {
            rice_select("Quinoa Rice", 4, 4700); // time 47 min
        }

        // ---------------------------------Mode6--------------------------------

        // ---------------Cup1----------------
        else if (mode_select >= 366 && mode_select <= 438 && cup_select > 0 && cup_select <= 255)
        {
            rice_select("Basmati Rice", 1, 1500); // time 15 min
        }
        // ---------------Cup2----------------
        else if (mode_select >= 366 && mode_select <= 438 && cup_select >= 256 && cup_select <= 511)
        {
            rice_select("Basmati Rice", 2, 1800); // time 18 min
        }
        // ---------------Cup3----------------
        else if (mode_select >= 366 && mode_select <= 438 && cup_select >= 512 && cup_select <= 767)
        {
            rice_select("Basmati Rice", 3, 2200); // time 22 min
        }
        // ---------------Cup4----------------
        else if (mode_select >= 366 && mode_select <= 438 && cup_select >= 768 && cup_select <= 1023)
        {
            rice_select("Basmati Rice", 4, 2600); // time 26 min
        }

        // ---------------------------------Mode7--------------------------------

        // ---------------Cup1----------------
        else if (mode_select >= 439 && mode_select <= 511 && cup_select > 0 && cup_select <= 255)
        {
            rice_select("Single B Rice", 1, 3200); // time 32 min
        }
        // ---------------Cup2----------------
        else if (mode_select >= 439 && mode_select <= 511 && cup_select >= 256 && cup_select <= 511)
        {
            rice_select("Single B Rice", 2, 3500); // time 35 min
        }
        // ---------------Cup3----------------
        else if (mode_select >= 439 && mode_select <= 511 && cup_select >= 512 && cup_select <= 767)
        {
            rice_select("Single B Rice", 3, 3800); // time 38 min
        }
        // ---------------Cup4----------------
        else if (mode_select >= 439 && mode_select <= 511 && cup_select >= 768 && cup_select <= 1023)
        {
            rice_select("Single B Rice", 4, 4200); // time 42 min
        }

        // ---------------------------------Mode8--------------------------------

        // ---------------Cup1----------------
        else if (mode_select >= 512 && mode_select <= 584 && cup_select > 0 && cup_select <= 255)
        {
            rice_select("Double B Rice", 1, 3500); // time 35 min
        }
        // ---------------Cup2----------------
        else if (mode_select >= 512 && mode_select <= 584 && cup_select >= 256 && cup_select <= 511)
        {
            rice_select("Double B Rice", 2, 3800); // time 38 min
        }
        // ---------------Cup3----------------
        else if (mode_select >= 512 && mode_select <= 584 && cup_select >= 512 && cup_select <= 767)
        {
            rice_select("Double B Rice", 3, 4200); // time 42 min
        }
        // ---------------Cup4----------------
        else if (mode_select >= 512 && mode_select <= 584 && cup_select >= 768 && cup_select <= 1023)
        {
            rice_select("Double B Rice", 4, 4600); // time 46 min
        }

        // ---------------------------------Mode9--------------------------------

        // ---------------Cup1----------------
        else if (mode_select >= 585 && mode_select <= 657 && cup_select > 0 && cup_select <= 255)
        {
            rice_select("Raw Rice", 1, 2000); // time 20 min
        }
        // ---------------Cup2----------------
        else if (mode_select >= 585 && mode_select <= 657 && cup_select >= 256 && cup_select <= 511)
        {
            rice_select("Raw Rice", 2, 2300); // time 23 min
        }
        // ---------------Cup3----------------
        else if (mode_select >= 585 && mode_select <= 657 && cup_select >= 512 && cup_select <= 767)
        {
            rice_select("Raw Rice", 3, 2700); // time 27 min
        }
        // ---------------Cup4----------------
        else if (mode_select >= 585 && mode_select <= 657 && cup_select >= 768 && cup_select <= 1023)
        {
            rice_select("Raw Rice", 4, 3100); // time 31 min
        }

        // -------------------------------Vegetables------------------------------
        // ---------------------------------Mode10--------------------------------

        else if (mode_select >= 658 && mode_select <= 730)
        {
            vegetable_select("Carrot", 5500, 1200); // time 12 min
        }

        // ---------------------------------Mode11--------------------------------
        else if (mode_select >= 731 && mode_select <= 803)
        {
            vegetable_select("Cabbage", 5500, 1100); // time 11 min
        }

        // ---------------------------------Mode12--------------------------------
        else if (mode_select >= 804 && mode_select <= 876)
        {
            vegetable_select("Green Peas", 5500, 800); // time 8 min
        }

        // ---------------------------------Mode13--------------------------------
        else if (mode_select >= 877 && mode_select <= 949)
        {
            vegetable_select("Spinach", 5500, 300); // time 3 min
        }

        // ---------------------------------Mode14--------------------------------
        else if (mode_select >= 950 && mode_select <= 1022)
        {
            vegetable_select("Potato", 5500, 1200); // time 12 min
        }
        // else {cooking_done();}
    }
}