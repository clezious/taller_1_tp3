#ifndef __CLIENT_H__
#define __CLIENT_H__

#include <string>
#include <vector>
#include "../common_src/common_protocol.h"
#include "../common_src/common_socket.h"

class Client{
private:
    Protocol protocol;
    Socket socket;
    //Separa el string "command" en substrings que lo conforman
    // e inserta cada una en "vector".
    void split_command(std::vector<std::string>& vector, 
                        const std::string& command);
    // Ejecuta un comando a partir de los parametros recibidos en "vector".
    void exec_command(const std::vector<std::string>& vector);
    bool is_running;
public:
    Client(const char *host, const char *service);
    // Bucle principal del Cliente.
    // Lee comandos por entrada estandar y los ejecuta.
    void listen_commands();
};
#endif
