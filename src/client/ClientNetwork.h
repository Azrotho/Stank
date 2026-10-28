//
// Created by azrotho on 17/10/2026.
//

#ifndef STANK_NETWORKING_H
#define STANK_NETWORKING_H

#include <thread>
#include <atomic>
#include <iostream>
#include <gf/Queue.h>
#include <gf/Packet.h>
#include <gf/TcpSocket.h>

#include "../common/Constants.h"
#include "../common/Protocol.h"

class ClientNetwork {
	public:
	ClientNetwork();
	void start();
	void stop();
	void run();
	gf::Queue<gf::Packet> queue;
	private:
	std::thread networkThread;
	gf::TcpSocket m_socket;
	std::atomic_bool m_shouldStop{false};
};


#endif //STANK_NETWORKING_H
