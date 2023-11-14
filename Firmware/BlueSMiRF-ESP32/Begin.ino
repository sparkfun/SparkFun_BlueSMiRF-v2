// Based on hardware features, determine if this is RTK Surveyor or RTK Express hardware
// Must be called after beginI2C (Wire.begin) so that we can do I2C tests
// Must be called after beginGNSS so the GNSS type is known
void beginBoard()
{
    // TODO look up fuses
    productVariant = BLUESMIRF_01;

    // Setup hardware pins
    if (productVariant == BLUESMIRF_01)
    {
        pin_pairButton = 0;
        pin_cts = 19; // Input
        pin_rts = 22; // Output
        pin_statusLED = 13;
        pin_connectLED = 14;

        strncpy(platformPrefix, "BlueSMiRF", sizeof(platformPrefix) - 1);

        pinMode(pin_cts, INPUT); // Has external pullup

        pinMode(pin_rts, OUTPUT);
        rtsDeassert(); // Tell external system we don't want data until we have completed getting setup.
    }

    char versionString[21];
    getFirmwareVersion(versionString, sizeof(versionString), true);
    systemPrintf("%s-%s\r\n", platformPrefix, versionString); // Report system name/version before starting

    // Get unit MAC address
    esp_read_mac(btMACAddress, ESP_MAC_WIFI_STA);
    btMACAddress[5] +=
        2; // Convert MAC address to Bluetooth MAC (add 2):
           // https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/system/system.html#mac-address

    // For all boards, check reset reason. If reset was due to wdt or panic, append last log
    if ((esp_reset_reason() == ESP_RST_POWERON) || (esp_reset_reason() == ESP_RST_SW))
    {
        // Normal start
    }
    else
    {
        systemPrint("Reset reason: ");
        switch (esp_reset_reason())
        {
        case ESP_RST_UNKNOWN:
            systemPrintln("ESP_RST_UNKNOWN");
            break;
        case ESP_RST_POWERON:
            systemPrintln("ESP_RST_POWERON");
            break;
        case ESP_RST_SW:
            systemPrintln("ESP_RST_SW");
            break;
        case ESP_RST_PANIC:
            systemPrintln("ESP_RST_PANIC");
            break;
        case ESP_RST_INT_WDT:
            systemPrintln("ESP_RST_INT_WDT");
            break;
        case ESP_RST_TASK_WDT:
            systemPrintln("ESP_RST_TASK_WDT");
            break;
        case ESP_RST_WDT:
            systemPrintln("ESP_RST_WDT");
            break;
        case ESP_RST_DEEPSLEEP:
            systemPrintln("ESP_RST_DEEPSLEEP");
            break;
        case ESP_RST_BROWNOUT:
            systemPrintln("ESP_RST_BROWNOUT");
            break;
        case ESP_RST_SDIO:
            systemPrintln("ESP_RST_SDIO");
            break;
        default:
            systemPrintln("Unknown");
        }
    }
}