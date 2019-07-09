class Response {
    public:
        Response (int statusA, char* payloadA);  
        Response();
        //Response& operator=(Response);
        unsigned int status = 1;
        char payload[120];
};

