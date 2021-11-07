#include "../common_src/common_protocol.h"
#include "../common_src/common_socket.h"
#include "./blocking_queue.h"
#include <unordered_map>
#include <string>
#include <queue>

#define LISTEN_POOL_SIZE 50
class Server{
    private:
        Protocol protocol;
        Socket socket;              
        std::unordered_map<std::string, BlockingQueue> queues;        
    public:
        Server(const char * service);        
        void serve_client();
};
