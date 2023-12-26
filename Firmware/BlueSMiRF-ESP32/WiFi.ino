/*
  With the provided credentials, attempt to connect to WiFi. If new firmware
  is available, download then reset.
*/

bool wifiCheckNewFirmware()
{
    // Attempt to connect to WiFi
    if (wifiConnect() == false)
        return (false);

    char reportedVersion[50] = {'\0'};

    // Get firmware version from server
    if (otaCheckVersion(reportedVersion, sizeof(reportedVersion)))
    {
        // We got a version number, now determine if it's newer or not
        char currentVersion[21];
        getFirmwareVersion(currentVersion, sizeof(currentVersion));

        systemPrintf("Current firmware version: %s\r\n", currentVersion);
        systemPrintf("New firmware version available: %s\r\n", reportedVersion);

        // Allow update if locally compiled developer version
        if (isReportedVersionNewer(reportedVersion, &currentVersion[1]) == true || FIRMWARE_VERSION_MAJOR == 99)
        {
            return (true);
        }
        else
        {
            systemPrintln("No new firmware available");
        }
    }
    else
    {
        // Failed to get version number
        systemPrintln("Failed to get version number from server.");
    }
    return (false);
}

bool wifiUpdate()
{
    if (wifiConnect() == false)
        return (false);

    systemPrintln("Getting new firmware");

    otaUpdate();

    return (true);
}

bool wifiConnect()
{
    if (strnlen(settings.wifiSsid, sizeof(settings.wifiSsid)) == 0)
    {
        // Check if user just entered the WiFi credentials, they will be in the temp settings struct
        if (strnlen(tempSettings.wifiSsid, sizeof(settings.wifiSsid)) == 0)
        {
            systemPrintln("Please provide WiFi credentials before attempting to update firmware.");
            return (false);
        }
        else
        {
            // Move temp settings into settings
            strncpy(settings.wifiPassword, tempSettings.wifiPassword, sizeof(settings.wifiPassword));
            strncpy(settings.wifiSsid, tempSettings.wifiSsid, sizeof(settings.wifiSsid));
        }
    }

#ifdef COMPILE_WIFI

// The token is provided at compile time via build flags
#define DEVELOPMENT_TOKEN 0xAA, 0xBB, 0xCC, 0xDD, 0x00, 0x11, 0x22, 0x33, 0x0A, 0x0B, 0x0C, 0x0D, 0x00, 0x01, 0x02, 0x03
#ifndef BLUESMIRF_PRIVATE_REPO_TOKEN
#warning Using the DEVELOPMENT_TOKEN for github!
#define BLUESMIRF_PRIVATE_REPO_TOKEN DEVELOPMENT_TOKEN
#endif // BLUESMIRF_PRIVATE_REPO_TOKEN

    reportHeapNow();

    WiFiMulti wifiMulti;
    wifiMulti.addAP(settings.wifiSsid, settings.wifiPassword);

    systemPrintf("Connecting to %s... ", settings.wifiSsid);

    int wifiResponse = wifiMulti.run(10000); // Scan for up to 10s
    if (wifiResponse == WL_CONNECTED)
    {
        systemPrintln("Connected!");
    }
    else if (wifiResponse == WL_DISCONNECTED)
    {
        systemPrintln("No friendly WiFi networks detected.");
        return (false);
    }
    else
    {
        systemPrintf("WiFi failed to connect: error #%d.\r\n", wifiResponse);
        return (false);
    }

    reportHeapNow();

    return (true);
#else
    return (false);
#endif
}

// Get the current firmware version
void getFirmwareVersion(char *buffer, int bufferLength)
{
    formatFirmwareVersion(FIRMWARE_VERSION_MAJOR, FIRMWARE_VERSION_MINOR, buffer, bufferLength);
}

// Format the firmware version
void formatFirmwareVersion(uint8_t major, uint8_t minor, char *buffer, int bufferLength)
{
    char prefix = 'v';

    if (bufferLength >= 9)
        // 123456789
        // pxxx.yyy0
        snprintf(buffer, bufferLength, "%c%d.%d", prefix, major, minor);
    else
    {
        systemPrintf("ERROR: Buffer too small for version number!\r\n");
        if (bufferLength > 0)
            *buffer = 0;
    }
}

// Returns true if we successfully got the versionAvailable
// Modifies versionAvailable with OTA getVersion response
bool otaCheckVersion(char *versionAvailable, uint8_t versionAvailableLength)
{
    bool gotVersion = false;
#ifdef COMPILE_WIFI

    char versionString[21];
    getFirmwareVersion(versionString, sizeof(versionString));

    const char *url = OTA_FIRMWARE_JSON_URL;
    systemPrintf("Checking to see if an update is available from %s\r\n", url);

    ESP32OTAPull ota;

    int response = ota.CheckForOTAUpdate(url, versionString, ESP32OTAPull::DONT_DO_UPDATE);

    // We don't care if the library thinks the available firmware is newer, we just need a successful JSON parse
    if (response == ESP32OTAPull::UPDATE_AVAILABLE || response == ESP32OTAPull::NO_UPDATE_AVAILABLE)
    {
        gotVersion = true;

        // Call getVersion after original inquiry
        String otaVersion = ota.GetVersion();
        otaVersion.toCharArray(versionAvailable, versionAvailableLength);
    }
    else if (response == ESP32OTAPull::HTTP_FAILED)
    {
        systemPrintln("Firmware server not available");
    }
    else
    {
        systemPrintln("OTA failed");
    }

    if (gotVersion == true)
        log_d("Available OTA firmware version: %s\r\n", versionAvailable);

#endif // COMPILE_WIFI
    return (gotVersion);
}

// Force updates firmware using OTA pull
// Exits by either updating firmware and resetting, or failing due to old/bad firmware version
void otaUpdate()
{
#ifdef COMPILE_WIFI
    char versionString[9];
    formatFirmwareVersion(0, 0, versionString, sizeof(versionString));

    ESP32OTAPull ota;

    int response;
    const char *url = OTA_FIRMWARE_JSON_URL;
    response = ota.CheckForOTAUpdate(url, &versionString[1], ESP32OTAPull::DONT_DO_UPDATE);

    if (response == ESP32OTAPull::UPDATE_AVAILABLE)
    {
        systemPrintln("Installing new firmware");
        ota.SetCallback(otaPullCallback);
        ota.CheckForOTAUpdate(url, &versionString[1]); // Install new firmware, no reset

        ESP.restart();
    }
    else if (response == ESP32OTAPull::NO_UPDATE_AVAILABLE)
    {
        systemPrintln("OTA Update: Current firmware is up to date");
    }
    else if (response == ESP32OTAPull::HTTP_FAILED)
    {
        systemPrintln("OTA Update: Firmware server not available");
    }
    else
    {
        systemPrintln("OTA Update: OTA failed");
    }

#endif // COMPILE_WIFI
}

// Called while the OTA Pull update is happening
void otaPullCallback(int bytesWritten, int totalLength)
{
    otaDisplayPercentage(bytesWritten, totalLength, false);
}

void otaDisplayPercentage(int bytesWritten, int totalLength, bool alwaysDisplay)
{
    static int previousPercent = -1;
    int percent = 100 * bytesWritten / totalLength;
    if (alwaysDisplay || (percent != previousPercent))
    {
        // Indicate progress
        int barWidthInCharacters = 20; // Width of progress bar, ie [###### % complete
        long portionSize = totalLength / barWidthInCharacters;

        // Indicate progress
        systemPrint("\r\n[");
        int barWidth = bytesWritten / portionSize;
        for (int x = 0; x < barWidth; x++)
            systemPrint("=");
        systemPrintf(" %d%%", percent);
        if (bytesWritten == totalLength)
            systemPrintln("]");

        previousPercent = percent;
    }
}

// Returns true if reportedVersion is newer than currentVersion
// Version number comes in as v2.7-Jan 5 2023
// 2.7-Jan 5 2023 is newer than v2.7-Jan 1 2023
bool isReportedVersionNewer(char *reportedVersion, char *currentVersion)
{
    float currentVersionNumber = 0.0;
    int currentDay = 0;
    int currentMonth = 0;
    int currentYear = 0;

    float reportedVersionNumber = 0.0;
    int reportedDay = 0;
    int reportedMonth = 0;
    int reportedYear = 0;

    breakVersionIntoParts(currentVersion, &currentVersionNumber, &currentYear, &currentMonth, &currentDay);
    breakVersionIntoParts(reportedVersion, &reportedVersionNumber, &reportedYear, &reportedMonth, &reportedDay);

    log_d("currentVersion: %f %d %d %d", currentVersionNumber, currentYear, currentMonth, currentDay);
    log_d("reportedVersion: %f %d %d %d", reportedVersionNumber, reportedYear, reportedMonth, reportedDay);

    // Production firmware is named "2.6"

    if (reportedVersionNumber > currentVersionNumber)
        return (true);

    // Check which date is more recent
    // https://stackoverflow.com/questions/5283120/date-comparison-to-find-which-is-bigger-in-c
    int reportedVersionScore = reportedDay + reportedMonth * 100 + reportedYear * 2000;
    int currentVersionScore = currentDay + currentMonth * 100 + currentYear * 2000;

    if (reportedVersionScore > currentVersionScore)
    {
        log_d("Reported version is greater");
        return (true);
    }

    return (false);
}

// Version number comes in as v2.7-Jan 5 2023
// Given a char string, break into version number, year, month, day
// Returns false if parsing failed
bool breakVersionIntoParts(char *version, float *versionNumber, int *year, int *month, int *day)
{
    int placed = 0;

    placed = sscanf(version, "%f", versionNumber);
    if (placed != 1)
    {
        log_d("Failed to sscanf");
        return (false); // Something went wrong
    }

    return (true);
}

void wifiStop()
{
#ifdef COMPILE_WIFI
    if (WiFi.getMode() != WIFI_OFF)
        WiFi.mode(WIFI_OFF);
#endif

    log_d("WiFi Stopped");
}