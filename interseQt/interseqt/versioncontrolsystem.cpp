#include "versioncontrolsystem.h"

#include <QDebug>
#include <QDir>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QSet>
#include <QProcess>
#include <QStandardPaths>



VersionControlSystem::VersionControlSystem(QString working_path, QObject *parent) :
    QObject(parent),
    _working_path(QDir::toNativeSeparators(working_path)),
    git_run(new QProcess()),
    _output(""),
    _contents("")
{
    Q_ASSERT(!_working_path.isEmpty());
    QString repo_path(QDir::toNativeSeparators( _working_path + "/.git"));
    if (!QFile::exists(repo_path)) {
        QDir work;
        work.mkpath(_working_path.toLocal8Bit());
        Q_ASSERT(QFile::exists(work.canonicalPath()));
        gitInit();
    }
}

VersionControlSystem::~VersionControlSystem()
{
}

void VersionControlSystem::gitInit()
{
    //TODO: set local git user here
    qDebug()<< gitOutput(QStringList() << "init");
    QString ignore_file(QDir::toNativeSeparators(QDir::cleanPath( _working_path + "/.gitignore")));
    if (!QFile::copy(":/resources/gitignore.txt", ignore_file)) {
        qDebug() << "initialization failed : " << ignore_file;
    } else {
        Q_ASSERT(QFile::exists(ignore_file));
        gitCommit("begin chronicle");
    }
}

void VersionControlSystem::gitCommit(QString note)
{
    qDebug()<< gitOutput(QStringList() << "add" << ".");
    qDebug()<< gitOutput(QStringList() << "commit" << "-m" << note.replace(":","-").replace("\"","-"));
}

//void VersionControlSystem::harvestOutput()
//{
//    QString msg = git_run->readAllStandardOutput();
//    if (msg != "") {
//        //qDebug() << "msg: " << msg; //be sure you need to see this, it is expensive
//        _output.append(msg).remove("\"");
//    }
//    QString err = git_run->readAllStandardError();
//    if (err != ""){
//        //qDebug() << "err: " << err; //be sure you need to see this, it is expensive
//        _output.append(err).remove("\"");
//    }
//}

//QStringList VersionControlSystem::output() const
//{
//    QString return_string(_output);
//    return return_string.split("\n");
//}


//QString VersionControlSystem::gitLog(QString since_date)
//{
//    if (since_date.isEmpty()) {
//        return gitOutput(QStringList() << "log" << "--format=\"id:::%H|||note:::%s|||date:::%ci\"");// << "--reverse");
//    } else {
//        QStringList args = QStringList() << "log" << "--format=\"id:::%H|||note:::%s|||date:::%ci\"" << "--since=\"" + since_date + "\"";// << "--reverse";
//        return gitOutput(args);
//    }
//}

//void VersionControlSystem::gitCommitFileList(quint32 index)
//{
//    executeGit(QStringList() << "show" << "--pretty=format:" << "--name-only" << "HEAD~" + index);
//}

//void VersionControlSystem::gitDiffFiles(quint32 newest_index, quint32 oldest_index, QString file)
//{
//    executeGit(QStringList() << "difftool"  << "HEAD~" + newest_index << "HEAD~" + oldest_index << "--" << file /*<< "-y"*/, true);
//}

//QString VersionControlSystem::gitRawDiff(quint32 newest_index, quint32 oldest_index)
//{
//    return gitOutput(QStringList() << "diff" << "HEAD~" + newest_index << "HEAD~" + oldest_index);
//}

QString VersionControlSystem::gitOutput(QStringList args)
{
    qDebug() << _working_path << "  - Capacitor::gitOutput: git " << args;
    if (!QDir::setCurrent(_working_path))
        qDebug() << "ERROR: QDir::setCurrent: " << _working_path;
    git_run = new QProcess(qobject_cast<QObject *>(this));
    git_run->setReadChannel(QProcess::StandardOutput);
    git_run->setWorkingDirectory(_working_path);
    git_run->start("git", args);
    bool ok = git_run->waitForStarted();
    Q_ASSERT(ok);
    ok = git_run->waitForReadyRead();
   // Q_ASSERT(ok);
    ok = git_run->waitForFinished();
    QString output(git_run->readAll());
    git_run->deleteLater();
//    qDebug() << output;
    return output;
}

QByteArray VersionControlSystem::gitFileContents(quint32 index, QString filename)
{
    QFileInfo fi(filename);
    QString data("HEAD~" + QString::number(index) + ":" + fi.fileName());
    _contents.clear();
    _contents = gitOutput(QStringList() << "show" << data).toLocal8Bit();
//    qDebug() << _contents;
    return (!_contents.isEmpty()) ? _contents : "Selected file was not being followed at the time of selected capture.";
}

QString VersionControlSystem::gitStat()
{
    return gitOutput(QStringList() << "log" << "--stat");
}

//QString VersionControlSystem::workingPath() const
//{
//    return _working_path;
//}

//void VersionControlSystem::executeGit(QStringList args, bool detached)
//{
//    qDebug() << "Capacitor::executeGit: git " << args.join(" ");
//    _output.clear();

//    if (!QDir::setCurrent(_working_path))
//        qDebug() << "ERROR: QDir::setCurrent: " << _working_path;
//    git_run = new QProcess(qobject_cast<QObject *>(this));

//    git_run->setReadChannel(QProcess::StandardOutput);

//    connect(git_run, &QProcess::readyRead,
//            this, &VersionControlSystem::harvestOutput);
//    connect(git_run, &QProcess::readyReadStandardError,
//            this, &VersionControlSystem::harvestOutput);
//    connect(git_run, &QProcess::readyReadStandardOutput,
//            this, &VersionControlSystem::harvestOutput);

//    git_run->setWorkingDirectory(_working_path);
//    if (detached) {
//        QProcess::startDetached("git " + args.join(" "));
//    } else {
//        git_run->start("git", args);
//        git_run->waitForReadyRead();
//        git_run->waitForFinished();
//        git_run->deleteLater();
//    }
//}



