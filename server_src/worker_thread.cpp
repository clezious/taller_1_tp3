#include "worker_thread.h"
#include <string>

WorkerThread::WorkerThread(Socket socket, 
                        QueuesMonitor& queues, 
                        Protocol& protocol):
                            socket(std::move(socket)),
                            queues(queues),
                            protocol(protocol),
                            is_running(true),
                            thread(&WorkerThread::run,this){}

void WorkerThread::process_commands(){
    char command_id;
    std::string queue_name;
    std::string message;    
    std::tie(command_id, 
            queue_name, 
            message) = this->protocol.recv_command(this->socket);
    if (command_id == 'd'){                
        this->queues.get_or_add_queue(queue_name);
    } else if (command_id == 'u'){
        this->queues.get_or_add_queue(queue_name).push(message);
    } else if (command_id == 'o'){
        this->protocol.send_message(this->socket,
                            this->queues.get_or_add_queue(queue_name).pop());
    }
}
void WorkerThread::run(){
    while (this->is_running){
        try{
            this->process_commands();
        } catch(...){
            this->is_running = false;            
        }
    }  
}
void WorkerThread::join(){
    this->thread.join();
}
bool WorkerThread::is_alive(){
    return this->is_running;
}
void WorkerThread::stop(){
    // this->is_running = false;
    this->socket.force_stop();
}
