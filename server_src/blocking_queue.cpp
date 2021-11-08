#include <mutex>
#include <string>
#include "./blocking_queue.h"

BlockingQueue::BlockingQueue(): 
                            queue(),
                            open(true){}
void BlockingQueue::close(){
    std::unique_lock<std::mutex> unique_lock(this->mutex);    
    this->open = false;
    this->condition_variable.notify_all();
} 
void BlockingQueue::push(const std::string &item){
    std::unique_lock<std::mutex> unique_lock(this->mutex);    
    this->queue.push(item);
    this->condition_variable.notify_all();    
} 
std::string BlockingQueue::pop(){
    std::unique_lock<std::mutex> unique_lock(this->mutex);
    while (this->queue.empty()){        
        if (!this->open){
            throw "BlockingQueue Closed";
        }
        this->condition_variable.wait(unique_lock);
    }
    std::string item = this->queue.front();
    this->queue.pop();
        
    return item;
} 
