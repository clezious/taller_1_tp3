#include <string>
#include <iostream>
#include <arpa/inet.h>
#include <tuple>
#include <vector>

#include "common_protocol.h"
#include "common_socket.h"

std::string Protocol::recv_message(Socket& socket){
    //Primero se obtiene la longitud del mensaje
    uint16_t length;
    socket.recv((char *) &length, sizeof(length));
    length = ntohs(length);
    // y luego el mensaje
    std::vector<char> buffer(length);
    socket.recv(buffer.data(), length);
    return std::string(buffer.begin(),buffer.end());
}

void Protocol::send_message(Socket& socket,
                            const std::string& message){
    //Envio de longitud del mensaje
    uint16_t length = ntohs(message.length());
    socket.send((char *) &length, sizeof(length));
    //Envio del mensaje
    socket.send(message.c_str(), message.length());
}

void Protocol::request(Socket& socket,
                        const std::string& command, 
                        const std::string& queue_name){
    char command_id = this->command_id_map[command];
    uint16_t queue_name_length = htons(queue_name.length());    
    socket.send(&command_id, sizeof(command_id));
    socket.send((char *) &queue_name_length , sizeof(queue_name_length));
    socket.send(queue_name.c_str(), queue_name.length());
}

void Protocol::request(Socket& socket,
                        const std::string& command, 
                        const std::string& queue_name, 
                        const std::string& message){
    this->request(socket,command,queue_name);
    if (!message.empty()){
        this->send_message(socket, message);
    }
}

std::tuple<char,
            std::string,
            std::string> Protocol::recv_command(Socket& socket){
    // Recepción del comando
    char command_id;
    socket.recv(&command_id, sizeof(command_id));
    // Recepción del nombre de la queue
    std::string queue_name = this->recv_message(socket);
    // Si la op es push, se recibe un mensaje extra
    std::string message("");
    if (command_id == 'u'){
        message = this->recv_message(socket);
    }
    return std::tuple<char,
                        std::string,
                        std::string>(command_id,queue_name,message);
}


