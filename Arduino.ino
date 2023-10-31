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

// C++ code
//
#include <Adafruit_LiquidCrystal.h>

int seconds = 0;

Adafruit_LiquidCrystal lcd_1(0);

void setup()
{
    lcd_1.begin(16, 2);
    lcd_1.print("Smart Cooker");
}

void loop()
{
    mode_select = analogRead(A0);

    if (mode_select <= 68)
    {
        lcd_1.setCursor(0, 1);
        lcd_1.clear();
        lcd_1.print("White Rice");

        delay(1000);

        lcd_1.clear();
        // Serial.println("Pushbutton state: ");

        // if (digitalRead(buttonPin) == HIGH || mode_1 == 1)
        // {
        //     mode_1 = 1;

        //     if (potValue <= 256)
        //     {
        //         lcd_1.clear();
        //         lcd_1.print("1 Cup Rice");
        //         delay(3000);
        //         lcd_1.clear();

        //         if (digitalRead(buttonPin) == HIGH || cup_1 == 1)
        //         {
        //             cup_1 = 1;

        //             // Jump to start cooking function
        //             clock(1);
        //             drain_servo(15000);
        //             int mode_1 = 0;
        //             int cup_1 = 0;
        //             int pos = 0;
        //         }
        //     }
        // }
    }

    lcd_1.setCursor(0, 1);
    lcd_1.print("Mode : 1");
    lcd_1.setBacklight(1);

    // delay(500); // Wait for 500 millisecond(s)
    // lcd_1.setBacklight(0);
    // delay(500); // Wait for 500 millisecond(s)
    // seconds += 1;
}

// Pin definitions
const int potentiometerPin = A0; // Potentiometer connected to analog pin A0
const int buttonPin = 2;         // Push button connected to digital pin 2

// Variables
int currentValue = 0;      // Current value from the potentiometer
int storedValue1 = 0;      // First stored value
int storedValue2 = 0;      // Second stored value
boolean isStoring = false; // Flag to indicate storage mode

void setup()
{
    // Initialize serial communication for debugging
    Serial.begin(9600);

    // Set buttonPin as an input
    pinMode(buttonPin, INPUT_PULLUP);
}

void loop()
{
    // Read the button state
    int buttonState = digitalRead(buttonPin);

    // If the button is pressed, toggle storage mode
    if (buttonState == LOW)
    {
        isStoring = !isStoring;
        delay(250); // Debounce delay
    }

    if (isStoring)
    {
        // In storage mode, read the potentiometer and store values
        currentValue = analogRead(potentiometerPin);
        storedValue1 = currentValue; // Store the value in storedValue1
    }
    else
    {
        // In normal mode, read and use stored values
        currentValue = analogRead(potentiometerPin);
        storedValue2 = currentValue; // Store the value in storedValue2
    }

    // Print values to the serial monitor
    Serial.print("Potentiometer Value: ");
    Serial.println(currentValue);

    if (isStoring)
    {
        Serial.println("Storing Mode: ON");
    }
    else
    {
        Serial.println("Storing Mode: OFF");
    }

    // Add a small delay for stability
    delay(100);
}

// C++ code
//
#include <Adafruit_LiquidCrystal.h>

int seconds = 0;
int mode_select = 0;
int cup_select = 0;

unsigned long ptime;
unsigned long ntime;

bool MODE = 0;
bool isStoring = false;

const int pot = A0;
const int btn = 2;

Adafruit_LiquidCrystal lcd_1(0);

void setup()
{
    lcd_1.begin(16, 2);
    lcd_1.print("Smart Cooker");
    delay(2000);
    pinMode(btn, INPUT_PULLUP);
    Serial.begin(9600);
}

void loop()
{

    int buttonState = digitalRead(btn);

    // If the button is pressed, toggle storage mode
    if (buttonState == HIGH)
    {
        isStoring = !isStoring;
        delay(1000); // Debounce delay
    }

    if (isStoring)
    {
        // In storage mode, read the potentiometer and store values
        mode_select = analogRead(pot); // Store the value in storedValue1
    }
    else
    {
        // In normal mode, read and use stored values
        cup_select = analogRead(pot); // Store the value in storedValue2
    }

    // Print values to the serial monitor
    Serial.print("Mode : ");
    Serial.println(mode_select);
    Serial.print("Cups : ");
    Serial.println(cup_select);

    if (isStoring)
    {
        Serial.println("Storing Mode: ON");
    }
    else
    {
        Serial.println("Storing Mode: OFF");
    }

    // Add a small delay for stability
    delay(100);

    /*
    MODE = digitalRead(btn);
      if (MODE)
      {
           mode_select = analogRead(A0);
      }

      if (MODE){
           cup_select = analogRead(A0);
        }

      Serial.println(MODE);

      Serial.print("mode select : ");
      Serial.println(mode_select);
      Serial.print("cup select : ");
      Serial.println(cup_select);



    */

    /*  if (mode_select <= 68)
      {
          lcd_1.setCursor(0, 1);
          lcd_1.clear();
          lcd_1.print("White Rice");

          delay(500);

          lcd_1.clear();*/
    // Serial.println("Pushbutton state: ");

    // if (digitalRead(buttonPin) == HIGH || mode_1 == 1)
    // {
    //     mode_1 = 1;

    //     if (potValue <= 256)
    //     {
    //         lcd_1.clear();
    //         lcd_1.print("1 Cup Rice");
    //         delay(3000);
    //         lcd_1.clear();

    //         if (digitalRead(buttonPin) == HIGH || cup_1 == 1)
    //         {
    //             cup_1 = 1;

    //             // Jump to start cooking function
    //             clock(1);
    //             drain_servo(15000);
    //             int mode_1 = 0;
    //             int cup_1 = 0;
    //             int pos = 0;
    //         }
    //     }
    // }
    //  }

    //  lcd_1.setCursor(0, 1);
    //  lcd_1.print("Mode : 1");
    //  lcd_1.setBacklight(1);

    // delay(500); // Wait for 500 millisecond(s)
    // lcd_1.setBacklight(0);
    // delay(500); // Wait for 500 millisecond(s)
    // seconds += 1;
}





// C++ code
//
#include <Adafruit_LiquidCrystal.h>

int seconds = 0;
int mode_select = 0;
int current_value = 0;
int cup_select =0;

unsigned long ptime = 2;
unsigned long ntime = 4;
  
bool MODE = 0;
bool isStoring = 1;

const int pot = A0;
const int btn = 2;

Adafruit_LiquidCrystal lcd_1(0);

void setup()
{
  lcd_1.begin(16, 2);
  lcd_1.print("Smart Cooker");
  delay(500);
  pinMode(btn, INPUT_PULLUP);
  Serial.begin(9600);
  
}

void loop()
{
  
  
  
  
  int buttonState = digitalRead(btn);

  if (buttonState == HIGH) {
    isStoring = !isStoring;
    delay(1000); // Debounce delay
  }
  
  if (isStoring) {
    
  current_value = analogRead(pot);
    mode_select = current_value;

    
  } else{

    current_value = analogRead(pot);
    cup_select = current_value; 
    
  }

  Serial.print("Mode : ");
  Serial.println(mode_select);
  Serial.print("Cups : ");
  Serial.println(cup_select);

  /*if (!isStoring) {
    Serial.println("Storing Mode: ON");
  } else {
    Serial.println("Storing Mode: OFF");
  }*/

  delay(100);
  
  if(mode_select){
    
  
  }
  
}



//////////////////////////////////////////////////////////////////////////////////////////////
// working if condition

// C++ code
//
#include <Adafruit_LiquidCrystal.h>

int seconds = 0;
int a = 0;
int b = 0;
int mode_select = 0;
int current_value = 0;
int cup_select = 0;

unsigned long ptime = 2;
unsigned long ntime = 4;

bool MODE = 0;
bool isStoring = 0;

const int pot = A0;
const int btn = 2;

Adafruit_LiquidCrystal lcd_1(0);

void setup()
{
    lcd_1.begin(16, 2);
    lcd_1.print("Smart Cooker");
    delay(500);
    pinMode(btn, INPUT_PULLUP);
    Serial.begin(9600);
}

void loop()
{

    int buttonState = digitalRead(btn);

    if (buttonState == HIGH)
    {
        isStoring = !isStoring;
        delay(1000); // Debounce delay
      
      if (isStoring)
    {

        current_value = analogRead(pot);
        a = current_value;
    }
    
    else
    {

        current_value = analogRead(pot);
        b = current_value;
    }
    }

    
  mode_select = a;
  cup_select = b;


    Serial.print("Mode : ");
    Serial.println(mode_select);
    Serial.print("Cups : ");
    Serial.println(cup_select);
    //Serial.println("Cooking mode selected ");


    /*if (!isStoring) {
      Serial.println("Storing Mode: ON");
    } else {
      Serial.println("Storing Mode: OFF");
    }*/

    delay(100);

    // ------------------------------Mode1--------------------------------

    // ---------------Cup1----------------
    if (mode_select > 0 && mode_select <= 73 && cup_select > 0 && cup_select <= 255)
    {

        lcd_1.clear();
        lcd_1.setCursor(0, 0);
        lcd_1.print("White Rice");
        lcd_1.setCursor(0, 1);
        lcd_1.print("Cups : 1");
        digitalWrite(LED_BUILTIN, HIGH); // heater on
        delay(5200);                     // Timer for 32 mins
        cooking_done();
    }

    }

    void cooking_done()
    {
        lcd_1.clear();
        lcd_1.setCursor(0, 0);
        lcd_1.print("Cooking Done");
    }





//////////////////////////////////////////////////////////////////////////////////////////////




// C++ code
//
#include <Adafruit_LiquidCrystal.h>

int seconds = 0;
int a = 0;
int b = 0;
int mode_select = 0;
int current_value = 0;
int cup_select = 0;

unsigned long ptime = 2;
unsigned long ntime = 4;

bool MODE = 0;
bool isStoring = 0;

const int pot = A0;
const int btn = 2;

Adafruit_LiquidCrystal lcd_1(0);

void setup()
{
    lcd_1.begin(16, 2);
    lcd_1.print("Smart Cooker");
    delay(500);
    pinMode(btn, INPUT_PULLUP);
    Serial.begin(9600);
}

void loop()
{

    int buttonState = digitalRead(btn);

    if (buttonState == HIGH)
    {
        isStoring = !isStoring;
        delay(1000); // Debounce delay
      
      if (isStoring)
    {

        current_value = analogRead(pot);
        a = current_value;
    }
    
    else
    {

        current_value = analogRead(pot);
        b = current_value;
    }
    }

    
  mode_select = a;
  cup_select = b;


    Serial.print("Mode : ");
    Serial.println(mode_select);
    Serial.print("Cups : ");
    Serial.println(cup_select);
    //Serial.println("Cooking mode selected ");


    /*if (!isStoring) {
      Serial.println("Storing Mode: ON");
    } else {
      Serial.println("Storing Mode: OFF");
    }*/

    delay(100);

    // ------------------------------Mode1--------------------------------

    // ---------------Cup1----------------
    if (mode_select > 0 && mode_select <= 73 && cup_select > 0 && cup_select <= 255)
    {

        lcd_1.clear();
        lcd_1.setCursor(0, 0);
        lcd_1.print("White Rice");
        lcd_1.setCursor(0, 1);
        lcd_1.print("Cups : 1");
        digitalWrite(LED_BUILTIN, HIGH); // heater on
        delay(5200);                     // Timer for 32 mins
        cooking_done();
    }
    // ---------------Cup2----------------
    if (mode_select > 0 && mode_select <= 73 && cup_select >= 256 && cup_select <= 511)
    {

        lcd_1.clear();
        lcd_1.setCursor(0, 0);
        lcd_1.print("White Rice");
        lcd_1.setCursor(0, 1);
        lcd_1.print("Cups : 2");
        digitalWrite(LED_BUILTIN, HIGH); // heater on
        delay(3500);                     // Timer for 35 mins
        cooking_done();
    }
    // ---------------Cup3----------------
    if (mode_select > 0 && mode_select <= 73 && cup_select >= 512 && cup_select <= 767)
    {
        lcd_1.clear();
        lcd_1.setCursor(0, 0);
        lcd_1.print("White Rice");
        lcd_1.setCursor(0, 1);
        lcd_1.print("Cups : 3");
        digitalWrite(LED_BUILTIN, HIGH); // heater on
        delay(3800);                     // Timer for 38 mins
        cooking_done();
    }
    // ---------------Cup4----------------
    if (mode_select > 0 && mode_select <= 73 && cup_select >= 768 && cup_select <= 1023)
    {
        lcd_1.clear();
        lcd_1.setCursor(0, 0);
        lcd_1.print("White Rice");
        lcd_1.setCursor(0, 1);
        lcd_1.print("Cups : 4");
        digitalWrite(LED_BUILTIN, HIGH); // heater on
        delay(4200);                     // Timer for 42 mins
        cooking_done();
    }




    // ---------------------------------Mode2--------------------------------

    // ---------------Cup1----------------
    if (mode_select >= 74 && mode_select <= 146 && cup_select > 0 && cup_select <= 255)
    {

        lcd_1.clear();
        lcd_1.setCursor(0, 0);
        lcd_1.print("Black Rice");
        lcd_1.setCursor(0, 1);
        lcd_1.print("Cups : 1");
        digitalWrite(LED_BUILTIN, HIGH); // heater on
        delay(5500);                     // Timer for 55 mins
        cooking_done();
    }
    // ---------------Cup2----------------
    if (mode_select >= 74 && mode_select <= 146 && cup_select >= 256 && cup_select <= 511)
    {

        lcd_1.clear();
        lcd_1.setCursor(0, 0);
        lcd_1.print("Black Rice");
        lcd_1.setCursor(0, 1);
        lcd_1.print("Cups : 2");
        digitalWrite(LED_BUILTIN, HIGH); // heater on
        delay(5700);                     // Timer for 57 mins
        cooking_done();
    }
    // ---------------Cup3----------------
    if (mode_select >= 74 && mode_select <= 146 && cup_select >= 512 && cup_select <= 767)
    {
        lcd_1.clear();
        lcd_1.setCursor(0, 0);
        lcd_1.print("Black Rice");
        lcd_1.setCursor(0, 1);
        lcd_1.print("Cups : 3");
        digitalWrite(LED_BUILTIN, HIGH); // heater on
        delay(6100);                     // Timer for 61 mins
        cooking_done();
    }
    // ---------------Cup4----------------
    if (mode_select >= 74 && mode_select <= 146 && cup_select >= 768 && cup_select <= 1023)
    {
        /////// Cannot cook
        // lcd_1.clear();
        // lcd_1.setCursor(0, 0);
        // lcd_1.print("Black Rice");
        // lcd_1.setCursor(0, 1);
        // lcd_1.print("Cups : 4");
        // digitalWrite(LED_BUILTIN, HIGH); // heater on
        // delay(6200);                     // Timer for 62 mins
        // cooking_done();
    }

    // ---------------------------------Mode3--------------------------------

    // ---------------Cup1----------------
    if (mode_select >= 147 && mode_select <= 219 && cup_select > 0 && cup_select <= 255)
    {

        lcd_1.clear();
        lcd_1.setCursor(0, 0);
        lcd_1.print("Brown Rice");
        lcd_1.setCursor(0, 1);
        lcd_1.print("Cups : 1");
        digitalWrite(LED_BUILTIN, HIGH); // heater on
        delay(5500);                     // Timer for 55 mins
        cooking_done();
    }
    // ---------------Cup2----------------
    if (mode_select >= 147 && mode_select <= 219 && cup_select >= 256 && cup_select <= 511)
    {

        lcd_1.clear();
        lcd_1.setCursor(0, 0);
        lcd_1.print("Brown Rice");
        lcd_1.setCursor(0, 1);
        lcd_1.print("Cups : 2");
        digitalWrite(LED_BUILTIN, HIGH); // heater on
        delay(5700);                     // Timer for 57 mins
        cooking_done();
    }
    // ---------------Cup3----------------
    if (mode_select >= 147 && mode_select <= 219 && cup_select >= 512 && cup_select <= 767)
    {
        lcd_1.clear();
        lcd_1.setCursor(0, 0);
        lcd_1.print("Brown Rice");
        lcd_1.setCursor(0, 1);
        lcd_1.print("Cups : 3");
        digitalWrite(LED_BUILTIN, HIGH); // heater on
        delay(6100);                     // Timer for 61 mins
        cooking_done();
    }
    // ---------------Cup4----------------
    if (mode_select >= 147 && mode_select <= 219 && cup_select >= 768 && cup_select <= 1023)
    {
        /////// Cannot cook
        // lcd_1.clear();
        // lcd_1.setCursor(0, 0);
        // lcd_1.print("Brown Rice");
        // lcd_1.setCursor(0, 1);
        // lcd_1.print("Cups : 4");
        // digitalWrite(LED_BUILTIN, HIGH); // heater on
        // delay(6200);                     // Timer for 62 mins
        // cooking_done();
    }



    // ---------------------------------Mode4--------------------------------
    if (mode_select >= 220 && mode_select <= 292 && cup_select > 0 && cup_select <= 255)
    {

        lcd_1.clear();
        lcd_1.setCursor(0, 0);
        lcd_1.print("Red Rice");
        lcd_1.setCursor(0, 1);
        lcd_1.print("Cups : 1");
        digitalWrite(LED_BUILTIN, HIGH); // heater on
        delay(5500);                     // Timer for 55 mins
        cooking_done();
    }
    // ---------------Cup2----------------
    if (mode_select >= 220 && mode_select <= 292 && cup_select >= 256 && cup_select <= 511)
    {

        lcd_1.clear();
        lcd_1.setCursor(0, 0);
        lcd_1.print("Red Rice");
        lcd_1.setCursor(0, 1);
        lcd_1.print("Cups : 2");
        digitalWrite(LED_BUILTIN, HIGH); // heater on
        delay(5700);                     // Timer for 57 mins
        cooking_done();
    }
    // ---------------Cup3----------------
    if (mode_select >= 220 && mode_select <= 292 && cup_select >= 512 && cup_select <= 767)
    {
        lcd_1.clear();
        lcd_1.setCursor(0, 0);
        lcd_1.print("Red Rice");
        lcd_1.setCursor(0, 1);
        lcd_1.print("Cups : 3");
        digitalWrite(LED_BUILTIN, HIGH); // heater on
        delay(6300);                     // Timer for 63 mins
        cooking_done();
    }
    // ---------------Cup4----------------
    if (mode_select >= 220 && mode_select <= 292 && cup_select >= 768 && cup_select <= 1023)
    {
        /////// Cannot cook
        // lcd_1.clear();
        // lcd_1.setCursor(0, 0);
        // lcd_1.print("Red Rice");
        // lcd_1.setCursor(0, 1);
        // lcd_1.print("Cups : 4");
        // digitalWrite(LED_BUILTIN, HIGH); // heater on
        // delay(6200);                     // Timer for 62 mins
        // cooking_done();
    }




    // ---------------------------------Rice---------------------------------
    // ---------------------------------Mode5--------------------------------

    // ---------------Cup1----------------
    if (mode_select >= 293 && mode_select <= 365 && cup_select > 0 && cup_select <= 255)
    {

        lcd_1.clear();
        lcd_1.setCursor(0, 0);
        lcd_1.print("Quinoa Rice");
        lcd_1.setCursor(0, 1);
        lcd_1.print("Cups : 1");
        digitalWrite(LED_BUILTIN, HIGH); // heater on
        delay(4200);                     // Timer for 42 mins
        cooking_done();
    }
    // ---------------Cup2----------------
    if (mode_select >= 293 && mode_select <= 365 && cup_select >= 256 && cup_select <= 511)
    {

        lcd_1.clear();
        lcd_1.setCursor(0, 0);
        lcd_1.print("Quinoa Rice");
        lcd_1.setCursor(0, 1);
        lcd_1.print("Cups : 2");
        digitalWrite(LED_BUILTIN, HIGH); // heater on
        delay(4400);                     // Timer for 44 mins
        cooking_done();
    }
    // ---------------Cup3----------------
    if (mode_select >= 293 && mode_select <= 365 && cup_select >= 512 && cup_select <= 767)
    {
        lcd_1.clear();
        lcd_1.setCursor(0, 0);
        lcd_1.print("Quinoa Rice");
        lcd_1.setCursor(0, 1);
        lcd_1.print("Cups : 3");
        digitalWrite(LED_BUILTIN, HIGH); // heater on
        delay(4400);                     // Timer for 44 mins
        cooking_done();
    }
    // ---------------Cup4----------------
    if (mode_select >= 293 && mode_select <= 365 && cup_select >= 768 && cup_select <= 1023)
    {
        lcd_1.clear();
        lcd_1.setCursor(0, 0);
        lcd_1.print("Quinoa Rice");
        lcd_1.setCursor(0, 1);
        lcd_1.print("Cups : 4");
        digitalWrite(LED_BUILTIN, HIGH); // heater on
        delay(4700);                     // Timer for 47 mins
        cooking_done();
    }


    // ---------------------------------Mode6--------------------------------

    // ---------------Cup1----------------
    if (mode_select >= 366 && mode_select <= 438 && cup_select > 0 && cup_select <= 255)
    {

        lcd_1.clear();
        lcd_1.setCursor(0, 0);
        lcd_1.print("Basmati Rice");
        lcd_1.setCursor(0, 1);
        lcd_1.print("Cups : 1");
        digitalWrite(LED_BUILTIN, HIGH); // heater on
        delay(1500);                     // Timer for 15 mins
        cooking_done();
    }
    // ---------------Cup2----------------
    if (mode_select >= 366 && mode_select <= 438 && cup_select >= 256 && cup_select <= 511)
    {

        lcd_1.clear();
        lcd_1.setCursor(0, 0);
        lcd_1.print("Basmati Rice");
        lcd_1.setCursor(0, 1);
        lcd_1.print("Cups : 2");
        digitalWrite(LED_BUILTIN, HIGH); // heater on
        delay(1800);                     // Timer for 18 mins
        cooking_done();
    }
    // ---------------Cup3----------------
    if (mode_select >= 366 && mode_select <= 438 && cup_select >= 512 && cup_select <= 767)
    {
        lcd_1.clear();
        lcd_1.setCursor(0, 0);
        lcd_1.print("Basmati Rice");
        lcd_1.setCursor(0, 1);
        lcd_1.print("Cups : 3");
        digitalWrite(LED_BUILTIN, HIGH); // heater on
        delay(2200);                     // Timer for 22 mins
        cooking_done();
    }
    // ---------------Cup4----------------
    if (mode_select >= 366 && mode_select <= 438 && cup_select >= 768 && cup_select <= 1023)
    {
        lcd_1.clear();
        lcd_1.setCursor(0, 0);
        lcd_1.print("Basmati Rice");
        lcd_1.setCursor(0, 1);
        lcd_1.print("Cups : 4");
        digitalWrite(LED_BUILTIN, HIGH); // heater on
        delay(2600);                     // Timer for 26 mins
        cooking_done();
    }

    // ---------------------------------Mode7--------------------------------

    // ---------------Cup1----------------
    if (mode_select >= 439 && mode_select <= 511 && cup_select > 0 && cup_select <= 255)
    {

        lcd_1.clear();
        lcd_1.setCursor(0, 0);
        lcd_1.print("Single B Rice");
        lcd_1.setCursor(0, 1);
        lcd_1.print("Cups : 1");
        digitalWrite(LED_BUILTIN, HIGH); // heater on
        delay(3200);                     // Timer for 32 mins
        cooking_done();
    }
    // ---------------Cup2----------------
    if (mode_select >= 439 && mode_select <= 511 && cup_select >= 256 && cup_select <= 511)
    {

        lcd_1.clear();
        lcd_1.setCursor(0, 0);
        lcd_1.print("Single B Rice");
        lcd_1.setCursor(0, 1);
        lcd_1.print("Cups : 2");
        digitalWrite(LED_BUILTIN, HIGH); // heater on
        delay(3500);                     // Timer for 35 mins
        cooking_done();
    }
    // ---------------Cup3----------------
    if (mode_select >= 439 && mode_select <= 511 && cup_select >= 512 && cup_select <= 767)
    {
        lcd_1.clear();
        lcd_1.setCursor(0, 0);
        lcd_1.print("Single B Rice");
        lcd_1.setCursor(0, 1);
        lcd_1.print("Cups : 3");
        digitalWrite(LED_BUILTIN, HIGH); // heater on
        delay(3800);                     // Timer for 38 mins
        cooking_done();
    }
    // ---------------Cup4----------------
    if (mode_select >= 439 && mode_select <= 511 && cup_select >= 768 && cup_select <= 1023)
    {
        lcd_1.clear();
        lcd_1.setCursor(0, 0);
        lcd_1.print("Single B Rice");
        lcd_1.setCursor(0, 1);
        lcd_1.print("Cups : 4");
        digitalWrite(LED_BUILTIN, HIGH); // heater on
        delay(4200);                     // Timer for 42 mins
        cooking_done();
    }

    // ---------------------------------Mode8--------------------------------

    // ---------------Cup1----------------
    if (mode_select >= 512 && mode_select <= 584 && cup_select > 0 && cup_select <= 255)
    {

        lcd_1.clear();
        lcd_1.setCursor(0, 0);
        lcd_1.print("Double B Rice");
        lcd_1.setCursor(0, 1);
        lcd_1.print("Cups : 1");
        digitalWrite(LED_BUILTIN, HIGH); // heater on
        delay(3500);                     // Timer for 35 mins
        cooking_done();
    }
    // ---------------Cup2----------------
    if (mode_select >= 512 && mode_select <= 584 && cup_select >= 256 && cup_select <= 511)
    {

        lcd_1.clear();
        lcd_1.setCursor(0, 0);
        lcd_1.print("Double B Rice");
        lcd_1.setCursor(0, 1);
        lcd_1.print("Cups : 2");
        digitalWrite(LED_BUILTIN, HIGH); // heater on
        delay(3800);                     // Timer for 38 mins
        cooking_done();
    }
    // ---------------Cup3----------------
    if (mode_select >= 512 && mode_select <= 584 && cup_select >= 512 && cup_select <= 767)
    {
        lcd_1.clear();
        lcd_1.setCursor(0, 0);
        lcd_1.print("Double B Rice");
        lcd_1.setCursor(0, 1);
        lcd_1.print("Cups : 3");
        digitalWrite(LED_BUILTIN, HIGH); // heater on
        delay(4200);                     // Timer for 42 mins
        cooking_done();
    }
    // ---------------Cup4----------------
    if (mode_select >= 512 && mode_select <= 584 && cup_select >= 768 && cup_select <= 1023)
    {
        lcd_1.clear();
        lcd_1.setCursor(0, 0);
        lcd_1.print("Double B Rice");
        lcd_1.setCursor(0, 1);
        lcd_1.print("Cups : 4");
        digitalWrite(LED_BUILTIN, HIGH); // heater on
        delay(4600);                     // Timer for 46 mins
        cooking_done();
    }

    // ---------------------------------Mode9--------------------------------

    // ---------------Cup1----------------
    if (mode_select >= 585 && mode_select <= 657 && cup_select > 0 && cup_select <= 255)
    {

        lcd_1.clear();
        lcd_1.setCursor(0, 0);
        lcd_1.print("Raw Rice");
        lcd_1.setCursor(0, 1);
        lcd_1.print("Cups : 1");
        digitalWrite(LED_BUILTIN, HIGH); // heater on
        delay(2000);                     // Timer for 20 mins
        cooking_done();
    }
    // ---------------Cup2----------------
    if (mode_select >= 585 && mode_select <= 657 && cup_select >= 256 && cup_select <= 511)
    {

        lcd_1.clear();
        lcd_1.setCursor(0, 0);
        lcd_1.print("Raw Rice");
        lcd_1.setCursor(0, 1);
        lcd_1.print("Cups : 2");
        digitalWrite(LED_BUILTIN, HIGH); // heater on
        delay(2300);                     // Timer for 23 mins
        cooking_done();
    }
    // ---------------Cup3----------------
    if (mode_select >= 585 && mode_select <= 657 && cup_select >= 512 && cup_select <= 767)
    {
        lcd_1.clear();
        lcd_1.setCursor(0, 0);
        lcd_1.print("Raw Rice");
        lcd_1.setCursor(0, 1);
        lcd_1.print("Cups : 3");
        digitalWrite(LED_BUILTIN, HIGH); // heater on
        delay(2700);                     // Timer for 27 mins
        cooking_done();
    }
    // ---------------Cup4----------------
    if (mode_select >= 585 && mode_select <= 657 && cup_select >= 768 && cup_select <= 1023)
    {
        lcd_1.clear();
        lcd_1.setCursor(0, 0);
        lcd_1.print("Raw Rice");
        lcd_1.setCursor(0, 1);
        lcd_1.print("Cups : 4");
        digitalWrite(LED_BUILTIN, HIGH); // heater on
        delay(3100);                     // Timer for 31 mins
        cooking_done();
    }




    // -------------------------------Vegetables------------------------------
    // ---------------------------------Mode10--------------------------------


    if (mode_select >= 658 && mode_select <= 730)
    {

        lcd_1.clear();
        lcd_1.setCursor(0, 0);
        lcd_1.print("Carrot");
        lcd_1.setCursor(0, 1);
        lcd_1.print("Preating 5-9 mins");
        digitalWrite(LED_BUILTIN, HIGH); // heater on
        delay(5500);                     // Timer for 5-9 mins

        digitalWrite(LED_BUILTIN, LOW); // Active cooking
        delay(1200);                    // Timer for 12 mins
        cooking_done();
    }

    // ---------------------------------Mode11--------------------------------
    if (mode_select >= 731 && mode_select <= 803)
    {

        lcd_1.clear();
        lcd_1.setCursor(0, 0);
        lcd_1.print("Cabbage");
        lcd_1.setCursor(0, 1);
        lcd_1.print("Preating 5-9 mins");
        digitalWrite(LED_BUILTIN, HIGH); // heater on
        delay(5500);                     // Timer for 5-9 mins

        digitalWrite(LED_BUILTIN, LOW); // Active cooking
        delay(1100);                    // Timer for 11 mins
        cooking_done();
    }

    // ---------------------------------Mode12--------------------------------
    if (mode_select >= 804 && mode_select <= 876)
    {

        lcd_1.clear();
        lcd_1.setCursor(0, 0);
        lcd_1.print("Green Peas");
        lcd_1.setCursor(0, 1);
        lcd_1.print("Preating 5-9 mins");
        digitalWrite(LED_BUILTIN, HIGH); // heater on
        delay(5500);                     // Timer for 5-9 mins

        digitalWrite(LED_BUILTIN, LOW); // Active cooking
        delay(8000);                    // Timer for 8 mins
        cooking_done();
    }

    // ---------------------------------Mode13--------------------------------
    if (mode_select >= 877 && mode_select <= 949)
    {

        lcd_1.clear();
        lcd_1.setCursor(0, 0);
        lcd_1.print("Spinach");
        lcd_1.setCursor(0, 1);
        lcd_1.print("Preating 5-9 mins");
        digitalWrite(LED_BUILTIN, HIGH); // heater on
        delay(5500);                     // Timer for 5-9 mins

        digitalWrite(LED_BUILTIN, LOW); // Active cooking
        delay(300);                    // Timer for 3 mins
        cooking_done();
    }

    // ---------------------------------Mode14--------------------------------
    if (mode_select >= 950 && mode_select <= 1022)
    {

        lcd_1.clear();
        lcd_1.setCursor(0, 0);
        lcd_1.print("Potato");
        lcd_1.setCursor(0, 1);
        lcd_1.print("Preating 5-9 mins");
        digitalWrite(LED_BUILTIN, HIGH); // preheater on
        delay(5500);                     // Timer for 5-9 mins

        digitalWrite(LED_BUILTIN, LOW); // Active cooking
        delay(1200);                    // Timer for 12 mins
        cooking_done();
    }
}

    void cooking_done()
    {
        lcd_1.clear();
        lcd_1.setCursor(0, 0);
        lcd_1.print("Cooking Done");
    }
