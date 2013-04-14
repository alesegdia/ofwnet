#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../client.hpp"
#include <QTimer>
#include <QApplication>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();

	void keyPressEvent(QKeyEvent* pe);
    void setclient(client* c);
    void setQApp(QApplication *qapp);

private slots:
	void onButtonClicked();
	void onBufferReload();

private:
	QApplication *_qapp;
	client *_c;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
