#ifndef MUSICSEMAPHORELOOP_H
#define MUSICSEMAPHORELOOP_H

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

#include <QTimer>
#include <QEventLoop>
#include "musicglobaldefine.h"

/*! @brief The class of the semaphore event loop.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT MusicSemaphoreLoop : public QEventLoop
{
    Q_OBJECT
    TTK_DECLARE_MODULE(MusicSemaphoreLoop)
public:
    /*!
     * Object contsructor.
     */
    explicit MusicSemaphoreLoop(QObject *parent = nullptr);
    ~MusicSemaphoreLoop();

    /*!
     * Event loop start.
     */
    int exec(ProcessEventsFlags flags = AllEvents);

protected:
    QTimer m_timer;

};

#endif // MUSICSEMAPHORELOOP_H
