#include <string.h>
#include <Arduino.h>
using namespace std;

class Response {
    public:
        /* Basic constructor */
        Response (int statusA, char* payloadA){
            status = statusA;
            strcpy(payload, payloadA);
        }  

        Response(){
            status = 777;
            strcpy(payload, "Unexpected error!");
        } 

        unsigned int status = 1; // 0 for success, other values for error codes
        char payload[120]; // the data to be transmitted, could be empty
};

/**
 * This class implements the logic server side
 * Should be instantiated in arduino and call runCommand(sensor_input);
 */
class Serv { 
    public:
        bool& counting;
        int& milisecondsPassed;
        double& current;

        /**
         * This is the constructor. It receives arduino control flags by reference
         */
        Serv(bool &countingA, int &milisecondsPassedA, double &currentA):counting(countingA),milisecondsPassed(milisecondsPassedA),current(currentA){}

        /**
         * This method receives a byte and retuns a method
         */
        Response* runCommand(unsigned int command){ 
            switch(command){
                case 0x1:
                    return getStatus();
                case 0x2:
                    return getCount();
                case 0x3:
                    return startCount();
                case 0x4:
                    return pauseCount();
                case 0x5:
                    return continueCount();
                case 0x6:
                    return stopCount();
                case 0xF:
                    return (new Response(0, "I\'m working, or at least responding"));
                default:
                    return (new Response(2, "Couldn't understand the command"));
            }
        }
    private: 
        /**
         * Returns sensor data
         * 0001
         */
        Response* getStatus(){
            char temp[10];
            dtostrf(this->current,2,2,temp);
            strcat(temp, "A");
            return (new Response(0, temp));
        }

        /**
         * Returns the current status of the count.
         * 0010
         */
        Response* getCount(){
            double count = this->milisecondsPassed / 1000;
            char temp[10];
            dtostrf(count,2,2,temp);
            strcat(temp, "s");
            return (new Response(0, temp));
        }


        /**
         * Starts a countdown from 300 seconds
         * 0011
         */
        Response* startCount(){
            counting = true;
            return (new Response(0, "COUNTDOWN STARTED"));
        }

        /**
         * Pauses counting
         * 0100
         */
        Response* pauseCount(){
            counting = false;
            return (new Response(0, "COUNTDOWN PAUSED"));
        }

        /**
         * Resumes counting
         * 0101
         */
        Response* continueCount(){
            counting = true;
            return (new Response(0, "COUNTDOWN RESTARTED"));
        }

        /**
         * Stops counting
         * 0110
         */
        Response* stopCount(){
            counting = false;
            milisecondsPassed = 0;
            return  (new Response(0, "COUNTDOWN STOPPED"));
        }
};