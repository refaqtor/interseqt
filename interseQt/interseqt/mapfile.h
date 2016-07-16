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
