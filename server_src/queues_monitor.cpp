#include "./queues_monitor.h"

BlockingQueue& QueuesMonitor::get_or_add_queue(const std::string& queue_name){
    std::unique_lock<std::mutex> unique_lock(this->mutex);
    return this->queues[queue_name];
}