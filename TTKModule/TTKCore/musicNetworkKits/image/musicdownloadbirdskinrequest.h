#ifndef MUSICDOWNLOADBIRDSKINREQUEST_H
#define MUSICDOWNLOADBIRDSKINREQUEST_H

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

#include "musicabstractdownloadskinrequest.h"

/*! @brief The class of download bird skin background.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT MusicDownloadBirdSkinRequest : public MusicAbstractDownloadSkinRequest
{
    Q_OBJECT
    TTK_DECLARE_MODULE(MusicDownloadBirdSkinRequest)
public:
    /*!
     * Object contsructor.
     */
    explicit MusicDownloadBirdSkinRequest(QObject *parent = nullptr);

    /*!
     * Start to download data from net.
     */
    virtual void startToDownload() override final;
    /*!
     * Start to download data from net.
     */
    virtual void startToDownload(const QString &id) override final;

Q_SIGNALS:
    /*!
     * Send download data from net.
     */
    void downLoadItemsChanged(const MusicSkinRemoteGroup &bytes);

public Q_SLOTS:
    /*!
     * Download data from net finished.
     */
    virtual void downLoadFinished(const QByteArray &bytes) override final;
    /*!
     * Download item data from net finished.
     */
    void downLoadItemsFinished(const QByteArray &bytes);

};

#endif // MUSICDOWNLOADBIRDSKINREQUEST_H
