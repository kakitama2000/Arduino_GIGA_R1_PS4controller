#ifndef MBED_USBPS4_H
#define MBED_USBPS4_H

#include <Arduino.h>
#include <Arduino_USBHostMbed5.h>

enum ButtonEnum {
    UP = 0, RIGHT, DOWN, LEFT,
    SQUARE, CROSS, CIRCLE, TRIANGLE,
    L1, R1, L2, R2, L3, R3,
    SHARE, OPTIONS, TOUCHPAD, PS
};

enum HatEnum {
    LeftHatX = 0, LeftHatY, RightHatX, RightHatY
};

class PS4USB : public IUSBEnumerator {
public:
    PS4USB() {
        host = USBHost::getHostInst();
        dev = NULL;
        ep = NULL;
        hijacked = false;
        currentButtons = 0;
        oldButtons = 0;
        clickButtons = 0;
        memset(hatValues, 128, sizeof(hatValues));
        l2_analog = 0;
        r2_analog = 0;
    }

    void poll() {
        if (hijacked && dev != NULL && ep != NULL) {
            alignas(32) uint8_t reportBuf[64];
            memset(reportBuf, 0, sizeof(reportBuf));
            
            USB_TYPE res = host->interruptRead(dev, ep, reportBuf, 64, true);
            
            if (res == 0 && reportBuf[0] == 0x01) { 
                hatValues[LeftHatX]  = reportBuf[1];
                hatValues[LeftHatY]  = reportBuf[2];
                hatValues[RightHatX] = reportBuf[3];
                hatValues[RightHatY] = reportBuf[4];

                l2_analog = reportBuf[8];
                r2_analog = reportBuf[9];

                uint32_t newButtons = 0;

                uint8_t dpad = reportBuf[5] & 0x0F;
                if (dpad < 8) {
                    if (dpad == 0 || dpad == 1 || dpad == 7) newButtons |= (1UL << UP);
                    if (dpad == 1 || dpad == 2 || dpad == 3) newButtons |= (1UL << RIGHT);
                    if (dpad == 3 || dpad == 4 || dpad == 5) newButtons |= (1UL << DOWN);
                    if (dpad == 5 || dpad == 6 || dpad == 7) newButtons |= (1UL << LEFT);
                }

                if (reportBuf[5] & 0x10) newButtons |= (1UL << SQUARE);
                if (reportBuf[5] & 0x20) newButtons |= (1UL << CROSS);
                if (reportBuf[5] & 0x40) newButtons |= (1UL << CIRCLE);
                if (reportBuf[5] & 0x80) newButtons |= (1UL << TRIANGLE);

                if (reportBuf[6] & 0x01) newButtons |= (1UL << L1);
                if (reportBuf[6] & 0x02) newButtons |= (1UL << R1);
                if (reportBuf[6] & 0x04) newButtons |= (1UL << L2);
                if (reportBuf[6] & 0x08) newButtons |= (1UL << R2);
                if (reportBuf[6] & 0x10) newButtons |= (1UL << SHARE);
                if (reportBuf[6] & 0x20) newButtons |= (1UL << OPTIONS);
                if (reportBuf[6] & 0x40) newButtons |= (1UL << L3);
                if (reportBuf[6] & 0x80) newButtons |= (1UL << R3);

                if (reportBuf[7] & 0x01) newButtons |= (1UL << PS);
                if (reportBuf[7] & 0x02) newButtons |= (1UL << TOUCHPAD);

                clickButtons |= (newButtons & ~oldButtons);
                currentButtons = newButtons;
                oldButtons = newButtons;
            }
            return;
        }

        for (uint8_t i = 0; i < MAX_DEVICE_CONNECTED; i++) {
            USBDeviceConnected* d = host->getDevice(i);
            if (d != NULL && !hijacked) {
                dev = d;
                hijacked = true;
                
                host->enumerate(d, this);
                host->controlWrite(d, 0x00, 0x09, 1, 0, NULL, 0);
                delay(200);

                ep = host->newEndpoint(INTERRUPT_ENDPOINT, IN, 64, 0x84);
                if (ep != NULL) {
                    host->addEndpoint(dev, 3, ep);
                }
            }
        }
    }

    bool connected() { return hijacked && ep != NULL; }

    bool getButtonPress(ButtonEnum b) {
        return (currentButtons & (1UL << b)) != 0;
    }

    bool getButtonClick(ButtonEnum b) {
        uint32_t mask = (1UL << b);
        if (clickButtons & mask) {
            clickButtons &= ~mask;
            return true;
        }
        return false;
    }

    uint8_t getAnalogHat(HatEnum a) {
        return hatValues[a];
    }

    uint8_t getAnalogButton(ButtonEnum b) {
        if (b == L2) return l2_analog;
        if (b == R2) return r2_analog;
        return getButtonPress(b) ? 255 : 0;
    }

    virtual void setVidPid(uint16_t vid, uint16_t pid) {}
    virtual bool parseInterface(uint8_t intf_nb, uint8_t intf_class, uint8_t intf_subclass, uint8_t intf_protocol) { return true; }
    virtual bool useEndpoint(uint8_t intf_nb, ENDPOINT_TYPE type, ENDPOINT_DIRECTION dir) { return false; }

private:
    USBHost *host;
    USBDeviceConnected *dev;
    USBEndpoint *ep;
    bool hijacked;

    uint32_t currentButtons;
    uint32_t oldButtons;
    uint32_t clickButtons;
    uint8_t hatValues[4];
    uint8_t l2_analog;
    uint8_t r2_analog;
};

#endif