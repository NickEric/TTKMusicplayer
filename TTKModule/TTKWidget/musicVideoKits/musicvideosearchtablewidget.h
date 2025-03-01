#ifndef MUSICVIDEOSEARCHTABLEWIDGET_H
#define MUSICVIDEOSEARCHTABLEWIDGET_H

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

#include "musicitemsearchtablewidget.h"
#include "musicabstractqueryrequest.h"

Q_DECLARE_METATYPE(MusicObject::MusicSongInformation)

/*! @brief The class of the video item play data item.
 * @author Greedysky <greedysky@163.com>
 */
typedef struct TTK_MODULE_EXPORT MusicVideoItem
{
    QString m_name;
    QString m_url;
    QString m_id;
    QString m_server;
}MusicVideoItem;


/*! @brief The class of the video search table widget.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT MusicVideoSearchTableWidget : public MusicItemSearchTableWidget
{
    Q_OBJECT
    TTK_DECLARE_MODULE(MusicVideoSearchTableWidget)
public:
    /*!
     * Object contsructor.
     */
    explicit MusicVideoSearchTableWidget(QWidget *parent = nullptr);
    ~MusicVideoSearchTableWidget();

    /*!
     * Start search query by text.
     */
    virtual void startSearchQuery(const QString &text) override final;
    /*!
     * Start search query by given id.
     */
    void startSearchSingleQuery(const QString &text);
    /*!
     * Start search query by given data.
     */
    void startSearchSingleQuery(const QVariant &data);
    /*!
     * Data download to local file.
     */
    virtual void musicDownloadLocal(int row) override final;

    /*!
     * Resize widget size by delta.
     */
    void resizeWindow(int delta);

Q_SIGNALS:
    /*!
     * Set current media name and url to play.
     */
    void mediaUrlPathChanged(const MusicVideoItem &item);

public Q_SLOTS:
    /*!
     * Table widget item cell enter.
     */
    virtual void itemCellEntered(int row, int column) override final;
    /*!
     * Table widget item cell click.
     */
    virtual void itemCellClicked(int row, int column) override final;
    /*!
     * Clear All Items.
     */
    virtual void clearAllItems() override final;
    /*!
     * Create searched items.
     */
    virtual void createSearchedItem(const MusicSearchedItem &songItem) override final;
    /*!
     * Item has double clicked.
     */
    virtual void itemDoubleClicked(int row, int column) override final;
    /*!
     * Get music media information data.
     */
    void musicMediaInfo(MusicObject::MusicSongAttributes &data);
    /*!
     * Download current mv by controller.
     */
    void downloadLocalFromControl();

protected:
    /*!
     * Override the widget event.
     */
    virtual void contextMenuEvent(QContextMenuEvent *event) override final;
    /*!
     * Download movie to local file by index.
     */
    void downloadLocalMovie(int row);

    QString m_currentSongName;
    bool m_singleRadioMode;

};

#endif // MUSICVIDEOSEARCHTABLEWIDGET_H
