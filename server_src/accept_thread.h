#ifndef __ACCEPT_THREAD_H__
#define __ACCEPT_THREAD_H__

#include <atomic>
#include <thread>
#include <iostream>
#include <vector>
#include "../common_src/common_protocol.h"
#include "../common_src/common_socket.h"
#include "./queues_monitor.h"
#include "./worker_thread.h"

class AcceptThread{
    private:
        Socket& socket;
        QueuesMonitor& queues;
        Protocol& protocol;
        std::atomic<bool> is_running;
        std::vector<WorkerThread*> workers;
        std::thread thread;   
    public:
        AcceptThread(Socket& socket, QueuesMonitor& queues, Protocol& protocol);
        void stop();
        bool is_alive();
        void join();
        void run();
};

#endif
