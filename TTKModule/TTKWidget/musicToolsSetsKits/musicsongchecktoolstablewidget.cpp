#include "musicsongchecktoolstablewidget.h"
#include "musicitemdelegate.h"
#include "musicnumberutils.h"
#include "musicconnectionpool.h"
#include "musicsongssummariziedwidget.h"

MusicSongCheckToolsRenameTableWidget::MusicSongCheckToolsRenameTableWidget(QWidget *parent)
    : MusicFillItemTableWidget(parent)
{
    setAttribute(Qt::WA_TranslucentBackground, false);
    setSelectionMode(QAbstractItemView::ExtendedSelection);

    setColumnCount(4);
    QHeaderView *headerview = horizontalHeader();
    headerview->resizeSection(0, 30);
    headerview->resizeSection(1, 290);
    headerview->resizeSection(2, 290);
#ifdef Q_OS_UNIX
    headerview->resizeSection(3, 51);
#else
    headerview->resizeSection(3, 54);
#endif

    setItemDelegateForColumn(3, new MusicPushButtonDelegate(this));
}

void MusicSongCheckToolsRenameTableWidget::createAllItems(const MusicSongCheckToolsRenames &items)
{
    setRowCount(items.count());
    QHeaderView *headerview = horizontalHeader();
    for(int i=0; i<items.count(); ++i)
    {
        const MusicSongCheckToolsRename &song = items[i];
        QTableWidgetItem *item = new QTableWidgetItem;
        item->setData(MUSIC_CHECK_ROLE, Qt::Unchecked);
        setItem(i, 0, item);

                          item = new QTableWidgetItem;
        item->setToolTip(song.m_locaName);
        item->setText(MusicUtils::Widget::elidedText(font(), item->toolTip(), Qt::ElideRight, headerview->sectionSize(1) - 10));
        item->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        setItem(i, 1, item);

                item = new QTableWidgetItem;
        item->setToolTip(song.m_recommendName);
        item->setText(MusicUtils::Widget::elidedText(font(), item->toolTip(), Qt::ElideRight, headerview->sectionSize(2) - 10));
        item->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        setItem(i, 2, item);

                item = new QTableWidgetItem;
        item->setData(MUSIC_TEXT_ROLE, tr("Delete"));
        setItem(i, 3, item);
    }
}

void MusicSongCheckToolsRenameTableWidget::itemCellClicked(int row, int column)
{
    MusicFillItemTableWidget::itemCellClicked(row, column);
    if(column == 3)
    {
        deleteCurrentRow();
    }
}

void MusicSongCheckToolsRenameTableWidget::selectedAllItems(bool check)
{
    for(int i=0; i<rowCount(); ++i)
    {
        item(i, 0)->setData(MUSIC_CHECK_ROLE, check ? Qt::Checked : Qt::Unchecked);
    }

    if(!check)
    {
        clearSelection();
        setCurrentIndex(QModelIndex());
    }
    else
    {
        selectAll();
    }
}

void MusicSongCheckToolsRenameTableWidget::deleteCurrentRow()
{
    if(rowCount() == 0 || currentRow() < 0)
    {
        return;
    }
    removeRow(currentRow());
}



MusicSongCheckToolsDuplicateTableWidget::MusicSongCheckToolsDuplicateTableWidget(QWidget *parent)
    : MusicFillItemTableWidget(parent)
{
    setAttribute(Qt::WA_TranslucentBackground, false);
    setSelectionMode(QAbstractItemView::ExtendedSelection);

    setColumnCount(7);
    QHeaderView *headerview = horizontalHeader();
    headerview->resizeSection(0, 30);
    headerview->resizeSection(1, 290);
    headerview->resizeSection(2, 65);
    headerview->resizeSection(3, 65);
    headerview->resizeSection(4, 80);
    headerview->resizeSection(5, 80);
#ifdef Q_OS_UNIX
    headerview->resizeSection(6, 51);
#else
    headerview->resizeSection(6, 54);
#endif

    MusicPushButtonDelegate *delegate = new MusicPushButtonDelegate(this);
    setItemDelegateForColumn(5, delegate);
    setItemDelegateForColumn(6, delegate);

    G_CONNECTION_PTR->setValue(className(), this);
    G_CONNECTION_PTR->poolConnect(className(), MusicSongsSummariziedWidget::className());
}

MusicSongCheckToolsDuplicateTableWidget::~MusicSongCheckToolsDuplicateTableWidget()
{
    G_CONNECTION_PTR->removeValue(className());
}

void MusicSongCheckToolsDuplicateTableWidget::createAllItems(const MusicSongCheckToolsDuplicates &songs)
{
    setRowCount(songs.count());
    QHeaderView *headerview = horizontalHeader();
    for(int i=0; i<songs.count(); ++i)
    {
        const MusicSongCheckToolsDuplicate &song = songs[i];
        QTableWidgetItem *item = new QTableWidgetItem;
        item->setData(MUSIC_CHECK_ROLE, Qt::Unchecked);
        setItem(i, 0, item);

                          item = new QTableWidgetItem;
        item->setToolTip(song.m_song.musicName());
        item->setText(MusicUtils::Widget::elidedText(font(), item->toolTip(), Qt::ElideRight, headerview->sectionSize(1) - 45));
        item->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        setItem(i, 1, item);

                item = new QTableWidgetItem;
        item->setText(song.m_song.musicPlayTime());
        item->setTextAlignment(Qt::AlignCenter);
        setItem(i, 2, item);

                item = new QTableWidgetItem;
        item->setText(song.m_song.musicSizeStr());
        item->setTextAlignment(Qt::AlignCenter);
        setItem(i, 3, item);

                item = new QTableWidgetItem;
        item->setText(song.m_bitrate);
        item->setTextAlignment(Qt::AlignCenter);
        setItem(i, 4, item);

                item = new QTableWidgetItem;
        item->setData(MUSIC_TEXT_ROLE, tr("Play"));
        item->setData(MUSIC_DATA_ROLE, song.m_song.musicPath());
        setItem(i, 5, item);

                item = new QTableWidgetItem;
        item->setData(MUSIC_TEXT_ROLE, tr("Delete"));
        setItem(i, 6, item);
    }
}

void MusicSongCheckToolsDuplicateTableWidget::itemCellClicked(int row, int column)
{
    MusicFillItemTableWidget::itemCellClicked(row, column);
    switch(column)
    {
        case 5: musicPlay(); break;
        case 6: deleteCurrentRow(); break;
        default: break;
    }
}

void MusicSongCheckToolsDuplicateTableWidget::selectedAllItems(bool check)
{
    for(int i=0; i<rowCount(); ++i)
    {
        item(i, 0)->setData(MUSIC_CHECK_ROLE, check ? Qt::Checked : Qt::Unchecked);
    }

    if(!check)
    {
        clearSelection();
        setCurrentIndex(QModelIndex());
    }
    else
    {
        selectAll();
    }
}

void MusicSongCheckToolsDuplicateTableWidget::musicPlay()
{
    if(rowCount() == 0 || currentRow() < 0)
    {
        return;
    }

    const QTableWidgetItem *it = item(currentRow(), 5);
    if(it)
    {
        const QString &path = it->data(MUSIC_DATA_ROLE).toString();
        Q_EMIT addSongToPlaylist(QStringList(QFile::exists(path) ? path : QString()));
    }
}

void MusicSongCheckToolsDuplicateTableWidget::deleteCurrentRow()
{
    if(rowCount() == 0 || currentRow() < 0)
    {
        return;
    }
    removeRow(currentRow());
}



MusicSongCheckToolsQualityTableWidget::MusicSongCheckToolsQualityTableWidget(QWidget *parent)
    : MusicFillItemTableWidget(parent)
{
    setAttribute(Qt::WA_TranslucentBackground, false);
    setSelectionMode(QAbstractItemView::ExtendedSelection);

    setColumnCount(8);
    QHeaderView *headerview = horizontalHeader();
    headerview->resizeSection(0, 30);
    headerview->resizeSection(1, 220);
    headerview->resizeSection(2, 65);
    headerview->resizeSection(3, 65);
    headerview->resizeSection(4, 80);
    headerview->resizeSection(5, 70);
    headerview->resizeSection(6, 80);
#ifdef Q_OS_UNIX
    headerview->resizeSection(7, 51);
#else
    headerview->resizeSection(7, 54);
#endif

    MusicPushButtonDelegate *delegate = new MusicPushButtonDelegate(this);
    setItemDelegateForColumn(6, delegate);
    setItemDelegateForColumn(7, delegate);

    G_CONNECTION_PTR->setValue(className(), this);
    G_CONNECTION_PTR->poolConnect(className(), MusicSongsSummariziedWidget::className());
}

MusicSongCheckToolsQualityTableWidget::~MusicSongCheckToolsQualityTableWidget()
{
    G_CONNECTION_PTR->removeValue(className());
}

void MusicSongCheckToolsQualityTableWidget::createAllItems(const MusicSongCheckToolsQualitys &songs)
{
    setRowCount(songs.count());
    QHeaderView *headerview = horizontalHeader();
    for(int i=0; i<songs.count(); ++i)
    {
        const MusicSongCheckToolsQuality &song = songs[i];
        QTableWidgetItem *item = new QTableWidgetItem;
        item->setData(MUSIC_CHECK_ROLE, Qt::Unchecked);
        setItem(i, 0, item);

                          item = new QTableWidgetItem;
        item->setToolTip(song.m_song.musicName());
        item->setText(MusicUtils::Widget::elidedText(font(), item->toolTip(), Qt::ElideRight, headerview->sectionSize(1) - 10));
        item->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        setItem(i, 1, item);

                item = new QTableWidgetItem;
        item->setText(song.m_song.musicPlayTime());
        item->setTextAlignment(Qt::AlignCenter);
        setItem(i, 2, item);

                item = new QTableWidgetItem;
        item->setText(song.m_song.musicSizeStr());
        item->setTextAlignment(Qt::AlignCenter);
        setItem(i, 3, item);

                item = new QTableWidgetItem;
        item->setText(song.m_bitrate);
        item->setTextAlignment(Qt::AlignCenter);
        setItem(i, 4, item);

                item = new QTableWidgetItem;
        QColor color;
        QString bitrate;
        MusicUtils::Number::transfromBitrateToQuality(MusicUtils::Number::transfromBitrateToLevel(song.m_bitrate), bitrate, color);
        item->setText(bitrate);
        item->setTextAlignment(Qt::AlignCenter);
#if TTK_QT_VERSION_CHECK(5,13,0)
        item->setForeground(color);
#else
        item->setTextColor(color);
#endif
        setItem(i, 5, item);

                item = new QTableWidgetItem;
        item->setData(MUSIC_TEXT_ROLE, tr("Play"));
        item->setData(MUSIC_DATA_ROLE, song.m_song.musicPath());
        setItem(i, 6, item);

                item = new QTableWidgetItem;
        item->setData(MUSIC_TEXT_ROLE, tr("Delete"));
        setItem(i, 7, item);
    }
}

void MusicSongCheckToolsQualityTableWidget::itemCellClicked(int row, int column)
{
    MusicFillItemTableWidget::itemCellClicked(row, column);
    switch(column)
    {
        case 6: musicPlay(); break;
        case 7: deleteCurrentRow(); break;
        default: break;
    }
}

void MusicSongCheckToolsQualityTableWidget::selectedAllItems(bool check)
{
    for(int i=0; i<rowCount(); ++i)
    {
        item(i, 0)->setData(MUSIC_CHECK_ROLE, check ? Qt::Checked : Qt::Unchecked);
    }

    if(!check)
    {
        clearSelection();
        setCurrentIndex(QModelIndex());
    }
    else
    {
        selectAll();
    }
}

void MusicSongCheckToolsQualityTableWidget::musicPlay()
{
    if(rowCount() == 0 || currentRow() < 0)
    {
        return;
    }

    const QTableWidgetItem *it = item(currentRow(), 6);
    if(it)
    {
        const QString &path = it->data(MUSIC_DATA_ROLE).toString();
        Q_EMIT addSongToPlaylist(QStringList(QFile::exists(path) ? path : QString()));
    }
}

void MusicSongCheckToolsQualityTableWidget::deleteCurrentRow()
{
    if(rowCount() == 0 || currentRow() < 0)
    {
        return;
    }
    removeRow(currentRow());
}
