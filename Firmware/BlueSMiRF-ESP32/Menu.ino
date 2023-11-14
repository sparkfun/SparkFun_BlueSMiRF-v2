void menuMain()
{
    while (1)
    {
        Serial.println("Menu: Main");

        Serial.printf("1) Number of scales: %d\r\n", 4);

        Serial.printf("2) Number of readings that must be within max percent to be considered stable: %d\r\n",
                      2);

        Serial.println("f) Reset settings to defaults");

        Serial.println("r) Reset system");

        Serial.println("x) Exit");

        byte incoming = getCharacterNumber();

        if (incoming == 1)
        {
            Serial.print("Enter number of scales (1 to 16): ");
            int numberOfScales = getNumber(); // Returns EXIT, TIMEOUT, or long
            if ((numberOfScales != INPUT_RESPONSE_GETNUMBER_EXIT) &&
                (numberOfScales != INPUT_RESPONSE_GETNUMBER_TIMEOUT))
            {
                if (numberOfScales < 1 || numberOfScales > 16)
                    Serial.println("Error: Number out of range");
                else
                    Serial.println("setting set");
            }
        }
        else if (incoming == 2)
        {
            getNewSetting("Enter number for stableCheckAmount", 4, 128, &settings.baudRate);
        }

        else if (incoming == 'f')
        {
            Serial.print("Are you sure you want to erase everything? ('y' to continue): ");
            int choice = getCharacterNumber(); // Returns EXIT, TIMEOUT, or long
            if (choice == 'y')
            {
                // systemSettings.clear(); //Erase all NVM settings
                Settings defaultSettings;
                settings = defaultSettings;
                recordSystemSettings();
                Serial.println("Reset to defaults. Resetting. Goodbye!");
                ESP.restart();
            }
            else
                Serial.println("Aborted!");
        }
        else if (incoming == 'r')
        {
            ESP.restart();
        }
        else if (incoming == 'x')
            break;
        else if (incoming == INPUT_RESPONSE_GETCHARACTERNUMBER_EMPTY)
            break;
        else if (incoming == INPUT_RESPONSE_GETCHARACTERNUMBER_TIMEOUT)
            break;
        else
            printUnknown(incoming);
    }

    Serial.println("Exit main menu");

    clearSerialBuffer();

    recordSystemSettings(); // Save settings struct to NVM
}

void getNewSetting(const char *settingPrompt, int min, int max, int *setting)
{
    while (1)
    {
        Serial.printf("%s (or x to exit): ", settingPrompt);
        int enteredValue = getNumber(); // Returns EXIT, TIMEOUT, or long
        if ((enteredValue == INPUT_RESPONSE_GETNUMBER_EXIT) || (enteredValue == INPUT_RESPONSE_GETNUMBER_TIMEOUT))
            break;

        if (enteredValue >= min && enteredValue <= max)
        {
            *setting = enteredValue; // Recorded to NVM and file at main menu exit
            break;
        }
        else
            Serial.println("Error: Number out of range");
    }
}

void getNewSetting(const char *settingPrompt, float min, float max, float *setting)
{
    while (1)
    {
        Serial.printf("%s [min: %0.2f max: %0.2f] (or x to exit): ", settingPrompt, min, max);
        double enteredValue = getDouble();
        if ((enteredValue == INPUT_RESPONSE_GETNUMBER_EXIT) || (enteredValue == INPUT_RESPONSE_GETNUMBER_TIMEOUT))
            break;

        if (enteredValue >= min && enteredValue <= max)
        {
            *setting = enteredValue; // Recorded to NVM and file at main menu exit
            break;
        }
        else
            Serial.println("Error: Number out of range");
    }
}
