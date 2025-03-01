#include "musicabstractdownloadrequest.h"
#include "musicsettingmanager.h"
#include "musicdownloadmanager.h"
#include "musiccoreutils.h"

#include <QSslError>

MusicAbstractDownLoadRequest::MusicAbstractDownLoadRequest(const QString &url, const QString &save, MusicObject::DownloadType type, QObject *parent)
    : MusicAbstractNetwork(parent)
{
    m_url = url;
    m_savePath = save;
    m_downloadType = type;
    m_hasReceived = 0;
    m_currentReceived = 0;

    if(QFile::exists(m_savePath))
    {
        QFile::remove(m_savePath);
    }
    m_file = new QFile(m_savePath, this);

    G_DOWNLOAD_MANAGER_PTR->connectNetworkMultiValue(this);

    m_speedTimer.setInterval(MT_S2MS);
    connect(&m_speedTimer, SIGNAL(timeout()), SLOT(updateDownloadSpeed()));
}

MusicAbstractDownLoadRequest::~MusicAbstractDownLoadRequest()
{
    if(m_speedTimer.isActive())
    {
        m_speedTimer.stop();
    }
    G_DOWNLOAD_MANAGER_PTR->removeNetworkMultiValue(this);
}

void MusicAbstractDownLoadRequest::deleteAll()
{
    MusicAbstractNetwork::deleteAll();
    if(m_file)
    {
        delete m_file;
        m_file = nullptr;
    }
    deleteLater();
}

void MusicAbstractDownLoadRequest::downLoadFinished()
{
    MusicAbstractNetwork::downLoadFinished();
    m_speedTimer.stop();
}

void MusicAbstractDownLoadRequest::replyError(QNetworkReply::NetworkError)
{
    TTK_LOGGER_ERROR("Abnormal network connection");
    Q_EMIT downLoadDataChanged("The file create failed");
    deleteAll();
}

#ifndef QT_NO_SSL
void MusicAbstractDownLoadRequest::sslErrors(QNetworkReply* reply, const QList<QSslError> &errors)
{
    sslErrorsString(reply, errors);
    Q_EMIT downLoadDataChanged("The file create failed");
    deleteAll();
}
#endif

void MusicAbstractDownLoadRequest::downloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    m_currentReceived = bytesReceived;
    m_totalSize = bytesTotal;
}

void MusicAbstractDownLoadRequest::updateDownloadSpeed()
{
    int delta = m_currentReceived - m_hasReceived;
    ///limit speed
    if(G_SETTING_PTR->value(MusicSettingManager::DownloadLimitEnable).toInt() == 0)
    {
        const int limitValue = G_SETTING_PTR->value(MusicSettingManager::DownloadDownloadLimitSize).toInt();
        if(limitValue != 0 && delta > limitValue * MH_KB)
        {
            MusicUtils::Core::sleep(MT_S2MS - limitValue * MH_KB * MT_S2MS / delta);
            delta = limitValue * MH_KB;
        }
    }
    m_hasReceived = m_currentReceived;
}

QString MusicAbstractDownLoadRequest::mapCurrentQueryData() const
{
    switch(m_downloadType)
    {
        case MusicObject::DownloadMusic: return "DownloadMusic";
        case MusicObject::DownloadLrc: return "DownloadLrc";
        case MusicObject::DownloadSmallBackground: return "DownloadSmallBackground";
        case MusicObject::DownloadBigBackground: return "DownloadBigBackground";
        case MusicObject::DownloadVideo: return "DownloadVideo";
        case MusicObject::DownloadOther: return "DownloadOther";
        default: return QString();
    }
}
