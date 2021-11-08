#include "accept_thread.h"
#include <vector>
#include <utility>

AcceptThread::AcceptThread(Socket& socket, 
                        QueuesMonitor& queues, 
                        Protocol& protocol):
                        socket(socket),
                        queues(queues),
                        protocol(protocol),
                        is_running(true),                        
                        thread(&AcceptThread::run,this){}

void AcceptThread::remove_dead_workers(){
    std::vector<size_t> dead_workers;
    for (size_t i = 0; i < workers.size(); i++){
        if (!this->workers[i]->is_alive()){
            dead_workers.push_back(i);                
        }
    }
    for (size_t i = 0; i < dead_workers.size(); i++){
        this->workers[i]->join();
        delete this->workers[i];
        this->workers.erase(this->workers.begin() + i);
    }        
}

void AcceptThread::remove_workers(){
    for (size_t i = 0; i < workers.size(); i++){
        this->workers[i]->stop();
        this->workers[i]->join();
        delete this->workers[i];
    }
}

void AcceptThread::run(){          
    while (this->is_running){
        try{
            Socket client = this->socket.accept();                    
            this->workers.push_back(new WorkerThread(std::move(client),
                                                this->queues,
                                                this->protocol));
        }
        catch(...){
            this->is_running = false;
        }        
        this->remove_dead_workers();
    }
    this->remove_workers();
}

void AcceptThread::join(){
    this->thread.join();
}
