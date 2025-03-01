#include "musiclocalsongsmanagerthread.h"
#include "musicformats.h"
#include "musicfileutils.h"

MusicLocalSongsManagerThread::MusicLocalSongsManagerThread(QObject *parent)
    : MusicAbstractThread(parent)
{

}

void MusicLocalSongsManagerThread::setFindFilePath(const QString &path)
{
    setFindFilePath(QStringList(path));
}

void MusicLocalSongsManagerThread::setFindFilePath(const QStringList &path)
{
    m_path = path;
}

void MusicLocalSongsManagerThread::run()
{
    MusicAbstractThread::run();

    QFileInfoList list;
    for(const QString &path : qAsConst(m_path))
    {
        if(m_running)
        {
            list << MusicUtils::File::fileListByDir(path, MusicFormats::supportMusicInputFilterFormats(), true);
        }
    }
    ///The name and path search ended when sending the corresponding
    Q_EMIT setSongNamePath(list);
}
