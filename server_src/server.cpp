#include "../common_src/common_protocol.h"
#include "../common_src/common_socket.h"
// #include "./server_blocking_queue.h"
#include "server.h"
#include <iostream>
#include <utility>

Server::Server(const char * service){
    socket.listen("localhost", service, LISTEN_POOL_SIZE);
}

void Server::serve_client(){
    Socket client = this->socket.accept();
    bool is_running = true;

    while(is_running){
        char command_id;
        std::string queue_name;
        std::string message;
        try{
            std::tie(command_id, queue_name, message) = protocol.recv_command(client);
            std::cout << command_id << ' ' << queue_name << ' ' << message << std::endl;
            if (command_id == 'd'){                
                this->queues.get_or_add_queue(queue_name);
            }
            if (command_id == 'u'){                
                this->queues.get_or_add_queue(queue_name).push(message);
            }
            if (command_id == 'o'){
                protocol.send_message(client,this->queues.get_or_add_queue(queue_name).pop());                
            }
        } catch(...){
            is_running = false;
        }
    }
}


int main(int argc, char const *argv[]){
    //Cantidad invalida de parámetros
    if (argc != 2){
        return 1;
    }
    Server server(argv[1]);
    server.serve_client();    
    
    return 0;
}

