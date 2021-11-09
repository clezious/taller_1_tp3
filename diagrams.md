classDiagram
    direction LR
    Server *--  "1" AcceptThread
    AcceptThread *--  "n" WorkerThread      
    WorkerThread --> QueuesMonitor      
    QueuesMonitor *--  "n" BlockingQueue

    class Server{          
        -Protocol
        -Socket
        +run();
    }
    class AcceptThread{
        -workers
        +run()
        +join()
    }
    class WorkerThread{
        -Socket client
        -process_commands()
        +run()          
        +join()          
    }
    class QueuesMonitor{
        -queues        
        +get_or_add_queue()
    }
    class BlockingQueue{
        -queue
        +push()
        +pop()
    }
      
classDiagram
    direction LR
    Client <--> WorkerThread : Protocol
    Server --> WorkerThread

    class Server{          
        -Protocol
        -Socket
        +run();
    }
    class WorkerThread{
        -Socket client
        -process_commands()
        +run()          
        +join()          
    }
    class Client{          
        -Protocol
        -Socket
        -exec_command()
        +listen_commands();
    }

sequenceDiagram    
    loop Client::listen_commands()
        Client->>WorkerThread:Protocol.request(push unaCola unMensaje) 
        WorkerThread->>QueuesMonitor: get_or_add_queue(unaCola)
        QueuesMonitor-->>WorkerThread: BlockingQueue
        WorkerThread->>WorkerThread: BlockingQueue.push(unMensaje)
        Client->>WorkerThread:Protocol.request(pop unaCola) 
        WorkerThread->>QueuesMonitor: get_or_add_queue(unaCola)
        QueuesMonitor-->>WorkerThread: BlockingQueue        
        WorkerThread-->>Client: protocol.send_message(BlockingQueue.pop())        
    end    
