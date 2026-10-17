//
// Created by azrotho on 09/10/2026.
//

#include <iostream>
#include <thread>
#include <src/common/Constants.h>

int receive(){
    return 0;
}

int send(){
    return 0;
}


int gameLoop(){
    return 0;
}

int network(){
    //First: open port to let clients connect
    //Second: initialize networking object (TODO: implement a networking object)
    //Third: create a thread for each client
    //  //Four: wait for clients to do something
    //  //Five: upon receiving an input, deserialize it and send it to the network thread
    //Six: send input to gameLoop
    //Seven: get gameState/answer from gameLoop 
    //  //Eight: send gameState to each client, then go to step Four
    //End of the game : disconnect from client, close port, close server
    return 0;
}

int main() {
    std::thread mainThread (gameLoop);
    std::thread receptionThread (network);
    std::cout << "Hello, World Server!" << std::endl;
    return 0;
}