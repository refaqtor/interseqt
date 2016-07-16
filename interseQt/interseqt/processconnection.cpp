/****************************************************************************
* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this file,
* You can obtain one at http://mozilla.org/MPL/2.0/.
*
* Copyright (c) 2016, shannon.mackey@refaqtory.com
* ***************************************************************************/
#include "processconnection.h"

#include <QFileInfo>
#include <QDir>
#include <QStandardPaths>
#include <QDebug>

QString appLocalDataLocation()
{
    return QStandardPaths::standardLocations(QStandardPaths::AppLocalDataLocation)
                .value(0,QDir::homePath());
}

QString extractResourceFile(QString resource_filepath, QString disk_filename, bool executable = false)
{  //this resource extraction requires "Q_INIT_RESOURCE(data);" in the constructor
    bool ok = false;
    QString local_file_path = appLocalDataLocation();

    qDebug() << "extraction: " << local_file_path;

    QDir dir;
    ok = dir.mkpath(local_file_path);
    if (!ok) qDebug() << QString("ERROR: %1 folder creation failed.").arg(local_file_path);

    local_file_path.append("/" + disk_filename);
    QFile::remove(local_file_path);

    ok = QFile::copy(resource_filepath,local_file_path);
    if (!ok) qDebug() << QString("ERROR: %1 file copy to %2 failed.").arg(resource_filepath).arg(local_file_path);

    QFile new_file(local_file_path);
    if (!executable){
        ok = new_file.setPermissions(QFileDevice::ReadOwner | QFileDevice::WriteOwner);
    } else {
        ok = new_file.setPermissions(QFileDevice::ReadOwner | QFileDevice::WriteOwner | QFileDevice::ExeOwner);
    }

    if (!ok) qDebug() << QString("ERROR: %1 permission settings failed.").arg(local_file_path);

    if (ok)
        return new_file.fileName();
    else
        return QString("");
}

ProcessConnection::ProcessConnection(QString exe_pathname, QObject *parent) :
    QObject(parent),
    gitOutput(QString(""))
{
    executeGit(QStringList() << exe_pathname);
}

void ProcessConnection::executeGit(QStringList args)
{
    gitOutput.clear();
    QFileInfo fi(args.value(0));
    QString working_directory(fi.absolutePath());

    QDir::setCurrent(working_directory);
    //TODO: delete lastQProcess pointer, if exists, before settingnew one
    gitProcess = new QProcess(qobject_cast<QObject *>(this));
   // gitProcess = new QProcess();

    gitProcess->setReadChannel(QProcess::StandardOutput);

    connect(gitProcess, &QProcess::readyRead,
    this, &ProcessConnection::harvestOutput);
    connect(gitProcess, &QProcess::readyReadStandardError,
            this, &ProcessConnection::harvestOutput);
    connect(gitProcess, &QProcess::readyReadStandardOutput,
            this, &ProcessConnection::harvestOutput);

    gitProcess->setWorkingDirectory(working_directory);

    gitProcess->setProcessChannelMode(QProcess::MergedChannels);
    qDebug() << args;
    gitProcess->start(args.value(0), args);
    qDebug() << gitProcess->waitForStarted();
    qDebug() << gitProcess->state();

//        gitProcess->waitForReadyRead();
//        gitProcess->waitForFinished();
//        gitProcess->deleteLater();
}

void ProcessConnection::sendCommand(QString cmd, QString payload)
{
    QString stuff = QString("%1 %2\n").arg(cmd).arg(payload);
    gitProcess->write(stuff.toLocal8Bit());
}

void ProcessConnection::harvestOutput()
{
    //qDebug("harvestOutput");

    QString msg = gitProcess->readAllStandardOutput();
    if (msg != "") {
                //qDebug() << msg;
        gitOutput.append(msg.remove("\""));
    }
    QString err = gitProcess->readAllStandardError();
    if (err != ""){
                //qDebug() << err;
        gitOutput.append(err);
    }
    emit resultsReady();
}

QString ProcessConnection::output()
{
    return gitOutput;
}

