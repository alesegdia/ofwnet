#include "mainwindow.h"
#include <QMainWindow>
#include "ui_mainwindow.h"
#include "../client.hpp"
#include <string>
#include <QKeyEvent>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //ui->pushButton->setDefault(true);
    _timer = new QTimer(this);

    //connect(_timer, SIGNAL(timeout()), this, SLOT(onBufferReload()));
    //_timer->start(1000);
	connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(onButtonClicked()));
}

  //connect(ui->b_create, SIGNAL(clicked()), this, SLOT(on_b_create_clicked()));

void MainWindow::keyPressEvent(QKeyEvent* pe)
{
	if(pe->key() == Qt::Key_Return) onButtonClicked();
	if(pe->key() == Qt::Key_Escape)
	{
		_c->cerrar();
		this->close();
	}
}

MainWindow::~MainWindow()
{
	delete _timer;
    delete ui;
}

void MainWindow::onButtonClicked()
{
	_c->broadcast_data(ui->lineEdit->displayText().toUtf8().constData());
	ui->lineEdit->clear();
}

void MainWindow::onBufferReload()
{
	ui->textEdit->clear();
	ui->textEdit->append(_c->getqstring());
}

void MainWindow::setclient(client *c)
{
	_c = c;
    connect(_c, SIGNAL(bufferUpdated()), this, SLOT(onBufferReload()));
}

