#ifndef __COMMON_PROTOCOL_H__
#define __COMMON_PROTOCOL_H__

#include <string>
#include "common_socket.h"
#include <unordered_map>
#include <tuple>

class Protocol{    
    private:
        //Traduce un comando a su char identificador        
        std::unordered_map<std::string,char> command_id_map = {
            {"define",'d'},
            {"push",'u'},
            {"pop",'o'},
        };

    public:
        // Para recibir un mensaje de un socket, siguiendo el
        // formato de 2 bytes con el largo del msg, y luego el msg.        
        std::string recv_message(Socket& socket);
        // Para enviar un mensaje a un socket, siguiendo el
        // formato de 2 bytes con el largo del msg, y luego el msg.        
        void send_message(Socket& socket,
                        const std::string& message);
        // Envía un comando al servidor
        void request(Socket& socket,
                    const std::string& command, 
                    const std::string& queue_name);
        // Envía un comando con mensaje al servidor
        void request(Socket& socket,
                    const std::string& command, 
                    const std::string& queue_name, 
                    const std::string& message); 
        // Recibe un comando del cliente.
        // Devuelve una tupla con el id del comando, 
        // el nombre de la cola, y el mensaje
        std::tuple<char,
                   std::string,
                   std::string> recv_command(Socket& socket);
};

#endif
