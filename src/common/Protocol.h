//
// Created by azrotho on 28/10/2026.
//

#ifndef STANK_PROTOCOL_H
#define STANK_PROTOCOL_H

#include <string>
#include <gf/Id.h>
#include <gf/SerializationOps.h>

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
	float x;
	float y;
	float rot;
};

template <typename Archive>
Archive& operator|(Archive& ar, ClientMove& data) {
	return ar | data.x | data.y | data.rot;
}

/*
 * Server --> Client packets
 */

#endif //STANK_PROTOCOL_H
