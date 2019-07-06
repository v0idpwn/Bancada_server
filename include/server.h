class Response {
    public:
        Response (int statusA, char* payloadA);  
        Response();
        unsigned int status;
        char payload[120];
};

class Serv { 
    public:
        bool& counting;
        unsigned long int& milisecondsPassed;
        double& current;
        Serv(bool &countingA, unsigned long int &milisecondsPassedA, double &currentA);
        Response* runCommand(unsigned int command);
    private: 
        Response* getStatus();
        Response* getCount();
        Response* startCount();
        Response* pauseCount();
        Response* continueCount();
        Response* stopCount();
};