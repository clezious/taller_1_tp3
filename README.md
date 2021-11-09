# TP3
## Taller de Programación FIUBA 2021 2C
## Manuel Reberendo 100930
<br>
<br>

# Introducción
El TP consiste en diseñar un *Message Oriented Middleware* (MOM) constituido por un Servidor que posee un repositorio de colas de mensajes (Cada una identificada por un nombre) y que puede atender a multiples clientes, que podrán crear colas, agregar mensajes a ellas, y consumirlos.

# Clases
Para la resolución del trabajo se utilizan diversas clases, cuyas principales caracteristicas e interacciones veremos con detalle a continuación:
## Clases compartidas
Hay dos clases que son utilizadas tanto por el cliente como por el servidor. Estas son las clases `Socket` y `Protocolo`:
### Socket
Se trata de un *wrapper* de un socket de c, pero en c++ y RAII.  
Se distingue principalmetne por lanzar un error cuando hay una falla en la comunicación provocada por el cierre de alguno de los dos sockets involucrados.
### Protocolo
Esta clase es utilizada por el cliente y servidor para enviarse mensajes entre si abstrayendo el protocolo "a nivel bytes" utilizado, que es el que por consigna debemos implementar.  
Todos sus métodos reciben una referencia a un `Socket`, que será de origen o destino dependiendo el caso.

## Clases del Cliente
### Client

El cliente solo hace uso de la clase `Client`, que implementa la lógica y el bucle principal del cliente, y su alcance es relativamente simple:

- Recibir comandos por entrada estandar
- "Ejecutar" esos comandos enviandolos al servidor
- Mostrar en pantalla el mensaje de respuestad el comando "pop"
- Salir ordenadamente si hubo algún error

Entre sus funciones más relevantes se encuentran:

```cpp
void Client::listen_commands(){
    std::string command;    
    while (this->is_running && std::getline(std::cin,command)){
        // Split del comando en un vector
        std::vector<std::string> command_vector;
        this->split_command(command_vector,command);
        //Se ejecuta el comando
        this->exec_command(command_vector);
    }
}
```
Que es la encargada de sostener el bucle principal, en el que se recibe por entrada estandar un comando, se parsea y se ejecuta.  

```cpp
void Client::exec_command(const std::vector<std::string>& vector){
    const std::string& command = vector[0];
    if (command == "exit"){
        this->is_running = false;        
    } else if (command == "push" && vector.size() > 2){
        this->protocol.request(this->socket,command,vector[1],vector[2]);
    } else if ((command == "pop" || command == "define") && vector.size() > 1){
        this->protocol.request(this->socket,command,vector[1]);
        if (command == "pop"){
            std::cout << this->protocol.recv_message(this->socket) << std::endl;
        }
    } else { throw "Invalid Command";}
}
```
Que es utilizada por `listen_commands()` y se encarga de enviar el comando ya parseado hacia el servidor.  
Tal como se había comentado, se ve cómo el cliente utiliza una instancia de `Protocol` para comunicarse con el socket del servidor, simplemente indicando el comando y el mensaje a enviar, abstrayendo así la lógica del protocolo subyacente.  
A continuación, un diagrama (simplificado) de esta clase y su interacción con el servidor (cuyas clases veremos más adelante):  

![Diagrama Client](./img/diagrama_clases_client.png)
## Clases del Servidor
El caso del servidor es un poco más complejo, sus clases constituyentes son:
### Server
La clase principal, punto de entrada y encargada de correr el bucle `main_loop()` en la función `main` del programa.  
Su principal función es la de lanzar el hilo aceptador y "escuchar" por entrada estandar, ya que si se recibe la letra q, debe finalizar su ejecución.  
Aquí su función más relevante `main_loop()`:
```cpp
void Server::main_loop(){
    AcceptThread accept_thread(this->socket,
                            this->queues,
                            this->protocol);
    std::string input = "";
    while (input != "q"){
        std::getline(std::cin,input);
    }    
    this->socket.force_stop();
    accept_thread.join();
}
```
Notese que para finalizar la ejecución se fuerza el cierre del socket aceptador, y de esta manera dejan de aceptarse conexiones de nuevos clientes




