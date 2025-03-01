#ifndef MUSICLOCALSONGSTABLEWIDGET_H
#define MUSICLOCALSONGSTABLEWIDGET_H

/***************************************************************************
 * This file is part of the TTK Music Player project
 * Copyright (C) 2015 - 2022 Greedysky Studio

 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License along
 * with this program; If not, see <http://www.gnu.org/licenses/>.
 ***************************************************************************/

#include "musicabstractsongslisttablewidget.h"

/*! @brief The class of the lcal songs table widget.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT MusicLocalSongsTableWidget : public MusicAbstractSongsListTableWidget
{
    Q_OBJECT
    TTK_DECLARE_MODULE(MusicLocalSongsTableWidget)
public:
    /*!
     * Object contsructor.
     */
    explicit MusicLocalSongsTableWidget(QWidget *parent = nullptr);
    ~MusicLocalSongsTableWidget();

    /*!
     * Clear current items.
     */
    void clear();
    /*!
     * Add show list items.
     */
    void addItems(const QFileInfoList &path);
    /*!
     * Set files container.
     */
    inline void setFiles(const QFileInfoList &path) { m_fileNames = path; }
    /*!
     * Get files container.
     */
    inline const QFileInfoList &getFiles() const { return m_fileNames; }

public Q_SLOTS:
    /*!
     * Table widget item cell click.
     */
    virtual void itemCellClicked(int row, int column) override final;
    /*!
     * Override the widget event.
     */
    virtual void contextMenuEvent(QContextMenuEvent *event) override final;

protected:
    QFileInfoList m_fileNames;

};

typedef QMap<QString , QFileInfoList> MusicInfoData;
typedef QMapIterator<QString , QFileInfoList> MusicInfoDataIterator;

/*! @brief The class of the lcal songs info table widget.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT MusicLocalSongsInfoTableWidget : public MusicAbstractTableWidget
{
    Q_OBJECT
    TTK_DECLARE_MODULE(MusicLocalSongsInfoTableWidget)
public:
    /*!
     * Object contsructor.
     */
    explicit MusicLocalSongsInfoTableWidget(QWidget *parent = nullptr);

    /*!
     * Clear current items.
     */
    void clear();
    /*!
     * Add show list item.
     */
    void addItems(const MusicInfoData &data);

Q_SIGNALS:
    /*!
     * Update file list.
     */
    void updateFileList(const QFileInfoList &list);

public Q_SLOTS:
    /*!
     * Table widget item cell click.
     */
    virtual void itemCellClicked(int row, int column) override final;
    /*!
     * Table widget list double cell click.
     */
    void itemDoubleClicked(int row, int column);

};

#endif // MUSICLOCALSONGSTABLEWIDGET_H
