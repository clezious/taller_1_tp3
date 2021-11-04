#include "../common_src/common_protocol.h"
#include "../common_src/common_socket.h"
#include <iostream>

int main(int argc, char const *argv[]){
    // Protocol protocol;       
    Socket socket;    
    socket.listen("localhost", "7778", 50);
    char * buffer = new char[50];
    Socket client = socket.accept();
    client.recv(buffer,sizeof(buffer));
    std::cout << buffer << std::endl;
    delete[] buffer;
    return 0;
}
