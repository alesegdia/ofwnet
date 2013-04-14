#include <cstdlib>
#include <cstring>
#include <iostream>
#include <enet/enet.h>
#include <omp.h>
#include <boost/thread.hpp>

ENetAddress address;
ENetHost *client;
ENetPeer *peer;
ENetEvent event;

void eventHandling();
void inputAsking();

bool salir = false;
void irse()
{
	salir = true;
}

int main(int argc, char** argv)
{
	/** 1. ENET INITIALIZATION **/
	if(enet_initialize() != 0)
	{
		std::cerr << "Error ocurred while initializing enet.";
		return EXIT_FAILURE;
	}


	/** 2. ENET HOST CREATION **/
	client = enet_host_create (NULL, 1, 2, 57600/8, 14400/8);

	if(client == NULL)
	{
		std::cerr << "Error while creating enet client" << std::endl;
		exit(EXIT_FAILURE);
	}

	std::cout << "Host: " << argv[1] << std::endl;
	enet_address_set_host(&address, argv[1]);
	address.port = 1234;

	/** 3. CONNECT AND USER SERVICE **/
	peer = enet_host_connect(client, &address, 2, 0);

	if(peer == NULL)
	{
		std::cerr << "No peers avail. to init a cx." << std::endl;
		exit(EXIT_FAILURE);
	}

	boost::thread t1(eventHandling);
	boost::thread t2(inputAsking);

	t1.join();
	t2.join();

	enet_host_destroy(client);
	enet_deinitialize();

	return 0;
}

void eventHandling()
{
	while(!salir)
	{
		while (enet_host_service(client, &event, 1000)>0)
		{
			switch(event.type)
			{
			case ENET_EVENT_TYPE_CONNECT:
				std::cout << "Conexion con "
					<< std::hex << event.peer->address.host << std::endl;
				std::cout.flush();
				break;

			case ENET_EVENT_TYPE_RECEIVE:
				std::cout << "Msg: " << event.packet->data << std::endl;
				std::cout.flush();
				enet_packet_destroy(event.packet);
				break;

			case ENET_EVENT_TYPE_DISCONNECT:
				std::cout << event.peer->data << " disconnected." << std::endl;
				event.peer->data=NULL;
				std::cout.flush();
			}
		}
	}
}
std::string line;
void inputAsking()
{
	while(!salir)
	{
		std::cout << "Say> ";
		std::getline(std::cin, line);
		if(line == "irse") irse();
		const char *message = line.c_str();

		if(strlen(message) > 0)
		{
			ENetPacket *packet = enet_packet_create(message, strlen(message)+1,
					ENET_PACKET_FLAG_RELIABLE);
			//strcpy(&packet->data, message);
			enet_peer_send(peer, 0, packet);
			//enet_host_flush(client);
		}
	}
}
