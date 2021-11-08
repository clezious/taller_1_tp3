#include "../common_src/common_protocol.h"
#include "../common_src/common_socket.h"
// #include "./server_blocking_queue.h"
#include "server.h"
#include "accept_thread.h"
#include <iostream>
#include <utility>
#include <string>


Server::Server(const char * service):                            
                            is_running(true){
    socket.listen("localhost", service, LISTEN_POOL_SIZE);
}

void Server::main_loop(){
    AcceptThread accept_thread(this->socket,
                            this->queues,
                            this->protocol);
    std::string input = "";
    while (input != "q"){
        std::getline(std::cin,input);
    }    
    this->socket.force_stop();
    accept_thread.join();
}

int main(int argc, char const *argv[]){
    //Cantidad invalida de parámetros
    if (argc != 2){
        return 1;
    }
    try {
        Server server(argv[1]);
        server.main_loop();        
    } catch(...){
        return 2;
    }    
    return 0;
}

