#ifndef __SERVER_H__
#define __SERVER_H__
#include "../common_src/common_protocol.h"
#include "../common_src/common_socket.h"
#include "./blocking_queue.h"
#include "./queues_monitor.h"
#include <string>
#include <vector>
#include <thread>
#include <atomic>


#define LISTEN_POOL_SIZE 50
class Server{
    private:
        Protocol protocol;
        Socket socket;                         
        QueuesMonitor queues;        
        std::atomic<bool> is_running;        
    public:
        explicit Server(const char * service);
        void main_loop();
};

#endif
