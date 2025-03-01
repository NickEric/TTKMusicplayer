#include "musicdownloadbatchwidget.h"
#include "ui_musicdownloadbatchwidget.h"
#include "musicsettingmanager.h"
#include "musicdownloadrecordconfigmanager.h"
#include "musicdownloadtagdatarequest.h"

#include <QTimer>

Q_DECLARE_METATYPE(MusicObject::MusicSongAttribute)

MusicDownloadBatchTableItem::MusicDownloadBatchTableItem(QWidget *parent)
    : QWidget(parent)
{
    m_supperClass = parent;
    m_songName = new QLabel(this);
    m_singer = new QLabel(this);
    m_information = new QLabel(this);
    m_information->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    m_qulity = new QComboBox(this);
    MusicUtils::Widget::generateComboBoxFormat(m_qulity, MusicUIObject::MQSSComboBoxStyle02 + MusicUIObject::MQSSItemView01);

    m_songName->setGeometry(0, 0, 190, ITEM_ROW_HEIGHT_S);
    m_singer->setGeometry(180, 0, 120, ITEM_ROW_HEIGHT_S);
    m_qulity->setGeometry(300, 0, 80, ITEM_ROW_HEIGHT_S);
    m_information->setGeometry(380, 0, 150, ITEM_ROW_HEIGHT_S);
    m_queryType = MusicAbstractQueryRequest::MusicQuery;

    connect(m_qulity, SIGNAL(currentIndexChanged(int)), SLOT(currentQualityChanged(int)));
}

MusicDownloadBatchTableItem::~MusicDownloadBatchTableItem()
{
    delete m_songName;
    delete m_singer;
    delete m_information;
    delete m_qulity;
}

void MusicDownloadBatchTableItem::createItem(const MusicObject::MusicSongInformation &info, MusicAbstractQueryRequest::QueryType type)
{
    m_songName->setToolTip(info.m_songName);
    m_songName->setText(MusicUtils::Widget::elidedText(m_songName->font(), m_songName->toolTip(), Qt::ElideRight, m_songName->width() - 10));

    m_singer->setToolTip(info.m_singerName);
    m_singer->setText(MusicUtils::Widget::elidedText(m_singer->font(), m_singer->toolTip(), Qt::ElideRight, m_singer->width() - 10));

    m_queryType = type;
    m_songInfo = info;

    MusicObject::MusicSongAttributes attrs(info.m_songAttrs);
    std::sort(attrs.begin(), attrs.end()); //to find out the min bitrate

    for(const MusicObject::MusicSongAttribute &attr : qAsConst(attrs))
    {
        if((attr.m_bitrate == MB_128 && m_queryType == MusicAbstractQueryRequest::MusicQuery) ||
           (attr.m_bitrate <= MB_250 && m_queryType == MusicAbstractQueryRequest::MovieQuery))       ///sd
        {
            m_qulity->addItem(tr("SD"), QVariant::fromValue<MusicObject::MusicSongAttribute>(attr));
            m_information->setText(QString("%1/%2KBPS/%3").arg(attr.m_size).arg(attr.m_bitrate).arg(attr.m_format.toUpper()));
        }
        else if((attr.m_bitrate == MB_192 && m_queryType == MusicAbstractQueryRequest::MusicQuery) ||
                (attr.m_bitrate == MB_500 && m_queryType == MusicAbstractQueryRequest::MovieQuery))  ///hd
        {
            m_qulity->addItem(tr("HQ"), QVariant::fromValue<MusicObject::MusicSongAttribute>(attr));
            m_information->setText(QString("%1/%2KBPS/%3").arg(attr.m_size).arg(attr.m_bitrate).arg(attr.m_format.toUpper()));
        }
        else if((attr.m_bitrate == MB_320 && m_queryType == MusicAbstractQueryRequest::MusicQuery) ||
                (attr.m_bitrate == MB_750 && m_queryType == MusicAbstractQueryRequest::MovieQuery))  ///sq
        {
            m_qulity->addItem(tr("SQ"), QVariant::fromValue<MusicObject::MusicSongAttribute>(attr));
            m_information->setText(QString("%1/%2KBPS/%3").arg(attr.m_size).arg(attr.m_bitrate).arg(attr.m_format.toUpper()));
        }
        else if((attr.m_bitrate > MB_320 && m_queryType == MusicAbstractQueryRequest::MusicQuery) ||
                (attr.m_bitrate >= MB_1000 && m_queryType == MusicAbstractQueryRequest::MovieQuery)) ///cd
        {
            m_qulity->addItem(tr("CD"), QVariant::fromValue<MusicObject::MusicSongAttribute>(attr));
            m_information->setText(QString("%1/%2KBPS/%3").arg(attr.m_size).arg(attr.m_bitrate).arg(attr.m_format.toUpper()));
        }
        else
        {
            continue;
        }
    }

    m_qulity->setCurrentIndex(DEFAULT_NORMAL_LEVEL);
    m_qulity->setCurrentIndex(0);
}

void MusicDownloadBatchTableItem::startToDownload()
{
    if(!G_NETWORK_PTR->isOnline() || m_qulity->currentIndex() < 0)
    {
        return;
    }

    if(m_queryType == MusicAbstractQueryRequest::MusicQuery)
    {
        startToDownloadMusic();
    }
    else if(m_queryType == MusicAbstractQueryRequest::MovieQuery)
    {
        startToDownloadMovie();
    }
}

void MusicDownloadBatchTableItem::setCurrentQuality(int index)
{
    int bitrate = -1;
    if(m_queryType == MusicAbstractQueryRequest::MusicQuery)
    {
        switch(index)
        {
            case 1: bitrate = MB_128; break;
            case 2: bitrate = MB_192; break;
            case 3: bitrate = MB_320; break;
            case 4: bitrate = MB_1000; break;
            default: break;
        }
    }
    else if(m_queryType == MusicAbstractQueryRequest::MovieQuery)
    {
        switch(index)
        {
            case 1: bitrate = MB_250; break;
            case 2: bitrate = MB_500; break;
            case 3: bitrate = MB_750; break;
            case 4: bitrate = MB_1000; break;
            default: break;
        }
    }

    index = -1;
    for(int i=0; i<m_qulity->count(); ++i)
    {
        const MusicObject::MusicSongAttribute &attr = m_qulity->itemData(i).value<MusicObject::MusicSongAttribute>();
        if(attr.m_bitrate == bitrate)
        {
            index = i;
            break;
        }
    }

    if(index >= 0)
    {
        m_qulity->setCurrentIndex(index);
    }
}

void MusicDownloadBatchTableItem::currentQualityChanged(int index)
{
    if(index < 0)
    {
        return;
    }

    const MusicObject::MusicSongAttribute &attr = m_qulity->itemData(index).value<MusicObject::MusicSongAttribute>();
    if((attr.m_bitrate == MB_128 && m_queryType == MusicAbstractQueryRequest::MusicQuery) ||
       (attr.m_bitrate <= MB_250 && m_queryType == MusicAbstractQueryRequest::MovieQuery))       ///sd
    {
        m_information->setText(QString("%1/%2KBPS/%3").arg(attr.m_size).arg(attr.m_bitrate).arg(attr.m_format.toUpper()));
    }
    else if((attr.m_bitrate == MB_192 && m_queryType == MusicAbstractQueryRequest::MusicQuery) ||
            (attr.m_bitrate == MB_500 && m_queryType == MusicAbstractQueryRequest::MovieQuery))  ///hd
    {
        m_information->setText(QString("%1/%2KBPS/%3").arg(attr.m_size).arg(attr.m_bitrate).arg(attr.m_format.toUpper()));
    }
    else if((attr.m_bitrate == MB_320 && m_queryType == MusicAbstractQueryRequest::MusicQuery) ||
            (attr.m_bitrate == MB_750 && m_queryType == MusicAbstractQueryRequest::MovieQuery))  ///sq
    {
        m_information->setText(QString("%1/%2KBPS/%3").arg(attr.m_size).arg(attr.m_bitrate).arg(attr.m_format.toUpper()));
    }
    else if((attr.m_bitrate > MB_320 && m_queryType == MusicAbstractQueryRequest::MusicQuery) ||
            (attr.m_bitrate >= MB_1000 && m_queryType == MusicAbstractQueryRequest::MovieQuery)) ///cd
    {
        m_information->setText(QString("%1/%2KBPS/%3").arg(attr.m_size).arg(attr.m_bitrate).arg(attr.m_format.toUpper()));
    }
}

void MusicDownloadBatchTableItem::startToDownloadMusic()
{
    const MusicObject::MusicSongAttribute &attr = m_qulity->itemData(m_qulity->currentIndex()).value<MusicObject::MusicSongAttribute>();
    QString musicSong = m_singer->toolTip() + " - " + m_songName->toolTip();
    const QString &downloadPrefix = G_SETTING_PTR->value(MusicSettingManager::DownloadMusicDirPath).toString();
    QString downloadName = QString("%1%2.%3").arg(downloadPrefix, musicSong, attr.m_format);

    MusicSongs records;
    MusicDownloadRecordConfigManager down(MusicObject::RecordNormalDownload, this);
    if(!down.readConfig())
    {
        return;
    }

    down.readDownloadData(records);
    MusicSong record;
    record.setMusicName(musicSong);
    record.setMusicPath(QFileInfo(downloadName).absoluteFilePath());
    record.setMusicSizeStr(attr.m_size);
    record.setMusicAddTimeStr("-1");
    records << record;
    down.writeDownloadData(records);
    //
    if(QFile::exists(downloadName))
    {
        for(int i=1; i<99; ++i)
        {
            if(!QFile::exists(downloadName))
            {
                break;
            }
            if(i != 1)
            {
                musicSong.chop(3);
            }
            musicSong += QString("(%1)").arg(i);
            downloadName = QString("%1%2.%3").arg(downloadPrefix, musicSong, attr.m_format);
        }
    }
    //
    MusicDownloadTagDataRequest *downSong = new MusicDownloadTagDataRequest(attr.m_url, downloadName, MusicObject::DownloadMusic, this);
    downSong->setRecordType(MusicObject::RecordNormalDownload);
    connect(downSong, SIGNAL(downLoadDataChanged(QString)), m_supperClass, SLOT(dataDownloadFinished()));

    MusicSongMeta meta;
    meta.setComment(m_songInfo.m_smallPicUrl);
    meta.setTitle(m_songInfo.m_songName);
    meta.setArtist(m_songInfo.m_singerName);
    meta.setAlbum(m_songInfo.m_albumName);
    meta.setTrackNum(m_songInfo.m_trackNumber);
    meta.setYear(m_songInfo.m_year);

    downSong->setSongMeta(meta);
    downSong->startToDownload();
}

void MusicDownloadBatchTableItem::startToDownloadMovie()
{
    const MusicObject::MusicSongAttribute &attr = m_qulity->itemData(m_qulity->currentIndex()).value<MusicObject::MusicSongAttribute>();
    const QString &downloadPrefix = MOVIE_DIR_FULL;
    QString musicSong = m_singer->toolTip() + " - " + m_songName->toolTip();
    //
    QString downloadName = QString("%1%2.%3").arg(downloadPrefix, musicSong, attr.m_format);
    if(QFile::exists(downloadName))
    {
        for(int i=1; i<99; ++i)
        {
            if(!QFile::exists(downloadName))
            {
                break;
            }
            if(i != 1)
            {
                musicSong.chop(3);
            }
            musicSong += QString("(%1)").arg(i);
            downloadName = QString("%1%2.%3").arg(downloadPrefix, musicSong, attr.m_format);
        }
    }
    //
    MusicDownloadDataRequest *download = new MusicDownloadDataRequest(attr.m_url, downloadName, MusicObject::DownloadVideo, this);
    download->startToDownload();
}



MusicDownloadBatchTableWidget::MusicDownloadBatchTableWidget(QWidget *parent)
    : MusicAbstractTableWidget(parent)
{
    m_supperClass = nullptr;
    m_downloadOffset = 0;

    setColumnCount(1);
    QHeaderView *headerview = horizontalHeader();
    headerview->resizeSection(0, 530);

    MusicUtils::Widget::setTransparent(this, 255);
    verticalScrollBar()->setStyleSheet(MusicUIObject::MQSSScrollBarStyle01);
    setStyleSheet(styleSheet() + MusicUIObject::MQSSTableWidgetStyle02);
}

MusicDownloadBatchTableWidget::~MusicDownloadBatchTableWidget()
{
    clearAllItems();
}

void MusicDownloadBatchTableWidget::setParentClass(QWidget *parent)
{
    m_supperClass = parent;
}

void MusicDownloadBatchTableWidget::clearAllItems()
{
    m_downloadOffset = 0;
    qDeleteAll(m_items);
    m_items.clear();
    MusicAbstractTableWidget::clear();
    setColumnCount(1);
}

void MusicDownloadBatchTableWidget::createItem(const MusicObject::MusicSongInformation &info, MusicAbstractQueryRequest::QueryType type)
{
    const int index = rowCount();
    setRowCount(index + 1);
    setRowHeight(index, ITEM_ROW_HEIGHT_S);

    QTableWidgetItem *it = new QTableWidgetItem;
    setItem(index, 0,  it);

    MusicDownloadBatchTableItem *item = new MusicDownloadBatchTableItem(this);
    item->createItem(info, type);
    m_items << item;
    setCellWidget(index, 0, item);
}

void MusicDownloadBatchTableWidget::startToDownload()
{
    for(MusicDownloadBatchTableItem *item : qAsConst(m_items))
    {
        item->startToDownload();
    }
}

void MusicDownloadBatchTableWidget::itemCellClicked(int row, int column)
{
    Q_UNUSED(row);
    Q_UNUSED(column);
}

void MusicDownloadBatchTableWidget::dataDownloadFinished()
{
    ++m_downloadOffset;
    if(m_downloadOffset >= rowCount())
    {
        QTimer::singleShot(MT_S2MS, m_supperClass, SLOT(close()));
    }
}

void MusicDownloadBatchTableWidget::currentQualityChanged(int index)
{
    for(MusicDownloadBatchTableItem *item : qAsConst(m_items))
    {
        ///Remove first null item object
        item->setCurrentQuality(index);
    }
}



MusicDownloadBatchWidget::MusicDownloadBatchWidget(QWidget *parent)
    : MusicAbstractMoveWidget(parent),
      m_ui(new Ui::MusicDownloadBatchWidget)
{
    m_ui->setupUi(this);
    setFixedSize(size());
    setAttribute(Qt::WA_DeleteOnClose);

    m_ui->topTitleCloseButton->setIcon(QIcon(":/functions/btn_close_hover"));
    m_ui->topTitleCloseButton->setStyleSheet(MusicUIObject::MQSSToolButtonStyle04);
    m_ui->topTitleCloseButton->setCursor(QCursor(Qt::PointingHandCursor));
    m_ui->topTitleCloseButton->setToolTip(tr("Close"));
    connect(m_ui->topTitleCloseButton, SIGNAL(clicked()), SLOT(close()));

    MusicUtils::Widget::generateComboBoxFormat(m_ui->qualityBox, MusicUIObject::MQSSComboBoxStyle02 + MusicUIObject::MQSSItemView01);
    m_ui->qualityBox->addItems({tr("Null"), tr("SD"), tr("HQ"), tr("SQ"), tr("CD")});
    connect(m_ui->qualityBox, SIGNAL(currentIndexChanged(int)), m_ui->tableWidget, SLOT(currentQualityChanged(int)));

    m_ui->qualityBox->setCurrentIndex(0);

    m_ui->tableWidget->setParentClass(this);
    m_ui->downloadButton->setStyleSheet(MusicUIObject::MQSSPushButtonStyle06);
#ifdef Q_OS_UNIX
    m_ui->downloadButton->setFocusPolicy(Qt::NoFocus);
#endif

    connect(m_ui->downloadButton, SIGNAL(clicked()), SLOT(startToDownload()));
}

MusicDownloadBatchWidget::~MusicDownloadBatchWidget()
{
    G_SINGLE_MANAGER_PTR->removeObject(className());
    delete m_ui;
}

void MusicDownloadBatchWidget::setSongName(const MusicObject::MusicSongInformations &infos, MusicAbstractQueryRequest::QueryType type)
{
    for(const MusicObject::MusicSongInformation &info : qAsConst(infos))
    {
        m_ui->tableWidget->createItem(info, type);
    }
    m_ui->songCountLabel->setText(tr("All Songs Count %1").arg(infos.count()));
}

void MusicDownloadBatchWidget::show()
{
    setBackgroundPixmap(m_ui->background, size());
    return MusicAbstractMoveWidget::show();
}

void MusicDownloadBatchWidget::startToDownload()
{
    m_ui->tableWidget->startToDownload();
    hide();
}
