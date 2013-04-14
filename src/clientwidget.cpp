/*
 * =====================================================================================
 *
 *       Filename:  clientwidget.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  14/04/13 04:14:58
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Alejandro Seguí Díaz (), alesegdia@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>

#include "clientwidget.hpp"

clientwidget::clientwidget(QWidget *parent) : QWidget(parent)
{

}

clientwidget::~clientwidget()  {}

void clientwidget::setclient(client *c)
{
	_c = c;
}

void clientwidget::updateBuffer(QTextEdit *qe)
{
	emit
}
