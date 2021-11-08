#include "accept_thread.h"
#include <vector>

AcceptThread::AcceptThread(Socket& socket, 
                        QueuesMonitor& queues, 
                        Protocol& protocol):
                        socket(socket),
                        queues(queues),
                        protocol(protocol),
                        is_running(true),                        
                        thread(&AcceptThread::run,this){}

void AcceptThread::run(){          
    while (this->is_running){
        try{
            Socket client = this->socket.accept();                    
            workers.push_back(new WorkerThread(std::move(client),
                                                this->queues,
                                                this->protocol));
        }
        catch(...){
            this->is_running = false;
        }        
        std::vector<size_t> dead_workers;
        for (size_t i = 0; i < workers.size(); i++){
            if (!workers[i]->is_alive()){
                dead_workers.push_back(i);                
            }
        }
        for (size_t i = 0; i < dead_workers.size(); i++){
            workers[i]->join();
            delete workers[i];
            workers.erase(workers.begin() + i);
        }        
    }    
    for (size_t i = 0; i < workers.size(); i++){
        workers[i]->stop();
        workers[i]->join();
        delete workers[i];               
    }    
}

void AcceptThread::join(){
    this->thread.join();
}
void AcceptThread::stop(){
    this->is_running = false;
}
bool AcceptThread::is_alive(){
    return this->is_running;
}
