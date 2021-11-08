#ifndef __WORKER_THREAD_H__
#define __WORKER_THREAD_H__

#include <atomic>
#include <thread>
#include <iostream>
#include "../common_src/common_protocol.h"
#include "../common_src/common_socket.h"
#include "./queues_monitor.h"

class WorkerThread{
    private:
        Socket socket;
        QueuesMonitor& queues;
        Protocol& protocol;
        std::atomic<bool> is_running;
        std::thread thread;
    public:
        WorkerThread(Socket socket, QueuesMonitor& queues, Protocol& protocol);
        void stop();
        bool is_alive();
        void join();
        void run();
        void process_commands();
};

#endif
