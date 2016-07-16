#ifndef CAPACITOR_H
#define CAPACITOR_H

#include <QFile>
#include <QMap>
#include <QObject>
#include <QProcess>

class VersionControlSystem : public QObject
{
    Q_OBJECT
public:
    explicit VersionControlSystem(QString working_path, QObject *parent = 0);
    ~VersionControlSystem();

//    QString workingPath() const;

//    QString gitRawDiff(quint32 newest_index, quint32 oldest_index);

    QByteArray gitFileContents(quint32 index, QString filename);

    QString gitStat();

public slots:

    void gitCommit(QString note = "---");

private:
    QString _working_path;

    QProcess *git_run;
    QString _output;
    QByteArray _contents;

    void gitInit();
    QString gitOutput(QStringList args);
};

#endif // CAPACITOR_H
