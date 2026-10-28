//
// Created by azrotho on 17/10/2026.
//

#include "ClientNetwork.h"

ClientNetwork::ClientNetwork() = default;

void ClientNetwork::start() {
	networkThread = std::thread(&ClientNetwork::run, this);
}

void ClientNetwork::run() {

	// TODO: Connexion au serveur

	// Creation du socket
	gf::TcpSocket socket(SERVER_IP, SERVER_PORT);

	if (!socket) {
		std::cerr << "Failed to connect to server " << SERVER_IP << ":" << SERVER_PORT << std::endl;
		return;
	}

	// TODO: Envoyer ClientHello packet au serveur

	while (!m_shouldStop.load()) {
		// TODO: Boucle recevoir les paquets.

	}
}

void ClientNetwork::stop() {
	m_shouldStop.store(true);
	this->networkThread.join();
}