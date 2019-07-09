#include<string.h>
#ifndef RESPONSE
#define RESPONSE
#include<response.hpp>
#endif


/** Constructor */
Response::Response (int statusA, char* payloadA){
    status = statusA;
    strcpy(payload, payloadA);
}  

/** Default constructor */
Response::Response (){
    status = 777;
    strcpy(payload, "Unexpected error!");
} 

//Response& Response::operator=(Response) = default;
