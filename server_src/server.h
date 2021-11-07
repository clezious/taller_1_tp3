#ifndef __SERVER_H__
#define __SERVER_H__
#include "../common_src/common_protocol.h"
#include "../common_src/common_socket.h"
#include "./blocking_queue.h"
#include "./queues_monitor.h"
#include <unordered_map>
#include <string>
#include <queue>

#define LISTEN_POOL_SIZE 50
class Server{
    private:
        Protocol protocol;
        Socket socket;                         
        QueuesMonitor queues;   
    public:
        Server(const char * service);        
        void serve_client();
};

#endif
