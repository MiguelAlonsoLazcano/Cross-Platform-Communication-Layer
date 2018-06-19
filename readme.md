## Object Oriented TCP / IP Socket Model design in C++

#### Socket Abstraction Layer

* ServerSocket : Modeled to Server end
* Connection   : Modeled to Client end

#### Classes

Socket: Socket base class

	-> ServerSocket: Server socket, TCP by default

	-> Connection: Establish a socket connection with the given address & port

        	-> ConnectionTCP: TCP Connection for communicate with a TCP Server

          	-> ConnectionUDP: UDP Connection for Communicate with a UDP Server

SocketException: Signal a problem with the execution of a socket call

ApplicationProtocol:  App level message model used for ::send & ::recv function calls.

clientConnection: Client end user space application

mainServer: Server end user user space application

#### Host build

```c++
A9-POC $ mkdir build
A9-POC $ cd build
A9-POC $ cmake -DTOOLCHAIN=HOST ..
A9-POC $ make
A9-POC $ ./mainServer <PORT>
```

#### Target build
```c++
A9-POC $ mkdir build
A9-POC $ cd build
A9-POC $ cmake -DTOOLCHAIN=ARM ..
A9-POC $ make
A9-POC $ ./mainServer <PORT>
```
```






