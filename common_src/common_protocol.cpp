#include <string>
#include <iostream>
#include <arpa/inet.h>

#include "common_protocol.h"
#include "common_socket.h"

void Protocol::request_define(Socket& socket, const std::string& queue_name){    
    char command = 'd';
    uint16_t length = htons(queue_name.length());
    socket.send(&command, sizeof(command));
    socket.send((char *) &length , sizeof(length));
    socket.send(queue_name.c_str(), queue_name.length());
}

