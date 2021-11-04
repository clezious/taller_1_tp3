#include "../common_src/common_protocol.h"
#include "../common_src/common_socket.h"
#include <iostream>

int main(int argc, char const *argv[]){
    Protocol protocol;       
    Socket socket;    
    socket.connect("localhost", "7777");
    protocol.request_define(socket, "UnaCola");
    return 0;
}
