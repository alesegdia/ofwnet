#include <cstdlib>
#include <iostream>
#include <enet/enet.h>
#include <thread>

int main (int argc, char** argv)
{
	ENetAddress address;
	ENetHost *server;
	ENetEvent event;
	int eventStatus;

	/** 1. ENET INITIALIZATION **/
	if(enet_initialize() != 0)
    {
        std::cerr << "Error ocurred while initializing enet.";
        return EXIT_FAILURE;
    }


	/** 2. ENET HOST CREATION  **/

	address.host = ENET_HOST_ANY;
	address.port = 1234;

	server = enet_host_create(&address, 32, 2, 0, 0);

	if(server == NULL)
	{
		std::cerr << "Error while creating enet server.\n";
		exit(EXIT_FAILURE);
	}


	/** 3. HANDLING ENET EVENTS **/
	while(1)
	{
		while (enet_host_service(server, &event, 1000)>0)
		{
			switch(event.type)
			{
				case ENET_EVENT_TYPE_CONNECT:
					std::cout << "New connection from "
						<< std::hex << event.peer->address.host << std::endl;
					break;

				case ENET_EVENT_TYPE_RECEIVE:
					std::cout << "Msg: " << event.packet->data << std::endl;
					enet_host_broadcast(server, 0, event.packet);
					enet_host_flush(server);
					break;

				case ENET_EVENT_TYPE_DISCONNECT:
					std::cout << event.peer->data << " disconnected." << std::endl;
					event.peer->data = NULL;
					break;
			}
		}
	}

	/** 4. ENET DEINITIALIZATION & HOST DESTRUCTION **/
	enet_host_destroy(server);
	enet_deinitialize();

	return 0;
}
