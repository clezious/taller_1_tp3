#ifndef __BLOCKING_QUEUE_H__
#define __BLOCKING_QUEUE_H__
#include <queue>
#include <mutex>
#include <string>
#include <condition_variable>

class BlockingQueue{
    private:
        std::mutex mutex;
        std::condition_variable condition_variable;
        std::queue<std::string> queue;
        bool open;
    public:
        BlockingQueue();
        void close();
        void push(const std::string& item);
        std::string pop();
};

#endif
