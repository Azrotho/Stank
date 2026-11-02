//
// Created by azrotho on 17/10/2026.
//

#include "ClientNetwork.h"

ClientNetwork::ClientNetwork() = default;

void ClientNetwork::start() {
	networkThread = std::thread(&ClientNetwork::run, this);
	networkThread.detach();
}

void ClientNetwork::run() {

	// Connexion au serveur

	// Creation du socket
	gf::TcpSocket socket(SERVER_IP, SERVER_PORT);

	if (!socket) {
		std::cerr << "Failed to connect to server " << SERVER_IP << ":" << SERVER_PORT << std::endl;
		return;
	}

	m_isConnected.store(true);

	// Envoyer ClientHello packet au serveur

	m_socket = std::move(socket);
	send(ClientHello{});

	while (!m_shouldStop.load()) {
		// TODO: Boucle recevoir les paquets.
		gf::Packet packet;

		if (!m_socket) {
			gf::Log::error("Socket is not connected\n");
			m_isConnected.store(false);
			m_shouldStop.store(true);
			return;
		}

		switch (m_socket.recvPacket(packet)) {
			case gf::SocketStatus::Data:
				queue.push(std::move(packet));
				break;
			case gf::SocketStatus::Error:
				gf::Log::error("Error while receiving a packet from server\n");
				m_isConnected.store(false);
				m_shouldStop.store(true);
				return;
			case gf::SocketStatus::Close:
				gf::Log::info("End of connection to the server\n");
				m_isConnected.store(false);
				m_shouldStop.store(true);
				return;
			case gf::SocketStatus::Block:
				assert(false);
				break;
		}
	}
}

void ClientNetwork::stop() {
	m_shouldStop.store(true);
}