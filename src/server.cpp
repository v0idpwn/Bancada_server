#include <string.h>
#include <Arduino.h>
#ifndef RESPONSE
#define RESPONSE
#include<response.hpp>
#endif
#ifndef SERVER
#define SERVER
#include<server.hpp>
#endif


Serv::Serv(bool &countingA, unsigned long int &milisecondsPassedA, double &currentA) : counting(countingA), milisecondsPassed(milisecondsPassedA), current(currentA) {}

Response Serv::runCommand(unsigned int command)
{
    switch (command)
    {
    case 0x1:
        return this->getStatus();
    case 0x2:
        return this->getCount();
    case 0x3:
        return this->startCount();
    case 0x4:
        return this->pauseCount();
    case 0x5:
        return this->continueCount();
    case 0x6:
        return this->stopCount();
    case 0xF:
        return (Response(0, "I\'m working, or at least responding"));
    default:
        return (Response(2, "Couldn't understand the command"));
    }
}

Response Serv::getStatus()
{
    char temp[10];
    dtostrf(this->current, 2, 2, temp);
    strcat(temp, "A");
    return (Response(0, temp));
}

Response Serv::getCount()
{
    double count = this->milisecondsPassed / 1000;
    char temp[10];
    dtostrf(count, 2, 2, temp);
    strcat(temp, "s");
    return (Response(0, temp));
}

Response Serv::startCount()
{
    this->counting = true;
    return (Response(0, "COUNTDOWN STARTED"));
}

Response Serv::pauseCount()
{
    this->counting = false;
    return (Response(0, "COUNTDOWN PAUSED"));
}

Response Serv::continueCount()
{
    this->counting = true;
    return (Response(0, "COUNTDOWN RESTARTED"));
}

Response Serv::stopCount()
{
    this->counting = false;
    this->milisecondsPassed = 0;
    return (Response(0, "COUNTDOWN STOPPED"));
}
