//
// Created by azrotho on 28/10/2026.
//

#ifndef STANK_PROTOCOL_H
#define STANK_PROTOCOL_H

#include <string>
#include <gf/Id.h>
#include <gf/SerializationOps.h>

#include "Struct.h"

using namespace gf::literals;

/*
 * Client --> Server packets
 */

struct ClientHello {
	static constexpr gf::Id type = "ClientHello"_id;
};

template<typename Archive>
Archive& operator|(Archive& ar, ClientHello& data) {
	return ar;
}

struct ClientMove {
	static constexpr gf::Id type = "ClientMove"_id;
	TankControls controls;
};

template <typename Archive>
Archive& operator|(Archive& ar, ClientMove& data) {
	return ar | data.controls;
}


struct ClientDisconnect {
	static constexpr gf::Id type = "ClientDisconnect"_id;
};

template <typename Archive>
Archive& operator|(Archive& ar, ClientDisconnect& data) {
	return ar;
}

struct ClientPlayerDisconnect {
	static constexpr gf::Id type = "ClientDisconnect"_id;
	gf::Id id;
};

template <typename Archive>
Archive& operator|(Archive& ar, ClientPlayerDisconnect& data) {
	return ar | data.id;
}

struct ClientPlayerConnect {
	static constexpr gf::Id type = "ClientDisconnect"_id;
	gf::Id id;
};

template <typename Archive>
Archive& operator|(Archive& ar, ClientPlayerConnect& data) {
	return ar | data.id;
}


/*
 * Server --> Client packets
 */

struct ServerHello {
	static constexpr gf::Id type = "ServerHello"_id;
	gf::Id id; // donner un id
	std::string name;
};

template<typename Archive>
Archive& operator|(Archive& ar, ServerHello& data) {
	return ar | data.id | data.name;
}

struct ServerTankUpdate {
	static constexpr gf::Id type = "ServerTankUpdate"_id;
	gf::Id id; // id of the tank to update
	float x;
	float y;
	float rot;
};

template<typename Archive>
Archive& operator|(Archive& ar, ServerTankUpdate& data) {
	return ar | data.id | data.x | data.y | data.rot;
}

#endif //STANK_PROTOCOL_H
