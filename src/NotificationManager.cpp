#include <Arduino.h>
#include "NotificationManager.hpp"

NotificationManager::NotificationManager(pin_t R, pin_t G, pin_t B, bool anode)
{
    // Setup LED pins
    this->led.R = R;
    this->led.G = G;
    this->led.B = B;

    // Set common anode/cathode
    this->led.anode = anode;

    // Handle pin modes
    pinMode(R, OUTPUT);
    pinMode(G, OUTPUT);
    pinMode(B, OUTPUT);

    // Start everything in 0
    analogWrite(this->led.R, this->led.anode
                                 ? ((~_STATUS_OFF & _STATUS_ON) & _RGB_RED) / _RGB_DIV_RED
                                 : (_STATUS_OFF & _RGB_RED) / _RGB_DIV_RED);

    analogWrite(this->led.G, this->led.anode
                                 ? ((~_STATUS_OFF & _STATUS_ON) & _RGB_GRN) / _RGB_DIV_GRN
                                 : (_STATUS_OFF & _RGB_GRN) / _RGB_DIV_GRN);

    analogWrite(this->led.B, this->led.anode
                                 ? ((~_STATUS_OFF & _STATUS_ON) & _RGB_BLE) / _RGB_DIV_BLE
                                 : (_STATUS_OFF & _RGB_BLE) / _RGB_DIV_BLE);

    // Start status at 0
    this->status = _STATUS_OFF;
}

bool NotificationManager::setColor(color_t color)
{
    if (color > 0xFFFFFF)
        return false;

    analogWrite(this->led.R, this->led.anode
                                 ? ((~color & _STATUS_ON) & _RGB_RED) / _RGB_DIV_RED
                                 : (color & _RGB_RED) / _RGB_DIV_RED);

    analogWrite(this->led.G, this->led.anode
                                 ? ((~color & _STATUS_ON) & _RGB_GRN) / _RGB_DIV_GRN
                                 : (color & _RGB_GRN) / _RGB_DIV_GRN);

    analogWrite(this->led.B, this->led.anode
                                 ? ((~color & _STATUS_ON) & _RGB_BLE) / _RGB_DIV_BLE
                                 : (color & _RGB_BLE) / _RGB_DIV_BLE);

    return true;
}

NotificationManager::color_t NotificationManager::setStatus(color_t status)
{
    color_t old_color = this->status;
    this->status = status;
    setColor(status);
    return old_color;
}

NotificationManager::color_t NotificationManager::getStatus() const
{
    return this->status;
}

NotificationManager::color_t NotificationManager::stopStatus()
{
    color_t old_color = this->status;
    this->status = _STATUS_OFF;
    setColor(_STATUS_OFF);
    return old_color;
}

void NotificationManager::sendNotification(color_t status,
                                           time_t timer,
                                           effect_t effect)
{
    // Set new color
    setColor(status);
    bool is_on = false;

    switch (effect)
    {
    case BLINK:
        for (int i = 0; i < timer / (_BLINK_SEC / BLINK); i++)
        {
            is_on = is_on
                        ? (setColor(_STATUS_OFF), false)
                        : (setColor(status), true);
            delay(_BLINK_SEC / BLINK);
        }

        break;

    case FAST_BLINK:
        for (int i = 0; i < timer / (_BLINK_SEC / FAST_BLINK); i++)
        {
            is_on = is_on
                        ? (setColor(_STATUS_OFF), false)
                        : (setColor(status), true);
            delay(_BLINK_SEC / FAST_BLINK);
        }
        break;

    default:
        // ON or any other effect
        delay(timer);
        break;
    }

    //Return last value
    setColor(this->status);

    /*
    time_t start = (time_t)millis(), elapsed = 0;

    // Start the color
    if (!setColor(status))
        return;

    while (elapsed < timer)
    {
        // Check elapsed time
        elapsed = (time_t)millis() - start;

        if (elapsed >= timer)
            break;

        ((elapsed % _BLINK_SEC) / (_BLINK_SEC % effect)) % 2 == 0
            ? setColor(status)
            : setColor(_STATUS_OFF);
    }

    // Return to the status
    setColor(this->status);
    */
}
