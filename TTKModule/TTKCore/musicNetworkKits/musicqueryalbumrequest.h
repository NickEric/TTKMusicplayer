#ifndef MUSICQUERYALBUMREQUEST_H
#define MUSICQUERYALBUMREQUEST_H

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

#include "musicabstractqueryrequest.h"

/*! @brief The class of query album download data from net.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT MusicQueryAlbumRequest : public MusicAbstractQueryRequest
{
    Q_OBJECT
    TTK_DECLARE_MODULE(MusicQueryAlbumRequest)
public:
    /*!
     * Object contsructor.
     */
    explicit MusicQueryAlbumRequest(QObject *parent = nullptr);

    /*!
     * Start to Search data from name and type.
     */
    virtual void startToSearch(QueryType type, const QString &album) override final;
    /*!
     * Start to Search data from name and type.
     */
    virtual void startToSearch(const QString &album) = 0;

Q_SIGNALS:
    /*!
     * Create the current album info item.
     */
    void createAlbumInfoItem(const MusicResultsItem &item);

};

#endif // MUSICQUERYALBUMREQUEST_H
