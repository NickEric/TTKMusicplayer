#include "musicfmradiodownloadtextrequest.h"

MusicFMRadioDownLoadTextRequest::MusicFMRadioDownLoadTextRequest(const QString &url, const QString &save, MusicObject::DownloadType  type, QObject *parent)
    : MusicAbstractDownLoadRequest(url, save, type, parent)
{

}

void MusicFMRadioDownLoadTextRequest::startToDownload()
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
            Q_EMIT downLoadDataChanged("The fm radio text file create failed");
            TTK_LOGGER_ERROR(QString("%1 file create failed").arg(className()));
            deleteAll();
        }
    }
}

void MusicFMRadioDownLoadTextRequest::downLoadFinished()
{
    MusicAbstractDownLoadRequest::downLoadFinished();
    if(m_reply && m_file && m_reply->error() == QNetworkReply::NoError)
    {
        QJson::Parser json;
        bool ok;
        const QVariant &data = json.parse(m_reply->readAll(), &ok);
        if(ok)
        {
            QByteArray lrcData;
            QVariantMap value = data.toMap();
            if(value.contains("lyric"))
            {
                lrcData = value["lyric"].toByteArray();
            }

            QTextStream outstream(m_file);
            outstream.setCodec("utf-8");
            outstream << lrcData;
#if TTK_QT_VERSION_CHECK(5,15,0)
            outstream << Qt::endl;
#else
            outstream << endl;
#endif
            m_file->close();
            TTK_LOGGER_INFO(QString("%1 download has finished").arg(className()));
        }
        else
        {
            TTK_LOGGER_ERROR(QString("%1 download file error").arg(className()));
            m_file->remove();
            m_file->close();
        }
    }

    Q_EMIT downLoadDataChanged(QString());
    deleteAll();
}
