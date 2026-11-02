//
// Created by azrotho on 17/10/2026.
//

// Un grand merci au fichier https://github.com/Hatunruna/ggj2020/blob/master/code/bits/client/ClientNetwork.cc kekw
// sinon impossible kekw

#ifndef STANK_NETWORKING_H
#define STANK_NETWORKING_H

#include <thread>
#include <atomic>
#include <iostream>
#include <gf/Queue.h>
#include <gf/Packet.h>
#include <gf/TcpSocket.h>
#include <gf/Log.h>

#include "../common/Constants.h"
#include "../common/Protocol.h"

class ClientNetwork {
	public:
	ClientNetwork();
	void start();
	void stop();
	void run();
	gf::Queue<gf::Packet> queue;
	std::atomic_bool m_isConnected{false};
	template<typename T>
	void send(const T& data) {
			gf::Packet packet;
			packet.is(data);
			m_socket.sendPacket(packet);
	}
	private:
	std::thread networkThread;
	gf::TcpSocket m_socket;
	std::atomic_bool m_shouldStop{false};
};


#endif //STANK_NETWORKING_H
