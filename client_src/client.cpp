#include "../common_src/common_protocol.h"
#include "../common_src/common_socket.h"
#include <iostream>

int main(int argc, char const *argv[]){
    Protocol protocol;       
    Socket socket;    
    socket.connect("localhost", "7777");
    protocol.request(socket, "push", "UnaCola", "pepito1234");
    protocol.request(socket, "define", "UnaCola");
    protocol.request(socket, "pop", "UnaCola");
    std::string response(protocol.recv_message(socket));
    std::cout << response << std::endl;
    return 0;
}
