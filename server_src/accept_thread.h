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

// Hilo "aceptador". Se encarga de aceptar nuevos clientes 
// y asignarles un hilo Worker, además de manejar los Workers existentes.

class AcceptThread{
    private:
        // Socket del que se aceptarán clientes
        Socket& socket;
        QueuesMonitor& queues;
        Protocol& protocol;
        std::atomic<bool> is_running;
        std::vector<WorkerThread*> workers;
        std::thread thread;   
        // Destruye y elimina del vector "workers" aquellos 
        // workers que ya no estén vivos
        void remove_dead_workers();
        // Destruye todos los workers del vector "workers" 
        // forzandolos a que terminen su ejecución
        void remove_workers();
    public:
        AcceptThread(Socket& socket, QueuesMonitor& queues, Protocol& protocol);
        // Join al hilo "thread"
        void join();
        // Función principal que es ejecutada por el hilo "thread"
        void run();
};

#endif
