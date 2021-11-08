#include "../common_src/common_protocol.h"
#include "../common_src/common_socket.h"
#include "./client.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

Client::Client(const char *host, const char *service): is_running(true){
    socket.connect(host,service);
}

void Client::split_command(std::vector<std::string>& vector, 
                            const std::string& command){
    std::stringstream stream(command);
    std::string token;    
    for (int i = 0; i < 3; i++){
        char delimiter = i == 2 ? '\n' : ' ';
        if (! std::getline(stream, token, delimiter)){
            break;
        }
        vector.push_back(token);
    }
}

void Client::exec_command(const std::vector<std::string>& vector){
    const std::string& command = vector[0];
    if (command == "exit"){
        this->is_running = false;        
    } else if (command == "push" && vector.size() > 2){
        this->protocol.request(this->socket,command,vector[1],vector[2]);
    } else if ((command == "pop" || command == "define") && vector.size() > 1){
        this->protocol.request(this->socket,command,vector[1]);
        if (command == "pop"){
            std::cout << this->protocol.recv_message(this->socket) << std::endl;
        }
    } else { throw "Invalid Command";}
}

void Client::listen_commands(){
    std::string command;    
    while (this->is_running && std::getline(std::cin,command)){
        // Split del comando en un vector
        std::vector<std::string> command_vector;
        this->split_command(command_vector,command);
        //Se ejecuta el comando
        this->exec_command(command_vector);
    }
}

int main(int argc, char const *argv[]){
    //Cantidad invalida de parámetros
    if (argc != 3){
        return 1;
    }    
    try{
        Client client(argv[1],argv[2]);
        client.listen_commands();
    }
    catch(...){        
        return 2;
    }    
    return 0;
}
