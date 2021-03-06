/****************************************************************************
* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this file,
* You can obtain one at http://mozilla.org/MPL/2.0/.
*
* Copyright (c) 2016, shannon.mackey@refaqtory.com
* ***************************************************************************/
#ifndef PROCESSCONNECTION_H
#define PROCESSCONNECTION_H

#include <QObject>
#include <QProcess>

class ProcessConnection : public QObject
{
    Q_OBJECT
public:
    ProcessConnection(QString exe_pathname, QObject *parent = 0);
    QString output();

public slots:
    void sendCommand(QString cmd, QString payload = "");


signals:
    void resultsReady();

private:
    QProcess *gitProcess;
    QString gitOutput;

    void executeGit(QStringList args);
    void harvestOutput();
};

#endif // PROCESSCONNECTION_H
