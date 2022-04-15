/*-
 * Copyright (c) 2016 Marcel Kaiser. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include <QStyle>
#include <QDesktopWidget>
#include <QWindow>
#include <QScreen>
#include "mainwin.h"
#include "bgwin.h"
#include "qt-helper/qt-helper.h"

#define PB_STYLE "padding: 2px; text-align: left;"

Mainwin::Mainwin(QWidget *parent) : QDialog(parent)
{
	icon_logout		 = qh_loadIcon("system-log-out");
	icon_shutdown		 = qh_loadIcon("system-shutdown");
	icon_suspend		 = qh_loadIcon("system-suspend");
	icon_reboot   		 = qh_loadIcon("system-reboot");
	icon_lock     		 = qh_loadIcon("system-lock-screen");
	QIcon icon_cancel 	 = qh_loadStockIcon(
					QStyle::SP_DialogCancelButton, NULL);
	QVBoxLayout *vbox	 = new QVBoxLayout;
	QVBoxLayout *layout	 = new QVBoxLayout(this);
	QPushButton *pb_logout	 = new QPushButton(icon_logout, tr("Logout"));
	QPushButton *pb_cancel   = new QPushButton(icon_cancel, tr("Cancel"));
	QPushButton *pb_lock     = new QPushButton(icon_lock,
						   tr("Lock screen"));
	QPushButton *pb_reboot	 = new QPushButton(icon_reboot,
						   tr("Reboot system"));
	QPushButton *pb_shutdown = new QPushButton(icon_shutdown,
						   tr("Shutdown system"));
	QPushButton *pb_suspend  = new QPushButton(icon_suspend,
						   tr("Suspend system"));
	pb_logout->setStyleSheet(PB_STYLE);
	pb_reboot->setStyleSheet(PB_STYLE);
	pb_shutdown->setStyleSheet(PB_STYLE);
	pb_cancel->setStyleSheet(PB_STYLE);
	pb_suspend->setStyleSheet(PB_STYLE);
	pb_lock->setStyleSheet(PB_STYLE);

	vbox->addWidget(pb_shutdown);
	vbox->addWidget(pb_reboot);
	vbox->addWidget(pb_logout);
	vbox->addWidget(pb_suspend);
	vbox->addWidget(pb_lock);
	vbox->addWidget(pb_cancel);
	vbox->setSpacing(5);
	layout->addLayout(vbox);
	layout->setContentsMargins(15, 15, 15, 15);

	connect(pb_lock,     SIGNAL(clicked()), this, SLOT(lockClicked()));
	connect(pb_logout,   SIGNAL(clicked()), this, SLOT(logoutClicked()));
	connect(pb_reboot,   SIGNAL(clicked()), this, SLOT(rebootClicked()));
	connect(pb_shutdown, SIGNAL(clicked()), this, SLOT(shutdownClicked()));
	connect(pb_suspend,  SIGNAL(clicked()), this, SLOT(suspendClicked()));
	connect(pb_cancel,   SIGNAL(clicked()), this, SLOT(reject()));

	setModal(true);
	setWindowFlags(windowFlags() | Qt::Dialog | Qt::FramelessWindowHint |
	    Qt::WindowStaysOnTopHint | Qt::BypassWindowManagerHint);
	show();
	setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter,
	    size(), qApp->primaryScreen()->geometry()));
}

void Mainwin::logoutClicked()
{
		button = LOGOUT;
		accept();
}

void Mainwin::rebootClicked()
{
		button = REBOOT;
		accept();
}

void Mainwin::shutdownClicked()
{
		button = SHUTDOWN;
		accept();
}

void Mainwin::suspendClicked()
{
		button = SUSPEND;
		accept();
}

void Mainwin::lockClicked()
{
		button = LOCK;
		accept();
}

int Mainwin::getButton()
{
	return (button);
}

