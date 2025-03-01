#include "musicqqdownloadimagerequest.h"
#include "musicdownloadsourcerequest.h"
#include "musicdownloaddatarequest.h"
#include "musicqqqueryinterface.h"

const QString BIG_ART_URL = "dGJmTlZOK1QvMDJENUxjMDk5UVhBWHVCb001eWtnQ1hKSnhsRWxLczNvRm9FV0kwbHhocTk4aml5SCs1Ym5mQU44SU05c1VZYVFzR2hLTEpGQ0hCNmM1ZUlZVnhnMm92QXNGMFN3PT0=";

MusicQQDownloadImageRequest::MusicQQDownloadImageRequest(const QString &name, const QString &save, QObject *parent)
    : MusicDownloadImageRequest(name, save, parent)
{

}

void MusicQQDownloadImageRequest::startToDownload()
{
    TTK_LOGGER_INFO(QString("%1 startToDownload").arg(className()));

    deleteAll();

    QNetworkRequest request;
    request.setUrl(MusicUtils::Algorithm::mdII(QQ_SONG_SEARCH_URL, false).arg(m_artName).arg(0).arg(50));
    MusicQQInterface::makeRequestRawHeader(&request);

    m_reply = m_manager.get(request);
    connect(m_reply, SIGNAL(finished()), SLOT(downLoadDataFinished()));
#if TTK_QT_VERSION_CHECK(5,15,0)
    connect(m_reply, SIGNAL(errorOccurred(QNetworkReply::NetworkError)), SLOT(replyError(QNetworkReply::NetworkError)));
#else
    connect(m_reply, SIGNAL(error(QNetworkReply::NetworkError)), SLOT(replyError(QNetworkReply::NetworkError)));
#endif
}

void MusicQQDownloadImageRequest::downLoadDataFinished()
{
    TTK_LOGGER_INFO(QString("%1 downLoadDataFinished").arg(className()));

    MusicAbstractNetwork::downLoadFinished();

    QString songId;
    if(m_reply && m_reply->error() == QNetworkReply::NoError)
    {
        QJson::Parser json;
        bool ok;
        const QVariant &data = json.parse(m_reply->readAll(), &ok);
        if(ok)
        {
            QVariantMap value = data.toMap();
            if(value.contains("data"))
            {
                value = value["data"].toMap();
                value = value["song"].toMap();
                const QVariantList &datas = value["list"].toList();
                for(const QVariant &var : qAsConst(datas))
                {
                    if(var.isNull())
                    {
                        continue;
                    }

                    value = var.toMap();
                    TTK_NETWORK_QUERY_CHECK();

                    songId = value["songid"].toString();
                    break;
                }
            }
        }
    }

    downLoadUrl(songId);
}

void MusicQQDownloadImageRequest::downLoadUrlFinished()
{
    TTK_LOGGER_INFO(QString("%1 downLoadUrlFinished").arg(className()));

    MusicAbstractNetwork::downLoadFinished();
    if(m_reply && m_reply->error() == QNetworkReply::NoError)
    {
        QStringList datas;
        const QString text(m_reply->readAll());
        QRegExp regx(QString("<url>([^<]+)</url>"));

        int pos = text.indexOf(regx);
        while(pos != -1)
        {
            datas << regx.cap(0).remove("<url>").remove("</url>").trimmed();
            pos += regx.matchedLength();
            pos = regx.indexIn(text, pos);
        }

        for(const QString &url : qAsConst(datas))
        {
            if(m_counter < 5)
            {
                MusicDownloadDataRequest *download = new MusicDownloadDataRequest(url, QString("%1%2%3%4").arg(BACKGROUND_DIR_FULL, m_savePath).arg(m_counter++).arg(SKN_FILE), MusicObject::DownloadBigBackground, this);
                connect(download, SIGNAL(downLoadDataChanged(QString)), SLOT(downLoadFinished()));
                download->startToDownload();
            }
        }
    }

    emit downLoadDataChanged(QString::number(m_counter));
    if(m_counter == 0)
    {
        deleteAll();
        deleteLater();
    }
}

void MusicQQDownloadImageRequest::downLoadUrl(const QString &id)
{
    TTK_LOGGER_INFO(QString("%1 downLoadUrl %2").arg(className(), id));

    deleteAll();

    QNetworkRequest request;
    request.setUrl(MusicUtils::Algorithm::mdII(BIG_ART_URL, false).arg(id));
    MusicQQInterface::makeRequestRawHeader(&request);

    m_reply = m_manager.get(request);
    connect(m_reply, SIGNAL(finished()), SLOT(downLoadUrlFinished()));
#if TTK_QT_VERSION_CHECK(5,15,0)
    connect(m_reply, SIGNAL(errorOccurred(QNetworkReply::NetworkError)), SLOT(replyError(QNetworkReply::NetworkError)));
#else
    connect(m_reply, SIGNAL(error(QNetworkReply::NetworkError)), SLOT(replyError(QNetworkReply::NetworkError)));
#endif
}
