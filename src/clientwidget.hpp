#ifndef __CLIENT_WID__
#define __CLIENT_WID__

#include <QWidget>
#include "client.hpp"

class clientwidget : public QWidget
{
	Q_OBJECT

	public:
		explicit clientwidget(QWidget *parent = 0);
		~clientwidget();
		setclient(client *c);

	signals:
		void bufferUpdated();

	slots:
		void updateBuffer();

	private:
		client *_c;
}

#endif
