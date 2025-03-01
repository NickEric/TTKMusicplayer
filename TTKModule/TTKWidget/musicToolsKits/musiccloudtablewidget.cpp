#include "musiccloudtablewidget.h"
#include "musicitemdelegate.h"
#include "musicconnectionpool.h"
#include "musicnumberutils.h"
#include "musictoastlabel.h"

Q_DECLARE_METATYPE(MusicCloudDataItem)

MusicCloudDownloadTableWidget::MusicCloudDownloadTableWidget(QWidget *parent)
    : MusicAbstractDownloadTableWidget(parent)
{
    G_CONNECTION_PTR->setValue(className(), this);

    setColumnCount(4);
    QHeaderView *headerview = horizontalHeader();
    headerview->resizeSection(0, 10);
    headerview->resizeSection(1, 168);
    headerview->resizeSection(2, 83);
    headerview->resizeSection(3, 50);

    m_type = MusicObject::RecordCloudDownload;
    setItemDelegateForColumn(2, m_delegate);
    setSelectionMode(QAbstractItemView::ExtendedSelection);

    MusicUtils::Widget::setTransparent(this, 0);
    verticalScrollBar()->setStyleSheet(MusicUIObject::MQSSScrollBarStyle03);

    setFixedHeight(0);
}

MusicCloudDownloadTableWidget::~MusicCloudDownloadTableWidget()
{
    G_CONNECTION_PTR->removeValue(className());
}

void MusicCloudDownloadTableWidget::createItem(int index, const MusicSong &record)
{
    QHeaderView *headerview = horizontalHeader();
    QTableWidgetItem *item = new QTableWidgetItem;
    setItem(index, 0, item);

                      item = new QTableWidgetItem;
    item->setToolTip(record.musicName());
    item->setText(MusicUtils::Widget::elidedText(font(), item->toolTip(), Qt::ElideRight, headerview->sectionSize(1) - 20));
#if TTK_QT_VERSION_CHECK(5,13,0)
    item->setForeground(QColor(MusicUIObject::MQSSColor01));
#else
    item->setTextColor(QColor(MusicUIObject::MQSSColor01));
#endif
    item->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    setItem(index, 1, item);

                      item = new QTableWidgetItem;
    item->setData(MUSIC_PROGRESS_ROLE, 100);
    setItem(index, 2, item);

                      item = new QTableWidgetItem(record.musicSizeStr());
#if TTK_QT_VERSION_CHECK(5,13,0)
    item->setForeground(QColor(MusicUIObject::MQSSColor01));
#else
    item->setTextColor(QColor(MusicUIObject::MQSSColor01));
#endif
    item->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
    item->setData(MUSIC_TIME_ROLE, record.musicAddTimeStr());
    setItem(index, 3, item);

    //just fix table widget size hint
    setFixedHeight(totalHeight());
}


MusicCloudUploadTableWidget::MusicCloudUploadTableWidget(QWidget *parent)
    : MusicAbstractDownloadTableWidget(parent)
{
    G_CONNECTION_PTR->setValue(className(), this);

    setColumnCount(3);
    QHeaderView *headerview = horizontalHeader();
    headerview->resizeSection(0, 10);
    headerview->resizeSection(1, 251);
    headerview->resizeSection(2, 50);

    m_type = MusicObject::RecordCloudUpload;
    setSelectionMode(QAbstractItemView::ExtendedSelection);

    MusicUtils::Widget::setTransparent(this, 0);
    verticalScrollBar()->setStyleSheet(MusicUIObject::MQSSScrollBarStyle03);

    setFixedHeight(0);
}

MusicCloudUploadTableWidget::~MusicCloudUploadTableWidget()
{
    G_CONNECTION_PTR->removeValue(className());
}

void MusicCloudUploadTableWidget::uploadFileError(const MusicCloudDataItem &item)
{
    const int count = rowCount() + 1;
    setRowCount(count);

    MusicSong record;
    record.setMusicName(item.m_dataItem.m_name);
    record.setMusicPath(item.m_path);
    record.setMusicSizeStr(MusicUtils::Number::sizeByte2Label(item.m_dataItem.m_size));

    createItem(count - 1, record);
}

void MusicCloudUploadTableWidget::reuploadFile()
{
    if(currentRow() < 0)
    {
        MusicToastLabel::popup(tr("Please select one item first!"));
        return;
    }

    QTableWidgetItem *it = item(currentRow(), 0);
    if(it == nullptr)
    {
        return;
    }

    const QString data(it->data(MUSIC_DATA_ROLE).toString());
    if(!data.isEmpty())
    {
        Q_EMIT reuploadFilesToServer({data});
    }
}

void MusicCloudUploadTableWidget::reuploadFiles()
{
    if(currentRow() < 0)
    {
        MusicToastLabel::popup(tr("Please select one item first!"));
        return;
    }

    QStringList datas;
    for(const int index : multiSelectedIndex())
    {
        QTableWidgetItem *it = item(index, 0);
        if(it == nullptr)
        {
            continue;
        }

        const QString data(it->data(MUSIC_DATA_ROLE).toString());
        if(!data.isEmpty())
        {
            datas << data;
        }
    }

    if(!datas.isEmpty())
    {
        Q_EMIT reuploadFilesToServer(datas);
    }
}

void MusicCloudUploadTableWidget::createItem(int index, const MusicSong &record)
{
    QHeaderView *headerview = horizontalHeader();
    QTableWidgetItem *item = new QTableWidgetItem;
    item->setData(MUSIC_DATA_ROLE, record.musicPath());
    setItem(index, 0, item);

                      item = new QTableWidgetItem;
    item->setToolTip(record.musicName());
    item->setText(MusicUtils::Widget::elidedText(font(), item->toolTip(), Qt::ElideRight, headerview->sectionSize(1) - 20));
#if TTK_QT_VERSION_CHECK(5,13,0)
    item->setForeground(QColor(MusicUIObject::MQSSColor01));
#else
    item->setTextColor(QColor(MusicUIObject::MQSSColor01));
#endif
    item->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    setItem(index, 1, item);

                      item = new QTableWidgetItem(record.musicSizeStr());
#if TTK_QT_VERSION_CHECK(5,13,0)
    item->setForeground(QColor(MusicUIObject::MQSSColor01));
#else
    item->setTextColor(QColor(MusicUIObject::MQSSColor01));
#endif
    item->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
    item->setData(MUSIC_TIME_ROLE, record.musicAddTimeStr());
    setItem(index, 2, item);

    //just fix table widget size hint
    setFixedHeight(totalHeight());
}

void MusicCloudUploadTableWidget::contextMenuEvent(QContextMenuEvent *event)
{
    Q_UNUSED(event);
    QMenu menu(this);
    menu.setStyleSheet(MusicUIObject::MQSSMenuStyle02);

    const bool status = !m_musicSongs->isEmpty();
    menu.addAction(tr("Song Info..."), this, SLOT(musicFileInformation()))->setEnabled(status);
    menu.addAction(QIcon(":/contextMenu/btn_localFile"), tr("Open File Dir"), this, SLOT(musicOpenFileDir()))->setEnabled(status);
    menu.addSeparator();

    menu.addAction(QIcon(":/contextMenu/btn_delete"), tr("Delete"), this, SLOT(setDeleteItemAt()))->setEnabled(status);
    menu.addAction(tr("Delete All"), this, SLOT(setDeleteItemAll()))->setEnabled(status);
    menu.addSeparator();

    menu.addAction(tr("Reupload"), this, SLOT(reuploadFile()))->setEnabled(status);
    menu.addAction(tr("Reupload All"), this, SLOT(reuploadFiles()))->setEnabled(status);
    menu.addSeparator();
    menu.exec(QCursor::pos());
}
