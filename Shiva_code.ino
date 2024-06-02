#include <Adafruit_LiquidCrystal.h>

Adafruit_LiquidCrystal lcd_2(0);

const int potPin = A0;
const int buttonPin = 2;
const int heaterPin = 13; // Assuming the LED is connected to pin 13
const int ledPin = 10;   // LED pin for warm mode
const int numModes = 9;  // Number of modes
const int numCups = 4;   // Number of cups
const int debounceDelay = 50;

const char *modes[] = {
    "White Rice",
    "Brown Rice",
    "Black Rice",
    "Red Rice",
    "Quinoa",
    "Basmati",
    "1*White Rice",
    "2*White Rice",
    "Raw Rice",
};
const char *cups[] = {
    "1 Cup",
    "2 Cups",
    "3 Cups",
    "4 Cups",
};

int selectedMode = -1; // Initially, no mode is selected
int selectedCup = -1;  // Initially, no cup is selected
int potValue = 0;
int lastButtonState = HIGH;
int currentButtonState = HIGH;
bool modeSelected = false;
bool cupSelected = false;
unsigned long startTime = 0;
unsigned long duration = 0;

void setup()
{
    lcd_2.begin(16, 2);
    pinMode(buttonPin, INPUT_PULLUP);
    pinMode(ledPin, OUTPUT);
    pinMode(heaterPin, OUTPUT);
    lcd_2.setCursor(0, 0);
    lcd_2.print("Smart Cooker");
    delay(1000);
    lcd_2.clear();
    Serial.begin(9600);
}

void loop()
{
    potValue = analogRead(potPin);

    if (!modeSelected)
    {
        int mode = map(potValue, 0, 1023, 0, numModes - 1);
        displayModeSelection(mode);
    }
    else if (!cupSelected)
    {
        int cup = map(potValue, 0, 1023, 0, numCups - 1);
        displayCupSelection(cup);
    }
    else
    {
        if (duration > 0)
        {
            unsigned long currentTime = millis();
            if (currentTime - startTime < duration)
            {
                digitalWrite(heaterPin, HIGH);
            }
            else
            {
                digitalWrite(heaterPin, LOW);
                digitalWrite(ledPin, HIGH);
                delay(6000);
                digitalWrite(ledPin, LOW);
                duration = 0;
                cookingdone();
            }
        }
    }

    currentButtonState = digitalRead(buttonPin);

    if (currentButtonState != lastButtonState)
    {
        delay(debounceDelay);

        if (currentButtonState == HIGH)
        {
            if (!modeSelected)
            {
                modeSelected = true;
                selectedMode = map(potValue, 0, 1023, 0, numModes - 1);
                Serial.print(selectedMode);
                displayModeSelection(selectedMode);
            }
            else if (!cupSelected)
            {
                cupSelected = true;
                selectedCup = map(potValue, 0, 1023, 0, numCups - 1);
                Serial.print(selectedCup);
                displayCupSelection(selectedCup);
                setLedDuration();
            }
        }
    }

    lastButtonState = currentButtonState;
}

void displayModeSelection(int mode)
{
    lcd_2.print("             ");
    lcd_2.setCursor(0, 0);

    if (mode >= 0 && mode < numModes)
    {
        lcd_2.print(modes[mode]);
    }
}

void displayCupSelection(int cup)
{
    lcd_2.print("             ");
    lcd_2.setCursor(0, 1);

    if (cup >= 0 && cup < numCups)
    {
        lcd_2.print(cups[cup]);
    }
}

void setLedDuration()
{
    switch (selectedMode)
    {
    case 0: // White Rice
    case 1:
    case 2:
    case 3:
    case 4:
    case 5: // 1*White Rice
    case 6: // 2*White Rice
    case 7:
    case 8:
    case 9:
        switch (selectedCup)
        {
        case 0: // 1 Cup
            duration = 10000; // 1 minute
            break;
        case 1: // 2 Cups
            duration = 20000; // 2 minutes
            break;
        case 2: // 3 Cups
            duration = 30000; // 3 minutes
            break;
        case 3: // 4 Cups
            duration = 400; // 4 minutes
            break;
        }
        break;
    }
    startTime = millis();
}

void cookingdone()
{
    lcd_2.clear();
    lcd_2.print("Cooking done !!!");
    delay(1000);
    lcd_2.setCursor(0, 0);
    lcd_2.print("                 ");
    lcd_2.setCursor(0, 0);
    lcd_2.print("warm mode");
    delay(1000);
}
