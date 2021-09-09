#include "Feeder.hpp"
#include <Servo.h>

Feeder::Feeder(pin_t servo_pin, degree_t aperture)
    : servo_pin(servo_pin), aperture(aperture)
{
    if (aperture > MAX_ANGLE)
        this->aperture = MAX_ANGLE;
}

Feeder::~Feeder()
{
    close();
    servoClass.detach();
    this->status = DISABLED;
}

void Feeder::begin()
{
    servoClass.attach(servo_pin);
    this->status = CLOSED;
    close();
}

Feeder::STATUS Feeder::getStatus() const
{
    return this->status;
}

void Feeder::open()
{
    servoClass.write(this->aperture);
    this->status = OPENED;
}

void Feeder::close()
{
    servoClass.write(MIN_ANGLE);
    this->status = CLOSED;
}

void Feeder::timer(time_t timeout)
{
    status = TIMED;

    open();
    delay(timeout);
    close();
}
