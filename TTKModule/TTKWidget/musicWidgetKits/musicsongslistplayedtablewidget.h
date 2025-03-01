#ifndef MUSICSONGSLISTPLAYEDTABLEWIDGET_H
#define MUSICSONGSLISTPLAYEDTABLEWIDGET_H

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

class MusicSongsListPlayedWidget;

/*! @brief The class of the songs played queue list table widget.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT MusicSongsListPlayedTableWidget : public MusicAbstractSongsListTableWidget
{
    Q_OBJECT
    TTK_DECLARE_MODULE(MusicSongsListPlayedTableWidget)
public:
    /*!
     * Object contsructor.
     */
    explicit MusicSongsListPlayedTableWidget(QWidget *parent = nullptr);
    ~MusicSongsListPlayedTableWidget();

    /*!
     * Update songs file names in table.
     */
    virtual void updateSongsFileName(const MusicSongs &songs) override final;
    /*!
     * Select the current play row by given index.
     */
    virtual void selectRow(int index) override final;

    /*!
     * Clear play queue state.
     */
    void clearPlayQueueState();
    /*!
     * Set play queue state.
     */
    void setPlayQueueState(int row);

    /*!
     * Clear All Items.
     */
    void clearAllItems();
    /*!
     * Select the current played row.
     */
    void selectPlayedRow();
    /*!
     * Adjust current play widget row.
     */
    void adjustPlayWidgetRow();

Q_SIGNALS:
    /*!
     * Delete items from indexs .
     */
    void deleteItemAt(const TTKIntList &index);

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
     * Delete item from list at current row.
     */
    virtual void setDeleteItemAt() override final;

protected:
    /*!
     * Override the widget event.
     */
    virtual void contextMenuEvent(QContextMenuEvent *event) override final;

    MusicSongsListPlayedWidget *m_musicSongsPlayWidget;

};

#endif // MUSICSONGSLISTPLAYEDTABLEWIDGET_H
