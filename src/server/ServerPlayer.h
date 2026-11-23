//
// Created by shirocku on 01/11/2026.
//

#ifndef STANK_SERVERPLAYER_H
#define STANK_SERVERPLAYER_H

#include <cstdint>
#include <gf/Sprite.h>
#include <gf/Texture.h>
#include <string>
#include <cmath>
#include <gf/Packet.h>
#include <gf/TcpSocket.h>



class ServerPlayer {

	public:
		ServerPlayer(float x, float y, float rot);
		void move(bool forward,bool backward,bool right,bool left,float dt);
		//renvoie true si un obus a été créé
		//renvoie false sinon
		bool shoot(); // pas encore implem
		float getX() const;
		float getY() const;
		float getRotation() const;
		float getSpeed() const;

		void setX(float newX);
		void setY(float newY);
		void setRotation(float newRotation);


        //c'était dans le struct donc j'le replace là
        gf::Id id = gf::InvalidId;
        std::string name;
        gf::TcpSocket socket;
        //si besoin d'une team : int32_t team = -1;
        //si besoin d'un lobby i guess ??? : bool ready = false;
    
        template<typename T>
        void send(const T& data) {
            gf::Packet packet;
            packet.is(data);
            socket.sendPacket(packet);
        }
		
	private :
		void deceleration(float dt);
		bool whatDir();
		//variables pour la vitesse
		float accel = 70.0f;
		float speed = 0.0f;
		float maxSpeed = 100.0f;
		//variables pour tourner
		float turn = 0.0f;
		float turnAccel=300.0f;
		float maxTurn=150.0f;
		//frein
		float brake=200.0f;

		//stats de bases
		float pv=100.0f;
		float pvMax=100.0f;
		float damages=50.0f;
	    float reloadTime=3.0f;


		float x;
		float y;
		float rot;
};

#endif //STANK_SERVERPLAYER_H