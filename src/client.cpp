#include <iostream>
#include <string>
#include "client.hpp"

#include <string>
#include <enet/enet.h>
#include <QString>
#include <QByteArray>
#include <qstring.h>
#include <string>

client::~client()
{
	enet_host_destroy(_client);
}

client::client(QWidget *parent) : QWidget(parent) {
	corriendo = true;
}

void client::init(std::string host, std::string pname)
{
	name = pname;
	_client = enet_host_create(NULL, 1, 2, 57600/8, 14400/8);
	if(_client == NULL)
	{
		std::cerr << "Error while creating client." << std::endl;
		exit(EXIT_FAILURE);
	}

	std::cout << "Host: " << host << std::endl;
	enet_address_set_host(&_address, host.c_str());
	_address.port=1234;

	_peer = enet_host_connect(_client, &_address, 2, 0);
	if(_peer == NULL)
	{
		std::cerr << "No peers available to init a connection." << std::endl;
		exit(EXIT_FAILURE);
	}
}

void client::cerrar()
{
	corriendo = false;
}

void client::run()
{
	while(corriendo)
    {
        while (enet_host_service(_client, &_event, 1000)>0)
        {
            switch(_event.type)
            {
            case ENET_EVENT_TYPE_CONNECT:
                std::cout << "Conexion con "
                    << std::hex << _event.peer->address.host << std::endl;
                std::cout.flush();
                break;

            case ENET_EVENT_TYPE_RECEIVE:
                std::cout << "Msg: " << _event.packet->data << std::endl;
                std::cout.flush();

				qs.append((const char*)(_event.packet->data));
                qs.append("\n");
				emit bufferUpdated();
                enet_packet_destroy(_event.packet);
                break;

            case ENET_EVENT_TYPE_DISCONNECT:
                std::cout << _event.peer->data << " disconnected." << std::endl;
                std::cout.flush();
            }
        }
    }
}

QString client::getqstring()
{
	return qs;
}

void client::broadcast_data(std::string s)
{
	std::string line;
	line += name;
	line += ": ";
	line += s;
	if(s.size() > 0)
	{
		ENetPacket *packet = enet_packet_create(line.c_str(), line.size()+1, ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(_peer, 0, packet);
	}
}
