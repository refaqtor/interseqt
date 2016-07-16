#include "mapfile.h"
#include <QDebug>


#include <QException>
#include <QJsonDocument>
#include <QJsonObject>

MapFile::MapFile(QString filename, QObject *parent) : QObject(parent),
    _filename(filename)
{
    Q_ASSERT(!filename.isEmpty());
    QFile load_file(_filename);
    try {
        if (load_file.exists()){
            if (load_file.open(QIODevice::ReadOnly)){
                loadDataMap(load_file);
            }
        } else {
            if (load_file.open(QIODevice::ReadWrite)) {
                QJsonDocument data_doc = QJsonDocument(QJsonObject::fromVariantMap(QVariantMap()));
                load_file.write(data_doc.toJson());
                loadDataMap(load_file);
            }
        }
    } catch (QException e) {
        //TODO: handle catch
    }
}

MapFile::~MapFile()
{
   // save();
}

void MapFile::save()
{
    QFile save_file(_filename);
    try {
        bool ok = save_file.open(QIODevice::WriteOnly);
        Q_ASSERT(ok);
        QJsonObject json_object = QJsonObject::fromVariantMap(_data_map);
        QJsonDocument data_doc = QJsonDocument(json_object);
        save_file.write(data_doc.toJson());
    } catch (QException e) {
        //TODO: handle catch
    }
}

void MapFile::loadDataMap(QFile &load_file)
{
    QByteArray load_data = load_file.readAll();
    QJsonDocument data_doc = QJsonDocument::fromJson(load_data);
   // Q_ASSERT(!data_doc.isEmpty());
    _data_map = data_doc.object().toVariantMap();
}

QVariant MapFile::get(QString key)
{
    return _data_map.value(key);
}

QString MapFile::filename()
{
    return _filename;
}

QStringList MapFile::keys()
{
    return _data_map.keys();
}

void MapFile::set(QString key, QVariant value, bool save)
{
    if (_data_map[key] != value){
        _data_map[key] = value;
        if (save)
            this->save();
        emit dataChanged(key, value);
    }
    Q_ASSERT(_data_map[key] == value);
}
