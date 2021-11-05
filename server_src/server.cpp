#include "../common_src/common_protocol.h"
#include "../common_src/common_socket.h"
#include <iostream>

int main(int argc, char const *argv[]){
    Protocol protocol;       
    Socket socket;    
    socket.listen("localhost", "7778", 50);    
    Socket client = socket.accept();
    
    while(true){
        char command_id;
        std::string queue_name;
        std::string message;
        std::tie(command_id, queue_name, message) = protocol.recv_command(client);
        std::cout << command_id << ' ' << queue_name << ' ' << message << std::endl;
        if (command_id == 'o'){
            protocol.send_message(client,"Respuesta del Pop!");
        }
    }
    
    return 0;
}
