/****************************************************************************
* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this file,
* You can obtain one at http://mozilla.org/MPL/2.0/.
*
* Copyright (c) 2016, shannon.mackey@refaqtory.com
* ***************************************************************************/
#ifndef MAPFILE_H
#define MAPFILE_H

#include <QFile>
#include <QObject>
#include <QVariantMap>

class MapFile : public QObject
{
    Q_OBJECT

public:
    explicit MapFile(QString filename, QObject *parent = 0);
    ~MapFile();

    QVariant get(QString key);
    QString filename();
    QStringList keys();

signals:
    void dataChanged(QString key, QVariant value);

public slots:
    void save();

    void set(QString key, QVariant value, bool save = true);


private:
    QString _filename;
    QVariantMap _data_map;

    void loadDataMap(QFile &load_file);
};


#endif // MAPFILE_H
