// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at http://mozilla.org/MPL/2.0/.

// Copyright (c) 2015, Shannon Mackey refaQtor@gmail.com


#include "processconnection.h"

#include <QFileInfo>
#include <QDir>
#include <QDebug>

//#include <//qDebug>

ProcessConnection::ProcessConnection(QString exe_pathname, QObject *parent) :
    QObject(parent),
    _output(QString(""))
{
    executeChronicled(QStringList() << exe_pathname);
}

void ProcessConnection::executeChronicled(QStringList args)
{
    _output.clear();
    QFileInfo fi(args.value(0));
    QString working_directory(fi.absolutePath());

    QDir::setCurrent(working_directory);
    _chronicled_run = new QProcess(qobject_cast<QObject *>(this));
   // _chronicled_run = new QProcess();

    _chronicled_run->setReadChannel(QProcess::StandardOutput);

    connect(_chronicled_run, &QProcess::readyRead,
    this, &ProcessConnection::harvestOutput);
    connect(_chronicled_run, &QProcess::readyReadStandardError,
            this, &ProcessConnection::harvestOutput);
    connect(_chronicled_run, &QProcess::readyReadStandardOutput,
            this, &ProcessConnection::harvestOutput);

    _chronicled_run->setWorkingDirectory(working_directory);

    _chronicled_run->setProcessChannelMode(QProcess::MergedChannels);
    qDebug() << args;
    _chronicled_run->start(args.value(0), args);
    qDebug() << _chronicled_run->waitForStarted();
    qDebug() << _chronicled_run->state();

//        _chronicled_run->waitForReadyRead();
//        _chronicled_run->waitForFinished();
//        _chronicled_run->deleteLater();
}

void ProcessConnection::sendCommand(QString cmd, QString payload)
{
    QString stuff = QString("%1 %2\n").arg(cmd).arg(payload);
    _chronicled_run->write(stuff.toLocal8Bit());
}

void ProcessConnection::harvestOutput()
{
    //qDebug("harvestOutput");

    QString msg = _chronicled_run->readAllStandardOutput();
    if (msg != "") {
                //qDebug() << msg;
        _output.append(msg.remove("\""));
    }
    QString err = _chronicled_run->readAllStandardError();
    if (err != ""){
                //qDebug() << err;
        _output.append(err);
    }
    emit resultsReady();
}

QString ProcessConnection::output()
{
    return _output;
}

