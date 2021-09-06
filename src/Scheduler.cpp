#include "Scheduler.hpp"

Scheduler::Scheduler()
{
    this->events = nullptr;
}

Scheduler::~Scheduler()
{
    stopListen();
    if (memory_allocated)
        delete this->events;
}

Scheduler::return_t Scheduler::begin()
{
    if (!clock.begin()) // Clock was not connected
        return RTC_NOT_FOUND;

    else if (!clock.isrunning()) // Clock is outdated
    {
        clock.adjust(DateTime(F(__DATE__), F(__TIME__)));
        return CLK_OUTDATED;
    }

    return SUCCESS;
}

boolean Scheduler::importHours(int elements, String hours[])
{
    // Get how many hours will be imported
    this->events = new DateTime[elements];
    n_events = elements;

    // Allocate each element
    for (int i = 0; i < elements; i++)
    {
        events[i] = DateTime(__DATE__, hours[i].c_str());
        if (!events[i].isValid())
            return false;
    }

    return true;
}

int Scheduler::listen()
{
    this->isListening = true;

    while (this->isListening)
    {
        // Hour should be the same
        // Minute should be the same
        // Second is ignored
        DateTime current = this->clock.now();

        for (int i = 0; i < n_events; i++)
        {
            // Hours are equal
            if (
                current.hour() == events[i].hour() &&
                current.minute() == events[i].minute())
            {
                // Call the event
                return n_events;

                // Delay for the rest of the Minute
                delay(_MINUTE);
            }
        }
    }

    return -1;
}

void Scheduler::stopListen()
{
    this->isListening = false;
}

String Scheduler::grabValue(String format)
{
    return String(this->clock.now().toString((char *)format.c_str()));
}

void Scheduler::updateClock()
{
    clock.adjust(DateTime(F(__DATE__), F(__TIME__)));
}
