#include "musickwqueryrequest.h"

MusicKWMusicInfoConfigManager::MusicKWMusicInfoConfigManager(QObject *parent)
    : MusicAbstractXml(parent)
{

}

void MusicKWMusicInfoConfigManager::readMusicInfoConfig(MusicObject::MusicSongInformation *info)
{
    info->m_singerName = readXmlTextByTagName("artist");
    info->m_songName = readXmlTextByTagName("name");
    info->m_songId = readXmlTextByTagName("music_id");
    info->m_artistId = readXmlTextByTagName("albid");
    info->m_albumId = readXmlTextByTagName("artid");
    info->m_albumName = readXmlTextByTagName("special");

    const QString &mp3Url = readXmlTextByTagName("mp3dl");
    if(!mp3Url.isEmpty())
    {
        QString v = readXmlTextByTagName("mp3path");
        if(!v.isEmpty())
        {
            MusicObject::MusicSongAttribute attr;
            attr.m_bitrate = MB_128;
            attr.m_format = MP3_FILE_PREFIX;
            attr.m_size = TTK_DEFAULT_STR;
            attr.m_url = QString("%1%2/resource/%3").arg(HTTP_PREFIX, mp3Url, v);
            info->m_songAttrs.append(attr);
        }

        v = readXmlTextByTagName("path");
        if(!v.isEmpty())
        {
            MusicObject::MusicSongAttribute attr;
            attr.m_bitrate = MB_96;
            attr.m_format = WMA_FILE_PREFIX;
            attr.m_size = TTK_DEFAULT_STR;
            attr.m_url = QString("%1%2/resource/%3").arg(HTTP_PREFIX, mp3Url, v);
            info->m_songAttrs.append(attr);
        }
    }

    const QString &aacUrl = readXmlTextByTagName("aacdl");
    if(!aacUrl.isEmpty())
    {
        const QString &v = readXmlTextByTagName("aacpath");
        if(!v.isEmpty())
        {
            MusicObject::MusicSongAttribute attr;
            attr.m_bitrate = MB_32;
            attr.m_format = AAC_FILE_PREFIX;
            attr.m_size = TTK_DEFAULT_STR;
            attr.m_url = QString("%1%2/resource/%3").arg(HTTP_PREFIX, aacUrl, v);
            info->m_songAttrs.append(attr);
        }
    }
}



MusicKWQueryRequest::MusicKWQueryRequest(QObject *parent)
    : MusicAbstractQueryRequest(parent)
{
    m_pageSize = 40;
    m_queryServer = QUERY_KW_INTERFACE;
}

void MusicKWQueryRequest::startToSearch(QueryType type, const QString &text)
{
    TTK_LOGGER_INFO(QString("%1 startToSearch %2").arg(className(), text));

    m_currentType = type;
    m_queryText = text.trimmed();
    MusicAbstractQueryRequest::downLoadFinished();

    startToPage(0);
}

void MusicKWQueryRequest::startToPage(int offset)
{
    TTK_LOGGER_INFO(QString("%1 startToPage %2").arg(className()).arg(offset));

    deleteAll();
    m_totalSize = 0;
    m_pageIndex = offset;

    QNetworkRequest request;
    request.setUrl(MusicUtils::Algorithm::mdII(KW_SONG_SEARCH_URL, false).arg(m_queryText).arg(offset).arg(m_pageSize));
    MusicKWInterface::makeRequestRawHeader(&request);

    m_reply = m_manager.get(request);
    connect(m_reply, SIGNAL(finished()), SLOT(downLoadFinished()));
#if TTK_QT_VERSION_CHECK(5,15,0)
    connect(m_reply, SIGNAL(errorOccurred(QNetworkReply::NetworkError)), SLOT(replyError(QNetworkReply::NetworkError)));
#else
    connect(m_reply, SIGNAL(error(QNetworkReply::NetworkError)), SLOT(replyError(QNetworkReply::NetworkError)));
#endif
}

void MusicKWQueryRequest::startToSingleSearch(const QString &text)
{
    TTK_LOGGER_INFO(QString("%1 startToSingleSearch %2").arg(className(), text));

    deleteAll();

    QNetworkRequest request;
    request.setUrl(MusicUtils::Algorithm::mdII(KW_SONG_INFO_URL, false).arg(text));
    MusicKWInterface::makeRequestRawHeader(&request);

    QNetworkReply *reply = m_manager.get(request);
    connect(reply, SIGNAL(finished()), SLOT(singleDownLoadFinished()));
#if TTK_QT_VERSION_CHECK(5,15,0)
    connect(reply, SIGNAL(errorOccurred(QNetworkReply::NetworkError)), SLOT(replyError(QNetworkReply::NetworkError)));
#else
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), SLOT(replyError(QNetworkReply::NetworkError)));
#endif
}

void MusicKWQueryRequest::downLoadFinished()
{
    TTK_LOGGER_INFO(QString("%1 downLoadFinished").arg(className()));

    MusicPageQueryRequest::downLoadFinished();
    if(m_reply && m_reply->error() == QNetworkReply::NoError)
    {
        QJson::Parser json;
        bool ok;
        const QVariant &data = json.parse(m_reply->readAll().replace("'", "\""), &ok);
        if(ok)
        {
            QVariantMap value = data.toMap();
            if(value.contains("abslist"))
            {
                m_totalSize = value["TOTAL"].toInt();
                const QVariantList &datas = value["abslist"].toList();
                for(const QVariant &var : qAsConst(datas))
                {
                    if(var.isNull())
                    {
                        continue;
                    }

                    value = var.toMap();
                    TTK_NETWORK_QUERY_CHECK();

                    MusicObject::MusicSongInformation musicInfo;
                    musicInfo.m_singerName = MusicUtils::String::charactersReplaced(value["ARTIST"].toString());
                    musicInfo.m_songName = MusicUtils::String::charactersReplaced(value["SONGNAME"].toString());
                    musicInfo.m_duration = MusicTime::msecTime2LabelJustified(value["DURATION"].toInt() * 1000);

                    musicInfo.m_songId = value["MUSICRID"].toString().replace("MUSIC_", "");
                    musicInfo.m_artistId = value["ARTISTID"].toString();
                    musicInfo.m_albumId = value["ALBUMID"].toString();

                    musicInfo.m_year = value["RELEASEDATE"].toString();
                    musicInfo.m_discNumber = "1";
                    musicInfo.m_trackNumber = "0";

                    if(!m_querySimplify)
                    {
                        TTK_NETWORK_QUERY_CHECK();
                        readFromMusicSongPicture(&musicInfo);
                        TTK_NETWORK_QUERY_CHECK();
                        musicInfo.m_lrcUrl = MusicUtils::Algorithm::mdII(KW_SONG_LRC_URL, false).arg(musicInfo.m_songId);
                        musicInfo.m_albumName = MusicUtils::String::charactersReplaced(value["ALBUM"].toString());
                        readFromMusicSongAttribute(&musicInfo, value["FORMATS"].toString(), m_queryQuality, m_queryAllRecords);
                        TTK_NETWORK_QUERY_CHECK();

                        if(musicInfo.m_songAttrs.isEmpty())
                        {
                            continue;
                        }
                        //
                        if(!findUrlFileSize(&musicInfo.m_songAttrs)) return;
                        //
                        MusicSearchedItem item;
                        item.m_songName = musicInfo.m_songName;
                        item.m_singerName = musicInfo.m_singerName;
                        item.m_albumName = musicInfo.m_albumName;
                        item.m_duration = musicInfo.m_duration;
                        item.m_type = mapQueryServerString();
                        Q_EMIT createSearchedItem(item);
                    }
                    m_musicSongInfos << musicInfo;
                }
            }
        }
    }

    Q_EMIT downLoadDataChanged(QString());
    deleteAll();
}

void MusicKWQueryRequest::singleDownLoadFinished()
{
    TTK_LOGGER_INFO(QString("%1 singleDownLoadFinished").arg(className()));

    MusicAbstractQueryRequest::downLoadFinished();
    QNetworkReply *reply = TTKObject_cast(QNetworkReply*, QObject::sender());
    if(reply && reply->error() == QNetworkReply::NoError)
    {
        QByteArray data = reply->readAll();
        data.insert(0, "<?xml version=\"1.0\" encoding=\"utf-8\"?>\r\n");
        data.replace("&", "%26");

        MusicObject::MusicSongInformation musicInfo;
        MusicKWMusicInfoConfigManager xml;
        if(xml.fromByteArray(data))
        {
            xml.readMusicInfoConfig(&musicInfo);

            musicInfo.m_year = QString();
            musicInfo.m_discNumber = "1";
            musicInfo.m_trackNumber = "0";

            TTK_NETWORK_QUERY_CHECK();
            readFromMusicSongPicture(&musicInfo);
            TTK_NETWORK_QUERY_CHECK();
            musicInfo.m_lrcUrl = MusicUtils::Algorithm::mdII(KW_SONG_LRC_URL, false).arg(musicInfo.m_songId);
            //
            if(!findUrlFileSize(&musicInfo.m_songAttrs)) return;
            //
            if(!musicInfo.m_songAttrs.isEmpty())
            {
                MusicSearchedItem item;
                item.m_songName = musicInfo.m_songName;
                item.m_singerName = musicInfo.m_singerName;
                item.m_duration = musicInfo.m_duration;
                item.m_type = mapQueryServerString();
                Q_EMIT createSearchedItem(item);
                m_musicSongInfos << musicInfo;
            }
        }
    }

    Q_EMIT downLoadDataChanged(QString());
    deleteAll();
}
