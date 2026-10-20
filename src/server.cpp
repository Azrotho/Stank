//
// Created by azrotho on 09/10/2026.
//

#include <iostream>
#include <thread>
#include "common/Constants.h"

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

int main() {
    std::thread mainThread (gameLoop);
    std::cout << "Hello, World Server!" << std::endl;
    return 0;
}