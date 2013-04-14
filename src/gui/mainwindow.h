#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../client.hpp"
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

	void keyPressEvent(QKeyEvent* pe);
    void setclient(client* c);

private slots:
	void onButtonClicked();
	void onBufferReload();

private:
	QTimer* _timer;
	client *_c;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
