#include <cstdlib>
#include <iostream>
#include <enet/enet.h>
#include <string>
#include <boost/thread.hpp>
#include "netmsg.pb.h"

int main (int argc, char** argv)
{
	ENetPeer *peer;
	ENetAddress address;
	ENetHost *client;
	ENetEvent event;

	/** 1. ENET INITIALIZATION **/
	if(enet_initialize() != 0)
    {
        std::cerr << "Error ocurred while initializing enet.";
        return EXIT_FAILURE;
    }


	/** 2. ENET HOST CREATION  **/

	address.host = ENET_HOST_ANY;
	address.port = 1234;

	client = enet_host_create(NULL, 1, 2, 57600/8, 14400/8);

	if(client == NULL)
	{
		std::cerr << "Error while creating enet client.\n";
		exit(EXIT_FAILURE);
	}

	// AQUI ES PARA CAMBIAR EL HOST
	enet_address_set_host(&address, argv[1]);
	address.port=1234;

	peer = enet_host_connect(client, &address, 2, 0);

	if(peer == NULL)
	{
		std::cerr << "no peers";
		exit(EXIT_FAILURE);
	}


	/** 3. HANDLING ENET EVENTS **/
	while(1)
	{
		while (enet_host_service(client, &event, 1000)>0)
		{
			switch(event.type)
			{
				case ENET_EVENT_TYPE_CONNECT:
					std::cout << "New connection from "
						<< std::hex << event.peer->address.host << std::endl;
					break;

				case ENET_EVENT_TYPE_RECEIVE: {
					std::cout << "Msg: " << event.packet->data << std::endl;

					std::string msg ((char*)event.packet->data);

					player_msg pmsg;
					pmsg.ParseFromString(msg);

					//create_player_data cpdata;
					//create_player_response cpresponse;
					//msg.ParseFromString(msg);

					enet_host_broadcast(client, 0, event.packet);





					/* RESPUESTA */
					player_msg cpresponse;
					// rellenar response
					//
					//



					std::string serialized;
					cpresponse.SerializeToString(&serialized);

					ENetPacket *packetresp = enet_packet_create(
							serialized.c_str(),
							serialized.size()+1,
							ENET_PACKET_FLAG_RELIABLE);

					enet_peer_send(event.peer, 0, packetresp);
					enet_host_flush(client);
					break;
				}

				case ENET_EVENT_TYPE_DISCONNECT:
					std::cout << event.peer->data << " disconnected." << std::endl;
					event.peer->data = NULL;
					break;
			}
		}
	}

	/** 4. ENET DEINITIALIZATION & HOST DESTRUCTION **/
	enet_host_destroy(client);
	enet_deinitialize();

	return 0;
}
