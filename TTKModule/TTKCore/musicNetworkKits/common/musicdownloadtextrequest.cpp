#include "musicdownloadtextrequest.h"

MusicDownLoadTextRequest::MusicDownLoadTextRequest(const QString &url, const QString &save, MusicObject::DownloadType type, QObject *parent)
    : MusicAbstractDownLoadRequest(url, save, type, parent)
{

}

void MusicDownLoadTextRequest::startToDownload()
{
    if(m_file && (!m_file->exists() || m_file->size() < 4))
    {
        if(m_file->open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
        {
            m_speedTimer.start();

            QNetworkRequest request;
            request.setUrl(m_url);
            MusicObject::setSslConfiguration(&request);

            m_reply = m_manager.get(request);
            connect(m_reply, SIGNAL(finished()), SLOT(downLoadFinished()));
#if TTK_QT_VERSION_CHECK(5,15,0)
            connect(m_reply, SIGNAL(errorOccurred(QNetworkReply::NetworkError)), SLOT(replyError(QNetworkReply::NetworkError)));
#else
            connect(m_reply, SIGNAL(error(QNetworkReply::NetworkError)), SLOT(replyError(QNetworkReply::NetworkError)));
#endif
            connect(m_reply, SIGNAL(downloadProgress(qint64, qint64)), SLOT(downloadProgress(qint64, qint64)));
        }
        else
        {
            Q_EMIT downLoadDataChanged("The text file create failed");
            TTK_LOGGER_ERROR("The text file create failed");
            deleteAll();
        }
    }
}

void MusicDownLoadTextRequest::downLoadFinished()
{
    MusicAbstractDownLoadRequest::downLoadFinished();
    if(m_reply && m_file && m_reply->error() == QNetworkReply::NoError)
    {
       
        const QByteArray &bytes = m_reply->readAll();
        if(!bytes.isEmpty())
        {
            QTextStream outstream(m_file);
            outstream.setCodec("utf-8");
            outstream << QString(bytes).remove("\r").toUtf8();
#if TTK_QT_VERSION_CHECK(5,15,0)
            outstream << Qt::endl;
#else
            outstream << endl;
#endif
            m_file->close();
            TTK_LOGGER_INFO("Text download has finished");
        }
        else
        {
            TTK_LOGGER_ERROR("Text download file error");
            m_file->remove();
            m_file->close();
        }
    }

    Q_EMIT downLoadDataChanged(mapCurrentQueryData());
    deleteAll();
}
