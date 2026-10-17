//
// Created by azrotho on 17/10/2026.
//

#include "Networking.h"


Networking::Networking() = default;

void Networking::start() {
	networkThread = std::thread(&Networking::run, this);
}

void Networking::run() {
	// TODO: do someting
}

void Networking::stop() {
	this->networkThread.join();
}