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

// Declaring response texts:
struct messages {
    char working[64] = "FUNCIONANDO, OU AO MENOS RESPONDENDO";
    char didnt_understand[64] = "COMANDO NAO ENTENDIDO";
    char started[64] = "CONTAGEM INICIADA";
    char stopped[64] = "CONTAGEM FINALIZADA";
    char paused[64] = "CONTAGEM PAUSADA";
    char restarted[64] = "CONTAGEM REINICIADA";
 } msg;

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
        return (Response(0, msg.working));
    default:
        return (Response(2, msg.didnt_understand));
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
    return (Response(0, msg.started));
}

Response Serv::pauseCount()
{
    this->counting = false;
    return (Response(0, msg.paused));
}

Response Serv::continueCount()
{
    this->counting = true;
    return (Response(0, msg.restarted));
}

Response Serv::stopCount()
{
    this->counting = false;
    this->milisecondsPassed = 0;
    return (Response(0, msg.stopped));
}
