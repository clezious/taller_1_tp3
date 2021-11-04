#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <cstring>
#include <iostream>

#include "./common_socket.h"

Socket::Socket(){
    std::cout << "SOCKET CREADO" << std::endl;
    this->file_descriptor = socket(AF_INET, SOCK_STREAM, 0);
}

Socket::Socket(int file_descriptor){
    std::cout << "SOCKET CREADO CON FD" << std::endl;
    this->file_descriptor = file_descriptor;
}

Socket::Socket(Socket&& other){
    std::cout << "SOCKET CREADO POR MOVIMIENTO" << std::endl;
    this->file_descriptor = other.file_descriptor;
    other.file_descriptor = -1;
}

Socket& Socket::operator=(Socket&& other){
    std::cout << "SOCKET ASIGNADO POR MOVIMIENTO" << std::endl;
    if(this != &other){
        this->file_descriptor = other.file_descriptor;
        other.file_descriptor = -1;
    }
    return *this;
}

Socket::~Socket(){
    if(this->file_descriptor != -1){
        shutdown(this->file_descriptor,SHUT_RDWR);
        close(this->file_descriptor);
    }
    std::cout << "SOCKET DESTRUIDO" << std::endl;
}

void Socket::_getaddrinfo(struct addrinfo **address, 
                  const char *host, 
                  const char * service, 
                  bool server){
    struct addrinfo hints;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    if (server == true){
        hints.ai_flags = AI_PASSIVE;
    }
    getaddrinfo(host, service, &hints, address);
}

void Socket::connect(const char *host, const char *service){
    struct addrinfo *address, *ptr;
    bool success = false;
    _getaddrinfo(&address, host, service, false);
    for (ptr = address; 
         ptr != NULL && success == false; 
         ptr = ptr->ai_next) {
        //Se recorren las direcciones intentando 
        //conectar hasta que lo logre (o no). 
        if (::connect(this->file_descriptor,
                    ptr->ai_addr,
                    ptr->ai_addrlen) != -1) {    
            success = true;
        }
    }
    freeaddrinfo(address);
}

void Socket::listen(const char *host, const char *service, int max_conn_pool){
    struct addrinfo *address;
    _getaddrinfo(&address, host, service, true);    
    bind(this->file_descriptor, address->ai_addr, address->ai_addrlen);
    freeaddrinfo(address);
    ::listen(this->file_descriptor, max_conn_pool);
}

Socket Socket::accept(){
    int file_descriptor = ::accept(this->file_descriptor, 0, 0);
    return std::move(Socket(file_descriptor));
}


ssize_t Socket::send(const char *buffer, size_t length){    
    size_t total_sent_bytes = 0;    
    //Manejo de short-writes
    while (total_sent_bytes < length){
        ssize_t sent_bytes = ::send(this->file_descriptor,
                              &buffer[total_sent_bytes],
                              length - total_sent_bytes,
                              MSG_NOSIGNAL);
        if (sent_bytes != -1){
            total_sent_bytes += sent_bytes;
        }
    }    
    return total_sent_bytes;
}

ssize_t Socket::recv(char *buffer, size_t length){    
    size_t total_recv_bytes = 0;    
    //Manejo de short-recv
    while (total_recv_bytes < length){
        ssize_t recv_bytes = ::recv(this->file_descriptor,
                        &buffer[total_recv_bytes],
                        length - total_recv_bytes,
                        0);
        if (recv_bytes != -1){
            total_recv_bytes += recv_bytes;
        }
    }    
    return total_recv_bytes;
}