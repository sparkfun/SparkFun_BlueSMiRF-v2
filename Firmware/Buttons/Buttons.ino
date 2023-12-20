/*

*/

// Buttons - Interrupt driven and debounce
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
#include <JC_Button.h>      //http://librarymanager/All#JC_Button v2.1.2
Button *pairButton = nullptr;

TaskHandle_t ButtonCheckTaskHandle = nullptr;
const uint8_t ButtonCheckTaskPriority = 0; // 3 being the highest, and 0 being the lowest
const int buttonTaskStackSize = 2000;
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

const uint8_t PIN_UNDEFINED = 255;

int pin_pairButton = 0; // Use the boot button for testing

int pin_statusLED = 13;
int pin_connectLED = 255;

uint8_t buffer[512];

void setup()
{
  Serial.begin(115200);
  delay(250);
  Serial.println("Button test");

  buttonBegin();

  ledBegin();
}

void loop()
{

}

// Reset system to defaults and blink LEDs until button is released
void buttonFactoryDefaults()
{
  factoryDefaults(); // Set settings struct to defaults
  recordSystemSettings();  // Record current settings struct to NVM

  systemPrintln("Factory defaults applied");

  //Pre-set LEDs ready for blink
  ledStatusOn();
  ledConnectOff();
  
  while (readPairButton() == LOW)
  {
    ledStatusBlink();
    ledConnectBlink();
    delay(250);
  }

  //Ensure LEDs are off
  ledStatusOff();
  ledConnectOff();
 
  systemPrintln("System resetting");
  delay(50);
  //systemFlush(); //Allow print to complete

  ESP.restart();
}

uint8_t readPairButton()
{
  if (pin_pairButton == 255)
    return (HIGH);
  return (digitalRead(pin_pairButton));
}

//Place holders
void factoryDefaults() {}
void recordSystemSettings() {}

void systemPrintln(char *toPrint)
{
  Serial.println(toPrint);
}

void systemFlush()
{
  Serial.flush();
}
