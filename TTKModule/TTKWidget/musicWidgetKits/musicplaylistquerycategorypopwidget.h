#ifndef MUSICPLAYLISTQUERYCATEGORYPOPWIDGET_H
#define MUSICPLAYLISTQUERYCATEGORYPOPWIDGET_H

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

#include "musictoolmenuwidget.h"
#include "musiccategoryconfigmanager.h"

/*! @brief The class of the playlist music query category item.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT MusicPlaylistQueryCategoryItem : public QWidget
{
    Q_OBJECT
    TTK_DECLARE_MODULE(MusicPlaylistQueryCategoryItem)
public:
    /*!
     * Object contsructor.
     */
    explicit MusicPlaylistQueryCategoryItem(QWidget *parent = nullptr);

    /*!
     * Set current category.
     */
    void setCategory(const MusicResultsCategory &category);

Q_SIGNALS:
    /*!
     * Current category changed.
     */
    void categoryChanged(const MusicResultsCategoryItem &category);

public Q_SLOTS:
    /*!
     * Current category item clicked.
     */
    void buttonClicked(int index);

protected:
    MusicResultsCategory m_category;

};



/*! @brief The class of the playlist music found category pop widget.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT MusicPlaylistFoundCategoryPopWidget : public MusicToolMenuWidget
{
    Q_OBJECT
    TTK_DECLARE_MODULE(MusicPlaylistFoundCategoryPopWidget)
public:
    /*!
     * Object contsructor.
     */
    explicit MusicPlaylistFoundCategoryPopWidget(QWidget *parent = nullptr);

    /*!
     * Set current category by input server.
     */
    void setCategory(const QString &server, QObject *obj);
    /*!
     * Close the menu dialog.
     */
    void closeMenu();

public Q_SLOTS:
    /*!
     * To popup menu.
     */
    virtual void popupMenu() override final;

protected:
    /*!
     * Create all widget in layout.
     */
    void initWidget();

};

#endif // MUSICPLAYLISTQUERYCATEGORYPOPWIDGET_H
