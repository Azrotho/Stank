//
// Created by azrotho on 17/10/2026.
//

#ifndef STANK_NETWORKING_H
#define STANK_NETWORKING_H

#include <thread>


class ClientNetwork {
	public:
	ClientNetwork();
	void start();
	void stop();
	void run();
	private:
	std::thread networkThread;
};


#endif //STANK_NETWORKING_H
