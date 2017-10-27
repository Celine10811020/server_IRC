# server_client_IRC
A simple IRC server and IRC client.
Protocol compliant RFC 1459, written in C.

# Compile
compiling:
    
    make
    
cleaning obj files:

    make clean
    
cleaning binary files:

    make fclean
    
    
cleaning all and compile:

    make re

# How to use it
Launch the server:

    ./server PORT

Launch the client:

    ./client
### At this time the client is unstable, I recommend to use Netcat or Telnet client (the both are supported)
