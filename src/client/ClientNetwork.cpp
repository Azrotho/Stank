//
// Created by azrotho on 17/10/2026.
//

#include "ClientNetwork.h"


ClientNetwork::ClientNetwork() = default;

void ClientNetwork::start() {
	networkThread = std::thread(&ClientNetwork::run, this);
}

void ClientNetwork::run() {
	// TODO: do someting
}

void ClientNetwork::stop() {
	this->networkThread.join();
}