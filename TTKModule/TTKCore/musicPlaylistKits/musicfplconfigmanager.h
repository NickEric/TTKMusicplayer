#ifndef MUSICFPLCONFIGMANAGER_H
#define MUSICFPLCONFIGMANAGER_H

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

#include "musicplaylistinterface.h"

/*! @brief The class of the foobar2k playlist Config Manager.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT MusicFPLConfigManager : public MusicPlaylistReader, private MusicPlaylistInterface
{
    TTK_DECLARE_MODULE(MusicFPLConfigManager)
public:
    /*!
     * Object contsructor.
     */
    explicit MusicFPLConfigManager();

    /*!
     * Read datas from config file.
     */
    virtual bool readPlaylistData(MusicSongItems &items) override final;
    /*!
     * Write datas into config file.
     */
    virtual bool writePlaylistData(const MusicSongItems &items, const QString &path) override final;

};

#endif // MUSICFPLCONFIGMANAGER_H
