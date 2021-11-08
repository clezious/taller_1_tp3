#ifndef __WORKER_THREAD_H__
#define __WORKER_THREAD_H__

#include <atomic>
#include <thread>
#include <iostream>
#include "../common_src/common_protocol.h"
#include "../common_src/common_socket.h"
#include "./queues_monitor.h"

// Hilo Worker. Se encarga de atender y procesar los requests de un cliente.
class WorkerThread{
    private:
        // Socket del cliente
        Socket socket;
        QueuesMonitor& queues;
        Protocol& protocol;
        std::atomic<bool> is_running;
        //Hilo principal
        std::thread thread;
        // Maneja la lógica de la recepción y el proceso de los
        // comandos recibidos por el cliente.
        void process_commands();
    public:
        WorkerThread(Socket socket, QueuesMonitor& queues, Protocol& protocol);
        // Fuerza el cierre del socket cliente, 
        // provocando la terminación de la función principal "run()"
        void stop();
        // Devuelve true si la función principal "run()" sigue activa.
        bool is_alive();
        // join del hilo "thread"
        void join();
        // Función principal. Maneja las interacciones con el cliente asociado
        void run();        
};

#endif
