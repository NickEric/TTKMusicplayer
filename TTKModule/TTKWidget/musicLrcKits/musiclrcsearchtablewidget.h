#ifndef MUSICLRCSEARCHTABLEWIDGET_H
#define MUSICLRCSEARCHTABLEWIDGET_H

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

/*! @brief The class of the lrc search table widget.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT MusicLrcSearchTableWidget : public MusicItemSearchTableWidget
{
    Q_OBJECT
    TTK_DECLARE_MODULE(MusicLrcSearchTableWidget)
public:
    /*!
     * Object contsructor.
     */
    explicit MusicLrcSearchTableWidget(QWidget *parent = nullptr);
    ~MusicLrcSearchTableWidget();

    /*!
     * Start search query by text.
     */
    virtual void startSearchQuery(const QString &text) override final;
    /*!
     * Data download to local file.
     */
    virtual void musicDownloadLocal(int row) override final;

Q_SIGNALS:
    /*!
     * Lrc search state is finished.
     */
    void resolvedSuccess();
    /*!
     * Lrc download state is finished.
     */
    void lrcDownloadStateChanged(const QString &name);

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

protected:
    /*!
     * Override the widget event.
     */
    virtual void contextMenuEvent(QContextMenuEvent *event) override final;

};

#endif // MUSICLRCSEARCHTABLEWIDGET_H
