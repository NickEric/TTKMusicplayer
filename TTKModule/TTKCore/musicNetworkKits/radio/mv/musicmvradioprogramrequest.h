#ifndef MUSICMVRADIOPROGRAMREQUEST_H
#define MUSICMVRADIOPROGRAMREQUEST_H

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

#include "musicabstractmvradiorequest.h"

/*! @brief The class of mv radio program request.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT MusicMVRadioProgramRequest : public MusicAbstractMVRadioRequest
{
    Q_OBJECT
    TTK_DECLARE_MODULE(MusicMVRadioProgramRequest)
public:
    explicit MusicMVRadioProgramRequest(QObject *parent = nullptr);

public Q_SLOTS:
    /*!
     * Download data from net finished.
     */
    virtual void downLoadFinished() override final;

protected:
    /*!
     * Read mv tags(size\bitrate\url) from query results.
     */
    void readFromMusicMVAttribute(MusicObject::MusicSongInformation *info);
    /*!
     * Read mv info attribute from query results.
     */
    void readFromMusicMVAttribute(MusicObject::MusicSongInformation *info, const QVariantMap &key);

};

#endif // MUSICMVRADIOPROGRAMREQUEST_H
