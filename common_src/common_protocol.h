#ifndef __COMMON_PROTOCOL_H__
#define __COMMON_PROTOCOL_H__

#include <string>
#include "common_socket.h"

class Protocol{    
    public:
        void request_define(Socket& socket, const std::string& queue_name);
        // void request_push(const std::string& queue_name, const std::string& message);
        // void request_pop(const std::string& queue_name);
};

#endif