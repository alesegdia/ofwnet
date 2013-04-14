#ifndef __CLIENT__
#define __CLIENT__

#include <enet/enet.h>
#include <QString>
#include <QWidget>

class client : public QWidget
{
	Q_OBJECT

	public:
		explicit client(QWidget *parent = 0);// : QWidget(parent) {}
		~client(); // {enet_host_destroy(_client); }
		void init(std::string host, std::string pname);
		void run();
		void broadcast_data(std::string s);
		QString getqstring();
		void cerrar();

	signals:
		void bufferUpdated();

	protected:
		bool corriendo;
		ENetAddress _address;
		ENetHost *_client;
		ENetPeer *_peer;
		ENetEvent _event;
		QString qs;
		std::string name;
};

#endif
