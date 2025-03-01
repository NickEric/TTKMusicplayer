#include "musickwdownloadimagerequest.h"
#include "musicdownloadsourcerequest.h"
#include "musicdownloaddatarequest.h"

const QString BIG_ART_URL = "NUJnNFVlSHprVzdaMWxMdXRvbEp5a3lldU51Um9GeU5RKzRDWFNER2FHL3pSRE1uK1VNRzVhVk53Y1JBUTlMbnhjeFBvRFMySnpUSldlY21xQjBkWE5GTWVkVXFsa0lNa1RKSnE3VHEwMDFPdVRDbXhUSThhWkM4TFI4RUZqbHFzVFFnQkpOY2hUR2c2YWdzb3U2cjBKSUdMYnpnZktucEJpbDVBTDlzMGF0QVMwcEtLR2JWVnc9PQ==";

MusicKWDownloadImageRequest::MusicKWDownloadImageRequest(const QString &name, const QString &save, QObject *parent)
    : MusicDownloadImageRequest(name, save, parent)
{

}

void MusicKWDownloadImageRequest::startToDownload()
{
    deleteAll();

    MusicDownloadSourceRequest *download = new MusicDownloadSourceRequest(this);
    ///Set search image API
    connect(download, SIGNAL(downLoadRawDataChanged(QByteArray)), SLOT(downLoadFinished(QByteArray)));
    download->startToDownload(MusicUtils::Algorithm::mdII(BIG_ART_URL, false).arg(m_artName));
}

void MusicKWDownloadImageRequest::downLoadFinished(const QByteArray &bytes)
{
    MusicAbstractNetwork::downLoadFinished();
    if(bytes != "NO_PIC")
    {
        QJson::Parser json;
        bool ok;
        const QVariant &data = json.parse(bytes, &ok);
        if(ok)
        {
            QVariantMap dataMap = data.toMap();
            const QVariantList &datas = dataMap["array"].toList();
            for(const QVariant &var : qAsConst(datas))
            {
                dataMap = var.toMap();
                if(m_counter < 5 && !dataMap.isEmpty())
                {
                    const QString &url = dataMap.values().first().toString();
                    MusicDownloadDataRequest *download = new MusicDownloadDataRequest(url, QString("%1%2%3%4").arg(BACKGROUND_DIR_FULL, m_savePath).arg(m_counter++).arg(SKN_FILE), MusicObject::DownloadBigBackground, this);
                    connect(download, SIGNAL(downLoadDataChanged(QString)), SLOT(downLoadFinished()));
                    download->startToDownload();
                }
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
