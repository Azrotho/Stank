//
// Created by shirocku on 20/10/2026.
//

#include "ServerNetworking.h"

#include <csignal>
#include <stdexcept>
#include <cinttypes>

#include "../common/Protocol.h"
#include <gf/TcpListener.h>
#include <gf/Log.h>
#include "../common/Constants.h"

ServerNetworking::ServerNetworking(gf::Random& random)
: m_random(random)
, m_listener(Service)
{
    if (!m_listener) {
        throw std::runtime_error("Can not start listener.");
    }
    m_selector.addSocket(m_listener);
    gf::Log::info("(SERVER) Waiting for connections on port %s...\n", Service);
}

void ServerNetworking::run() {
    static constexpr gf::Time Timeout = gf::seconds(1);
    while (g_running){
        auto status = m_selector.wait(Timeout);

        if (status == gf::SocketSelectorStatus::Timeout) {
            continue;
        }

        if (status == gf::SocketSelectorStatus::Error) {
            gf::Log::error("(SERVER) An error occurred in the selector. Stopping the server...\n");
            break;
        }

        std::vector<gf::Id> purgatory; // Pour stocker les clients à purger
        for (auto& kv :m_players) {
            auto& player = kv.second;

            if (m_selector.isReady(player.socket)) {
                gf::Packet packet;
                switch (player.socket.recvPacket(packet)) {
                    case gf::SocketStatus::Data:
                        switch (packet.getType()) {
                            case ClientDisconnect::type:
                                gf::Log::info("(SERVER) {%" PRIX64 "} Disconnected.\n", player.id);
                                purgatory.push_back(player.id);
                                break;
                            default:
                                //TODO update le lobby
                                break;
                        }
                        break;

                    case gf::SocketStatus::Error:
                        gf::Log::error("(SERVER) {%" PRIX64 "} Error receiving data.\n", player.id);

                        case gf::SocketStatus::Close:
                            gf::Log::info("(SERVER) {%" PRIX64 "} Socket closed.\n", player.id);
                            purgatory.push_back(player.id);
                            break;
                    case gf::SocketStatus::Block:
                        assert(false);
                        break;
                }
            }
        }

        if (m_selector.isReady(m_listener)) {
            gf::TcpSocket socket = m_listener.accept();
            if (!socket)continue;

            gf::Id id = m_random.get().computeId();

            ServerPlayer playerInstance;
            playerInstance.id = id;
            playerInstance.socket = std::move(socket);
            playerInstance.name = "";

            auto res = m_players.emplace(id, std::move(playerInstance));
            assert(res.second);
            auto& player = res.first->second;//TODO à comprendre
            m_selector.addSocket(player.socket);
            //TODO ajouter le joueur au ServerLobby

            gf::Log::info("(SERVER) {%" PRIX64 "} Connected.\n", player.id);

            if (!purgatory.empty()) {
                for (auto id : purgatory) {
                    auto it = m_players.find(id);
                    assert(it != m_players.end());
                    auto& player = it->second;
                    m_selector.removeSocket(player.socket);
                    //TODO retirer le joueur du ServerLobby
                    m_players.erase(it);
                }
            }
        }

    }
}

