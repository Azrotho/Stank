//
// Created by azrotho on 09/10/2026.
//

#include <iostream>
#include <thread>
#include <Constants.h>

int receive(){
    return 0;
}

int send(){
    return 0;
}


int gameLoop(){
    //First: Initialize the game
    //Second: start a 30 TPS loop
    //Third: wait for inputs from network threads
    //Fourth: modify gameState according to the inputs
    //Fifth: send gameState to the network thread then go to third step
    return 0;
}

int network(){
    //First: open port to let clients connect
    //Second: initialize networking object (TODO: implement a networking object)
    //Third: create a thread for each client
    //  //Fourth: wait for clients to do something
    //  //Fifth: upon receiving an input, deserialize it and send it to the network thread
    //Sixth: send input to gameLoop
    //Seventh: get gameState/answer from gameLoop 
    //  //Eighth: send gameState to each client, then go to step Four
    //End of the game : disconnect from client, close port, close server
    return 0;
}

int main() {
    std::thread mainThread (gameLoop);
    std::thread receptionThread (network);
    std::cout << "Hello, World Server!" << std::endl;
    return 0;
}