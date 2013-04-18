#include "mainwindow.h"
#include <QMainWindow>
#include "ui_mainwindow.h"
#include "../client.hpp"
#include <string>
#include <QKeyEvent>
#include <iostream>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(onButtonClicked()));

	_sample = new QSound("sonido.wav", this);
    _sample->setLoops(5);
	connect(ui->pushButton, SIGNAL(clicked()), _sample, SLOT(play()));
}

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
    delete ui;
}

void MainWindow::setQApp(QApplication* qapp)
{
	_qapp = qapp;
}

void MainWindow::onButtonClicked()
{
	_c->broadcast_data(ui->lineEdit->displayText().toUtf8().constData());
	ui->lineEdit->clear();
}

void MainWindow::onBufferReload()
{
	QSound::play("sonido.wav");
	_sample->play();
	_qapp->alert(this, 5000);
	ui->textEdit->clear();
	ui->textEdit->append(_c->getqstring());
}

void MainWindow::setclient(client *c)
{
	_c = c;
    connect(_c, SIGNAL(bufferUpdated()), this, SLOT(onBufferReload()));
}

