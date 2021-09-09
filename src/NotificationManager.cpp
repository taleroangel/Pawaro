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

    // Start status at 0
    this->status = _STATUS_OFF;
}

void NotificationManager::begin()
{
    // Handle pin modes
    pinMode(led.R, OUTPUT);
    pinMode(led.G, OUTPUT);
    pinMode(led.B, OUTPUT);

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
}

bool NotificationManager::setColor(color_t color)
{
#ifdef _NM_DISABLE
    color = _STATUS_OFF;
#endif

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
                                           EFFECT effect)
{
    // Set new color
    setColor(status);
    bool is_on = false;

    switch (effect)
    {
    case EFFECT::BLINK:
        for (time_t i = 0;
             i < timer / (_BLINK_SEC / (uint8_t)EFFECT::BLINK); i++)
        {
            is_on = is_on
                        ? (setColor(_STATUS_OFF), false)
                        : (setColor(status), true);
            delay(_BLINK_SEC / (uint8_t)EFFECT::BLINK);
        }

        break;

    case EFFECT::FAST_BLINK:
        for (time_t i = 0;
             i < timer / (_BLINK_SEC / (uint8_t)EFFECT::FAST_BLINK); i++)
        {
            is_on = is_on
                        ? (setColor(_STATUS_OFF), false)
                        : (setColor(status), true);
            delay(_BLINK_SEC / (uint8_t)EFFECT::FAST_BLINK);
        }
        break;

    default:
        // ON or any other effect
        delay(timer);
        break;
    }

    //Return last value
    setColor(this->status);
}

void NotificationManager::sendNotification(color_t status, EFFECT effect)
{
    NotificationManager::sendNotification(status, _DEFAULT_ND, effect);
}

void NotificationManager::interruptNotifier(color_t status, time_t time)
{
    // Set new color
    setColor(status);

    // Get value in seconds
    time /= _DEFAULT_ND;

    for (time_t i = 0; i < time; i++)
    {
        // Time up (1s)
        for (int j = 0; j < _BLINK_SEC; j++)
        {
            setColor(status);
            delayMicroseconds(_BLINK_SEC);
        }

        if (i == (time - 1))
            break; //No need to wait 1s in off state last cycle

        // Time down (1s)
        for (int k = 0; k < _BLINK_SEC; k++)
        {
            setColor(_STATUS_OFF);
            delayMicroseconds(_BLINK_SEC);
        }
    }

    //Return last value
    setColor(this->status);
}
