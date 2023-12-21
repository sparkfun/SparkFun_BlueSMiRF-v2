#ifdef COMPILE_BT

// We use a local copy of the BluetoothSerial library so that we can make the following changes:
//* Adjust the TX and RX buffers
//* Adjust the Bluetooth connection timeout
#include "src/BluetoothSerial/BluetoothSerial.h"

#include <BleSerial.h> //Click here to get the library: http://librarymanager/All#ESP32_BleSerial v1.0.4 by Avinab Malla

class BTSerialInterface
{
  public:
    BTSerialInterface(){};
    ~BTSerialInterface(){};

    virtual bool begin(String deviceName, bool isMaster, uint16_t rxQueueSize, uint16_t txQueueSize) = 0;

    virtual bool connect(uint8_t remoteAddress[], int channel = 0,
                         esp_spp_sec_t sec_mask = (ESP_SPP_SEC_ENCRYPT | ESP_SPP_SEC_AUTHENTICATE),
                         esp_spp_role_t role = ESP_SPP_ROLE_MASTER, uint16_t connectTimeout = 10000) = 0;

    virtual bool connected(int timeout = 0) = 0;

    virtual void disconnect() = 0;
    virtual void end() = 0;

    virtual bool discoverAsync(BTAdvertisedDeviceCb cb, int timeout = 0x30 * 1280) = 0; // 61,440ms
    virtual void discoverAsyncStop() = 0;

    virtual esp_err_t register_callback(esp_spp_cb_t callback) = 0;
    virtual void setTimeout(unsigned long timeout) = 0;

    virtual int available() = 0;
    virtual size_t readBytes(uint8_t *buffer, size_t bufferSize) = 0;
    virtual int read() = 0;

    virtual size_t write(const uint8_t *buffer, size_t size) = 0;
    virtual size_t write(uint8_t value) = 0;
    virtual void flush() = 0;
};

class BTClassicSerial : public virtual BTSerialInterface, public BluetoothSerial
{
    // Everything is already implemented in BluetoothSerial since the code was
    // originally written using that class
  public:
    bool begin(String deviceName, bool isMaster, uint16_t rxQueueSize, uint16_t txQueueSize)
    {
        return BluetoothSerial::begin(deviceName, isMaster, rxQueueSize, txQueueSize);
    }

    bool connect(uint8_t remoteAddress[], int channel, esp_spp_sec_t sec_mask, esp_spp_role_t role,
                 uint16_t connectTimeout)
    {
        return BluetoothSerial::connect(remoteAddress, channel, sec_mask, role, connectTimeout);
    }

    bool connected(int timeout)
    {
        return BluetoothSerial::connected(timeout);
    }

    void disconnect()
    {
        BluetoothSerial::disconnect();
    }

    void end()
    {
        BluetoothSerial::end();
    }

    bool discoverAsync(BTAdvertisedDeviceCb cb, int timeout)
    {
        return BluetoothSerial::discoverAsync(cb, timeout);
    }
    void discoverAsyncStop()
    {
        BluetoothSerial::discoverAsyncStop();
    }

    esp_err_t register_callback(esp_spp_cb_t callback)
    {
        return BluetoothSerial::register_callback(callback);
    }

    void setTimeout(unsigned long timeout)
    {
        BluetoothSerial::setTimeout(timeout);
    }

    int available()
    {
        return BluetoothSerial::available();
    }

    size_t readBytes(uint8_t *buffer, size_t bufferSize)
    {
        return BluetoothSerial::readBytes(buffer, bufferSize);
    }

    int read()
    {
        return BluetoothSerial::read();
    }

    size_t write(const uint8_t *buffer, size_t size)
    {
        return BluetoothSerial::write(buffer, size);
    }

    size_t write(uint8_t value)
    {
        return BluetoothSerial::write(value);
    }

    void flush()
    {
        BluetoothSerial::flush();
    }
};

class BTLESerial : public virtual BTSerialInterface, public BleSerial
{
  public:
    // Missing from BleSerial
    bool begin(String deviceName, bool isMaster, uint16_t rxQueueSize, uint16_t txQueueSize)
    {
        BleSerial::begin(deviceName.c_str());
        return true;
    }

    // Not implemented yet
    bool connect(uint8_t remoteAddress[], int channel, esp_spp_sec_t sec_mask, esp_spp_role_t role,
                 uint16_t connectTimeout)
    {
        return (true);
    }

    bool connected(int timeout)
    {
        return (false); //Not implemented in BLE
    }

    void disconnect()
    {
        Server->disconnect(Server->getConnId());
    }

    void end()
    {
        BleSerial::end();
    }

    bool discoverAsync(BTAdvertisedDeviceCb cb, int timeout)
    {
        return (false); // Not implemented in BLE
    }
    void discoverAsyncStop()
    {
        return; // Not implemented in BLE
    }

    esp_err_t register_callback(esp_spp_cb_t callback)
    {
        connectionCallback = callback;
        return ESP_OK;
    }

    void setTimeout(unsigned long timeout)
    {
        BleSerial::setTimeout(timeout);
    }

    int available()
    {
        return BleSerial::available();
    }

    size_t readBytes(uint8_t *buffer, size_t bufferSize)
    {
        return BleSerial::readBytes(buffer, bufferSize);
    }

    int read()
    {
        return BleSerial::read();
    }

    size_t write(const uint8_t *buffer, size_t size)
    {
        return BleSerial::write(buffer, size);
    }

    size_t write(uint8_t value)
    {
        return BleSerial::write(value);
    }

    void flush()
    {
        BleSerial::flush();
    }

    // override BLEServerCallbacks
    void onConnect(BLEServer *pServer)
    {
        connectionCallback(ESP_SPP_SRV_OPEN_EVT, nullptr);
    }

    void onDisconnect(BLEServer *pServer)
    {
        connectionCallback(ESP_SPP_CLOSE_EVT, nullptr);
        Server->startAdvertising();
    }

  private:
    esp_spp_cb_t connectionCallback;
};

#endif // COMPILE_BT
