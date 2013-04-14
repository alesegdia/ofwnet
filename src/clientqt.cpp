#include <cstdlib>
#include <cstring>
#include <iostream>
#include <enet/enet.h>
#include <boost/thread.hpp>
#include <QtGui/QApplication>
#include "gui/mainwindow.h"
#include "client.hpp"


int main(int argc, char** argv)
{

	/** 1. ENET INITIALIZATION **/
	if(enet_initialize() != 0)
	{
		std::cerr << "Error ocurred while initializing enet.";
		return EXIT_FAILURE;
	}

	QApplication app(argc, argv);
	std::cout << "qapp ok\n";
	MainWindow window;
	std::cout << "window ok\n";

	client *c = new client();
	c->init(argv[1], argv[2]);

	std::cout << "cliente creado\n";
	window.setclient(c);
	std::cout << "window setclient ok\n";

	std::cout << "cliente seteado\n";
	boost::thread t(boost::bind(&client::run, c));

	window.setQApp(&app);
	window.show();
	app.exec();

	t.join();

	delete c;
	enet_deinitialize();

	return 0;
}
