#ifndef __QUEUES_MONITOR_H__
#define __QUEUES_MONITOR_H__

#include <unordered_map>
#include <string>
#include "./blocking_queue.h"
class QueuesMonitor{
    private:
        std::mutex mutex;
        std::condition_variable condition_variable;
        // El mapa donde se guardarán las colas por nombre.
        std::unordered_map<std::string, BlockingQueue> queues;    
    public:
        // Se devuelve una referencia a la cola con el "queue_name"
        // indicado si ya existe, y si no, primero se crea.
        BlockingQueue& get_or_add_queue(const std::string& queue_name);
};

#endif
